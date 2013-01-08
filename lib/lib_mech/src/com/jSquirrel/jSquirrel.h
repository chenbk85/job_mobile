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



// ���� ifdef ����� DLL���� ���������ϴ� �۾��� ���� �� �ִ� ��ũ�θ� ����� 
// ǥ�� ����Դϴ�. �� DLL�� ��� �ִ� ������ ��� ����ٿ� ���ǵ� _EXPORTS ��ȣ��
// �����ϵǸ�, ������ DLL�� ����ϴ� �ٸ� ������Ʈ������ �� ��ȣ�� ������ �� �����ϴ�.
// �̷��� �ϸ� �ҽ� ���Ͽ� �� ������ ��� �ִ� �ٸ� ��� ������Ʈ������ 
// JSQUIRREL_API �Լ��� DLL���� �������� ������ ����, �� DLL��
// �� DLL�� �ش� ��ũ�η� ���ǵ� ��ȣ�� ���������� ������ ���ϴ�.




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

