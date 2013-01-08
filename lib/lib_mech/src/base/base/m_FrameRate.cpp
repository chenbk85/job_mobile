/* 
	filename:	m_FrameRate.cpp
	coder	:	Cho Wook Rea (mech12@hanmail.net)
	compiler:	vc++ 6.0
	date	:	1999 / 
	title	:	
*/
#include "stdafx.h"
#include <mmsystem.h>
#include "m_FrameRate.h"


namespace nMech
{
	namespace nTIME
	{
		//////////////////////////////////////////////
		void CFrameRate::Init()
			//////////////////////////////////////////////
		{
			m_Frames=0,m_Count=0;
			m_FrameTime = timeGetTime();
		}

		//////////////////////////////////////////////
		void CFrameRate::Update(){
			//////////////////////////////////////////////
			m_Count++;		
			time= timeGetTime() - m_FrameTime;

			if (time > 1000 ) 
			{	
				m_Frames = ( m_Count*1000 )/time;
				m_FrameTime = timeGetTime();
				m_Count = 0;
			}
		}
		uint32 e,s;

	}//nTIME

}
