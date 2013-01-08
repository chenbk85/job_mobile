/* file : jINet.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-13 20:55:25
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jINet_OGS_header__
#define __jINet_OGS_header__
#pragma once

#include "header/jDefine.h"
#include "util/jUtil.h"
#include "base/jRtti.h"
#include "interface/net/jTypedef_net.h"
#include "interface/net/jINet_asio.h"
#include "interface/net/jIPacketDispatch.h"
#define _ARG_jNamedEventHandler nMech::nNET::jIPacketSocket_IOCP* pS,BYTE *pReadBuff, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP,void* pData

namespace nMech
{
	namespace nSQ
	{
		class SquirrelObject;
	}
	namespace nNET
	{
		typedef void OnPacketSize_UsageInfo_t(nMech::tcstr szPlugIn,nMech::uint64 packet_size,nMech::tname1024_t info);

		//--------------------------------------------------------------------------
		// �Ʒ� 3���� jIPacketDispatch.h"�� ����Ҷ� Ŀ�����ϰ� �����ϴ� �ڵ��̴�.
		//--------------------------------------------------------------------------
		struct jIPacketSocket_IOCP;
		struct _jNamed_Event_Handler {	virtual void Call(_ARG_jNamedEventHandler) const =0;};

		struct jSOCKADDR_IN;
		struct jIGridNode;
		struct jINetGrid;

		enum ESocket_Type
		{
			eNULL_SOCKET,
			eLISTEN_SOCKET,
			eACCEPTED_SOCKET, // m_pPacketSocket[eLISTEN_SOCKET]�� ����� �����̴�. �������� �����ϴ� ���ӵ� ����.
			eCONNECTING_SOCKET, // �ٸ������� ������ Clent socket�̴�.
			eTCP_SOCKET_END,
			eUDP_SOCKET,
		};

		//--------------------------------------------------------------------------
		// jEnCodeInfo
		//--------------------------------------------------------------------------		
		typedef void (*EnCodeFunc)( nMech::uint32 nProtocol, BYTE* pBuf, int nLen, int nRandIdx );
		struct jEnCodeInfo
		{		
			jEnCodeInfo(){};
			jEnCodeInfo( EnCodeFunc e, EnCodeFunc d, int n ) : EnFunc(e), DeFunc(d), RandIdx(n)	{ }
			EnCodeFunc EnFunc;
			EnCodeFunc DeFunc;
			int RandIdx;			
		};

		//--------------------------------------------------------------------------
		// jIPacketSocket_IOCP
		//--------------------------------------------------------------------------
		typedef void SocketDebugPrint_t(struct jIPacketSocket_IOCP*);

		typedef uint32 send_file_cookie_t;

#define jINTERFACE_jIPacketSocket_IOCP(x) public:	\
	virtual void	SetUserData(void* v)##x\
	virtual void*	GetUserData()##x \
	virtual jIGridNode* GetGridNode() ##x \
	virtual BOOL	WritePacket(jPacket_Base* pP)##x\
	virtual BOOL	WriteToPacket(jIP_Address* pIP, jPacket_Base* pP)##x \
	virtual BOOL	WriteToPacket_Direct(jIP_Address* pIP, jPacket_Base* pP) ##x \
	virtual BOOL	WritePacket(jPacket_Base& pP)##x\
	virtual BOOL	WriteToPacket(jIP_Address* pIP, jPacket_Base& pP)##x \
	virtual BOOL	WriteToPacket_Direct(jIP_Address* pIP, jPacket_Base& pP) ##x \
	virtual jIE*	Get_jIE()##x\
	virtual nMech::cstr	GetIP(nMech::tname_t buf)##x\
	virtual int		GetPort()##x\
	virtual SOCKADDR_IN GetAddressADDR() ##x \
	virtual nMech::cstr	GetAddressString(nMech::fname_t buf) ##x \
	virtual nNET::ESocket_Type GetType()##x \
	\
	/*for tcp connection */\
	virtual BOOL  IsConnected(VOID)##x \
	/* socket name defineded by jINet_OGS internal! */\
	virtual nMech::cstr	GetName()##x \
	virtual void DebugPrint()##x \
	virtual void SetDebugger(SocketDebugPrint_t*) ##x\
	/*2009/03/08/HMC jmToDo GPK*/\
	virtual void SetEncode_Decode_Func( const jEnCodeInfo& info )##x\
	/*���� : SendFile�� ������ ��Ŷ�� RECIEVER���� READ_PACKET() ȣ���� uint16 size, sizeof(TCHAR)*size��ŭ �ӽ����� ��Ʈ���� �о���Ѵ�. */\
	/* szRemotePath�� ���� \\�� �ƴϸ� ���ϸ����� �ν�. \\�� ������ �ش� ������ szPath�� ������ ��ġ��Ų��.*/\
	/* return ���� file cookie��. 0�̸� ���� */\
	virtual send_file_cookie_t SendFile(tcstr szPath,tcstr szRemoteJobThread/*=0*/,tcstr szRemotePath/*=0*/,jPacket_Base* pP)##x\

		jINTERFACE_END(jIPacketSocket_IOCP);


