# 🌱 智慧农业大棚管理系统

本项目旨在开发一个综合性智慧农业大棚管理系统，结合硬件和软件的集成方案，实现对大棚内环境的智能化管理和监测，从而提高农作物的生长质量和产量。该系统将实时收集并处理数据，通过前端管理平台直观地呈现给用户，帮助农户更好地管理农业生产。

## 📦 系统组成

### 硬件系统 (2.2.1)
1. **智能环境控制设备**  
   包括温度、湿度、光照、二氧化碳浓度等传感器及相应的调控设备，实时监测农作物生长环境的变化。通过这些传感器，系统能够自动调整环境参数，确保作物的最佳生长条件。

2. **自动化灌溉与施肥设备**  
   该设备基于智能环境控制设备反馈的信息，自动进行灌溉和施肥操作，以确保作物获得所需的水分和营养，提供稳定的生长环境。

3. **病虫害监测和防护设备**  
   使用诱虫灯、性诱剂等病虫害监测设备，实时监控大棚内的病虫害情况，及时采取防护措施，有效提高作物的质量和产量。

### 软件系统 (2.2.2)
1. **前端管理系统**  
   为农户提供便捷的大棚管理平台，通过该平台农户可以实时查看大棚内环境条件参数和作物生长状态，并可远程控制灌溉、通风等设备。该系统进一步提高了农业大棚的操作性和管理性，方便农户随时掌握生产情况。

2. **后端数据处理系统**  
   通过高效的数据存储、检索和分析，后端系统能够处理传感器数据和作物生长信息，为农户提供作物生长周期、预期产量等有价值的信息，帮助农户更好地规划和控制产量。

3. **智能问答系统**  
   针对农户在大棚生产中遇到的常见问题，系统汇总农业专家、专业文献等信息来源，基于自然语言处理技术提供自动化解答。该问答系统可以有效辅助农户解决日常管理中的常见问题，降低咨询成本。

## 🌐 系统架构

本项目基于物联网 (IoT) 和云计算架构，结合硬件传感器、数据处理、前端用户界面和自然语言处理等技术，打造一体化的智慧大棚管理系统。系统架构包括：

- **数据采集层**：包括温湿度传感器、光照传感器、CO₂传感器等，采集大棚内的环境数据。
- **数据传输层**：通过无线网络（如 LoRa、Wi-Fi）将数据实时传输到云端。
- **数据处理层**：后端服务器进行数据存储、分析，并生成可视化报表。
- **应用层**：农户通过前端管理系统查看和管理大棚，并获取智能问答系统提供的帮助。

## 🛠 技术栈

- **前端**：React, Vue.js
- **后端**：Node.js, Python (Flask), MySQL, MongoDB
- **数据处理**：Pandas, Numpy
- **物联网协议**：MQTT, HTTP, LoRa
- **云平台**：AWS, Azure
- **机器学习与自然语言处理**：TensorFlow, NLP Libraries (NLTK, spaCy)

## 📈 系统功能

- 实时环境监测与反馈调节
- 自动灌溉与精准施肥
- 病虫害智能监测与防护
- 作物生长数据分析与预测
- 农户问答系统，提供自动化技术支持

## 🚀 安装与使用

1. **克隆本项目**：
   ```bash
   git clone https://PCFXPCFX/The-first-warehouse-in-the-country.git
   ```
