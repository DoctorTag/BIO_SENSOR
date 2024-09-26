# Projet Bio-sensor (https://github.com/feelkit/BIO_SENSOR/blob/master/Readme_cn.md)
## Un projet Bio-sensor terminé comprenant des solutions logicielles et matérielles; également en fonction des projets suivants:
Projet de micrologiciel Bluetooth BLE: [https://github.com/feelkit/bioModule_NRF52_BLE </font>(https://github.com/feelkit/bioModule_NRF52_BLE)

Outil d'évaluation utilisant LabWindows CVI:
[https://github.com/feelkit/bioDemo_labwindows_cviITED(https://github.com/feelkit/bioDemo_labwindows_cvi)

Projet HDF (Healthcare Development Framework): [https://github.com/feelkit/HDF[/https://github.com/feelkit/HDF)

# Présenter
Le projet comprend un module de soins de santé Bio-Sensor （[BIO-Sensor: F58GM] (https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_SPEC_EN.pdf)）, des projets de santé conçus pour le Bio-capteur et solutions logicielles, y compris le micrologiciel Bluetooth BLE et WIFI et les outils d'évaluation de bureau / mobiles.

Le Bio-Sensor mesure et transfère divers types de données biologiques, notamment ECG, RESP, GSR, HR, PPG, HCM et BIA, etc., Bio-Processor intégré avec frontal analogique pour créer une solution de surveillance de la santé tout-en-un. Le noyau de l'algorithme fonctionne dans Bio-Processor, y compris SPO2, la reconnaissance de mouvement, la surveillance dynamique de la fréquence cardiaque, l'analyse des tendances de la pression artérielle, le stress émotionnel et mental, etc.
 
La carte d'évaluation prend en charge Bluetooth BLE avec le chipset NRF52832 de NordicSemi.

La solution logicielle comprend le micrologiciel Bluetooth pour NRF52, un outil d'évaluation de bureau sur LabWindows CVI; Nous développons également l'APK pour ANDROID, qui sera publié et open-source.

# [Bio-Sensor: F58GM] (https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_UM_EN.pdf)
! [image] (https://github.com/feelkit/BIO_SENSOR/raw/master/image/F58GM.png)
Le Bio-module intègre des LED tricolores rouges (660 nm), vertes (520 nm) et infrarouges (940 nm) et un capteur à photodiode (PD) pour réaliser des applications liées au PPG; et prend en charge quatre électrodes pour réaliser des applications avec des activités électriques humaines et des activités d'impédance; Capteur G à trois axes sur module 14 bits pour les applications de mouvement / veille.

L'interface matérielle du Bio-module prend en charge SPI / I2C / UART en option, référence de connecteur FPC [DF37NB-30DS-0.4V] (https://www.hirose.com/product/en/products/DF37/DF37NB-30DS-0.4V % 2851% 29 /).

## CARACTÉRISTIQUES DU BIO-Sensor
### ECG à une seule dérivation:
- 3 électrodes avec pilote de jambe droite;
- Détection de plomb;
### Bio-impédance avec 4 électrodes:
- DAC intégré et générateur de forme d'onde multifréquence;
- Soutenir le REEE, le BIA et le GSR, etc.
### PPG:
- LED et PD rouge (660 nm), verte (520 nm) et infrarouge (940 nm) sur le module;
- Soutenir les RH, SPO2 et Bio-test, etc.
### Les électrodes signifient l'interface:
- Soutenir les électrodes comme clavier d'entrée;
- Prend en charge la paire d'électrodes comme canal de données: par exemple, USB / UART, etc.
- Soutenir la paire d'électrodes comme canal de chargeur d'alimentation;

### Gsensor:
- Capteur G à 3 axes 14 bits intégré, plage + 2G, + 4G, + 8g, + 16g;
- Podomètre, reconnaissance d'action;

### Interface matérielle:
- SPI / UART / I2C en option;
- Connecteur FPC [DF37NB-30DS-0.4V] (https://www.hirose.com/product/en/products/DF37/DF37NB-30DS-0.4V%2851%29/), de hirose;

### Petite taille, convient aux appareils de bracelets:
- 22x26 mm;

## APPLICATIONS BIO-M001A

1. Fitness, dispositifs de bracelet;
2. Appareils de santé;
3. Appareils mobiles et robots, etc.

# Kits de développement pour Bio-M001A
! [image] (https://github.com/feelkit/BIO_SENSOR/raw/master/image/DEMO1.png)
Le matériel d'évaluation comprend la carte mère Bluetooth, le tableau d'affichage; le logiciel comprend le micrologiciel Bluetooth BLE, l'application PC / mobile. Pour utiliser la carte d'évaluation, veuillez vous reporter au [manuel de l'utilisateur] (https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/demo_UM_EN.pdf).
## Carte mère Bluetooth
 La carte mère prend en charge Bluetooth BLE avec le chipset NRF52832 de NordicSemi, en utilisant SPI / I2C / UART en option connectant le Bio-M001A; il communique avec APP via Bluetooth BLE. L'outil PC le connecte par Uart. Pour plus de détails, veuillez consulter
[manuel de l'utilisateur] (https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/MAIN_UM_EN.pdf)。

## Tableau d'affichage
Le tableau d'affichage est utilisé pour transformer l'interface FPC de Bio-M001A en une interface matérielle open-source commune (xRDUINO UNO), pour prendre en charge plus de cartes mères d'autres fournisseurs.Pour plus de détails, veuillez vous référer au [manuel de l'utilisateur] (https: / /github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/PinBoard_UM_EN.pdf)。
## Micrologiciel Bluetooth
Pour les détails, veuillez vous référer au projet ： [https://github.com/feelkit/bioModule_NRF52_BLE] (https://github.com/feelkit/bioModule_NRF52_BLE)

## Outil d'évaluation
Pour plus de détails, veuillez vous référer au projet ： [https://github.com/feelkit/bioDemo_labwindows_cvi] (https://github.com/feelkit/bioDemo_labwindows_cvi)
# RESSOURCES

1. BIO-M001A
- Bio-capteur - Spécifications M001A ： [https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_SPEC_EN.pdf] (https://github.com/feelkit/BIO_SENSOR/raw/master /DOC/M001A/M001A_SPEC_EN.pdf)
- Bio-sensor - Manuel de l'utilisateur M001A ：
»
- Bio-capteur - Fichiers CAO M001A (échelle: 1: 1, type de fichier dxf) ：
[Disposition du haut du module] (https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/M001A_TOP.dxf), [Disposition du bas du module] (https://github.com/feelkit/BIO_SENSOR/raw /master/DOC/M001A/M001A_BOT.dxf).

2. Carte mère Bluetooth BLE
- Manuel de l'utilisateur de la carte mère ： [https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A/MAIN_UM_EN.pdf] (https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/M001A /MAIN_UM_EN.pdf)
- Projet BLE carte mère SCH et PCB ：
[https://lceda.cn/seanfan/med_main_nrf[ ](https://lceda.cn/seanfan/med_main_nrf)
- Module Bluetooth BLE avec NRF52832 ： [http://www.freqchina.com/uploads/soft/201801/PTR9618_CN%20V1.4.pdf] (http://www.freqchina.com/uploads/soft/201801/PTR9618_CN % 20V1.4.pdf)
- Projet de micrologiciel Bluetooth ：
[https://github.com/feelkit/bioModule_NRF52_BLE Often (https://github.com/feelkit/bioModule_NRF52_BLE)
- Informations sur NRF52832 ： [https://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52832] (https://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52832 )

3. PinBoard-M001A
- Manuel de l'utilisateur PinBoard ：
[https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/PinBoard_UM_EN.pdf </font>(https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/PinBoard_UM_EN.pdf)
- Projet Pin-board SCH et PCB ：
[https://lceda.cn/seanfan/wmmed_ext_openhd </font>(https://lceda.cn/seanfan/wmmed_ext_openhd)
- Connecteur FPC [DF37NB-30DS-0.4V]
[https://www.hirose.com/product/en/products/DF37/DF37NB-30DS-0.4V%2851%29/[https://www.hirose.com/product/en/products/DF37/ DF37NB-30DS-0,4V% 2851% 29 /)
- Fil FPC SCH ：
[https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/fpc_M001A_sch.pdf </font>(https://github.com/feelkit/BIO_SENSOR/raw/master/DOC/fpc_M001A_sch.pdf)

# Contacter
Si vous avez des problèmes techniques et des idées pour communiquer avec nous, vous pouvez
contactez-nous par Email: fanfeiwu@gmail.com, QQ: 4646079

Pour plus d'informations, veuillez parcourir notre page d'accueil: [www.feelkit.com] (http://www.feelkit.com).