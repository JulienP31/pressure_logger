#ifndef __PL_PROC_MANAGER_H
#define __PL_PROC_MANAGER_H



#include "stm32f1xx_hal.h"
#include "pl_app_infos.h"
#include "pl_led.h"
#include "pl_usart.h"
#include "pl_sensor.h"


// -------------------- Typedefs --------------------
typedef enum pl_proc_manager_state
{
	PL_PROC_MANAGER_INIT,
	PL_PROC_MANAGER_CHECK_SENSOR,
	PL_PROC_MANAGER_GET_DATA,
	PL_PROC_MANAGER_SET_FREQ
} pl_proc_manager_state_t;


// -------------------- HAL Functions --------------------
void pl_proc_task(void *pvParameters);



#endif /* __PL_PROC_MANAGER_H */
