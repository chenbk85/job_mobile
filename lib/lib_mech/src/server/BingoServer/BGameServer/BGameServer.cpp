#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>

#include <intrin.h>
#pragma intrinsic(__rdtsc)
#define RDTSC(low) __rdtsc();
#define RDTSC_EX( low , high )

#include <iostream>
#include <stdexcept>
#include <sstream>


#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/concurrency/BoostThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransportUtils.h>

//#define DEF_TNonblockingServer
//#define DEF_TThreadedServer
#define DEF_TThreadPoolServer


#if defined (DEF_TNonblockingServer)
#include <thrift/server/TNonblockingServer.h>
#endif

#include "../BCommonThrift/GameServer_cpp/BingoGameServer.h"

using namespace apache::thrift;
using namespace nBingo;

class BingoGameServerHandler : public nBingo::BingoGameServerIf {
public:
	void X2LG_LOGIN(s_LG2X_LOGIN& _return, const s_X2LG_LOGIN& Data)
	{
		printf("recv : X2LG_LOGIN\n");
	}

};

int main(int argc, char **argv) 
{
	int port =9090;

	WSADATA WsaData;
	WSAStartup(MAKEWORD(2, 2), &WsaData);	// 2.2 버전을 로드합니다.

  boost::shared_ptr<BingoGameServerHandler> handler(new BingoGameServerHandler());
  boost::shared_ptr<TProcessor> processor(new nBingo::BingoGameServerProcessor(handler));

  boost::shared_ptr<server::TServerTransport> serverTransport(new transport::TServerSocket(port));

	boost::shared_ptr<server::TProtocolFactory> protocolFactory(new server::TBinaryProtocolFactory());
	boost::shared_ptr<server::TTransportFactory> transportFactory(new transport::TBufferedTransportFactory());


#if defined(DEF_TNonblockingServer)

	//shared_ptr<TTransportFactory> transportFactory_NB(new TFramedTransportFactory());
	boost::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(15);
	boost::shared_ptr<BoostThreadFactory> threadFactory(new BoostThreadFactory());
	threadManager->threadFactory(threadFactory);
	threadManager->start();
	TNonblockingServer server(processor, 
														protocolFactory, 
														port, 
														threadManager);

#elif defined(DEF_TThreadPoolServer)
	const int workerCount = 100;
  boost::shared_ptr<server::ThreadManager> threadManager = server::ThreadManager::newSimpleThreadManager(workerCount);
	boost::shared_ptr<concurrency::BoostThreadFactory> threadFactory(new concurrency::BoostThreadFactory());
  threadManager->threadFactory(threadFactory);
  threadManager->start();
  server::TThreadPoolServer server(processor,
                           serverTransport,
                           transportFactory,
                           protocolFactory,
                           threadManager);

#elif defined(DEF_TThreadedServer)
  server::TThreadedServer server(processor,
                         serverTransport,
                         transportFactory,
                         protocolFactory);

#else
	server::TSimpleServer server(processor,
		serverTransport,
		transportFactory,
		protocolFactory);
#endif

  printf("Starting the server... : port= %d\n",port);
  server.serve();
  printf("done.\n");
  return 0;
}

