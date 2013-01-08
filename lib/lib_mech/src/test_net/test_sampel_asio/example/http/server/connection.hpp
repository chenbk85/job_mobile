//
// connection.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at jHttp://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_CONNECTION_HPP
#define HTTP_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "reply.hpp"
#include "request.hpp"
#include "request_handler.hpp"
#include "request_parser.hpp"

namespace jHttp {
namespace jServer {

class jConnection_manager;

/// Represents a single jConnection from a client.
//--------------------------------------------------------------------------
class jConnection
//--------------------------------------------------------------------------
  : public boost::enable_shared_from_this<jConnection>,
    private boost::noncopyable
{
public:
  /// Construct a jConnection with the given io_service.
  explicit jConnection(boost::asio::io_service& io_service,
      jConnection_manager& manager, jRequest_handler& handler);

  /// Get the socket associated with the jConnection.
  boost::asio::ip::tcp::socket& socket();

  /// Start the first asynchronous operation for the jConnection.
  void start();

  /// Stop all asynchronous operations associated with the jConnection.
  void stop();

private:
  /// Handle completion of a read operation.
  void handle_read(const boost::system::error_code& e,
      std::size_t bytes_transferred);

  /// Handle completion of a write operation.
  void handle_write(const boost::system::error_code& e);

  /// Socket for the jConnection.
  boost::asio::ip::tcp::socket socket_;

  /// The manager for this jConnection.
  jConnection_manager& connection_manager_;

  /// The handler used to process the incoming jRequest.
  jRequest_handler& request_handler_;

  /// Buffer for incoming data.
  boost::array<char, 8192> buffer_;

  /// The incoming jRequest.
  jRequest request_;

  /// The parser for the incoming jRequest.
  jRequest_parser request_parser_;

  /// The jReply to be sent back to the client.
  jReply reply_;
};

typedef boost::shared_ptr<jConnection> connection_ptr;

} // namespace jServer
} // namespace jHttp

#endif // HTTP_CONNECTION_HPP
