#include "server.hpp"

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>


#define ENABLE_MSG_TRACE
#include "basekit/dump.hpp"


using namespace std;

/* -------------------------------------------------------------------------- */

Server::Server():
  shutdown_(false),
  port_(0)
{
  for(int i = 0; i < MAX_CONNECTIONS; i++)
  {
    sessions_[i] = NULL;
  }
}

/* -------------------------------------------------------------------------- */

Server::~Server()
{
}

/* -------------------------------------------------------------------------- */

Server::Session::Session():
  Socket(),
  read_buffer_length_(0)
{
}

/* -------------------------------------------------------------------------- */

bool
Server::Session::read()
{
  int n;

  n = Socket::recv(&read_buffer_[read_buffer_length_],
                        4096-read_buffer_length_);
  if (n <= 0)
  {
    return false;
  }

  read_buffer_length_ += n;

  MSG_DUMP("--->", read_buffer_, read_buffer_length_);

  if (read_buffer_length_ < 4)
  {
    return true;
  }

  int* length;
  int idx = 0;

  while (idx < (int)read_buffer_length_)
  {
    if (idx + 4 <= (int)read_buffer_length_)
    {
      length = (int*)&read_buffer_[idx];
    }
    else
    {
      return true;
    }

    if (*length > 0)
    {
      if (idx + 4 + (*length) <= (int)read_buffer_length_)
      {
        if (!dispatch(&read_buffer_[idx+4], (*length)))
        {
          cerr << "패킷 처리에 문제가 있음\n";
        }
      }
      else
      {
        break;
      }
    }

    idx += 4 + (*length);
  }

  if (idx > 0 && idx != (int)read_buffer_length_)
  {
    std::memmove(&read_buffer_[idx], read_buffer_, read_buffer_length_ - idx);
    read_buffer_length_ -= idx;
  }

  if (idx == (int)read_buffer_length_)
  {
    read_buffer_length_ = 0;
  }

  return true;
}

/* -------------------------------------------------------------------------- */

void 
Server::Session::send(::google::protobuf::MessageLite& message)
{
  int len = (int)message.ByteSize();

  memcpy(write_buffer_, &len, sizeof(len));
  message.SerializeToArray(write_buffer_ + 4, len);

  MSG_DUMP("<---", write_buffer_, len + 4);

  Socket::send(write_buffer_, len+4);
}

/* -------------------------------------------------------------------------- */

void 
Server::run()
{
  std::cout << "service started\n";

  int max_fd, fd;

  fd_set read_fds, temp_fds;
  struct timeval tv;


  if (!create())
  {
    return;
  }

  if (!bind(port_))
  {
    close();
    return;
  }

  if (!listen())
  {
    close();
    return;
  }

  max_fd = handle();

  FD_ZERO(&read_fds);
  FD_SET(handle(), &read_fds);

  tv.tv_sec = 0;
  tv.tv_usec = 1000;

  while (shutdown_ == false)
  {
    temp_fds = read_fds;

    if (select(max_fd + 1, &temp_fds, 0, 0, &tv) < 0)
    {
      close();
      return;
    }
    else
    {
      for(fd = 0; fd <= max_fd; fd++)
      {
        if (FD_ISSET(fd, &temp_fds))
        {
          if (fd == handle())
          {
            Session* new_conn = create_session();
            new_conn->create();
           
            if (!accept(*new_conn))
            {
              delete new_conn;
              printf("accept() failed\n"); 
            }
            else
            {
              cout << "new connection\n";
              if (new_conn->handle() < MAX_CONNECTIONS)
              {
                FD_SET(new_conn->handle(), &read_fds);
                sessions_[new_conn->handle()] = new_conn;
                if (new_conn->handle() > max_fd)
                {
                  max_fd = new_conn->handle();
                }
              }
              else
              {
                assert(false && "over max connection");
              }
            }
          }
          else
          {
            Session* current = sessions_[fd];
            assert(current);

            //cout << "read data " << fd << endl;
            if (!current->read())
            {
              FD_CLR(fd, &read_fds);
              current->close();
              delete current;
              sessions_[fd] = NULL;
              //cout << "connection closed\n";
            }
          }
        }
      }
    }
  }
  close();

  std::cout << "finish service\n";
}

/* -------------------------------------------------------------------------- */

