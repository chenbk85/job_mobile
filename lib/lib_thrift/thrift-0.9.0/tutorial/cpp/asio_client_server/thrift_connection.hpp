#ifndef THRIFT_ASIO_SERVER_CONNECTION_HPP
#define THRIFT_ASIO_SERVER_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "../gen-cpp/Calculator.h"

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace tutorial;
using namespace shared;

using boost::shared_ptr;
using namespace boost;

namespace thrift_asio {
namespace server {

class connection
            : public boost::enable_shared_from_this<connection>,
            private boost::noncopyable
{
public:
    explicit connection(asio::io_service& io_service,
                        shared_ptr<TProcessor> processor,
                        shared_ptr<TProtocolFactory> inputProtocolFactory,
                        shared_ptr<TProtocolFactory> outputProtocolFactory);

    asio::ip::tcp::socket& socket();

    void start();

private:
    void handle_read_length(const boost::system::error_code& e);

    void handle_read_frame(int32_t sz, const boost::system::error_code& e);

    void handle_write(const boost::system::error_code& e);

    asio::io_service::strand strand_;

    asio::ip::tcp::socket socket_;

    boost::array<uint8_t, 4> length_;

    shared_ptr<TProcessor> processor_;

    shared_ptr<TProtocolFactory> inputProtocolFactory_;

    shared_ptr<TProtocolFactory> outputProtocolFactory_;

    std::vector<uint8_t> frame_;

    asio::io_service& io_service_;
};

typedef boost::shared_ptr<connection> connection_ptr;

} // namespace server
} // namespace thrift_asio

#endif // THRIFT_ASIO_SERVER_CONNECTION_HPP
