#include "main.h"



int main(void)
{	
	// Initialize hardware
	pl_led_init();
	pl_time_init();
	
	
	// Initialize state machines
	
	
	while (1)
	{
		// Run state machines
		
		
		// DEBUG (to be deleted)
		pl_led_toggle();
		pl_time_waitMs(500);
	}
}

