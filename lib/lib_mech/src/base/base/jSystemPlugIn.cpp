#include "stdafx.h"
#include "jSystemPlugIn.h"

namespace nMech
{

	//jSINGTON_INTERFACE_DEFINE(JBASE_API , jSystemPlugIn,jISystemPlugIn)	{	}

	JBASE_API jISystemPlugIn* Get_jISystemPlugIn()
	{
		static jSystemPlugIn *a=0;
		if(!a)
		{
			a = new jSystemPlugIn;
		}
		return a;
	}
	jSystemPlugIn::jSystemPlugIn()
	{ 
		int i=0;
		++i;
		int b =i;
	}

	jSystemPlugIn::~jSystemPlugIn(void)
	{
		//UnRegistAll();
	}

	void jSystemPlugIn::UnRegistAll()
	{
#define 	_clear_to_list(x)  m_##x.clear();
		_for_each_jSystemPlugIn_func(_clear_to_list);
#undef _clear_to_list

	}

	void jSystemPlugIn::UnRegist(void* pObj)
	{
#define jITERATOR(x) x##_it
#define 	_erase_to_list(x)  { jITERATOR(m_##x) it = m_##x.begin() , ie = m_##x.end();\
	for(;it!=ie;++it){ if(it->first==pObj){ m_##x.erase(it); break;} } }
		_for_each_jSystemPlugIn_func(_erase_to_list);
#undef _erase_to_list

	}


	void jSystemPlugIn::Regist(void* pObj, const jSystemPlugIn_func* r )
	{
#define 	_push_back_to_list(x)  Regist_##x(pObj,r->m_##x,r->m_isFirst_##x);
		_for_each_jSystemPlugIn_func(_push_back_to_list);
#undef _push_back_to_list

	}


#define __OnEvent_func_def(x, y,arg_type, arg) \
	inline void jSystemPlugIn::x(arg_type arg) {   m_##y  it = m_##x.begin() , ie = m_##x.end(); 	for(;it!=ie; ++it) { if(it->second) it->second(arg); } }
#define __INTERFACE_FUNC_DEF(x,arg_type, arg) __OnEvent_func_def(x, x##_it,arg_type,arg)

	__INTERFACE_FUNC_DEF(SetLocalWnd, HWND , hWnd);
	__INTERFACE_FUNC_DEF(OnCreateDevice, void* , pDevice);
	__INTERFACE_FUNC_DEF(OnRender, void , _VOID_);
	__INTERFACE_FUNC_DEF(OnFrameMove,void, _VOID_);
	__INTERFACE_FUNC_DEF(Close,void , _VOID_);
	__INTERFACE_FUNC_DEF(OnLostDevice,void , _VOID_);
	__INTERFACE_FUNC_DEF(OnResetDevice,void , _VOID_);
	__INTERFACE_FUNC_DEF(OnDestroyDevice,void , _VOID_);

	bool jSystemPlugIn::OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
	{   
		//using namespace lambda;
		//OnMsgProc_pt pt;
		//for_each(m_OnMsgProc.begin() , m_OnMsgProc.end() , (var(pt )= _1, var(pt).second(hWnd,uMsg, wParam, lParam)) );
		m_OnMsgProc_it  it = m_OnMsgProc.begin() , ie = m_OnMsgProc.end();
		for(;it!=ie; ++it)
		{
			if( it->second(hWnd, uMsg, wParam , lParam) ) return true;
		}
		return false;
	}
}//namespace nMech
