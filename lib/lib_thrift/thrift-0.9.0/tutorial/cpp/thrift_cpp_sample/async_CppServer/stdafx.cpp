// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// CppServer.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"

// TODO: 필요한 추가 헤더는
// 이 파일이 아닌 STDAFX.H에서 참조합니다.
#if 0

int main_NonBlock(int argc, char **argv) 
{
	WSADATA WsaData;
	WSAStartup(MAKEWORD(2, 2), &WsaData);	// 2.2 버전을 로드합니다.

	///////////////////////////////////////////////////////////
	// 2) Create the event manager as the first thing in main().
	ThriftWin32EventManger eventMgr;
	///////////////////////////////////////////////////////////

	int port = 9090;
	boost::shared_ptr<CalculatorHandler> handler(new CalculatorHandler());
	boost::shared_ptr<TProcessor> processor(new CalculatorProcessor(handler));

	boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
	boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

	boost::shared_ptr< TNonblockingServer > server = eventMgr.createNonblockingServer( processor, protocolFactory, port );

	server->serve();

	return 0;
}

#endif

