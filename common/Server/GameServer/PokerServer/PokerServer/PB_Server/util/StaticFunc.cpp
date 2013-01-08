#include "stdafx.h"

#ifdef WIN32
#if !defined(DEF_LINUX)
#include <windows.h>
#endif
#endif
#include <time.h>
#include "StaticFunc.h"
#include "../../Protocol Buffers/Poker/AdlGameCommon.h"

using namespace adl;

//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int Calendar_BeforeDay(int Year, int Month)
{
	if((0>=Month)||(12<Month)) return 0;
	int i=0;
	int Before=(Year-1)*365;                 //원년비 일수
	int Yun=(((Year-1)/4)-((Year-1)/100)+((Year-1)/400)); //윤년 일수
	Before=Before+Yun;
	int BeforeDay=0;
	int Months[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 
	for(i=0; i<Month-1; i++){
		BeforeDay+=Months[i];
	}
	if(Month>=2){
		BeforeDay=((true==Calendar_IsYunYear(Year))?(Before+BeforeDay+1):(Before+BeforeDay));
	}
	else{
		BeforeDay=Before+BeforeDay;
	}
	return BeforeDay;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int Calendar_DiffDay(int PrevYearMonthDay, int NextYearMonthDay)
{
	int PrevYear=PrevYearMonthDay/10000;
	int PrevMonth=(PrevYearMonthDay-PrevYear*10000)/100;
	int PrevDay=PrevYearMonthDay-PrevYear*10000-PrevMonth*100;
	int NextYear=NextYearMonthDay/10000;
	int NextMonth=(NextYearMonthDay-NextYear*10000)/100;
	int NextDay=NextYearMonthDay-NextYear*10000-NextMonth*100;
	return Calendar_DiffDay(PrevYear, PrevMonth, PrevDay, NextYear, NextMonth, NextDay);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int Calendar_DiffDay(int PrevYear, int PrevMonth, int PrevDay, int NextYear, int NextMonth, int NextDay)
{
	int BeforePrevDay=Calendar_BeforeDay(PrevYear, PrevMonth);
	BeforePrevDay+=(PrevDay-Calendar_MonthDay(PrevYear, PrevMonth));
	int BeforeNextDay=Calendar_BeforeDay(NextYear, NextMonth);
	BeforeNextDay+=(NextDay-Calendar_MonthDay(NextYear, NextMonth));
	return (BeforeNextDay-BeforePrevDay);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int Calendar_DiffMonth(int PrevYearMonth, int NextYearMonth)
{
	int PrevYear=PrevYearMonth/10000;
	int PrevMonth=(PrevYearMonth-PrevYear*10000)/100;
	int NextYear=NextYearMonth/10000;
	int NextMonth=(NextYearMonth-NextYear*10000)/100;
	return Calendar_DiffMonth(PrevYear, PrevMonth, NextYear, NextMonth);	
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int Calendar_DiffMonth(int PrevYear, int PrevMonth, int NextYear, int NextMonth)
{
	int DiffYear=NextYear-PrevYear;
	int DiffMonth=0;
	if(NextMonth>PrevMonth){
		DiffMonth=NextMonth-PrevMonth;
	}
	else{
		DiffYear--;
		DiffMonth=NextMonth+12-PrevMonth;
	}
	return DiffYear*12+DiffMonth;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool Calendar_IsYunYear(int Year)
{
	return ((0!=(Year%4))?(false):((0!=(Year%100))?(true):((0!=(Year%400))?(false):(true))));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int Calendar_MonthDay(int Year, int Month)
{
	if((0>=Month)||(12<Month)) return 0;
	int Day=0;
	int Months[]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if((2==Month)&&(true==Calendar_IsYunYear(Year))){
		Day=Months[Month-1]+1;
	}
	else{
		Day=Months[Month-1];
	}
	return Day;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int Calendar_ADayOftheWeek(int BeforeDay, int Day)
{
	int Week=(BeforeDay)%7;
	return ((Day+Week)%7);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int Calendar_Quarterly(int YearMonthDay)
{
	int Year=YearMonthDay/10000;
	int Month=(YearMonthDay-Year*10000)/100;
	int Day=YearMonthDay-Year*10000-Month*100;
	if(10<=Month){
		return 4;
	}
	if(7<=Month){
		return 3;
	}
	if(4<=Month){
		return 2;
	}
	return 1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
#define TYPE_0    0   // Linear congruential
#define BREAK_0   8
#define DEG_0     0
#define SEP_0     0

#define TYPE_1    1   // x**7 + x**3 + 1
#define BREAK_1   32
#define DEG_1     7
#define SEP_1     3

#define TYPE_2    2   // x**15 + x + 1
#define BREAK_2   64
#define DEG_2     15
#define SEP_2     1

#define TYPE_3    3   // x**31 + x**3 + 1
#define BREAK_3   128
#define DEG_3     31
#define SEP_3     3

#define TYPE_4    4   // x**63 + x + 1
#define BREAK_4   256
#define DEG_4     63
#define SEP_4     1

#define MAX_TYPES 5     // Max number of types above

#define NSHUFF 100      // To drop part of seed -> 1st value correlation

static long glDegrees[MAX_TYPES]={DEG_0, DEG_1, DEG_2, DEG_3, DEG_4};
static long glSeps[MAX_TYPES]={SEP_0, SEP_1, SEP_2, SEP_3, SEP_4};
static long glRandtbl[DEG_3+1]={
	TYPE_3,
		0x991539b1, 0x16a5bce3, 0x6774a4cd, 0x3e01511e, 0x4e508aaa, 0x61048c05,
		0xf5500617, 0x846b7115, 0x6a19892c, 0x896a97af, 0xdb48f936, 0x14898454,
		0x37ffd106, 0xb58bff9c, 0x59e17104, 0xcf918a49, 0x09378c83, 0x52c7a471,
		0x8d293ea9, 0x1f4fc301, 0xc3db71be, 0x39b44e1c, 0xf8a44ef9, 0x4c8b80b1,
		0x19edc328, 0x87bf4bdd, 0xc9b240e5, 0xe9ee4b1b, 0x4382aee7, 0x535b6b41,
		0xf3bec5da
};

static long* gplfptr=&glRandtbl[SEP_3+1];
static long* gplrptr=&glRandtbl[1];
static long* gplState=&glRandtbl[1];
static long glRand_Type=TYPE_3;
static long glRand_Deg=DEG_3;
static long glRand_Sep=SEP_3;
static long* gplEnd_ptr=&glRandtbl[DEG_3+1];
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
long Good_Rand(long lValue)
{
	long lhi=0, llo=0;
	// Can't be initialized with 0, so use another value.
	if(0==lValue) lValue=123459876;
	lhi=lValue/127773;
	llo=lValue%127773;
	lValue=16807*llo-2836*lhi;
	if(0>lValue) lValue+=0x7fffffff;
	return lValue;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
void SRand(unsigned long lValue)
{
	long i=0, lim=0;
	gplState[0]=lValue;
	if(TYPE_0==glRand_Type)
		lim=NSHUFF;
	else{
		for(i=1; i<glRand_Deg; i++){
			gplState[i]=Good_Rand(gplState[i-1]);
		}
		gplfptr=&gplState[glRand_Sep];
		gplrptr=&gplState[0];
		lim=10*glRand_Deg;
	}
	for(i=0; i<lim; i++){
		Random32();
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
long Random32(void)
{
	long i=0;
	long* f=NULL, * r=NULL;
	if(TYPE_0==glRand_Type){
		i=gplState[0];
		gplState[0]=i=(Good_Rand(i))&0x7fffffff;
	} 
	else{
		f=gplfptr;
		r=gplrptr;
		(*f)+=(*r);
		i=((*f)>>1)&0x7fffffff; // Chucking least random bit
		if((++f)>=gplEnd_ptr){
			f=gplState;
			++r;
		}
		else if((++r)>=gplEnd_ptr){
			r=gplState;
		}
		gplfptr=f;
		gplrptr=r;
	}
	return i;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
long Random32(long lMax)
{
	if(0>=lMax) return Random32();
	return Random32()%lMax;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int MakeSeedRandom(void)
{
	/*
	DWORD dwSeed=0;
	dwSeed=time(0);//::timeGetTime();
	GUID guid;
	::CoCreateGuid(&guid);
	unsigned char* p=(unsigned char*)&guid;
	for(int i=0; i<16; i++){
		unsigned char dw=p[i];
		dwSeed+=(DWORD)dw;
	}
	int j=dwSeed%257;
	for(int i=0; i<j; i++){
		rand();
	}
	return dwSeed;
	*/

	return time(0);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int PersentMakeRandomValue(int Persent, ...)
{
	vector<int> ctPersentVector;
	int IntValue=0;
	int IntMulti=0;
	va_list vl;
	va_start(vl, Persent);
	IntValue=Persent;
	while(-1!=IntValue){
		IntMulti+=IntValue;
		ctPersentVector.push_back(IntValue);
		IntValue=va_arg(vl, int);
	}
	va_end(vl);
	if(0!=(IntValue=(100-IntMulti))){
		ctPersentVector.push_back(IntValue);
	}
	MakeSeedRandom();
	int Random=(rand()%(101));
	int Total=(int)ctPersentVector.size();
	int IntPrevMulti=0;
	int IntNextMulti=0;
	for(int i=0; i<Total; i++){
		IntValue=ctPersentVector[i];
		IntPrevMulti=IntNextMulti;
		IntNextMulti=IntPrevMulti+IntValue;
		if(IntPrevMulti==IntNextMulti) continue;
		if((IntPrevMulti<=Random)&&(IntNextMulti>=Random)){
			return i;
		}
	}
	return 0;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int PersentSumMakeRandomValue(int Persent, ...)
{
	vector<int> ctPersentVector;
	int IntValue=0;
	int IntMulti=0;
	va_list vl;
	va_start(vl, Persent);
	IntValue=Persent;
	while(-1!=IntValue){
		IntMulti+=IntValue;
		ctPersentVector.push_back(IntValue);
		IntValue=va_arg(vl, int);
	}
	va_end(vl);
	SRand(time(0));//timeGetTime());
	int Random=Random32(IntMulti+1);
	int Total=(int)ctPersentVector.size();
	int IntPrevMulti=0;
	int IntNextMulti=0;
	for(int i=0; i<Total; i++){
		IntValue=ctPersentVector[i];
		IntPrevMulti=IntNextMulti;
		IntNextMulti=IntPrevMulti+IntValue;
		if(IntPrevMulti==IntNextMulti) continue;
		if((IntPrevMulti<=Random)&&(IntNextMulti>=Random)){
			return i;
		}
	}
	return 0;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
string	StringParserTable(string sSource, string sType, string sDivide, string sValue)
{
	vector<string> vtParsed;
	string::size_type pos;
	int nNext=0;
	int nPrev=0;
	string strTemp;
	int nSize=(int)sDivide.size();
	while(true){
		nNext=(int)sSource.find(sDivide, nPrev);
		if(string::npos==nNext){
			if((int)sSource.size()>nPrev){
				strTemp.assign(sSource, nPrev, sSource.size()-nPrev);
				vtParsed.push_back(strTemp);
			}
			break;
		}
		else{
			strTemp.assign(sSource, nPrev, nNext-nPrev);
			vtParsed.push_back(strTemp);
			nPrev=nNext+nSize;
		}
	}
	nSize=(int)sValue.size();
	for(int i=0; i<static_cast<int>(vtParsed.size()); i++){
		pos=vtParsed[i].find_first_of(sValue);
		string sTemp=vtParsed[i].substr(0, pos);
		if(-1!=sTemp.find(sType)){
			pos=vtParsed[i].find_first_of(sValue);
			vtParsed[i].erase(vtParsed[i].begin(), vtParsed[i].begin()+pos+nSize);
			return vtParsed[i].c_str();
		}
	}
	return "";
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int StringParserTable(vector<string>* pvtParsed, string sSource, string sDivide)
{
	if(NULL==pvtParsed) return 0;
	string::size_type pos;
	int nNext=0;
	int nPrev=0;
	string strTemp;
	int nSize=(int)sDivide.size();
	while(TRUE){
		nNext=(int)sSource.find(sDivide, nPrev);
		if(string::npos==nNext){
			if((int)sSource.size()>nPrev){
				strTemp.assign(sSource, nPrev, sSource.size()-nPrev);
				pvtParsed->push_back(strTemp);
			}
			break;
		}
		else{
			if(0<(nNext-nPrev)){
				strTemp.assign(sSource, nPrev, nNext-nPrev);
				pvtParsed->push_back(strTemp);
			}
			nPrev=nNext+nSize;
		}
	}
	return (int)pvtParsed->size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
//------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------//
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int CParser::MakeStringToTable(string sSource, string sDivide)
{
	int nNext=0;
	int nPrev=0;
	string strTemp;
	int nSize=(int)sDivide.size();
	while(TRUE){
		nNext=(int)sSource.find(sDivide, nPrev);
		if(string::npos==nNext){
			if((int)sSource.size()>nPrev){
				strTemp.assign(sSource, nPrev, sSource.size()-nPrev);
				push_back(strTemp);
			}
			break;
		}
		else{
			if(0<(nNext-nPrev)){
				strTemp.assign(sSource, nPrev, nNext-nPrev);
				push_back(strTemp);
			}
			else{
				push_back("0");
			}
			nPrev=nNext+nSize;
		}
	}
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
string CParser::MakeTableToString(string sDivide)
{
	string strSource;
	int nTotal=static_cast<int>(size());
	for(int i=0; i<nTotal; i++){
		if(i!=(nTotal-1)){
			strSource+=((*this)[i]+sDivide);
		}
		else{
			strSource+=((*this)[i]);
		}
	}
	return strSource;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
string CParser::FindStringTable(string sSource, string sType, string sDivide, string sValue)
{
	string::size_type pos;
	int nNext=0;
	int nPrev=0;
	string strTemp;
	int nSize=(int)sValue.size();
	for(int i=0; i<static_cast<int>(size()); i++){
		pos=(*this)[i].find_first_of(sValue);
		string sTemp=(*this)[i].substr(0, pos);
		if(-1!=sTemp.find(sType)){
			pos=(*this)[i].find_first_of(sValue);
			(*this)[i].erase((*this)[i].begin(), (*this)[i].begin()+pos+nSize);
			return (*this)[i].c_str();
		}
	}
	return "";
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
__int64 CParser::GetHyper(int nArray, __int64 llNonValue)
{
	if((0>nArray)||((int)size()<=nArray)) return llNonValue;
	return _atoi64((*this)[nArray].c_str());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
string CParser::GetSting(int nArray, string sNonValue)
{
	if((0>nArray)||((int)size()<=nArray)) return sNonValue;
	return (string)(*this)[nArray];
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int CParser::GetInt(int nArray, int nNonValue)
{
	if((0>nArray)||((int)size()<=nArray)) return nNonValue;
	return atoi((*this)[nArray].c_str());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
long CParser::GetLong(int nArray, long lNonValue)
{
	if((0>nArray)||((int)size()<=nArray)) return lNonValue;
	return atol((*this)[nArray].c_str());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CParser::GetBool(int nArray, bool bNonValue)
{
	if((0>nArray)||((int)size()<=nArray)) return bNonValue;
	return (bool)atol((*this)[nArray].c_str());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
void CParser::SetHyper(__int64 llValue)
{
	string strTemp=::format("%I64d", llValue);
	push_back(strTemp);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
void CParser::SetSting(string sValue)
{
	push_back(sValue);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
void CParser::SetInt(int nValue)
{
	string strTemp=::format("%d", nValue);
	push_back(strTemp);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
void CParser::SetLong(long lValue)
{
	string strTemp=::format("%d", lValue);
	push_back(strTemp);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
void CParser::Setbool(bool bValue)
{
	string strTemp=::format("%d", bValue);
	push_back(strTemp);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//


