#include "main.hpp"



#define PL_NB_REPORTS 2



int main(void)
{
	int iRet = 0;
	
	try
	{
		unsigned char ucByte = 0;
		int i = 0;
		pl_uart rUart;
		pl_report *tprReports[PL_NB_REPORTS] = {NULL};
		pl_report_bin rReport_bin;
		pl_report_txt rReport_txt;
		
		rUart.recv(&ucByte);
		cout << ucByte << '\n';
		
		tprReports[0] = &rReport_bin;
		tprReports[1] = &rReport_txt;
		for (i = 0 ; i < PL_NB_REPORTS ; i++)
		{
			tprReports[i]->write(&ucByte, 1);
			cout << ucByte << '\n';
		}
	}
	catch (exception &e)
	{
		cout << "Exception: " << e.what();
		iRet = -1;
	}

	return iRet;
}

