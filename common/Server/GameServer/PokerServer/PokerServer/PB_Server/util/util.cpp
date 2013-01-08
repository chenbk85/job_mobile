//------------------------------------------------------------------------------------
// Module Name			: util(.cpp)
// First Modified Date	: 2010/07/02
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Utility functions
//------------------------------------------------------------------------------------


#include "stdafx.h"

#if !defined(DEF_LINUX)
#include <windows.h>
#endif
#include "util.h"
#include "../include/gstring.h"


namespace util
{
	void CopyString( string& strTo, const string& strFrom ) 
	{
		strTo.erase();
		strTo.assign(strFrom.c_str(), strFrom.length());
	}
	__int64 GetCurrentSystemTime()
	{
		SYSTEMTIME st; 
		ZeroMemory(&st, sizeof(SYSTEMTIME));
#ifndef _IPHONE
		GetLocalTime(&st);
#endif
		__int64 lTime=(st.wYear*10000000000ll) + (st.wMonth*100000000) + (st.wDay*1000000) + (st.wHour*10000) + (st.wMinute*100) + st.wSecond;

		return lTime;
	}
	bool ParsePreToken(string& sMsg, string& sToken, string sDelimeter)
	{
		bool bReturn=true;
		if( sDelimeter.empty() )
		{
			sToken=sMsg;
			return true;
		}
		if( sDelimeter==sMsg.substr(0,sDelimeter.size()) )
		{
			sMsg.erase(0, sDelimeter.size());
		}

		strpos lDelPos=sMsg.find(sDelimeter);
		if( lDelPos==string::npos )
		{
			sToken=sMsg;
			bReturn=false;
		}
		else
		{
			sToken=sMsg.substr(0, lDelPos);
		}

		sMsg.erase(0, lDelPos); // sMsg.erase(0, lDelPos + sDelimeter.size());
		sToken;

		return bReturn;
	}
	bool ParseStringToString( string &sData, vector<string>& vt, string sDelimeter )
	{
		string sToken;

		vt.clear();

		for(;;)
		{
			sToken.erase();
			if( !ParsePreToken(sData, sToken, sDelimeter) )
			{
				if (sToken.size()>0)
				{
					vt.push_back(sToken);
				}
				break;
			}
			else
			{
				vt.push_back(sToken);
			}
		}
		return true;
	}
	bool IsDifferentDay( __int64 lTime1, __int64 lTime2 )
	{
		// 20040226152007 - ÀÏ°¡Áö¸¸ ºñ±³
		return ((lTime1 / 1000000)!=(lTime2 / 1000000));
	}
	bool IsRefillResetDay(__int64 lTime1, __int64 lTime2)
	{ // ³· 12½Ã reset
		lTime1-=120000;
		lTime2-=120000;
		return ((lTime1 / 1000000)!=(lTime2 / 1000000));
	}
	int Rand(int n) 
	{
	//	srand( timeGetTime() + (rand() % GetTickCount()) + GetCurrentThreadId() );
		return rand() % n ;
	};
}



