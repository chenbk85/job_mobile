//
// header.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at jHttp://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_HEADER_HPP
#define HTTP_HEADER_HPP

#include <string>

namespace jHttp {
namespace jServer {

struct jHeader
{
  std::string name;
  std::string value;
};

} // namespace jServer
} // namespace jHttp

#endif // HTTP_HEADER_HPP
