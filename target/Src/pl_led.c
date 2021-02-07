#include "pl_led.h"



// -------------------- pl_led_init() --------------------
void pl_led_init(void)
{
	GPIO_InitTypeDef rGPIO_Init = {0};

	// Configure LED GPIO
	rGPIO_Init.Pin = LED_PIN;
	rGPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	rGPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
	rGPIO_Init.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(LED_PORT, &rGPIO_Init);	
}


// -------------------- pl_led_toggle() --------------------
void pl_led_toggle(void)
{
	HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
}


// -------------------- pl_led_deinit() --------------------
void pl_led_deinit(void)
{
	HAL_GPIO_DeInit(LED_PORT, LED_PIN);
}

