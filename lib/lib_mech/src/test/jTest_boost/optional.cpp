
#include <stdafx.h>
#include <boost/optional.hpp>
using namespace std;
using namespace boost;

// ��x �� ���� �ʴ� �ִ��� ������ �����ִ� �Լ�
// �����϶��� optional<>�� false���� ������.
optional<int> sqrt( int x )
{
	if( x < 0 )
		return optional<int>();//���ʱ�ȭ�� int�� ����
	int i;
	for(i=0; i*i<=x; ++i) {}
	return optional<int>(i-1);//�ʱ�ȭ�� int���� ����
}

int main_optional()
{
	for(int j=-5; j<=5; ++j)
	{
		optional<int> x = sqrt(j);
		if( x ) // int������ ���� �����ϰ� �ִ��� üũ
			cout << j << " => " << *x << endl; 
			//�ùٸ��� dereferenceó���� ���� ������
		else
			cout << j << " => " << "invalid" << endl;
	}
	return 0;
}

/*
��¿�
invalid
invalid
invalid
invalid
invalid
0
1
1
1
2
2

*/
