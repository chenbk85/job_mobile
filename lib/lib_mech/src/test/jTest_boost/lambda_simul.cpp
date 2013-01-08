#include <stdafx.h>
#if 0
// 
// 입출력은 모두int 의 1 변수 함수를 보통 산술식의 
// 형태로 기술할 수 있도록 하는 라이브러리. 
// lambda (이)나 phoenix (을)를 보고 스스로도 간단한 것 
// (을)를 만들어 보고 싶어졌으므로, 시험삼아 만들었습니다. 
// 

namespace petit_fex 
{
	// int 형태 정수 ----------------------------------- 
	struct val 
	{
		val(int v) : v_(v) 
		{
		} 
		const int v_;
		int operator()(int t) const 
		{
			return v_;
		} 



	};

	// int 형 => val 형태에의 필터 ------------------ 
	template <typename V> 	struct tr 	{		typedef V typ; 	};
	template<>					struct tr 	{		typedef val typ;	};

	// 변수 ---------------------------------------- 
	struct var 
	{
		int operator()(int t) const 
		{
			return t;
		} 

	};

	// 단항 연산자 ---------------------------------- 

#define unary_op( NAME, OP ) 
	template 
	struct NAME 
	{
		NAME(A a) : a_(a) 
		{
		} A a_;
		int operator()(int t) 
		{
			return OP a_(t);
		} 

	};
	template NAME::typ> operator OP ( A a ) 
	{
		return NAME::typ>(tr::typ(a));
	} unary_op( pf_not, ! ) unary_op( pf_neg, - ) unary_op( pf_inv, ~ ) 


#undef unary_op 
		// 2항연산자 ---------------------------------- 
#define binary_op( NAME, OP ) 
template 
	struct NAME 
	{
		NAME(A a, B b) : a_(a), b_(b) 
		{
		} A a_;
		B b_;
		int operator()(int t) 
		{
			return a_(t) OP b_(t);
		} 

	};
	template NAME::typ,tr::typ> operator OP (A a, B b) 
	{
		return NAME::typ,tr::typ> (tr::typ(a),tr::typ(b));
	} 
	binary_op( pf_plus, + ) 
	binary_op( pf_minus, - ) 
	binary_op( pf_mult, * ) 
	binary_op( pf_div, / ) 
	binary_op( pf_mod, % ) 
	binary_op( pf_lsft, << ) 
	binary_op( pf_rsft, >> ) 
	binary_op( pf_eq, == ) 
	binary_op( pf_neq, != ) 
	binary_op( pf_less, < ) 
	binary_op( pf_more, > ) 
	binary_op( pf_lesse, <= ) 
	binary_op( pf_moree, >= ) 
	binary_op( pf_and, && ) 
	binary_op( pf_or, || ) 
	binary_op( pf_band, & ) 
	binary_op( pf_bor, | ) 
	binary_op( pf_xor, ^ ) 

#undef binary_op 
} 

namespace 
{
	static petit_fex::var X;
} 

int main_test_lambda_sim()
{
	std::list<int> c(100);
	int i = 80;
	for_each(c.begin(),c.end() , _1 = i++);

	find_if( c.begin(), c.end(), 100<=X && X<=200 ); 
	int r = (X*5+X/3+2) (6); 
	return 0;
}
#endif