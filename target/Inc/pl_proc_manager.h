#ifndef __PL_PROC_MANAGER_H
#define __PL_PROC_MANAGER_H



#include "stm32f1xx_hal.h"
#include "pl_led.h"
#include "pl_usart.h"
#include "pl_sensor.h"


// -------------------- Typedefs --------------------
typedef enum pl_proc_manager_state
{
	PL_PROC_MANAGER_INIT,
	PL_PROC_MANAGER_WAIT_DATA,
	PL_PROC_MANAGER_GET_DATA,
	PL_PROC_MANAGER_CHECK_FREQ,
	PL_PROC_MANAGER_APPLY_FREQ
} pl_proc_manager_state_t;


// -------------------- HAL Functions --------------------
void pl_proc_manager_init(void);
void pl_proc_manager_run(void);



#endif /* __PL_PROC_MANAGER_H */
