// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// CppServer.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"

// TODO: �ʿ��� �߰� �����
// �� ������ �ƴ� STDAFX.H���� �����մϴ�.
#if 0

int main_NonBlock(int argc, char **argv) 
{
	WSADATA WsaData;
	WSAStartup(MAKEWORD(2, 2), &WsaData);	// 2.2 ������ �ε��մϴ�.

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

