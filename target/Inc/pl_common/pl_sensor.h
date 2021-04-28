#ifndef __PL_SENSOR_H
#define __PL_SENSOR_H



#include "stm32f1xx_hal.h"


// -------------------- Constants --------------------
#define SENSOR_FIFO_SIZE    32

#define SENSOR_BUF_SIZE_MAX (3 * SENSOR_FIFO_SIZE)


// -------------------- Typedefs --------------------
typedef enum pl_sensor_freq
{
	PL_SENSOR_FREQ_ONE_SHOT,
	PL_SENSOR_FREQ_1_HZ,
	PL_SENSOR_FREQ_7_HZ,
	PL_SENSOR_FREQ_12_5_HZ,
	PL_SENSOR_FREQ_25_HZ,
	PL_SENSOR_FREQ_MIN = PL_SENSOR_FREQ_ONE_SHOT,
	PL_SENSOR_FREQ_MAX = PL_SENSOR_FREQ_25_HZ
} pl_sensor_freq_t;


// -------------------- HAL Functions --------------------
void pl_sensor_init(void);
void pl_sensor_start(pl_sensor_freq_t eFreq, uint8_t uiWatermark);
uint8_t pl_sensor_get_data(uint8_t tuiBuffer[]);
uint8_t pl_sensor_data_avail(void);
void pl_sensor_stop(void);



#endif /* __PL_SENSOR_H */
