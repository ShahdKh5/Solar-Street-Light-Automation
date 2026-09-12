#ifndef F_CPU
#define F_CPU 8000000UL
#endif
//Main CPU clock freq= 8MHz (unsigned long)

#include <util/delay.h>
#include "../00-LIB/STD_TYPES.h"
#include "../00-LIB/BIT_MATH.h"
#include "../01-DIO/DIO_interface.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

u8 ADC_u8BusyFlag = NOTBUSY;
//Tracks whether the ADC is currently performing a conversion to prevent collision errors
u16 ADC_u16Result;
//Holds the converted 10-bit digital result globally for asynchronous calls
void (*ADC_pvNotificationFunction)(void) = NULL;
//A function pointer that points to a user function to execute when an asynchronous ADC conversion completes

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
	//Clears clock division bits using a bitwise mask
	ADC_u8_ADCSRA_REG |= ADC_PRESCALAR_VAL;
	////Sets the desired prescaler ratio (divides F_CPU down to optimal ADC clock speed)
	SET_BIT(ADC_u8_ADCSRA_REG, ADC_u8_ADCSRA_ADEN);
	//Enables the ADC hardware module (ADEN)
}

u16 ADC_u16ReadSynchronus(u8 Copy_u8ChannelNum) //Blocking
{
	if(ADC_u8BusyFlag == BUSY) return BUSY;
	else
	{
		ADC_u8BusyFlag = BUSY;
		ADC_u8_ADMUX_REG &= ADC_CHANNEL_MASK;			
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNum;

		SET_BIT(ADC_u8_ADCSRA_REG, ADC_u8_ADCSRA_ADSC);
		while(GET_BIT(ADC_u8_ADCSRA_REG, ADC_u8_ADCSRA_ADIF) == 0);
		//halts execution until the hardware sets the Interrupt Flag (ADIF), signaling conversion is done
		SET_BIT(ADC_u8_ADCSRA_REG, ADC_u8_ADCSRA_ADIF);
		_delay_us(10);
		//Clears ADIF flag by writing 1 to it and waits 10us for stabilization

		ADC_u8BusyFlag = NOTBUSY;
		return ADC_u16_ADC_REG;
		//returns digital value read from ADC register
	}
}

u16 ADC_u16ReadAsynchronus(u8 Copy_u8ChannelNum, void (*Copy_pvCallBackFunctionPtr)(void))
//Interrupt-Driven
{
	if( (ADC_u8BusyFlag == BUSY) || (Copy_pvCallBackFunctionPtr == NULL) ) return 0;
	else
	{
		ADC_u8BusyFlag = BUSY;
		ADC_u8_ADMUX_REG &= ADC_CHANNEL_MASK;			
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNum;

		ADC_pvNotificationFunction = Copy_pvCallBackFunctionPtr;
		//saves callback function address
		SET_BIT(ADC_u8_ADCSRA_REG, ADC_u8_ADCSRA_ADSC);
		SET_BIT(ADC_u8_ADCSRA_REG, ADC_u8_ADCSRA_ADIE);
		//Sets ADIE (ADC Interrupt Enable) to trigger ISR upon completion

		return ADC_u16Result;
	}
}

void __vector_16 (void)   __attribute__((signal)); //ISR
//The hardware automatically jumps to this function when ADC conversion completes
void __vector_16 (void)
{
	ADC_u16Result = ADC_u16_ADC_REG;
	//Reads hardware result register into global storage
	ADC_u8BusyFlag = NOTBUSY;
	if (ADC_pvNotificationFunction != NULL) ADC_pvNotificationFunction();
	CLR_BIT(ADC_u8_ADCSRA_REG, ADC_u8_ADCSRA_ADIE);
	//Disables ADC interrupt until next asynchronous call
}
