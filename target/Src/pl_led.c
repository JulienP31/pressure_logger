#include "stm32f1xx_hal_rcc.h"
#include "stm32f1xx_hal_gpio.h"
#include "pl_led.h"



// -------------------- Constants --------------------
#define LED_PORT GPIOA
#define LED_PIN  GPIO_PIN_5


// -------------------- Functions --------------------
void pl_led_init(void)
{
	GPIO_InitTypeDef rGPIO_Init = {0};
	
	// Enable GPIOA clock
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// Configure LED GPIO
	rGPIO_Init.Pin = LED_PIN;
	rGPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	rGPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
	rGPIO_Init.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(LED_PORT, &rGPIO_Init);	
}


void pl_led_toggle(void)
{
	HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
}


void pl_led_deinit(void)
{
	HAL_GPIO_DeInit(LED_PORT, LED_PIN);
}

