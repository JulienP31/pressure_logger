#include "main.h"



#define DEBUG 1


void system_clock_config(void);
void debug_usart(void);
void debug_sensor(void);


// -------------------- main Function --------------------
int main(void)
{
	/* debug_usart(); */
	/* debug_sensor(); */
	
	pl_app_infos_t rAppInfos = {0};
	
	// Initialize HW resources
	system_clock_config();
	pl_led_init();
	pl_usart_init();
	pl_sensor_init();
	
	// Initialize SW resources
	pl_notifier_init(&rAppInfos.rNotifier);
		
	// Initialize state machines
	pl_host_manager_init(&rAppInfos);
	pl_proc_manager_init(&rAppInfos);
	
	while (1)
	{
		// Run state machines
		pl_host_manager_run(&rAppInfos);
		pl_proc_manager_run(&rAppInfos);
	}
}


// -------------------- system_clock_config Function --------------------
void system_clock_config(void)
{
	RCC_OscInitTypeDef rRCC_OscInit = {0};
	RCC_ClkInitTypeDef rRCC_ClkInit = {0};

	// Initialize RCC oscillators
	rRCC_OscInit.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	rRCC_OscInit.HSIState = RCC_HSI_ON;
	rRCC_OscInit.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	rRCC_OscInit.PLL.PLLState = RCC_PLL_NONE;
	
	HAL_RCC_OscConfig(&rRCC_OscInit);

	// Initialize CPU, AHB and APB bus clocks
	rRCC_ClkInit.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	rRCC_ClkInit.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	rRCC_ClkInit.AHBCLKDivider = RCC_SYSCLK_DIV1;
	rRCC_ClkInit.APB1CLKDivider = RCC_HCLK_DIV1;
	rRCC_ClkInit.APB2CLKDivider = RCC_HCLK_DIV1;
	
	HAL_RCC_ClockConfig(&rRCC_ClkInit, FLASH_LATENCY_0);
}


// -------------------- Debug Functions --------------------
#if DEBUG

#include <string.h>
#include "pl_time.h"


void debug_usart(void)
{
	uint8_t uiMyByte = 'a';
	
	system_clock_config();
	pl_time_init();
	pl_led_init();
	pl_usart_init();
	
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
	uint8_t tuiBuffer[SENSOR_BUF_SIZE_MAX] = {0};
	uint8_t uiNbSamp = 0;
	pl_sensor_freq_t eFreq = PL_SENSOR_FREQ_1_HZ;
	
	system_clock_config();
	pl_sensor_init();
	
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

