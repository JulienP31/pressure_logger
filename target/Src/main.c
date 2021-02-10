#include "main.h"



int main(void)
{
	uint8_t uiMyByte = 'a';
	
	// Initialize hardware
	pl_led_init();
	pl_time_init();
	pl_usart_init();
	
	
	// Initialize state machines
	
	pl_usart_send(uiMyByte);
	while (1)
	{
		// Run state machines
		
		
		// DEBUG (to be deleted)
		if ( pl_usart_data_avail() )
		{
			pl_led_toggle();
			pl_usart_recv(&uiMyByte);
			pl_usart_send(uiMyByte+1);
			pl_time_waitMs(100);
		}
	}
}

