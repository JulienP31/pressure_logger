#include "pl_report.hpp"



pl_report::pl_report()
{
	
}


void pl_report::close()
{
	_rFile.close();
}


pl_report::~pl_report()
{
	close();
}

