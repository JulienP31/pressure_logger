#include "pl_proc_manager.h"



// -------------------- Constants --------------------
#define PROC_MANAGER_WATERMARK 4


// -------------------- Global variables --------------------
static pl_proc_manager_state_t geProcManagerState;


// -------------------- HAL Functions --------------------
void pl_proc_manager_init(pl_app_infos_t *prAppInfos)
{
	geProcManagerState = PL_PROC_MANAGER_INIT;
}


void pl_proc_manager_run(pl_app_infos_t *prAppInfos)
{
	uint8_t tuiData[SENSOR_BUF_SIZE_MAX] = {0};
	uint8_t i = 0;
	
	switch (geProcManagerState)
	{
		case PL_PROC_MANAGER_INIT :
			// Start sensor
			pl_sensor_start(PL_SENSOR_FREQ_MIN, PROC_MANAGER_WATERMARK);
			
			geProcManagerState = PL_PROC_MANAGER_CHECK_SENSOR;
			
			break;
			
		case PL_PROC_MANAGER_CHECK_SENSOR :
			// Dispatch actions depending on app state
			if ( pl_sensor_data_avail() )
			{
				// Data ready
				geProcManagerState = PL_PROC_MANAGER_GET_DATA;
			}
			else if ( prAppInfos->bUpdateFreq )
			{
				// Freq update requested
				geProcManagerState = PL_PROC_MANAGER_SET_FREQ;
			}
			
			break;
			
		case PL_PROC_MANAGER_GET_DATA :
			// Get data
			pl_sensor_get_data(tuiData);
			
			// Send data to host
			for (i = 0 ; i < PROC_MANAGER_WATERMARK ; i++)
			{
				pl_usart_send(tuiData[i]);
			}
			
			// Toggle LED
			pl_led_toggle();
			
			geProcManagerState = PL_PROC_MANAGER_CHECK_SENSOR;
			
			break;
			
		case PL_PROC_MANAGER_SET_FREQ :
			// Re-start sensor with new freq
			pl_sensor_stop();
			pl_sensor_start(prAppInfos->eFreq, PROC_MANAGER_WATERMARK);
			
			// Clear flag
			prAppInfos->bUpdateFreq = 0;
			
			geProcManagerState = PL_PROC_MANAGER_CHECK_SENSOR;
			break;
			
		default :
			;
	}
}