//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string LongToStr(__int64 llMoney, long lType)
{
#ifdef _IPHONE
	if(llMoney==0){ return ("0¿ø"); }
	
	string sMark("");
	string sTemp("");	
	string sMoney=::format("%I64i", llMoney);
	UINT uSize=sMoney.size();
	
	if(uSize==0){ return (""); }
	
#else
	if(llMoney==0){ return _T("0¿ø"); }

	string sMark("");
	string sTemp("");	

	char tmpString[256];
	sprintf(tmpString, "%I64i", llMoney);
	string sMoney(tmpString);//=::format("%I64i", llMoney);
	UINT uSize=sMoney.size();

	if(uSize==0){ return _T(""); }
#endif

	if(llMoney<0){
		sMoney.erase(0,1);
		sMark="-";
		--uSize;
	}

	vector<string> vtDel;
	vtDel.push_back("¿ø");
	vtDel.push_back("¸¸");
	vtDel.push_back("¾ï");
	vtDel.push_back("Á¶");
	vtDel.push_back("°æ");
	vector<string> vt;
	UINT uDel=uSize % 4;
	UINT uDelCnt=((uSize-1) / 4);
	UINT uDisCnt=(uDelCnt + 1);
	UINT uCutCnt=lType ;
	if((uCutCnt!=0) && (uDelCnt >= uCutCnt)){
		uDisCnt=uCutCnt;
	}
	if(uDel==0){
		sTemp=sMoney.substr(0, 4);
		sMoney.erase(0,4);
	}
	else{
		sTemp=sMoney.substr(0, uDel);
		sMoney.erase(0, uDel);
	}
	vt.push_back(sTemp);
	for(UINT i=0; i<uDelCnt; i++){
		sTemp=sMoney.substr(4*i, 4);
		char tmpString[256];
		sprintf(tmpString, "%d", atoi(sTemp.c_str()));
		vt.push_back(tmpString);
		//sTemp=::format("%d", atoi(sTemp.c_str()));
		//vt.push_back(sTemp);
	}
#ifdef _IPHONE
	sMoney=("");
#else
	sMoney=_T("");
#endif
	for(UINT j=0; j<vt.size(); j++){
		if(vt[j].compare("0")){
			vt[j]+=vtDel[uDelCnt-j];
			sMoney+=vt[j];
			uDisCnt--;
			if(uDisCnt==0) break;
		}
	}
	strpos pos=sMoney.find("¿ø");
	if(pos==NPOS){
#ifdef _IPHONE
		sMoney+=("¿ø");
#else
		sMoney+=_T("¿ø");
#endif
	}
	return (sMark + sMoney);
}
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
int GetOptionString(string sOption, string sType, int iMax)
{
	vector<string> vtParsed;
	string::size_type pos;
	pos=sOption.find_first_of('|');
	while(pos!=string::npos)
	{
		string sTemp=sOption.substr(0, pos);
		vtParsed.push_back(sTemp);
		sOption.erase(sOption.begin(), sOption.begin() + pos + 1);
		pos=sOption.find_first_of('|');
	}

	for(int i=0; i<static_cast<int>( vtParsed.size() ); i++)
	{
		if(vtParsed[i].find(sType)!=-1)
		{
			pos=vtParsed[i].find_first_of('=');
			vtParsed[i].erase(vtParsed[i].begin(), vtParsed[i].begin() + pos + 1);
			int m=atoi(vtParsed[i].c_str());
			//if(m>iMax)
			//	return 0;

			return m;
		}
	}

	return 0;
}
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
string GetOptionString(string sOption, string sType)
{
	vector<string> vtParsed;
	string::size_type pos;
	pos=sOption.find_first_of('|');
	while(pos!=string::npos)
	{
		string sTemp=sOption.substr(0, pos);
		vtParsed.push_back(sTemp);
		sOption.erase(sOption.begin(), sOption.begin() + pos + 1);
		pos=sOption.find_first_of('|');
	}

	for(int i=0; i<static_cast<int>( vtParsed.size() ); i++)
	{
		if(vtParsed[i].find(sType)!=-1)
		{
			pos=vtParsed[i].find_first_of('=');
			vtParsed[i].erase(vtParsed[i].begin(), vtParsed[i].begin() + pos + 1);
			return vtParsed[i].c_str();
		}
	}

	return "";
}
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
bool	Is_NO_IPCheck_ID( string &strid )
{
	vector<string> NoCheckIp_ID;
	// ±âÈ¹ÆÀ
	NoCheckIp_ID.push_back("crazykempf");
	NoCheckIp_ID.push_back("bluetear98");
	NoCheckIp_ID.push_back("dbsnrl");
	NoCheckIp_ID.push_back("sjg0502");
	NoCheckIp_ID.push_back("hearty30");
	// µðÀÚÀÎÆÀ
	NoCheckIp_ID.push_back("geyloo");
	NoCheckIp_ID.push_back("moonddu");
	NoCheckIp_ID.push_back("palalala");
	NoCheckIp_ID.push_back("popp76");
	NoCheckIp_ID.push_back("toy1227");
	// ÇÁ·Î´ö¼Ç2ÆÀ
	NoCheckIp_ID.push_back("penta4");
	NoCheckIp_ID.push_back("selfguy");
	NoCheckIp_ID.push_back("pil2008");
	NoCheckIp_ID.push_back("Qjdzk72");
	NoCheckIp_ID.push_back("yoha");
	NoCheckIp_ID.push_back("ackell");
	// QA
	NoCheckIp_ID.push_back("neogms_04");
	NoCheckIp_ID.push_back("neogms_05");
	NoCheckIp_ID.push_back("neogms_06");
	NoCheckIp_ID.push_back("neogms_07");
	NoCheckIp_ID.push_back("neogms_08");
	NoCheckIp_ID.push_back("neogms_09");
	NoCheckIp_ID.push_back("neogms_10");
	NoCheckIp_ID.push_back("neogms_11");
	NoCheckIp_ID.push_back("neogms_12");
	NoCheckIp_ID.push_back("neogms_15");
	NoCheckIp_ID.push_back("neogms_22");
	NoCheckIp_ID.push_back("neogms_24");
	NoCheckIp_ID.push_back("neogms_25");
	NoCheckIp_ID.push_back("neogms_27");
	NoCheckIp_ID.push_back("neogms_29");
	NoCheckIp_ID.push_back("neogms_30");
	NoCheckIp_ID.push_back("neogms_31");
	NoCheckIp_ID.push_back("neogms_33");
	NoCheckIp_ID.push_back("neogms_7581");
	NoCheckIp_ID.push_back("neogms_7582");
	NoCheckIp_ID.push_back("neogms_1623");
	NoCheckIp_ID.push_back("neogms_2094");
	// °ÔÀÓ»ç¾÷ÆÀ
	NoCheckIp_ID.push_back("merong81o");
	NoCheckIp_ID.push_back("consthink");
	NoCheckIp_ID.push_back("somante");
	// ½ÃÀåºÐ¼®ÆÀ
	NoCheckIp_ID.push_back("joohwani");
	NoCheckIp_ID.push_back("pogom");
	NoCheckIp_ID.push_back("pirause");
	NoCheckIp_ID.push_back("findit");


	for( int i=0; i< (int)NoCheckIp_ID.size(); i++ )
	{
		if( strcmp( strid.c_str(), NoCheckIp_ID[i].c_str() )==0 )
			return true;
	}
	return false;
}
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
bool IsGhostIDCheck(const string& sUID)
{
	string sMyUID;
	sMyUID.assign(sUID.c_str());
	//tolower(sMyUID.c_str());
	if (sMyUID.size()>6)
	{
		string sTemp=sMyUID.substr(0,6);

		if ( 0==sTemp.compare("pmang_"))
			return true;
		else
			return false;
	}
	else
		return false;
}

