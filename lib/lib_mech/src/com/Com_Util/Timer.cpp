//////////////////////////////////////////////////////////////////////
//
//	jctek jcENGINE Source code
//	
//	File:Timer.cpp
//  Description: Implementation of the timer class: timing functions
//
//	History:
//	-Jan 31,2001:Created by Marco Corbetta
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Timer.h"
/////////////////////////////////////////////////////

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include "windows.h"
	#include "Mmsystem.h"
#endif

#include "interface/xml/jIXml.h"
#include "interface/jIConsoleVar.h"
#include "interface/jISystemPlugIn.h"
#include <boost/bind.hpp>


namespace nMech
{
	jIVar* pv_e_time_profiling = jCV(ITimer, e_time_profiling,0,0,"0=off, 1=xx, 2=peak profiling, 3=xx" );
	jIVar* pv_e_time_smoothing = jCV(ITimer, e_time_smoothing,0,0,"[0..15] 0=no smoothing, x=x additional steps ");
	jIVar* pv_fixed_time_step = jCV(ITimer, fixed_time_step,0.0f,0,"Game updated with this fixed time step");

	using namespace nGLOBAL;
	namespace nTIME
	{
		//#define PROFILING 1
#ifdef PROFILING
		static int64 g_lCurrentTime = 0;
#endif


		static CTimer s_Timer;
		/////////////////////////////////////////////////////
		CTimer::CTimer() 
		{
			nInterface::g_pITimer = this;
			m_pfnUpdate=NULL;
			m_lBaseTime=0;
			m_lLastTime=0;
			m_lTicksPerSec=0;
			m_lCurrentTime=0;
			m_fFrameTime=0;
			m_fCurrTime=0;

			// smoothing
			m_timecount=0;
			for (int k=0;k<FPS_FRAMES;k++) 
				m_previousTimes[k]=0;

			m_nCurProfLine=0;
			m_fProfStartTime = -1;
			memset(m_TimeInfoTable,0,sizeof(m_TimeInfoTable));

			m_nCurProfLinesNum = 0;
			m_fStatsLogic = m_fStatsRender = m_fStatsSumm = 0;
			m_bEnabled=true;


		}

		//init the timer
		/////////////////////////////////////////////////////
		bool CTimer::Init()
		{
			LARGE_INTEGER TTicksPerSec;

			if (QueryPerformanceFrequency(&TTicksPerSec))
			{ 
				// performance counter is available, use it instead of multimedia timer
				LARGE_INTEGER t;
				QueryPerformanceCounter( &t );
				m_lTicksPerSec=TTicksPerSec.QuadPart;
				m_pfnUpdate = &CTimer::GetPerformanceCounterTime;
			}
			else
			{ 
				//Use MM timer if unable to use the High Frequency timer
				m_lTicksPerSec=1000;
				m_pfnUpdate = &CTimer::GetMMTime;
			}

			Reset();


			jSystemPlugIn_func fn;
			fn.m_OnFrameMove= boost::bind(&CTimer::Update, this);
			Get_jISystemPlugIn()->Regist(this,&fn );

			return (true);
		}

		//get frame rate
		/////////////////////////////////////////////////////
		float CTimer::GetFrameRate()
		{
			float diff=GetFrameTime();
			if (diff) return (1.0f/diff);
			return (0);
		}

		void CTimer::RefreshCurrTime()
		{
			double dVal=(double)m_lCurrentTime;

			m_fCurrTime=(float)(dVal/(double)(m_lTicksPerSec));
			if(m_fCurrTime <=0) m_fCurrTime=1.f;
			//assert(m_fCurrTime>=0);
		}

