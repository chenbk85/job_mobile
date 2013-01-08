//
// server.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at jHttp://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include <boost/asio.hpp>
#include <string>
#include <boost/noncopyable.hpp>
#include "connection.hpp"
#include "connection_manager.hpp"
#include "request_handler.hpp"

namespace jHttp {
namespace jServer {

/// The top-level class of the HTTP jServer.
class jServer
  : private boost::noncopyable
{
public:
  /// Construct the jServer to listen on the specified TCP address and port, and
  /// serve up files from the given directory.
  explicit jServer(const std::string& address, const std::string& port,
      const std::string& doc_root);

  /// Run the jServer's io_service loop.
  void run();

private:
  /// Initiate an asynchronous accept operation.
  void Start_accept();

  /// Handle completion of an asynchronous accept operation.
  void Handle_accept(const boost::system::error_code& e);

  /// Handle a jRequest to stop the jServer.
  void Handle_stop();

  /// The io_service used to perform asynchronous operations.
  boost::asio::io_service io_service_;

  /// The signal_set is used to register for process termination notifications.
  boost::asio::signal_set signals_;

  /// Acceptor used to listen for incoming connections.
  boost::asio::ip::tcp::acceptor acceptor_;

  /// The jConnection manager which owns all live connections.
  jConnection_manager connection_manager_;

  /// The next jConnection to be e_accepted.
  connection_ptr new_connection_;

  /// The handler for all incoming requests.
  jRequest_handler request_handler_;
};

} // namespace jServer
} // namespace jHttp

#endif // HTTP_SERVER_HPP
