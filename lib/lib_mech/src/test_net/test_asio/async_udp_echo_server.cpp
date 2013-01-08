#include "stdafx.h"
//
// async_udp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class jServer
{
public:
	jServer(boost::asio::io_service& io_service, short port)
		: m_io_service(io_service),
		m_socket(io_service, udp::endpoint(udp::v4(), port))
	{
		m_socket.async_receive_from(
			boost::asio::buffer(m_data, iMAX_LENGTH), m_sender_endpoint,
			boost::bind(&jServer::handle_receive_from, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}

	void handle_receive_from(const boost::system::error_code& error,
		size_t bytes_recvd)
	{
		if (!error && bytes_recvd > 0)
		{
			m_socket.async_send_to(
				boost::asio::buffer(m_data, bytes_recvd), m_sender_endpoint,
				boost::bind(&jServer::handle_send_to, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}
		else
		{
			m_socket.async_receive_from(
				boost::asio::buffer(m_data, iMAX_LENGTH), m_sender_endpoint,
				boost::bind(&jServer::handle_receive_from, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}
	}

	void handle_send_to(const boost::system::error_code& /*error*/,
		size_t /*bytes_sent*/)
	{
		m_socket.async_receive_from(
			boost::asio::buffer(m_data, iMAX_LENGTH), m_sender_endpoint,
			boost::bind(&jServer::handle_receive_from, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}

private:
	boost::asio::io_service& m_io_service;
	udp::socket m_socket;
	udp::endpoint m_sender_endpoint;
	char m_data[iMAX_LENGTH];
};

int main_async_udp_echo_server(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: async_udp_echo_server <port>\n";
			return 1;
		}

		boost::asio::io_service io_service;

		using namespace std; // For atoi.
		jServer s(io_service, atoi(argv[1]));

		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
