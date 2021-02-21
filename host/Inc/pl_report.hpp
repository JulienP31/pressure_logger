#ifndef __PL_REPORT_HPP
#define __PL_REPORT_HPP



class pl_report
{
public:
	pl_report();
	virtual int open() = 0;
	virtual int write(unsigned char *pucByte, unsigned int uiLength) const = 0;
	void close();
	~pl_report();
};



#endif /* __PL_REPORT_HPP */

