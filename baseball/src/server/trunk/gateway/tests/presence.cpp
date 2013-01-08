#include "presence.hpp"

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define ENABLE_MSG_TRACE
#include "protocol/dump.hpp"

#include "protocol/presence.pb.h"

#include <google/protobuf/io/zero_copy_stream_impl.h>

using namespace std;
using google::protobuf::io::ArrayInputStream;


/* -------------------------------------------------------------------------- */

Presence::Presence():
  Server()
{
}

/* -------------------------------------------------------------------------- */

Presence::~Presence()
{
}

/* -------------------------------------------------------------------------- */

Server::Session* 
Presence::create_session()
{
  return new Presence::GSession();
}

/* -------------------------------------------------------------------------- */

bool
Presence::GSession::dispatch(unsigned char* packet, std::size_t length)
{
  cerr << "PRESENCE\n";

  ArrayInputStream input(packet, length);

  PReqProtocol request;

  if (!request.ParseFromZeroCopyStream(&input))
  {
    return false;
  }
  
  MSG::DumpPReqProtocol(request);

  PAnsProtocol answer;

  switch(request.command())
  {
  case LOGIN:
    {
      answer.set_command(LOGIN);
      answer.set_seqid(request.seqid());
      answer.set_gameid(request.gameid());
      answer.set_svcid(request.svcid());
      answer.set_category(request.category());
      answer.set_result(true);
      answer.set_status("L");
      answer.set_detached(false);
      answer.set_ip("");
      answer.set_port(0);
      answer.set_roomid(0);
    }
    break;
  case LOGOUT:
    {
      answer.set_command(LOGOUT);
      answer.set_seqid(request.seqid());
      answer.set_gameid(request.gameid());
      answer.set_svcid(request.svcid());
      answer.set_category(request.category());
      answer.set_result(true);
      answer.set_status("U");
      answer.set_detached(false);
      answer.set_ip("");
      answer.set_port(0);
      answer.set_roomid(0);
    }
    break;
  case GAMEENTER:
    {
      answer.set_command(GAMEENTER);
      answer.set_seqid(request.seqid());
      answer.set_gameid(request.gameid());
      answer.set_svcid(request.svcid());
      answer.set_category(request.category());
      answer.set_result(true);
      answer.set_status("G");
      answer.set_detached(false);
      answer.set_ip("localhost");
      answer.set_port(6020);
      answer.set_roomid(10);
    }
    break;
  case GAMELEAVE:
    {
      answer.set_command(GAMELEAVE);
      answer.set_seqid(request.seqid());
      answer.set_gameid(request.gameid());
      answer.set_svcid(request.svcid());
      answer.set_category(request.category());
      answer.set_result(true);
      answer.set_status("L");
      answer.set_detached(false);
      answer.set_ip("");
      answer.set_port(0);
      answer.set_roomid(0);
    }
    break;
  case DETACH:
    return false;
  case PLUG:
    return false;
  case CATEGORY:
    {
      answer.set_command(CATEGORY);
      answer.set_seqid(request.seqid());
      answer.set_gameid(request.gameid());
      answer.set_svcid(request.svcid());
      answer.set_category(request.category());
      answer.set_result(true);
      answer.set_status("L");
      answer.set_detached(false);
      answer.set_ip("");
      answer.set_port(0);
      answer.set_roomid(0);
      answer.set_info("10,20,30,40,50");
    }
    break;

  default:
    return false;
  }

  MSG::DumpPAnsProtocol(answer);
  send(answer);

  return true;  
}

/* -------------------------------------------------------------------------- */


