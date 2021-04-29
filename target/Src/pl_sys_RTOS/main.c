#include "main.h"



static void system_clock_config(void);


// -------------------- main Function --------------------
int main(void)
{
	pl_app_infos_t rAppInfos = {0};
	
	// Initialize HW resources
	system_clock_config();
	pl_led_init();
	pl_usart_init();
	pl_sensor_init();
	
	// Initialize SW resources
	rAppInfos.hQueue_HostProc = xQueueCreate(PL_HP_QUEUE_LEN, PL_HP_QUEUE_ITEM_SIZE);
	
	// Create tasks
        xTaskCreate(pl_host_task, "host", configMINIMAL_STACK_SIZE, &rAppInfos, PL_HOST_TASK_PRIORITY, NULL);
        xTaskCreate(pl_proc_task, "proc", configMINIMAL_STACK_SIZE, &rAppInfos, PL_PROC_TASK_PRIORITY, NULL);
		
	// Run tasks
	vTaskStartScheduler();
	
	while (1) { }
}


// -------------------- system_clock_config Function --------------------
static void system_clock_config(void)
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

