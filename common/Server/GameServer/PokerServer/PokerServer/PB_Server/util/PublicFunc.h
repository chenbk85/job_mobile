#pragma once

//#include <vector>
#if !defined(DEF_LINUX)
#include <windows.h>
#endif

#include "StaticFunc.h"
#include "../util/CTVector.h"
#include "../util/CTVVector.h"
#include "../util/CTPairVector.h"
#include "../util/Define.h"

typedef struct tagInt3{
public:
	tagInt3(void){ ClearInt3(); }
	tagInt3(int nint1, int nint2, int nint3){ nInt1=nint1; nInt2=nint2; nInt3=nint3; }
public:
	void ClearInt3(void){ nInt1=nInt2=nInt3=0; }
	int IntSum(void){ return (nInt1+nInt2+nInt3); }
	bool IsSame1(int nint1){ return (nInt1==nint1); }
	bool IsSame2(int nint2){ return (nInt2==nint2); }
	bool IsSame3(int nint3){ return (nInt3==nint3); }
	bool IsSame12(int nint1, int nint2){ return ((nInt1==nint1)&&(nInt2==nint2)); }
	bool IsSame13(int nint1, int nint3){ return ((nInt1==nint1)&&(nInt3==nint3)); }
	bool IsSame23(int nint2, int nint3){ return ((nInt2==nint2)&&(nInt3==nint3)); }
	bool IsSame123(int nint1, int nint2, int nint3){ return ((nInt1==nint1)&&(nInt2==nint2)&&(nInt3==nint3)); }
public:
	int nInt1;
	int nInt2;
	int nInt3;
}tInt3;
//sort 관련
//------------------------------------------------------------------//
void Sort_Ascend(int Start, int End, void* pVoid, int (*Function)(void* pVoid, int nArrayNum), void (*Swap)(void* pVoid, int nSwap1, int nSwap2));
//------------------------------------------------------------------//
void Sort_Descend(int Start, int End, void* pVoid, int (*Function)(void* pVoid, int nArrayNum), void (*Swap)(void* pVoid, int nSwap1, int nSwap2));
//------------------------------------------------------------------//
void Sort_Ascend(int Start, int End, int nReserve, void* pVoid, int (*Function)(void* pVoid, int nArrayNum, int nReserve), void (*Swap)(void* pVoid, int nSwap1, int nSwap2));
//------------------------------------------------------------------//
void Sort_Descend(int Start, int End, int nReserve, void* pVoid, int (*Function)(void* pVoid, int nArrayNum, int nReserve), void (*Swap)(void* pVoid, int nSwap1, int nSwap2));
//------------------------------------------------------------------//
void Sort_Ascend(vector<int>* pvVector);
//------------------------------------------------------------------//
void Sort_Descend(vector<int>* pvVector);
//------------------------------------------------------------------//
void Sort_Ascend3(vector<tInt3>* pvVector, int nSortInt=0);
//------------------------------------------------------------------//
void Sort_Descend3(vector<tInt3>* pvVector, int nSortInt=0);
//------------------------------------------------------------------//
int GetVector(void* pvVoid, int nArray);
//------------------------------------------------------------------//
void SwapVector(void* pvVoid, int nSwap1, int nSwap2);
//------------------------------------------------------------------//
int GetVector3(void* pvVoid, int nArray, int nReserve);
//------------------------------------------------------------------//
void SwapVector3(void* pvVoid, int nSwap1, int nSwap2);
//------------------------------------------------------------------//
void SameVector_int(vector<int>* pvVector, vector<int>* pvSame, vector<int>* pvRest);
//------------------------------------------------------------------//
void SameVector_long(vector<long>* pvVector, vector<long>* pvSame, vector<long>* pvRest);
//------------------------------------------------------------------//

//영역 관련
//------------------------------------------------------------------//
void RectClear(RECT &rRect);
//------------------------------------------------------------------//
void PointClear(POINT &pPoint);
//------------------------------------------------------------------//
int RectToWidth(RECT rRect);
//------------------------------------------------------------------//
int RectToHeight(RECT rRect);
//------------------------------------------------------------------//
POINT RectToTL(RECT rRect);
//------------------------------------------------------------------//
POINT RectToBR(RECT rRect);
//------------------------------------------------------------------//
POINT RectToTR(RECT rRect);
//------------------------------------------------------------------//
POINT RectToBL(RECT rRect);
//------------------------------------------------------------------//
POINT PointXY(int x, int y);
//------------------------------------------------------------------//
RECT RectWH(int x, int y, int cx, int cy);
//------------------------------------------------------------------//
RECT RectLTRB(int left, int top, int right, int bottom);
//------------------------------------------------------------------//
RECT RectToCenter(RECT rRect, int nWidth, int nHeight);
//------------------------------------------------------------------//
RECT RectPerCenter(RECT rRect, float fPerWidth, float fPerHeight);
//------------------------------------------------------------------//
RECT CutRectTL(RECT rRect, SIZE sSize);
//------------------------------------------------------------------//
RECT CutRectBR(RECT rRect, SIZE sSize);
//------------------------------------------------------------------//
RECT CutRect(RECT rRect, SIZE sSize);
//------------------------------------------------------------------//
POINT Circle(int nRadius);
//------------------------------------------------------------------//
POINT Circle(POINT pPos, int nRadius);
//------------------------------------------------------------------//
bool InCircle(POINT pCheckPos, POINT pPos, int nRadius);
//------------------------------------------------------------------//
bool IsSamePoint(POINT pPoint1, POINT pPoint2);
//------------------------------------------------------------------//
bool IsSameRect(RECT rRect1, RECT rRect2);
//------------------------------------------------------------------//


typedef struct tagClock{
public:
	enum{
		CLOCKTYPE_NONE=0,
		CLOCKTYPE_MOVEPRESTART=1,
		CLOCKTYPE_MOVESTART=2,
		CLOCKTYPE_MOVING=4,
		CLOCKTYPE_MOVEHALF=8,
		CLOCKTYPE_MOVEHALFING=16,
		CLOCKTYPE_MOVEHALFEND=32,
		CLOCKTYPE_MOVEEND=64,
		CLOCKTYPE_DELAY=128,
		CLOCKTYPE_WAIT=256,
		CLOCKTYPE_HALFNONE=0,
		CLOCKTYPE_HALFPREV=1,
		CLOCKTYPE_HALFNEXT=2,
		CLOCKTYPE_HALF=4,
		CLOCKTYPE_HALFEND=8,
	};
public:
	tagClock(void){ ClearClock(); }
public:
	int nTotalClock;
	int nDelayClock;
	int nBaseClock;
	int nCurClock;
	int nHalfClock;
	float fRate;
	bool bMove;
public:
	void SetClock(tagClock* ptClock){
		if(NULL==ptClock) return;
		nTotalClock=ptClock->nTotalClock; nDelayClock=ptClock->nDelayClock; nBaseClock=ptClock->nBaseClock; nCurClock=ptClock->nCurClock;
		nHalfClock=ptClock->nHalfClock; fRate=ptClock->fRate; bMove=ptClock->bMove;
	}
	void SetClock(int ntotalclock, int nbaseclock=0, int nwaitclock=0, int ndelayclock=0, int nhalfclock=0){
		nTotalClock=ntotalclock; nBaseClock=nbaseclock+nwaitclock; nDelayClock=ndelayclock; nHalfClock=nhalfclock; fRate=0.0f; nCurClock=0; bMove=false; 
	}
	void ResetClock(int nbaseclock){
		if(0==nBaseClock){
			nBaseClock=nbaseclock;
		}
		else{
			if(nbaseclock>nBaseClock){
				nTotalClock=nTotalClock-(nbaseclock-nBaseClock);
				nBaseClock=nbaseclock;
			}
		}
	}
	void SetDelay(int ndelayclock){ nDelayClock=ndelayclock; }
	void SetDelayInClock(int ntotalclock){ nDelayClock=ntotalclock-nTotalClock; }
	bool IsClock(void){ return bMove; }
	bool IsClockEnd(void){
		if(false==bMove){
			if(nCurClock==nTotalClock+nDelayClock){
				return true;
			}
		}
		return false;
	}
public:
	static bool IsNone(int nReturn){ return (CLOCKTYPE_NONE==nReturn); }
	static bool IsStart(int nReturn){ return (CLOCKTYPE_MOVESTART==(CLOCKTYPE_MOVESTART&nReturn)); }
	static bool IsHalf(int nReturn){ return (CLOCKTYPE_MOVEHALF==(CLOCKTYPE_MOVEHALF&nReturn)); }
	static bool IsHalfIng(int nReturn){ return (CLOCKTYPE_MOVEHALFING==(CLOCKTYPE_MOVEHALFING&nReturn)); }
	static bool IsHalfEnd(int nReturn){ return (CLOCKTYPE_MOVEHALFEND==(CLOCKTYPE_MOVEHALFEND&nReturn)); }
	static bool IsEnd(int nReturn){ return (CLOCKTYPE_MOVEEND==(CLOCKTYPE_MOVEEND&nReturn)); }
	static bool IsIng(int nReturn){ return (CLOCKTYPE_MOVING==(CLOCKTYPE_MOVING&nReturn)); }
	static bool IsDelay(int nReturn){ return (CLOCKTYPE_DELAY==(CLOCKTYPE_DELAY&nReturn)); }
	static bool IsWait(int nReturn){ return (CLOCKTYPE_WAIT==(CLOCKTYPE_WAIT&nReturn)); }
public:
	int TotalClock(void){ return nTotalClock; }
	int DelayClock(void){ return nDelayClock; }
	int BaseClock(void){ return nBaseClock; }
	int CurClock(void){ return nCurClock; }
	float FRate(void){ return fRate; }
public:
	int EndClock(void){ return nBaseClock+(nTotalClock-nCurClock); }
	void ClearClock(void){ nTotalClock=nDelayClock=nBaseClock=nCurClock=nHalfClock=0; bMove=false; fRate=0.0f; }
	bool Play(int nbaseclock=-1, int ncurclock=0){ if(0<=nbaseclock){ nBaseClock=nbaseclock; } nCurClock=ncurclock; fRate=0.0f; bMove=((0!=nTotalClock)?(true):(false)); return bMove; }
	void Stop(void){ bMove=false; fRate=1.0f; nCurClock=nTotalClock+nDelayClock; }
	void Pause(void){ bMove=false; }
	bool IsWaiting(int nClock){ return (nBaseClock>nClock); }
	bool IsUpdateToEnd(int nClock, bool bLoop=false){
		return IsEnd(Update(nClock, bLoop));
	}
	bool IsUpdateDelayToEnd(int nClock, bool bLoop=false){
		return IsEnd(UpdateDelay(nClock, bLoop));
	}
	int Update(int nClock, bool bLoop=false){
		if(false==bMove) return CLOCKTYPE_NONE;
		if(nBaseClock>nClock) return CLOCKTYPE_WAIT;
		if(0==nBaseClock){ nBaseClock=nClock; return CLOCKTYPE_MOVEPRESTART; }
		int nReturn=CLOCKTYPE_NONE;
		if(0.0f==fRate){
			nReturn=CLOCKTYPE_MOVESTART;
		}
		int nDiffClock=nClock-nBaseClock;
		nBaseClock=nClock;
		nCurClock+=nDiffClock;
		if(0.5f>fRate){
			if((nTotalClock/2)<=nCurClock){
				nReturn=nReturn|CLOCKTYPE_MOVEHALF;
			}
		}
		if(true==bLoop){
			if((nTotalClock+nDelayClock)<=nCurClock){
				Play(nBaseClock);
				return nReturn|CLOCKTYPE_MOVEEND;
			}
		}
		else{
			if((nTotalClock+nDelayClock)<=nCurClock){
				Stop();
				return nReturn|CLOCKTYPE_MOVEEND;
			}
		}
		fRate=0.0f;
		if(0==nCurClock){ fRate=0.0f; } 
		if(0==nTotalClock){ fRate=1.0f; } 
		else if(0<=nCurClock){
			fRate=1.0f;
			if(nCurClock<=nTotalClock){
				fRate=(float)((float)(nCurClock)/(float)(nTotalClock)); 
			}
		}
		return nReturn|CLOCKTYPE_MOVING;
	}
	int UpdateDelay(int nClock, bool bLoop=false){
		if(false==bMove) return CLOCKTYPE_NONE;
		if(nBaseClock>nClock) return CLOCKTYPE_WAIT;
		if(0==nBaseClock){ nBaseClock=nClock; return CLOCKTYPE_MOVEPRESTART; }
		int nReturn=CLOCKTYPE_NONE;
		if(0.0f==fRate){
			nReturn=CLOCKTYPE_MOVESTART;
		}
		int nDiffClock=nClock-nBaseClock;
		nBaseClock=nClock;
		nCurClock+=nDiffClock;
		if(0.5f>fRate){
			if((nTotalClock/2)<=nCurClock){
				if(0!=nHalfClock){
					nHalfClock=nHalfClock+nTotalClock/2;
				}
				nReturn=nReturn|CLOCKTYPE_MOVEHALF;
			}
		}
		if(0!=nHalfClock){
			if((nTotalClock/2)<=nCurClock){
				fRate=0.5f;
				if(nCurClock<=nHalfClock){
					return nReturn|CLOCKTYPE_MOVEHALFING;
				}
				else{
					nHalfClock=nHalfClock-nTotalClock/2;
					nCurClock=nCurClock-nHalfClock;
					nHalfClock=0;
					nReturn=nReturn|CLOCKTYPE_MOVEHALFEND;
				}
			}
		}
		if(true==bLoop){
			if(nTotalClock<=nCurClock){
				if((nTotalClock+nDelayClock)>=nCurClock){
					fRate=1.0f;
					return nReturn|CLOCKTYPE_MOVEEND|CLOCKTYPE_DELAY;
				}
				else{
					Play(nBaseClock);
					return nReturn|CLOCKTYPE_MOVEEND;
				}
			}
		}
		else{
			if(nTotalClock<=nCurClock){
				if((nTotalClock+nDelayClock)>=nCurClock){
					fRate=1.0f;
					return nReturn|CLOCKTYPE_MOVEEND|CLOCKTYPE_DELAY;
				}
				else{
					Stop();
					return nReturn|CLOCKTYPE_MOVEEND;
				}
			}
		}
		fRate=0.0f;
		if(0==nCurClock){ fRate=0.0f; } 
		if(0==nTotalClock){ fRate=1.0f; } 
		else if(0<=nCurClock){
			fRate=1.0f;
			if(nCurClock<=nTotalClock){
				fRate=(float)((float)(nCurClock)/(float)(nTotalClock)); 
			}
		}
		return nReturn|CLOCKTYPE_MOVING;
	}
	float PowRate(float frate, float fPow=0.0f){
		if(0.0f==fPow) return frate;
		if(-200.0f==fPow) return sinf(D3DToRadian(90.0f*frate));
		if(-100.0f==fPow) return sqrt(sinf(D3DToRadian(90.0f*frate)));
		if(0.0f>fPow) return sinf(D3DToRadian(90.0f*powf(frate, fabs(fPow))));
		return powf(frate, fPow);
	}
	float Rate(float fPow=0.0f){
		float frate=0.0f;
		if(0==nCurClock){ fRate=0.0f; } 
		if(0==nTotalClock){ frate=1.0f; } 
		else if(0<=nCurClock){
			frate=1.0f;
			if(((nTotalClock/2)<=nCurClock)&&(nHalfClock>=nCurClock)){
				frate=0.5f;
			}
			else if(nCurClock<=nTotalClock){
				frate=(float)((float)(nCurClock)/(float)(nTotalClock));
			}
		}
		return PowRate(frate, fPow);
	}
	float DelayRate(float fPow=0.0f){
		if(0==nCurClock){ return 0.0f; } 
		if(0==nTotalClock){ return 1.0f; } 
		if(0==nDelayClock){ return 1.0f; } 
		if(nTotalClock<=nCurClock){
			if((nTotalClock+nDelayClock)>=nCurClock){
				float frate=(float)((float)(nCurClock-nTotalClock)/(float)(nDelayClock));
				return PowRate(frate, fPow);
			}
			return 1.0f;
		}
		return 0.0f;
	}
	float HalfRate(float fPow=0.0f){
		if(0==nCurClock){ return 0.0f; } 
		if(0==nTotalClock){ return 1.0f; } 
		if(0==nHalfClock){ return 1.0f; } 
		if((nTotalClock/2)<=nCurClock){
			if(nCurClock<=nHalfClock){
				float frate=(float)((float)(nCurClock-nTotalClock/2)/(float)(nHalfClock-nTotalClock/2));
				return PowRate(frate, fPow);
			}
			return 1.0f;
		}
		return 0.0f;
	}
	int HalfTypeRate(float &frate, float fPow=0.0f){
		if(nTotalClock==0){
			frate=1.0f;
			return CLOCKTYPE_HALFNONE;
		} 
		else if(0<=nCurClock){
			frate=1.0f;
			if(((nTotalClock/2)<=nCurClock)&&(nHalfClock>=nCurClock)){
				frate=0.5f;
			}
			else if(nCurClock<=nTotalClock){
				frate=(float)((float)(nCurClock)/(float)(nTotalClock));
			}
			else{
				return CLOCKTYPE_HALFEND;
			}
		}
		if(0.5f>frate){
			frate=frate/0.5f;
			frate=PowRate(frate, fPow);
			return CLOCKTYPE_HALFPREV;
		}
		else if(0.5f<frate){
			frate=(frate-0.5f)/0.5f;
			frate=PowRate(frate, fPow);
			return CLOCKTYPE_HALFNEXT;
		}
		else{
			frate=1.0f;
			frate=PowRate(frate, fPow);
			return CLOCKTYPE_HALF;
		}
		return CLOCKTYPE_HALFNONE;
	}
	float Rate2(void){
		float frate=0.0f;
		if(nTotalClock==0){
			frate=1.0f; 
		} 
		else if(0<=nCurClock){
			frate=1.0f;
			if(nCurClock<=nTotalClock){
				frate=(float)((float)(nCurClock)/(float)(nTotalClock));
			}
		}
		return sqrt(sinf(D3DToRadian(90.0f*frate)));
	}
	void ClockTimeToTime(int &nHour, int &nMinute, int &nSecond, int &nMilliseconds){
		float fFrameTime=((float)nCurClock)*0.001f;
		nHour=(((int)fFrameTime)/(60*60))%60;
		nMinute=(((int)fFrameTime)/60)%60;
		nSecond=(((int)fFrameTime))%60;
		nMilliseconds=((int)(fFrameTime*1000.0f))%1000;
	}
	void ClockTimeToTime_Remain(int &nHour, int &nMinute, int &nSecond, int &nMilliseconds){
		float fFrameTime=((float)(nTotalClock-nCurClock))*0.001f;
		nHour=(((int)fFrameTime)/(60*60))%60;
		nMinute=(((int)fFrameTime)/60)%60;
		nSecond=(((int)fFrameTime))%60;
		nMilliseconds=((int)(fFrameTime*1000.0f))%1000;
	}
	void ClockTimeFromTime(int nHour, int nMinute, int nSecond, int nMilliseconds){
		nCurClock=nBaseClock+(int)(DWORD_PTR)(((float)nHour)*60.0f*60.0f+((float)nMinute)*60.0f+((float)nSecond)+((float)nMilliseconds)/1000.0f)/0.001f;
	}
}tClock;

