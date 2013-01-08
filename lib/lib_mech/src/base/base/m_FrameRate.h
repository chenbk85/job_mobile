/* 
	filename:	m_FrameRate.h
	coder	:	Cho Wook Rea (mech12@hanmail.net)
	compiler:	vc++ 6.0
	date	:	1999 / 
	title	:	
*/

#if !defined(AFX_M_FRAMERATE_H__E47B14E7_E6E0_11D2_8FBA_00A02486A654__INCLUDED_)
#define AFX_M_FRAMERATE_H__E47B14E7_E6E0_11D2_8FBA_00A02486A654__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define M_USING_FRAMERATE
#define MOVEPIXEL_PER_SEC_BY_KEY 180

#include "header/jRDTSC.h"
namespace nMech
{
	namespace nTIME
	{
		extern uint32 e,s;
		class  JBASE_API CFrameRate
		{
			unsigned int                   m_FrameTime;    // Time of the last frame.
			unsigned int                   m_Frames;       // The frame rate (frames/second).
			unsigned int                   m_Count;   // Frames displayed.
			unsigned int time ;
		public:
			CFrameRate(){Init();}
			void Init();
			void Update();
			operator int(){return m_Frames;}
			int GetFramePerSec(){return m_Frames;}
			unsigned int GetClock(){return time;}

			//////////////////////////////////////////////
			// RDTSC¿ë.
			//////////////////////////////////////////////
			void Start(){ RDTSC(s); }
			unsigned int End(){RDTSC(e);return e-s;}

			//	virtual ~CFrameRate(){;};

		};

	}//nTIME

}
#if 0

#ifndef __CClock__
#define __CClock__

	 #include <time.h>
	 #if !defined( CLOCKS_PER_SEC )
	 #define 		CLOCKS_PER_SEC 		CLK_TCK
	 #endif

	 class CFps{
	 private:
		 clock_t m_Begin,m_End;
		 clock_t m_Max , m_Min, m_Curr;
		 

	 public:
		void Init(){m_Max = m_Begin =0; m_Min = 9999;}
		void Begin(){m_Begin=clock(); }

		void End(){	m_Curr = clock()-m_Begin;		}

		float GetTimePerFrame(){ return (float)(m_Curr)/(float)(CLOCKS_PER_SEC);}
		const long& GetClockPerFrame() const { return m_Curr;}
		const long& GetMaxClock() const {return m_Max;}
		const long& GetMinClock() const {return m_Min;}


	 };

#endif //__CClock__
#endif

#endif // !defined(AFX_M_FRAMERATE_H__E47B14E7_E6E0_11D2_8FBA_00A02486A654__INCLUDED_)

