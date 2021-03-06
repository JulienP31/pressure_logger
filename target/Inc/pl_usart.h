#ifndef __PL_USART_H
#define __PL_USART_H



#include "stm32f1xx_hal.h"


// -------------------- HAL Functions --------------------
void pl_usart_init(void);
void pl_usart_send(uint8_t uiByte);
void pl_usart_recv(uint8_t *puiByte);
uint8_t pl_usart_data_avail(void);



#endif /* __PL_USART_H */
