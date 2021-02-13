#include "pl_host_manager.h"



// -------------------- Constants --------------------



// -------------------- Global variables --------------------
static pl_host_manager_state_t eHostManagerState;


// -------------------- HAL Functions --------------------
void pl_host_manager_init(void)
{
	eHostManagerState = PL_HOST_MANAGER_INIT;
}


void pl_host_manager_run(void)
{
	switch (eHostManagerState)
	{
		case PL_HOST_MANAGER_INIT :
		
			break;
		case PL_HOST_MANAGER_WAIT_CMD :
		
			break;
		case PL_HOST_MANAGER_UPDATE_FREQ :
		
			break;
		default :
			;
	}
}


pl_sensor_freq_t pl_host_manager_get_freq(void)
{
	return PL_SENSOR_FREQ_1_HZ;
}

