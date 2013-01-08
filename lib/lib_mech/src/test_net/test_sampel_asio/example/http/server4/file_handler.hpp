//
// file_handler.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at jHttp://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_SERVER4_FILE_HANDLER_HPP
#define HTTP_SERVER4_FILE_HANDLER_HPP

#include <string>

namespace jHttp {
namespace jServer {

struct jReply;
struct jRequest;

/// The common handler for all incoming requests.
class jFile_handler
{
public:
  /// Construct with a directory containing files to be served.
  explicit jFile_handler(const std::string& doc_root);

  /// Handle a jRequest and produce a jReply.
  void operator()(const jRequest& req, jReply& rep);

private:
  /// The directory containing the files to be served.
  std::string doc_root_;

  /// Perform URL-decoding on a string. Returns false if the encoding was
  /// invalid.
  static bool url_decode(const std::string& in, std::string& out);
};

} // namespace jServer
} // namespace jHttp

#endif // HTTP_SERVER4_FILE_HANDLER_HPP
