#include<stdafx.h>
//--- main.cpp ---
// ComponentLayout의 실체를 프로젝트마다
// 매크로 정의 일발로 바꾸고 싶다.그런데 어떻게 할까.
#include <boost/preprocessor.hpp>

class ComponentLayout
{
public:
	virtual void ShowName() {}
	virtual void PlaceUnits() {}
	virtual void Resize(int cx, int cy) {}
};

#if 0

// 연결하고 나서 문자열화
// #include CL_PROJECTNAME.h (으)로 하고 싶다
#include BOOST_PP_STRINGIZE(          
           BOOST_PP_CAT( CL_,         
           BOOST_PP_CAT( PROJECTNAME, 
                         .h            )))

int main_preprocessor()
{
	// 연결
	// new ComponentLayout_PROJECTNAME (으)로 하고 싶다
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
출력예
>> bcc32 -DPROJECTNAME=Iroha main.cpp
>> main
Project: IROHA

>> bcc32 -DPROJECTNAME=Abc main.cpp
>> main
Project: ABC

*/
#endif