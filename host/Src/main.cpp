#include "main.hpp"



#define PL_NB_SAMP 100



int main(void)
{
	int iRet = 0;
	
	try
	{
		pl_process proc("/dev/ttyUSB0");
		
		proc.initialize(PL_SENSOR_FREQ_25_HZ, PL_NB_SAMP);
		while ( proc.get_samp() );
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		iRet = -1;
	}

	return iRet;
}

