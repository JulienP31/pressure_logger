#ifndef __PL_ERROR_HPP
#define __PL_ERROR_HPP



#include <exception>
#include <cstdio>



class pl_error : public std::exception
{
public:
	pl_error(const char *pcErrDesc, int iErrCode);
	const char *what() const throw();
	~pl_error();
private:
	char *_pcErrDesc;
};



#endif /* __PL_ERROR_HPP */

