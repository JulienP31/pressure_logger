#include "main.h"



int main(void)
{
	// Enable APB2 clock domain (GPIOA for LED, TIM1 for time, SPI1 for sensor, USART1 for host)
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	// Initialize hardware
	pl_led_init();
	
	while (1)
	{
		pl_led_toggle();
	}
}

