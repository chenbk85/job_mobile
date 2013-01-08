/* file : jSington.h
Coder : by icandoit ( mech12@nate.com)
Date : 2006-10-25 17:09:35
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jSington_header__
#define __jSington_header__
#pragma once

#include "header/jCriticalSection.h"

namespace nMech
{
/*
	간단히 싱글톤 선언후 사용할때 사용.

	AAA.h에서

	struct AAA
	{
		jSINGTON_DECLEAR(AAA);

		...
	};


	AAA.cpp에서

	jSINGTON_DEFINE(AAA);

	
	사용할때

	AAA* pAAA = AAA::Get();

*/
#define jSINGTON_DECLEAR(_class_) \
private: _class_();\
public: 	static _class_* Get();


#define jSINGTON_DEFINE(_class_) \
	_class_* _class_::Get()\
	{\
	static _class_ *a=0;\
	if(!a)\
	{\
	static jCriticalSection cs;\
	cs.Lock();\
	static _class_ b;\
	a = &b;\
	cs.UnLock();\
	}\
	return a;\
	}\
	_class_::_class_()


// 인터페이스 상속받은 클래스 해더의 맨 마지막에 선언
#define jSINGTON_INTERFACE_HEADER(where , _interface_)	\
	extern where  _interface_* Get_##_interface_();


// 인터페이스 상속받은 클래스 내부에 선언
#define jSINGTON_INTERFACE_DECLEAR(where , _class_ , _interface_)  \
private: _class_() ; \
	friend where _interface_* Get_##_interface_();


// 인터페이스 상속받은 클래스의 cpp모듈 처음에 선언.
#define jSINGTON_INTERFACE_DEFINE(where ,  _class_ , _interface_) \
	where  _interface_* Get_##_interface_()\
	{\
	static _interface_* a=0;\
	if(!a)\
	{\
	static nUtil::jCriticalSection cs;\
	cs.Lock();\
	static _class_ b;\
	a = &b;\
	cs.UnLock();\
	}\
	return a;\
	}\
	_class_::_class_()

}

#endif // __jSington_header__
