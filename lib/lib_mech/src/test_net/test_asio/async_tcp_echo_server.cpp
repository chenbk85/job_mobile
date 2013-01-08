//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "stdafx.h"

using boost::asio::ip::tcp;

class jSession
{
public:
	jSession(boost::asio::io_service& io_service)
		: m_socket(io_service)
	{
		jFUNC_GAURD12()
	}

	tcp::socket& get_socket()
	{
		jFUNC_GAURD12()
		return m_socket;
	}

	void start()
	{
		jFUNC_GAURD12()
		m_socket.async_read_some(boost::asio::buffer(m_data, iMAX_LENGTH),
			boost::bind(&jSession::handle_read, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}

	void handle_read(const boost::system::error_code& error,
		size_t bytes_transferred)
	{
		jFUNC_GAURD12()
		if (!error)
		{
			char szData[iMAX_LENGTH+1];
			memcpy ( szData, m_data,bytes_transferred);
			szData[bytes_transferred]=0;
			printf(__FUNCTION__ " DATA= %s\n",szData);
			boost::asio::async_write(m_socket,
				boost::asio::buffer(m_data, bytes_transferred),
				boost::bind(&jSession::handle_write, this,
				boost::asio::placeholders::error));
		}
		else
		{
			error_print(__FUNCTION__ " error !!\n");
			delete this;
		}
	}

	void handle_write(const boost::system::error_code& error)
	{
		jFUNC_GAURD12()
		if (!error)
		{
			m_socket.async_read_some(boost::asio::buffer(m_data, iMAX_LENGTH),
				boost::bind(&jSession::handle_read, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}
		else
		{
			error_print(__FUNCTION__ " error !!\n");

			delete this;
		}
	}

private:
	tcp::socket m_socket;
	char m_data[iMAX_LENGTH+1];
};

class jServer
{
public:
	jServer(boost::asio::io_service& io_service, short port)
		: m_io_service(io_service),
		m_acceptor(io_service, tcp::endpoint(tcp::v4(), port))
	{
		jFUNC_GAURD12()
		jSession* new_session = new jSession(m_io_service);
		m_acceptor.async_accept(new_session->get_socket(),
			boost::bind(&jServer::handle_accept, this, new_session,
			boost::asio::placeholders::error));
	}

	void handle_accept(jSession* new_session,
		const boost::system::error_code& error)
	{
		jFUNC_GAURD12()
		if (!error)
		{
			new_session->start();
			new_session = new jSession(m_io_service);
			m_acceptor.async_accept(new_session->get_socket(),
				boost::bind(&jServer::handle_accept, this, new_session,
				boost::asio::placeholders::error));
		}
		else
		{
			error_print(__FUNCTION__ " error !!\n");

			delete new_session;
		}
	}

private:
	boost::asio::io_service& m_io_service;
	tcp::acceptor m_acceptor;
};

int main_async_tcp_echo_server(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: async_tcp_echo_server <port>\n";
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
