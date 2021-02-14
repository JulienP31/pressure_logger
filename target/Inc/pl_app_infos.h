#ifndef __PL_APP_INFOS_H
#define __PL_APP_INFOS_H



#include "pl_sensor.h"


// -------------------- Typedefs --------------------
typedef struct pl_app_infos
{
	uint8_t bUpdateFreq;
	pl_sensor_freq_t eFreq;
} pl_app_infos_t;



#endif /* __PL_APP_INFOS_H */
