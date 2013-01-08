/* file : jICpuInfo.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-28 21:30:11
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jICpuInfo_header__
#define __jICpuInfo_header__
#pragma once
namespace nMech
{
	namespace nOS
	{
#define jINTERFACE_jICpuInfo(x) public:	\
	virtual bool hasMMX()##x\
	virtual bool hasSSE()##x\
	virtual bool hasSSE2()##x\
	virtual bool has3DNow()##x\
	virtual bool IsAMD64() ##x \
	\
	/* jILog::LogA()로 출력한다.*/\
	virtual void Detect()##x\
	virtual double GetCpu_SecPerCycle(int cpuIndex)##x\

		jINTERFACE_END_BASE1(jICpuInfo,nInterface::jIInterface);

		// 사용법 
		// jICpuInfo* pjICpuInfo = jCREATE_INTERFACE(nMech::nOS::jICpuInfo);
	}
}


#endif // __jICpuInfo_header__
