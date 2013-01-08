
#include <stdafx.h>
#include <iostream>

using namespace std;

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

#define CALL_X(X) printf("\n\n %s call!!! \n",#X);int X(); X();
int main()
{
	_AAA_ a ,b;
	int int_val = 1;

	a.m_int = 1;
	b.m_bool_p = reinterpret_cast<bool* > (&int_val);


	//CALL_X(main_serialization);

	//사족 util
	CALL_X(main_typeid);
	CALL_X(main_addressof);
	CALL_X(main_ref);
	CALL_X(main_crc);
	CALL_X(main_tuple);
	CALL_X(main_variant);
	CALL_X(main_optional);
	CALL_X(main_pool);



	CALL_X(main_scope_ptr);
	CALL_X(main_weak_ptr);
	CALL_X(main_intrusive_ptr);


	CALL_X(main_lexical_cast);

	CALL_X(main_format);
	CALL_X(main_next);
	CALL_X(main_value_initialized);

	CALL_X(main_any);
	CALL_X(main_any2);
	CALL_X(main_any_msg);
	CALL_X(main_array);
	CALL_X(main_array1);
	CALL_X(main_array2);
	CALL_X(main_array3);
	CALL_X(main_array4);

	CALL_X(main_bind);
	CALL_X(main_mem_fn);
	CALL_X(main_bind_2);
	CALL_X(main_bind_2_1);
	CALL_X(main_bind_null);
	CALL_X(main_functional);
	CALL_X(main_fucntion1);


	CALL_X(main_tokenizer);
	CALL_X(main_regex);
	CALL_X(main_regix2);


	//CALL_X(main_progress_display); //
	//CALL_X(main_thread); //멀티 스레드 셈플

	CALL_X(main_path);
	CALL_X(main_filesystem0);
	CALL_X(main_simple_ls);

	CALL_X(main_lambda);
	CALL_X(main_lambda2);

	CALL_X(main_signal);
	CALL_X(main_signal_slot_arg);

	CALL_X(main_graph_visitor);

	CALL_X(main_property_map);

	CALL_X(main_base_from_member);

	CALL_X(main_random);
	//CALL_X(main_random2);
	CALL_X(main_random3);

	CALL_X(main_graph);
	
	//CALL_X(main_spirit);// 계산기 파서
	CALL_X(main_parse_numbers); // 23, 23.3 , 2654 같은 숫자리스트 파싱샘플
	CALL_X(main_calc_plain); //표준 예제 spirit calc
	CALL_X(main_sprit_subrule_calc);
	CALL_X(main_spirit_roman_numerals);
	CALL_X(main_spirit_calc_jp1);
	CALL_X(main_spirit_calc_jp2);

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
	
	return 0;
}
