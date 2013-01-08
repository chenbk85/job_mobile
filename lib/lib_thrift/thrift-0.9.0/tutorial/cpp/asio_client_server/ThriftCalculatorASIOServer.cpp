#include <iostream>
#include <stdexcept>
#include <map>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "../gen-cpp/Calculator.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace tutorial;
using namespace shared;
using namespace boost;
using boost::shared_ptr;

using asio::ip::tcp;

class ThriftServerProtocol
{
public:
    ThriftServerProtocol(asio::io_service& io_service, shared_ptr<TProcessor> processor,
                         shared_ptr<TProtocolFactory> inputProtocolFactory, shared_ptr<TProtocolFactory> outputProtocolFactory)
            : socket_(io_service), processor_(processor), inputProtocolFactory_(inputProtocolFactory),
            outputProtocolFactory_(outputProtocolFactory)
    {
    }

    tcp::socket& socket()
    {
        return socket_;
    }

    void start()
    {
        std::cout << "Incoming connection" << std::endl;
        asio::async_read(socket_,
                         asio::buffer(length_, 4),
                         boost::bind(&ThriftServerProtocol::handle_read_length, this, _1));

    }

    void handle_read_length(const boost::system::error_code& error) {
        if (!error) {
            int32_t sz = *(int32_t *)length_;
            sz = (int32_t)ntohl(sz);

            if (sz < 0) {
                std::cerr << "Frame length is negative. Are you sure your client uses a TFramedTransport?" << std::endl;
                delete this;
            } else if (sz == 0) {
                std::cerr << "Frame length is zero, weird" << std::endl;
                delete this;
            } else {
                frame_.resize(sz);

                asio::async_read(socket_,
                                 asio::buffer(frame_, sz),
                                 boost::bind(&ThriftServerProtocol::handle_read_frame, this, sz, _1));
            }

        } else {
            delete this;
        }
    }

    void handle_read_frame(int32_t sz, const boost::system::error_code& error) {

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
                              boost::bind(&ThriftServerProtocol::handle_write, this, _1));

        } else {
            delete this;
        }
    }

    void handle_write(const boost::system::error_code& error)
    {
        if (!error)
        {
            asio::async_read(socket_, asio::buffer(length_, 4),
                             boost::bind(&ThriftServerProtocol::handle_read_length, this, _1));
        }
        else
        {
            delete this;
        }
    }

private:
    tcp::socket socket_;

    uint8_t length_[4];

    std::vector<uint8_t> frame_;

    shared_ptr<TProcessor> processor_;
    shared_ptr<TProtocolFactory> inputProtocolFactory_;
    shared_ptr<TProtocolFactory> outputProtocolFactory_;
};

class ThriftCalculatorServer
{
public:
    ThriftCalculatorServer(asio::io_service& io_service, short port, shared_ptr<TProcessor> processor,
                           shared_ptr<TProtocolFactory> inputProtocolFactory, shared_ptr<TProtocolFactory> outputProtocolFactory)
            : io_service_(io_service),
            acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
            processor_(processor), inputProtocolFactory_(inputProtocolFactory), outputProtocolFactory_(outputProtocolFactory)
    {
        ThriftServerProtocol* new_session = new ThriftServerProtocol(io_service_, processor_,
                inputProtocolFactory_, outputProtocolFactory_);
        acceptor_.async_accept(new_session->socket(),
                               boost::bind(&ThriftCalculatorServer::handle_accept, this, new_session,
                                           asio::placeholders::error));
    }

    void handle_accept(ThriftServerProtocol* new_session,
                       const boost::system::error_code& error)
    {
        if (!error)
        {
            new_session->start();
            new_session = new ThriftServerProtocol(io_service_, processor_, inputProtocolFactory_,
                                                   outputProtocolFactory_);
            acceptor_.async_accept(new_session->socket(),
                                   boost::bind(&ThriftCalculatorServer::handle_accept, this, new_session,
                                               asio::placeholders::error));
        }
        else
        {
            delete new_session;
        }
    }

private:
    asio::io_service& io_service_;
    tcp::acceptor acceptor_;
    shared_ptr<TProcessor> processor_;
    shared_ptr<TProtocolFactory> inputProtocolFactory_;
    shared_ptr<TProtocolFactory> outputProtocolFactory_;
};

class CalculatorHandler : public CalculatorIf {
public:
    CalculatorHandler() {}

    void ping() {
        printf("ping()\n");
    }

    int32_t add(const int32_t n1, const int32_t n2) {
        printf("add(%d,%d)\n", n1, n2);
        return n1 + n2;
    }

    int32_t calculate(const int32_t logid, const Work &work) {
        printf("calculate(%d,{%d,%d,%d})\n", logid, work.op, work.num1, work.num2);
        int32_t val;

        switch (work.op) {
				case Operation::ADD:
            val = work.num1 + work.num2;
            break;
        case Operation::SUBTRACT:
            val = work.num1 - work.num2;
            break;
        case Operation::MULTIPLY:
            val = work.num1 * work.num2;
            break;
        case Operation::DIVIDE:
            if (work.num2 == 0) {
                InvalidOperation io;
                io.what = work.op;
                io.why = "Cannot divide by 0";
                throw io;
            }
            val = work.num1 / work.num2;
            break;
        default:
            InvalidOperation io;
            io.what = work.op;
            io.why = "Invalid Operation";
            throw io;
        }

        SharedStruct ss;
        ss.key = logid;
        char buffer[11];
        sprintf(buffer, "%d", val);
        ss.value = buffer;

        log[logid] = ss;

        return val;
    }

    void getStruct(SharedStruct &ret, const int32_t logid) {
        printf("getStruct(%d)\n", logid);
        ret = log[logid];
    }

    void zip() {
        printf("zip()\n");
    }

protected:
    std::map<int32_t, SharedStruct> log;

};

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: ThriftCalculatorASIOServer.cpp <port>" << std::endl;
            return 1;
        }

        asio::io_service io_service;

        shared_ptr<CalculatorHandler> handler(new CalculatorHandler());
        shared_ptr<TProcessor> processor(new CalculatorProcessor(handler));
        shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

        using namespace std; // For atoi.
        ThriftCalculatorServer s(io_service, atoi(argv[1]), processor, protocolFactory, protocolFactory);

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
