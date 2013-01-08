/* file : Recv_TestServer.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-28 17:05:50
comp.: wiki.test.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TestClient.h"
#include "PlugIn_ToBackEnd.h"

jNET_EVENT_BEGIN(PlugIn_ToBackEnd)
{
	namespace _from_TestServer
	{
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(S_HELLO,TestServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			be_READ_PACKET_P2P_PB(S_HELLO);
		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(S_ECHO,TestServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			be_READ_PACKET_P2P_PB(S_ECHO);

			if(Data.type==0)
			{
				jLOG(_T("S_ECHO(%d) %s"),Data.type, Data.msg.c_str());
			}
			else
			{
				jLOG(_T("\t%s"),Data.msg);
			}

#if 0
			if( Data.msg[0]=='%' ) 
			{
				tstring str = Data.msg+1;

				if( isdigit(str[0]))
				{

					TCHAR* ch = jt_strchr(Data.msg+1 , ' ');
					if(!ch) return;
					*ch=0;
					int id = jt_atoi(Data.msg+1);
					if(id != pBE->m_DummyID) return;
					++ch;
					str =ch; 
				}
				if(nCONSOLE::Get_jIConsoleCmd()->ParseCmd(jT(str) ))
				{
					nswb1024_t buf;
					pS->WritePacket(&WRITE_TS_ECHO(buf
						, jA(pBE->m_DummyName)
						,str.c_str()
						,2));
				}
#endif
			}
		
#if 0
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(aaa,TestServer)
		{
			// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
			be_READ_PACKET_P2P_PB(aaa);
		}
#endif

	}//namespace _from_TestServer

}
jNET_EVENT_END(PlugIn_ToBackEnd)
