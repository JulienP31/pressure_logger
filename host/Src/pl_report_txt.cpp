#include "pl_report_txt.hpp"



#define BUF_MAX_LEN 16



int pl_report_txt::open()
{
	_rFile.open("pressure.txt", std::ios::trunc);

	return _rFile.is_open() ? 0 : -1;
}


int pl_report_txt::write(const unsigned char *pucByte, unsigned int uiLength)
{
	char tcBuffer[BUF_MAX_LEN] = {0};
	int iPressure = 0;
	int i = 0;

	for (i = 0 ; i < uiLength ; i+=3)
	{
		iPressure = (pucByte[i+2] << 16 | pucByte[i+1] << 8 | pucByte[i+0] << 0) / 4096;

		snprintf(tcBuffer, BUF_MAX_LEN, "%d", iPressure);

		_rFile.write((const char *)tcBuffer, strlen(tcBuffer));
		_rFile << std::endl;
	}

	return _rFile.good() ? 0 : -2;
}



pl_report_txt::~pl_report_txt()
{
	
}

