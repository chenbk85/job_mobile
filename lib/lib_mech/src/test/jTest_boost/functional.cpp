#include <stdafx.h>
 
bool is_even( int x )
{
	cout << "is_even = " << x <<endl;
	if(x%7 == 0)
		cout << "is_event ok: " << x<<endl;
    return x%2 == 0;
}
 
int main_functional()
{
		//std::�� <functional>�ش��� �ִ� ���� ��ƿ �Լ���ü�� ����.
		//������ �������� ���� ���ŷο��� �ذ�.
       int arr[] = {1,2,3,4,5,6,7,8,9,10};
 
       // ���� �Լ���std::not1�� �ǳ� �ַ��� ptr_fun�� �ʿ�
       // �� std::find_if( arr, arr+10, std::not1(is_even) );
       std::find_if( arr, arr+10, std::not1(std::ptr_fun(is_even)) );
 
       // boost::not1�� �״�� �ǳ��� ���� �ִ�
       std::find_if( arr, arr+10, boost::not1(is_even) );
 
       return 0;
}
