//
// timer.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;
#define LOG_PRINT(X) cout<< __FUNCTION__ << " " << GetCurrentThreadId() << ") " << X  << std::endl;

void print(const boost::system::error_code& /*e*/)
{
	LOG_PRINT("4");
  std::cout << "Hello, world!\n";
}

int main()
{
  boost::asio::io_service io;

  boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
  LOG_PRINT("1");
  t.async_wait(&print);
  LOG_PRINT("2");

  io.run();
  LOG_PRINT("3");

  return 0;
}
