#include "StdAfx.h"
#include "DummyServer.h"
#include "DummyClient.h"
#include "settings.h"

CDummyServer::CDummyServer(void)
{
	m_pClient = NULL;
}

CDummyServer::~CDummyServer(void)
{
}

void CDummyServer::connect( CDummyClient *pClient )
{
	m_pClient = pClient;
	serverToClient( MSG_CONNECT, 0 );
}

void CDummyServer::clientToServer( std::string str )
{
	contacts::test testObject;
	testObject.ParseFromString( str );

	if( testObject.data() > MAX_EXCHANGE_DATA )
	{
		serverToClient( MSG_DISCONNECT, 0 );
	}
	else
	{
		serverToClient( MSG_GAMEDATA, testObject.data() );
	}
}

void CDummyServer::serverToClient( GAMEMESSAGE msg, int data )
{
	if( m_pClient != NULL )
	{
		contacts::test testObject;
		testObject.set_msg( (int)msg );
		testObject.set_data( data );
		
		std::string str;
		testObject.SerializeToString( &str );

		m_pClient->serverToClient( str );
	}
}