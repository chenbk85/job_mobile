#include "thrift_server.hpp"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace thrift_asio {
namespace server {

server::server(const std::string& address, const std::string& port,
               std::size_t thread_pool_size,
               shared_ptr<TProcessor> processor, shared_ptr<TProtocolFactory> input_protocol_factory,
               shared_ptr<TProtocolFactory> output_protocol_factory)
        : thread_pool_size_(thread_pool_size),
        acceptor_(io_service_),
        new_connection_(new connection(io_service_, processor, input_protocol_factory,
                                       output_protocol_factory)),
        processor_(processor),
        input_protocol_factory_(input_protocol_factory),
        output_protocol_factory_(output_protocol_factory)
{
    asio::ip::tcp::resolver resolver(io_service_);
    asio::ip::tcp::resolver::query query(address, port);
    asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();
    acceptor_.async_accept(new_connection_->socket(),
                           boost::bind(&server::handle_accept, this,
                                       asio::placeholders::error));
}

void server::run()
{
    std::vector<boost::shared_ptr<boost::thread> > threads;
    for (std::size_t i = 0; i < thread_pool_size_; ++i)
    {
        boost::shared_ptr<boost::thread> thread(new boost::thread(
                                                   boost::bind(&asio::io_service::run, &io_service_)));
        threads.push_back(thread);
    }

    for (std::size_t i = 0; i < threads.size(); ++i) {
        threads[i]->join();
    }
}

void server::stop()
{
    io_service_.stop();
}

void server::handle_accept(const boost::system::error_code& e)
{
    if (!e)
    {
        new_connection_->start();
        new_connection_.reset(new connection(io_service_, processor_,
                                             input_protocol_factory_, output_protocol_factory_));
        acceptor_.async_accept(new_connection_->socket(),
                               boost::bind(&server::handle_accept, this,
                                           asio::placeholders::error));
    }
}

} // namespace server
} // namespace thrift_asio
