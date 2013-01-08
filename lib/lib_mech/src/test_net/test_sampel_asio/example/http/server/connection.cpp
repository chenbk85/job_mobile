//
// jConnection.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at jHttp://www.boost.org/LICENSE_1_0.txt)
//

#include "connection.hpp"
#include <vector>
#include <boost/bind.hpp>
#include "connection_manager.hpp"
#include "request_handler.hpp"

namespace jHttp {
namespace jServer {

jConnection::jConnection(boost::asio::io_service& io_service,
    jConnection_manager& manager, jRequest_handler& handler)
  : socket_(io_service),
    connection_manager_(manager),
    request_handler_(handler)
{
}

boost::asio::ip::tcp::socket& jConnection::socket()
{
  return socket_;
}

void jConnection::start()
{
  socket_.async_read_some(boost::asio::buffer(buffer_),
      boost::bind(&jConnection::handle_read, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void jConnection::stop()
{
  socket_.close();
}

void jConnection::handle_read(const boost::system::error_code& e,
    std::size_t bytes_transferred)
{
  if (!e)
  {
    boost::tribool result;
    boost::tie(result, boost::tuples::ignore) = request_parser_.parse(
        request_, buffer_.data(), buffer_.data() + bytes_transferred);

    if (result)
    {
      request_handler_.Handle_request(request_, reply_);
      boost::asio::async_write(socket_, reply_.to_buffers(),
          boost::bind(&jConnection::handle_write, shared_from_this(),
            boost::asio::placeholders::error));
    }
    else if (!result)
    {
      reply_ = jReply::stock_reply(jReply::e_bad_request);
      boost::asio::async_write(socket_, reply_.to_buffers(),
          boost::bind(&jConnection::handle_write, shared_from_this(),
            boost::asio::placeholders::error));
    }
    else
    {
      socket_.async_read_some(boost::asio::buffer(buffer_),
          boost::bind(&jConnection::handle_read, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
  }
  else if (e != boost::asio::error::operation_aborted)
  {
    connection_manager_.stop(shared_from_this());
  }
}

void jConnection::handle_write(const boost::system::error_code& e)
{
  if (!e)
  {
    // Initiate graceful jConnection closure.
    boost::system::error_code ignored_ec;
    socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
  }

  if (e != boost::asio::error::operation_aborted)
  {
    connection_manager_.stop(shared_from_this());
  }
}

} // namespace jServer
} // namespace jHttp