__int64 GetCurrentSystemTime()
{
	SYSTEMTIME st; 

#ifndef _IPHONE
	GetLocalTime(&st);
#endif

	__int64 lTime=(st.wYear*10000000000ll) + (st.wMonth*100000000) + (st.wDay*1000000) + (st.wHour*10000) + (st.wMinute*100) + st.wSecond;

	return lTime;
}

string GetCurrentSystemTime_s()
{
	SYSTEMTIME sys;
	memset(&sys, 0, sizeof(SYSTEMTIME));
#ifndef _IPHONE
	::GetLocalTime(&sys);
#endif
	char tmpString[256];
	sprintf(tmpString, "%d%02d%02d%02d%02d%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
	string sTemp(tmpString);
	//string sTemp=::format("%d%02d%02d%02d%02d%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);

	return sTemp;
}


bool IsDifferenceDay(__int64 lTime)
{
	__int64 lCurrentTime=GetCurrentSystemTime();
	if((lCurrentTime/1000000)>(lTime/1000000))
		return true;

	return false;
}

void ParseString(string sSource, vector<string>& vtParsed)
{
	string::size_type pos;
	pos=sSource.find_first_of('|');
	while(pos!=string::npos)
	{
		string sTemp=sSource.substr(0, pos);
		vtParsed.push_back(sTemp);
		sSource.erase(sSource.begin(), sSource.begin() + pos + 1);

		pos=sSource.find_first_of('|');
	}
}
