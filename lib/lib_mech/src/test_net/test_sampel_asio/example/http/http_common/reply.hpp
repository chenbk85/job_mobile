//
// reply.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at jHttp://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_REPLY_HPP
#define HTTP_REPLY_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "header.hpp"

namespace jHttp {
namespace jServer {

/// A jReply to be sent to a client.
struct jReply
{
  /// The status of the jReply.
  enum EStatusType
  {
    eST_ok = 200,
    e_created = 201,
    e_accepted = 202,
    e_no_content = 204,
    e_multiple_choices = 300,
    e_moved_permanently = 301,
    e_moved_temporarily = 302,
    e_not_modified = 304,
    e_bad_request = 400,
    e_unauthorized = 401,
    e_forbidden = 403,
    e_not_found = 404,
    e_internal_server_error = 500,
    e_not_implemented = 501,
    e_bad_gateway = 502,
    e_service_unavailable = 503
  } status;

  /// The headers to be included in the jReply.
  std::vector<jHeader> headers;

  /// The content to be sent in the jReply.
  std::string content;

  /// Convert the jReply into a vector of buffers. The buffers do not own the
  /// underlying memory blocks, therefore the jReply object must remain valid and
  /// not be changed until the write operation has completed.
  std::vector<boost::asio::const_buffer> to_buffers();

  /// Get a stock jReply.
  static jReply stock_reply(EStatusType status);
};

} // namespace jServer
} // namespace jHttp

#endif // HTTP_REPLY_HPP
