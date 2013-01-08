#ifndef __NWM_MSG_GATEWAY_TEST_SERVER_HPP__
#define __NWM_MSG_GATEWAY_TEST_SERVER_HPP__

#include "socket.hpp"

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/container/map.hpp>

#include <google/protobuf/message_lite.h>

class Server: 
  public Socket
{
protected:
  enum
  {
    MAX_CONNECTIONS = 64,
  };

protected:
  class Session: 
    public Socket
  {
  public:
    Session(); 

    virtual bool read();
    virtual bool dispatch(unsigned char* packet, std::size_t length) = 0;

    void send(::google::protobuf::MessageLite& message);

    unsigned char read_buffer_[4096];
    unsigned int read_buffer_length_;

    unsigned char write_buffer_[4096];
  };

protected:
  typedef boost::shared_ptr<boost::thread> thread_sptr;

public:
  Server();
  virtual ~Server();

  void start(unsigned short port)
  {
    std::cerr << "server::start()\n";

    port_ = port;

    thread_ = thread_sptr(new boost::thread(boost::bind(&Server::run, this)));
  }

  void stop()
  {
    std::cerr << "server::stop()\n";

    shutdown_ = true;
    thread_->join();
  }


protected:
  virtual Session* create_session() = 0;

private:
  void run();


private:
  bool          shutdown_;
  thread_sptr   thread_;

  Session*      sessions_[MAX_CONNECTIONS];

  unsigned short port_;
};

#endif
