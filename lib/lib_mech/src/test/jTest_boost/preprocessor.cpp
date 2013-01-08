#include<stdafx.h>
//--- main.cpp ---
// ComponentLayout�� ��ü�� ������Ʈ����
// ��ũ�� ���� �Ϲ߷� �ٲٰ� �ʹ�.�׷��� ��� �ұ�.
#include <boost/preprocessor.hpp>

class ComponentLayout
{
public:
	virtual void ShowName() {}
	virtual void PlaceUnits() {}
	virtual void Resize(int cx, int cy) {}
};

#if 0

// �����ϰ� ���� ���ڿ�ȭ
// #include CL_PROJECTNAME.h (��)�� �ϰ� �ʹ�
#include BOOST_PP_STRINGIZE(          
           BOOST_PP_CAT( CL_,         
           BOOST_PP_CAT( PROJECTNAME, 
                         .h            )))

int main_preprocessor()
{
	// ����
	// new ComponentLayout_PROJECTNAME (��)�� �ϰ� �ʹ�
	ComponentLayout* pLay = new
	  BOOST_PP_CAT( ComponentLayout_, PROJECTNAME );

	pLay->ShowName();
	delete pLay;
	return 0;
}

//--- CL_Abc.h ---
#include <iostream>

class ComponentLayout_Abc : public ComponentLayout
{
	void ShowName() { std::cout << "Project: ABC" << std::endl; }
};

//--- CL_Iroha.h ---
#include <iostream>

class ComponentLayout_Iroha : public ComponentLayout
{
	void ShowName() { std::cout << "Project: IROHA" << std::endl; }
};
/*
��¿�
>> bcc32 -DPROJECTNAME=Iroha main.cpp
>> main
Project: IROHA

>> bcc32 -DPROJECTNAME=Abc main.cpp
>> main
Project: ABC

*/
#endif