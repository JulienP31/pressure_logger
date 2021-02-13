#include "pl_proc_manager.h"



// -------------------- Constants --------------------



// -------------------- Global variables --------------------
static pl_proc_manager_state_t eProcManagerState;


// -------------------- HAL Functions --------------------
void pl_proc_manager_init(void)
{
	eProcManagerState = PL_PROC_MANAGER_INIT;
}


void pl_proc_manager_run(void)
{
	switch (eProcManagerState)
	{
		case PL_PROC_MANAGER_INIT :
		
			break;
		case PL_PROC_MANAGER_WAIT_DATA :
		
			break;
		case PL_PROC_MANAGER_GET_DATA :
		
			break;
		case PL_PROC_MANAGER_CHECK_FREQ :
		
			break;
		case PL_PROC_MANAGER_APPLY_FREQ :
		
			break;
		default :
			;
	}
}

