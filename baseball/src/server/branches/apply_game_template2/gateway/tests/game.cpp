#include "game.hpp"

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define ENABLE_MSG_TRACE
#include "protocol/dump.hpp"

#include "protocol/game.pb.h"
#include "../../game/proto.h"
#include "../../game/excel_baseball_table_db.pb.cc"
#include "../../game/gameLogic.pb.cc"
#include "../../game/PT_BaseballServer.pb.cc"



#include <google/protobuf/io/zero_copy_stream_impl.h>


using namespace std;
using google::protobuf::io::ArrayInputStream;

/* -------------------------------------------------------------------------- */

Game::Game():
  Server()
{
}

/* -------------------------------------------------------------------------- */

Server::Session* 
Game::create_session()
{
  return new Game::GSession();
}

/* -------------------------------------------------------------------------- */

bool
Game::GSession::dispatch(unsigned char* packet, std::size_t length)
{
  cerr << "GAME\n";

  ArrayInputStream input(packet, length);

  GReqProtocol request;

  if (!request.ParseFromZeroCopyStream(&input))
  {
    return false;
  }

  MSG::DumpGReqProtocol(request);

  GAnsProtocol answer;

  switch(request.type())
  {
  case GReqProtocol_Type_GREQSTATUS:
  case GReqProtocol::NONE:
    break;

  case GReqProtocol::GREQGAMEENTER:
    {
      answer.set_type(GAnsProtocol::GANSGAMEENTER);
      GameRoomInfo room_info;
     
     #if 0
      // 룸 정보 설정
      room_info.set_roomid(10);
      room_info.set_pointmoney(100);
     #endif

      // 원래는 사용자 정보도 추가로 보내줘야 함
     
      GAnsGameEnter* enter = answer.mutable_ansgameenter();
      room_info.SerializeToString(enter->mutable_gameroominfo());
    }
    break;

  case GReqProtocol::GREQGAMELEAVE:
     {
      answer.set_type(GAnsProtocol::GANSGAMELEAVE);
      GAnsGameLeave* leave = answer.mutable_ansgameleave();

      leave->set_gameid(100);
      leave->set_ntype((GAnsGameLeave_KICK_TYPE)1);
    }
    break;

  case GReqProtocol::GREQDETACH:
    return false;

  case GReqProtocol::GREQPLUG:
    return false;

  case GReqProtocol::GLREQGAMEPROTOCOL:
    {
      GAnsProtocol request;

      request.set_type(GAnsProtocol::GDBREQ);

      ReqDB* query = request.mutable_reqdb();

      query->set_seq(0);
      query->set_query("select * from player");

      send(request);
      MSG::DumpGAnsProtocol(request);

      return true;

#if 0
      GLReqGameProtocol game_request;

      game_request.ParseFromString(request.reqgameprotocol());

      assert(game_request.type() == GameReqProtocol::TEST_PACKET);
      
      answer.set_type(GAnsProtocol::GLANSGAMEPROTOCOL);

      GameAnsProtocol game_answer;
      game_answer.set_type(GameAnsProtocol::TEST_PACKET);
      game_answer.SerializeToString(answer.mutable_ansgameprotocol());
#endif
    }
    break;

  case GReqProtocol::GDBANS:
    break;
  }

  MSG::DumpGAnsProtocol(answer);
  send(answer);

  return true;
}

/* -------------------------------------------------------------------------- */



