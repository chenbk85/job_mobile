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
			tstring s1;                       // ���� �̸��� ����
			jTEST_CHECK(s1.empty());//size()�� 0�̶� ���ϴ� �ͺ��� �Ϲ������� ������. 

			tstring s2(_T("a string"));           // �ʱⰪ ����
			tstring s3 = _T("initial value");     // �ʱⰪ ����
			tstring s4(s3);                   // ���� ������ �̿�

			s4.assign(s2, 0, 3);         // s2�� ó�� 3 ���ڸ� s4�� �����Ѵ�
			jTEST_CHECK(s4 == _T("a s"));
			s4.append(s3, 2, 3);         // 2, 3, 4�� ��ġ�� �ִ� ���ڵ��� �����δ�
			jTEST_CHECK(s4 == _T("a siti"));

			s3.swap(s4);                 // s4�� s3�� �ٲ۴�
			jTEST_CHECK(s3 == _T("a siti"));
			jTEST_CHECK(s4 == _T("initial value"));
			s4[2] = 'x';                  // 2�� ��ġ�� ���ڸ� ����
			jEQUAL(s4.at(2) , 'x');

			tstring s6(_T("small value"), 100);   // 11���� ���ڸ� ����, 100������ ���� �� ����
			tstring s6_1(s6);
			size_t asdf ;
			jTEST_CHECK(s6.capacity() > 100);
			jEQUAL(s6.size(), 100);
			s6.reserve(200);                    // capacity�� 200���� �ٲ۴�
			jTEST_CHECK(s6 != tstring(_T("small value") ));
			jTEST_CHECK(s6 == s6_1);
			asdf = s6.capacity();
			jTEST_CHECK(s6.capacity() > 200);
			asdf = s6.max_size();
			jTEST_CHECK(s6.max_size() > 201);

			tstring s7(10, '\n');             // 10���� ���๮�ڷ� �ʱ�ȭ
			jTEST_CHECK(s7 == _T("\n\n\n\n\n\n\n\n\n\n"));
			jEQUAL(s7.size(), 10);

			s7.resize(15, '\t');                // �� ���� �� ���ڵ��� �߰��Ͽ� ����� �ø���
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
		�ݺ����� ��ȿȭ  
		append�� insert�� ���� ���� string ������ ���Ҵ��� �ʷ��� �� �ִ� ������ ������ �ڿ��� 
		�ݺ��ڰ� ����Ű�� ���� ��ȿ�ϴٰ� ������ �� ����.  
		*/
		{
			tstring s3 = _T("0123456789");    
			s3.insert(3, _T("abc"));      // 3�� ��ġ �ڿ� "abc" ����
			jTEST_CHECK(s3 == _T("012abc3456789"));
			s3.erase(4, 2);           // 4, 5�� ��ġ ����
			jTEST_CHECK(s3== _T("012a3456789"));
			s3.replace(4, 2, _T("pqr"));  // 4, 5�� ��ġ�� "pqr"�� ġȯ	
			jTEST_CHECK(s3 == _T("012apqr56789"));
		}
		{
			tstring s3 = _T("0123456789");     
			fname_t s4 ,s5;
			memset(s4,0,sizeof(s4));
			memset(s5,0,sizeof(s5));
			s3.copy(s4, 2);           
			jTEST_CHECK(std::tstring(s4)==_T("01"));
			s3.copy(s5, 2, 5);// 5��°���� 2�� ����
			jTEST_CHECK(std::tstring(s5)== _T("56"));

		}
		{
			tstring s3 = _T("0123456789");     // �ʱⰪ ����
			jTEST_CHECK(s3.substr(3)== _T("3456789"));// 3�� ��ġ���� ������
			jTEST_CHECK(s3.substr(3,2)== _T("34"));// 3, 4�� ��ġ
		}
		{
			tstring s1 = _T("01234567890123456789");
			jEQUAL(s1.find(_T("asdf")) , std::tstring::npos);
			jEQUAL(s1.find(_T("23"))		,2);             
			jEQUAL(s1.find(_T("23"), 5) , 12);           
			jEQUAL(s1.rfind(_T("23"))				, 12 );
			size_t i = s1.rfind(_T("23"), 10)	;
			jEQUAL(i	, 2);

			i = s1.find_first_of(_T("94567"));            // "4568"�����߿� ù��°�� �߰ߵǴ� ��ġ
			jEQUAL(i, 4);
			size_t j = s1.find_first_not_of(_T("94567"), 8);     // �ش� �����߿� �ѹ��� �ȳ�Ÿ���� ù��°��ġ
			jEQUAL(j , 8);

			i = s1.find_last_of(_T("56"));
			jEQUAL(i  , 16);
			j = s1.find_last_not_of(_T("56"), i);
			jEQUAL(j, 14);
		}


	}
	jTEST_SUITE_END( string_test )
}
