#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <util/delay.h>
#include "../00-LIB/STD_TYPES.h"
#include "../00-LIB/BIT_MATH.h"
#include "../01-DIO/DIO_interface.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

u8 ADC_u8BusyFlag = NOTBUSY;
u16 ADC_u16Result;
void (*ADC_pvNotificationFunction)(void) = NULL;

void ADC_voidInit(void)
{
	DIO_voidSetPortDirection(DIO_u8_PORTA,DIO_u8_INPUT);

	#if		ADC_REFVOLT == ADC_AREF
		CLR_BIT(ADC_u8_ADMUX_REG, ADC_u8_ADMUX_REFS0);
		CLR_BIT(ADC_u8_ADMUX_REG, ADC_u8_ADMUX_REFS1);
	#elif   ADC_REFVOLT == ADC_AVCC
		SET_BIT(ADC_u8_ADMUX_REG, ADC_u8_ADMUX_REFS0);
		CLR_BIT(ADC_u8_ADMUX_REG, ADC_u8_ADMUX_REFS1);
	#elif   ADC_REFVOLT == ADC_INTERNAL
		SET_BIT(ADC_u8_ADMUX_REG, ADC_u8_ADMUX_REFS0);
		SET_BIT(ADC_u8_ADMUX_REG, ADC_u8_ADMUX_REFS1);
	#endif
	
	#if	ADC_ADJUST_CTRL == LEFT
		SET_BIT(ADC_u8_ADMUX_REG, ADC_u8_ADMUX_ADLAR);
	#elif ADC_ADJUST_CTRL == RIGHT
		CLR_BIT(ADC_u8_ADMUX_REG, ADC_u8_ADMUX_ADLAR);
	#endif
	
	ADC_u8_ADCSRA_REG &= ADC_PRES_MASK;
	ADC_u8_ADCSRA_REG |= ADC_PRESCALAR_VAL;
	SET_BIT(ADC_u8_ADCSRA_REG, ADC_u8_ADCSRA_ADEN);
}

u16 ADC_u16ReadSynchronus(u8 Copy_u8ChannelNum)
{
	if(ADC_u8BusyFlag == BUSY) return BUSY;
	else
	{
		ADC_u8BusyFlag = BUSY;
		ADC_u8_ADMUX_REG &= ADC_CHANNEL_MASK;			
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNum;

		SET_BIT(ADC_u8_ADCSRA_REG, ADC_u8_ADCSRA_ADSC);
		while(GET_BIT(ADC_u8_ADCSRA_REG, ADC_u8_ADCSRA_ADIF) == 0);
		SET_BIT(ADC_u8_ADCSRA_REG, ADC_u8_ADCSRA_ADIF);
		_delay_us(10);

		ADC_u8BusyFlag = NOTBUSY;
		return ADC_u16_ADC_REG;
	}
}

u16 ADC_u16ReadAsynchronus(u8 Copy_u8ChannelNum, void (*Copy_pvCallBackFunctionPtr)(void))
{
	if( (ADC_u8BusyFlag == BUSY) || (Copy_pvCallBackFunctionPtr == NULL) ) return 0;
	else
	{
		ADC_u8BusyFlag = BUSY;
		ADC_u8_ADMUX_REG &= ADC_CHANNEL_MASK;			
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNum;

		ADC_pvNotificationFunction = Copy_pvCallBackFunctionPtr;
		SET_BIT(ADC_u8_ADCSRA_REG, ADC_u8_ADCSRA_ADSC);
		SET_BIT(ADC_u8_ADCSRA_REG, ADC_u8_ADCSRA_ADIE);

		return ADC_u16Result;
	}
}

void __vector_16 (void)   __attribute__((signal));
void __vector_16 (void)
{
	ADC_u16Result = ADC_u16_ADC_REG;
	ADC_u8BusyFlag = NOTBUSY;
	if (ADC_pvNotificationFunction != NULL) ADC_pvNotificationFunction();
	CLR_BIT(ADC_u8_ADCSRA_REG, ADC_u8_ADCSRA_ADIE);
}
