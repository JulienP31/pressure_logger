#include "pl_process.hpp"



#define SAMP_SIZE 3



pl_process::pl_process(const char *pcDevPath) :
	_rUart(pcDevPath)
{
	
}


void pl_process::initialize(pl_sensor_freq_t eSensorFreq, unsigned int uiNbSamp)
{
	int iRet = 0;

	// Initialize UART
	iRet = _rUart.initialize();
	if (iRet != 0)
		throw pl_error("Could not initialize UART", iRet);

	// Start sensor with specified data rate
	iRet = _rUart.send(eSensorFreq);
	if (iRet == 0)
		throw pl_error("Could not start sensor", iRet);
	
	// Set the nb of samples to log
	_uiNbSamp = uiNbSamp;
}


unsigned int pl_process::get_samp()
{
	unsigned char tucByte[SAMP_SIZE] = {0};
	int iRet = 0;
	int i = 0;

	// Get 3 bytes (XL/L/H) for each sample
	for (i = 0 ; i < SAMP_SIZE ; i++)
	{
		iRet = _rUart.recv(tucByte+i, 1);
		if (iRet)
		{
			;
		}
		else
		{
			throw pl_error("Could not receive sensor sample", iRet);
		}
	}
	
	// Return remaining samples
	return --_uiNbSamp;
}


void pl_process::shutdown()
{
	// Stop sensor
	_rUart.send(PL_SENSOR_FREQ_NONE);
	
	// Shutdown UART
	_rUart.shutdown();
}


pl_process::~pl_process()
{
	shutdown();
}

