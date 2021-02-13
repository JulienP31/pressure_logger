#include "main.h"



#define DEBUG 1


// -------------------- Debug Functions --------------------
#if DEBUG

#include <string.h>


void debug_usart(void)
{
	uint8_t uiMyByte = 'a';
	
	pl_usart_send(uiMyByte);
	while (1)
	{
		if ( pl_usart_data_avail() )
		{
			pl_led_toggle();
			pl_usart_recv(&uiMyByte);
			pl_usart_send(uiMyByte+1);
			pl_time_waitMs(100);
		}
	}
}


void debug_sensor(void)
{
	uint8_t tuiBuffer[256] = {0};
	uint8_t uiNbSamp = 0;
	pl_sensor_freq_t eFreq = PL_SENSOR_FREQ_1_HZ;
	
	for (eFreq = PL_SENSOR_FREQ_1_HZ ; eFreq <= PL_SENSOR_FREQ_7_HZ ; eFreq++)
	{
		memset(tuiBuffer, 0, sizeof(tuiBuffer));
		uiNbSamp = 0;
		pl_sensor_start(eFreq, 4);
		while (uiNbSamp < 30)
		{
			if ( pl_sensor_data_avail() )
			{
				uiNbSamp += pl_sensor_get_data(tuiBuffer + uiNbSamp);
			}
		}
		pl_sensor_stop();
	}
}

#endif


// -------------------- Main Function --------------------
int main(void)
{
	// Initialize hardware
	pl_led_init();
	pl_time_init();
	//pl_usart_init();
	pl_sensor_init();
	
	//debug_usart();
	debug_sensor();
	
	// Initialize state machines
	
	
	while (1)
	{
		// Run state machines
		
	}
}

