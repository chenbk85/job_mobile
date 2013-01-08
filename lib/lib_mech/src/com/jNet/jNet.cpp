// jNet.cpp : DLL 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "jNet.h"
#include <objbase.h>
#include "interface/xml/jIElement.h"
#include "jNetSession_Client.h"
#include "base/jxVar.h"
#include "jNetSession_CS.h"
#include "interface/jILog.h"
#include "interface/net/jNet_util.h"
#include "jNetIOModel_IOCP.h"
#include "interface/Squirrel/jISquirrel.h"
#include "interface/jIConsoleCmd.h"
#include "jClient_IOCP.h"
#include "interface/ITimer.h"
#include "Interface/net/jINet_Util.h"
#include "interface/jISystemPlugIn.h"
#include "Interface/xml/jIXmlUtil.h"

#ifndef jFUNC1 
#define jLogT(type) g_Current_LogLevel_jStringID,jx(type)
#define jLogL g_Current_LogLevel_jStringID,jx(NULL)
#define jFUNC1 _T(__FUNCTION__) _T(">")
#endif //jFUNC1 
#include "interface/jIThread.h"



volatile float aaa;

DECLARE_INSTANCE_TYPE(jIE);

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{

	aaa++;
	float _aaa = aaa;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

namespace nMech
{

	namespace nNET
	{

		OnPacketSize_UsageInfo_t* m_pFunc_OnPacketSize_UsageInfo=0;
		uint64 m_iPacketSize_UsageInfo=0;


		jIVar* pvIsRUN_MSG_FRAME_MOVE=jCV(jINet_OGS,IsRUN_MSG_FRAME_MOVE, false,0,"if 1 then create thread for nMech::nEVENT::jIMsgManager::FrameMove()");

		Impl::jNet *g_pjNet ;
		jIPacketDispatch* g_pjIPacketDispatch=0;
		nThread::jIThreadManager* g_pjIThreadManager=0;
		nThread::jIThread* g_pjINet_MsgManager_thread=0;
		bool g_isMsgThread_jIMsgManager=0;
		namespace Impl
		{
			void jNet::DoWakeUp_Msg()
			{
				if(g_pjINet_MsgManager_thread)
					g_pjINet_MsgManager_thread->DoWake();
			}


			static void jIMsgManager_FrameMove( nThread::jIThread* pT)
			{
				for(;pT->IsRun();)
				{
					nTIME::Get_ITimer()->Update();
					nMech::nEVENT::jIMsgManager::FrameMove();
					Sleep(13);
				}
			}

			static void PacketPump_by_GameClient()// 클라이언트에서는 스레드를 생성안하고 게임루프에서 콜해야하므로
			{
				g_pjNet->m_pMM_PacketPump->Run(); 
			}
			static void PacketPump_Waked( nThread::jIThread* )
			{
				g_pjNet->m_pMM_PacketPump->Run(); 
				//nMech::nEVENT::jIMsgManager::FrameMove();
			}
			static void PacketPump_Normal(nThread::jIThread*)
			{
				g_pjNet->m_pMM_PacketPump->Run(); 
				//nMech::nEVENT::jIMsgManager::FrameMove();
				Sleep(1);
			}

			extern "C"
			{

				JNET_OGS_API void* jCreateInterface(jIE* pE)
				{
					g_pjIThreadManager = jCREATE_INTERFACE(nMech::nThread::jIThreadManager);
					jASSERT0(g_pjIThreadManager && _T("jINet::g_pjIThreadManager()"));
					g_pjIPacketDispatch= jCREATE_INTERFACE(nMech::nNET::jIPacketDispatch);
					jASSERT0(g_pjIPacketDispatch&& _T("jINet::g_pjIPacketDispatch()"));
					g_pjNet = new jNet(pE);
					nInterface::g_pjINet_OGS = g_pjNet;

					jIVar* pvBegin= jCV(jINet_OGS,Auto_Begin,true,0,"Call Begin() when jINet_OGS.DLL loading time");
					jIVar* pvCoInit = jCV(jINet_OGS,CoInitialize,true,0,"Is call CoInitialize when jINet_OGS::Begin()");
					if(pvBegin->Get_bool()) 
						g_pjNet->Begin(pvCoInit->Get_bool());

					return nInterface::g_pjINet_OGS;
				}
				JNET_OGS_API void jDeleteInterface()
				{
					g_pjIThreadManager->Release();
					g_pjIPacketDispatch->Release();
					jIVar* pvBegin= nCONSOLE::Get_jIConsoleVar()->GetVar(_T("jINet_OGS"),_T("Auto_Begin"));
					if(pvBegin->Get_bool())
					{
						if(g_pjNet)
							g_pjNet->End();
					}
					SAFE_DELETE(g_pjNet);

				}
				JNET_OGS_API acstr jGetModuleOwnerName()
				{
					return ("icandoit");
				}
			}

			void JOB_PacketSize_Info(nEVENT::jIMessage* pMsg)
			{
#if 0
				if(!g_pjNet) return;
				if(!g_pjNet->m_pFunc_OnPacketSize_UsageInfo) return;
				tname1024_t buf;
				g_pjNet->m_pFunc_OnPacketSize_UsageInfo(0 , m_iPacketSize_UsageInfo , buf);
				m_iPacketSize_UsageInfo=0;
#endif
				//g_pjNet->DoWakeUp_Msg();
			}
			jNet::jNet(jIE* pE)
				:m_bCoInit(false)
				,m_peDLL(pE)
				,m_pSocketDebugPrint_SendFile(0)
			{

				m_pMM_PacketPump = nEVENT::jIMsgManager::Get(_T("_nNET::jNet"),true);
				// Winsock을 사용하기 위한 DLL 로드
				WSADATA WsaData;
				WSAStartup(MAKEWORD(2, 2), &WsaData);	// 2.2 버전을 로드합니다.

				nInterface::g_pjINet_OGS= this;

				m_pMM_Util = nEVENT::jIMsgManager::Get(jS(nNET::jNet),true);
				float sec = pv_OnPacketSize_UsageInfo_TIME->Get_float();
				nEVENT::jIMessage* pM = m_pMM_Util->Regist_TimeBase(0,jFUNC_Msg(JOB_PacketSize_Info), 0,sec);
				pM->DoWakeUp();
			}
			jNet::~jNet()
			{
				WSACleanup();
			}

			acstr jNet::GetHostIpString(int idx)
			{
				if(idx >=0 && (size_t)idx < m_listNetHostIP.size())
					return m_listNetHostIP[idx].c_str();
				return ("127.0.0.1");
			}

			void jNet::Begin(bool coInit)
			{
				m_bCoInit = coInit;
				if(m_bCoInit)
					::CoInitializeEx(NULL, COINIT_MULTITHREADED);

				if(!gethostname(m_szHostName, sizeof(m_szHostName)))
				{
					struct	hostent *hp;
					hp = gethostbyname(m_szHostName);
					if (hp) 
					{
						jLOG(_T("network hostname: %s"),nUNI::scb256_t(hp->h_name).getT());
						ja_strcpy(m_szNetHostName, hp->h_name);
						int i = 0;
						while(hp->h_aliases[i]) 
						{
							m_listNetHostAlias.push_back(hp->h_aliases[i]);
							jLOG(_T("  alias: %s\n"), hp->h_aliases[i]);
							i++;
						}

						i = 0;
						while(hp->h_addr_list[i])
						{
							sockaddr_in host_in;
							memcpy(&(host_in.sin_addr), hp->h_addr_list[i], hp->h_length);
							afname_t szBuf;
#if defined(LINUX)
							const in_addr_windows *pin_addr_win = reinterpret_cast<const in_addr_windows*>(&host_in.sin_addr);
							sprintf(szBuf,_T("%d.%d.%d.%d"),		//  port:%d  family:%x"),	
								(int)(pin_addr_win->S_un.S_un_b.s_b1),
								(int)(pin_addr_win->S_un.S_un_b.s_b2),
								(int)(pin_addr_win->S_un.S_un_b.s_b3),
								(int)(pin_addr_win->S_un.S_un_b.s_b4));
							jLOG(_T("  ip:%s"),szBuf);
#else
							ja_sprintf(szBuf,("%d.%d.%d.%d"),		//  port:%d  family:%x"),	
								(int)(host_in.sin_addr.S_un.S_un_b.s_b1),
								(int)(host_in.sin_addr.S_un.S_un_b.s_b2),
								(int)(host_in.sin_addr.S_un.S_un_b.s_b3),
								(int)(host_in.sin_addr.S_un.S_un_b.s_b4));
							//		(int)host_in.sin_port,(unsigned int)host_in.sin_family);
							jLOG(_T("  ip:%s"),nUNI::scb64_t(szBuf).getT());
#endif
							m_listNetHostIP.push_back(szBuf);
							i++;
						}
					}
				}
				else
					ja_strcpy(m_szHostName,("NULL"));

				if(!pv_Custom_MsgLoop->Get_int())
				{
					if( pv_UseMsgManagerEvent->Get_bool() )
					{
						nThread::thread_func_t f = PacketPump_Waked;
						g_pjINet_MsgManager_thread = g_pjIThreadManager->Run_Wake(f,jS(jIN),jS(PacketPump_Waked));
					}
					else
					{
						nThread::thread_func_t f = PacketPump_Normal;
						g_pjIThreadManager->Run(f,jS(jIN),jS(PacketPump_Normal),false);
					}
				}
				else
				{
					jSystemPlugIn_func fn;
					fn.m_OnFrameMove = PacketPump_by_GameClient;
					fn.m_isFirst_OnFrameMove = true;
					Get_jISystemPlugIn()->Regist(this,&fn );

				}
				if(pvIsRUN_MSG_FRAME_MOVE->Get_bool())
				{
					g_isMsgThread_jIMsgManager = true;
					nThread::thread_func_t f = jIMsgManager_FrameMove;
					g_pjIThreadManager->Run(f,jS(jIN),jS(jIMsgManager_FrameMove));
				}
			}

			void jNet::RunMessageThread(bool isStopThread)
			{
				if(isStopThread)
				{
					jASSERT0(0 && "jNet::RunMessageThread");
					g_pjIThreadManager->End(jS(jIN),0);
				}
				else
				{

					if(g_pjIThreadManager->IsRun(jS(jIN),jS(jIMsgManager_FrameMove)) == nThread::eTS_START)
						return;
					if(g_isMsgThread_jIMsgManager)
						return;

					nThread::thread_func_t f = jIMsgManager_FrameMove;

					g_pjIThreadManager->Run(f,jS(jIN),jS(jIMsgManager_FrameMove));
					g_isMsgThread_jIMsgManager = true;
				}
			}

			void jNet::End()
			{
				//jMB(jS(jIN), _T("end"));
				g_pjIThreadManager->End(jS(jIN),0);
				g_pjIThreadManager->EndAll();
				// Winsock을 Unload합니다.
				WSACleanup();
				if(m_bCoInit)
					CoUninitialize();
			}

			cstr jNet::GetSocketError(int iError, jIE** ppE)
			{
				if(ppE) *ppE =0;
				static jID* pDocError = GetjIXml()->Load(_T("xml\\system\\jSocketError.xml"));
				if(!pDocError)
				{
					return _T("jSocketError.xml not loaded");
				}
				jIE* pE = pDocError->BaseI()->FindByFirstAttr(_T("id"),jIVar::EDint, &iError);
				if(!pE)
				{
					return _T("not found error string");
				}
				if(ppE)
				{
					*ppE = pE;
				}
				return pE->Get_cstr();
			}
			int jNet::ProcessMsg(cstr szMsg , void* pData)
			{
				if(!jt_strcmp(szMsg,_T("LogNetworkInfo")))
				{
					//logNetworkInfo();
				}
				else if(!jt_strcmp(szMsg,_T("g_pjIThreadManager->EndAll()")))
				{
					g_pjIThreadManager->EndAll();
				}

				return 0;
			}

			struct jxjClient_IOCP_create_node
			{
				jClient_IOCP* pObj;
				jxjClient_IOCP_create_node(jClient_IOCP*p):pObj(p){}
				void operator()(jIE* it)
				{
					if(!it->size())
						pObj->add_ClientSocket(it);
				}
			};
				
			void _make_OverrideAttribute(jIE* pE)
			{
				nXML::jE e = pE;
				nXML::jE eOverrideRoot = pE->GetRoot()->Find(jS(OverrideAttribute));
				if(eOverrideRoot.empty()) return;

				jVar v = e.Attr(jS(TYPE));
				if(v.empty()) return;
				nXML::jE eOverride; 
				if(v->IsContents(jS(TcpServer)))
				{
					jVar overrideName = e->PersistAttr(jS(NAME),jS(NULL));
					eOverride = eOverrideRoot(overrideName->Get_cstr());
					if(eOverride.empty()) eOverride = eOverrideRoot;

					Get_jIXmlUtil()->GetOverrideAttr(pE , jS(ENABLE), jIVar::EDbool,_T("1") , eOverride);
					Get_jIXmlUtil()->GetOverrideAttr(pE , jS(ServerTcpPort), jIVar::EDint,_T("0") , eOverride);
					Get_jIXmlUtil()->GetOverrideAttr(pE , jS(ServerIP), jIVar::EDcstr,_T("PRIVATE_IP") , eOverride);
					Get_jIXmlUtil()->GetOverrideAttr(pE , jS(MaxTcpUser), jIVar::EDint,_T("100") , eOverride);
					Get_jIXmlUtil()->GetOverrideAttr(pE , jS(QueueSize), jIVar::EDint,_T("500") , eOverride);
					Get_jIXmlUtil()->GetOverrideAttr(pE , jS(PACKET_HEADER_TYPE), jIVar::EDcstr,_T("DEFAULT") , eOverride);
					Get_jIXmlUtil()->GetOverrideAttr(pE , jS(ThreadCount), jIVar::EDint,_T("0") , eOverride);
					Get_jIXmlUtil()->GetOverrideAttr(pE , jS(HEADER), jIVar::EDStringID,_T("NULL") , eOverride);
				}
				else if(v->IsContents(jS(IOCPSession)))
				{
					Get_jIXmlUtil()->GetOverrideAttr(pE , jS(ENABLE), jIVar::EDbool,_T("1") , eOverrideRoot);
					Get_jIXmlUtil()->GetOverrideAttr(pE , jS(QueueSize), jIVar::EDint,_T("500") , eOverrideRoot);
					Get_jIXmlUtil()->GetOverrideAttr(pE , jS(ThreadCount), jIVar::EDint,_T("0") , eOverrideRoot);
					jIE* it = pE->begin();
					jrFOR(it)
					{
						eOverride = eOverrideRoot(it->GetTagName());
						if(eOverride.empty()) eOverride = eOverrideRoot;

						Get_jIXmlUtil()->GetOverrideAttr(it , jS(ENABLE), jIVar::EDbool,_T("1") , eOverride);
						Get_jIXmlUtil()->GetOverrideAttr(it , jS(TYPE), jIVar::EDcstr,_T("TCP") , eOverride);
						Get_jIXmlUtil()->GetOverrideAttr(it , jS(PACKET_HEADER_TYPE), jIVar::EDcstr,_T("DEFAULT") , eOverride);
						Get_jIXmlUtil()->GetOverrideAttr(it , jS(HEADER), jIVar::EDStringID,_T("NULL") , eOverride);
						Get_jIXmlUtil()->GetOverrideAttr(it , jS(SERVER_ONLINE_ACTION), jIVar::EDcstr,_T("NULL") , eOverride);

						if(it->GetVar()->IsType(jIVar::ETelement) 
							|| (it->GetVar()->IsType(jIVar::EDcstr) 
								&& ( it->IsContents(jS(NULL))  
									|| !jt_strlen(it->Get_cstr()) 
									)
								)
							)
						{
							jIVar* pvPort = Get_jIXmlUtil()->GetOverrideAttr(it , jS(ServerTcpPort), jIVar::EDint,_T("0") , eOverride);
							jIVar* pvIP = Get_jIXmlUtil()->GetOverrideAttr(it , jS(ServerIP), jIVar::EDcstr,_T("PRIVATE_IP") , eOverride);
							fname_t buf;
							jt_sprintf(buf, _T("%s:%d"), pvIP->Get_cstr(), pvPort->Get_int());
							it->Set_cstr(buf);
						}
					}
				}
				else if(v->IsContents(jS(jClientSession_Asio)))
				{

				}
			}

			void jNet::_createNetObject(jIE* peNetObj)
			{
				_make_OverrideAttribute(peNetObj);

				if(!peNetObj->GetAttrVar(_T("ENABLE"))->Get_bool()) return;

				jIVar* pvType = peNetObj->GetAttrVar(_T("TYPE"));
				
				jNamedEventTable* pPHTL=0 ;
				cstr szHEADER = peNetObj->GetAttr(jS(HEADER));
				if(szHEADER)
					pPHTL= g_pjIPacketDispatch->GetNamedEventTable(szHEADER);

				try
				{
					if(pvType->IsContents(_T("TcpSession")) || pvType->IsContents(_T("UdpSession")) )
					{
						if(xGET_USER_DATA(jINetSession_Service,peNetObj ) ) throw _T("jINetSession_Service node is not NULL");
						jINetSession_Service* pObj =CreateClientSession(peNetObj->GetTagName() ,peNetObj);
						peNetObj->SetUserData(jS(jINetSession_Service),pObj);
						pObj->GetPlugIn()->m_pPHTL = pPHTL;
					}
					else if(pvType->IsContents(_T("P2PSession")))
					{
						if(peNetObj->GetUserData(jS(jINetSession_Service))) throw _T("jINetSession_Service node is not NULL");
						jINetSession_Service* pObj = CreateNetSession_CS(peNetObj->GetTagName() ,peNetObj) ;
						peNetObj->SetUserData(jS(jINetSession_Service),pObj);
						pObj->GetPlugIn()->m_pPHTL = pPHTL;
					}
					else if(pvType->IsContents(jS(IOCPSession)))
					{
						if(peNetObj->GetUserData(jS(jINetSession_Service))) throw _T("IOCPSession Node is not NULL");
						jINetSession_Service* pObj = (jINetSession_Service*)Create_jClient_IOCP(peNetObj->GetTagName(), peNetObj);
						peNetObj->SetUserData(jS(jINetSession_Service),pObj);
						pObj->GetPlugIn()->m_pPHTL = pPHTL;

						//peNetObj->for_each(jxjClient_IOCP_create_node((jClient_IOCP*)pObj));
					}
					else if(pvType->IsContents(jS(jClientSession_Asio)))
					{
						if(peNetObj->GetUserData(jS(jIPlugin_jIClientSession_Asio))) throw _T("jClientSession_Asio Node is not NULL");

						jIPlugin_jIClientSession_Asio* pObj = Create_Plugin_jClientSession_Asio(peNetObj->GetTagName(), peNetObj);
						//pObj->GetPlugIn()->m_pPHTL = pPHTL;
					}

					else if(jt_strstr(pvType->Get_cstr() , _T("Server")))
					{
						if(peNetObj->GetUserData(jS(jIServer_IOCP))) throw _T("jIServer_IOCP node is not NULL");
						jIServer_IOCP* pObj =0; 
						if(pvType->IsContents(_T("TcpUdpServer")))
						{
							pObj = CreateTcpUdpServer_IOCP(peNetObj->GetTagName() ,peNetObj) ;
						}
						else if(pvType->IsContents(_T("TcpServer")))
						{
							pObj = CreateTcpServer_IOCP(peNetObj->GetTagName() ,peNetObj) ;
						}
						else if(pvType->IsContents(_T("UdpServer")))
						{
							pObj = CreateUdpServer_IOCP(peNetObj->GetTagName() ,peNetObj) ;
						}
						if(!pObj) throw _T("Create Server IOCP FAIL");
						
						peNetObj->SetUserData(jS(jIServer_IOCP),pObj);
						pObj->GetPlugIn()->m_pPHTL = pPHTL;
					}
					else 
					{
						throw _T("unkown net object type");
					}
				}
				catch (tcstr szError)
				{
					peNetObj->DebugPrint(true);
					jWARN_T("%s",szError);
					throw false;
				}
			}

			bool  jNet::CreateNetObject(jIE* peNetList)
			{
				try
				{
					jIVar* pV = peNetList->GetAttrVar(_T("TYPE"));
					if(!pV)
					{
						peNetList->DebugPrint(nInterface::g_pjILog);
						jERROR(_T("%s: NetConfig노드에 TYPE이 지정안되어 있음"),_T(__FUNCTION__));
					}
					if( pV->IsContents(_T("PlugInList") ) )
					{
						m_peNetObjList[peNetList->GetTagName()] = peNetList;
						jIE* it = peNetList->begin();
						jrFOR(it)
						{
							_createNetObject(it);
						}
					}
					else 
					{
						_createNetObject(peNetList);
					}
				}
				catch (...)
				{
					return false;
				}
				return true;
			}

			jINetSession_Service* jNet::GetNetSession(jIE* pE)
			{
				return xGET_USER_DATA(jINetSession_Service,pE);
			}

			cstr ip_string_convert(cstr szIP , tname32_t buf)
			{
				//jLOG(_T("ip_string_convert , input ip = %s"),szIP);
				aname32_t abuf;
				if(jt_strlen(szIP)==0 || !jt_strcmp(szIP,_T("PUBLIC_IP")))
				{
					jt_strcpy(buf, jT(g_pjINet_OGS->GetUtil()->GetPublicIP(abuf) ) );
				//	jLOG(_T("ip_string_convert 1 , return ip = %s"),buf);
					return buf;
				}
				else if(!jt_strcmp(szIP, _T("PRIVATE_IP")))
				{
					jt_strcpy(buf, jT(g_pjINet_OGS->GetUtil()->GetPrivateIP(abuf) ) );
				//	jLOG(_T("ip_string_convert 2, return ip = %s"),buf);
					return buf;
				}
				jt_strcpy(buf, szIP);
				//jLOG(_T("ip_string_convert 3, return(마지막) ip = %s"),buf);
				return buf;
			}
			void  jNet::_runNetObject(jIE* pE)
			{
				tname32_t ip_buf,ip_buf2;
				if(!pE->GetAttrVar(_T("ENABLE"))->Get_bool()) return;

				jIVar* pvType = pE->GetAttrVar(_T("TYPE"));
				if(pvType->IsContents(_T("TcpSession")) || pvType->IsContents(_T("UdpSession")) )
				{
					jNetSession_Client* pObj = (jNetSession_Client*)xGET_USER_DATA(jINetSession_Service,pE);
					if(pvType->IsContents(_T("UdpSession")) )
					{
						tcstr szUdpLocalIP = ip_string_convert(pE->GetAttr(_T("UdpLocalIP")),ip_buf2);
						int iLocalPort=pE->GetAttrVar(_T("UdpLocalPort") )->Get_int();
						if(!pObj->ConnectUdp(szUdpLocalIP, iLocalPort,0))
						{
							throw _T("jINetSession_Service udp");
						}
					}
					else if(pvType->IsContents(_T("TcpSession")) )
					{
						cstr serverIP = ip_string_convert(pE->GetAttr(_T("ServerIP")), ip_buf);
						int serverPort = pE->GetAttrVar(_T("ServerPort") )->Get_int();
						//cstr serverIP = ip_string_convert(pE->GetAttr(_T("ServerIP") ), ip_buf2);
						if(!pObj->ConnectTcp(serverIP , serverPort,0))
							throw _T("jINetSession_Service tcp");
					}
					else
						jASSERT0(0);
				}
				else if(pvType->IsContents(jS(IOCPSession)))
				{
					jINetSession_Service* pObj = xGET_USER_DATA(jINetSession_Service,pE);
					if(!pObj) throw _T("error pE->GetUserData(jS(jINetSession_Service));");
	
					jClient_IOCP* _pObj = (jClient_IOCP*)pObj;
					pE->for_each(jxjClient_IOCP_create_node((jClient_IOCP*)pObj));

					_pObj->Start(pE);
				}
				else if(pvType->IsContents(jS(jClientSession_Asio)))
				{
					Run_jClientSession_Asio(pE);
				}


				else if(pvType->IsContents(_T("TcpUdpServer")) || pvType->IsContents(_T("TcpServer")) || pvType->IsContents(_T("UdpServer")))
				{
					jIServer_IOCP* pObj = xGET_USER_DATA(jIServer_IOCP,pE);
					jASSERT0(pObj != 0);
					if (!pObj->StartServer(pE) ) throw _T("error jIServer_IOCP");
				}
				else if(pvType->IsContents(_T("P2PSession")) )
				{
					jNetSession_CS* pObj = (jNetSession_CS*)xGET_USER_DATA(jINetSession_Service,pE);
					cstr szLocalIP =ip_string_convert(pE->GetAttr(_T("LocalTcpServerIP")),ip_buf);
					jIVar* pvPort = pE->GetAttrVar(_T("LocalTcpServerPort"));
					if( !pObj->StartTcpServer( szLocalIP , pvPort->Get_int() ,pE) )
						throw _T("error jINetSession_Service");
				}
				else 
					jASSERT0(0);
			}

			void jNet::RunNetObject(jIE* peNetObj)
			{
				try
				{
					jIVar* pV = peNetObj->GetAttrVar(_T("TYPE"));
					if( pV->IsContents(_T("PlugInList") ) )
					{
						SquirrelObject sqNetConfig;
						SquirrelObject sqPlugIn;
						try
						{
							fname_t buf;
							jt_sprintf(buf, _T("sq\\net\\%s.nut"), peNetObj->GetTagName() );
							nFileSystem::jFolder dir;
							if(dir.Is_Exist(buf))
							{
								sqNetConfig= GetjISQ()->VM_CompileScript(buf);
								assert(sqPlugIn.IsNull());
								if(!sqNetConfig.IsNull())
								{
									GetjISQ()->VM_RunScript(sqNetConfig);

									SquirrelObject root = GetjISQ()->VM_GetRootTable();
									sqPlugIn = root.GetValue(peNetObj->GetTagName());
									if(!sqPlugIn.IsNull())
									{
										SquirrelFunction<void> func(sqPlugIn,jS(OnPreRun));
										if(!func.func.IsNull()) {func( peNetObj ); }
									}
								}
							}
						}
						jSQ_CATCH_ERROR()
						jIE* it = peNetObj->begin();
						jrFOR(it)
						{
							_runNetObject(it);
						}
						try
						{
							if(!sqPlugIn.IsNull())
							{
								SquirrelFunction<void> func(sqPlugIn,jS(OnRunned));
								if(!func.func.IsNull()){func( peNetObj ); }
							}
						}
						jSQ_CATCH_ERROR()
						{

						}

					}
					else 
					{
						_runNetObject(peNetObj);
					}
				}
				catch (...)
				{
				}
			}


			struct jxIOCPSession_node_stop
			{
				jClient_IOCP* pObj;
				bool is;
				jxIOCPSession_node_stop(jClient_IOCP*p,bool is1):pObj(p),is(is1){}
				void operator()(jIE* it)
				{
					if(it->size()==0)
						pObj->Stop_ClientSocket(it,is);
				}
			};

			void  jNet::_stopNetObject(jIE* pE,bool isRelease)
			{
				if(!pE->GetAttrVar(_T("ENABLE")) || !pE->GetAttrVar(_T("ENABLE"))->Get_bool()) return;

				jIVar* pvType = pE->GetAttrVar(_T("TYPE"));
				if(pvType->IsContents(_T("TcpSession")) || pvType->IsContents(_T("UdpSession")) )
				{
					jINetSession_Service* pObj = xGET_USER_DATA(jINetSession_Service,pE);
					if(isRelease)
					{
						SAFE_RELEASE(pObj);
						pE->SetUserData(jS(jINetSession_Service),0);
						jINetSession_Service* p = xGET_USER_DATA(jINetSession_Service,pE);
						assert(!p);
					}
					else
					{
						((jNetSession_Client*)pObj)->EndService();
					}
				}
				else if(pvType->IsContents(jS(jClientSession_Asio)))
				{
					Stop_jClientSession_Asio(pE);
				}
				else if(pvType->IsContents(jS(IOCPSession)))
				{
					jINetSession_Service* pObj = xGET_USER_DATA(jINetSession_Service,pE);
					if(!pObj) return;
					if(isRelease)
					{
						pObj->Release();
						pE->SetUserData(jS(jINetSession_Service),0);
						jINetSession_Service* p = xGET_USER_DATA(jINetSession_Service,pE);
						assert(!p);
					}
					else
					{
						//pE->for_each(jxIOCPSession_node_stop(pObj,false));
						jClient_IOCP* _pObj = (jClient_IOCP*)pObj;
						_pObj->End();
					}
				}
				else if(jt_strstr(pvType->Get_cstr() , _T("Server") ) )
				{
					jIServer_IOCP* pObj = xGET_USER_DATA(jIServer_IOCP,pE);
					if(isRelease)
					{
						SAFE_RELEASE(pObj);
						pE->SetUserData(jS(jIServer_IOCP),0);
					}
					else
					{
						pObj->EndServer();
					}
				}
				else if(pvType->IsContents(_T("P2PSession")) )
				{
					jNetSession_CS* pObj = (jNetSession_CS*)xGET_USER_DATA(jINetSession_Service,pE);
					if(isRelease)
					{
						jIE* it = pE->begin();
						jrFOR(it)
						{
							pObj->Stop_ClientSocket(it,true);
						}
						SAFE_RELEASE(pObj);
						pE->SetUserData(jS(jINetSession_Service),0);
						jINetSession_Service* p = xGET_USER_DATA(jINetSession_Service,pE);
						assert(!p);

					}
					else
					{
						jIE* it = pE->begin();
						jrFOR(it)
						{
							pObj->Stop_ClientSocket(it,false);
						}
						pObj->EndService();
					}

				}
				else 
				{
					jASSERT0(0);
				}
			}

			void jSchedule_StopLogin(nEVENT::jIMessage* pM)
			{
				jIE* pE = (jIE*)pM->GetArg(0)->GetUserData();
				bool is = pM->GetArg(1)->Get_bool();
				g_pjNet->_StopNetObject(pE,is);
				pM->Erase();
			}
			void jNet::_StopNetObject(jIE* peNetList,bool isRelease)
			{
				jIVar* pV = peNetList->GetAttrVar(_T("TYPE"));
				if( pV->IsContents(_T("PlugInList") ) )
				{
					SquirrelObject sqPlugIn ;
					SquirrelObject root ;
					try
					{
						root = GetjISQ()->VM_GetRootTable();
						sqPlugIn = root.GetValue(peNetList->GetTagName());
						if(!sqPlugIn.IsNull())
						{
							SquirrelFunction<void> func(sqPlugIn,jS(OnPreStop));
							if( !func.func.IsNull() ) {func( peNetList ); }
						}
					}
					jSQ_CATCH_ERROR()

					jIE* it = peNetList->begin();
					jrFOR(it)
					{
						_stopNetObject(it,isRelease);
					}
					try
					{

						sqPlugIn = root.GetValue(peNetList->GetTagName());
						if(!sqPlugIn.IsNull())
						{
							SquirrelFunction<void> func(sqPlugIn,jS(OnStopped));
							if(!func.func.IsNull()) {func( peNetList ); }
						}
					}
					jSQ_CATCH_ERROR()
				}
				else 
				{
					_stopNetObject(peNetList,isRelease);
				}
			}

			void jNet::StopNetObject(jIE* peNetList,bool isRelease,bool isImmediately)
			{
				if(isImmediately)
				{
					_StopNetObject(peNetList, isRelease);
					return;
				}
				nEVENT::jIMsgManager* pMM = nEVENT::jIMsgManager::Get(_T("nNET::jNet"));
				nEVENT::jIMessage* pMsg = pMM->Regist_Loop(1,jFUNC_Msg(jSchedule_StopLogin),2);
				pMsg->GetArg(0)->SetUserData(peNetList);
				pMsg->GetArg(1)->InitValue(isRelease);
				pMsg->DoWakeUp();

				DoWakeUp_Msg();
			}

			jIServer_IOCP* jNet::GetServer(jIE* peNetObj)
			{
				return xGET_USER_DATA(jIServer_IOCP,peNetObj);
			}

			//해당 소켓을 종료 시킨다.
			void jNet::CloseSocket( SOCKET socketClose , bool bIsForce )
			{
				struct linger stLinger = {0, 0};	// SO_DONTLINGER로 설정

				// bIsForce가 true이면 SO_LINGER, timeout = 0으로 설정하여
				// 강제 종료 시킨다. 주의 : 데이터 손실이 있을수 있음 
				if( true == bIsForce )
					stLinger.l_onoff = 1; 

				//socketClose소켓의 데이터 송수신을 모두 중단 시킨다.
				shutdown( socketClose, SD_BOTH );
				//소켓 옵션을 설정한다.
				setsockopt( socketClose, SOL_SOCKET, SO_LINGER, (char *)&stLinger, sizeof(stLinger) );
				//소켓 연결을 종료 시킨다. 
				closesocket( socketClose );

				socketClose = INVALID_SOCKET;
			}

			void jNet::DeleteProactor(jIProactor_IOCP* p)
			{
#ifdef jUSE_ONE_PROACTOR
#else
				SAFE_DELETE(p);
#endif
			}
			jIProactor_IOCP* jNet::GetProactor(jIE* pePlugIn)
			{
#ifdef jUSE_ONE_PROACTOR
				static jIVar* pvThreadCnt = jCV(jINet_OGS,ThreadCount,(int)0,0,"IOCP 스레스 갯수");
				static jNetIOModel_IOCP a( pvThreadCnt->Get_int() );
				return &a;
#else
				jIVar* pV = pePlugIn->GetAttrVar(_T("ThreadCount"));
				jASSERT0(pV);
				return new jNetIOModel_IOCP(pV->Get_int());
#endif
			}
			
			jIPlugIn_Net* jNet::GetPlugIn(jIE* peNetConfigNode)
			{
				nXML::jE e = peNetConfigNode;
				if(!e.Attr(_T("ENABLE"))->Get_bool()) return 0;

				jVar pvType = e.Attr(_T("TYPE"));
				if(pvType->IsContents(_T("TcpSession")) 
					|| pvType->IsContents(_T("UdpSession")) 
					|| pvType->IsContents(_T("P2PSession"))
					|| pvType->IsContents(jS(IOCPSession))
					)
				{
					jINetSession_Service* pObj = xGET_USER_DATA(jINetSession_Service,e);
					return pObj->GetPlugIn();
				}
				else if(pvType->IsContents(_T("TcpUdpServer")) || pvType->IsContents(_T("TcpServer")) || pvType->IsContents(_T("UdpServer")))
				{
					jIServer_IOCP* pObj = xGET_USER_DATA(jIServer_IOCP,e);
					return pObj->GetPlugIn();
				}
				else if(pvType->IsContents(jS(jClientSession_Asio)))
				{
					jERROR_T("GetPlugIn : -> jClientSession_Asio") 
				}
				else 
				{
					peNetConfigNode->DebugPrint(true);
					jWARN(_T("TYPE이 NET CONFIG NODE가 아님"));
				}
				return 0;
			}


			void Job_PacketJobThread(nEVENT::jIMessage* pM)
			{
				nUTIL::jCircularQueueBuffer* pQ = (nUTIL::jCircularQueueBuffer*)pM->GetArg(0)->GetUserData();
				if(pQ->empty()) return;
				//jRETURN_P(100,pQ->empty());
				jIPacketSocket_IOCP* pIS;
				jPacketSocket_IOCP* pS; BYTE pReadBuff[MAX_BUFFER_LENGTH]; jPacketLen_t dwLen; void* pPlugIn; jIP_Address pFromIP;
				
				pPlugIn = pM->GetArg(1)->GetUserData();

				VOID *pObject = NULL;
				jPacketNum_t dwProtocol;
				while(1)
				{
					if(!pQ->Pop(&pObject, dwProtocol, pReadBuff, dwLen, &pFromIP) )
						return ;
					if(!pObject) 
						return;

					pIS= (jIPacketSocket_IOCP*)pObject;
					pS = (jPacketSocket_IOCP*)pIS;
					const _jNamed_Event_Handler* pNEH = pS->m_pjIPacketDispatchTable->find(dwProtocol);
					if(pNEH)pNEH->Call(pS, pReadBuff, dwLen, pPlugIn ,&pFromIP,0);
				}
			}

			//nMech::nNET::jIPacketSocket_IOCP* pS,BYTE *pReadBuff, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
			void jNet::Push_To_PacketJobThread(tcstr thread_name , tcstr szPlugIn,jPacketNum_t dwProtocol,_ARG_jNamedEventHandler)
			{
				fname_t szThread;
				jt_sprintf(szThread,_T("_%s.%s"),thread_name,szPlugIn);

				_JobThreadPoolNode jtpn;
				m_mapJobThreadPool_it it = m_mapJobThreadPool.find(szThread);
				if(it!=m_mapJobThreadPool.end())
				{
					jtpn = it->second;
				}
				else
				{
					jIVar* pvQueueSize = nMech::nCONSOLE::Get_jIConsoleVar()->CreateVar(jS(jINet_JobThread_QueueSize)
						, szThread, 1000,0,_T("jCircularQueueBuffer size. if above queueing packet must skip!"));

					jtpn.m_pMM = nEVENT::jIMsgManager::Get(szThread,true);
					jtpn.m_pQ = new nUTIL::jCircularQueueBuffer(pvQueueSize->Get_int());
					jtpn.m_pQ->Begin();
					jtpn.m_pPlugIn = pPlugIn;

					m_mapJobThreadPool[szThread] = jtpn;
					nEVENT::jIMessage* pMsg = jtpn.m_pMM->Regist_Loop(0,jFUNC_Msg(Job_PacketJobThread), 2,true);
					pMsg->GetArg(0)->SetUserData(jtpn.m_pQ);
					pMsg->GetArg(1)->SetUserData(jtpn.m_pPlugIn);
					pMsg->DoWakeUp();
					jtpn.m_pMM->StartThread(true);
				}
				jtpn.m_pQ->Push(pS,dwProtocol,pReadBuff,dwLen,pFromIP);
				jtpn.m_pMM->WakeThread();
			}

			jCONSOLE_CMD_AUTO(net,reload_plugin_sq,0,"jINetPlugIn관련스크립트로딩","<net_config_node> <plugin_name>")
			{
				tstring net_config_node = arg[0];
				tstring plugin_name = arg[1];
				if(!g_pjNet->m_peNetObjList.count(net_config_node))
				{
					jWARN(_T("net_config_node = %s 항목못찾음"),net_config_node.c_str() );
					return false;
				}

				jIE* pE = g_pjNet->m_peNetObjList[net_config_node];
				nXML::jE e = pE->Find(plugin_name.c_str());
				if(e.empty()) return false;

				jIPlugIn_Net* pPlugIn = g_pjNet->GetPlugIn(e);
				if(!pPlugIn) return false;
				return pPlugIn->Load_SQ();
			}
			tcstr _L2G_IP(tstring & outAddress )
			{
				if(!outAddress.size() || outAddress==jS(127.0.0.1))
				{
					outAddress = jT(g_pjINet_OGS->GetHostIpString(0));
				}
				return outAddress.c_str();
			}

			int _Get_IP_PORT(tcstr szIP, tstring & outAddress )
			{
				vector<tstring> out;
				tstring parsedIP;
				if(jt_strstr(szIP,jS(APP_DOC)) )
				{
					nString::jSplit(szIP,_T("."),out);
					jIE* pE =0;
					pE = nGLOBAL::g_pDocApp->BaseI();
					for(int i=1 ;i< out.size(); ++i )
					{
						cstr sz = out[i].c_str();
						pE = pE->Find(sz );
						if(!pE)
						{
							jWARN(_T("APP_DOC ip string error : %s , out[%d]=%s"),szIP,i,sz);
							return -1;
						}
					}
					parsedIP = pE->Get_cstr();
					szIP=parsedIP.c_str();
				}
				out.clear();
				nString::jSplit(szIP,jS(:),out);
				if(out.size()!=2)
				{
					jWARN(_T("ip string error : %s"),szIP);
					return -1;
				}
				outAddress = out[0];
				_L2G_IP(outAddress);
				return jt_atoi(out[1].c_str());
			}


			void jNet::SetCallback_PacketSize_UsageInfo(OnPacketSize_UsageInfo_t* f)
			{
				m_pFunc_OnPacketSize_UsageInfo=f;
			}
			void jNet::SetDebugger_SendFile(SocketDebugPrint_SendFile_t* fn)
			{
				m_pSocketDebugPrint_SendFile= fn;
			}



		}// nNet::Impl
	} //nNET
}//nMech


