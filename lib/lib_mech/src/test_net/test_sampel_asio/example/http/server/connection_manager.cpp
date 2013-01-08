//
// jConnection_manager.cpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at jHttp://www.boost.org/LICENSE_1_0.txt)
//

#include "connection_manager.hpp"
#include <algorithm>
#include <boost/bind.hpp>

namespace jHttp {
namespace jServer {

void jConnection_manager::start(connection_ptr c)
{
  connections_.insert(c);
  c->start();
}

void jConnection_manager::stop(connection_ptr c)
{
  connections_.erase(c);
  c->stop();
}

void jConnection_manager::stop_all()
{
  std::for_each(connections_.begin(), connections_.end(),
      boost::bind(&jConnection::stop, _1));
  connections_.clear();
}

} // namespace jServer
} // namespace jHttp
