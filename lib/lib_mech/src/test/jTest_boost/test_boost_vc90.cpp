// test_boost_vc90.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


struct _AAA_
{
	union 
	{
		bool*  m_bool_p;
		int* m_int_p;
		bool m_bool;
		int m_int;
	};
	int asdf;
};

#define CALL_X(X) printf("\n\n %s call!!! \n",#X);int main_##X(); main_##X();
int main()
{
	int main_local_time();main_local_time();

	int test_path();test_path();
	_AAA_ a ,b;
	int int_val = 1;

	a.m_int = 1;
	b.m_bool_p = reinterpret_cast<bool* > (&int_val);

#if 1
	//CALL_X(serialization);

	//사족 util
	CALL_X(typeid);
	CALL_X(addressof);
	CALL_X(ref);
	CALL_X(crc);
	CALL_X(tuple);
	CALL_X(variant);
	CALL_X(optional);
	CALL_X(pool);



	CALL_X(scope_ptr);
	CALL_X(weak_ptr);
	CALL_X(intrusive_ptr);


	CALL_X(lexical_cast);

	CALL_X(format);
	CALL_X(next);
	CALL_X(value_initialized);

	CALL_X(any);
	CALL_X(any2);
	CALL_X(any_msg);
	CALL_X(array);
	CALL_X(array1);
	CALL_X(array2);
	CALL_X(array3);
	CALL_X(array4);

	CALL_X(bind);
	CALL_X(mem_fn);
	CALL_X(bind_2);
	CALL_X(bind_2_1);
	CALL_X(bind_null);
	CALL_X(functional);
	CALL_X(fucntion1);


	CALL_X(tokenizer);
	CALL_X(regex);
	CALL_X(regix2);


	//CALL_X(progress_display); //
	//CALL_X(thread); //멀티 스레드 셈플

	CALL_X(path);
	//CALL_X(filesystem0);
	//CALL_X(simple_ls);

	CALL_X(lambda);
	CALL_X(lambda2);

	CALL_X(signal);
	CALL_X(signal_slot_arg);

	CALL_X(graph_visitor);

	//CALL_X(property_map);

	CALL_X(base_from_member);

	CALL_X(random);
	//CALL_X(random2);
	CALL_X(random3);

	CALL_X(graph);

	//CALL_X(spirit);// 계산기 파서
	CALL_X(parse_numbers); // 23, 23.3 , 2654 같은 숫자리스트 파싱샘플
	CALL_X(calc_plain); //표준 예제 spirit calc
	CALL_X(sprit_subrule_calc);
	CALL_X(spirit_roman_numerals);
	CALL_X(spirit_calc_jp1);
	CALL_X(spirit_calc_jp2);

	//CALL_X(main);
	//CALL_X(main);
	//CALL_X(main);
	//CALL_X(main);
	//CALL_X(main);
	//CALL_X(main);
	//CALL_X(main);
	//CALL_X(main);
	//CALL_X(main);
	//CALL_X(main);
	//CALL_X(main);
	//CALL_X(main);
	//CALL_X(main);
	//CALL_X(main);
	//CALL_X(main);
	//CALL_X(main);
	//CALL_X(main);
	//CALL_X(main);
#endif
	return 0;
}