/*

jIPacketSocket_IOCP::SendFile(..) ����.

	jIPacketSocket_IOCP*pS;
	pS-> SendFile("test\\test.txt",0,"test\\",pk); // �������� ���� test\test.txt�� �������� �������� �� test������ ����.
	pS-> SendFile("test\\test.txt",0,"test\\test",pk); // �������� ���� test\test.txt�� �������� �������� �� test\test��� ���Ϸ� ����.
	pS-> SendFile("c:\\test\\test.txt",0,0,pk); // c:\test\test.txt�� �������� �ӽ������� ����.

	���� pk�� ���� jNET_EVENT_RECEIVER()���� ��ó���� READ_PACKET_SEND_FILENAME�� ����ؼ� ���ϸ��� ���� �Ľ��ؾ���.
	jNET_EVENT_RECEIVER_P2P(M2A_SEND_FILE,MonitorServer)
	{
		// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
		READ_PACKET_SEND_FILENAME(fileLen, szFileName);
		be_READ_PACKET_P2P_PB(M2A_SEND_FILE);
	}


*/


		struct jNamedEventTable;
		#define jNETARG_SOCK_NUM_BUFF_LEN_IP jIPacketSocket_IOCP* pS, jPacket_Base* pk,jIP_Address* pIP,jNamedEventTable*pHT
		struct jIPlugIn_Net
		{
			jINetGrid* m_pjINetGrid;
			jIE* m_pE;
			jNamedEventTable* m_pPHTL;
			virtual VOID OnIoConnected(jIPacketSocket_IOCP* ){};//tcp��忡���� ȣ���. �������Ӽ�����
			virtual void OnIoRead(jNETARG_SOCK_NUM_BUFF_LEN_IP)
			{
				jNamedEventNode* pHN = pHT->GetByNum(pk->num);
				jWARN(_T("%d:%s"),pk->num,pHN?pHN->m_szName:jS(NULL));
			}//���������� ���� �ȉ����� ȣ���
			virtual VOID OnIoWrote(jIPacketSocket_IOCP*){} // �񵿱� ����Ϸ��뺸��
			virtual VOID OnIoDisconnected(jIPacketSocket_IOCP*){}; // tcp��忡���� ȣ���. ���ݿ��� ����������

			virtual bool ParseCmd(nMech::tcstr szCommand){ return false;}
			virtual void Start(){}// ���񽺰� �⵿ or ��⵿ �Ҷ� ȣ���
			virtual void Stop(){}// ���񽺰� ���⶧ ȣ��
			virtual bool Load_SQ(){ return false;}//sq���� ��ũ��Ʈ ���� �ε�
			virtual nSQ::SquirrelObject* GetSQTable(){return 0;}
			virtual void DoDisconnect(jIPacketSocket_IOCP* pS)=0; // �ش� ������ ������ ȣ������.
		};


		#define jNETARG_NUM_BUFF_LEN jPacketNum_t &dwProtocol, BYTE *pPacketBuff, jPacketLen_t &dwPacketLength

		//--------------------------------------------------------------------------
		// jINetSession_Service
		//--------------------------------------------------------------------------
		struct jIPlugIn_Connection;
		#define jINTERFACE_jINetSession_Service(x) public:	\
			virtual jIPlugIn_Connection* GetPlugIn() ##x\
			virtual void Release() ##x \
			\
			virtual jIPacketSocket_IOCP* ReadPacket(jNETARG_NUM_BUFF_LEN)##x \
			virtual jIPacketSocket_IOCP* ReadFromPacket(jNETARG_NUM_BUFF_LEN , jIP_Address*pIP)##x \
			\
			/* IOCPSessoin���� Get_ClientSocket("TEST001:SessionServer") �� ���������� m_pE->FindByPath()�� ã�´�*/\
			virtual jIPacketSocket_IOCP* Get_ClientSocket(nMech::cstr sz) ##x \
			virtual jIPacketSocket_IOCP* Start_ClientSocket(jIE* peSocketNode)##x\
			virtual void Stop_ClientSocket(jIE* peSocketNode,bool isRelease) ##x\

		jINTERFACE_END(jINetSession_Service);

		//--------------------------------------------------------------------------
		//jIServer_IOCP
		//--------------------------------------------------------------------------
		struct jIPlugIn_Server_IOCP;
		#define jINTERFACE_jIServer_IOCP(x) public:	\
			virtual bool StartServer(jIE* peNetNode)##x\
			virtual void EndServer()##x\
			\
			virtual jIPlugIn_Server_IOCP* GetPlugIn() ##x\
			virtual void Release() ##x\
			\
			virtual void DisconnectTcpClient(jIPacketSocket_IOCP*)##x\
			virtual jIPacketSocket_IOCP* GetUdpListenSocket()##x\
			virtual jSOCKADDR_IN* GetTcpListenAddress()##x\
			virtual jIPacketSocket_IOCP* GetUdpSocket(nMech::StringID &id)##x\
			virtual jIPacketSocket_IOCP* AddUdpSocket(nMech::StringID &id,nMech::cstr szIP,int port)##x\

		jINTERFACE_END(jIServer_IOCP);

		//--------------------------------------------------------------------------
		// jIPlugIn_Server_IOCP
		//--------------------------------------------------------------------------
		struct jIPlugIn_Server_IOCP :  public nMech::jRttiObj ,public jIPlugIn_Net
		{
			jIServer_IOCP* m_pServer;
			jIPlugIn_Net* BaseI(){ return (jIPlugIn_Net*)this;} 
			void DoDisconnect(jIPacketSocket_IOCP* pS)
			{ 
				if(pS->GetType() != nNET::eUDP_SOCKET)
					m_pServer->DisconnectTcpClient(pS);
				else
				{
					jASSERT0(0 && "jIPlugIn_Server_IOCP::DoDisconnect : pS == eUDP_SOCKET");
				}
			}
		};

		//--------------------------------------------------------------------------
		// jIPlugIn_Connection
		//--------------------------------------------------------------------------
		struct jIPlugIn_Connection : public nMech::jRttiObj , public jIPlugIn_Net
		{
			jINetSession_Service* m_pClientSession;
			jIPlugIn_Net* BaseI(){ return (jIPlugIn_Net*)this;} 
			void DoDisconnect(jIPacketSocket_IOCP* pS)
			{
				m_pClientSession->Stop_ClientSocket(pS->Get_jIE(), false/*scheduled disconnecting */);
			}
		};


		struct jINet_Util;
		struct jINetGrid;
		typedef void for_each_jINetGrid_func_t(tcstr sPlugIn,jINetGrid*);

		//jIPacketSocket_IOCP::SendFile�ÿ� ȣ��Ǵ� �������ۻ��¿�.
		struct SocketDebugPrint_SendFile_Info
		{
			enum ESendMode{eSEND,eRECV};
			ESendMode eMode; // ������ ������ , �޴�������.
			send_file_cookie_t cookie; // ���� ��Ű
			int iFileSize; // �����ų� ���� ������ ��üũ��.
			int iCurrSize; // �ްų� ���� ���� ������.
			tcstr szFile; //���� �������� ���ϸ�.
			int remainFileCount;//���� ���ϼ�
		};
		typedef void SocketDebugPrint_SendFile_t(struct jIPacketSocket_IOCP*,SocketDebugPrint_SendFile_Info*);

		//--------------------------------------------------------------------------
		// jINet_OGS
		//--------------------------------------------------------------------------
		#define jINTERFACE_jINet_OGS(x) public:	\
			virtual int ProcessMsg(nMech::cstr szMsg, void* pData)##x \
			virtual void Begin(bool coInit)##x \
			virtual void End()##x \
			\
			/* jIMsgManager::FrameMove()�� ������ �����Ѵ�. ���ڰ� true�̸� ������ ����*/\
			virtual void RunMessageThread(bool isStopThread=false)##x\
			\
			virtual nMech::cstr GetSocketError(int iError, jIE** ppE=0) ##x\
			\
			virtual bool CreateNetObject(jIE* peNetList) ##x \
			virtual void RunNetObject(jIE* peNetObj)##x\
			virtual void StopNetObject(jIE* peNetList,bool isRelease=false,bool isImmediately=true) ##x \
			\
			virtual acstr GetHostName()##x\
			virtual acstr GetHostIpString(int idx)##x\
			virtual jINet_Util* GetUtil()##x\
			virtual void FrameMove()##x\
			virtual jIPlugIn_Net* GetPlugIn(jIE* peNetConfigNode)##x \
			virtual void SetCallback_PacketSize_UsageInfo(OnPacketSize_UsageInfo_t*)##x\
			virtual void for_each_jINetGrid(for_each_jINetGrid_func_t*)##x\
			virtual void SetDebugger_SendFile(SocketDebugPrint_SendFile_t* fn)##x\
			virtual struct jIClientSessionManager* Get_jIClientSessionManager() x\

			jINTERFACE_END(jINet_OGS);


		/* *_* by icandoit : 2007-07-02 16:50:12
		inline void jINet_OGS_Init()
		{
		HMODULE hM = ::LoadLibrary( "jNet.DLL" );
		assert(hM);
		jCreateInterface_t* pFunc = (jCreateInterface_t*)::GetProcAddress(hM, "jCreateInterface"));
		pFunc(0);
		}
		*/ //*_* by icandoit : 2007-07-02 16:50:15

	}//namespace nNET
	namespace nInterface
	{
		extern JBASE_API nNET::jINet_OGS* g_pjINet_OGS;
	}

}

