#include "pl_proc_manager.h"



// -------------------- Constants --------------------
#define PROC_MANAGER_START_CHAR 'S'

#define PROC_MANAGER_WATERMARK 4


// -------------------- Global variables --------------------
static pl_proc_manager_state_t geProcManagerState;


// -------------------- HAL Functions --------------------
void pl_proc_manager_init(pl_app_infos_t *prAppInfos)
{
	// Send 'START' char to host
	pl_usart_send(PROC_MANAGER_START_CHAR);
	
	geProcManagerState = PL_PROC_MANAGER_INIT;
}


void pl_proc_manager_run(pl_app_infos_t *prAppInfos)
{
	uint8_t tuiData[SENSOR_BUF_SIZE_MAX] = {0};
	uint8_t uiCmd = 0;
	uint8_t i = 0;
	
	switch (geProcManagerState)
	{
		case PL_PROC_MANAGER_INIT :
			geProcManagerState = PL_PROC_MANAGER_CHECK_SENSOR;			
			break;
			
		case PL_PROC_MANAGER_CHECK_SENSOR :
			// Dispatch actions depending on app state
			if ( pl_sensor_data_avail() )
			{
				// Data ready
				geProcManagerState = PL_PROC_MANAGER_GET_DATA;
			}
			else if ( pl_notifier_data_avail(&prAppInfos->rNotifier) )
			{
				// Freq update requested
				geProcManagerState = PL_PROC_MANAGER_SET_FREQ;
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
			
			geProcManagerState = PL_PROC_MANAGER_CHECK_SENSOR;
			
			break;
			
		case PL_PROC_MANAGER_SET_FREQ :
			// Take the new freq from producer (host)
			pl_notifier_take(&prAppInfos->rNotifier, &uiCmd);
			
			// [Re-]start sensor with new freq, stop it otherwise (one-shot mode)
			pl_sensor_stop();
			if (uiCmd > PL_SENSOR_FREQ_ONE_SHOT)
			{
				pl_sensor_start(uiCmd, PROC_MANAGER_WATERMARK);
			}
			
			geProcManagerState = PL_PROC_MANAGER_CHECK_SENSOR;
			
			break;
			
		default :
			;
	}
}

