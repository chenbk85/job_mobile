#pragma once

#include <string>
#include <vector>

using namespace std;

#ifndef IsInRange
#define IsInRange(v,n,m)         (((n)<=(v))&&((v)<=(m))) //?(true):(false))
#endif
#ifndef IsAndBITS
#define IsAndBITS(t,u)          ((u)==((t)&(u))) //?(true):(false))
#endif
#ifndef InsertBITS
#define InsertBITS(t,u)         ((t)|(u))
#endif
#ifndef RemoveBITS
#define RemoveBITS(t,u)         ((t)^((t)&(u)))
#endif


//달력
//------------------------------------------------------------------//
int Calendar_BeforeDay(int Year, int Month);
//------------------------------------------------------------------//
int Calendar_DiffDay(int PrevYearMonthDay, int NextYearMonthDay);
//------------------------------------------------------------------//
int Calendar_DiffDay(int PrevYear, int PrevMonth, int PrevDay, int NextYear, int NextMonth, int NextDay);
//------------------------------------------------------------------//
int Calendar_DiffMonth(int PrevYearMonth, int NextYearMonth);
//------------------------------------------------------------------//
int Calendar_DiffMonth(int PrevYear, int PrevMonth, int NextYear, int NextMonth);
//------------------------------------------------------------------//
bool Calendar_IsYunYear(int Year);
//------------------------------------------------------------------//
int Calendar_MonthDay(int Year, int Month);
//------------------------------------------------------------------//
int Calendar_ADayOftheWeek(int BeforeDay, int Day);
//------------------------------------------------------------------//
int Calendar_Quarterly(int YearMonthDay);
//------------------------------------------------------------------//


//random 관련
//------------------------------------------------------------------//
long Good_Rand(long lValue);
//------------------------------------------------------------------//
void SRand(unsigned long lValue);
//------------------------------------------------------------------//
long Random32(void);
//------------------------------------------------------------------//
long Random32(long lMax);
//------------------------------------------------------------------//
int MakeSeedRandom(void);
//------------------------------------------------------------------//
int PersentMakeRandomValue(int Persent, ...);
//------------------------------------------------------------------//
int PersentSumMakeRandomValue(int Persent, ...);
//------------------------------------------------------------------//
string StringParserTable(string sSource, string sType, string sDivide, string sValue);
//------------------------------------------------------------------//
int StringParserTable(vector<string>* pvtParsed, string sSource, string sDivide);



class CParser : public vector<string>
{
public:
	CParser(void){ InitParser(); }
	virtual ~CParser(void){ FreeParser(); }
	void InitParser(void){ clear(); }
	void FreeParser(void){ clear(); }
public:
	int MakeStringToTable(string sSource, string sDivide);
	string MakeTableToString(string sDivide);
	string FindStringTable(string sSource, string sType, string sDivide, string sValue);
public:
	__int64 GetHyper(int nArray, __int64 llNonValue=0);
	string GetSting(int nArray, string sNonValue="-");
	int GetInt(int nArray, int nNonValue=0);
	long GetLong(int nArray, long lNonValue=0);
	bool GetBool(int nArray, bool bNonValue=false);
public:
	void SetHyper(__int64 llValue=0);
	void SetSting(string sValue="-");
	void SetInt(int nValue=0);
	void SetLong(long lValue=0);
	void Setbool(bool bValue=false);
};