class CTimeToPos : public tClock
{
public:
	POINT m_pStartPos;
	POINT m_pEndPos;
	POINT m_pCurPos;
	int m_nIndex;
public:
	CTimeToPos(void):tClock(){ InitTimeToPos(); }
	virtual ~CTimeToPos(void){ FreeTimeToPos(); }
	void InitTimeToPos(void){ m_pStartPos.x=m_pStartPos.y=m_pEndPos.x=m_pEndPos.y=m_pCurPos.x=m_pCurPos.y=0; m_nIndex=0; }
	void FreeTimeToPos(void){}
public:
	void SetIndex(int nIndex){ m_nIndex=nIndex; }
	void SetTimeToPos(POINT pStartPos, POINT pEndPos, int nTotalTime, int nBaseTime=0, int nWaitTime=0){
		SetClock(nTotalTime, nBaseTime, nWaitTime);
		m_pCurPos=m_pStartPos=pStartPos; m_pEndPos=pEndPos;
	}
	void SetTimeToPos(POINT pPos, int nTotalTime, int nBaseTime=0, int nWaitTime=0){
		SetClock(nTotalTime, nBaseTime, nWaitTime);
		m_pCurPos=m_pStartPos=m_pEndPos=pPos;
	}
	void SetAreaToPos(RECT rStart, RECT rEnd, bool bRectOrCircle=false){
		MakeSeedRandom();
		if(true==bRectOrCircle){
			m_pStartPos.x=RandomRange(rStart.left, rStart.right);
			m_pStartPos.y=RandomRange(rStart.top, rStart.bottom);
			if(0==::RectToWidth(rEnd)){
				m_pEndPos=m_pStartPos;
			}
			else{
				m_pEndPos.x=RandomRange(rEnd.left, rEnd.right);
				m_pEndPos.y=RandomRange(rEnd.top, rEnd.bottom);
			}
		}
		else{
			m_pStartPos=::Circle(::RectToTL(rStart), (rStart.right-rStart.left)/2);
			if(0==::RectToWidth(rEnd)){
				m_pEndPos=m_pStartPos;
			}
			else{
				m_pEndPos=::Circle(::RectToTL(rEnd), (rEnd.right-rEnd.left)/2);
			}
		}
		m_pCurPos=m_pStartPos;
	}
	void SetPos(POINT pStartPos, POINT pEndPos){
		m_pCurPos=m_pStartPos=pStartPos; m_pEndPos=pEndPos;
	}
	void SetDistanceToTime(POINT pStartPos, POINT pEndPos, int nDistance, int nTotalTime, int nBaseTime=0, int nWaitTime=0){
		m_pCurPos=m_pStartPos=pStartPos; m_pEndPos=pEndPos;
		float fDistance=Pythagoras2(m_pEndPos.x, m_pEndPos.y, m_pStartPos.x, m_pStartPos.y);
		int nTime=0;
		if(0==nDistance){
			nTime=nTotalTime;
		}
		else{
			nTime=(int)(fDistance/(float)nDistance*(float)nTotalTime);
		}
		SetClock(nTime, nBaseTime, nWaitTime);
	}
	void PlayTimeToPos(int nbaseclock=-1, int ncurclock=0){ Play(nbaseclock, ncurclock); StartTimeToPos();  }
	void StopTimeToPos(void){ Stop(); EndTimeToPos(); }
	void PauseTimeToPos(void){ Pause(); }
	void StartTimeToPos(void){ m_pCurPos.x=m_pStartPos.x; m_pCurPos.y=m_pStartPos.y; }
	void EndTimeToPos(void){ m_pCurPos.x=m_pEndPos.x; m_pCurPos.y=m_pEndPos.y; }
	void MoveTimeToPos(float fPow=0.0f){
		m_pCurPos.x=(int)Value_Lerp(m_pStartPos.x, m_pEndPos.x, Rate(fPow));
		m_pCurPos.y=(int)Value_Lerp(m_pStartPos.y, m_pEndPos.y, Rate(fPow));
	}
	int UpdateTimeToPos(int nClock, float fPow=0.0f, bool bLoop=false){
		if(false==IsClock()) return CLOCKTYPE_NONE;
		int nReturn=Update(nClock, bLoop);
		if(true==IsStart(nReturn)){ StartTimeToPos(); }
		if(true==IsIng(nReturn)){ MoveTimeToPos(fPow); }
		if(true==IsEnd(nReturn)){ EndTimeToPos(); }
		return nReturn;
	}
};


typedef struct tagAct{
public:
	enum{
		ACT_NOIDENTY=-2,
		ACT_NOSET=-1,
		ACT_NONE=0,
		ACT_NORMAL=1,
		ACT_HIDE=2,
		ACT_SELECT=4,
		ACT_DARK=8,
		ACT_BACK=16,
		ACT_EACH=32,
		ACT_OPEN=64,
		ACT_NONNORMAL=ACT_HIDE|ACT_SELECT|ACT_DARK|ACT_BACK|ACT_EACH|ACT_OPEN,
		ACT_WAIT=128,
		ACT_START=256,
		ACT_MOVE=1024,
		ACT_HALF=2048,
		ACT_DELAY=4096,
		ACT_END=8192,
		ACT_STATE=ACT_WAIT|ACT_START|ACT_MOVE|ACT_HALF|ACT_DELAY|ACT_END,
		ACT_COVER=32768,
		ACT_ERASE=65536,
		ACT_CLICK=131072,
		ACT_OVER=262144,
		ACT_ONLY=524288,
		ACT_MULTY=1048576,
		ACT_MOUSENONE=2097152,
		ACT_MOUSE=ACT_CLICK|ACT_OVER|ACT_ONLY|ACT_MULTY|ACT_MOUSENONE,
		ACT_MOUSESELECT=ACT_MOUSE|ACT_SELECT,
		ACT_TOP=8388608,
		ACT_INSERT=16777216,
		ACT_INSERTMESSAGETOEND=33554432,
		ACT_STARTTILL=67108864,
		ACT_HALFTILL=134217728,
		ACT_ENDTILL=268435456,
		ACT_ENDCONTINUE=536870912,
		ACT_ENDMESSAGETOTYPE=1073741824,
	};
public:
	tagAct(void){ ClearAct(); }
	tagAct(int nidenty, int ntype, int nmessage){ nIdenty=nidenty; nType=ntype; nMessage=nmessage; }
public:
	bool IsActIdenty(int nidenty){ return (nIdenty==nidenty); }
	bool IsActType(int ntype){ return (nType==ntype); }
	bool IsActMessage(int nmessage){ return (nMessage==nmessage); }
	bool IsActAndType(int ntype){ return IsAndBITS(nType, ntype); }
	bool IsActAndMessage(int nmessage){ return IsAndBITS(nMessage, nmessage); }
public:
	void ClearAct(void){ nIdenty=nType=nMessage=0; }
	int GetMessageClear(void){ int nmessage=nMessage; nMessage=0; return nmessage; }
	void SetAct(tagAct* ptAct){ if(NULL==ptAct){ return; } nIdenty=ptAct->nIdenty; nType=ptAct->nType; nMessage=ptAct->nMessage; }
	void InsertActType(int ntype){ if(ACT_NOSET!=ntype){ nType=InsertBITS(nType, ntype); } }
	void RemoveActType(int ntype){ nType=RemoveBITS(nType, ntype); }
	void InsertActMessage(int nmessage){ if(ACT_NOSET!=nmessage){ nMessage=InsertBITS(nMessage, nmessage); } }
	void RemoveActMessage(int nmessage){ nMessage=RemoveBITS(nMessage, nmessage); }
public:
	void SetActIdenty(int nidenty){ if(ACT_NOIDENTY!=nidenty){ nIdenty=nidenty; } }
	void SetActType(int ntype){
		if(ACT_NOSET!=ntype){
			if(true==IsAndBITS(ntype, ACT_INSERT)){
				ntype=RemoveBITS(ntype, ACT_INSERT);
				nType=InsertBITS(nType, ntype);
			}
			else{
				nType=ntype;
			}
		}
	}
	void SetActMessage(int nmessage){
		if(ACT_NOSET!=nmessage){
			if(true==IsAndBITS(nmessage, ACT_INSERT)){
				nmessage=RemoveBITS(nmessage, ACT_INSERT);
				nMessage=InsertBITS(nMessage, nmessage);
			}
			else{
				nMessage=nmessage;
			}
		}
	}
	void SetAct(int nidenty, int ntype, int nmessage){ SetActIdenty(nidenty); SetActType(ntype); SetActMessage(nmessage); }
	void SetActNonMove(int nidenty, int ntype){ SetActIdenty(nidenty); SetActType(ntype); }
	void SetActMove(int nidenty, int ntype){ SetActIdenty(nidenty); InsertActType(ACT_MOVE|ntype); }
public:
	void ActWaitToType(void){
		nType=InsertBITS(nType, ACT_WAIT);
	}
	void ActStartToType(void){
		nType=RemoveBITS(nType, ACT_WAIT);
		nType=InsertBITS(nType, ACT_START);
		if(true==IsAndBITS(nType, ACT_STARTTILL)){
			nType=RemoveBITS(nType, ACT_STARTTILL);
		}
	}
	void ActIngToType(void){
		nType=RemoveBITS(nType, ACT_START);
	}
	void ActHalfToType(void){
		if(true==IsAndBITS(nType, ACT_HALFTILL)){
			nType=RemoveBITS(nType, ACT_NONNORMAL|ACT_HALFTILL);
		}
	}
	void ActHalfStartToType(void){
		nType=InsertBITS(nType, ACT_HALF);
	}
	void ActHalfEndToType(void){
		nType=RemoveBITS(nType, ACT_HALF);
	}
	void ActDelayToType(void){
		nType=InsertBITS(nType, ACT_DELAY);
		nType=RemoveBITS(nType, ACT_END);
	}
	void ActEndToType(void){
		if(true==IsAndBITS(nType, ACT_ENDMESSAGETOTYPE)){
			nType=RemoveBITS(nMessage, ACT_MOVE|ACT_TOP|ACT_ENDMESSAGETOTYPE);
			nMessage=ACT_NONE;
		}
		else{
			nType=RemoveBITS(nType, ACT_MOVE|ACT_TOP);
		}
		if(true==IsAndBITS(nType, ACT_ENDTILL)){
			nType=RemoveBITS(nType, ACT_NONNORMAL|ACT_ENDTILL);
		}
		else if(true==IsAndBITS(nType, ACT_HALFTILL)){
			nType=RemoveBITS(nType, ACT_NONNORMAL|ACT_HALFTILL);
		}
		nType=RemoveBITS(nType, ACT_STATE|ACT_OPEN);
		if(true==IsAndBITS(nType, ACT_ENDCONTINUE)){
			nType=RemoveBITS(nType, ACT_ENDCONTINUE);
			nType=InsertBITS(nType, ACT_END);
			nMessage=ACT_NONE;
		}
		else if(true==IsAndBITS(nType, ACT_INSERTMESSAGETOEND)){
			nType=RemoveBITS(nType, ACT_INSERTMESSAGETOEND);
			nType=InsertBITS(nType, nMessage);
			nMessage=ACT_NONE;
		}
	}
public:
	int nIdenty;
	int nType;
	int nMessage;
}tAct;

typedef struct tagStateMessage{
public:
	tagStateMessage(void){ ClearStateMessage(); }
	tagStateMessage(int narray, int nmessage){ nArray=narray; nMessage=nmessage; }
public:
	void ClearStateMessage(void){ nMessage=nArray=0; }
public:
	int nArray;
	int nMessage;
}tStateMessage;

