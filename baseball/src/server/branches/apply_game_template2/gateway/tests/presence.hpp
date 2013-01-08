#ifndef __TEST_PRESENCE_HPP__
#define __TEST_PRESENCE_HPP__

#include <iostream>

#include "server.hpp"


class Presence: 
  public Server
{
protected:
  class GSession: public Server::Session
  {
  public:
    virtual bool dispatch(unsigned char* packet, std::size_t length);
  };

public:
  Presence();

  virtual ~Presence();


  void start()
  {
    std::cerr << "PRESENCE 서버 시작 PORT(6000)\n";

    Server::start(6000);
  }

  void stop()
  {
    Server::stop();

    std::cerr << "PRESENCE 서버 종료\n";
  }

protected:
  virtual Server::Session* create_session();  

};

#endif
