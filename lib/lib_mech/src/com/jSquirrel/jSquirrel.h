/* file : jSquirrel.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-26 12:40:01
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __jSquirrel_header__
#define __jSquirrel_header__
#pragma once



// 다음 ifdef 블록은 DLL에서 내보내기하는 작업을 쉽게 해 주는 매크로를 만드는 
// 표준 방식입니다. 이 DLL에 들어 있는 파일은 모두 명령줄에 정의된 _EXPORTS 기호로
// 컴파일되며, 동일한 DLL을 사용하는 다른 프로젝트에서는 이 기호를 정의할 수 없습니다.
// 이렇게 하면 소스 파일에 이 파일이 들어 있는 다른 모든 프로젝트에서는 
// JSQUIRREL_API 함수를 DLL에서 가져오는 것으로 보고, 이 DLL은
// 이 DLL은 해당 매크로로 정의된 기호가 내보내지는 것으로 봅니다.




#include "Interface/Squirrel/jISquirrel.h"


namespace nMech
{
	namespace nSQ
	{
		class jSquirrel : public jISquirrel
		{
			jINTERFACE_HEADER(jISquirrel);
			jSquirrel():m_isBegin(false){}
		private:
			jLIST_TYPEDEF_map(std::tstring,bind_module_func_t*, m_binder);
			static void bind_module_func_caller(jSquirrel::m_binder_vt it){ it.second();}
			bool m_isBegin;

		};

	}//namespace nSQ
}



#include "sqplus/SquirrelVM.h"


#endif // __jSquirrel_header__

