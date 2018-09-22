# 生物传感器工程
这是一个包含软件和硬件方案的生物传感器工程。
# 概述
这个工程的硬件方案包括传感器模块BIO-M001A、模块转接板PINBOARD-M001A和评估主板MED-MAIN-DEMO。  

BIO-M001A 是一款一体化多参数健康监测模块。它测量和处理包括HR（心率），RESP（呼吸）,ECG（心电），PPG（脉搏波），SPO2（血氧），GSR（皮电），BIA（人体阻抗分析）和计步运动/睡眠等多类型基础生物数据。   

BIO-M001A集成红（660nm）、绿（520nm）和红外（940nm）三种光收发传感电路，实现PPG相关应用；支持4电极接入，实现人体电及阻抗活动的相关应用；板载14位三轴Gsensor，实现运动功能需求。  

BIO-M001A内嵌带生物模拟前端和24位模数转换器的MCU/DSP单元，运行的算法核能完成滤波、人体综合行为判定等数据分析，比如运动识别等。硬件接口支持SPI/I2C/UART可选，FPC连接器参考[DF37NB-30DS-0.4V](https://www.hirose.com/product/en/products/DF37/DF37NB-30DS-0.4V%2851%29/)。

模块转接板PINBOARD-M001A主要负责模块BIO-M001A的fpc接口到评估主板或其它DIY主板的转接，它兼容市面上主流的开源硬件接口。

评估主板采用[NRF52832蓝牙ble芯片](https://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52832)，来自于NordicSemi

这个工程的软件方案包括评估主板上MCU（NRF52832）的固件和基于LabWindows CVI 2017开发的PC端windows评估软件。我们也正在开发基于ANDROID的评估APK，到时也会开源释放。

# 硬件--[传感器模块BIO-M001A](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_UM_CN.pdf)
![image](https://github.com/feelkit/BIO_SENSOR/raw/master/image/M001A.jpg)
## 功能描述
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
# 硬件--模块转接板PINBOARD-M001A
![image](https://github.com/feelkit/BIO_SENSOR/raw/master/image/pinboard.jpg)
转接板的主要功能就是把FPC接口转成主流的开源硬件接口，方便扩展支持更多的硬件评估平台。
# 硬件--评估主板MED-MAIN-DEMO
![image](https://github.com/feelkit/BIO_SENSOR/raw/master/image/MAIN_BOARD.jpg)
# 资源
## 传感器模块BIO-M001A结构文件（1：1比例，dxf文件），[PCB顶层布局](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_TOP.dxf)，[PCB底层布局](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_BOT.dxf)。