#include "client.hpp"

#define ENABLE_MSG_TRACE
#include "basekit/dump.hpp"


#include <google/protobuf/io/zero_copy_stream_impl.h>
using google::protobuf::io::ArrayInputStream;

/* -------------------------------------------------------------------------- */

Client::Client():
  read_length_(0)
{
  create();
  set_non_blocking(true);
}

/* -------------------------------------------------------------------------- */

Client::~Client()
{
  close();
}

/* -------------------------------------------------------------------------- */

bool 
Client::connect(const char* host, unsigned short port, int timeout)
{
  return Socket::connect(host, port, timeout);
}

/* -------------------------------------------------------------------------- */

void 
Client::disconnect()
{
  close();
}

/* -------------------------------------------------------------------------- */

void 
Client::send(UReqProtocol& request)
{
  int len = (int)request.ByteSize();

  MSG::DumpUReqProtocol(request);

  memcpy(buffer_, &len, sizeof(len));

  if (!request.SerializeToArray(buffer_ + 4, len))
  {
    std::cerr << "fail to generate byte stream\n";
  }

  MSG_DUMP("<---", buffer_, len + 4);

  Socket::send(buffer_, len+4);
}

/* -------------------------------------------------------------------------- */

bool
Client::wait(UAnsProtocol& answer, int timeout)
{
  struct timeval tv;
  fd_set fd_r;

  read_length_ = 0;

  while(1)
  {
    tv.tv_sec = timeout;
    tv.tv_usec = 0L;

    FD_ZERO(&fd_r);
    FD_SET(handle(), &fd_r);

    if ( select(FD_SETSIZE, &fd_r, NULL, NULL, &tv) <= 0)
    {
      return false; 
    }

    if (FD_ISSET(handle(), &fd_r))
    {
      int n = recv(&buffer_[read_length_], BUFFER_SIZE - read_length_);
      if (n == 0)
      {
        // connection closed
        close();
        return false;
      }

      read_length_ += n;

      int *len;
      if (read_length_ > 4)
      {
        len = (int*)buffer_; 
      }

      if ((4 + (*len)) <= (int)read_length_)
      {
        ArrayInputStream input(&buffer_[4], *len);

        if (!answer.ParseFromZeroCopyStream(&input))
        {
          read_length_ = 0;
          return false;
        }

        MSG::DumpUAnsProtocol(answer);

        return true;
      }
    }
    else
    {
      return false;
    }
  }

  return false;
}

/* -------------------------------------------------------------------------- */


