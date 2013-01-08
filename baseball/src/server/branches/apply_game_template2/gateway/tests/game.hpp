#ifndef __TEST_GAME_HPP__
#define __TEST_GAME_HPP__

#include <iostream>
#include "server.hpp"

class Game:
  public Server
{
protected:
  class GSession: public Server::Session
  {
  public:
    virtual bool dispatch(unsigned char* packet, std::size_t length);
  };

public:
  Game();

  void start()
  {
    std::cerr << "GAME 서버 시작 PORT(6020)\n";
    Server::start(6020);
  }

  void stop()
  {
    Server::stop();
    std::cerr << "GAME 서버 종료\n";
  }

protected:
  virtual Server::Session* create_session();

};

#endif
