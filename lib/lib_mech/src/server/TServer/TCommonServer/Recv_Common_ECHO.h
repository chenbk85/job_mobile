/* file : Recv_Common_ECHO.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-18 22:37:02
comp.: t3.co.kr
title : 
desc : 

*/




//jNET_EVENT_BEGIN(PlugIn_Connect) // 내가 접속한 서버로 부터 날라오는 패킷.
namespace __from_connectingServer_ECHO
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(C_ECHO,CentralServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		READ_PACKET(C_ECHO);		
		if(Data.msg[0]!='$') return;
		g_SG.ParseRemoteCmd(Data.msg,jsSERVER_NAME);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(CD_ECHO,CommandServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		READ_PACKET(CD_ECHO);		
		if(Data.msg[0]!='$') return;
		g_SG.ParseRemoteCmd(Data.msg,jsSERVER_NAME);
	}

#define for_each_ECHO_634(X) X(U,User) X(MG,Msg) X(W,World) X(A,Auction) X(M,Mail) X(T,Trade) X(DC,DBCache) 
#define Recv_ECHO_634(SERVER_TAG,SERVER_NAME) jNET_EVENT_RECEIVER_P2P(SERVER_TAG##_ECHO,SERVER_NAME##Server){READ_PACKET(SERVER_TAG##_ECHO);}
	for_each_ECHO_634(Recv_ECHO_634);

}//__from_connectingServer_ECHOF
//jNET_EVENT_END(PlugIn_Connect)
