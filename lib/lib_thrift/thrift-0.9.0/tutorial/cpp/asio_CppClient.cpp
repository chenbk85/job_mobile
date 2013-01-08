#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <async/TAsioAsync.h>
#include <protocol/TBinaryProtocol.h>

#include "Calculator.h"

using namespace apache::thrift;

void pingCallback() {
  printf("ping()\n");
}

void pingErrback(const tutorial::Calculator_ping_result& result) {
  printf("Exception caught\n");
}

void addCallback(int32_t a, int32_t b, int32_t sum) {
  printf("%d+%d=%d\n", a, b, sum);
}

void addErrback(const tutorial::Calculator_add_result& result) {
  printf("Exception caught\n");
}

void calculateCallback(int32_t workID) {
  printf("work id = %d\n", workID);
}

void calculateErrback(const tutorial::Calculator_calculate_result& result) {
  printf("error: calculate: %s\n", result.ouch.why.c_str());
}

void getStructCallback(const shared::SharedStruct& result) {
  printf("getStruct: %d: %s\n", result.key, result.value.c_str());
}

void getStructErrback(const shared::SharedService_getStruct_result& result) {
  printf("getStruct error!\n");
}

void connected(boost::shared_ptr<tutorial::CalculatorAsyncClient> client) {
  std::cout << "connected!!!" << std::endl;

  // The server in async/CppServer.cpp has an add method which waits for a + b seconds before returning
  client->add(2, 3).setCallback(boost::bind(&addCallback, 2, 3, _1)).setErrback(&addErrback);  // will return after 5s
  client->add(1, 2).setCallback(boost::bind(&addCallback, 1, 2, _1)).setErrback(&addErrback);  // will return after 3s
  client->add(1, 1).setCallback(boost::bind(&addCallback, 1, 1, _1)).setErrback(&addErrback);  // will return after 2s

  // Will return immediately
  client->ping().setCallback(pingCallback).setErrback(pingErrback);

  tutorial::Work work;
  work.op = tutorial::DIVIDE;
  work.num1 = 42;
  work.num2 = 0;

  // Should throw a division by zero error exception
  client->calculate(1, work).setCallback(calculateCallback).setErrback(calculateErrback);

  // Create a normal request which should work fine
  work.op = tutorial::ADD;
  client->calculate(1, work).setCallback(calculateCallback).setErrback(calculateErrback);

  // Should cause warnings from the TController when the result comes back but there is no handler ready
  client->ping();

  // calculate(...) writes to the log each time. We try to fetch the two first entries
  client->getStruct(0).setCallback(getStructCallback).setErrback(getStructErrback);
  client->getStruct(1).setCallback(getStructCallback).setErrback(getStructErrback);

  // Oneway function returns void so we can't invoke setCallback/setErrback
  client->zip();
}

int main(int argc, char* argv[])
{
  try
  {
    boost::asio::io_service io_service;

    boost::shared_ptr<protocol::TProtocolFactory> protocolFactory(new protocol::TBinaryProtocolFactory());
    
    boost::shared_ptr<async::TAsioClient> client (
						  new async::TAsioClient(
									 io_service,
									 protocolFactory,
									 protocolFactory));

    client->connect("localhost", 9090, connected);

    io_service.run(); // Will block

    printf("Done, returning\n");
  }
  catch (std::exception& e)
  {
    std::cout << "Exception: " << e.what() << "\n";
  }

  return 0;
}
