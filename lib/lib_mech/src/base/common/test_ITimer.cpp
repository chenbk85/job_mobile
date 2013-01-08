/* file : test_ITimer.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-01 17:53:37
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "base/jTestUnit.h"
#include "interface/ITimer.h"
#include <boost/timer.hpp>
#include <Mmsystem.h>

#pragma comment(lib, "winmm.lib")

#if 1
using namespace nMech;
namespace 
{
	using namespace nMech::nTIME;
	jTEST_SUITE_BEGIN(jBase_suite)
	jTEST(ITimer_test)
	{
		nTIME::Get_ITimer();

		{
			int i=1;
			float fStart = nTIME::Get_ITimer()->GetCurrTime();
			float fEnd=0;
			boost::timer tBoostTime;
			DWORD iStart=0 ,iEnd=0, iTot =0;;
			iStart = timeGetTime();
			for (;1 ;++i )
			{
				nTIME::Get_ITimer()->Update();


				if( tBoostTime.elapsed() > 5.f)
				{
					iEnd = timeGetTime();
					iTot = iEnd - iStart;
					Sleep(1);
					fEnd = nTIME::Get_ITimer()->GetCurrTime();
					fEnd-=fStart;
					jCLOSE(fEnd, 5.f, 0.100);
					break;
				}

				//float fps = nTIME::Get_ITimer()->GetFrameRate();
				//jEQUAL(fps,i);
			}
		}


		{
			int i=0;
			CTimeValue tStart = nTIME::Get_ITimer()->GetCurrTimePrecise();
			float fEnd=0;
			boost::timer tBoostTime;
			for (;1 ;++i )
			{
				nTIME::Get_ITimer()->Update();
				if( tBoostTime.elapsed() > 5.f)
				{
					Sleep(1);
					CTimeValue tEnd = nTIME::Get_ITimer()->GetCurrTimePrecise();
					tEnd = tEnd - tStart;
					float tot = tEnd.GetMilliSeconds();
					jCLOSE(tot, 5000.f, 50.f);
					break;
				}
			}

		}
	}

	jTEST_SUITE_END(jBase_suite)
}


#endif