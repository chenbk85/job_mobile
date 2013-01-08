#include <stdafx.h>
#if 0
//
// �����Ϥ�����int�Σ��ѿ��ؿ������̤λ��Ѽ���
// ���ǵ��ҤǤ���褦�ˤ���饤�֥�ꡣ
//  lambda �� phoenix �򸫤Ƽ�ʬ�Ǥ��ñ�ʤ��
// ���äƤߤ����ʤä��Τǡ���˺��ޤ�����
//

namespace petit_fex {

	// int����� -----------------------------------

	struct val {
		val(int v) : v_(v) {} const int v_;
		int operator()(int t) const { return v_; }
	};

	// int�� => val���ؤΥե���? ------------------

	template<typename V> struct tr      { typedef  V  typ; };
	template<>           struct tr<int> { typedef val typ; };

	// �ѿ� ----------------------------------------

	struct var {
		int operator()(int t) const { return t; }
	};

	// ñ��黻�� ----------------------------------

#define unary_op( NAME, OP )                   \
	template<typename A> struct NAME {           \
	NAME(A a) : a_(a) {} A a_;                 \
	int operator()(int t) { return OP a_(t); } \
	};                                           \
	template<typename A>                         \
	NAME<tr<A>::typ> operator OP ( A a ) {       \
	return NAME<tr<A>::typ>(tr<A>::typ(a));    \
	}

		unary_op( pf_not, ! )
		unary_op( pf_neg, - )
		unary_op( pf_inv, ~ )

#undef unary_op

		// ���黻�� ----------------------------------

#define binary_op( NAME, OP )                        \
	template<typename A, typename B> struct NAME {     \
	NAME(A a, B b) : a_(a), b_(b) {} A a_; B b_;     \
	int operator()(int t) { return a_(t) OP b_(t); } \
	};                                                 \
	template<typename A, typename B>                   \
	NAME<tr<A>::typ,tr<B>::typ> operator OP (A a, B b) \
	{ return NAME<tr<A>::typ,tr<B>::typ>               \
	(tr<A>::typ(a),tr<B>::typ(b));      \
	}

		binary_op( pf_plus,   + )
		binary_op( pf_minus,  - )
		binary_op( pf_mult,   * )
		binary_op( pf_div,    / )
		binary_op( pf_mod,    % )
		binary_op( pf_lsft,  << )
		binary_op( pf_rsft,  >> )
		binary_op( pf_eq,    == )
		binary_op( pf_neq,   != )
		binary_op( pf_less,   < )
		binary_op( pf_more,   > )
		binary_op( pf_lesse, <= )
		binary_op( pf_moree, >= )
		binary_op( pf_and,   && )
		binary_op( pf_or,    || )
		binary_op( pf_band,   & )
		binary_op( pf_bor,    | )
		binary_op( pf_xor,    ^ )

#undef binary_op
}

namespace {
	static petit_fex::var X;
}

//
// example:
//   ��find_if( c.begin(), c.end(), 100<=X && X<=200 );
//   ��int r = (X*5+X/3+2) (6);
//

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