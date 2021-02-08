#include "main.h"



int main(void)
{	
	// Initialize hardware
	pl_led_init();
	
	// Initialize state machines
	
	while (1)
	{
		// Run state machines
		pl_led_toggle();
	}
}