		//update the timer
		/////////////////////////////////////////////////////
		void CTimer::Update()
		{
			if(!m_bEnabled)
				return;

#ifdef PROFILING
			m_fFrameTime = 20; //20ms = 50fps
			g_lCurrentTime += (int)(m_fFrameTime*(float)(TIMEVALUE_PRECISION));
			m_lCurrentTime = g_lCurrentTime;
			m_lLastTime = m_lCurrentTime;
			RefreshCurrTime();
			return;
#endif

			if (pv_fixed_time_step->Get_float() != 0)
			{
				m_fFrameTime = pv_fixed_time_step->Get_float();
				m_lCurrentTime += (int64)(pv_fixed_time_step->Get_float()*(float)(m_lTicksPerSec));
				m_lLastTime = m_lCurrentTime;
				RefreshCurrTime();
				return;
			}

			if(m_pfnUpdate)
			{
				m_lCurrentTime =  (*m_pfnUpdate)() - m_lBaseTime;
			}
			RefreshCurrTime();

			m_fFrameTime=(float)(m_lCurrentTime-m_lLastTime) / (float)(m_lTicksPerSec);

			if (m_fFrameTime < 0) 
				m_fFrameTime = 0;

			if(pv_e_time_smoothing->Get_int()>0)
			{
				if(pv_e_time_smoothing->Get_int()>FPS_FRAMES-1)
					pv_e_time_smoothing->Set_int(FPS_FRAMES-2);

				if(m_fFrameTime < 0.0000001f)
					m_fFrameTime = 0.0000001f;

				m_previousTimes[m_timecount] = m_fFrameTime;

				m_timecount++;
				if(m_timecount>=pv_e_time_smoothing->Get_int())
					m_timecount=0;


				// average multiple frames together to smooth changes out a bit
				float total = 0;
				for (int i = 0 ; i < pv_e_time_smoothing->Get_int()+1; i++ ) 
					total += m_previousTimes[i];	

				if (!total) 
					total = 1;

				m_fFrameTime=total/(float)(pv_e_time_smoothing->Get_int()+1);
			}

			m_lLastTime = m_lCurrentTime;
		}

		//reset the timer
		/////////////////////////////////////////////////////
		void CTimer::Reset()
		{
			if(m_pfnUpdate)
			{
				m_lBaseTime = (*m_pfnUpdate)();
			}
			m_lLastTime = m_lCurrentTime = 0;
			m_fFrameTime = 0;
			RefreshCurrTime();
		}

		void CTimer::Enable(bool bEnable) 
		{ 
			if(!bEnable) 
				m_fFrameTime=0.0001f; 

			m_bEnabled = bEnable; 
		};

		//get time from performance counter
		/////////////////////////////////////////////////////
		int64 CTimer::GetPerformanceCounterTime()
		{
#ifdef PROFILING
			return g_lCurrentTime;
#endif

			LARGE_INTEGER lNow;

			QueryPerformanceCounter(&lNow);

			// for the following calculation even 64bit integer isn't enough
			//	int64 lCurTime=(lNow.QuadPart*TIMEVALUE_PRECISION) / m_lTicksPerSec;
			//	int64 lCurTime = (int64)((double)lNow.QuadPart / m_lTicksPerMicroSec);

			return lNow.QuadPart;
		}

		//get time from multimedia timer
		/////////////////////////////////////////////////////
		int64 CTimer::GetMMTime()
		{		
			int64 lNow=timeGetTime();

			return lNow;
		}

