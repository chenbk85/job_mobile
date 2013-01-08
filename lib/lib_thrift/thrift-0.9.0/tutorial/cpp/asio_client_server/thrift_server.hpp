//
// server.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at thrift_asio://www.boost.org/LICENSE_1_0.txt)
//

#ifndef THRIFT_ASIO_SERVER_SERVER_HPP
#define THRIFT_ASIO_SERVER_SERVER_HPP

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "thrift_connection.hpp"

#include "../gen-cpp/Calculator.h"
#include <thrift/protocol/TBinaryProtocol.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace tutorial;
using namespace shared;

using boost::shared_ptr;

namespace thrift_asio {
namespace server {

class server
            : private boost::noncopyable
{
public:
    explicit server(const std::string& address, const std::string& port,
                    std::size_t thread_pool_size,
                    shared_ptr<TProcessor> processor, shared_ptr<TProtocolFactory> input_protocol_factory,
                    shared_ptr<TProtocolFactory> output_protocol_factory);

    void run();

    void stop();

private:
    void handle_accept(const boost::system::error_code& e);

    std::size_t thread_pool_size_;

    asio::io_service io_service_;

    asio::ip::tcp::acceptor acceptor_;

    connection_ptr new_connection_;

    shared_ptr<TProcessor> processor_;

    shared_ptr<TProtocolFactory> input_protocol_factory_;

    shared_ptr<TProtocolFactory> output_protocol_factory_;
};

} // namespace server
} // namespace thrift_asio

#endif // THRIFT_ASIO_SERVER_SERVER_HPP
