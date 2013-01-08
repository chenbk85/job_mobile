/* file : sample_interface.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-01-29 14:25:43
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jTestUnit.h"



namespace 
{
	jTEST_SUITE_BEGIN(string_test)

	struct test_interface
	{
#define jINTERFACE_test_interface(X)\
	virtual void asdf(int a) ##X \
	virtual float asdf1(int aa) ##X \

	jINTERFACE_ABSTRACT(test_interface);

	};

	class test_class : public test_interface
	{
	public:
		jINTERFACE_HEADER(test_interface);
	};

	void test_class::asdf(int a){}
	float test_class::asdf1(int ){ return 0;}

	test_class aaa;

	jTEST(indexed_string)
	{

	}
	jTEST_SUITE_END(string_test)

}
