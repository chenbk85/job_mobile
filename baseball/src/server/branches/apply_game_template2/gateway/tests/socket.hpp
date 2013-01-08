#ifndef __NWM_MSG_GATEWAY_TEST_SOCKET_HPP__
#define __NWM_MSG_GATEWAY_TEST_SOCKET_HPP__

#include <sys/socket.h>
#include <netinet/in.h>


class Socket
{
public:
  Socket();
  virtual ~Socket();

  bool create();

  bool bind(unsigned short port);

  bool listen();

  bool accept(Socket&);

  bool connect(const char* host, unsigned short port, int timeout = 0);

  bool send(void* data, int length);

  int recv(void* buffer, int max_length);

  void set_non_blocking(bool enable);

  bool is_valid() const
  {
    return socket_ != -1;
  }

  void close();

  int handle() { return socket_; }

private:
  int                   socket_;
  struct sockaddr_in    addr_;
  bool                  blocking_;
};

#endif
