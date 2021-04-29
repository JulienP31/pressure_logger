#include "pl_host_manager.h"



// -------------------- Constants --------------------
#define HOST_MANAGER_TASK_PERIOD_MS 50


// -------------------- HAL Functions --------------------
void pl_host_task(void *pvParameters)
{
	pl_host_manager_state_t eHostManagerState = PL_HOST_MANAGER_INIT;
	pl_app_infos_t *prAppInfos = (pl_app_infos_t *)pvParameters;
	pl_msg_host_proc_t rMsgHostProc = {0};
	
	TickType_t xLastWakeTime = xTaskGetTickCount();
	
	while (1)
	{
		switch (eHostManagerState)
		{
			case PL_HOST_MANAGER_INIT :
				eHostManagerState = PL_HOST_MANAGER_WAIT_CMD;
				break;
				
			case PL_HOST_MANAGER_WAIT_CMD :
				// Wait for host cmd
				if ( pl_usart_data_avail() )
				{
					eHostManagerState = PL_HOST_MANAGER_UPDATE_FREQ;
				}
				
				break;
				
			case PL_HOST_MANAGER_UPDATE_FREQ :
				// Get cmd
				pl_usart_recv(&rMsgHostProc.uiCmd);
				rMsgHostProc.uiCmd -= '0'; //< '0' offset for readable numeric char
				
				// Check cmd
				if ( rMsgHostProc.uiCmd >= PL_SENSOR_FREQ_MIN && rMsgHostProc.uiCmd <= PL_SENSOR_FREQ_MAX )
				{
					// Give the new freq to consumer (proc)
					xQueueSend(prAppInfos->hQueue_HostProc, &rMsgHostProc.uiCmd, 0);
				}
				
				eHostManagerState = PL_HOST_MANAGER_WAIT_CMD;
				
				break;
				
			default :
				;
		}
		vTaskDelayUntil(&xLastWakeTime, HOST_MANAGER_TASK_PERIOD_MS/portTICK_PERIOD_MS);
	}
}