#define jNET_EVENT_BEGIN					jNAMED_EVENT_BEGIN
#define jNET_EVENT_END						jNAMED_EVENT_END

//--------------------------------------------------------------------------
// P2P���� Ŭ���̾�Ʈ ������ ������ ��� ��Ʈ�� ���ù��� ���� ������ ���
//--------------------------------------------------------------------------
#define jNET_EVENT_RECEIVER					jNAMED_EVENT_RECEIVER
#define jNET_EVENT_RECEIVER_P2P_SERVER_tcp	jNAMED_EVENT_RECEIVER

// xml�� ��Ŷ���� jIE*�� �ش��ϴ� ������.
#define jNET_EVENT_RECEIVER_xml(PACKET,xml) S_##PACKET Data; Data.xml=GetjIXml()->CreateElement(); jNET_EVENT_RECEIVER(PACKET,Data)

//--------------------------------------------------------------------------
// P2P���� TCP or UDP Ŭ���̾�Ʈ ���������� ���ù������� ���.
//--------------------------------------------------------------------------
#define jNET_EVENT_RECEIVER_P2P				jNAMED_EVENT_RECEIVER2


#define JNET_PLUGIN_SINGTONE_DECL(NAME)\
	private: static NAME* ms_p##NAME;static nMech::nUtil::jCriticalSection ms_cs##NAME;\
	public : static void Set(NAME* p){ nMech::nUtil::jCriticalSection::Auto a(&ms_cs##NAME); ms_p##NAME= p;}\
	public : static NAME* Get() {nMech::nUtil::jCriticalSection::Auto a(&ms_cs##NAME); return ms_p##NAME;}

#define JNET_PLUGIN_SINGTONE_DEFINE(NAME)	NAME* NAME::ms_p##NAME=0; nMech::nUtil::jCriticalSection NAME::ms_cs##NAME;

#ifdef _DEBUG
#define _jNET_SEND_DEBUG(X) jLOG(_T("send : ")  jS(X) );
#else
#define _jNET_SEND_DEBUG(X)
#endif

#define jNET_SEND2(SOCK,PACKET,...) SOCK.WritePacket(WRITE_##PACKET(buf,__VA_ARGS__ ) );_jNET_SEND_DEBUG(PACKET);

#define jNET_SEND(SOCK,PACKET,...) if(SOCK){SOCK->WritePacket(&WRITE_##PACKET(buf,__VA_ARGS__ ) ); _jNET_SEND_DEBUG(PACKET);}
#define jNET_SEND_B(SOCK,PACKET,buf,...) if(SOCK)SOCK->WritePacket(&WRITE_##PACKET(buf,__VA_ARGS__ ) );_jNET_SEND_DEBUG(PACKET);
#define jNET_SEND_N(SOCK,PACKET,NAME_SPACE,...) if(SOCK)SOCK->WritePacket(&NAME_SPACE::WRITE_##PACKET(buf,__VA_ARGS__ ) );_jNET_SEND_DEBUG(PACKET);
#define jNET_SEND_NB(SOCK,PACKET,NAME_SPACE,buf,...) if(SOCK)SOCK->WritePacket(&NAME_SPACE::WRITE_##PACKET(buf,__VA_ARGS__ ) );_jNET_SEND_DEBUG(PACKET);

#define jNET_SEND_FILE(SOCK,szPath,szRemotePath,PACKET,...) if(SOCK){SOCK->SendFile(&WRITE_##PACKET(buf,__VA_ARGS__ ) ); _jNET_SEND_DEBUG(PACKET);}
#define jNET_SEND_FILE_B(SOCK,szPath,szRemotePath,PACKET,buf,...) if(SOCK)SOCK->SendFile(&WRITE_##PACKET(buf,__VA_ARGS__ ) );_jNET_SEND_DEBUG(PACKET);
#define jNET_SEND_FILE_N(SOCK,szPath,szRemotePath,PACKET,NAME_SPACE,...) if(SOCK)SOCK->SendFile(&NAME_SPACE::WRITE_##PACKET(buf,__VA_ARGS__ ) );_jNET_SEND_DEBUG(PACKET);
#define jNET_SEND_FILE_NB(SOCK,szPath,szRemotePath,PACKET,NAME_SPACE,buf,...) if(SOCK)SOCK->SendFile(&NAME_SPACE::WRITE_##PACKET(buf,__VA_ARGS__ ) );_jNET_SEND_DEBUG(PACKET);


#endif // __jINet_OGS_header__
			