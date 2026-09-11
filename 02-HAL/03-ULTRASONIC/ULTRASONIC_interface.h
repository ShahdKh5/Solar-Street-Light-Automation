#ifndef ULTRASONIC_INTERFACE_H
#define ULTRASONIC_INTERFACE_H

#include "../../01-MCAL/00-LIB/STD_TYPES.h"

#define TRIGGER_PORT     DIO_u8_PORTD
#define ECHO_PORT        DIO_u8_PORTD

#define TRIGGER_PIN     DIO_u8_PIN3
#define ECHO_PIN        DIO_u8_PIN2

/* Initialize the Trigger and Echo pins for the Ultrasonic sensor */
void ULTRASONIC_voidInit(void);

/* Send a trigger pulse to the Ultrasonic sensor */
void ULTRASONIC_voidTrigger(void);

/* Measure the distance in centimeters using the Ultrasonic sensor */
u16 ULTRASONIC_u16GetDistance(void);

#endif
