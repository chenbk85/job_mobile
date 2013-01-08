/* file : jNet.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-08 15:25:09
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jNet_header__
#define __jNet_header__
#pragma once

#ifdef JNET_OGS_EXPORTS
#define JNET_OGS_API WINDOWS_DLL_TAG
#else
#define JNET_OGS_API __declspec(dllimport)
//#pragma comment(lib, "jNet.lib")
#endif

#include "interface/net/jINet.h"
#include "base/jMsgManager.h"
#include "interface/jIThread.h"
#include "jQueueManger.h"


using namespace std;
namespace nMech
{

	namespace nNET
	{
		namespace Impl
		{
			struct jIProactor_IOCP;
			class jNetSession_CS;

			//--------------------------------------------------------------------------
			class jNet : public jINet_OGS
			//--------------------------------------------------------------------------
			{
				jINTERFACE_HEADER(jINet_OGS);
			private:
				bool m_bCoInit;
				jIE* m_peDLL;
			public:
				SocketDebugPrint_SendFile_t* m_pSocketDebugPrint_SendFile;
				nEVENT::jIMsgManager* m_pMM_PacketPump;
				nEVENT::jIMsgManager* m_pMM_Util; //일반적 메세지 처리용

				afname_t m_szHostName;
				afname_t m_szNetHostName;
				std::vector<std::astring> m_listNetHostAlias;
				std::vector<std::astring> m_listNetHostIP;

			public:
				jNet(jIE* pE);
				~jNet();
				void _createNetObject(jIE* peNetObj);
				void  _runNetObject(jIE* pE);
				void  _stopNetObject(jIE* pE,bool isRelease);
				void logNetworkInfo();
				jLIST_TYPEDEF_map(tstring , jIE*, m_peNetObjList);
				static void CloseSocket( SOCKET socketClose , bool bIsForce=false );
				
				void _StopNetObject(jIE* peNetList,bool isRelease);
				void DoWakeUp_Msg();

				jINetSession_Service* CreateClientSession(cstr szPlugIn,jIE* peNetNode);
				jIServer_IOCP* CreateUdpServer_IOCP(cstr szPlugIn ,jIE* peNetNode);
				jIServer_IOCP* CreateTcpServer_IOCP(cstr szPlugIn ,jIE* peNetNode);
				jIServer_IOCP* CreateTcpUdpServer_IOCP(cstr szPlugIn , jIE* peNetNode);
				jINetSession_Service* CreateNetSession_CS(cstr szPlugIn,jIE* peNetNode);
				jINetSession_Service* jNet::Create_jClient_IOCP(cstr szPlugIn,jIE* pE);

				jINetSession_Service* GetNetSession(jIE*);
				jIServer_IOCP* GetServer(jIE*);

				jIProactor_IOCP* GetProactor(jIE* pePlugIn);
				void DeleteProactor(jIProactor_IOCP*);


			public:
				//--------------------------------------------------------------------------
				// packet thread_name -> job thead pool
				//--------------------------------------------------------------------------
				struct _JobThreadPoolNode
				{
					nEVENT::jIMsgManager* m_pMM;
					nNET::nUTIL::jCircularQueueBuffer* m_pQ;
					void* m_pPlugIn;
					void* pData;
				};
				jLIST_TYPEDEF_map(tstring/*thread_name*/,_JobThreadPoolNode,m_mapJobThreadPool);
				void Push_To_PacketJobThread(tcstr thead_name , tcstr szPlugIn,jPacketNum_t dwProtocol,_ARG_jNamedEventHandler);


			};//class jNet : public jINet_OGS
			inline acstr jNet::GetHostName(){return m_szHostName;}
			inline void jNet::FrameMove()
			{
				m_pMM_PacketPump->Run();
			}

			extern cstr ip_string_convert(cstr szIP , tname32_t buf);
			void jNET_Plugin_callback_OnIoConnected(jIPlugIn_Net* m_pPlugIn, jIPacketSocket_IOCP* pS);
			void jNET_Plugin_callback_OnIoDisconnected(jIPlugIn_Net* m_pPlugIn, jIPacketSocket_IOCP* pS);
			void jNET_Plugin_callback_Start(jIPlugIn_Net* m_pPlugIn);
			void jNET_Plugin_callback_Stop(jIPlugIn_Net* m_pPlugIn);

			extern tcstr _L2G_IP(std::tstring & outAddress );
			extern int _Get_IP_PORT(tcstr szIP, std::tstring & outAddress );


		}// nNet::Impl
		extern Impl::jNet *g_pjNet ;
		extern jIPacketDispatch* g_pjIPacketDispatch;
		extern nThread::jIThreadManager* g_pjIThreadManager;


		extern OnPacketSize_UsageInfo_t* m_pFunc_OnPacketSize_UsageInfo;
		extern uint64 m_iPacketSize_UsageInfo;


		// S : Sender , R : Reciever
		#define for_each_ESendFile(X)\
			X(eNET_SEND_FILE_BEGIN				,"S->R ,pS->SendFile()시 최초 알림")\
			X(eNET_SEND_FILE_DATA				,"S->R ,파일데이타 보냄")\
			X(eNET_SEND_FILE_DATA_NEXT_REQ		,"S<-R ,파일데이타 계속보내라고 통보")\
			X(eNET_SEND_FILE_CANCEL_REQ			,"S<-R ,SendFile한 쪽에 파일보내기 실패 알림.")\
			X(eNET_SEND_FILE_END				,"S->R ,파일보냄 끝 알림.")\
			X(eNET_SEND_FILE_CANCEL				,"S->R ,파일보내기 실패 알림.")\


		jDEFINE_ENUM_CODE2(ESendFile);

	} //nNET
}//nMech

#define m_pPlugIn_Start() jNET_Plugin_callback_Start(m_pPlugIn)

#define m_pPlugIn_Stop() jNET_Plugin_callback_Stop(m_pPlugIn)


#include "interface/net/jNet_util.h"

//Get_jPlugInHelpNode(pHT,pk.num); // jNamedEventNode* pPHN , tcstr sz
#define Get_jPlugInHelpNode(pHT, num)\
jNamedEventNode* pPHN = pHT->GetByNum(num);\
if(!pPHN)\
{\
	jWARN(_T("pk.num is unknown : %d") , num);\
	pS->Get_jIE()->DebugPrint(true);\
	continue;\
}\
tcstr sz = pPHN->m_szName;\
fname_t buf;\



#define call_SQ_jNetEvent(udp_imcomming_ip)\
SquirrelFunction<void> func(*pSO,buf);\
if(!func.func.IsNull())\
{\
	try \
	{	\
		func(pS->BaseI(),&pk,udp_imcomming_ip);\
	} \
	catch (SquirrelError & e) \
	{\
		jWARN(_T("SQ Error: %s (%s)\n"),e.desc,_T(__FUNCTION__) ); \
	};\
	continue;\
}\


#define jPARSE_eNET_SEND_FILE(pS)\
BYTE pReadBuff_eNET_SEND_FILE[MAX_BUFFER_LENGTH] = {0,};\
jPacket_Base pk;\
pk.buf = pReadBuff_eNET_SEND_FILE;\
ESendFile eType = pS->Recv_eNET_SEND_FILE(pReadBuff, dwPacketLength,pk);\
if(eType!=eNET_SEND_FILE_END) continue;\
ZeroMemory(pReadBuff,sizeof(pReadBuff));\
memcpy(pReadBuff ,pk.buf, pk.GetLen() );\
dwPacketLength = pk.GetLen();\
dwProtocol = pk.num;\




#endif // __jNet_header__
