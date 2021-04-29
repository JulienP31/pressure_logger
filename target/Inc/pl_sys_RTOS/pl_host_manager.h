#ifndef __PL_HOST_MANAGER_H
#define __PL_HOST_MANAGER_H



#include "stm32f1xx_hal.h"
#include "pl_app_infos.h"
#include "pl_usart.h"
#include "pl_sensor.h"


// -------------------- Typedefs --------------------
typedef enum pl_host_manager_state
{
	PL_HOST_MANAGER_INIT,
	PL_HOST_MANAGER_WAIT_CMD,
	PL_HOST_MANAGER_UPDATE_FREQ
} pl_host_manager_state_t;


// -------------------- HAL Functions --------------------
void pl_host_task(void *pvParameters);



#endif /* __PL_HOST_MANAGER_H */
