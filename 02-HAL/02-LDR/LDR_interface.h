#ifndef LDR_INTERFACE_H
#define LDR_INTERFACE_H
#include "../../01-MCAL/00-LIB/STD_TYPES.h"

/* Initialize LDR connection pin */
void LDR_voidInit(void);

/* Check if it's Day or Night based on LDR reading. 
   Return 0 for DAY, 1 for NIGHT. */
u8 LDR_u8IsNight(void);

#endif
