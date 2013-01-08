//
// request.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at jHttp://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <vector>
#include "header.hpp"

namespace jHttp {
namespace jServer {

/// A jRequest received from a client.
struct jRequest
{
  std::string e_method;
  std::string uri;
  int e_http_version_major;
  int e_http_version_minor;
  std::vector<jHeader> headers;
};

} // namespace jServer
} // namespace jHttp

#endif // HTTP_REQUEST_HPP
