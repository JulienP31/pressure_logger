#ifndef __PL_UART_HPP
#define __PL_UART_HPP



class pl_uart
{
public:
	pl_uart();
	int initialize();
	int send(unsigned char ucByte) const;
	int recv(unsigned char *pucByte) const;
	void shutdown();
	~pl_uart();
};



#endif /* __PL_UART_HPP */

