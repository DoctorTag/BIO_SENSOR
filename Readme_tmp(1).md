# 生物传感器工程
## 一个包含软件和硬件方案的生物传感器工程。
### 概述
这个工程包括多种生物医学传感器、及针对这些传感器设计的评估板、软件开发框架和桌面/移动评估工具。 
### 传感器

我们针对健康应用设计的传感器, 包括:

| 微型多参数健康采集模组F58 | 压电薄膜非接触式健康传感器 | 
|:----:|:----:|
|  [<img src="https://github.com/feelkit/BIO_SENSOR/raw/master/image/F58.png" width="400" alt ="BioSensor-F58 Development Board" align="center" />](https://docs.espressif.com/projects/esp-adf/en/latest/get-started/get-started-esp32-lyrat.html)  |  [<img src="https://github.com/feelkit/BIO_SENSOR/raw/master/image/y58.png" width="380" alt ="BCG-Y58 Development Board" align="center" />](https://docs.espressif.com/projects/esp-adf/en/latest/get-started/get-started-esp32-lyratd-msc.html)  |  
|  [Getting Started with BioSensor-F58](https://docs.espressif.com/projects/esp-adf/en/latest/get-started/get-started-esp32-lyrat.html)  |  [Getting Started with BCG-Y58](https://docs.espressif.com/projects/esp-adf/en/latest/get-started/get-started-esp32-lyrat-mini.html)  |  

#### BioSensor-F58:
F58是一款一体化多参数健康监测模块。它测量和处理包括ECG（心电），RESP（呼吸），HR（心率），PPG（脉搏波），SPO2（血氧），GSR（皮电），BIA（人体阻抗分析），体重，体温，EMG(肌电),EEG(脑电)或其它类型的传感器信号（如压电传感器,实现非接触式心率，呼吸等测量）。

![image](https://github.com/feelkit/BIO_SENSOR/raw/master/image/F58.png)
#### BCG-Y58:
采用压电薄膜传感技术，带状传感器铺在枕头、褥子、床垫或座椅下方；人只要躺/坐着，非接触式，无需任何操作即可自动工作;

测量心率，呼吸率，体动（睡眠）和判断离/在床等；HRV分析，诊断OSAHS；

![image](https://github.com/feelkit/BIO_SENSOR/raw/master/image/y58.png)

### Healthcare Development Framework(HDF)
HDF的目标是创建一个关于健康应用的跨平台开发框架，包括传感器驱动，健康数据算法分析和应用；比如峰值查找，心率计算，HRV分析等等。当前支持C/C++，硬件支持来自于乐鑫的ESP32。

### 评估软件工具
基于LabWindows CVI 2017开发的[PC端windows评估软件工程](https://github.com/feelkit/bioDemo_labwindows_cvi)。我们也正在开发基于ANDROID的评估APK，到时会开源释放。

LabWindows CVI评估工具请参考这个工程：[https://github.com/feelkit/bioDemo_labwindows_cvi](https://github.com/feelkit/bioDemo_labwindows_cvi)

### Contact
如果你有技术方面问题与想法想与我沟通，可以通过下面的方式联系我。

QQ： 4646079

Email： fanfeiwu@gmail.com

WWW : [www.feelkit.com](http://www.feelkit.com).



