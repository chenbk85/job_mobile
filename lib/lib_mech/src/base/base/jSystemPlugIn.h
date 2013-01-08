#pragma once

#include "header/jSington.h"
#include "Interface/jISystemPlugIn.h"

namespace nMech
{

	class JBASE_API jSystemPlugIn : public jISystemPlugIn
	{
	private:		jSINGTON_INTERFACE_DECLEAR(JBASE_API , jSystemPlugIn,jISystemPlugIn);

	public:		jINTERFACE_HEADER(jISystemPlugIn);

#pragma warning(disable : 4251)

#define 	_list_define(x) typedef pair<void* , x##_t> x##_pt; jLIST_TYPEDEF_list(x##_pt, m_##x);
						_for_each_jSystemPlugIn_func(_list_define);
#undef _list_define

#pragma warning(default : 4251)

#define 	_Regist_func(x) inline void jSystemPlugIn::Regist_##x(void* pvObj , x##_t  func,bool isFirst=false) \
						{ if(isFirst) m_##x.push_front(make_pair(pvObj, func)); else m_##x.push_back(make_pair(pvObj,  func)) ; }
						_for_each_jSystemPlugIn_func(_Regist_func);
#undef _Regist_func

						~jSystemPlugIn(void);
	};
}
