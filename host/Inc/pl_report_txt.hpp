#ifndef __PL_REPORT_TXT_HPP
#define __PL_REPORT_TXT_HPP



#include <cstring>
#include "pl_report.hpp"



class pl_report_txt : public pl_report
{
public:
	int open();
	int write(const unsigned char *pucByte, unsigned int uiLength);
	~pl_report_txt();
};



#endif /* __PL_REPORT_TXT_HPP */