		float CTimer::MeasureTime(LPCSTR szComment)
		{
			// *_* by icandoit : 2005-06-17 11:32:04
			//
#if 0
			if(pv_e_time_profiling->Get_int()==0)
			{
				m_nCurProfLinesNum = m_nCurProfLine;
				m_nCurProfLine = 0;
				return (0);
			}
			if(!szComment)
				return 0;

			if(szComment==(LPCSTR)-1)
				szComment=0;

			/* *_* by icandoit : 2005-06-17 11:25:52

			if (!m_pSystem || !m_pSystem->GetIRenderer())
			return 0;

			/* *_* by icandoit : 2005-06-17 11:06:49
			int nRecursionLevel = (int)m_pSystem->GetIRenderer()->EF_Query(EFQ_RecurseLevel) - 1;
			if(nRecursionLevel>0)
			return 0;
			*/ //*_* by icandoit : 2005-06-17 11:06:51

			if(m_fProfStartTime == -1) // this var should be initialized only now
				m_fProfStartTime = (float)(GetAsyncCurTime()*1000);

			float fEnd = (float)(GetAsyncCurTime()*1000);
			float fTime = (fEnd - m_fProfStartTime);
			m_fProfStartTime = fEnd;

			float fMinShowTime = -100.0f;
			if (pv_e_time_profiling->Get_int() == 3)
				fMinShowTime = 0.02f;

			if(m_nCurProfLine>=TIME_PROFILE_PARAMS)
				return 0;

			if( szComment && m_nCurProfLine>=0 && m_nCurProfLine<TIME_PROFILE_PARAMS && strlen(szComment)>0 )
			{
				assert( (int)strlen(szComment) < sizeof(m_TimeInfoTable[m_nCurProfLine].param_name) );
				strcpy(m_TimeInfoTable[m_nCurProfLine].param_name, szComment);    
				m_TimeInfoTable[m_nCurProfLine].param_name[10]=0;								// bad

				if(fTime<0)
					fTime=0;

				if((pv_e_time_profiling->Get_int()==2 && fTime>m_TimeInfoTable[m_nCurProfLine].value) || (GetFrameTime()>1))
					m_TimeInfoTable[m_nCurProfLine].value = (fTime); // peak profiling
				else
					m_TimeInfoTable[m_nCurProfLine].value = (fTime+m_TimeInfoTable[m_nCurProfLine].value*50)/51.f;

				m_nCurProfLine++;
			}
			else if(pv_e_time_profiling->Get_int())
			{ // detail stats
				//		m_pSystem->GetIRenderer()->EnableFog(false);

				int nLine=0;
				float fSumm=0;

#ifndef _XBOX
				float fOffs = 78;
#else
				float fOffs = 60;
#endif
				int nLinesInCollumn=36;

				int nCollumns = m_nCurProfLine/nLinesInCollumn;

				//if(GetFrameTime()>1)
				//	m_pSystem->GetILog()->Log(TEXT("-- Slow frame rate profiling --"));

				int nColumn = 0;
				for(int i=0; i<m_nCurProfLine; i++)
				{
					if (m_TimeInfoTable[i].value < fMinShowTime)
						continue;
					if(m_TimeInfoTable[i].param_name[0])
					{
						float fColorK = (m_TimeInfoTable[i].value>0.1f) ? 1.f : 0.5f;
						m_pSystem->GetIRenderer()->TextToScreenColor(
							(int)(fOffs-(nCollumns-nColumn/nLinesInCollumn)*20),
							(int)(25+((((nLine++)%nLinesInCollumn)*2))), 
							(m_TimeInfoTable[i].param_name[0]=='3')*fColorK,fColorK,fColorK,1,
							"%12s %.02f", 
							m_TimeInfoTable[i].param_name + (m_TimeInfoTable[i].param_name[0]=='3'), 
							m_TimeInfoTable[i].value);

						//if(GetFrameTime()>1)
						//	m_pSystem->GetILog()->Log(TEXT("  %12s %.02f"), m_TimeInfoTable[i].param_name, m_TimeInfoTable[i].value);
					}
					fSumm += m_TimeInfoTable[i].value;
					nColumn++;
				}

				m_pSystem->GetIRenderer()->TextToScreen(
					fOffs-(nCollumns-nColumn/nLinesInCollumn)*16,
					(float)(25+((((nLine++)%nLinesInCollumn)*2))),
					"%12s %.02f", "* Summ *", fSumm);

				m_nCurProfLinesNum = m_nCurProfLine;
				m_nCurProfLine = 0;
			}
			/*		
			if( szComment==0 || szComment[0] == 0 ) // update basic stats
			{
			float fStatsLogic=0;
			float fStatsRender=0;
			float fStatsSumm=0;
			for(int i=0; i<m_nCurProfLinesNum; i++)
			{
			if(m_TimeInfoTable[i].param_name[0])
			{
			if(m_TimeInfoTable[i].param_name[0]=='3')
			fStatsRender += m_TimeInfoTable[i].value;
			else
			fStatsLogic += m_TimeInfoTable[i].value;
			}
			fStatsSumm += m_TimeInfoTable[i].value;
			}

			m_fStatsLogic  = (m_fStatsLogic +fStatsLogic)*0.5f;
			m_fStatsRender = (m_fStatsRender+fStatsRender)*0.5f;
			m_fStatsSumm   = (m_fStatsSumm  +fStatsSumm)*0.5f;
			}
			*/
			return fTime;
#endif
			return 0;

		}

		bool CTimer::GetBasicStats( float & fStatsLogic, float & fStatsRender, float & fStatsSumm )
		{
			fStatsLogic = m_fStatsLogic;
			fStatsRender= m_fStatsRender;
			fStatsSumm  = m_fStatsSumm;

			return fStatsSumm!=0;
		}

		TCHAR* CTimer::GetCurrentTimeString(fname_t szCurrentTime)
		{
			SYSTEMTIME	SystemTime;
			GetLocalTime(&SystemTime);
			_sntprintf(szCurrentTime, 250, _T("%02d %02d:%02d:%02d.%03d"),
				SystemTime.wDay, 
				SystemTime.wHour,
				SystemTime.wMinute,
				SystemTime.wSecond,
				SystemTime.wMilliseconds);
			return szCurrentTime;
		}

		TCHAR*  CTimer::GetCurrentDateString(fname_t szCurrentDate)
		{
			SYSTEMTIME	SystemTime;
			GetLocalTime(&SystemTime);
			_sntprintf(szCurrentDate, 250, _T("%d-%02d-%02d %02d"), 
				SystemTime.wYear, 
				SystemTime.wMonth, 
				SystemTime.wDay,
				SystemTime.wHour);
			return szCurrentDate;
		}
	}
}


