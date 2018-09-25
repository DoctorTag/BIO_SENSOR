# 生物传感器工程
## 一个包含软件和硬件方案的生物传感器工程。
# 概述
这个工程包括[生物多参数传感器模组](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_SPEC_CN.pdf)、及针对该模组设计的评估板、软件方案包括蓝牙主板固件和桌面/移动评估工具。 

传感器模组（BIO-M001A）是一款一体化多参数健康监测模组。它测量和处理包括HR（心率），RESP（呼吸）,ECG（心电），PPG（脉搏波），SPO2（血氧），GSR（皮电），BIA（人体阻抗分析）和计步运动/睡眠等多类型基础人体体征数据。 

评估主板采用NRF52832蓝牙ble芯片，来自于NordicSemi

软件方案包括评估主板上[MCU（NRF52）的固件工程](https://github.com/feelkit/bioModule_NRF52_BLE)；基于LabWindows CVI 2017开发的[PC端windows评估软件工程](https://github.com/feelkit/bioDemo_labwindows_cvi)。我们也正在开发基于ANDROID的评估APK，到时会开源释放。

# [传感器模组BIO-M001A](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_UM_CN.pdf)
![image](https://github.com/feelkit/BIO_SENSOR/raw/master/image/M001A.jpg)
模组BIO-M001A集成红（660nm）、绿（520nm）和红外（940nm）三种光收发传感电路，实现PPG相关应用；支持4电极接入，实现人体电及阻抗活动的相关应用；板载14位三轴Gsensor，实现运动功能需求。  

BIO-M001A内嵌带生物模拟前端和24位模数转换器的MCU/DSP单元，运行的算法核能完成滤波、人体综合行为判定等数据分析，比如运动识别等。硬件接口支持SPI/I2C/UART可选，FPC连接器参考[DF37NB-30DS-0.4V](https://www.hirose.com/product/en/products/DF37/DF37NB-30DS-0.4V%2851%29/)。

## 模组功能描述
### 集成单导心电（ECG）:
- 三电极配置，支持右腿驱动;
- 导联脱落检测;
### 四电极生物阻抗测量:
- 内置DAC和多频率波形发生电路;
- 支持RESP（呼吸）,BIA （人体阻抗分析）和皮肤电（ GSR） 等;
### 脉搏波（PPG）电路:
- 支持520nm,660nm和940nm三波长led，灵活的时序控制器;
- 支持心率（HR），血氧（SPO2）和红外接近感应等模式;
### 电极感应电路:
- 支持导联脱落检测;
- 独特的电极新型功能支持;

### 运动计步:
- 内置14位三轴Gsensor，可选范围±2g, ±4g, ±8g, ±16g;
- 支持运动计步与识别等;

### 通讯接口： 
- SPI/UART/I2C可选；
- FPC连接器参考[DF37NB-30DS-0.4V](https://www.hirose.com/product/en/products/DF37/DF37NB-30DS-0.4V%2851%29/),制造商为hirose; 

### 超小体积，适合手环（表）装配使用： 
- 22×26mm;
## 应用
1. 可穿戴设备（手环/手表等）； 
2. 健康监测设备；
3. 手持便携设备；

# 传感器模组评估包
![image](https://github.com/feelkit/BIO_SENSOR/raw/master/image/demo_device.jpg)
这个工程硬件包括蓝牙ble主板，模组转接板；软件包括蓝牙BLE固件，PC/移动端apk。关于评估板的使用，请查阅[用户手册](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/demo_UM_CN.pdf)。
## 蓝牙BLE主板
评估主板采用的[NRF52832蓝牙ble芯片](https://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52832)支持I2C,SPI或UART三种任一方式连接[传感器模组BIO-M001A](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_UM_CN.pdf)；通过UART连接[PC端windows评估软件](https://github.com/feelkit/BIO_SENSOR/raw/master/tool/bio_demo.exe)；通过蓝牙BLE连接手机端apk。详情请参考[用户手册](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/MAIN_UM_CN.pdf)。

## 转接板
转接板的主要目标是把FPC接口转成主流的开源硬件接口，方便该模组扩展支持更多其它厂商的评估主板；详情请参考[用户手册](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/PinBoard_UM_CN.pdf)。
## 蓝牙ble固件
请参考这个工程：[https://github.com/feelkit/bioModule_NRF52_BLE](https://github.com/feelkit/bioModule_NRF52_BLE)

## LabWindows CVI评估工具
请参考这个工程：[https://github.com/feelkit/bioDemo_labwindows_cvi](https://github.com/feelkit/bioDemo_labwindows_cvi)
# 资源

1. 传感器模块BIO-M001A 
- 传感器模组简介：[https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_SPEC_CN.pdf](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_SPEC_CN.pdf)
- 传感器模组用户手册：
[https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_UM_CN.pdf](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_UM_CN.pdf)
- 传感器模块结构文件（1：1比例，dxf文件）：
[PCB顶层布局CAD文件](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_TOP.dxf)，[PCB底层布局CAD文件](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_BOT.dxf)。

2. 蓝牙ble主板 MED_MAIN_DEMO
- 主板用户手册：[https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/MAIN_UM_CN.pdf](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/MAIN_UM_CN.pdf)
- 主板原理图及pcb开源工程：
[https://lceda.cn/seanfan/med_main_nrf](https://lceda.cn/seanfan/med_main_nrf)
- 主板采用的蓝牙BLE模组：[http://www.freqchina.com/uploads/soft/201801/PTR9618_CN%20V1.4.pdf](http://www.freqchina.com/uploads/soft/201801/PTR9618_CN%20V1.4.pdf)
- 主板蓝牙ble固件工程：
[https://github.com/feelkit/bioModule_NRF52_BLE](https://github.com/feelkit/bioModule_NRF52_BLE) 
- NRF52832蓝牙ble芯片资料：[https://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52832](https://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52832)

3. 模组转接板 PinBoard-M001A
- 模组转接板用户手册：
[https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/PinBoard_UM_CN .pdf](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/PinBoard_UM_CN .pdf)
- 转接板原理图及pcb开源工程：
[https://lceda.cn/seanfan/wmmed_ext_openhd](https://lceda.cn/seanfan/wmmed_ext_openhd)
- FPC连接器[DF37NB-30DS-0.4V] 
[https://www.hirose.com/product/en/products/DF37/DF37NB-30DS-0.4V%2851%29/](https://www.hirose.com/product/en/products/DF37/DF37NB-30DS-0.4V%2851%29/)
- FPC连接线原理图：
[https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/fpc_M001A_sch.pdf](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/fpc_M001A_sch.pdf)

# Contact
如果你有技术方面问题与想法想与我沟通，可以通过下面的方式联系我。

QQ： 4646079

Email： fanfeiwu@gmail.com