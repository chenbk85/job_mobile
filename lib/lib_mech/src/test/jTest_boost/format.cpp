/*
http://j2k.naver.com/j2k_frame.php/korean/www.kmonos.net/alang/boost/classes/format.html
*/
#include <stdafx.h>
#include <iostream>
#include <boost/format.hpp>
using namespace std;

int main_format()
{
	cout <<  boost::format("%1% %2%") % "hello" % 100 << endl;

	// printf(��)�� ���� ���ĵ�OK.
	// %05d:0�����5�ڸ����� ���� %x:16��ǥ�� %f:�ε� �Ҽ�����(�Ǽ�) %%:%�װ�
	cout <<  boost::format("%05d %x %f %%") % 200 % 255 % 3.33 << endl;

	// %2%�� %1%�� ������ ����ϴ� �ϵ� ����
	cout <<	  boost::format("%2% %1%") % "hello" % 100	<< endl;

	// %N$...���� ������ ��� ���� ���� ����
	// %04x: 0�� �տ� ���̴� 4�ڸ��� 16���� , %s:���ڿ�
	cout	<<	  boost::format("%2$04x %1$s") % "hello" % 254
			<< endl;

	/* ���
				main_format call!!!
				hello 100
				00200 ff 3.330000 %
				100 hello
				00fe hello
	*/
	return 0;
}



