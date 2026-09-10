#include "../../01-MCAL/00-LIB/STD_TYPES.h"
#include "../../01-MCAL/01-DIO/DIO_interface.h"
#include "ULTRASONIC_interface.h"
#include <delay/util.h>

void ULTRASONIC_voidInit(void) {
    /* TODO: 
       1. Configure Trigger pin as OUTPUT.
       2. Configure Echo pin as INPUT.
    */
    //Trigger -> PD3
    DIO_voidSetPinDirection(DIO_u8_PORTD, TRIGGER_PIN, DIO_u8_OUTPUT);
    //Echo -> PD2
    DIO_voidSetPinDirection(DIO_u8_PORTD, ECHO_PIN, DIO_u8_INPUT);
}

void ULTRASONIC_voidTrigger(void) {
    /* TODO: 
       1. Set Trigger pin HIGH.
       2. Delay for ~10 microseconds.
       3. Set Trigger pin LOW.
    */
    DIO_voidSetPinValue(DIO_u8_PORTD, TRIGGER_PIN, DIO_u8_HIGH);
    _delay_ms(0.01);
    DIO_voidSetPinValue(DIO_u8_PORTD, TRIGGER_PIN, DIO_u8_LOW);
}

u16 ULTRASONIC_u16GetDistance(void) {
    /* TODO: 
       1. Call ULTRASONIC_voidTrigger().
       2. Measure the Echo pulse width duration (using Timer/ICU or delay loop).
       3. Calculate distance: Distance (cm) = (Duration * 0.0343) / 2.
       4. Return the calculated distance in cm.
    */
    u32 Local_u32Duration = 0;
    u16 Local_u16Distance_cm = 0;

    //1. Send trigger pulse
    ULTRASONIC_voidTrigger();

    //2. Wait for ECHO pin to go HIGH
    while (DIO_u8GetPinValue(DIO_u8_PORTD, ECHO_PIN) == DIO_LOW);

    //3. Count microsecond delays while ECHO pin stays HIGH
    while (DIO_u8GetPinValue(DIO_u8_PORTD, ECHO_PIN) == DIO_HIGH) {
        Local_u32Duration++;
        _delay_us(1); //1us delay per iteration
    }

    //Local_u32Duration now holds the pulse duration in microseconds

    Local_u16Distance_cm= (u16)((Local_u32Duration * 0.0343) / 2);
    return Local_u16Distance_cm;
}