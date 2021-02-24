#include "pl_process.hpp"



#define NB_REPORT 2
#define SAMP_SIZE 3



pl_process::pl_process(const char *pcDevPath) :
	_rUart(pcDevPath),
	_uiNbSamp(0)
{
	int i = 0;
	
	_tprReport = new pl_report *[NB_REPORT];

	for (i = 0 ; i < NB_REPORT ; i++)
	{
		switch (i)
		{
			case 0:
				_tprReport[i] = new pl_report_txt;
				break;
			default: //< 1
				_tprReport[i] = new pl_report_bin;
		}
	}
}


void pl_process::initialize(pl_sensor_freq_t eSensorFreq, unsigned int uiNbSamp)
{
	int i = 0;
	int iRet = 0;

	// Initialize UART
	iRet = _rUart.initialize();
	if (iRet != 0)
		throw pl_error("Could not initialize UART", iRet);

	// Start sensor with specified data rate
	iRet = _rUart.send(eSensorFreq);
	if (iRet == 0)
		throw pl_error("Could not start sensor", iRet);

	// Open reports
	for (i = 0 ; i < NB_REPORT ; i++)
	{		
		iRet = _tprReport[i]->open();
		if (iRet < 0)
			throw pl_error("Could not open report", iRet);
	}

	// Set the nb of samples to log
	_uiNbSamp = uiNbSamp;
}


unsigned int pl_process::get_samp()
{
	unsigned char tucByte[SAMP_SIZE] = {0};
	int iRet = 0;
	int i = 0;

	// Get 3 bytes (XL/L/H) for 1 sample
	for (i = 0 ; i < SAMP_SIZE ; i++)
	{
		iRet = _rUart.recv(tucByte+i);
		if (iRet == 0)
			throw pl_error("Could not receive sensor sample", iRet);
	}

	// Log sample
	for (i = 0 ; i < NB_REPORT ; i++)
	{
		iRet = _tprReport[i]->write(tucByte, SAMP_SIZE);
		if (iRet < 0)
			throw pl_error("Could not write report", iRet);
	}
	
	// Return remaining samples
	return --_uiNbSamp;
}


void pl_process::shutdown()
{
	int i = 0;
	
	// Close reports
	for (i = 0 ; i < NB_REPORT ; i++)
	{
		_tprReport[i]->close();
	}

	// Stop sensor
	_rUart.send(PL_SENSOR_FREQ_NONE);
	
	// Shutdown UART
	_rUart.shutdown();
}


pl_process::~pl_process()
{
	int i = 0;

	shutdown();

	for (i = 0 ; i < NB_REPORT ; i++)
	{
		if (_tprReport[i])
			delete _tprReport[i];
	}

	if (_tprReport)
		delete[] _tprReport;
}

