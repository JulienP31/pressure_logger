#include "pl_notifier.h"



// -------------------- HAL Functions --------------------
void pl_notifier_init(pl_notifier_t *prNotifier)
{
	prNotifier->uiByte = 0;
	prNotifier->bDataAvail = 0;
}


void pl_notifier_give(pl_notifier_t *prNotifier, uint8_t uiByte)
{
	prNotifier->uiByte = uiByte;
	prNotifier->bDataAvail = 1;
}


void pl_notifier_take(pl_notifier_t *prNotifier, uint8_t *puiByte)
{
	*puiByte = prNotifier->uiByte;
	pl_notifier_init(prNotifier);
}


uint8_t pl_notifier_data_avail(pl_notifier_t *prNotifier)
{
	return prNotifier->bDataAvail;
}

