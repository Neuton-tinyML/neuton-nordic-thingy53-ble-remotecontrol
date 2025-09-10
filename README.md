# Neuton.AI Nordic Thingy:53 Gesture Based BLE Remote Control Device

- [Overview](#overview)
- [Hardware Used](#hw-used)
- [Setup Software Environment](#setup-sw-env)
- [Setup Firmware Project](#setup-fw-proj)
- [Python Demo Setup](#python-demo)
- [How The Project Works](#how-works)

## Overview <div id='overview'/>

This project demonstrates a gesture based remote control device using [__Nordic Thingy:53__](https://www.nordicsemi.com/Products/Development-hardware/Nordic-Thingy-53). The development kit could be connected to the PC via Bluetooth as a HID device and using gestures the user can control media stream or slides of the presentation. Based on accelerometer and gyroscope data the Neuton.AI model could recognize __8 classes__ of gestures: Swipe Right, Swipe Left, Double Shake, Double Tap, Rotation Clockwise and Counter clockwise, No Gestures(IDLE) and Unknown Gesture. Use-case demonstration [video](https://youtu.be/kVSK7JG2L_s). Raw dataset used for model training, which you can use to train your own model, or augment it with your own data and train a more robust model is located [here](https://drive.google.com/file/d/1mbECXMTTk7QbLah3stydOKv4n8uoSr8G/view?usp=sharing).

[Here](https://docs.google.com/document/d/1UMOTXBaaYdG9_hd3CwTOa2hkph7cb4i2/edit#heading=h.vobk9ee6qydz) you can find a manual on how to create similar solutions on the Neuton platform from scratch.

## Hardware Used <div id='hw-used'/>

[__Nordic Thingy:53 Multi-protocol IoT prototyping platform__](https://www.nordicsemi.com/Products/Development-hardware/Nordic-Thingy-53)

The Nordic Thingy:53™ is an easy-to-use IoT prototyping platform. It makes it possible to create prototypes and proofs-of-concept without building custom hardware. The Thingy:53 is built around the nRF5340 SoC, the flagship dual-core wireless SoC. The processing power and memory size of its dual Arm Cortex-M33 processors enables it to run embedded machine learning (ML) models directly on the device.

The Thingy:53 also includes many different integrated sensors, like environmental-, and color and light sensors, accelerometers, and a magnetometer, which all can be taken advantage of without additional hardware. It is powered by a rechargeable Li-Po battery that can be charged via USB-C. There is also an external 4-pin JST connector compatible with the Stemma/Qwiic/Grove standards for hardware accessories.

![nordic-thingy-kit-img](resources/nordic_thingy.jpg)

## Setup Software Environment <div id='setup-sw-env'/>

To set this project up, you will need to install the following software:
- Visual Studio Code (https://code.visualstudio.com)
- nRF Connect for VS Code (https://www.nordicsemi.com/Products/Development-tools/nRF-Connect-for-VS-Code)
- [**Optional**] TeraTerm Terminal (https://teratermproject.github.io/index-en.html)

## Setup Firmware Project <div id='setup-fw-proj'/>

1. Clone this repository: https://github.com/Neuton-tinyML/neuton-nordic-thingy53-ble-remotecontrol
2. In the VS code, `Open folder` where you did clone the repository.
3. `Manage toolchain` install toolchain version **v3.0.0**. `Manage SDK` install version **v2.6.2** in nRF Connect tab.

![sw-install-step3-img](resources/sw-install-step-3.jpg)

4. `Add Build configuration` for Nordic Thingy 53 dev kit

![sw-install-step4-img](resources/sw-install-step-4.jpg)

5. Choose `thingy53_nrf5340_cpuapp` in the `Board` selector and click `Build Configuration`

![sw-install-step5-img](resources/sw-install-step-5.jpg)

6. After your build will be configured you should see the following options:

![sw-install-step6-img](resources/sw-install-step-6.jpg)

**IMPORTANT** If your `thingy53_nrf5340_cpuapp_defconfig` file does not has **`CONFIG_FPU=y`** you should add this because Neuton library is compiled with `-mfloat-abi=hard` flag

![sw-install-step5-1-img](resources/sw-install-step-5-1-important.jpg)

8. Now turn on your Thingy 53 dev kit and connect to your PC via debugger and USB

![sw-install-step7-img](resources/connected-devkit-sw-install-step-7.jpg)

9. Build & Flash the device with firmware

![sw-install-step8-img](resources/sw-install-step-8.jpg)

# Python Demo Setup <div id='python-demo'/>

To install and run the UI demo you should have installed:

+ Python 3 and add python3 to your system PATH
+ Pip3 (Python should install it automatically, you can check it with `pip3 --version`)

After installing python3 you can execute `install_demo_win.bat` or run `pip3 install -r requirements.txt`, this script will install all necessary python dependencies for demo application.

To run the UI demo application:
- on Windows you can run `run_demo_win.bat` 
- on Linux/MacOS use the following [manual](demo/README.md)



# How the project works <div id='how-works'/>

Once the application script is running, after approximately 10 seconds you will see **Ready to work** in the console output and the UI application will be running in a dedicated screen.

After Bluetooth connection the device will change LED indication from RED LED glowing to GREEN LED glowing. 


| No Bluetooth connection |  Bluetooth connection established |
| ------------------------ |---------------------------- |
| ![Alt Text](resources/device-led-no-ble-connect.gif) |![Alt Text](resources/device-led-ble-connect.gif) |

After the device is connected a UI Demo window will open
![demo_screen_1](resources/demo_1.png)

Next, follow the guidelines on how to make gestures bellow. For better recognition use your wrists more when making gestures, and not your whole hand.

__How to Make Gestures__
> **_NOTE:_**  The dataset for creating this model is immature and this affects the generalization of the model on different persons, so please follow the instructions for good gesture recognition.

To begin with, please make sure that the default (initial) position of the device is the same as following:

![gestures-img-1](resources/initial_orientation.gif)


__Swipe Right & Left__
|                                        |                                               |
| -------------------------------------- | --------------------------------------------- |
| ![Alt Text](resources/swipe_right.gif) | ![Alt Text](resources/swipe_left.gif)        |
| Swipe Right                            |    Swipe Left                                |

__Rotation Clockwise & Counter Clockwise__

|                                           |                                               |
| --------------------------------------    | --------------------------------------------- |
| ![Alt Text](resources/rotation_right.gif) | ![Alt Text](resources/rotation_left.gif)      |
| Rotation Clockwise(Right)                 |    Rotation Counter Clockwise(Left)            |

__Double Shake & Double Tap__

|                                           |                                               |
| --------------------------------------    | --------------------------------------------- |
| ![Alt Text](resources/double_shake.gif)   | ![Alt Text](resources/double_tap.gif)      |
| Double Shake                              |    Double Tap                              |

When performing gestures with the device, in the serial port terminal, you should see the similar messages:

```
Ready to work
2,96
SWIPE RIGHT, probability 96 %
3,81
SWIPE LEFT, probability 81 %
2,97
SWIPE RIGHT, probability 97 %
7,86
ROTATION LEFT, probability 86 %
3,99
SWIPE LEFT, probability 99 %
```

The UI demo app will duplicate this with a graphical representation of recongized gestures:

![gui-example-1](resources/gui_example.gif)


Have fun and use this model for your future gesture control projects!

