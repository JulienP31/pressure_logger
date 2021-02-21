#include "pl_report_bin.hpp"



int pl_report_bin::open()
{
	
	
	return 0;
}


int pl_report_bin::write(unsigned char *pucByte, unsigned int uiLength) const
{
	*pucByte = 'B';
	
	return 0;
}



pl_report_bin::~pl_report_bin()
{
	
}

