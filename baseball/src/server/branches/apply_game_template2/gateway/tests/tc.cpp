#include "client.hpp"
#include "presence.hpp"
#include "game.hpp"

#include "protocol/ug.pb.h"

#include "../../game/gameLogic.pb.h"

#include <iostream>

#include <boost/test/unit_test.hpp>



using namespace boost::unit_test;


void test_case1();


test_suite*
init_unit_test_suite(int argc, char* argv[])
{
    test_suite* baseball = BOOST_TEST_SUITE("Baseball Gateway Test");

    baseball->add(BOOST_TEST_CASE(&test_case1), 0);

    framework::master_test_suite().add(baseball);

    return 0;
}


void test_case1()
{
  Client c;

  std::cout << "CHANNEL 테스트\n";

  std::cout << " * 접속시도 -> ";

  if (!c.connect("localhost", 12000))
  {
    std::cout << "접속 실패\n";  
    return;
  }

  std::cout << "접속 성공\n";

  // 접속 정보 송신
  std::cout << " * CONNECT 정보 송신\n";
  {
    MemberInfo member_info;

    member_info.set_game_id(100);
    member_info.set_avatar_url("test");
    member_info.set_nick_name("test");
    member_info.set_gender_option(true);

    UReqProtocol request;
  
    request.set_type(UReqProtocol::UREQCONNECT);
    UReqConnect* connect = request.mutable_reqconnect();
    connect->set_svcid(1);
    connect->set_gameid(member_info.game_id());
    connect->set_lastclosetime(time(0));

    Version version;
    version.set_major(0);
	version.set_protocol(1204010);
	version.set_framework(0);
	version.set_service(0);

    connect->mutable_version()->CopyFrom(version);
    connect->mutable_memberinfo()->CopyFrom(member_info);

    c.send(request);
  }

  // 응답 대기
  std::cout << " * CONNECT 응답 대기\n";
  {
    UAnsProtocol answer;
    c.wait(answer);
    assert(answer.type() == UAnsProtocol::UANSCONNECT);
  }

  std::cout << " * INFO 정보 송신\n";
  {
    UReqProtocol request;
    request.set_type(UReqProtocol::UREQINFO);
    c.send(request);
  }

  std::cout << " * INFO 응답 대기\n";
  {
    UAnsProtocol answer;
    c.wait(answer);
    assert(answer.type() == UAnsProtocol::UANSINFO);
  }

  std::cout << " * CHANNEL 정보 송신\n";
  {
    UReqProtocol request;
    request.set_type(UReqProtocol::UREQCHANNEL);
    c.send(request);
  }

  std::cout << " * CHANNEL 응답 대기\n";
  {
    UAnsProtocol answer;
    c.wait(answer);
    assert(answer.type() == UAnsProtocol::UANSCHANNEL);
  }

  usleep(500);


  std::cout << " * AUTOJOIN 정보 송신\n";
  {
    UReqProtocol request;
	
   	request.set_type(UReqProtocol::UREQAUTOJOIN);
    UReqAutoJoin* autojoin = request.mutable_reqautojoin();
    autojoin->set_categoryid(0);
    autojoin->set_channelid(0);

    c.send(request);
  }

  std::cout << " * AUTOJOIN 응답 대기\n";
  {
    UAnsProtocol answer;
    c.wait(answer);
    assert(answer.type() == UAnsProtocol::UANSAUTOJOIN);
  }

  
  std::cout << " * LEAVEGAME 정보 송신\n";
  {
    UReqProtocol request;
    request.set_type(UReqProtocol::UREQLEAVEGAME);
    UReqLeaveGame* leave = request.mutable_reqleavegame();
    leave->set_gameid(100);
    leave->set_kick(true);	
    c.send(request);
  }

  std::cout << " * LEAVEGAME 응답 대기\n";
  {
    UAnsProtocol answer;
    c.wait(answer);
    assert(answer.type() == UAnsProtocol::UANSLEAVEGAME);
  }

  usleep(500);

  
  std::cout << " * CLOSE 정보 송신\n";
  {
    UReqProtocol request;
    c.make_reqclose(request);
    c.send(request);
  }

  std::cout << " * CLOSE 응답 대기\n";
  {
    UAnsProtocol answer;
    c.wait(answer);
    assert(answer.type() == UAnsProtocol::UANSCLOSE);
  }

  c.disconnect();
  std::cout << " * 접속 해제\n";

  usleep(100);

//  g.stop();
//  p.stop();
}



