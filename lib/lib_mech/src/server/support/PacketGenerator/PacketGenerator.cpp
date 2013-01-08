/* file : PacketGenerator.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2007-07-26 10:20:23
comp.: jgame.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "common/jInit.h"
#include "PacketGenerator.h"
#include "conio.h"

tcstr g_szName_HEADER_NameSpace=0;
int g_bDebugPrint=2;

void _jConsolePrinterFunc( const TCHAR *szString,bool bAdd )
{
	DWORD writtenCount;

	if(bAdd)
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), szString, jt_strlen(szString), &writtenCount, NULL);
	else
	{
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), _T("\n"), 1, &writtenCount, NULL);
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), szString, jt_strlen(szString), &writtenCount, NULL);
	}

}



int _tmain(int argc, _TCHAR* argv[])
{
#ifdef _DEBUG
	jMB("debug mode","안내");
#endif
	//try{
		//jUtil_Create();
		jMech_Init();

		nInterface::g_pjILog->SetPrinter(_jConsolePrinterFunc);
		if(argc <3)
		{
			jMB("arg 를세팅하세요.","종료");
			return 0;
		}
		nFileSystem::jFileName fn(argv[1]);

		if(jt_strstr(fn.ext,_T("xml") ) )
		{
			_tmain_Gen_Xml(argc,argv);
			return 0;
		}

		if(argc<3)	return 0;


		// packetgenerator.exe 
		if(!jt_strcmp(argv[1], _T("ucd")) )
		{
			_tmain_Gen_ucd(argc,argv);
		}
		else if(!jt_strcmp(argv[1], _T("usd")) )
		{
			_tmain_Gen_usd(argc,argv);
		}
		else if(!jt_strcmp(argv[1], _T("uss")) )
		{
			_tmain_Gen_uss(argc,argv);
		}
		else if(!jt_strcmp(argv[1], _T("uad") ) )
		{
			_tmain_Gen_uad(argc,argv);
		}

		jMech_Close();
/*
	}
	catch (tcstr sz)
	{
		jt_printf(_T("error throw : %s"),sz);
	}
	*/
	return 0;
}
