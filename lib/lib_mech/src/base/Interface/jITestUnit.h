/* file : jITestUnit.h
Coder : by icandoit ( mech12@nate.com)
Date : 2006-11-21 12:50:56
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jITestUnit_header__
#define __jITestUnit_header__
#pragma once

#include "header/jBoost.h"
#include "header/jSington.h"

namespace nMech
{

	typedef function<void (jIE*)> jTestUnitFunc_t;

#define jINTERFACE_jITestUnit(x) public:	\
	virtual void RegistTest(cstr szName, jTestUnitFunc_t) ##x\
	virtual void RunTest(jID* pDocTestTarget) ##x \

	jINTERFACE_END(jITestUnit);


	jSINGTON_INTERFACE_HEADER(JBASE_API , jITestUnit);

#define jTESTUNIT_REGIST(a) Get_jITestUnit()->RegistTest(_T(#a), a::TestUnit);

#ifndef jNOT_USE_TEST

	//#undef V2
	//#define  V2(x)  jAssert(x, ("xxx::TestUnit() " #x ))

	// peTestNode는 xml/system/jTestunit.xml에서의 해당 테스트 노드
#define jTESTUNIT_DO(X) namespace X {	void TestUnit(jIE*);jONCE_RUN(X##jONCE_RUN)	{	jTESTUNIT_REGIST(X)	};	void TestUnit(jIE* peTestNode) 

#endif

}


#endif // __jITestUnit_header__
