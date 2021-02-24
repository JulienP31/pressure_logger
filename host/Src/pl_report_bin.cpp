#include "pl_report_bin.hpp"



int pl_report_bin::open()
{
	_rFile.open("pressure.bin", std::ios::binary | std::ios::trunc);

	return _rFile.is_open() ? 0 : -1;
}


int pl_report_bin::write(const unsigned char *pucByte, unsigned int uiLength)
{
	_rFile.write((const char *)pucByte, uiLength);

	return _rFile.good() ? 0 : -2;
}



pl_report_bin::~pl_report_bin()
{
	
}

