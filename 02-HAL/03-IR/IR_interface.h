#ifndef IR_INTERFACE_H
#define IR_INTERFACE_H
#include "../../01-MCAL/00-LIB/STD_TYPES.h"

/* Initialize the pins for Zone A and Zone B IR sensors */
void IR_voidInit(void);

/* Read Zone A IR sensor. Return 1 if motion detected. */
u8 IR_u8ZoneA_Read(void);

/* Read Zone B IR sensor. Return 1 if motion detected. */
u8 IR_u8ZoneB_Read(void);

#endif
