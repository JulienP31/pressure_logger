#ifndef __PL_UART_HPP
#define __PL_UART_HPP



#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>



class pl_uart
{
public:
	pl_uart(const char *pcDevPath);
	int initialize();
	int send(unsigned char ucByte) const;
	int recv(unsigned char *pucBuffer, size_t uiLength) const;
	void shutdown();
	~pl_uart();
private:
	pl_uart(const pl_uart&) = delete; //< Delete copy-constructor
	pl_uart& operator=(const pl_uart&) = delete; //< Delete assigment operator

	char *_pcDevPath;
	int _iFileDesc;
	struct termios _rTerm;
};



#endif /* __PL_UART_HPP */

