# ADC_Embedded
---
### Table of Contents:-

- [Features](#Features)
- [Demos](#Demos)
- [Tools](#Tools)
---

## Features
The Driver has the following services:

1- void ADC_Init(ADCConfigType* ConfigParamPtr)

Where ADCConfigType is a struct that c+ontains all the configuration parameters needed to
initialize the STM ADC.

The configuration parameters are listed below:

1- Resolution (enum type)
2- Conversion mode (single or continues) - (enum type).
3- Reference voltage

The following configuration macro shall be checked to enable or disable ADC Interrupt (USE_POLLING == 1)

---
2- void ADC_StartConv(unsigned char ChannelNum):

The function is used to start a software conversion in the single conversion mode or start the
first conversion in the continuous mode.

---
3- void ADC_GetConversionState(unsigned char* ConversionStatePtr):

The function shall be enabled only when the configuration macro USE_POLLING is set to 1 and is used by the client to check if conversion is done (1) or not (0).

----
4- unsigned char ADC_ReadData(unsigned short int* DataPtr):

The function shall be used by the client to read the ADC value. The function shall return 0 when there is a valid ADC value and the DataPtr is Dereferenced.. The function shall return 1 when there is no valid ADC value and the DataPtr is not dereferenced.

----
5- An ISR shall be implemented to notify that a conversion is completed. The implementation will be enabled only when the configuration macro USE_POLLING is set to 0.

---
The ADC driver, it uses to interface an LM35 temperature sensor.
The sensor temperature continuously monitored and displayed on LM016 character LCD.
---

### Demos
---
![](https://github.com/Sandra-Essa/ADC_Embedded/blob/main/GIF/ADC_driver_GIF.gif)
---
### Tools
----
- System Workbench - Code C Language 
- Proteus version 8.11 - Simulation
----
