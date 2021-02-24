#ifndef __PL_REPORT_HPP
#define __PL_REPORT_HPP



#include <iostream>
#include <fstream>



class pl_report
{
public:
	pl_report();
	virtual int open() = 0;
	virtual int write(const unsigned char *pucByte, unsigned int uiLength) = 0;
	void close();
	~pl_report();
protected:
	std::ofstream _rFile;
};



#endif /* __PL_REPORT_HPP */

