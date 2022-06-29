#ifndef INCLUDE_ADC_H_
#define INCLUDE_ADC_H_

#define USE_POLLING 1

typedef enum {bit_12, bit_10, bit_8, bit_6} Resolution;
typedef enum {single, continues} Conversion_Mode ;

typedef struct {
	Resolution resolution ;
	Conversion_Mode ConversionMode;
    float Reference_Volt;
}ADCConfigType ;


void ADC_Init(ADCConfigType* ConfigParamPtr);
void ADC_StartConv(unsigned char ChannelNum);
void ADC_GetConversionState(unsigned char* ConversionStatePtr);
unsigned char ADC_ReadData(unsigned short int* DataPtr);

#endif /* INCLUDE_ADC_H_ */
