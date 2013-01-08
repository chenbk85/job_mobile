#include <stdafx.h>
#include <boost/operators.hpp>
/*
a > b (��)�� b < a (��)�� ���� �ǹ̷� �ϴ� ���� ���ٰ� �����մϴ�.
������,operator< �� �����ϸ� �ڵ����� operator> �� ���ǵ�.
operator== , operator!= ,  operator<= ,operator>= �� ���赵 �ڵ����ǵ�. 
�ʼ����� �����ڸ��� �����ϸ� �������� boost::operators. �� �ڵ������� ������.
���� ������ �ڵ� ���� �Ǵ� �����ڸ� Ŀ�����ϰ� ���ǰ���.

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

