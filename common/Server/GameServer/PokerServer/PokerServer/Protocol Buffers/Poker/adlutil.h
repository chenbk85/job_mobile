//------------------------------------------------------------------------------------
// Module Name			: util(.h)
// First Modified Date	: 2010/07/02
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Utility functions
//------------------------------------------------------------------------------------
#pragma once
#include <string>
#include "xadldefine.h"

using namespace std;

namespace util
{
	void CopyString( string& strTo, const string& strFrom );
	__int64 GetCurrentSystemTime();
	bool ParsePreToken(string& sMsg, string& sToken, string sDelimeter);
	bool ParseStringToString( string &sData, vector<string>& vt, string sDelimeter );
	bool IsDifferentDay( __int64 lTime1, __int64 lTime2 );
	bool IsRefillResetDay(__int64 lTime1, __int64 lTime2);
	int	 Rand( int n );
}

#define MAX_GSTRINGBUF (1024)
//string viformat(LPCSTR fmt, va_list vl);
string format(LPCSTR fmt, ...);


string LongToStr(__int64 llMoney, long lType);
int GetOptionString(string sOption, string sType, int iMax);
string GetOptionString(string sOption, string sType);
bool Is_NO_IPCheck_ID( string &strid );
bool IsGhostIDCheck(const string& sUID);
__int64 GetCurrentSystemTime();
string GetCurrentSystemTime_s();
bool IsDifferenceDay(__int64 lTime);
void ParseString(string sSource, vector<string>& vtParsed);

