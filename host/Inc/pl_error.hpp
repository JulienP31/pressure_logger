#ifndef __PL_ERROR_HPP
#define __PL_ERROR_HPP



#include <exception>
#include <cstdio>
#include <cstring>



class pl_error : public std::exception
{
public:
	pl_error(const char *pcErrDesc, int iErrCode);
	pl_error(const pl_error& rError) noexcept; //< Copy-constructor [NOTA : https://www.cplusplus.com/articles/y8hv0pDG/]
	const char *what() const noexcept;
	~pl_error();
private:
	pl_error& operator=(const pl_error&) = delete; //< Delete assigment operator

	char *_pcErrDesc;
};



#endif /* __PL_ERROR_HPP */

