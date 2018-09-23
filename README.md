# 生物传感器工程
## 一个包含软件和硬件方案的生物传感器工程。
# 概述
这个工程包括[传感器模组](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_SPEC_CN.pdf)、及其评估主板、主板固件和桌面/移动评估软件。 

传感器模组（BIO-M001A）是一款一体化多参数健康监测模组。它测量和处理包括HR（心率），RESP（呼吸）,ECG（心电），PPG（脉搏波），SPO2（血氧），GSR（皮电），BIA（人体阻抗分析）和计步运动/睡眠等多类型基础人体体征数据。 

评估主板采用NRF52832蓝牙ble芯片，来自于NordicSemi

软件方案包括评估主板上[MCU（NRF52）的固件工程](https://github.com/feelkit/bioModule_NRF52_BLE)；基于LabWindows CVI 2017开发的[PC端windows评估软件工程](https://github.com/feelkit/bioDemo_labwindows_cvi)。我们也正在开发基于ANDROID的评估APK，到时会开源释放。

# 硬件--[传感器模组BIO-M001A](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_UM_CN.pdf)
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

# 硬件--评估主板
评估主板采用的[NRF52832蓝牙ble芯片](https://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52832)支持I2C,SPI或UART三种任一方式连接[传感器模块BIO-M001A](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_UM_CN.pdf)；通过UART连接[PC端windows评估软件](https://github.com/feelkit/BIO_SENSOR/raw/master/tool/bio_demo.exe)；通过蓝牙BLE连接手机端apk。

# 硬件--转接板
转接板的目标就是把FPC接口转成主流的开源硬件接口，方便扩展支持更多其它厂商的评估主板。
# 软件--NRF52蓝牙ble评估方案
- 模块BIO-M001A驱动接口和控制；
- 传感器数据流采集和控制；
- 蓝牙BLE传感器PROFILE;

# 软件--LabWindows CVI评估方案
请参考这个工程：[https://github.com/feelkit/bioDemo_labwindows_cvi](https://github.com/feelkit/bioDemo_labwindows_cvi)
# 资源

- 传感器模块BIO-M001A结构文件（1：1比例，dxf文件），[PCB顶层布局CAD文件](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_TOP.dxf)，[PCB底层布局CAD文件](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_BOT.dxf)。
- NRF52832蓝牙ble芯片资料，[https://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52832](https://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52832)