typedef struct tagPos{
public:
	tagPos(void){ ClearPos(); }
	tagPos(POINT pstart, POINT pend){ pCur=pStart=pstart; pEnd=pend; }
	tagPos(POINT pcur, POINT pstart, POINT pend){ pCur=pcur; pStart=pstart; pEnd=pend; }
public:
	POINT LerpPos(float fRate){
		fCurRate=fRate;
		if((pMiddle.x==pEnd.x)&&(pMiddle.y==pEnd.y)){
			if(pStart.x!=pEnd.x){
				pCur.x=(int)Value_Lerp(pStart.x, pEnd.x, fCurRate);
			}
			else{
				pCur.x=pEnd.x;
			}
		}
		else{
			if(0.5f>fRate){
				fCurRate=fRate/0.5f;
				if(pStart.x!=pMiddle.x){
					pCur.x=(int)Value_Lerp(pStart.x, pMiddle.x, fCurRate);
				}
				else{
					pCur.x=pMiddle.x;
				}
			}
			else if(0.5f<fRate){
				fCurRate=(fRate-0.5f)/0.5f;
				if(pMiddle.x!=pEnd.x){
					pCur.x=(int)Value_Lerp(pMiddle.x, pEnd.x, fCurRate);
				}
				else{
					pCur.x=pEnd.x;
				}
			}
			else{
				pCur.x=pMiddle.x;
			}
		}
		if((pMiddle.x==pEnd.x)&&(pMiddle.y==pEnd.y)){
			if(pStart.y!=pEnd.y){
				pCur.y=(int)Value_Lerp(pStart.y, pEnd.y, fCurRate);
			}
			else{
				pCur.y=pEnd.y;
			}
		}
		else{
			if(0.5f>fRate){
				fCurRate=fRate/0.5f;
				if(pStart.y!=pMiddle.y){
					pCur.y=(int)Value_Lerp(pStart.y, pMiddle.y, fCurRate);
				}
				else{
					pCur.y=pMiddle.y;
				}
			}
			else if(0.5f<fRate){
				fCurRate=(fRate-0.5f)/0.5f;
				if(pMiddle.y!=pEnd.y){
					pCur.y=(int)Value_Lerp(pMiddle.y, pEnd.y, fCurRate);
				}
				else{
					pCur.y=pEnd.y;
				}
			}
			else{
				pCur.y=pMiddle.y;
			}
		}
		return pCur;
	}
	POINT StartPos(void){ pCur=pStart; fCurRate=0.0f; return pCur; }
	POINT MiddlePos(void){ pCur=pMiddle; fCurRate=0.5f; return pCur; }
	POINT EndPos(bool bAllPos=false){
		fCurRate=1.0f;
		if(true==bAllPos){ pCur=pStart=pMiddle=pEnd; }
		else{ pCur=pEnd; }
		return pCur;
	}
	bool IsMiddle(void){ return ::IsSamePoint(pEnd, pMiddle); }
	float Distance(void){
		if(false==::IsSamePoint(pEnd, pMiddle)){
			return Pythagoras2(pEnd.x, pEnd.y, pMiddle.x, pMiddle.y)+Pythagoras2(pMiddle.x, pMiddle.y, pStart.x, pStart.y);
		}
		return Pythagoras2(pEnd.x, pEnd.y, pStart.x, pStart.y);
	}
	bool PtInPos(POINT pPos, int nWidth, int nHeight){
		if(pCur.x>pPos.x) return false;
		if(pCur.y>pPos.y) return false;
		if((pCur.x+nWidth)<pPos.x) return false;
		if((pCur.y+nHeight)<pPos.y) return false;
		return true;
	}
public:
	void ClearPos(void){ pCur.x=pCur.y=0; pStart.x=pStart.y=0; pEnd.x=pEnd.y=0; pMiddle.x=pMiddle.y=0; fCurRate=0.0f; }
	void SetPos(tagPos* ptPos){
		if(NULL==ptPos) return;
		pCur=ptPos->pCur; pStart=ptPos->pStart; pEnd=ptPos->pEnd; pMiddle=ptPos->pMiddle; fCurRate=ptPos->fCurRate;
	}
	void SetCurPos(POINT pcur){ pCur=pcur; }
	void SetStartPos(POINT pstart){ pStart=pstart; }
	void SetMiddlePos(POINT pmiddle){ pMiddle=pmiddle; }
	void SetEndPos(POINT pend){ pEnd=pend; }
	void SetPos(POINT pcur){ pCur=pStart=pMiddle=pEnd=pcur; }
	void SetPos(POINT pstart, POINT pend){ pCur=pStart=pstart; pMiddle=pEnd=pend; }
	void SetPos(POINT pstart, POINT pmiddle, POINT pend){ pCur=pStart=pstart; pMiddle=pmiddle; pEnd=pend; }
	void SetRectToPos(RECT rStart, RECT rEnd, bool bRectOrCircle){
		MakeSeedRandom();
		if(true==bRectOrCircle){
			pStart.x=RandomRange(rStart.left, rStart.right);
			pStart.y=RandomRange(rStart.top, rStart.bottom);
			if(rEnd.right==rEnd.left){
				pMiddle.x=pEnd.x=pStart.x;
			}
			else{
				pMiddle.x=pEnd.x=RandomRange(rEnd.left, rEnd.right);
			}
			if(rEnd.bottom==rEnd.top){
				pMiddle.x=pEnd.y=pStart.y;
			}
			else{
				pMiddle.x=pEnd.y=RandomRange(rEnd.top, rEnd.bottom);
			}
		}
		else{
			pStart=::Circle(::RectToTL(rStart), min(::RectToWidth(rStart)/2, ::RectToHeight(rStart)/2));
			if((rEnd.right==rEnd.left)||(rEnd.bottom==rEnd.top)){
				pMiddle=pEnd=pStart;
			}
			else{
				pMiddle=pEnd=::Circle(::RectToTL(rEnd), min(::RectToWidth(rEnd)/2, ::RectToHeight(rEnd)/2));
			}
		}
		pCur=pStart;
	}
public:
	POINT pCur;
	POINT pStart;
	POINT pEnd;
	POINT pMiddle;
	float fCurRate;
}tPos;

class CActPos_Clock : public tPos, public tAct, public tClock
{
public:
	CActPos_Clock(void):tPos(),tAct(),tClock(){ InitActPos_Clock(); }
	virtual ~CActPos_Clock(void){ FreeActPos_Clock(); }
	void InitActPos_Clock(void){}
	void FreeActPos_Clock(void){ ClearPos(); ClearAct(); ClearClock(); }
public:
	void SetActPos_Clock(CActPos_Clock* pcActPos_Clock){
		SetAct(static_cast<tAct*>(pcActPos_Clock));
		SetPos(static_cast<tPos*>(pcActPos_Clock));
		SetClock(static_cast<tClock*>(pcActPos_Clock));
	}
public:
	void SetActPos_Clock(POINT pcur){ SetPos(pcur); }
	void SetActPos_Clock(int ntotalclock, int nbaseclock=0, int nwaitclock=0, int ndelayclock=0, int nhalfclock=0){
		SetClock(ntotalclock, nbaseclock, nwaitclock, ndelayclock, nhalfclock);
	}
	void SetActPos_Clock(POINT pend, int ntotalclock, int nbaseclock=0, int nwaitclock=0, int ndelayclock=0, int nhalfclock=0){
		SetPos(pCur, pend);
		SetClock(ntotalclock, nbaseclock, nwaitclock, ndelayclock, nhalfclock);
	}
	void SetActPos_Clock(POINT pstart, POINT pend, int ntotalclock, int nbaseclock=0, int nwaitclock=0, int ndelayclock=0, int nhalfclock=0){
		SetPos(pstart, pend);
		SetClock(ntotalclock, nbaseclock, nwaitclock, ndelayclock, nhalfclock);
	}
	void SetActPos_Clock(POINT pstart, POINT pmiddle, POINT pend, int ntotalclock, int nbaseclock=0, int nwaitclock=0, int ndelayclock=0, int nhalfclock=0){
		SetPos(pstart, pmiddle, pend);
		SetClock(ntotalclock, nbaseclock, nwaitclock, ndelayclock, nhalfclock);
	}
	void SetActPos_Clock_Distance(POINT pend, int ndistance, int ntotalclock, int nbaseclock=0, int nwaitclock=0, int ndelayclock=0, int nhalfclock=0){
		SetPos(pCur, pend);
		float fDistance=Distance();
		int nTime=0;
		if(0==ndistance){
			nTime=ntotalclock;
		}
		else{
			nTime=(int)(fDistance/(float)ndistance*(float)ntotalclock);
		}
		SetClock(nTime, nbaseclock, nwaitclock, ndelayclock, nhalfclock);
	}
	void SetActPos_Clock_Distance(POINT pstart, POINT pend, int ndistance, int ntotalclock, int nbaseclock=0, int nwaitclock=0, int ndelayclock=0, int nhalfclock=0){
		SetPos(pstart, pend);
		float fDistance=Distance();
		int nTime=0;
		if(0==ndistance){
			nTime=ntotalclock;
		}
		else{
			nTime=(int)(fDistance/(float)ndistance*(float)ntotalclock);
		}
		SetClock(nTime, nbaseclock, nwaitclock, ndelayclock, nhalfclock);
	}
	void SetActPos_Clock_Distance(POINT pstart, POINT pmiddle, POINT pend, int ndistance, int ntotalclock, int nbaseclock=0, int nwaitclock=0, int ndelayclock=0, int nhalfclock=0){
		SetPos(pstart, pmiddle, pend);
		float fDistance=Distance();
		int nTime=0;
		if(0==ndistance){
			nTime=ntotalclock;
		}
		else{
			nTime=(int)(fDistance/(float)ndistance*(float)ntotalclock);
		}
		SetClock(nTime, nbaseclock, nwaitclock, ndelayclock, nhalfclock);
	}
	void SetActPos_Clock(int nidenty, int ntype, int nmessage, POINT pcur){
		SetAct(nidenty, ntype, nmessage);
		SetActPos_Clock(pcur);
	}
	void SetActPos_Clock(int nidenty, int ntype, POINT pend, int ntotalclock, int nbaseclock=0, int nwaitclock=0, int ndelayclock=0, int nhalfclock=0){
		if(0!=ntotalclock){
			SetActMove(nidenty, ntype);
		}
		else{
			SetActNonMove(nidenty, ntype);
		}
		SetActPos_Clock(pend, ntotalclock, nbaseclock, nwaitclock, ndelayclock, nhalfclock);
	}
	void SetActPos_Clock(int nidenty, int ntype, int nmessage, POINT pstart, POINT pend, int ntotalclock, int nbaseclock=0, int nwaitclock=0, int ndelayclock=0, int nhalfclock=0){
		SetAct(nidenty, ntype, nmessage);
		SetActPos_Clock(pstart, pend, ntotalclock, nbaseclock, nwaitclock, ndelayclock, nhalfclock);
	}
	void SetActPos_Clock(int nidenty, int ntype, int nmessage, POINT pstart, POINT pmiddle, POINT pend, int ntotalclock, int nbaseclock=0, int nwaitclock=0, int ndelayclock=0, int nhalfclock=0){
		SetAct(nidenty, ntype, nmessage);
		SetActPos_Clock(pstart, pmiddle, pend, ntotalclock, nbaseclock, nwaitclock, ndelayclock, nhalfclock);
	}
	void SetActPos_Clock_Distance(int nidenty, int ntype, int nmessage, POINT pend, int ndistance, int ntotalclock, int nbaseclock=0, int nwaitclock=0, int ndelayclock=0, int nhalfclock=0){
		SetAct(nidenty, ntype, nmessage);
		SetActPos_Clock_Distance(pend, ndistance, ntotalclock, nbaseclock, nwaitclock, ndelayclock, nhalfclock);
	}
	void SetActPos_Clock_Distance(int nidenty, int ntype, int nmessage, POINT pstart, POINT pend, int ndistance, int ntotalclock, int nbaseclock=0, int nwaitclock=0, int ndelayclock=0, int nhalfclock=0){
		SetAct(nidenty, ntype, nmessage);
		SetActPos_Clock_Distance(pstart, pend, ndistance, ntotalclock, nbaseclock, nwaitclock, ndelayclock, nhalfclock);
	}
	void SetActPos_Clock_Distance(int nidenty, int ntype, int nmessage, POINT pstart, POINT pmiddle, POINT pend, int ndistance, int ntotalclock, int nbaseclock=0, int nwaitclock=0, int ndelayclock=0, int nhalfclock=0){
		SetAct(nidenty, ntype, nmessage);
		SetActPos_Clock_Distance(pstart, pmiddle, pend, ndistance, ntotalclock, nbaseclock, nwaitclock, ndelayclock, nhalfclock);
	}
public:
	void ChangeActPos_Clock_EndPos(POINT pEnd){
		if(true==IsClock()){
			SetMiddlePos(pEnd);
			SetEndPos(pEnd);
		}
		else{
			SetCurPos(pEnd);
			SetMiddlePos(pEnd);
			SetEndPos(pEnd);
		}
	}
public:
	void PlayActPos_Clock(int nbaseclock=-1, int ncurclock=0){
		if(true==Play(nbaseclock, ncurclock)){ StartPos(); InsertActType(tAct::ACT_MOVE); }
		else { EndPos(); ActEndToType(); }
	}
	bool ContinueActPos_Clock(int nbaseclock=0){
		if(true==IsActAndType(tAct::ACT_ENDCONTINUE)){
			EndPos(true);
			SetClock(nMessage, nbaseclock, 0, nDelayClock);
			PlayActPos_Clock();
			ActEndToType();
			return true;
		}
		return false;
	}
	void StopActPos_Clock(void){
		EndPos(true);
		Stop();
		ActEndToType();
	}
	void PauseActPos_Clock(void){ Pause(); }
	int UpdatePosFromTime(int nClock, float fPow=0.0f, bool bLoop=false){
		if(false==IsClock()) return CLOCKTYPE_NONE;
		int nReturn=UpdateDelay(nClock, bLoop);
		if(true==IsWait(nReturn)){ ActWaitToType(); }
		if(true==IsIng(nReturn)){ LerpPos(Rate(fPow)); ActIngToType(); }
		if(true==IsStart(nReturn)){ StartPos(); ActStartToType(); }
		if(true==IsHalf(nReturn)){ ActHalfToType(); LerpPos(Rate(fPow)); if(true==IsHalfIng(nReturn)){ ActHalfStartToType(); } }
		if(true==IsHalfEnd(nReturn)){ ActHalfEndToType(); }
		if(true==IsDelay(nReturn)){ ActDelayToType(); }
		if(true==IsEnd(nReturn)){ EndPos(); if(false==ContinueActPos_Clock(nClock)){ if(false==IsDelay(nReturn)){ StopActPos_Clock(); } } }
		return nReturn;
	}
	//void StopActPos_Clock(int nbaseclock=0){
	//	if(true==IsActAndType(tAct::ACT_ENDCONTINUE)){
	//		EndPos(true);
	//		SetClock(nMessage, nbaseclock, 0, 0);
	//		PlayActPos_Clock();
	//	}
	//	else{
	//		EndPos(false);
	//		Stop();
	//	}
	//	ActEndToType();
	//}
	//void PauseActPos_Clock(void){ Pause(); }
	//int UpdatePosFromTime(int nClock, float fPow=0.0f, bool bLoop=false){
	//	if(false==IsClock()) return CLOCKTYPE_NONE;
	//	int nReturn=UpdateDelay(nClock, bLoop);
	//	if(true==IsWait(nReturn)){ ActWaitToType(); }
	//	if(true==IsStart(nReturn)){ StartPos(); ActStartToType(); }
	//	if(true==IsIng(nReturn)){ LerpPos(Rate(fPow)); }
	//	if(true==IsHalf(nReturn)){ ActHalfToType(); LerpPos(Rate(fPow)); if(true==IsHalfIng(nReturn)){ ActHalfStartToType(); } }
	//	if(true==IsHalfEnd(nReturn)){ ActHalfEndToType(); }
	//	if(true==IsDelay(nReturn)){ ActDelayToType(); }
	//	if(true==IsEnd(nReturn)){ EndPos(); if(false==IsDelay(nReturn)){ StopActPos_Clock(nClock); } }
	//	return nReturn;
	//}
};

