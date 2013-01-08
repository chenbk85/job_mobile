#ifndef __TEST_CLIENT_HPP__
#define __TEST_CLIENT_HPP__


#include <boost/system/system_error.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/noncopyable.hpp>

#include "protocol/ug.pb.h"
#include "../../game/gameLogic.pb.h"

#include "protocol/dump.hpp"

#include "socket.hpp"

class Client:
  private boost::noncopyable,
  public Socket
{
  enum
  {
    BUFFER_SIZE = 8192,
  };
public:
  Client();

  virtual ~Client();

public:
  bool connect(const char *host, 
               unsigned short port,
               int timeout = 10);

  void disconnect();

  void send(UReqProtocol& request);

  bool wait(UAnsProtocol& answer, int timeout = 10);

public:
  void make_reqconnect(UReqProtocol& request,
                       MemberInfo& member_info)
  {
    request.set_type(UReqProtocol::UREQCONNECT);
    UReqConnect* connect = request.mutable_reqconnect();
    connect->set_svcid(1);
    connect->set_gameid(member_info.game_id());
    connect->set_lastclosetime(time(0));

    Version version;
    version.set_major(1);
    version.set_protocol(1204010);
    version.set_framework(0);
	version.set_service(2);

    connect->mutable_version()->CopyFrom(version);
    connect->mutable_memberinfo()->CopyFrom(member_info);
  }

  void make_reqinfo(UReqProtocol& request)
  {
    request.set_type(UReqProtocol::UREQINFO);
  }

  void make_reqchannel(UReqProtocol& request)
  {
    request.set_type(UReqProtocol::UREQCHANNEL);
  }

  void make_reqclose(UReqProtocol& request)
  {
    request.set_type(UReqProtocol::UREQCLOSE);
  }

  void make_reqautojoin(UReqProtocol& request)
  {
    request.set_type(UReqProtocol::UREQAUTOJOIN);
    UReqAutoJoin* autojoin = request.mutable_reqautojoin();
    autojoin->set_categoryid(0);
    autojoin->set_channelid(0);
  }

  void make_reqleavegame(UReqProtocol& request,
                         int gameid, bool kick)
  {
    request.set_type(UReqProtocol::UREQLEAVEGAME);
    UReqLeaveGame* leave = request.mutable_reqleavegame();
    leave->set_gameid(gameid);
    leave->set_kick(kick);
  }

  void make_sample_gameprotocol(UReqProtocol& request)
  {
#if 0
    GLReqGameProtocol game_request;

    request.set_type(UReqProtocol::GLREQGAMEPROTOCOL);

    game_request.set_type(GLReqGameProtocol::req_ping);
    game_request.mutable_m_req_ping()->set_usn(1111);
    game_request.SerializeToString(request.mutable_reqgameprotocol());
#endif
  }

private:
  unsigned char buffer_[BUFFER_SIZE];
  std::size_t read_length_;
};

#endif
