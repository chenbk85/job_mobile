#include "client.hpp"
#include "presence.hpp"
#include "game.hpp"

#include "protocol/ug.pb.h"

#include "../../game/gameLogic.pb.h"

#include "protocol/dump.hpp"

#include <iostream>

int 
main(int argc, char* argv[])
{
  Game g;
  Presence p;
  Client c;

  std::cout << "TEST CONNECT\n";

  g.start();
  p.start();

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
    MSG::DumpUAnsProtocol(answer);
    assert(answer.type() == UAnsProtocol::UANSCONNECT);
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

  g.stop();
  p.stop();

  return 0;
}
