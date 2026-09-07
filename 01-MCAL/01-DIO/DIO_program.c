#include "../00-LIB/STD_TYPES.h"
#include "../00-LIB/BIT_MATH.h"
#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"

void DIO_voidSetPinValue(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8Value) {
    if( (Copy_u8PortId > DIO_u8_PORTD) || (Copy_u8PinId > DIO_u8_PIN7)) { }
    else {
        switch(Copy_u8PortId) {
            case DIO_u8_PORTA:  switch(Copy_u8Value) {
                                    case  DIO_u8_LOW:   CLR_BIT(DIO_u8_PORTA_REG,Copy_u8PinId);     break;
                                    case  DIO_u8_HIGH:  SET_BIT(DIO_u8_PORTA_REG,Copy_u8PinId);     break;
                                } break;
            case DIO_u8_PORTB:  switch(Copy_u8Value) {       
                                    case  DIO_u8_LOW:   CLR_BIT(DIO_u8_PORTB_REG,Copy_u8PinId);     break;
                                    case  DIO_u8_HIGH:  SET_BIT(DIO_u8_PORTB_REG,Copy_u8PinId);     break;
                                } break;
            case DIO_u8_PORTC:  switch(Copy_u8Value) {
                                    case  DIO_u8_LOW:   CLR_BIT(DIO_u8_PORTC_REG,Copy_u8PinId);     break;
                                    case  DIO_u8_HIGH:  SET_BIT(DIO_u8_PORTC_REG,Copy_u8PinId);     break;
                                } break;
            case DIO_u8_PORTD:  switch(Copy_u8Value) {
                                    case  DIO_u8_LOW:   CLR_BIT(DIO_u8_PORTD_REG,Copy_u8PinId);     break;
                                    case  DIO_u8_HIGH:  SET_BIT(DIO_u8_PORTD_REG,Copy_u8PinId);     break;
                                } break;
        }
    }
}

void DIO_voidSetPinDirection(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8Direction) {
    if( (Copy_u8PortId > DIO_u8_PORTD) || (Copy_u8PinId > DIO_u8_PIN7)) { }
    else {
        switch(Copy_u8PortId) {
            case DIO_u8_PORTA:  switch(Copy_u8Direction) {
                                    case  DIO_u8_INPUT:   CLR_BIT(DIO_u8_DDRA_REG,Copy_u8PinId);     break;
                                    case  DIO_u8_OUTPUT:  SET_BIT(DIO_u8_DDRA_REG,Copy_u8PinId);     break;
                                } break;
            case DIO_u8_PORTB:  switch(Copy_u8Direction) {       
                                    case  DIO_u8_INPUT:   CLR_BIT(DIO_u8_DDRB_REG,Copy_u8PinId);     break;
                                    case  DIO_u8_OUTPUT:  SET_BIT(DIO_u8_DDRB_REG,Copy_u8PinId);     break;
                                } break;
            case DIO_u8_PORTC:  switch(Copy_u8Direction) {
                                    case  DIO_u8_INPUT:   CLR_BIT(DIO_u8_DDRC_REG,Copy_u8PinId);     break;
                                    case  DIO_u8_OUTPUT:  SET_BIT(DIO_u8_DDRC_REG,Copy_u8PinId);     break;
                                } break;
            case DIO_u8_PORTD:  switch(Copy_u8Direction) {
                                    case  DIO_u8_INPUT:   CLR_BIT(DIO_u8_DDRD_REG,Copy_u8PinId);     break;
                                    case  DIO_u8_OUTPUT:  SET_BIT(DIO_u8_DDRD_REG,Copy_u8PinId);     break;
                                } break;
        }
    }
}

