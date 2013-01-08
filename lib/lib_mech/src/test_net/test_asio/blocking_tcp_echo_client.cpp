#include "stdafx.h"
//
// blocking_tcp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main_blocking_tcp_echo_client(int argc, char* argv[])
{
	try
	{
		if (argc != 3)
		{
			std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
			return 1;
		}

		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		tcp::resolver::query query(tcp::v4(), argv[1], argv[2]);
		tcp::resolver::iterator iterator = resolver.resolve(query);

		tcp::socket s(io_service);
		s.connect(*iterator);

		using namespace std; // For strlen.
		const int iMAX_LENGTH2=1024;
		while(1)
		{
			std::cout << "Enter message: ";
			char request[iMAX_LENGTH2];
			std::cin.getline(request, iMAX_LENGTH2);
			size_t request_length = strlen(request);
			boost::asio::write(s, boost::asio::buffer(request, request_length));

			char reply[iMAX_LENGTH2];
			size_t reply_length = boost::asio::read(s,
				boost::asio::buffer(reply, request_length));
			std::cout << "Reply is: ";
			std::cout.write(reply, reply_length);
			std::cout << "\n";
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
