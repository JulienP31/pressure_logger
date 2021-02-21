#ifndef __PL_REPORT_TXT_HPP
#define __PL_REPORT_TXT_HPP



#include "pl_report.hpp"



class pl_report_txt : public pl_report
{
public:
	int open();
	int write(unsigned char *pucByte, unsigned int uiLength) const;
	~pl_report_txt();
};



#endif /* __PL_REPORT_TXT_HPP */

