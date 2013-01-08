#ifndef __TEST_CLIENT_HPP__
#define __TEST_CLIENT_HPP__


#include <boost/system/system_error.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/noncopyable.hpp>

#include "protocol/game.pb.h"
#include "proto.h"

#include "protocol/dump.hpp"

#include "socket.h"


class Gateway:
  private boost::noncopyable,
  public Socket
{
  enum
  {
    BUFFER_SIZE = 8192,
  };
public:
  Gateway();

  virtual ~Gateway();

public:
  bool connect(const char *host, 
               unsigned short port,
               int timeout = 10);

  void disconnect();

  void send(GReqProtocol& request);

  bool wait(GAnsProtocol& answer, int timeout = 10);

public:

private:
  unsigned char buffer_[BUFFER_SIZE];
  std::size_t read_length_;
};

#endif
