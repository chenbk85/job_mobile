#include "thrift_connection.hpp"
#include <vector>
#include <boost/bind.hpp>

namespace thrift_asio {
namespace server {

connection::connection(asio::io_service& io_service,
                       shared_ptr<TProcessor> processor,
                       shared_ptr<TProtocolFactory> inputProtocolFactory,
                       shared_ptr<TProtocolFactory> outputProtocolFactory
                      )
        : strand_(io_service),
        socket_(io_service),
        processor_(processor),
        inputProtocolFactory_(inputProtocolFactory),
        outputProtocolFactory_(outputProtocolFactory),
        io_service_(io_service)
{
}

asio::ip::tcp::socket& connection::socket()
{
    return socket_;
}

void connection::start()
{
    asio::async_read(socket_, asio::buffer(length_),
                     strand_.wrap(
                         boost::bind(&connection::handle_read_length, shared_from_this(),
                                     asio::placeholders::error)));
}

void connection::handle_read_length(const boost::system::error_code& error) {
    if (!error) {
        int32_t sz =
            ((length_[0] & 0xff) << 24) |
            ((length_[1] & 0xff) << 16) |
            ((length_[2] & 0xff) <<  8) |
            ((length_[3] & 0xff));

        if (sz < 0) {
            std::cerr << "Frame length is negative. Are you sure your client uses a TFramedTransport?" << std::endl;
        } else if (sz == 0) {
            std::cerr << "Frame length is zero, weird" << std::endl;
        } else {
            frame_.resize(sz);

            asio::async_read(socket_,
                             asio::buffer(frame_, sz),
                             strand_.wrap(
                                 boost::bind(&connection::handle_read_frame, shared_from_this(), sz, _1)));
        }

    }
}

void connection::handle_read_frame(int32_t sz, const boost::system::error_code& error) {

    if (!error) {

        shared_ptr<TMemoryBuffer> inputTransport(new TMemoryBuffer(&frame_[0], sz));
        shared_ptr<TProtocol> inputProtocol = inputProtocolFactory_->getProtocol(inputTransport);

        shared_ptr<TMemoryBuffer> outputTransport(new TMemoryBuffer);
        shared_ptr<TFramedTransport> outputFramedTransport(new TFramedTransport(outputTransport));
        shared_ptr<TProtocol> outputProtocol = outputProtocolFactory_->getProtocol(outputFramedTransport);

        processor_->process(inputProtocol, outputProtocol,0);

        uint32_t outframeSize;
        uint8_t *outframe;

        outputTransport->getBuffer(&outframe, &outframeSize);

        asio::async_write(socket_,
                          asio::buffer(outframe, outframeSize),
                          strand_.wrap(boost::bind(&connection::handle_write, shared_from_this(), _1)));

    }
}


void connection::handle_write(const boost::system::error_code& error)
{
    if (!error)
    {
        asio::async_read(socket_, asio::buffer(length_),
                         strand_.wrap(boost::bind(&connection::handle_read_length, shared_from_this(), _1)));
    }
}
} // namespace server
} // namespace thrift_asio
