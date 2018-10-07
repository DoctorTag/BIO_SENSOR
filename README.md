# Bio-sensor Project                                          [中文](https://github.com/feelkit/BIO_SENSOR/blob/master/Readme_cn.md)
## A completed Bio-sensor project including software and hardware solutions; also depending on the following projects:
Bluetooth BLE Firmware project: [https://github.com/feelkit/bioModule_NRF52_BLE](https://github.com/feelkit/bioModule_NRF52_BLE)

Evaluation Tool using LabWindows CVI :
[https://github.com/feelkit/bioDemo_labwindows_cvi](https://github.com/feelkit/bioDemo_labwindows_cvi)

# Introduce
The project includes a Bio-module（[BIO-M001A](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_SPEC_EN.pdf)）, an evaluation board designed for the Bio-module, and software solutions including Bluetooth BLE firmware and desktop/mobile evaluation tools.

Bio-M001A is a Bio-module in healthcare;The Bio-module measures and transfers various types of bio-data including ECG, RESP, GSR, HR, PPG, HCM and BIA etc, integrated Bio-Processor with Analog Front-End to make an all-in-one health monitoring solution. The algorithm core runs in Bio-Processor,including SPO2,motion recognition,dynamic heart rate monitoring, trend analysis of blood pressure, Emotional and mental stress etc.
 
The evaluation board supports  Bluetooth BLE with NRF52832 chipset from NordicSemi.

The software solution includes Bluetooth firmware for NRF52,desktop evaluation tool about LabWindows CVI; We are also developing APK for ANDROID, which will be released and open-source .

# [Bio-Module : M001A](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_UM_EN.pdf)
![image](https://github.com/feelkit/BIO_SENSOR/raw/master/image/M001A.jpg)
The Bio-module integrates red (660 nm), green (520 nm) and infrared (940 nm) three-color LED and photodiode(PD) sensor to realize PPG-related applications; and supports four electrodes to achieve applications with human electrical activities and impedance activities; on-module 14-bit three-axis Gsensor for motion/sleep applications.

The Bio-module hardware interface supports SPI/I2C/UART optional, FPC connector reference [DF37NB-30DS-0.4V](https://www.hirose.com/product/en/products/DF37/DF37NB-30DS-0.4V%2851%29/).

## BIO-M001A FEATURES
### Single lead ECG :
- 3 electrodes with right leg driver;
- Lead-off detect;
### Bio-impedance with 4 electrodes:
- Built-in DAC and multi-frequency waveform generator;
- Support RESP,BIA and GSR etc;
### PPG:
- on-module red (660 nm), green (520 nm) and infrared (940 nm) LED and PD;
- Support HR,SPO2 and Bio-assay etc;
### Electrodes mean interface:
- Support electrodes as input keypad;
- Support pair of electrodes as data channel: eg,USB/UART etc;
- Support pair of electrodes as power charger channel;

### Gsensor:
- Built-in 14 bits 3-axis Gsensor, range + 2G, + 4G, + 8g, + 16g;
- Pedometer,Action recognition;

### Hardware interface:
- Optional SPI/UART/I2C;
- FPC connector [DF37NB-30DS-0.4V](https://www.hirose.com/product/en/products/DF37/DF37NB-30DS-0.4V%2851%29/),from hirose; 

### Small size, suitable for wristband devices:
- 22x26mm;

## BIO-M001A APPLICATIONS

1. Fitness,wristband devices;
2. Healthcare devices;
3. Mobile devices and robots etc;

# Development Kits for Bio-M001A
![image](https://github.com/feelkit/BIO_SENSOR/raw/master/image/DEMO1.png)
The evaluation hardware includes Bluetooth mainboard, pin-board; software includes Bluetooth BLE firmware, PC / mobile APP. How to use the evaluation board, please refer to [user's manual](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/demo_UM_EN.pdf).
## Bluetooth Mainboard
 The Mainboard supports  Bluetooth BLE with NRF52832 chipset from NordicSemi,using optional SPI/I2C/UART connecting the Bio-M001A;it communicates with APP via Bluetooth BLE. PC tool connects it by Uart. For the details,please refer to 
[user's manual](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/MAIN_UM_EN.pdf)。

## Pin-board
The Pin-board is used to turn FPC interface of Bio-M001A into a common open-source hardware interface (xRDUINO UNO), to support more mainboards from other suppliers.For the details,please refer to [user's manual](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/PinBoard_UM_EN.pdf)。
## Bluetooth Firmware
For the details,please refer to the project：[https://github.com/feelkit/bioModule_NRF52_BLE](https://github.com/feelkit/bioModule_NRF52_BLE)

## Evaluation tool
For the details,please refer to the project：[https://github.com/feelkit/bioDemo_labwindows_cvi](https://github.com/feelkit/bioDemo_labwindows_cvi)
# RESOURCES

1. BIO-M001A 
- Bio-sensor--M001A Specs：[https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_SPEC_EN.pdf](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_SPEC_EN.pdf)
- Bio-sensor--M001A User's Manual：
[https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_UM_EN.pdf](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_UM_EN.pdf)
- Bio-sensor--M001A CAD files (scale: 1:1, dxf file type)：
[Module top layout](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_TOP.dxf), [Module bottom layout](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_BOT.dxf).


2. Bluetooth BLE mainboard
- Mainboard User's Manual：[https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/MAIN_UM_EN.pdf](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/MAIN_UM_EN.pdf)
- BLE mainboard SCH and PCB project：
[https://lceda.cn/seanfan/med_main_nrf](https://lceda.cn/seanfan/med_main_nrf)
- Bluetooth BLE module with NRF52832：[http://www.freqchina.com/uploads/soft/201801/PTR9618_CN%20V1.4.pdf](http://www.freqchina.com/uploads/soft/201801/PTR9618_CN%20V1.4.pdf)
- Bluetooth Firmware Project：
[https://github.com/feelkit/bioModule_NRF52_BLE](https://github.com/feelkit/bioModule_NRF52_BLE) 
- Information about NRF52832：[https://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52832](https://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52832)

3. PinBoard-M001A
- PinBoard User's Manual：
[https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/PinBoard_UM_EN.pdf](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/PinBoard_UM_EN.pdf)
- Pin-board SCH and PCB project：
[https://lceda.cn/seanfan/wmmed_ext_openhd](https://lceda.cn/seanfan/wmmed_ext_openhd)
- FPC Connector[DF37NB-30DS-0.4V] 
[https://www.hirose.com/product/en/products/DF37/DF37NB-30DS-0.4V%2851%29/](https://www.hirose.com/product/en/products/DF37/DF37NB-30DS-0.4V%2851%29/)
- FPC wire SCH：
[https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/fpc_M001A_sch.pdf](https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/fpc_M001A_sch.pdf)

# Contact
If you have technical problems and ideas to communicate with us, you can
contact us by Email: fanfeiwu@gmail.com.  

For more information,please browse our homepage: [www.feelkit.com](http://www.feelkit.com).





