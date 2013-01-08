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
	������ �̱��� ������ ����Ҷ� ���.

	AAA.h����

	struct AAA
	{
		jSINGTON_DECLEAR(AAA);

		...
	};


	AAA.cpp����

	jSINGTON_DEFINE(AAA);

	
	����Ҷ�

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


// �������̽� ��ӹ��� Ŭ���� �ش��� �� �������� ����
#define jSINGTON_INTERFACE_HEADER(where , _interface_)	\
	extern where  _interface_* Get_##_interface_();


// �������̽� ��ӹ��� Ŭ���� ���ο� ����
#define jSINGTON_INTERFACE_DECLEAR(where , _class_ , _interface_)  \
private: _class_() ; \
	friend where _interface_* Get_##_interface_();


// �������̽� ��ӹ��� Ŭ������ cpp��� ó���� ����.
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
