#ifndef __PL_NOTIFIER_H
#define __PL_NOTIFIER_H



#include "stm32f1xx_hal.h"


// -------------------- Typedefs --------------------
typedef struct pl_notifier
{
	uint8_t uiByte;
	uint8_t bDataAvail;
} pl_notifier_t;


// -------------------- HAL Functions --------------------
void pl_notifier_init(pl_notifier_t *prNotifier);
void pl_notifier_give(pl_notifier_t *prNotifier, uint8_t uiByte);
void pl_notifier_take(pl_notifier_t *prNotifier, uint8_t *puiByte);
uint8_t pl_notifier_data_avail(pl_notifier_t *prNotifier);



#endif /* __PL_NOTIFIER_H */