u8 DIO_voidGetPinValue(u8 Copy_u8PortId, u8 Copy_u8PinId) {
    u8 Local_u8PinValue = 5;
    if( (Copy_u8PortId > DIO_u8_PORTD) || (Copy_u8PinId > DIO_u8_PIN7)) { }
    else {
        switch(Copy_u8PortId) {
            case DIO_u8_PORTA:  Local_u8PinValue = GET_BIT(DIO_u8_PINA_REG,Copy_u8PinId);  break;
            case DIO_u8_PORTB:  Local_u8PinValue = GET_BIT(DIO_u8_PINB_REG,Copy_u8PinId);  break;
            case DIO_u8_PORTC:  Local_u8PinValue = GET_BIT(DIO_u8_PINC_REG,Copy_u8PinId);  break;
            case DIO_u8_PORTD:  Local_u8PinValue = GET_BIT(DIO_u8_PIND_REG,Copy_u8PinId);  break;
        }
    }
    return Local_u8PinValue;
}

void DIO_voidSetPortValue(u8 Copy_u8PortId, u8 Copy_u8Value) {
    if( (Copy_u8PortId > DIO_u8_PORTD)) { }
    else {
        switch(Copy_u8PortId) {
            case DIO_u8_PORTA:  DIO_u8_PORTA_REG = Copy_u8Value;  break;
            case DIO_u8_PORTB:  DIO_u8_PORTB_REG = Copy_u8Value;  break;
            case DIO_u8_PORTC:  DIO_u8_PORTC_REG = Copy_u8Value;  break;
            case DIO_u8_PORTD:  DIO_u8_PORTD_REG = Copy_u8Value;  break;
        }
    }
}

void DIO_voidSetPortDirection(u8 Copy_u8PortId, u8 Copy_u8Direction) {
    if( (Copy_u8PortId > DIO_u8_PORTD)) { }
    else {
        switch(Copy_u8PortId) {
            case DIO_u8_PORTA:  DIO_u8_DDRA_REG = Copy_u8Direction;  break;
            case DIO_u8_PORTB:  DIO_u8_DDRB_REG = Copy_u8Direction;  break;
            case DIO_u8_PORTC:  DIO_u8_DDRC_REG = Copy_u8Direction;  break;
            case DIO_u8_PORTD:  DIO_u8_DDRD_REG = Copy_u8Direction;  break;
        }
    }
}

u8 DIO_voidGetPortValue(u8 Copy_u8PortId) {
    u8 Local_u8PortValue = 0;
    if( (Copy_u8PortId > DIO_u8_PORTD)) { }
    else {
        switch(Copy_u8PortId) {
            case DIO_u8_PORTA:  Local_u8PortValue = DIO_u8_PINA_REG;  break;
            case DIO_u8_PORTB:  Local_u8PortValue = DIO_u8_PINB_REG;  break;
            case DIO_u8_PORTC:  Local_u8PortValue = DIO_u8_PINC_REG;  break;
            case DIO_u8_PORTD:  Local_u8PortValue = DIO_u8_PIND_REG;  break;
        }
    }
    return Local_u8PortValue;
}

void DIO_voidTogglePin(u8 Copy_u8PortId, u8 Copy_u8PinId) {
    if( (Copy_u8PortId > DIO_u8_PORTD) || (Copy_u8PinId > DIO_u8_PIN7)) { }
    else {
        switch(Copy_u8PortId) {
            case DIO_u8_PORTA:  TOG_BIT(DIO_u8_PORTA_REG,Copy_u8PinId);  break;
            case DIO_u8_PORTB:  TOG_BIT(DIO_u8_PORTB_REG,Copy_u8PinId);  break;
            case DIO_u8_PORTC:  TOG_BIT(DIO_u8_PORTC_REG,Copy_u8PinId);  break;
            case DIO_u8_PORTD:  TOG_BIT(DIO_u8_PORTD_REG,Copy_u8PinId);  break;
        }
    }
}
void DIO_voidTogglePort(u8 Copy_u8PortId) {
    if( (Copy_u8PortId > DIO_u8_PORTD)) { }
    else {
        switch(Copy_u8PortId) {
            case DIO_u8_PORTA:  DIO_u8_PORTA_REG ^= 0xFF;  break;
            case DIO_u8_PORTB:  DIO_u8_PORTB_REG ^= 0xFF;  break;
            case DIO_u8_PORTC:  DIO_u8_PORTC_REG ^= 0xFF;  break;
            case DIO_u8_PORTD:  DIO_u8_PORTD_REG ^= 0xFF;  break;
        }
    }
}
