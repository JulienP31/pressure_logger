#include "pl_proc_manager.h"



// -------------------- Constants --------------------
#define PROC_MANAGER_TASK_PERIOD_MS 5

#define PROC_MANAGER_START_CHAR 'S'

#define PROC_MANAGER_WATERMARK 4


// -------------------- HAL Functions --------------------
void pl_proc_task(void *pvParameters)
{
	pl_proc_manager_state_t eProcManagerState = PL_PROC_MANAGER_INIT;
	pl_app_infos_t *prAppInfos = (pl_app_infos_t *)pvParameters;
	pl_msg_host_proc_t rMsgHostProc = {0};
	uint8_t tuiData[SENSOR_BUF_SIZE_MAX] = {0};
	uint8_t i = 0;
	
	// Send 'START' char to host
	pl_usart_send(PROC_MANAGER_START_CHAR);
	
	TickType_t xLastWakeTime = xTaskGetTickCount();
	
	while (1)
	{
		switch (eProcManagerState)
		{
			case PL_PROC_MANAGER_INIT :
				eProcManagerState = PL_PROC_MANAGER_CHECK_SENSOR;			
				break;
				
			case PL_PROC_MANAGER_CHECK_SENSOR :
				// Dispatch actions depending on app state
				if ( pl_sensor_data_avail() )
				{
					// Data ready
					eProcManagerState = PL_PROC_MANAGER_GET_DATA;
				}
				else if ( uxQueueMessagesWaiting(prAppInfos->hQueue_HostProc) )
				{
					// Freq update requested
					eProcManagerState = PL_PROC_MANAGER_SET_FREQ;
				}
				
				break;
				
			case PL_PROC_MANAGER_GET_DATA :
				// Get data
				pl_sensor_get_data(tuiData);
				
				// Send data to host
				for (i = 0 ; i < 3*PROC_MANAGER_WATERMARK ; i++)
				{
					pl_usart_send(tuiData[i]);
				}
				
				// Toggle LED
				pl_led_toggle();
				
				eProcManagerState = PL_PROC_MANAGER_CHECK_SENSOR;
				
				break;
				
			case PL_PROC_MANAGER_SET_FREQ :
				// Take the new freq from producer (host)
				xQueueReceive(prAppInfos->hQueue_HostProc, &rMsgHostProc.uiCmd, 0);
				
				// [Re-]start sensor with new freq, stop it otherwise (one-shot mode)
				pl_sensor_stop();
				if (rMsgHostProc.uiCmd > PL_SENSOR_FREQ_ONE_SHOT)
				{
					pl_sensor_start(rMsgHostProc.uiCmd, PROC_MANAGER_WATERMARK);
				}
				
				eProcManagerState = PL_PROC_MANAGER_CHECK_SENSOR;
				
				break;
				
			default :
				;
		}
		vTaskDelayUntil(&xLastWakeTime, PROC_MANAGER_TASK_PERIOD_MS/portTICK_PERIOD_MS);
	}
}

