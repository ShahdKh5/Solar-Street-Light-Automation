#include "../../01-MCAL/00-LIB/STD_TYPES.h"
#include "../../01-MCAL/01-DIO/DIO_interface.h"
#include "../../01-MCAL/02-ADC/ADC_interface.h"
#include "LDR_interface.h"

void LDR_voidInit(void) {
    /* TODO: 
       1. Set the direction of the ADC channel pin connected to LDR as INPUT.
    */
}

u8 LDR_u8IsNight(void) {
    /* TODO: 
       1. Read ADC value for the LDR channel using ADC_u16ReadSynchronus.
       2. Compare the result with a threshold (e.g., if reading > 512, it's night).
       3. Return 1 if night, 0 if day.
    */
    return 0;
}
