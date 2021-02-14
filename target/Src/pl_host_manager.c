#include "pl_host_manager.h"



// -------------------- Constants --------------------
#define HOST_MANAGER_START 'S'
#define HOST_MANAGER_ACK   'A'
#define HOST_MANAGER_NACK  'N'


// -------------------- Global variables --------------------
static pl_host_manager_state_t geHostManagerState;


// -------------------- HAL Functions --------------------
void pl_host_manager_init(pl_app_infos_t *prAppInfos)
{
	geHostManagerState = PL_HOST_MANAGER_INIT;
}


void pl_host_manager_run(pl_app_infos_t *prAppInfos)
{
	uint8_t uiCmd = 0;
	
	switch (geHostManagerState)
	{
		case PL_HOST_MANAGER_INIT :
			// Send 'START' char to host
			pl_usart_send(HOST_MANAGER_START);
			
			geHostManagerState = PL_HOST_MANAGER_WAIT_CMD;
			
			break;
			
		case PL_HOST_MANAGER_WAIT_CMD :
			// Wait for host cmd
			if ( pl_usart_data_avail() )
			{
				geHostManagerState = PL_HOST_MANAGER_UPDATE_FREQ;
			}
			
			break;
			
		case PL_HOST_MANAGER_UPDATE_FREQ :
			// Get cmd
			pl_usart_recv(&uiCmd);
			
			// Check cmd (offset '0' for readable numeric char)
			if ( uiCmd-'0' >= PL_SENSOR_FREQ_MIN && uiCmd-'0' <= PL_SENSOR_FREQ_MAX )
			{
				// Update freq info
				prAppInfos->eFreq = uiCmd;
				
				// Set flag
				prAppInfos->bUpdateFreq = 1;
				
				// Send 'ACK' char to host
				pl_usart_send(HOST_MANAGER_ACK);
			}
			else
			{
				// Invalid cmd -> Send 'NACK' char to host
				pl_usart_send(HOST_MANAGER_NACK);				
			}
			
			geHostManagerState = PL_HOST_MANAGER_WAIT_CMD;
			
			break;
			
		default :
			;
	}
}