class CIDVector : public vector<pair<unsigned int, int> >
{
public:
	typedef pair<unsigned int, int> PairVector;
	vector<pair<unsigned int, int> >::iterator m_vtIterater;
public:
	CIDVector(void){ InitIDVector(); }
	virtual ~CIDVector(void){ FreeIDVector(); }
	void InitIDVector(void){}
	void FreeIDVector(void){ DelVector(); }
	bool IsEmpty(void){ return (bool)empty(); }
	int TotalVector(void){ return (int)size(); }
public:
	int AddVector(unsigned int nIdenty, int nValue);
	int FindAddVector(unsigned int nIdenty, int nValue);
	int FindVector(unsigned int nIdenty);
	bool FindDelVector(unsigned int nIdenty);
	bool DelVector(int nArray);
	void DelVector(void){ clear(); }
	bool GetVector(int nArray, int &nValue);
	bool GetVector(int nArray, unsigned int &nIdenty, int &nValue);
public:
	int CurIterater(void){ return (int)(m_vtIterater-begin()); }
	bool VectorBegin(unsigned int &nIdenty, int &nValue);
	bool VectorNext(unsigned int &nIdenty, int &nValue);
};

class CActPos_Vector : public vector<CActPos_Clock>, public tClock
{
public:
	static CIDVector m_cUpdate;
public:
	POINT m_pSelect;
	POINT m_pClick;
	POINT m_pMulty;
	POINT m_pOnly;
	POINT m_pOver;
	int m_nProcessEnd;
	bool m_bMove;
	vector<tStateMessage> m_vtReturnMessage;
	vector<tStateMessage> m_vtEndMessage;
public:
	CActPos_Vector(void):vector<CActPos_Clock>(),tClock(){ InitActPos_Vector(); }
	virtual ~CActPos_Vector(void){ FreeActPos_Vector(); }
	void InitActPos_Vector(void){ m_nProcessEnd=0; m_pOnly.x=m_pOnly.y=m_pMulty.x=m_pMulty.y=m_pSelect.x=m_pSelect.y=m_pClick.x=m_pClick.y=m_pOver.x=m_pOver.y=0; m_vtReturnMessage.clear(); m_vtEndMessage.clear(); clear(); m_bMove=false; }
	void FreeActPos_Vector(void){ m_vtReturnMessage.clear(); m_vtEndMessage.clear(); clear(); }
public:
	bool IsUsableArray(int nArray){ return ((0<=nArray)&&((int)size()>nArray)); }
	int AddActPos_Vector(CActPos_Clock** ppcActPos_Clock){
		int nArray=(int)size();
		CActPos_Clock tempCActPos_Clock;
		push_back(tempCActPos_Clock);
		(*ppcActPos_Clock)=&(*this)[nArray];
		return nArray;
	}
	bool SwapActPos_Vector(int nArray1, int nArray2){
		if(nArray1==nArray2) return true;
		if(false==IsUsableArray(nArray1)) return false;
		if(false==IsUsableArray(nArray2)) return false;
		CActPos_Clock cActPos_Clock=(*this)[nArray1];
		(*this)[nArray1]=(*this)[nArray2];
		(*this)[nArray2]=cActPos_Clock;
		return true;
	}
	bool DelActPos_Vector(int nArray){
		if(false==IsUsableArray(nArray)) return false;
		vector<CActPos_Clock>::iterator it = this->begin();
		erase(it + nArray);
		//erase(&(*this)[nArray]);
		return true;
	}
	void DelActPos_Vector(void){ clear(); }
	bool GetActPos_Vector(int nArray, CActPos_Clock** ppcActPos_Clock){
		if(false==IsUsableArray(nArray)) return false;
		(*ppcActPos_Clock)=&(*this)[nArray];
		return true;
	}
	bool GetActPos_Vector(int nArray, int &nIdenty, int &nType, POINT &pCurPos){
		if(false==IsUsableArray(nArray)) return false;
		nIdenty=(*this)[nArray].nIdenty;
		nType=(*this)[nArray].nType;
		pCurPos=(*this)[nArray].pCur;
		if(true==(*this)[nArray].IsActAndType(tAct::ACT_SELECT)){
			pCurPos.x+=m_pSelect.x;
			pCurPos.y+=m_pSelect.y;
		}
		if(true==(*this)[nArray].IsActAndType(tAct::ACT_MULTY)){
			pCurPos.x+=m_pMulty.x;
			pCurPos.y+=m_pMulty.y;
		}
		if(true==(*this)[nArray].IsActAndType(tAct::ACT_ONLY)){
			pCurPos.x+=m_pOnly.x;
			pCurPos.y+=m_pOnly.y;
		}
		if(true==(*this)[nArray].IsActAndType(tAct::ACT_CLICK)){
			pCurPos.x+=m_pClick.x;
			pCurPos.y+=m_pClick.y;
		}
		if(true==(*this)[nArray].IsActAndType(tAct::ACT_OVER)){
			pCurPos.x+=m_pOver.x;
			pCurPos.y+=m_pOver.y;
		}
		return true;
	}
	bool GetActPos_Vector(int nArray, int &nIdenty, int &nType, POINT &pCurPos, CActPos_Clock** ppcActPos_Clock){
		if(false==IsUsableArray(nArray)) return false;
		nIdenty=(*this)[nArray].nIdenty;
		nType=(*this)[nArray].nType;
		pCurPos=(*this)[nArray].pCur;
		if(true==(*this)[nArray].IsActAndType(tAct::ACT_SELECT)){
			pCurPos.x+=m_pSelect.x;
			pCurPos.y+=m_pSelect.y;
		}
		if(true==(*this)[nArray].IsActAndType(tAct::ACT_MULTY)){
			pCurPos.x+=m_pMulty.x;
			pCurPos.y+=m_pMulty.y;
		}
		if(true==(*this)[nArray].IsActAndType(tAct::ACT_ONLY)){
			pCurPos.x+=m_pOnly.x;
			pCurPos.y+=m_pOnly.y;
		}
		if(true==(*this)[nArray].IsActAndType(tAct::ACT_CLICK)){
			pCurPos.x+=m_pClick.x;
			pCurPos.y+=m_pClick.y;
		}
		if(true==(*this)[nArray].IsActAndType(tAct::ACT_OVER)){
			pCurPos.x+=m_pOver.x;
			pCurPos.y+=m_pOver.y;
		}
		(*ppcActPos_Clock)=&(*this)[nArray];
		return true;
	}
	int GetActPos_Total(void){ return (int)size(); }
	void SetActPos_Select(POINT pSelect){ m_pSelect=pSelect; }
	void SetActPos_Click(POINT pClick){ m_pClick=pClick; }
	void SetActPos_Multy(POINT pMulty){ m_pMulty=pMulty; }
	void SetActPos_Only(POINT pOnly){ m_pOnly=pOnly; }
	void SetActPos_Over(POINT pOver){ m_pOver=pOver; }
	void SetActPos_ProcessEnd(int nProcessEnd){ m_nProcessEnd=nProcessEnd; }
	void AddActPos_ProcessEnd(int nProcessEnd){ m_nProcessEnd=InsertBITS(m_nProcessEnd, nProcessEnd); }
	int GetActPos_Time(void);
public:
	static POINT GetActPos_Pos_Front(int nArray, POINT pBase, int nWidth, int nHeight, int nPosTotal){
		if(1>=nPosTotal) return pBase;
		SIZE sSize;
		sSize.cx=nWidth/(nPosTotal-1);
		sSize.cy=nHeight/(nPosTotal-1);
		POINT pPos;
		pPos.x=pBase.x+sSize.cx*nArray;
		pPos.y=pBase.y+sSize.cy*nArray;
		return pPos;
	}
	static POINT GetActPos_Pos_Back(int nArray, POINT pBase, int nWidth, int nHeight, int nPosTotal){
		if(1>=nPosTotal) return pBase;
		SIZE sSize;
		sSize.cx=nWidth/(nPosTotal-1);
		sSize.cy=nHeight/(nPosTotal-1);
		POINT pPos;
		pPos.x=pBase.x-sSize.cx*((nPosTotal-1)-nArray);
		pPos.y=pBase.y-sSize.cy*((nPosTotal-1)-nArray);
		return pPos;
	}
public:
	int AddActPos_Vector(int nIdenty, int nType, int nMessage, POINT pCur){
		CActPos_Clock* pcActPos_Clock=NULL;
		int nArray=0;
		if(-1==(nArray=AddActPos_Vector(&pcActPos_Clock))) return nArray;
		pcActPos_Clock->SetActPos_Clock(nIdenty, nType, nMessage, pCur);
		return nArray;
	}
	int AddActPos_Vector(int nIdenty, int nType, int nMessage, POINT pBase, int nWidth, int nHeight, int nPosTotal){
		CActPos_Clock* pcActPos_Clock=NULL;
		int nArray=0;
		POINT pCur;
		if(-1==(nArray=AddActPos_Vector(&pcActPos_Clock))) return nArray;
		if(0==nPosTotal){ nPosTotal=(int)size(); }
		pCur=GetActPos_Pos_Front(nArray, pBase, nWidth, nHeight, nPosTotal);
		pcActPos_Clock->SetActPos_Clock(nIdenty, nType, nMessage, pCur);
		return nArray;
	}
	int AddActPos_Vector(int nIdenty, int nType, int nMessage, POINT pStart, POINT pEnd, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0){
		CActPos_Clock* pcActPos_Clock=NULL;
		int nArray=0;
		if(-1==(nArray=AddActPos_Vector(&pcActPos_Clock))) return nArray;
		pcActPos_Clock->SetActPos_Clock(nIdenty, nType, nMessage, pStart, pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
		return nArray;
	}
	int AddActPos_Vector(int nIdenty, int nType, int nMessage, POINT pStart, POINT pMiddle, POINT pEnd, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0){
		CActPos_Clock* pcActPos_Clock=NULL;
		int nArray=0;
		if(-1==(nArray=AddActPos_Vector(&pcActPos_Clock))) return nArray;
		pcActPos_Clock->SetActPos_Clock(nIdenty, nType, nMessage, pStart, pMiddle, pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
		return nArray;
	}
	int AddActPos_Vector(int nIdenty, int nType, int nMessage, POINT pStart, POINT pBase, int nWidth, int nHeight, int nPosTotal, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0){
		CActPos_Clock* pcActPos_Clock=NULL;
		int nArray=0;
		POINT pEnd;
		if(-1==(nArray=AddActPos_Vector(&pcActPos_Clock))) return nArray;
		if(0==nPosTotal){ nPosTotal=(int)size(); }
		pEnd=GetActPos_Pos_Front(nArray, pBase, nWidth, nHeight, nPosTotal);
		pcActPos_Clock->SetActPos_Clock(nIdenty, nType, nMessage, pStart, pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
		return nArray;
	}
	int AddActPos_Vector_Distance(int nIdenty, int nType, int nMessage, POINT pStart, POINT pEnd, int nDistance, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0){
		CActPos_Clock* pcActPos_Clock=NULL;
		int nArray=0;
		if(-1==(nArray=AddActPos_Vector(&pcActPos_Clock))) return nArray;
		pcActPos_Clock->SetActPos_Clock_Distance(nIdenty, nType, nMessage, pStart, pEnd, nDistance, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
		return nArray;
	}
	int AddActPos_Vector_Distance(int nIdenty, int nType, int nMessage, POINT pStart, POINT pMiddle, POINT pEnd, int nDistance, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0){
		CActPos_Clock* pcActPos_Clock=NULL;
		int nArray=0;
		if(-1==(nArray=AddActPos_Vector(&pcActPos_Clock))) return nArray;
		pcActPos_Clock->SetActPos_Clock_Distance(nIdenty, nType, nMessage, pStart, pMiddle, pEnd, nDistance, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
		return nArray;
	}
public:
	bool ActPos_Vector_AreaToPos(POINT pBase, int nWidth, int nHeight, int nPosTotal, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_AreaToPos(RECT rArea, int nPosTotal, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_AreaToDel(int nArray, POINT pBase, int nWidth, int nHeight, int nPosTotal, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_AreaToDel(int nArray, RECT rArea, int nPosTotal, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_DiffFront(POINT pDiff, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_DiffBack(POINT pDiff, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_DiffFront(POINT pBase, int nWidth, int nHeight, int nPosTotal, POINT pDiff, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_DiffBack(POINT pBase, int nWidth, int nHeight, int nPosTotal, POINT pDiff, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_DiffPos(POINT pDiff, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_DiffPos(POINT pBase, int nWidth, int nHeight, int nPosTotal, POINT pDiff, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_DiffPosReturn(POINT pDiff, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_DiffPosReturn(POINT pBase, int nWidth, int nHeight, int nPosTotal, POINT pDiff, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_DiffPos(int nArray, POINT pDiff, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_DiffPos(int nArray, POINT pBase, int nWidth, int nHeight, int nPosTotal, POINT pDiff, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_DiffPosReturn(int nArray, POINT pDiff, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_DiffPosReturn(int nArray, POINT pBase, int nWidth, int nHeight, int nPosTotal, POINT pDiff, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_StepFront(int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_StepBack(int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_StepArray(int nArray, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_StepFront(POINT pBase, int nWidth, int nHeight, int nPosTotal, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_StepBack(POINT pBase, int nWidth, int nHeight, int nPosTotal, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_StepArray(int nArray, POINT pBase, int nWidth, int nHeight, int nPosTotal, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_ChangePos(int nArray, int nIdenty, int nType, int nMessage, POINT pPos, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_ChangePosComeAndGo(int nArray, int nIdenty, int nType, int nMessage, POINT pPos, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_MovePos(int nArray, POINT pPos, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_MovePos(int nArray, POINT pBase, int nWidth, int nHeight, int nPosTotal, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_MovePosComeAndGo(int nArray, POINT pPos, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_MoveArray(int nArray1, int nArray2, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_MoveArrayComeAndGo(int nArray1, int nArray2, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_MoveArray(vector<int> ctvArray, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_Swap(int nArray1, int nArray2, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_SwapDistance(int nArray1, int nArray2, int nDistance, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_SwapAndAreaToPos(int nArray1, int nArray2, POINT pBase, int nWidth, int nHeight, int nPosTotal, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_SwapDistanceAndAreaToPos(int nArray1, int nArray2, POINT pBase, int nWidth, int nHeight, int nPosTotal, int nDistance, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_Del(int nArray, int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0);
	bool ActPos_Vector_Select(int nArray, bool bOnly=false);
public:
	bool SetAllActPos_Pos(POINT pBase, int nWidth, int nHeight, int nPosTotal);
	bool IsAllActPos_Move(void);
	bool SetAllActPos_Identy(vector<long> cvtIdenty, int nType, int nMessage);
	bool SetAllActPos_Identy(vector<long> cvtIdenty, int nType, int nMessage, POINT pBase, int nWidth, int nHeight, int nPosTotal);
	bool IsAllActPos_Type(int nType);
	bool IsAllActPos_AndType(int nType);
	bool IsActPos_Type(int nArray, int nType);
	bool IsActPos_AndType(int nArray, int nType);
	bool SetAllActPos_Clock(int nTotalClock, int nBaseClock=0, int nWaitClock=0, int nDelayClock=0, int nHalfClock=0, int nArray1=-1, int nArray2=-1);
	bool SetAllActPos_Identy(int nIdenty, int nArray1=-1, int nArray2=-1);
	bool SetAllActPos_Type(int nType, int nArray1=-1, int nArray2=-1);
	bool SetAllActPos_InsertType(int nType, int nArray1=-1, int nArray2=-1);
	bool SetAllActPos_RemoveType(int nType, int nArray1=-1, int nArray2=-1);
	bool SetAllActPos_ChangeType(int nType, int nChangeType, int nArray1=-1, int nArray2=-1);
	bool SetAllActPos_Message(int nMessage, int nArray1=-1, int nArray2=-1);
	bool SetAllActPos_InsertMessage(int nMessage, int nArray1=-1, int nArray2=-1);
	bool SetAllActPos_RemoveMessage(int nMessage, int nArray1=-1, int nArray2=-1);
	bool SetAllActPos_ChangeMessage(int nMessage, int nChangeMessage, int nArray1=-1, int nArray2=-1);
	int FindActPos_Vector_FromIdenty(int nIdenty);
	int FindActPos_Array_FromAndType(int nType, vector<int>* pvArray, vector<int>* pvNonArray);
	int FindActPos_Identy_FromAndType(int nType, vector<long>* pvIdenty, vector<long>* pvNonIdenty);
	int FindActPos_FromAndType(int nType, vector<int>* pctvIA, vector<int>* pctvNonIA);
	int FindActPos_FromAndType(int nType, vector<long>* pvIdenty, vector<long>* pvNonIdenty, vector<int>* pvArray, vector<int>* pvNonArray);
public:
	int PtInPosDown(POINT pPos, int nWidth, int nHeight, bool bClick=false, bool bSwitch=false);
	int PtInPosUp(POINT pPos, int nWidth, int nHeight, int nSelect=0, bool bSwitch=false, bool bAllSwitch=false);
	int PtInPosUp_Type(POINT pPos, int nWidth, int nHeight, int nType, int nSelect=0, bool bSwitch=false, bool bAllSwitch=false);
	int PtInPosMove(POINT pPos, int nWidth, int nHeight);
public:
	int UpdateActPos_Vector(int nClock, float fPow=0.0f, bool bLoop=false);
};

typedef struct tagSeperator
{
public:
	enum{
		SEPERATOR_NONE=0,
		SEPERATOR_MIN=1,
		SEPERATOR_MIDDLE=2,
		SEPERATOR_MAX=3,
	};
public:
	tagSeperator(void){ nMin=nMax=0; nValue=0; }
	tagSeperator(__int64 nmin, __int64 nmax, unsigned int nvalue){
		nMin=min(nmin, nmax); nMax=max(nmin, nmax); nValue=nvalue;
	}
	tagSeperator(__int64 nmin, __int64 nmax, unsigned short int svalue1, unsigned short int svalue2){
		nMin=min(nmin, nmax); nMax=max(nmin, nmax); tSValue.sValue1=svalue1; tSValue.sValue2=svalue2;
	}
	tagSeperator(__int64 nmin, __int64 nmax, unsigned char cvalue1, unsigned char cvalue2, unsigned char cvalue3, unsigned char cvalue4){
		nMin=min(nmin, nmax); nMax=max(nmin, nmax); tCValue.cValue1=cvalue1; tCValue.cValue2=cvalue2; tCValue.cValue3=cvalue3; tCValue.cValue4=cvalue4;
	}
public:
	void SetSeperator(__int64 nmin, __int64 nmax, unsigned int nvalue){
		nMin=min(nmin, nmax); nMax=max(nmin, nmax); nValue=nvalue;
	}
	void SetSeperator(__int64 nmin, __int64 nmax, unsigned short int svalue1, unsigned short int svalue2){
		nMin=min(nmin, nmax); nMax=max(nmin, nmax); tSValue.sValue1=svalue1; tSValue.sValue2=svalue2;
	}
	void SetSeperator(__int64 nmin, __int64 nmax, unsigned char cvalue1, unsigned char cvalue2, unsigned char cvalue3, unsigned char cvalue4){
		nMin=min(nmin, nmax); nMax=max(nmin, nmax); tCValue.cValue1=cvalue1; tCValue.cValue2=cvalue2; tCValue.cValue3=cvalue3; tCValue.cValue4=cvalue4;
	}
public:
	bool InSeperator(__int64 nSeperate){ return (((nMin<=nSeperate)&&(nMax>nSeperate))?(true):(false)); }
	int OverSeperator(__int64 nSeperate){
		if(nMax==nMin) return SEPERATOR_NONE;
		if(nMax<=nSeperate) return SEPERATOR_MAX;
		if(nMin>nSeperate) return SEPERATOR_MIN;
		return SEPERATOR_MIDDLE;
	}
	int Seperator(__int64 &nSeperate){
		if(false==InSeperator(nSeperate)) return 0;
		if(1>=tCValue.cValue1){
			nSeperate=nSeperate%nMin;
			return 1;
		}
		__int64 nDiff=(nMax-nMin)/(tCValue.cValue1-1);
		__int64 nmax=0;
		__int64 nmin=0;
		for(int i=0; i<tCValue.cValue1; i++){
			nmin=nMin+nDiff*i;
			nmax=nMin+nDiff*(i+1);
			if((nmin<=nSeperate)&&(nmax>nSeperate)){
				nSeperate-=nmin;
				return i+1;
			}
		}
		return 0;
	}
	__int64 SeperatorMin_Start(__int64 &nSeperate)
	{
		bool bFindEnd=false;
		__int64 nmin=nMin;
		__int64 nmax=nMin*10;
		__int64 nTotal=0;
		__int64 nCount=1;
		do{
			while((nmin<=nSeperate)&&(nmax>nSeperate)){
				nSeperate-=nmin;
				nTotal+=nCount;
				bFindEnd=true;
				if(nMin>nSeperate){
					goto End;
				}
			}
			if(true==bFindEnd){
				nmin=nmin/10;
				nmax=nmax/10;
				nCount=nCount/10;
			}
			else{
				nmin=nmin*10;
				nmax=nmax*10;
				nCount=nCount*10;
			}
		}while(true);
End:
		return nTotal;
	}
	int SeperatorMin(__int64 &nSeperate)
	{
		int nCount=0;
		while(nMin<=nSeperate){
			nSeperate-=nMin;
			nCount++;
			if(0>=nSeperate){
				return nCount;
			}
		}
		return nCount;
	}
	int SeperatorMax(__int64 &nSeperate)
	{
		int nCount=0;
		while(nMax<=nSeperate){
			nSeperate-=nMax;
			nCount++;
			if(0>=nSeperate){
				return nCount;
			}
		}
		return nCount;
	}
public:
	__int64 nMin;
	__int64 nMax;
	union{
		unsigned int nValue;
		struct{
			unsigned short int sValue1;
			unsigned short int sValue2;
		}tSValue;
		struct{
			unsigned char cValue1;
			unsigned char cValue2;
			unsigned char cValue3;
			unsigned char cValue4;
		}tCValue;
	};
}tSeperator;


class CChipSeperator : public vector<tSeperator>
{
public:
	vector<int> m_ctSeperateHeap;
	vector<int> m_ctSeperateTable;
public:
	CChipSeperator(void):vector<tSeperator>(){ InitChipSeperator(); }
	virtual ~CChipSeperator(void){ FreeChipSeperator(); }
	void InitChipSeperator(void){}
	void FreeChipSeperator(void){ clear(); m_ctSeperateHeap.clear(); m_ctSeperateTable.clear(); }
public:
	int AddChipSeperator(__int64 nMin, __int64 nMax, unsigned int nValue){
		int nArray=(int)size();
		push_back(tSeperator(nMin, nMax, nValue));
		return nArray;
	}
	int AddChipSeperator(__int64 nMin, __int64 nMax, unsigned short int sValue1, unsigned short int sValue2){
		int nArray=(int)size();
		push_back(tSeperator(nMin, nMax, sValue1, sValue2));
		return nArray;
	}
	int AddChipSeperator(__int64 nMin, __int64 nMax, unsigned char cValue1, unsigned char cValue2, unsigned char cValue3, unsigned char cValue4){
		int nArray=(int)size();
		push_back(tSeperator(nMin, nMax, cValue1, cValue2, cValue3, cValue4));
		return nArray;
	}
	void DelChipSeperator(int nArray){
		if((0>nArray)||((int)size()<=nArray)) return;
		vector<tSeperator>::iterator it = this->begin();
		erase(it + nArray);
		//erase(&(*this)[nArray]);
	}
	void DelChipSeperator(void){ clear(); }
	void DelHeap(void){ m_ctSeperateHeap.clear(); }
	void DelTable(void){ m_ctSeperateTable.clear(); }
	int GetHeapTotal(void){ return (int)m_ctSeperateHeap.size(); }
	bool GetHeap(int nArray, tSeperator** pptSeperator){
		if((0>nArray)||((int)m_ctSeperateHeap.size()<=nArray)) return false;
		int nHeap=m_ctSeperateHeap[nArray];
		if((0>nHeap)||((int)size()<=nHeap)) return false;
		(*pptSeperator)=&(*this)[nHeap];
		return true;
	}
	int GetTableTotal(void){ return (int)m_ctSeperateTable.size(); }
	bool GetTable(int nArray, int &nCount, tSeperator** pptSeperator){
		if((0>nArray)||((int)m_ctSeperateTable.size()<=nArray)) return false;
		nCount=m_ctSeperateTable[nArray];
		if((0>nArray)||((int)size()<=nArray)) return false;
		(*pptSeperator)=&(*this)[nArray];
		return true;
	}
public:
	int ChipSeperatorHeap(__int64 nSeperate){
		if(0>=nSeperate) return 0;
		m_ctSeperateHeap.clear();
		int i=0, j=0;
		int nTotal=(int)size();
		int nCount=0;
		for(i=nTotal-1; i>=0; i--){
			nCount=(*this)[i].Seperator(nSeperate);
			for(j=0; j<nCount; j++){
				m_ctSeperateHeap.push_back(i);
			}
			if(nSeperate<=0){
				break;
			}
		}
		if(0<nSeperate){
			m_ctSeperateHeap.push_back(0);
		}
		return (int)m_ctSeperateHeap.size();
	}
	void ChipSeperatorTable(__int64 nSeperate){
		if(0>=nSeperate) return;
		int i=0;
		int nTotal=(int)size();
		m_ctSeperateTable.clear();
		m_ctSeperateTable.resize(nTotal);
		int nCount=0;
		for(i=nTotal-1; i>=0; i--){
			nCount=(*this)[i].Seperator(nSeperate);
			m_ctSeperateTable[i]=nCount;
			if(nSeperate<=0){
				break;
			}
		}
		if(0<nSeperate){
			m_ctSeperateTable[0]=1;
		}
	}
};

typedef struct tagRange{
public:
	tagRange(void){ ClearRange(); }
	tagRange(int nmin, int nmax){ nMin=nmin; nMax=nmax; }
public:
	void ClearRange(void){ nMin=nMax=0; }
	bool InRange(int nRange){ return (((nMin<=nRange)&&(nMax>=nRange))?(true):(false)); }
public:
	int nMin;
	int nMax;
}tRange;

typedef struct tagRangeIdenty : public tRange{
public:
	tagRangeIdenty(void):tRange(){ ClearRangeIdenty(); }
	tagRangeIdenty(int nidenty, int nmin, int nmax){ nIdenty=nidenty; nMin=nmin; nMax=nmax; }
public:
	void ClearRangeIdenty(void){ ClearRange(); nIdenty=0; }
public:
	int nIdenty;
}tRangeIdenty;


class CRangeTable : public vector<tRangeIdenty>
{
public:
	CRangeTable(void):vector<tRangeIdenty>(){ InitRangeTable(); }
	virtual ~CRangeTable(void){ FreeRangeTable(); }
	void InitRangeTable(void){}
	void FreeRangeTable(void){ clear(); }
public:
	int AddRangeTable(int nIdenty, int nRange){
		int nTotal=(int)size();
		int nMin=0;
		int nMax=nRange;
		if(0<nTotal){
			nMin=(*this)[nTotal-1].nMax;
			nMax+=(*this)[nTotal-1].nMax;
		}
		push_back(tRangeIdenty(nIdenty, nMin, nMax));
		return nTotal;
	}
	void DelRangeTable(int nArray){
		if((0>nArray)||((int)size()<=nArray)) return;
		vector<tRangeIdenty>::iterator it = this->begin();
		erase(it + nArray);
		//erase(&(*this)[nArray]);
	}
	void DelRangeTable(void){ clear(); }
	int GetRangeTableTotal(void){ return (int)size(); }
public:
	int GetRangeTable(int nRange){
		int nTotal=(int)size();
		for(int i=nTotal-1; i>=0; i--){
			if(true==(*this)[i].InRange(nRange)){
				return i;
			}
		}
		return -1;
	}
	int GetRangeTableIdenty(int nRange){
		int nTotal=(int)size();
		for(int i=nTotal-1; i>=0; i--){
			if(true==(*this)[i].InRange(nRange)){
				return (*this)[i].nIdenty;
			}
		}
		return -1;
	}
	int RandomRangeTable(void){
		int nTotal=(int)size();
		if(0==nTotal) return -1;
		MakeSeedRandom();
		if(0<(*this)[nTotal-1].nMax){
			return GetRangeTable(IRandom((*this)[nTotal-1].nMax));
		}
		return -1;
	}
	int RandomRangeTableIdenty(void){
		int nTotal=(int)size();
		if(0==nTotal) return -1;
		MakeSeedRandom();
		if(0<(*this)[nTotal-1].nMax){
			return GetRangeTableIdenty(IRandom((*this)[nTotal-1].nMax));
		}
		return -1;
	}
};

typedef struct tagCardArray{
public:
	tagCardArray(void){ Clear(); }
public:
	void Clear(void){ m_tCard.sCard=-1; m_tCard.sArray=-1; }
	void Empty(void){ m_tCard.sCard=-1; m_tCard.sArray=-1; }
public:
	union{
		int m_nCard;
		struct{
			short sCard;
			short sArray;
		}m_tCard;
	};
}tCardArray;

typedef struct tagResultFactor{
public:
	tagResultFactor(void){ Clear(); }
public:
	void Clear(void){ m_nResult=m_nSelect=0; m_tCardArray1=tCardArray(); m_tCardArray2=tCardArray(); }
	void Empty(void){
		m_tResult.cMade=-1; m_tResult.cAnother=-1; m_tResult.cOrder=-1; m_tResult.cReserve=-1; m_tSelect.sSelect=-1; m_tSelect.sMadeSelect=-1; 
		m_tCardArray1.Empty(); m_tCardArray2.Empty();
	}
	void Select(short sSelect, short sMadeSelect, bool bMadeSelect=false){
		m_tSelect.sSelect=sSelect;
		m_tSelect.sMadeSelect=sMadeSelect;
		if(true==bMadeSelect){
			m_tResult.cReserve=(char)m_tSelect.sMadeSelect;
		}
		else{
			m_tResult.cReserve=(char)m_tSelect.sSelect;
		}
	}
public:
	union{
		int m_nResult;
		struct{
			char cOrder;
			char cAnother;
			char cMade;
			char cReserve;
		}m_tResult;
	};
	union{
		int m_nSelect;
		struct{
			short sSelect; 
			short sMadeSelect;
		}m_tSelect;
	};
	tCardArray m_tCardArray1;
	tCardArray m_tCardArray2;
}tResultFactor;

typedef struct tagMade{
public:
	tagMade(void){ Clear(); }
	void Clear(void){ m_tCardArray1=m_tCardArray2=m_tCardArray3=tCardArray(); m_nMade=0; }
public:
	int m_nMade;
	tCardArray m_tCardArray1;
	tCardArray m_tCardArray2;
	tCardArray m_tCardArray3;
}tMade;

typedef struct tagRest{
public:
	tagRest(void){ Clear(); }
	void Clear(void){ m_tCardArray1=m_tCardArray2=tCardArray(); m_nOrder=m_nAnother=0; }
public:
	int m_nOrder;
	int m_nAnother;
	tCardArray m_tCardArray1;
	tCardArray m_tCardArray2;
}tRest;

class CResultFactor : public tResultFactor{
public:
	enum{
		MADETYPE_NONE=0,
		MADETYPE_NOANOTHER=1,
		MADETYPE_MADE=2,
	};
	enum{
		RESULT_NONE=-1,
		RESULT_NOMADE=0,
		RESULT_MADE=1,
		RESULT_NOJJOK=1,
		RESULT_NINE_FOUR=2,
		RESULT_FOOL_NINE_FOUR=3,
		RESULT_THREE_SEVEN=4,
		RESULT_FOUR_SEVEN=5,
		RESULT_JJOK=6,
		RESULT_NINE_FOUR_JJOK=7,
		RESULT_DDAND19=8,
		RESULT_THREE_SEVEN_DDANG=9,
		RESULT_FOOL_NINE_FOUR_DDANG=10,
		RESULT_DDAND10=11,
		RESULT_THREE_SEVEN_DDANG10=12,
		RESULT_GHANGDDANG138=13,
		RESULT_FOUR_SEVEN_GHANGDDANG138=14,
		RESULT_GHANGDDANG38=15,
		RESULT_ZERO=0,
		RESULT_ONE=1,
		RESULT_TWO=2,
		RESULT_THREE=3,
		RESULT_FOUR=4,
		RESULT_FIVE=5,
		RESULT_SIX=6,
		RESULT_SEVEN=7,
		RESULT_EIGHT=8,
		RESULT_NINE=9,
		RESULT_FOUR_SIX=10,
		RESULT_TEN_FOUR=11,
		RESULT_TEN_ONE=12,
		RESULT_ONE_NINE=13,
		RESULT_ONE_FOUR=14,
		RESULT_ONE_TWO=15,
		RESULT_1DDANG=16,
		RESULT_2DDANG=17,
		RESULT_3DDANG=18,
		RESULT_4DDANG=19,
		RESULT_5DDANG=20,
		RESULT_6DDANG=21,
		RESULT_7DDANG=22,
		RESULT_8DDANG=23,
		RESULT_9DDANG=24,
		RESULT_10DDANG=25,
		RESULT_13DDANG=26,
		RESULT_18DDANG=27,
		RESULT_38DDANG=28,
		RESULT_FIND=64,
	};
	enum{
		MADE_NONE=0,
		MADE_118=118,//1
		MADE_127=127,//2
		MADE_136=136,//3
		MADE_145=145,//4
		MADE_190=190,//5
		MADE_226=226,//6
		MADE_235=235,//7
		MADE_280=280,//8
		MADE_334=334,//9
		MADE_370=370,//10
		MADE_389=389,//11
		MADE_442=442,//12
		MADE_460=460,//13
		MADE_479=479,//14
		MADE_550=550,//15
		MADE_569=569,//16
		MADE_578=578,//17
		MADE_668=668,//18
		MADE_776=776,//19
		MADE_884=884,//20
		MADE_992=992,//21
		MADE_000=1000,//22
		MADENUM_NONE=0,
		MADENUM_118=1,
		MADENUM_127=2,
		MADENUM_136=3,
		MADENUM_145=4,
		MADENUM_190=5,
		MADENUM_226=6,
		MADENUM_235=7,
		MADENUM_280=8,
		MADENUM_334=9,
		MADENUM_370=10,
		MADENUM_389=11,
		MADENUM_442=12,
		MADENUM_460=13,
		MADENUM_479=14,
		MADENUM_550=15,
		MADENUM_569=16,
		MADENUM_578=17,
		MADENUM_668=18,
		MADENUM_776=19,
		MADENUM_884=20,
		MADENUM_992=21,
		MADENUM_000=22,
		MADE_TOTAL=22,
	};
public:
	CResultFactor(void):tResultFactor(){ InitResultFactor();  }
	virtual ~CResultFactor(void){ FreeResultFactor(); }
	void InitResultFactor(void){ m_nIndex=0; m_nRule=0; }
	void FreeResultFactor(void){ ClearResultFactor(); }
	void ClearResultFactor(void){ Clear(); m_vCard.clear(); m_vtMade.clear(); m_nIndex=m_nResult=0; m_tSelect.sSelect=m_tSelect.sMadeSelect=0; m_tCardArray1=tCardArray(); m_tCardArray2=tCardArray(); }
public:
	int m_nRule;
	int m_nIndex;
	vector<int> m_vCard;
	vector<tMade> m_vtMade;
public:
	bool GetMadePtr(int nArray, tMade** pptMade){
		if(false==IsUsableMadeArray(nArray)) return false;
		(*pptMade)=&m_vtMade[nArray];
		return true;
	}
	void SetRule(int nRule){ m_nRule=nRule; }
	int GetMadeCount(void){ return (int)m_vtMade.size(); }
public:
	void SetResultIndex(int nIndex){ m_nIndex=nIndex;}
	bool IsUsableArray(int nArray);
	bool IsUsableArray(int nArray1, int nArray2);
	bool IsUsableArray(int nArray1, int nArray2, int nArray3);
	bool IsUsableMadeArray(int nMadeArray);
	void AddResultCard(int nCard);
	void SetResultCard(vector<int> vCard);
	void SetResultCard(vector<long> vCard);
	void ChangeResultCard(int nArray, int nCard);
	void DelResultCard(int nArray);
	void SetResultFactor(CResultFactor* pcResultFactor);
public:
	void SetResultFactorNoMadeToSelect(int nMadeType, short sSelect, int nFindOrder=RESULT_NONE);
	void SetResultFactorNoMadeToArray(int nMadeType, int nArray1, int nArray2, int nFindOrder=RESULT_NONE);
	void SetResultFactorNoMadeToSelect(int nMadeType, short sSelect, int &nArray1, int &nArray2, int nFindOrder=RESULT_NONE);
	void SetResultFactorNoMadeToArray(int nMadeType, short &sSelect, int nArray1, int nArray2, int nFindOrder=RESULT_NONE);
	int FindResultFactorNoMade(int nMadeType, char cAnother, char cOrder, int &nArray1, int &nArray2, int nFindOrder=RESULT_NONE);
	void SetResultFactorMadeToSelect(int nMadeType, short sMadeSelect, int nFindOrder=RESULT_NONE);
	void SetResultFactorMadeToArray(int nMadeType, int nMadeArray1, int nMadeArray2, int nMadeArray3, int nFindOrder=RESULT_NONE);
	void SetResultFactorMadeToRemain(int nMadeType, int nArray1, int nArray2, int nFindOrder=RESULT_NONE);
	void SetResultFactorMadeToSelect(int nMadeType, short sMadeSelect, int &nArray1, int &nArray2, int nFindOrder=RESULT_NONE);
	void SetResultFactorMadeToArray(int nMadeType, int nMadeArray1, int nMadeArray2, int nMadeArray3, int &nArray1, int &nArray2, int nFindOrder=RESULT_NONE);
	void SetResultFactorMadeToRemain(int nMadeType, short &sMadeSelect, int nArray1, int nArray2, int nFindOrder=RESULT_NONE);
	int FindResultFactorMade(int nMadeType, char cAnother, char cOrder, short &sMadeSelect, int &nArray1, int &nArray2, int nFindOrder=RESULT_NONE);
public:
	int HighResultFactor(int nMadeType, int nFindOrder=RESULT_NONE);
	int HighResultFactor(int nMadeType, int &nArray1, int &nArray2, int nFindOrder=RESULT_NONE);
	int ResultFactor(int nMadeType, vector<tMade>* pvtMadeCard, vector<tRest>* pvtRestCard, int nFindOrder=RESULT_NONE);
	bool IsResultFactor(int nMadeType, char cOrder, int nFindOrder=RESULT_NONE);
	void MadeResultFactor(void);
	void MadeResultExceptFactor(vector<tCardArray>* pvExecptCardArray);
	short MadeResultExceptFactor(short sMadeSelect, vector<tCardArray>* pvExecptCardArray);
	short SelectToArray(short sSelect, int &nArray1, int &nArray2);
	short MadeSelectToArray(short sMadeSelect, int &nArray1, int &nArray2);
	short MadeSelectToArray(int nMadeArray1, int nMadeArray2, int nMadeArray3, int &nArray1, int &nArray2);
	short MadeSelectToMadeArray(short sMadeSelect, int &nMadeArray1, int &nMadeArray2, int &nMadeArray3);
	short ArrayToSelect(int nArray1, int nArray2);
	short ArrayToMadeSelect(int nArray1, int nArray2);
	short ArrayToMadeSelect(int nMadeArray1, int nMadeArray2, int nMadeArray3);
public:
	int GetResultFactor(int nMadeType, bool bIsDdang19, bool bIsDdang10, bool bIsGhangDdang138, bool bIsGhangDdang38, bool bIsFool94);
	char GetResultAnother(int nMadeType, bool bIsDdang19, bool bIsDdang10, bool bIsGhangDdang138, bool bIsGhangDdang38, bool bIsFool94);
	string GetResultString(int nMadeType, bool bIsDdang19, bool bIsDdang10, bool bIsGhangDdang138, bool bIsGhangDdang38, bool bIsFool94);
	bool OverResultFactor(int nMadeType, char cAnother, char cOrder);
public:
	static char GetOrder(int nMadeType, vector<long> vtCard, int nFindOrder=RESULT_NONE);
	static char GetAnother(int nMadeType, vector<long> vtCard, int nFindOrder=RESULT_NONE);
	static bool IsFindOrder(int nMadeType, vector<long> vtCard, int nFindOrder=RESULT_NONE);
	static int GetMade(vector<long> vtCard);
	static int GetMadeArray(vector<long> vtCard);
	static bool IsMade(vector<long> vtCard);
	static char GetOrder(int nMadeType, int nCard1, int nCard2, int nFindOrder=RESULT_NONE);
	static char GetAnother(int nMadeType, int nCard1, int nCard2, int nFindOrder=RESULT_NONE);
	static bool IsFindOrder(int nMadeType, int nCard1, int nCard2, int nFindOrder=RESULT_NONE);
	static int GetMade(int nCard1, int nCard2, int nCard3);
	static int GetMadeArray(int nCard1, int nCard2, int nCard3);
	static int IsAnother(char cAnother);
	static int IsAnother(int nMadeType, char cMade, char cAnother);
	static int MadeToArray(int nMade);
	static int MadeFromArray(int nMadeArray);
	static void MadeLineCol(int nMade, vector<long> vtCard, vector<int>* pvtMadePos);
	static void MadeLineCol(vector<long> vtCard, vector<int> vtMadePos[MADE_TOTAL]);
	static void MadeList(vector<int> vtCard, vector<tInt3>* pvtMade, vector<int>* pvMade, int nSortType=0);
	static void MadeList(vector<long> vtCard, vector<tInt3>* pvtMade, vector<int>* pvMade, int nSortType=0);
	static string GetString(int nMadeType, char cAnother, char cOrder);
	static string GetMadeString(int nMade);
	static string GetMadeString_Num(int nMade);
	static string GetMadeArrayString(int nMadeArray);
	static int ArrayToSelect(int nArray1, int nArray2, int nTotal);
	static void SelectToArray(int nSelect, int nTotal, int &nArray1, int &nArray2);
	static void ResultToCard(int nMadeType, char cAnother, char cOrder, int &nCard1, int &nCard2);
	static void ResultToCard(int nMadeType, char cMade, char cAnother, char cOrder, int &nMadeCard1, int &nMadeCard2, int &nMadeCard3, int &nCard1, int &nCard2);
//	static int HighRestCard(vector<tRest>* pvtRestCard, bool b94);
//	static int HighRestCard(int nMadeType, vector<tRest>* pvtRestCard, vector<long> vCard, bool b94);
	static int HighRestCard(vector<tRest>* pvtRestCard, int &nSelect94);
	static int HighRestCard(int nMadeType, vector<tRest>* pvtRestCard, vector<long> vCard, int nFindOrder=RESULT_NONE);
	static int HighRestCard94(int nMadeType, vector<tRest>* pvtRestCard, vector<long> vCard, int &nSelect94, int nFindOrder=RESULT_NONE);
	static bool SameCard(tRest* ptRest, int nCard1, int nCard2);
	static int FindMade(vector<tMade>* pvtMadeCard, int nMade);
	static int OrderAnother(vector<tRest>* pvtRestCard, char aAnother, char aOrder);
};

class CResultOrder : public vector<CResultFactor>
{
public:
	enum{
		RESULT_NONE=0,
		RESULT_ONLY=1,
		RESULT_REMATCH=2,
		RESULT_REMATCH_NOMADE=4|RESULT_REMATCH,
		RESULT_REMATCH_SAME=8|RESULT_REMATCH,
		RESULT_REMATCH_94=16|RESULT_REMATCH,
		RESULT_REMATCH_FOOL94=32|RESULT_REMATCH,
		RESULT_REMATCH_FIND=64|RESULT_REMATCH,
		RESULT_ONLY_DDANG19=128|RESULT_ONLY,
		RESULT_ONLY_DDANG10=256|RESULT_ONLY,
		RESULT_ONLY_GHANGDDANG138=512|RESULT_ONLY,
		RESULT_ONLY_GHANGDDANG38=1024|RESULT_ONLY,
	};
public:
	vector<int> m_vDDang19;
	vector<int> m_vDDang10;
	vector<int> m_vGhangDDang138;
	vector<int> m_vGhangDDang38;
	vector<int> m_vFool94;
	vector<int> m_vtResultIndex;
	vector<int> m_vtResult;
	int m_nMadeType;
	CRangeTable m_cRangeTable;
	int m_nFindOrder;
public:
	CResultOrder(void):vector<CResultFactor>(){ InitResultOrder(); }
	virtual ~CResultOrder(void){ FreeResultOrder(); }
	void InitResultOrder(void){ m_nMadeType=CResultFactor::MADETYPE_NONE; m_nFindOrder=CResultFactor::RESULT_NONE; }
	void FreeResultOrder(void){ m_nMadeType=CResultFactor::MADETYPE_NONE; m_nFindOrder=CResultFactor::RESULT_NONE; ClearResultOrder(); }
	void ClearResultOrder(void){ clear(); m_vDDang19.clear(); m_vDDang10.clear(); m_vGhangDDang138.clear(); m_vGhangDDang38.clear(); m_vtResultIndex.clear(); m_vtResult.clear(); m_vFool94.clear(); }
	bool IsUsableArray(int nArray){ return ((0<=nArray)&&(((int)size()-1)>=nArray)); }
public:
	void SetMadeType(int nMadeType=CResultFactor::MADETYPE_NONE){ m_nMadeType=nMadeType; }
	void AddFindOrder(int nFindOrder, int nRange){ m_cRangeTable.AddRangeTable(nFindOrder, nRange); }
	void DelFindOrder(int nArray){ m_cRangeTable.DelRangeTable(nArray); }
	void DelFindOrder(void){ m_cRangeTable.DelRangeTable(); }
	void MakeFindOrder(void){ m_nFindOrder=m_cRangeTable.RandomRangeTableIdenty(); }
public:
	void AddResultOrderNoMadeToSelect(int nIndex, int nCard, int nSelect=-1);
	void AddResultOrderNoMadeToArray(int nIndex, int nCard, int nArray1=-1, int nArray2=-1);
	void AddSetResultOrderNoMadeToSelect(int nIndex, vector<int> vCard, int nSelect=-1, bool bHigh=false);
	void AddSetResultOrderNoMadeToArray(int nIndex, vector<int> vCard, int nArray1=-1, int nArray2=-1, bool bHigh=false);
	void AddSetResultOrderNoMadeToSelect(int nIndex, vector<long> vCard, int nSelect=-1, bool bHigh=false);
	void AddSetResultOrderNoMadeToArray(int nIndex, vector<long> vCard, int nArray1=-1, int nArray2=-1, bool bHigh=false);
	bool FindResultOrderNoMadeToSelect(int nIndex, int nCard, int nSelect=-1);
	bool FindResultOrderNoMadeToArray(int nIndex, int nCard, int nArray1=-1, int nArray2=-1);
	bool SetResultOrderNoMadeToSelect(int nIndex, vector<int> vCard, int nSelect=-1, bool bHigh=false);
	bool SetResultOrderNoMadeToArray(int nIndex, vector<int> vCard, int nArray1=-1, int nArray2=-1, bool bHigh=false);
	bool SetResultOrderNoMadeToSelect(int nIndex, vector<long> vCard, int nSelect=-1, bool bHigh=false);
	bool SetResultOrderNoMadeToArray(int nIndex, vector<long> vCard, int nArray1=-1, int nArray2=-1, bool bHigh=false);
	bool ChangeFactorResultOrderNoMadeToSelect(int nIndex, int nSelect, int &nArray1, int &nArray2);
	bool ChangeFactorResultOrderNoMadeToArray(int nIndex, int nArray1=-1, int nArray2=-1);
	void AddResultOrderMadeToSelect(int nIndex, int nCard, int nMadeSelect=-1);
	void AddResultOrderMadeToArray(int nIndex, int nCard, int nMadeArray1=-1, int nMadeArray2=-1, int nMadeArray3=-1);
	void AddResultOrderMadeToRemain(int nIndex, int nCard, int nArray1=-1, int nArray2=-1);
	void AddSetResultOrderMadeToSelect(int nIndex, vector<int> vCard, int nMadeSelect=-1, bool bHigh=false);
	void AddSetResultOrderMadeToArray(int nIndex, vector<int> vCard, int nMadeArray1=-1, int nMadeArray2=-1, int nMadeArray3=-1, bool bHigh=false);
	void AddSetResultOrderMadeToRemain(int nIndex, vector<int> vCard, int nArray1=-1, int nArray2=-1, bool bHigh=false);
	void AddSetResultOrderMadeToSelect(int nIndex, vector<long> vCard, int nMadeSelect=-1, bool bHigh=false);
	void AddSetResultOrderMadeToArray(int nIndex, vector<long> vCard, int nMadeArray1=-1, int nMadeArray2=-1, int nMadeArray3=-1, bool bHigh=false);
	void AddSetResultOrderMadeToRemain(int nIndex, vector<long> vCard, int nArray1=-1, int nArray2=-1, bool bHigh=false);
	bool FindResultOrderMadeToSelect(int nIndex, int nCard, int nMadeSelect=-1);
	bool FindResultOrderMadeToArray(int nIndex, int nCard, int nMadeArray1=-1, int nMadeArray2=-1, int nMadeArray3=-1);
	bool FindResultOrderMadeToRemain(int nIndex, int nCard, int nArray1=-1, int nArray2=-1);
	bool SetResultOrderMadeToSelect(int nIndex, vector<int> vCard, int nMadeSelect=-1, bool bHigh=false);
	bool SetResultOrderMadeToArray(int nIndex, vector<int> vCard, int nMadeArray1=-1, int nMadeArray2=-1, int nMadeArray3=-1, bool bHigh=false);
	bool SetResultOrderMadeToRemain(int nIndex, vector<int> vCard, int nArray1=-1, int nArray2=-1, bool bHigh=false);
	bool SetResultOrderMadeToSelect(int nIndex, vector<long> vCard, int nMadeSelect=-1, bool bHigh=false);
	bool SetResultOrderMadeToArray(int nIndex, vector<long> vCard, int nMadeArray1=-1, int nMadeArray2=-1, int nMadeArray3=-1, bool bHigh=false);
	bool SetResultOrderMadeToRemain(int nIndex, vector<long> vCard, int nArray1=-1, int nArray2=-1, bool bHigh=false);
	bool ChangeFactorResultOrderMadeToSelect(int nIndex, int nMadeSelect, int &nArray1, int &nArray2);
	bool ChangeFactorResultOrderMadeToArray(int nIndex, int nMadeArray1, int nMadeArray2, int nMadeArray3, int &nArray1, int &nArray2);
	bool ChangeFactorResultOrderMadeToRemain(int nIndex, int &nMadeSelect, int nArray1=-1, int nArray2=-1);
public:
	bool ResultOrder(int nIndexTotal);
	int ResultOrderValue(int nIndexTotal);
	int ResultOrderToResult(int nIndexTotal);
	void MakeResultOrder(int nIndexTotal, char &cMade, char &cAnother, char &cOrder);
	int MaxMadeResultOrder(void);
public:
	int FindIndexToArrayResultOrder(int nIndex);
	bool FindIndexToArrayResultOrder(int nIndex, int &nArray);
	bool IsResultFactor(int nIndex, char cOrder);
	void SwapResultOrder(int nArray1, int nArray2);
	void DelResultOrder(int nIndex);
	void ClearResultOrder(int nIndex);
	void HighResultOrder(int nIndex);
	void SetResultOrder(void);
	CResultFactor* GetResultOrder(int nIndex);
	int GetResultOrder(int nIndex, CResultFactor** ppcResultFactor);
	int GetResultOrderArray(int nArray, CResultFactor** ppcResultFactor);
	string GetResultOrderString(int nIndex);
	int GetResultOrderTotal(void){ return (int)size(); }
public:
	void AddCheck(char cAnother, int nIndex);
	void DelCheck(char cAnother, int nIndex);
	void DelCheck(int nIndex);
	char FindCheck(int nIndex);
	bool FindCheck(char cAnother, int nIndex);
	void ClearCheck(void);
public:
	void Sort_Index(bool bAscOrDes=false);
	void Sort_Made(bool bAscOrDes=false);
	void Sort_Another(bool bAscOrDes=false);
	void Sort_Order(bool bAscOrDes=false);
	void Sort_MadeOrderAndAnother(bool bAscOrDes=false);
	friend void Swap(void* pVoid, int nArray1, int nArray2);
	friend int Index(void* pVoid, int nArray);
	friend int Made(void* pVoid, int nArray);
	friend int Another(void* pVoid, int nArray);
	friend int Order(void* pVoid, int nArray);
	friend int MadeOrderAndAnother(void* pVoid, int nArray);
};


typedef struct tagCard{
public:
	enum{
		CARD_JOKER=4,
		CARD_BITS_NONE=0,
		CARD_BITS_1=1,
		CARD_BITS_2=2,
		CARD_BITS_3=4,
		CARD_BITS_4=8,
		CARD_BITS_5=16,
		CARD_BITS_6=32,
		CARD_BITS_7=64,
		CARD_BITS_8=128,
		CARD_BITS_9=256,
		CARD_BITS_10=512,
		CARD_BITS_11=1024,
		CARD_BITS_12=2048,
		CARD_BITS_0_13=4096,
		CARD_BITS_S=8,
		CARD_BITS_D=4,
		CARD_BITS_H=2,
		CARD_BITS_C=1,
	};
public:
	tagCard(void){ nType=-1; nNum=-1; }
	tagCard(int ncardvalue){ nType=ncardvalue/13; nNum=ncardvalue%13; }
	tagCard(int ntype, int nnum){ nType=ntype; nNum=nnum%13; }
public:
	BOOL IsJoker(void){ return (4<=nType); }
	BOOL IsEmpty(void){ return ((-1==nType)||(-1==nNum)); }
	BOOL IsEmptyType(void){ return (-1==nType); }
	BOOL IsEmptyNum(void){ return (-1==nNum); }
	BOOL IsCard(int ncardvalue){ return (CardValue()==ncardvalue); }
	BOOL IsCard(int ntype, int nnum){ return ((ntype==nType)&&((nnum%13)==(nNum%13))); }
	void Clear(void){ nType=nNum=-1; }
	int CardValue(void){ return (13*(nType%4)+nNum); }
	int CardStateValue(void){ if(9<=nNum){ return 10; } return nNum+1; }
	int CardBits(void){
		switch(nNum){
		case 0:
		case 13:
			return CARD_BITS_0_13;
		case 1:
			return CARD_BITS_1;
		case 2:
			return CARD_BITS_2;
		case 3:
			return CARD_BITS_3;
		case 4:
			return CARD_BITS_4;
		case 5:
			return CARD_BITS_5;
		case 6:
			return CARD_BITS_6;
		case 7:
			return CARD_BITS_7;
		case 8:
			return CARD_BITS_8;
		case 9:
			return CARD_BITS_9;
		case 10:
			return CARD_BITS_10;
		case 11:
			return CARD_BITS_11;
		case 12:
			return CARD_BITS_12;
		}
		return CARD_BITS_NONE;
	}
	int CardBitsType(void){
		switch(nType){
		case 0:
			return CARD_BITS_S;
		case 1:
			return CARD_BITS_D;
		case 2:
			return CARD_BITS_H;
		case 3:
			return CARD_BITS_C;
		}
		return CARD_BITS_NONE;
	}
public:
	void SetCardValue(int ncardvalue){
		if(0>ncardvalue){ Clear(); return; }
		nType=ncardvalue/13; nNum=ncardvalue%13;
	}
	void SetCardValue(int ntype, int nnum){ nType=ntype; nNum=nnum%13; }
	void SetCardValue(tagCard* ptCard){
		if(NULL==ptCard) return;
		nType=ptCard->nType;
		nNum=ptCard->nNum;
	}
public:
	int nType;
	int nNum;
}tCard;


typedef struct tagHyperInt{
public:
	tagHyperInt(void){ Clear(); }
	tagHyperInt(unsigned __int64 llHyperInt){ m_llHyperInt=llHyperInt; }
	tagHyperInt(unsigned int nInt1, unsigned int nInt2){
		m_tInt.nInt1=nInt1; m_tInt.nInt2=nInt2;
	}
	tagHyperInt(unsigned short int sShort1, unsigned short int sShort2, unsigned short int sShort3, unsigned short int sShort4){
		m_tShort.sShort1=sShort1; m_tShort.sShort2=sShort2; m_tShort.sShort3=sShort3; m_tShort.sShort4=sShort4;
	}
	tagHyperInt(unsigned char cChar1, unsigned char cChar2, unsigned char cChar3, unsigned char cChar4, unsigned char cChar5, unsigned char cChar6, unsigned char cChar7, unsigned char cChar8){
		m_tChar.cChar1=cChar1; m_tChar.cChar2=cChar2; m_tChar.cChar3=cChar3; m_tChar.cChar4=cChar4; m_tChar.cChar5=cChar5; m_tChar.cChar6=cChar6; m_tChar.cChar7=cChar7; m_tChar.cChar8=cChar8;
	}
public:
	void Clear(void){ m_llHyperInt=0; }
public:
	union{
		unsigned __int64 m_llHyperInt;
		struct{
			unsigned int nInt1;
			unsigned int nInt2;
		}m_tInt;
		struct{
			unsigned short int sShort1;
			unsigned short int sShort2;
			unsigned short int sShort3;
			unsigned short int sShort4;
		}m_tShort;
		struct{
			unsigned char cChar1;
			unsigned char cChar2;
			unsigned char cChar3;
			unsigned char cChar4;
			unsigned char cChar5;
			unsigned char cChar6;
			unsigned char cChar7;
			unsigned char cChar8;
		}m_tChar;
	};
}tHyperInt;


class CPokerRules : public CTVVector<int>
{
public:
	typedef enum ePokerType{
		POKERTYPE_NONE=0,
		POKERTYPE_ONEPAIR=1,
		POKERTYPE_TWOPAIR=2,
		POKERTYPE_THREE=4,
		POKERTYPE_STRAIGHT=8,
		POKERTYPE_BACKSTRAIGHT=16,
		POKERTYPE_MOUNTAIN=32,
		POKERTYPE_FLUSH=64,
		POKERTYPE_FULLHOUSE=128,
		POKERTYPE_FOUR=256,
		POKERTYPE_STRAIGHTFLUSH=512,
		POKERTYPE_BACKSTRAIGHTFLUSH=1024,
		POKERTYPE_ROYALSTRAIGHTFLUSH=2048,
	}ePokerType;
public:
	tLineCol m_tLineCol_StraightFlush;
	tLineCol m_tLineCol_Straight;
	ePokerType m_ePokerType;
	CTVector<tCard> m_cvtMakeCard;
	CTVector<tCard> m_cvtRestCard;
	tHyperInt m_tHyperInt_Level;
	CTVector<tLineCol> m_ctStraightFlush;
	CTVector<tLineCol> m_ctStraight;
	CTVector<int> m_ctVector4;
	CTVector<int> m_ctVector3;
	CTVector<int> m_ctVector2;
	CTVector<long> m_ctFullCard;
public:
	CPokerRules(void):CTVVector<int>(){ InitPokerRules(); }
	virtual ~CPokerRules(void){ FreePokerRules(); }
	void InitPokerRules(void){ m_tLineCol_StraightFlush=m_tLineCol_Straight=tLineCol(-1, -1); m_ePokerType=POKERTYPE_NONE; m_tHyperInt_Level.Clear(); }
	void FreePokerRules(void){ DelVector(); }
public:
	void CreatePokerRules(void);
	void ClearPokerRules(void);
	void MakeFullCard(int nCardTotal);
	void ShuffleFullCard(void);
	bool SetPokerRulesType(ePokerType eType);
	void SetPokerRules(int nCardValue...);
	void SetPokerRules(CTVector<long>* pvIndex);
	void SetPokerRules(CTVector<tCard>* pcvtCard);
	void SetMakePokerRules(CTVector<tCard>* pcvtMakeCard, CTVector<tCard>* pcvtRestCard, int nCardValue...);
	void SetMakePokerRules(CTVector<long>* pvMakeIndex, CTVector<long>* pvRestIndex, CTVector<long>* pvIndex, int nStart=0, int nEnd=0);
	void SetMakePokerRules(CTVector<tCard>* pcvtMakeCard, CTVector<tCard>* pcvtRestCard, CTVector<tCard>* pcvtCard, int nStart=0, int nEnd=0);
	void SetEnablePokerRules(tCard* ptCard, int nCardValue...);
	void SetEnablePokerRules(long lIndex, CTVector<long>* pvIndex);
	void SetEnablePokerRules(tCard* ptCard, CTVector<tCard>* pcvtCard);
	void MakeCheck(void);
	void MakeCheck(CTVector<tCard>* pcvtMakeCard, CTVector<tCard>* pcvtRestCard);
	void MakeEnableCheck(tCard* ptCard);
	void CheckPokerRules(void);
	void CheckPokerRules(CTVector<tCard>* pcvtMakeCard);
	void CheckEnablePokerRules(tCard* ptCard);
	bool MakeLineColCard12(tLineCol* ptLineCol, CTVector<tCard>* pcvtCard, int nCount, bool bInverse=true);
	bool MakeLineColCard(tLineCol* ptLineCol, CTVector<tCard>* pcvtCard, int nCount, bool bInverse=true);
	bool MakeSameLineCard(int nLine, CTVector<tCard>* pcvtCard, int nCount);
	bool MakeSameColCard(int nCol, CTVector<tCard>* pcvtCard, int nCount);
	bool MakeMaxSameColCard(int nLine, int nOver, CTVector<tCard>* pcvtCard, int nCount);
	bool MakeFirstCard(CTVector<tCard>* pcvtCard, int nCount);
	bool MakeFirstCard(CTVector<tCard>* pcvtCard, CTVector<tCard>* pcRestCard, int nCount);
	bool FindCard(CTVector<tCard>* pcvtCard, int nType, int nNum);
	bool FindLineColCard12(tLineCol* ptLineCol, tCard* ptCard);
	bool FindLineColCard(tLineCol* ptLineCol, tCard* ptCard);
	bool FindSameLineCard(int nLine, tCard* ptCard);
	bool FindSameColCard(int nCol, tCard* ptCard);
	bool FindMaxSameColCard(int nLine, int nOver, tCard* ptCard);
	bool FindFirstSameCard(tCard* ptCard);
	bool FindFirstCard(tCard* ptCard);
	tHyperInt MakeLevel(void){ m_tHyperInt_Level=MakeLevel(m_ePokerType, &m_cvtMakeCard, &m_cvtRestCard); return m_tHyperInt_Level; }
	string MakeString(void){ return MakeString(m_ePokerType, &m_cvtMakeCard); }
public:
	static void MakeFullCard(CTVector<long>* pctFullCard, int nCardTotal);
	static void ShuffleFullCard(CTVector<long>* pctFullCard);
	static void RemoveFullCard(CTVector<long>* pcvtAllCard, CTVector<long>* pcvtCard);
	static void ConvertIndexToCard(CTVector<tCard>* pcvtCard, CTVector<long>* pctIndex);
	static void ConvertIndexFromCard(CTVector<tCard>* pcvtCard, CTVector<long>* pctIndex);
	static void ConvertVVToIndex(CTVVector<int>* pcvvtCard, CTVector<long>* pcvtIndex);
	static void ConvertVVToCard(CTVVector<int>* pcvvtCard, CTVector<tCard>* pcvtCard);
	static tHyperInt MakeLevel(ePokerType eType, CTVector<tCard>* pcvtMakeCard, CTVector<tCard>* pcvtRestCard=NULL);
	static string GetPokerRulesCardString(ePokerType eType);
	static string GetPokerRulesCardAlphaBetString(ePokerType eType);
	static string GetPokerRulesCardValueString(ePokerType eType);
	static string GetCardTypeNumString(int nCardType, int nCardNum);
	static string GetCardNumString(int nCardNum);
	static string GetCardTypeString(int nCardType);
	static string MakeString(ePokerType eType, CTVector<tCard>* pcvtMakeCard);
	static string MakeString(ePokerType eType, CTVector<tCard>* pcvtMakeCard, CTVector<tCard>* pcvtRestCard, int nCount, string cDiff=",");
public:
	static void MakePokerCardProbability(CTVector<long>* pcvtCard, CTVector<long>* pcvtExcept, CTPairVector<ePokerType, int>* pcvtProbability);
	static void MakePokerCardProbability(CTVector<tCard>* pcvtCard, CTVector<tCard>* pcvtExcept, CTPairVector<ePokerType, int>* pcvtProbability);
	static void MakePokerCard(ePokerType eType, CTVector<long>* pcvtCard, int nMakeCnt, int nValue=-1);
	static void MakePokerCard(ePokerType eType, CTVector<tCard>* pcvtCard, int nMakeCnt, int nValue=-1);
	static void MakePokerCard(CTVector<long>* pcvtAllCard, ePokerType eType, CTVector<long>* pcvtCard);
	static void MakePokerCard(CTVector<long>* pcvtAllCard, ePokerType eType, CTVector<tCard>* pcvtCard);
	static void MakePokerRestCard(CTVector<long>* pcvtAllCard, CTVector<long>* pcvtCard, int nMakeCnt);
	static void MakePokerRestCard(CTVector<long>* pcvtAllCard, CTVector<tCard>* pcvtCard, int nMakeCnt);
};


class CPosInfo
{
public:
	enum{
		InsertType_None=0,
		InsertType_DiffToLeftRight=1,
		InsertType_DiffToTopBottom=2,
		InsertType_DiffToBoth=4,
		InsertType_AreaToCutLeftRight=8,
		InsertType_AreaToCutTopBottom=16,
		InsertType_AreaToCutBoth=32,
		InsertType_AreaFillToLeftRight=64,
		InsertType_AreaFillToTopBottom=128,
		InsertType_AreaFillToBoth=256,
		InsertType_LineCol=512,
		InsertType_PointList=1024,
		InsertType_Num=12,
	};
	enum{
		PosType_None=0,
		PosType_Start=1,
		PosType_User=2,
		PosType_Pan=3,
	};
public:
	POINT m_pPos;
	POINT m_pDiff;
	RECT m_rArea;
	int m_nPosType;
	union{
		unsigned int m_nInsertType;
		struct{
			unsigned short int High;
			unsigned short int Low;
		}m_tInsertType;
	};
	vector<int> m_vLineCol;
	vector<POINT> m_vPointList;
public:
	CPosInfo(void){ InitPosInfo(); }
	virtual ~CPosInfo(void){ FreePosInfo(); }
	void InitPosInfo(void){ m_pPos.x=m_pPos.y=0; m_pDiff.x=m_pDiff.y=0; m_rArea.left=m_rArea.top=m_rArea.right=m_rArea.bottom=0; m_nPosType=PosType_None; m_nInsertType=InsertType_None; }
	void FreePosInfo(void){ ClearPosInfo(); }
	void ClearPosInfo(void){ m_pPos.x=m_pPos.y=0; m_pDiff.x=m_pDiff.y=0; m_rArea.left=m_rArea.top=m_rArea.right=m_rArea.bottom=0; m_nPosType=PosType_None; m_nInsertType=InsertType_None; m_vLineCol.clear(); }
public:
	POINT &GetPos(void){ return m_pPos; }
	POINT &GetDiff(void){ return m_pDiff; }
	RECT &GetArea(void){ return m_rArea; }
	int &GetPosType(void){ return m_nPosType; }
	unsigned int &GetInsertType(void){ return m_nInsertType; }
	unsigned short int &GetInsertTypeHigh(void){ return m_tInsertType.High; }
	unsigned short int &GetInsertTypeLow(void){ return m_tInsertType.Low; }
public:
	void SetPosInfo(POINT pPos){ m_pPos=pPos; }
	void SetPosInfo(int x, int y){ m_pPos.x=x; m_pPos.y=y; }
	void SetPosDiff(POINT pDiff){ m_pDiff=pDiff; }
	void SetPosDiff(int x, int y){ m_pDiff.x=x; m_pDiff.y=y; }
	void SetPosArea(SIZE Size){ m_rArea.left=m_pPos.x; m_rArea.top=m_pPos.y; m_rArea.right=m_pPos.x+Size.cx; m_rArea.bottom=m_pPos.y+Size.cy; }
	void SetPosArea(int cx, int cy){ m_rArea.left=m_pPos.x; m_rArea.top=m_pPos.y; m_rArea.right=m_pPos.x+cx; m_rArea.bottom=m_pPos.y+cy; }
	void SetPosType(int nPosType){ m_nPosType=nPosType; }
	void SetInsertType(unsigned short int nInsertTypeHigh, unsigned short int nInsertTypeLow=0){ m_tInsertType.High=nInsertTypeHigh; m_tInsertType.Low=nInsertTypeLow; }
	void SetPosInfo_Diff(POINT pPos, POINT pDiff){ m_pPos=pPos; m_pDiff=pDiff; }
	void SetPosInfo_Area(RECT rArea){ m_rArea=rArea; m_pPos.x=m_rArea.left; m_pPos.y=m_rArea.top; }
	void SetPosInfo_LineCol(RECT rArea, POINT pDiff, int nLineCol, ...);
public:
	int AddLineCol(int nLineCol){ int nArray=(int)m_vLineCol.size(); m_vLineCol.push_back(nLineCol); return nArray; }
	void DelLineCol(int nArray)
	{
		if((0<=nArray)&&((int)m_vLineCol.size()>nArray)) 
		{

			vector<int>::iterator it = m_vLineCol.begin();
			m_vLineCol.erase(it + nArray); 
			//m_vLineCol.erase(&m_vLineCol[nArray]); 
		}
	}
	void DelLineCol(void){ m_vLineCol.clear(); }
	int TotalLineCol(void){ return (int)m_vLineCol.size(); }
	bool GetLineCol(int nArray, int &nLineCol){ if((0<=nArray)&&((int)m_vLineCol.size()>nArray)){ nLineCol=m_vLineCol[nArray]; return true; } return false; }
	int AddPointList(POINT pPos){ int nArray=(int)m_vPointList.size(); m_vPointList.push_back(pPos); return nArray; }
	void DelPointList(int nArray)
	{ 
		if((0<=nArray)&&((int)m_vPointList.size()>nArray)) 
		{
			vector<POINT>::iterator it = m_vPointList.begin();
			m_vPointList.erase(it + nArray);
			//m_vPointList.erase(&m_vPointList[nArray]); 
		}
	}
	void DelPointList(void){ m_vPointList.clear(); }
	int TotalPointList(void){ return (int)m_vPointList.size(); }
	bool GetPointList(int nArray, POINT &pPos){ if((0<=nArray)&&((int)m_vPointList.size()>nArray)){ pPos=m_vPointList[nArray]; return true; } return false; }
public:
	int StringToInsertType(string str);
	string InsertTypeToString(int InsertType);
public:
	POINT FindPos(int nArray, int nPosCount, int nTotal, SIZE Size, bool bFindLow=true);
	POINT FindPos(int nArray, int nPosCount, int nTotal, int cx, int cy, bool bFindLow=true);
	POINT FindPos(int nArray, int nPosCount, int nTotal, bool bFindLow=true);
	POINT FindPos_DiffToLeftRight(POINT pPos, int nArray);
	POINT FindPos_DiffToTopBottom(POINT pPos, int nArray);
	POINT FindPos_DiffToBoth(POINT pPos, int nArray);
	POINT FindPos_AreaToCutLeftRight(POINT pPos, int nArray, int nTotal, SIZE Size);
	POINT FindPos_AreaToCutTopBottom(POINT pPos, int nArray, int nTotal, SIZE Size);
	POINT FindPos_AreaToCutBoth(POINT pPos, int nArray, int nTotal, SIZE Size);
	POINT FindPos_AreaToCutLeftRight(POINT pPos, int nArray, int nTotal, int cx, int cy);
	POINT FindPos_AreaToCutTopBottom(POINT pPos, int nArray, int nTotal, int cx, int cy);
	POINT FindPos_AreaToCutBoth(POINT pPos, int nArray, int nTotal, int cx, int cy);
	POINT FindPos_AreaToCutLeftRight(POINT pPos, int nArray, int nTotal);
	POINT FindPos_AreaToCutTopBottom(POINT pPos, int nArray, int nTotal);
	POINT FindPos_AreaToCutBoth(POINT pPos, int nArray, int nTotal);
	POINT FindPos_AreaFillToLeftRight(POINT pPos, int nArray, int nTotal, SIZE Size);
	POINT FindPos_AreaFillToTopBottom(POINT pPos, int nArray, int nTotal, SIZE Size);
	POINT FindPos_AreaFillToBoth(POINT pPos, int nArray, int nTotal, SIZE Size);
	POINT FindPos_AreaFillToLeftRight(POINT pPos, int nArray, int nTotal, int cx, int cy);
	POINT FindPos_AreaFillToTopBottom(POINT pPos, int nArray, int nTotal, int cx, int cy);
	POINT FindPos_AreaFillToBoth(POINT pPos, int nArray, int nTotal, int cx, int cy);
	POINT FindPos_AreaFillToLeftRight(POINT pPos, int nArray, int nTotal);
	POINT FindPos_AreaFillToTopBottom(POINT pPos, int nArray, int nTotal);
	POINT FindPos_AreaFillToBoth(POINT pPos, int nArray, int nTotal);
	POINT FindPos_LineCol(POINT pPos, int nArray);
	POINT FindPos_PointList(POINT pPos, int nArray);
};


class CLineCol{
public:
	enum{
		LINE_1=0,
		LINE_2=1,
		LINE_3=2,
		COL_1=1,
		COL_2=5,
		COL_3=10,
		COL_MOL=25,
		COL_TOTAL=3,		
	};
	long m_lLine;
	long m_lCol;
public:
	CLineCol(void){ Clear(); }
	virtual ~CLineCol(void){}
public:
	void Clear(){
		m_lLine=0;
		m_lCol=0;
	}
	void SetLineMoney(long lLine, long lCol){
		m_lLine=lLine; m_lCol=lCol;
	}
	bool IsLine(long lLine){
		return (((LINE_1<=lLine)||(LINE_3>=lLine))?(true):(false));
	}
	bool IsCol(long lCol){
		return (((COL_1==lCol)||(COL_2==lCol)||(COL_3==lCol)||(COL_MOL==lCol))?(true):(false));
	}
};

class CBetLog : CTPairVector<int, string>
{
public:
	enum{
		BET_STRING=12,
	};
public:
	CBetLog(void){ InitBetLog(); }
	virtual ~CBetLog(void){ FreeBetLog(); }
	void InitBetLog(void){}
	void FreeBetLog(void){ DelVector(); }
public:
	int AddBetLog(int nIdenty){
		string str;
		str.clear();
		str.resize(BET_STRING, '-');
		return FindBeginAddVector(nIdenty, str);
	}
	bool DelBetLog(int nIdenty){ return (-1!=FindBeginDelVector(nIdenty)); }
	void DelBetLog(void){ DelVector(); }
	bool GetBetLog(int nIdenty, string &str){ return (-1!=FindBeginVector(nIdenty, str)); }
	bool SetBetLog(int nIdenty, string str){ return (-1!=FindBeginAddVector(nIdenty, str)); }
public:
	bool SetBetLogReceive(int nBetIdenty, int nIdenty, int nBetTurn=0, int nBet=0, vector<CLineCol>* pvtSelectLine=NULL);
	char GetBetChar(int nBet);
	char GetBetOrder(int nPos);
};