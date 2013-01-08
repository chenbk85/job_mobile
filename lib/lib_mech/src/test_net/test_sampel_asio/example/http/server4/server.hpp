//
// server.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at jHttp://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_SERVER4_SERVER_HPP
#define HTTP_SERVER4_SERVER_HPP

#include <boost/asio.hpp>
#include <string>
#include <boost/array.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include "coroutine.hpp"
#include "request_parser.hpp"

namespace jHttp {
namespace jServer {

struct jRequest;
struct jReply;

/// The top-level coroutine of the HTTP server.
class jServer : coroutine
{
public:
  /// Construct the server to listen on the specified TCP address and port, and
  /// serve up files from the given directory.
  explicit jServer(boost::asio::io_service& io_service,
      const std::string& address, const std::string& port,
      boost::function<void(const jRequest&, jReply&)> jRequest_handler);

  /// Perform work associated with the server.
  void operator()(
      boost::system::error_code ec = boost::system::error_code(),
      std::size_t length = 0);

private:
  typedef boost::asio::ip::tcp tcp;

  /// The user-supplied handler for all incoming requests.
  boost::function<void(const jRequest&, jReply&)> request_handler_;

  /// Acceptor used to listen for incoming connections.
  boost::shared_ptr<tcp::acceptor> acceptor_;

  /// The current jConnection from a client.
  boost::shared_ptr<tcp::socket> socket_;

  /// Buffer for incoming data.
  boost::shared_ptr<boost::array<char, 8192> > buffer_;

  /// The incoming jRequest.
  boost::shared_ptr<jRequest> request_;

  /// Whether the jRequest is valid or not.
  boost::tribool valid_request_;

  /// The parser for the incoming jRequest.
  jRequest_parser request_parser_;

  /// The jReply to be sent back to the client.
  boost::shared_ptr<jReply> reply_;
};

} // namespace jServer
} // namespace jHttp

#endif // HTTP_SERVER4_SERVER_HPP
