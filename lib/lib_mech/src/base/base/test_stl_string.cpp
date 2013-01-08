/* file : test_stl_string.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-01-31 16:27:39
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jTestUnit.h"


using namespace nMech;

namespace 
{

	jTEST_SUITE_BEGIN( string_test)
	jTEST( stl_string)
	{
		//jSET_LOCALE();
		jSET_LOCALE1("kor");

		//http://idb.snu.ac.kr/~sjjung/stl/str_7474.htm#12.2.9
		{
			tstring s1;                       // 변수 이름만 지정
			jTEST_CHECK(s1.empty());//size()를 0이랑 비교하는 것보다 일반적으로 빠르다. 

			tstring s2(_T("a string"));           // 초기값 제공
			tstring s3 = _T("initial value");     // 초기값 제공
			tstring s4(s3);                   // 복사 생성자 이용

			s4.assign(s2, 0, 3);         // s2의 처음 3 문자를 s4에 대입한다
			jTEST_CHECK(s4 == _T("a s"));
			s4.append(s3, 2, 3);         // 2, 3, 4번 위치에 있는 문자들을 덧붙인다
			jTEST_CHECK(s4 == _T("a siti"));

			s3.swap(s4);                 // s4와 s3를 바꾼다
			jTEST_CHECK(s3 == _T("a siti"));
			jTEST_CHECK(s4 == _T("initial value"));
			s4[2] = 'x';                  // 2번 위치의 문자를 변경
			jEQUAL(s4.at(2) , 'x');

			tstring s6(_T("small value"), 100);   // 11개의 문자를 포함, 100개까지 담을 수 있음
			tstring s6_1(s6);
			size_t asdf ;
			jTEST_CHECK(s6.capacity() > 100);
			jEQUAL(s6.size(), 100);
			s6.reserve(200);                    // capacity를 200으로 바꾼다
			jTEST_CHECK(s6 != tstring(_T("small value") ));
			jTEST_CHECK(s6 == s6_1);
			asdf = s6.capacity();
			jTEST_CHECK(s6.capacity() > 200);
			asdf = s6.max_size();
			jTEST_CHECK(s6.max_size() > 201);

			tstring s7(10, '\n');             // 10개의 개행문자로 초기화
			jTEST_CHECK(s7 == _T("\n\n\n\n\n\n\n\n\n\n"));
			jEQUAL(s7.size(), 10);

			s7.resize(15, '\t');                // 맨 끝에 탭 문자들을 추가하여 사이즈를 늘린다
			jEQUAL(s7.size(), 15);
			jEQUAL(s7.length(), 15);


			vector<TCHAR> aList;
			aList.push_back('a');
			aList.push_back('b');
			aList.push_back('c');
			aList.push_back('d');
			tstring s8(aList.begin(), aList.end());
			jTEST_CHECK(s8 ==_T("abcd"));

		}



		/*
		반복자의 무효화  
		append나 insert와 같이 내부 string 버퍼의 재할당을 초래할 수 있는 연산을 수행한 뒤에는 
		반복자가 가리키는 값이 유효하다고 보장할 수 없다.  
		*/
		{
			tstring s3 = _T("0123456789");    
			s3.insert(3, _T("abc"));      // 3번 위치 뒤에 "abc" 삽입
			jTEST_CHECK(s3 == _T("012abc3456789"));
			s3.erase(4, 2);           // 4, 5번 위치 삭제
			jTEST_CHECK(s3== _T("012a3456789"));
			s3.replace(4, 2, _T("pqr"));  // 4, 5번 위치를 "pqr"로 치환	
			jTEST_CHECK(s3 == _T("012apqr56789"));
		}
		{
			tstring s3 = _T("0123456789");     
			fname_t s4 ,s5;
			memset(s4,0,sizeof(s4));
			memset(s5,0,sizeof(s5));
			s3.copy(s4, 2);           
			jTEST_CHECK(std::tstring(s4)==_T("01"));
			s3.copy(s5, 2, 5);// 5번째에서 2개 복사
			jTEST_CHECK(std::tstring(s5)== _T("56"));

		}
		{
			tstring s3 = _T("0123456789");     // 초기값 제공
			jTEST_CHECK(s3.substr(3)== _T("3456789"));// 3번 위치부터 끝까지
			jTEST_CHECK(s3.substr(3,2)== _T("34"));// 3, 4번 위치
		}
		{
			tstring s1 = _T("01234567890123456789");
			jEQUAL(s1.find(_T("asdf")) , std::tstring::npos);
			jEQUAL(s1.find(_T("23"))		,2);             
			jEQUAL(s1.find(_T("23"), 5) , 12);           
			jEQUAL(s1.rfind(_T("23"))				, 12 );
			size_t i = s1.rfind(_T("23"), 10)	;
			jEQUAL(i	, 2);

			i = s1.find_first_of(_T("94567"));            // "4568"글자중에 첫번째로 발견되는 위치
			jEQUAL(i, 4);
			size_t j = s1.find_first_not_of(_T("94567"), 8);     // 해당 글자중에 한번도 안나타나는 첫번째위치
			jEQUAL(j , 8);

			i = s1.find_last_of(_T("56"));
			jEQUAL(i  , 16);
			j = s1.find_last_not_of(_T("56"), i);
			jEQUAL(j, 14);
		}


	}
	jTEST_SUITE_END( string_test )
}
