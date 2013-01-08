//------------------------------------------------------------------------------------
// Module Name			: Log(.h)
// First Modified Date	: 2010/07/16
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: A log class work with file.
//------------------------------------------------------------------------------------
#pragma once

#if !defined(DEF_LINUX)
#include <windows.h>
#endif
#include <string>

using namespace std;

//------------------------------------------------------------------------------------
class CLog
//------------------------------------------------------------------------------------
{
private:
	CLog();
public:
	~CLog();

public:
	void CreateLogFile();
	void SetLog( std::string message );

	friend CLog& _LOG();
public:
	HANDLE m_hLog;
};

CLog& _LOG();