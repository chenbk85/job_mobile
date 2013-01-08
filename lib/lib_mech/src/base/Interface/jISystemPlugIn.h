/* file : jISystemPlugIn.h
Coder : by icandoit ( mech12@nate.com)
Date : 2006-11-20 14:36:55
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jISystemPlugIn_heade234242sdfewr__
#define __jISystemPlugIn_heade234242sdfewr__
#pragma once

#include <boost/function.hpp>

namespace nMech
{

#define _VOID_ 

	typedef boost::function< void ( HWND) > SetLocalWnd_t;
	typedef boost::function< void ( void* ) > OnCreateDevice_t;
	typedef boost::function< void (void) > OnRender_t;
	typedef boost::function< void (void) > OnFrameMove_t;
	typedef boost::function< void (void) > Close_t;
	typedef boost::function< void (void) > OnLostDevice_t;
	typedef boost::function< void (void) > OnResetDevice_t;
	typedef boost::function< void (void) > OnDestroyDevice_t;
	typedef boost::function< bool (HWND , UINT , WPARAM , LPARAM ) > OnMsgProc_t;

	//return값이 void이고 arg가 한개또는 void형인 함수
#define _for_each_jSystemPlugIn_void_func_arg1(ACTION) \
	ACTION(SetLocalWnd);\
	ACTION(OnCreateDevice);\
	ACTION(OnRender);\
	ACTION(OnFrameMove);\
	ACTION(Close);\
	ACTION(OnLostDevice);\
	ACTION(OnResetDevice);\
	ACTION(OnDestroyDevice);\

#define _for_each_jSystemPlugIn_func(ACTION) \
	_for_each_jSystemPlugIn_void_func_arg1(ACTION)\
	ACTION(OnMsgProc);


	struct  jSystemPlugIn_func
	{
#define 	_member_define_j(x) x##_t m_##x;
#define _member_bool_j(x) bool m_isFirst_##x;
		_for_each_jSystemPlugIn_func(_member_define_j)
			_for_each_jSystemPlugIn_func(_member_bool_j)
#undef _member_define_j
#undef _member_bool_j

			jSystemPlugIn_func(){ memset(this , 0 , sizeof(*this));}
	};

#define jINTERFACE_jISystemPlugIn(x) public:	\
	virtual void SetLocalWnd(HWND hWnd) ##x \
	virtual void OnCreateDevice( void* pd3dDevice) ##x \
	virtual void OnRender()##x \
	virtual void OnFrameMove() ##x \
	virtual void Close() ##x \
	virtual void OnLostDevice() ##x \
	virtual void OnResetDevice() ##x \
	virtual void OnDestroyDevice() ##x \
	virtual bool OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ##x \
	virtual void Regist(void* pObj, const jSystemPlugIn_func* inputFunc ) ##x \
	virtual void UnRegist(void*) ##x \
	virtual void UnRegistAll() ##x \

	jINTERFACE_END(jISystemPlugIn);

	//jSINGTON_INTERFACE_HEADER(JBASE_API , jISystemPlugIn);
	extern JBASE_API  jISystemPlugIn* Get_jISystemPlugIn();
}

#endif // __jISystemPlugIn_heade234242sdfewr__
