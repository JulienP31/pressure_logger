#include "pl_report_txt.hpp"



int pl_report_txt::open()
{
	
	
	return 0;
}


int pl_report_txt::write(unsigned char *pucByte, unsigned int uiLength) const
{
	*pucByte = 'T';
	
	return 0;
}



pl_report_txt::~pl_report_txt()
{
	
}

