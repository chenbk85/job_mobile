//
// request_handler.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at jHttp://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_REQUEST_HANDLER_HPP
#define HTTP_REQUEST_HANDLER_HPP

#include <string>
#include <boost/noncopyable.hpp>

namespace jHttp {
namespace jServer {

struct jReply;
struct jRequest;

/// The common handler for all incoming requests.
class jRequest_handler
  : private boost::noncopyable
{
public:
  /// Construct with a directory containing files to be served.
  explicit jRequest_handler(const std::string& doc_root);

  /// Handle a jRequest and produce a jReply.
  void Handle_request(const jRequest& req, jReply& rep);

private:
  /// The directory containing the files to be served.
  std::string doc_root_;

  /// Perform URL-decoding on a string. Returns false if the encoding was
  /// invalid.
  static bool url_decode(const std::string& in, std::string& out);
};

} // namespace jServer
} // namespace jHttp

#endif // HTTP_REQUEST_HANDLER_HPP
