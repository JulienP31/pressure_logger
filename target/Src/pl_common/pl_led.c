#include "pl_led.h"



// -------------------- Constants --------------------
#define LED_PORT GPIOA
#define LED_PIN  GPIO_PIN_5


// -------------------- HAL Functions --------------------
void pl_led_init(void)
{
	GPIO_InitTypeDef rGPIO_Init = {0};
	
	// Enable GPIOA clock
	__GPIOA_CLK_ENABLE();

	// Configure LED GPIO
	rGPIO_Init.Pin = LED_PIN;
	rGPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	rGPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
	
	// Initialize LED GPIO
	HAL_GPIO_Init(LED_PORT, &rGPIO_Init);	
}


void pl_led_toggle(void)
{
	HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
}

