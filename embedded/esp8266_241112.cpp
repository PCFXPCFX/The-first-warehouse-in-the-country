#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <Adafruit_SGP30.h>
#include <Adafruit_BH1750.h>
#include <DHT.h>

// WiFi 配置
ESP8266WiFiMulti wifiMulti;

// 定义常量
#define SERVER_ADDRESS "http://your.server.com" // 固定的服务器地址
#define UPLOAD_INTERVAL 60000                   // 数据上传间隔 (ms)

// I2C 软件定义
#define SDA_PIN D1
#define SCL_PIN D2

// DHT11 配置
#define DHTPIN D3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// 土壤湿度传感器
#define SOIL_MOISTURE_PIN D4

// 外接泵机控制
#define PUMP_PIN D0

// 蜂鸣器
#define BUZZER_PIN D5
int melody[] = {262, 262, 392, 392, 440, 440, 392, 349, 349, 330, 330, 294, 294, 262};
int noteDurations[] = {4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 2};

// 初始化传感器对象
Adafruit_SGP30 sgp;
Adafruit_BH1750 lightMeter;

// 初始化传感器
void initSensors() {
    Wire.begin(SDA_PIN, SCL_PIN);

    // 初始化 SGP30
    if (!sgp.begin()) {
        Serial.println("SGP30 initialization failed!");
        while (1);
    }
    Serial.println("SGP30 initialized.");

    // 初始化 GY-302
    if (!lightMeter.begin()) {
        Serial.println("GY-302 initialization failed!");
        while (1);
    }
    Serial.println("GY-302 initialized.");

    // 初始化 DHT11
    dht.begin();
    Serial.println("DHT11 initialized.");

    // 初始化泵机和土壤湿度传感器
    pinMode(PUMP_PIN, OUTPUT);
    digitalWrite(PUMP_PIN, LOW);
    pinMode(SOIL_MOISTURE_PIN, INPUT);

    Serial.println("Sensors initialized.");
}

// WiFi 连接
void connectToWiFi() {
    wifiMulti.addAP("WiFi1", "password1");
    wifiMulti.addAP("WiFi2", "password2");
    wifiMulti.addAP("WiFi3", "password3");

    Serial.println("Connecting to WiFi...");
    while (wifiMulti.run() != WL_CONNECTED) {
        delay(1000);
        Serial.print('.');
    }

    Serial.println("\nConnected to WiFi!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

// 与服务器握手
void handshakeWithServer() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String url = String(SERVER_ADDRESS) + "/handshake?device_ip=" + WiFi.localIP().toString();
        http.begin(url);
        int httpCode = http.GET();
        if (httpCode == HTTP_CODE_OK) {
            Serial.println("Handshake successful!");
        } else {
            Serial.println("Handshake failed, code: " + String(httpCode));
        }
        http.end();
    }
}

// 上传数据到服务器
void uploadDataToServer() {
    if (WiFi.status() == WL_CONNECTED) {
        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity();
        uint16_t eco2, tvoc;
        sgp.IAQmeasure();
        eco2 = sgp.eCO2;
        tvoc = sgp.TVOC;
        float light = lightMeter.readLightLevel();
        int soilMoisture = analogRead(SOIL_MOISTURE_PIN);

        String jsonPayload = String("{\"temperature\":") + temperature +
                             ",\"humidity\":" + humidity +
                             ",\"eco2\":" + eco2 +
                             ",\"tvoc\":" + tvoc +
                             ",\"light\":" + light +
                             ",\"soilMoisture\":" + soilMoisture + "}";

        HTTPClient http;
        String url = String(SERVER_ADDRESS) + "/upload";
        http.begin(url);
        http.addHeader("Content-Type", "application/json");
        int httpCode = http.POST(jsonPayload);

        if (httpCode == HTTP_CODE_OK) {
            Serial.println("Data upload successful!");
        } else {
            Serial.println("Data upload failed, code: " + String(httpCode));
        }
        http.end();
    }
}

// 检查泵机控制状态
void checkPumpControl() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String url = String(SERVER_ADDRESS) + "/pump_status";
        http.begin(url);
        int httpCode = http.GET();
        if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            if (payload == "ON") {
                digitalWrite(PUMP_PIN, HIGH);
            } else if (payload == "OFF") {
                digitalWrite(PUMP_PIN, LOW);
            }
        }
        http.end();
    }
}

// 播放《小星星》
void playMelody() {
    for (int thisNote = 0; thisNote < 14; thisNote++) {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(BUZZER_PIN, melody[thisNote], noteDuration);
        delay(noteDuration * 1.3);
        noTone(BUZZER_PIN);
    }
}

void setup() {
    Serial.begin(115200);
    initSensors();
    connectToWiFi();
    handshakeWithServer();
}

void loop() {
    unsigned long currentTime = millis();

    if (currentTime - lastUploadTime > UPLOAD_INTERVAL) {
        uploadDataToServer();
        lastUploadTime = currentTime;
    }

    checkPumpControl();
    // playMelody(); // 可根据条件调用
}
