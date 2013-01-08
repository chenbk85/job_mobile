#include <stdafx.h>
#include <boost/operators.hpp>
/*
a > b (와)과 b < a (은)는 같은 의미로 하는 것이 많다고 생각합니다.
요컨데,operator< 를 정의하면 자동으로 operator> 도 정의됨.
operator== , operator!= ,  operator<= ,operator>= 의 관계도 자동정의됨. 
초소한의 연산자만은 정의하면 나머지를 boost::operators. 에 자동적으로 생성됨.
물론 각각의 자동 생성 되는 연산자를 커스텀하게 정의가능.

*/
class Int
	: private boost::operators<Int>
{
public:
	Int( int n = 0 ) : m_i( n ) {}

	bool operator<(const Int& x) const { return m_i < x.m_i; }
	bool operator==(const Int& x) const { return m_i == x.m_i; }
	Int& operator+=(const Int& x) { m_i+=x.m_i; return *this; }
	Int& operator-=(const Int& x) { m_i-=x.m_i; return *this; }
	Int& operator*=(const Int& x) { m_i*=x.m_i; return *this; }
	Int& operator/=(const Int& x) { m_i/=x.m_i; return *this; }
	Int& operator%=(const Int& x) { m_i%=x.m_i; return *this; }
	Int& operator|=(const Int& x) { m_i|=x.m_i; return *this; }
	Int& operator&=(const Int& x) { m_i&=x.m_i; return *this; }
	Int& operator^=(const Int& x) { m_i^=x.m_i; return *this; }
	Int& operator++()                 { ++m_i;       return *this; }
	Int& operator--()                 { --m_i;       return *this; }

private:
	int m_i;
};

int main_operators()
{
	Int i = 200 ,	j = 100;
	Int k = (i + j) * (j - i) % (i / 50);
	k++;	return 0;
}

