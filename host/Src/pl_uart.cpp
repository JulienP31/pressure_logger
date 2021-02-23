#include "pl_uart.hpp"



pl_uart::pl_uart(const char *pcFilePath) :
	_iFileDesc(0)
{
	size_t uiLength = 0;

	uiLength = strlen(pcFilePath);
	_pcFilePath = new char[uiLength+1];
	strncpy(_pcFilePath, pcFilePath, uiLength);

	memset(&_rTerm, 0, sizeof(_rTerm));
}


int pl_uart::initialize()
{
	int iRet = 0;

	// Open serial port
	_iFileDesc = open(_pcFilePath, O_RDWR);
	if (_iFileDesc < 0)
		return _iFileDesc;

	// Get serial port attributes
	iRet = tcgetattr(_iFileDesc, &_rTerm);
	if (iRet != 0)
		return iRet;

	// Set control flags
	_rTerm.c_cflag &= ~PARENB; //< Clear parity bit, disabling parity
	_rTerm.c_cflag &= ~CSTOPB; //< Clear stop field, only one stop bit used in communication
	_rTerm.c_cflag &= ~CSIZE; //< Clear all the size bits
	_rTerm.c_cflag |= CS8; //< 8 bits per byte
	_rTerm.c_cflag &= ~CRTSCTS; //< Disable RTS/CTS hardware flow control
	_rTerm.c_cflag |= CREAD | CLOCAL; //< Turn on READ & ignore ctrl lines (CLOCAL = 1)

	_rTerm.c_cc[VTIME] = 100; //< Wait for up to 10 s (100 deciseconds), returning as soon as any data is received
	_rTerm.c_cc[VMIN] = 0;

	// Set local flags
	_rTerm.c_lflag &= ~ICANON; //< Non-canonical mode
	_rTerm.c_lflag &= ~(ECHO | ECHOE | ECHONL); //< Disable echo, erase and new-line echo
	_rTerm.c_lflag &= ~ISIG; //< Disable interpretation of INTR, QUIT and SUSP

	// Set input flags
	_rTerm.c_iflag &= ~(IXON | IXOFF | IXANY); //< Turn off software flow control
	_rTerm.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); //< Disable any special handling of received bytes

	// Set output flags
	_rTerm.c_oflag &= ~OPOST; //< Prevent special interpretation of output bytes (e.g. newline chars)
	_rTerm.c_oflag &= ~ONLCR; //< Prevent conversion of newline to carriage return/line feed

	// Set baud rate
	cfsetspeed(&_rTerm, B115200);

	// Apply the new serial port attributes
	iRet = tcsetattr(_iFileDesc, TCSANOW, &_rTerm);
	if (iRet != 0)
		return iRet;

	return 0;
}


int pl_uart::send(unsigned char ucByte) const
{		
	return write(_iFileDesc, &ucByte, 1);
}


int pl_uart::recv(unsigned char *pucBuffer, size_t uiLength) const
{
	return read(_iFileDesc, pucBuffer, uiLength);
}


void pl_uart::shutdown()
{
	if (_iFileDesc)
		close(_iFileDesc);
}


pl_uart::~pl_uart()
{
	shutdown();
	if (_pcFilePath)
		delete[] _pcFilePath;
}

