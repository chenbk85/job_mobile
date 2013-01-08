// test_template.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

//FUNC(FULLNAME,NAME)
#define for_each_asio_test(X)\
	X(com_maestia_yd_monitor,cyd)\
	X(maestia_yd_monitor_client,ydc)\
	X(main_async_tcp_echo_server,ats)\
	X(main_async_udp_echo_server,aus)\
	X(main_blocking_tcp_echo_client,btc)\
	X(main_blocking_tcp_echo_server,bts)\
	X(main_blocking_udp_echo_client,buc)\
	X(main_blocking_udp_echo_server,bus)\


int main(int argc, CHAR* argv[])
{
	if(argc <3)
	{
		#define prt12(FULLNAME,NAME) printf(".exe  <%s:%s> <port>\n",#NAME, #FULLNAME);
		for_each_asio_test(prt12);
		return 0;
	}
	astring sArg = argv[1];

	#define call12(FULLNAME,NAME) else if(sArg==#NAME){\
	int FULLNAME(int argc, char* argv[]); \
	printf(#FULLNAME " CALL!!\n");\
	FULLNAME(argc-1,argv+1);\
	}

	if(0){}
	for_each_asio_test(call12);
	return 0;
}

