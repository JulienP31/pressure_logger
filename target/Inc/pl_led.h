#ifndef __PL_LED_H
#define __PL_LED_H



#include "stm32f1xx_hal_gpio.h"


// -------------------- Constants --------------------
#define LED_PORT GPIOA
#define LED_PIN  GPIO_PIN_5


// -------------------- Functions --------------------
void pl_led_init(void);
void pl_led_toggle(void);
void pl_led_deinit(void);



#endif /* __PL_LED_H */
