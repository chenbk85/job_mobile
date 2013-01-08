// jTest_stl.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


int main_atoi()
{
	int i = atoi("asdf");
	i = atoi("23 asdf");
	i = atoi("sdf 23 asdf");
	return 0;
}

#define CALL_X(X) printf("\n\n %s call!!! \n",#X);int X(); X();

int _tmain(int argc, _TCHAR* argv[])
{
	CALL_X(main_atoi);

	CALL_X(main_ostream_iterator);
	CALL_X(main_ostream_iterator_copy);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);
	//CALL_X(main_ostream_iterator);

	return 0;
}

