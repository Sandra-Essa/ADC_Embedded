#include "stm32f4xx.h"
#include "ADC.h"
#include "gpio.h"


// First Function: configuration
void ADC_Init(ADCConfigType* ConfigParamPtr)
{
	//enable ADC1 Clock
	RCC->APB2ENR|=(1u<<8);

	// Enable the ADC
	ADC1->CR2 |=(1u<<0);

	//Alternative input
	GPIOA->MODER |=(1u<<10);
    GPIOA->MODER |=(1u<<11);




/*********************************************************
	//configuration resolution from struct:
	/*Bits 25:24-> RES[1:0]
	 * 00: 12-bit
       01: 10-bit
       10: 8-bit
       11: 6-bit
**************************************************************/

	  // 00: 12-bit
		if(ConfigParamPtr->resolution==bit_12){
			ADC1->CR1&=~(1<<24);
			ADC1->CR1&=~(1<<25);
		}

		//01: 10-bit
		else if(ConfigParamPtr->resolution==bit_10){
				ADC1->CR1|=(1<<24);
				ADC1->CR1&=~(1<<25);
			}
		//10: 8-bit
		else if(ConfigParamPtr->resolution==bit_8){
				ADC1->CR1&=~(1<<24);
				ADC1->CR1|=(1<<25);
			}
		//11: 6-bit
		else if(ConfigParamPtr->resolution==bit_6){
				ADC1->CR1|=(1<<24);
				ADC1->CR1|=(1<<25);
			}

/*******************************************************************************

		/* Secound Check Conversion mode:
		 * CONT: Continuous conversion
		 * 0: Single conversion mode        1: Continuous conversion mode
**************************************************************************** */


		//1: Continuous conversion mode
		if(ConfigParamPtr->ConversionMode==continues){
			ADC1->CR2|=(1u<<1);
		}

		 //0: Single conversion mode
		else if(ConfigParamPtr->ConversionMode==single){
			ADC1->CR2&=~(1u<<1);
		}




/*********************************************************************
		/*Bit 5 EOCIE: Interrupt enable for EOC
		 * 0: EOC interrupt disabled
		    1: EOC interrupt enabled.
		 * An interrupt is generated when the EOC bit is set

**********************************************************************/

	//Enable interrupt if USE_POLLING=0
		//enable macro
	#if (USE_POLLING==0)
		{
// 1: EOC interrupt enabled.
		ADC1->CR1|=(1u<<5);

		NVIC->ISER[0]|=(1u<<18);}
	#endif

}


void ADC_StartConv(unsigned char ChannelNum){

 ADC1->SQR3 = ChannelNum;

/*******************************************************************
 * Bits 23:20 L[3:0]: Regular channel sequence length
 * 0000: 1 conversion
 *
 * *********************************************************/

	ADC1->SQR1&=~(1u<<20);
	ADC1->SQR1&=~(1u<<21);
	ADC1->SQR1&=~(1u<<22);
	ADC1->SQR1&=~(1u<<23);

/********************************************************************
	 * Bit 30 SWSTART: Start conversion of regular channels
	 * 0: Reset state
     1: Starts conversion of regular channels
 * ************************************************************/


// start conversion
	ADC1->CR2 |=(1u<<30);



}

void ADC_GetConversionState(unsigned char* ConversionStatePtr){
//Check macro
	#if (USE_POLLING==1)

	/*****************************************************************************
	 * Bit 1 EOC: Regular channel end of conversion
		 * 0: Conversion not complete (EOCS=0), or sequence of conversions not complete (EOCS=1)
	       1: Conversion complete (EOCS=0), or sequence of conversions complete (EOCS=1)

************************************************************************************/
if(ADC1->SR&(1u<<1))
// if conversion is done (1)
			*ConversionStatePtr = 1;
else
			//  is not (0)
			*ConversionStatePtr = 0;
	#endif
}

unsigned char ADC_ReadData(unsigned short int* DataPtr){
	/*****************************************************************
	     * Bit 1 EOC: Regular channel end of conversion
			 * 0: Conversion not complete (EOCS=0), or sequence of conversions not complete (EOCS=1)
		       1: Conversion complete (EOCS=0), or sequence of conversions complete (EOCS=1)
 *************************************************************** */


	if(ADC1->SR&(1u<<1)){
		//there is a valid ADC value and the DataPtr is Dereferenced When 0
		//DR Read Only
			*DataPtr = ADC1->DR;
			return 0;
		} else {
			// return 1 when there is no valid ADC value and the DataPtr is not dereferenced.
			return 1;
		}
	}

