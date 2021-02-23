#include "pl_error.hpp"



#define ERR_DESC_MAX_LEN 128



pl_error::pl_error(const char *pcErrDesc, int iErrCode)
{
	_pcErrDesc = new char[ERR_DESC_MAX_LEN];
	if (pcErrDesc)
		snprintf(_pcErrDesc, ERR_DESC_MAX_LEN, "[pl_error] %s (ret = %d)", pcErrDesc, iErrCode);
	else
		snprintf(_pcErrDesc, ERR_DESC_MAX_LEN, "[pl_error] Undefined (ret = %d)", iErrCode);
}


pl_error::pl_error(const pl_error& rError) noexcept
{
	_pcErrDesc = new char[ERR_DESC_MAX_LEN];
	strncpy(_pcErrDesc, rError._pcErrDesc, ERR_DESC_MAX_LEN);
}


const char *pl_error::what() const noexcept
{
	return _pcErrDesc;
}


pl_error::~pl_error()
{
	if (_pcErrDesc)
		delete[] _pcErrDesc;
}

