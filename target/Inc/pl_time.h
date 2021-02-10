#ifndef __PL_TIME_H
#define __PL_TIME_H



#include "stm32f1xx_hal.h"


// -------------------- HAL Functions --------------------
void pl_time_init(void);
uint32_t pl_time_getMs(void);
void pl_time_waitMs(uint32_t uiDuration); //< approximate wait (for debug only)



#endif /* __PL_TIME_H */
