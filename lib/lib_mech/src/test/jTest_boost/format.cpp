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

	// printf(와)과 같은 서식도OK.
	// %05d:0묻어로5자리수의 정수 %x:16진표기 %f:부동 소수점수(실수) %%:%그것
	cout <<  boost::format("%05d %x %f %%") % 200 % 255 % 3.33 << endl;

	// %2%와 %1%를 역순에 사용하는 일도 가능
	cout <<	  boost::format("%2% %1%") % "hello" % 100	<< endl;

	// %N$...차례 지정과 출력 형식 지정 샘플
	// %04x: 0을 앞에 붙이는 4자리의 16진수 , %s:문자열
	cout	<<	  boost::format("%2$04x %1$s") % "hello" % 254
			<< endl;

	/* 출력
				main_format call!!!
				hello 100
				00200 ff 3.330000 %
				100 hello
				00fe hello
	*/
	return 0;
}



