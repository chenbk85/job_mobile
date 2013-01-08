//
// Server.cpp
// ~~~~~~~~~~
//
//
#include "stdafx.h"

#include "common_def.hpp"
#include "server.hpp"
#include "connection.hpp"
#include "connection_manager.hpp"
//#include "UgRequestHandler.hpp"
namespace presence {

Server::Server(	const std::string& ug_ip, 
				const std::string& ug_port,
				const std::string& monitoring_ip, 
				const std::string& monitoring_port)
	:
	signals_(io_service_),
	ug_acceptor_(io_service_),
	monitoring_acceptor_(io_service_)		
{
	// Register to handle the signals that indicate when the Server should exit.
	// It is safe to register for the same signal multiple times in a program,
	// provided all registration for the specified signal is made through Asio.
	signals_.add(SIGINT);
	signals_.add(SIGTERM);
#if defined(SIGQUIT)
	signals_.add(SIGQUIT);
#endif // defined(SIGQUIT)
	signals_.async_wait(boost::bind(&Server::handle_stop_, this));

	// Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
	boost::asio::ip::tcp::resolver resolver(io_service_);

	boost::asio::ip::tcp::resolver::query query(ug_ip, ug_port);	
	boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
	ug_acceptor_.open(endpoint.protocol());
	ug_acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	ug_acceptor_.bind(endpoint);
	ug_acceptor_.listen();

	boost::asio::ip::tcp::resolver::query query2(monitoring_ip, monitoring_port);
	boost::asio::ip::tcp::endpoint endpoint2 = *resolver.resolve(query2);
	monitoring_acceptor_.open(endpoint2.protocol());
	monitoring_acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	monitoring_acceptor_.bind(endpoint2);
	monitoring_acceptor_.listen();

	start_ug_accept_();
	start_monitoring_accept_();
}

void Server::run()
{
//	io_service_.run();
    // Create a pool of threads to run all of the io_services.
    std::vector<boost::shared_ptr<boost::thread> > threads;
    for (std::size_t i = 0; i < 10; ++i)
    {
        boost::shared_ptr<boost::thread> thread(new boost::thread(
                                                    boost::bind(&boost::asio::io_service::run, &io_service_)));
        threads.push_back(thread);
    }

    // Wait for all threads in the pool to exit.
    for (std::size_t i = 0; i < threads.size(); ++i)
        threads[i]->join();

	MSG_LOG() << "Server ended..." << std::endl;
}

void Server::start_ug_accept_()
{
	SpConnection new_connection(new Connection(io_service_));

	ug_acceptor_.async_accept(new_connection->socket(),
		boost::bind(&Server::handle_ug_accept_, this, new_connection,
		boost::asio::placeholders::error));
}

void Server::start_monitoring_accept_()
{
	// ToDo :
}

void Server::handle_ug_accept_(SpConnection& new_connection, const boost::system::error_code& e)
{
	// accept 핸들러가 뜨기 전에 서버가 내려가 있는 예외 상황 처리.
	if (false == ug_acceptor_.is_open())
	{
		return;
	}
	
	// 정상 플로우
	if (no_error(e))
	{
		the_connection_manager.start(new_connection);
	}
	else
	{
		// ToDo : 로그.
	}

	start_ug_accept_();
}


void Server::handle_stop_()
{
	// The Server is stopped by cancelling all outstanding asynchronous
	// operations. Once all operations have finished the io_service::run() call
	// will exit.
	ug_acceptor_.close();		
	the_connection_manager.stop_all();

	io_service_.stop();
}

}  // namespace presence
