
//#define DEF_TNonblockingServer
//#define DEF_TThreadedServer
#define DEF_TThreadPoolServer

#include <stdio.h>
#include <tchar.h>
#include <intrin.h>
#pragma intrinsic(__rdtsc)
#define RDTSC(low) __rdtsc();
#define RDTSC_EX( low , high )


/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#if defined (DEF_TNonblockingServer)
//#include "d:\\svn\\lib\\lib_thrift\\libevent-2.0.21-stable\\include\\event2\\event.h"
#include <thrift/server/TNonblockingServer.h>
#endif

#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/concurrency/BoostThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include <iostream>
#include <stdexcept>
#include <sstream>

#include "../gen-cpp/Calculator.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::server;

using namespace tutorial;
using namespace shared;

using namespace boost;

class CalculatorHandler : public CalculatorIf {
public:
  void ping() {printf("ping()\n"); }
  int32_t add(const int32_t n1, const int32_t n2) {
    printf("add(%d,%d)\n", n1, n2); 
		return n1 + n2;
  }
  int32_t calculate(const int32_t logid, const Work &work) {
    printf("calculate(%d,{%d,%d,%d})\n", logid, work.op, work.num1, work.num2);
    int32_t val;
    switch (work.op) {
    case Operation::ADD:
      val = work.num1 + work.num2; break;
    case Operation::SUBTRACT:
      val = work.num1 - work.num2; break;
    case Operation::MULTIPLY:
      val = work.num1 * work.num2; break;
    case Operation::DIVIDE:
      if (work.num2 == 0) {
        InvalidOperation io;  io.what = work.op; io.why = "Cannot divide by 0";
        throw io;
      }
      val = work.num1 / work.num2;
      break;
    default:
      InvalidOperation io; io.what = work.op; io.why = "Invalid Operation";
      throw io;
    }
    SharedStruct ss;
    ss.key = logid;
    char buffer[12];
    _snprintf(buffer, sizeof(buffer), "%d", val);
    ss.value = buffer;
    m_mapLog[logid] = ss;
    return val;
  }
  void getStruct(SharedStruct &ret, const int32_t logid) {
    printf("getStruct(%d)\n", logid);
    ret = m_mapLog[logid];
  }
  void zip() { printf("zip()\n");}

protected:
  map<int32_t, SharedStruct> m_mapLog;

};

int main(int argc, char **argv) {

	WSADATA WsaData;
	WSAStartup(MAKEWORD(2, 2), &WsaData);	// 2.2 버전을 로드합니다.

  boost::shared_ptr<CalculatorHandler> handler(new CalculatorHandler());
  boost::shared_ptr<TProcessor> processor(new CalculatorProcessor(handler));

  boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(9090));

	boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
	boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());


#if defined(DEF_TNonblockingServer)

	//shared_ptr<TTransportFactory> transportFactory_NB(new TFramedTransportFactory());
	boost::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(15);
	boost::shared_ptr<BoostThreadFactory> threadFactory(new BoostThreadFactory());
	threadManager->threadFactory(threadFactory);
	threadManager->start();
	TNonblockingServer server(processor, 
														protocolFactory, 
														9090, 
														threadManager);

#elif defined(DEF_TThreadPoolServer)
	const int workerCount = 20000;
  boost::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(workerCount);
	boost::shared_ptr<BoostThreadFactory> threadFactory(new BoostThreadFactory());
  threadManager->threadFactory(threadFactory);
  threadManager->start();
  TThreadPoolServer server(processor,
                           serverTransport,
                           transportFactory,
                           protocolFactory,
                           threadManager);

#elif defined(DEF_TThreadedServer)
  TThreadedServer server(processor,
                         serverTransport,
                         transportFactory,
                         protocolFactory);

#else
	TSimpleServer server(processor,
		serverTransport,
		transportFactory,
		protocolFactory);
#endif

  printf("Starting the server...\n");
  server.serve();
  printf("done.\n");
  return 0;
}

