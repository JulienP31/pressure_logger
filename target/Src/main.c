#include "main.h"



int main(void)
{
	uint8_t uiMyByte = 'Y';
	
	// Initialize hardware
	pl_led_init();
	pl_time_init();
	pl_usart_init();
	
	
	// Initialize state machines
	
	
	while (1)
	{
		// Run state machines
		
		
		// DEBUG (to be deleted)
		pl_led_toggle();
		pl_time_waitMs(500);
		if ( pl_usart_data_avail() )
		{
			pl_usart_recv(&uiMyByte);
			pl_usart_send(uiMyByte);
		}
	}
}

