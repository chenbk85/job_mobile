//
//  main.cpp
//  DualGoServer
//
//  Created by jin young park on 11. 11. 23..
//  Copyright (c) 2011년 집. All rights reserved.
//

#include <stdlib.h>
#include <iostream>

#include "game/game.h"

#include "baseball_user.h" 
#include "baseball_room.h" 
#include "proto.h"
#include "common/jILog.h"
#include "stdafx.h"
#include "../MOB_lib/nMOB.h"
#include "PT_BaseballServer.pb.h"



#define BOOST_TEST_MODULE BaseballServerGame
#include <boost/test/unit_test.hpp>
using namespace boost::unit_test_framework;

BOOST_AUTO_TEST_CASE(TEST)
{
	BOOST_CHECK(1);                          // assert 와 같은놈 참이면 pass 거짓이면 fail
	BOOST_CHECK_EQUAL(1,1);                  // 두 인자 동등비교. 이게 굳이 필요한가? BOOST_CHECK 하나로 충분한거 아닌가
	// 어쨌건 요런놈들을 test tools 라고 하는데 boost/test/test_tools.hpp 를 읽어보자.

	int i = 0;
	BOOST_TEST_CHECKPOINT("before divzero"); // 신기하구나. 시그널이나 트랩등이 걸린 경우는 가장 마지막 CHECKPOINT 를 찍어준다. 의심나는 구간 앞에 박아두면 된다.
	i = 100 / i;

	BOOST_TEST_MESSAGE("you sucks");         // 찍혀야 하는거 아닌가 안찍히네
	// 아.. 이놈을 빌드해서 나온 파일을 실행할때 --log_level=all 이란 옵션을 주면 된다.
	// 또는 환경변수에 BOOST_TEST_LOG_LEVEL=all 를 줘도 같은 효과.
	// boost test 의 문서중 parameters 라는 부분을 찾아 읽어보자.
}


MSG::RoomLogic* create_room_logic()
{
	return new baseball::Room();
}

void destroy_room_logic(MSG::RoomLogic* room_logic)
{
	delete room_logic;
}

bool on_server_initialize() { return true; }

void on_server_deinitialize() { }


void _jConsolePrinterFunc( tcstr szString,bool bAdd )
{
	std::string buffer;
	boost::posix_time::ptime now_ptime = boost::posix_time::microsec_clock::local_time();
	buffer = boost::posix_time::to_simple_string(now_ptime);
	buffer = buffer.substr(5,buffer.size()-5-7);
	buffer += " ";
	buffer += ">";

	if(bAdd)
	{
		cout << buffer << szString;
	}
	else
	{
		cout << endl << buffer << szString;
	}
}

void Init_BasebllServer()
{
	string sOrgLogFile = nMech::nInterface::g_pjILog->GetFileName();
	fname_t szLogFile;
	jt_sprintf(szLogFile, "%s_game", sOrgLogFile.c_str());
	nMech::nInterface::g_pjILog->SetFileName(szLogFile);

	void _jConsolePrinterFunc( tcstr szString,bool bAdd );
	GetjILog()->SetPrinter(_jConsolePrinterFunc);

	LOG_DEBUG("szLogFile = " << szLogFile);

	LOG_DEBUG("LOG on");
	LOG_INFO("initizlise server...");	
	jRETURN(nG::g_DocApp.LoadFile("../etc/xml/baseball.xml" ) != false );

	nG::g_ECV.load_xml();
	nG::g_ECV.print_all();

	Load_Common_CSV();
}



int
main(int argc, const char* argv[])
{
	// X(PACKET이름		,허용가능한 반복시간)
#	define for_each_Client_BaseballServer_REPEAT_TIME(X)\
	X(x2bs_echo			,1000)\
	X(x2bs_echo2		,1000)\
	X(req_chat			,1000)\

#	define __set_repeat_time(PACKET,TIME_MSEC) \
	nMOB::g_allowed_repeat_time[Client_BaseballServer_Type_##PACKET]=TIME_MSEC;

	for_each_Client_BaseballServer_REPEAT_TIME(__set_repeat_time);


	void Init_BasebllServer();Init_BasebllServer();

    return MSG::main(argc, argv);
}

