//
// Server.hpp
// ~~~~~~~~~~
//
//
// 최초 작성 : 2012.07.30. kts123@neowiz.com
// ~~~~~~~~~~
//

#ifndef PRESENCE_SERVER_HPP
#define PRESENCE_SERVER_HPP

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "../proto/presence.pb.h"
#include "connection.hpp"
#include "common_def.hpp"

#include "connection.hpp"
#include "connection_manager.hpp"
#include "ug_request_handler.hpp"

namespace presence {

/// The top-level class of the presece Server.

class Server
	: private boost::noncopyable
{
public:
	/// Construct the Server to listen on the specified TCP address and port, and
	/// serve up files from the given directory.
	explicit Server(const std::string& ug_ip, 
					const std::string& ug_port,
					const std::string& monitoring_ip, 
					const std::string& monitoring_port);

	/// Run the Server's io_service loop.
	void run();

private:
	/// Initiate an asynchronous accept operation.
	void start_ug_accept_();
	void start_monitoring_accept_();

	/// Handle completion of an asynchronous accept operation.
	//void handle_accept(const boost::system::error_code& e);
	void handle_ug_accept_(SpConnection& new_connection, const boost::system::error_code& e);

	/// Handle a request to stop the Server.
	void handle_stop_();

private:
	/// The number of threads that will call io_service::run().
	std::size_t thread_pool_size_;

	/// The io_service used to perform asynchronous operations.
	boost::asio::io_service io_service_;

	/// The signal_set is used to register for process termination notifications.
	boost::asio::signal_set signals_;

	/// Acceptor used to listen for incoming connections.
	boost::asio::ip::tcp::acceptor ug_acceptor_;
	boost::asio::ip::tcp::acceptor monitoring_acceptor_;
};

} // namespace prsence

#endif // PRESENCE_SERVER_HPP
