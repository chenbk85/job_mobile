#include "socket.h"
#include <errno.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>
#include <arpa/inet.h>

/* -------------------------------------------------------------------------- */

Socket::Socket():
  socket_(-1),
  blocking_(true)
{
  memset(&addr_, 0, sizeof(addr_));
}

/* -------------------------------------------------------------------------- */

Socket::~Socket()
{
  close();
}

/* -------------------------------------------------------------------------- */

bool 
Socket::create()
{
  socket_ = ::socket(AF_INET, SOCK_STREAM, 0);

  if (!is_valid())
  {
    return false;
  }

  return true;
}

/* -------------------------------------------------------------------------- */

void 
Socket::close()
{
  if (is_valid())
  {
    ::close(socket_);
    socket_ = -1;
  }
}

/* -------------------------------------------------------------------------- */

bool 
Socket::bind(unsigned short port)
{
  if (!is_valid())
  {
    return false;
  }


  // TIME_WAIT - argh
  int on = 1;
  if (setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, 
                      (const char*)&on, sizeof(on)) == -1)
  {
    return false;
  }


  addr_.sin_family = AF_INET;
  addr_.sin_addr.s_addr = INADDR_ANY;
  addr_.sin_port = htons(port);

  int bind_return = ::bind(socket_, (struct sockaddr*)&addr_, sizeof(addr_));

  if ( bind_return == -1 )
  {
    return false;
  }

  return true;
}

/* -------------------------------------------------------------------------- */

bool 
Socket::listen() 
{
  if ( ! is_valid() )
  {
    return false;
  }

  int listen_return = ::listen(socket_, 5);


  if ( listen_return == -1 )
  {
    return false;
  }

  return true;
}

/* -------------------------------------------------------------------------- */

bool 
Socket::accept(Socket& new_socket)
{
  int addr_length = sizeof(new_socket.addr_);
  new_socket.socket_ = ::accept(socket_, 
                                (struct sockaddr*)&new_socket.addr_, 
                                (socklen_t *) &addr_length );

  if (new_socket.socket_ <= 0)
  {
    return false;
  }
  else
  {
    return true;
  }
}


/* -------------------------------------------------------------------------- */

bool
Socket::send(void* data, int length)
{
  int status = ::send(socket_, data, length, 0);
  if ( status == -1 )
  {
    return false;
  }
  else
  {
    return true;
  }
}

/* -------------------------------------------------------------------------- */

int 
Socket::recv(void* buffer, int max_length)
{
  int status = ::recv(socket_, buffer, max_length, 0);

  if ( status == -1 )
  {
    std::cerr << "status == -1   errno == " << errno << " in socket::recv\n";
  }
 
  return status; 
}

/* -------------------------------------------------------------------------- */

bool 
Socket::connect(const char* host, unsigned short port, int timeout)
{
  if (!is_valid()) 
  {
    return false;
  }

  addr_.sin_family = AF_INET;
  addr_.sin_port = htons(port);

  int status = inet_pton(AF_INET, host, &addr_.sin_addr);

  if (errno == EAFNOSUPPORT) 
  {
    return false;
  }

  if (blocking_)
  {
    status = ::connect(socket_, (struct sockaddr *)&addr_, sizeof(addr_));

    if ( status == 0 )
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    status = ::connect(socket_, (struct sockaddr *)&addr_, sizeof(addr_));

    if (status < 0 && errno != EINPROGRESS)
    {
      return false;
    }

    fd_set fd_w; 
    struct timeval tv; 
    tv.tv_sec = timeout;
    tv.tv_usec = 0L;

    FD_ZERO(&fd_w);
    FD_SET(socket_, &fd_w);

    status = select(FD_SETSIZE, NULL, &fd_w, NULL, &tv);
    if (status < 0)
    {
      // select() error
      return false;
    }

    if (status == 0)
    {
      // timeout
      return false;
    }

    int ret;
    int len;

    len = sizeof(ret); 
    status = getsockopt(socket_, SOL_SOCKET, SO_ERROR, &ret, (socklen_t*)&len); 
    if (status < 0) 
    {
      // getsockopt() error
      return false;
    }

    if (ret)
    {
      return false;
    }

    return true;
  }
}

/* -------------------------------------------------------------------------- */

void 
Socket::set_non_blocking(bool enable)
{
  int opts;

  opts = fcntl(socket_, F_GETFL); 
  if ( opts < 0 )
  {
    return;
  }

  blocking_ = !enable;

  if (enable)
  {
    opts = (opts | O_NONBLOCK);
  }
  else
  {
    opts = (opts & ~O_NONBLOCK);
  }

  fcntl(socket_, F_SETFL, opts);
}

/* -------------------------------------------------------------------------- */


