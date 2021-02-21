#ifndef __PL_REPORT_BIN_HPP
#define __PL_REPORT_BIN_HPP



#include "pl_report.hpp"



class pl_report_bin : public pl_report
{
public:
	int open();
	int write(unsigned char *pucByte, unsigned int uiLength) const;
	~pl_report_bin();
};



#endif /* __PL_REPORT_BIN_HPP */

