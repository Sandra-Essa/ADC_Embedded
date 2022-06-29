#include "stm32f4xx.h"
#include "ADC.h"
#include "gpio.h"
#include "interrupt.h"
#include "LCD.h"

// macros defines
#define MAX_VOLT 5
#define MAX_TEMPERATURE 4095

//Global variable
unsigned short int Data;
unsigned short int temperature; //700 ,100


int main(void)
{

	//Adc configure parameters
	//ADCConfigType test={bit_12,continues,5};    // for polling=0
	ADCConfigType test={bit_12,single,5};      // for polling=1

	unsigned short int digital_data;
	unsigned short int *dataptr;
	dataptr=&digital_data;
	unsigned char state;

	//initialize LCD
	LCD_Init();

	//initialize ADC with our parameters
	ADC_Init(&test);

	//Start conversion on channel 5
	ADC_StartConv(5);


	while( 1){


	#if(USE_POLLING==1)
			ADC_GetConversionState(&state);
			//if conversion not complete

			if(state == 1){
				LCD_ClearScreen();
				ADC_ReadData(dataptr);
				temperature = (int)((digital_data/(1.5*MAX_TEMPERATURE))*MAX_VOLT*150);
				LCD_DisplayString("Temp:");
				LCD_IntToStr(temperature);
				for(int i=0; i<500000; i++){}
				LCD_ClearScreen();
}
   #endif
         //case single
		 //parameters = single
			if(test.ConversionMode==single){     // for single mode, start conversion again
				ADC_StartConv(5);
			}
		}



		}

void ISR_OF_ADC(void){

	if(ADC1->SR&(1u<<1)){
		Data=ADC1->DR;
		}
	LCD_ClearScreen();
	//using interrupt in this case
	temperature = (int)((Data/(1.5*MAX_TEMPERATURE))*MAX_VOLT*150);
	LCD_DisplayString("Temp:");
	LCD_IntToStr(temperature);
	for(int i=0; i<500000; i++){}
	//parameters = single
	ADC_StartConv(5);
}

void ADC_IRQHandler(void){
	ISR_OF_ADC();
}
