#pragma once
#include "gameMessage.h"

#pragma comment(lib, "libprotobuf.lib")
#pragma comment(lib, "libprotobuf-lite.lib")
#pragma comment(lib, "libprotoc.lib")
#include "test.pb.h"

class CDummyClient;

class CDummyServer
{
public:
	CDummyServer(void);
	~CDummyServer(void);

	void connect( CDummyClient *pClient );
	void clientToServer( std::string str );

private:
	CDummyClient *m_pClient;
	void serverToClient( GAMEMESSAGE msg, int data );
};
