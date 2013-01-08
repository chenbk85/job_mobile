#include "client.hpp"
#include "presence.hpp"
#include "game.hpp"

#include "protocol/ug.pb.h"

#include "../gameLogic.pb.h"
#include "../../game/proto.h"

#include <iostream>

int 
main(int argc, char* argv[])
{
#ifdef jUSE_DIRECT_CONNECT_TO_GAMESERVER
  Game g;
  Presence p;
#endif
  Client c;

  std::cout << "CONNECT 및 CLOSE 테스트\n";
#ifdef jUSE_DIRECT_CONNECT_TO_GAMESERVER
  g.start();
  p.start();
#endif

  std::cout << " * 접속시도 -> ";

  if (!c.connect("localhost", 12000))
  {
    std::cout << "접속 실패\n";  
    return 0;
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
    c.make_reqconnect(request, member_info);
    c.send(request);
  }

  // 응답 대기
  std::cout << " * CONNECT 응답 대기\n";
  {
    UAnsProtocol answer;
    c.wait(answer);
    assert(answer.type() == UAnsProtocol::UANSCONNECT);
  }

  std::cout << " * AUTOJOIN 정보 송신\n";
  {
    UReqProtocol request;
    c.make_reqautojoin(request);
    c.send(request);
  }

  std::cout << " * AUTOJOIN 응답 대기\n";
  {
    UAnsProtocol answer;
    c.wait(answer);
    assert(answer.type() == UAnsProtocol::UANSAUTOJOIN);
  }

  std::cout << " * GAME 정보 송신\n";
  {
    Client_BaseballServer sendMsgG;
    sendMsgG.set_type(Client_BaseballServer::req_ping1);
    s_req_ping1* req = sendMsgG.mutable_m_req_ping1();
	req->set_type(1111);
	req->set_msg("asdf");

	UReqProtocol sendMsgU;
    sendMsgU.set_type(UReqProtocol::GLREQGAMEPROTOCOL);
    sendMsgG.SerializeToString(sendMsgU.mutable_reqgameprotocol());
    c.send(sendMsgU);
  }

  std::cout << " * GAME 응답 대기\n";
  {
    UAnsProtocol answer;
    c.wait(answer);
    assert(answer.type() == UAnsProtocol::GLANSGAMEPROTOCOL);
    BaseballServer_Client message;
    message.ParseFromString(answer.ansgameprotocol());

    switch(message.type())
    {
    case BaseballServer_Client::ans_pong1:
		{
			const s_ans_pong1& ans = message.m_ans_pong1();
			std::cout << "\n\n\n case BaseballServer_Client::ans_pong1: " << ans.msg() << "\n\n\n";
		}
      break;
    default:
		std::cout << "\n알수 없는 패킷 \n";
      break;
    }
  }

  std::cout << " * LEAVEGAME 정보 송신\n";
  {
    UReqProtocol request;
    c.make_reqleavegame(request, 100, true);
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
#ifdef jUSE_DIRECT_CONNECT_TO_GAMESERVER
  g.stop();
  p.stop();
#endif

  return 0;
}
