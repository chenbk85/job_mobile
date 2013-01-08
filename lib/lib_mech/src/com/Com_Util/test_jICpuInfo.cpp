/* file : test_jICpuInfo.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-12 12:43:31
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "base/jTestUnit.h"
#include "interface/jICpuInfo.h"


using namespace nMech;
namespace 
{
	jTEST_SUITE_BEGIN(com_util)
	jTEST(jICpuInfo_test)
	{
		using namespace nOS;
		jICpuInfo* pjICpuInfo = jCREATE_INTERFACE(nMech::nOS::jICpuInfo);
		jCHECK(pjICpuInfo);
		pjICpuInfo->Detect();
		double cpuClock = pjICpuInfo->GetCpu_SecPerCycle(0);
		jCHECK(cpuClock > 0);

	}

	jTEST_SUITE_END(com_util)
}
