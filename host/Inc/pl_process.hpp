#ifndef __PL_PROCESS_HPP
#define __PL_PROCESS_HPP



#include "pl_error.hpp"
#include "pl_uart.hpp"
#include "pl_report.hpp"
#include "pl_report_bin.hpp"
#include "pl_report_txt.hpp"



typedef enum pl_sensor_freq
{
	PL_SENSOR_FREQ_NONE = '0',
	PL_SENSOR_FREQ_1_HZ,
	PL_SENSOR_FREQ_7_HZ,
	PL_SENSOR_FREQ_12_5_HZ,
	PL_SENSOR_FREQ_25_HZ,
} pl_sensor_freq_t;



class pl_process
{
public:
	pl_process(const char *pcDevPath);
	void initialize(pl_sensor_freq_t eSensorFreq, unsigned int uiNbSamp);
	unsigned int get_samp();
	void shutdown();
	~pl_process();
private:
	pl_process(const pl_process&) = delete; //< Delete copy-constructor
	pl_process& operator=(const pl_process&) = delete; //< Delete assigment operator
	
	pl_uart _rUart;
	pl_report **_tprReport;
	unsigned int _uiNbSamp;
};



#endif /* __PL_PROCESS_HPP */

