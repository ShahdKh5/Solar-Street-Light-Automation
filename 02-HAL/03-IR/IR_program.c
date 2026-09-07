#include "../../01-MCAL/00-LIB/STD_TYPES.h"
#include "../../01-MCAL/01-DIO/DIO_interface.h"
#include "IR_interface.h"

void IR_voidInit(void) {
    /* TODO: 
       1. Configure the GPIO pins connected to IR Zone A and IR Zone B as INPUT.
       (e.g., PD2 and PD3 according to the PDF)
    */
}

u8 IR_u8ZoneA_Read(void) {
    /* TODO: 
       1. Read the pin state for Zone A.
       2. Return the state (1 if motion detected, 0 otherwise).
    */
    return 0;
}

u8 IR_u8ZoneB_Read(void) {
    /* TODO: 
       1. Read the pin state for Zone B.
       2. Return the state.
    */
    return 0;
}
