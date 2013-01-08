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

#ifndef jFUNC1 
#define jLogT(type) g_Current_LogLevel_jStringID,jx(type)
#define jLogL g_Current_LogLevel_jStringID,jx(NULL)
#define jFUNC1 _T(__FUNCTION__) _T(">")
#endif //jFUNC1 




volatile float aaa;

DECLARE_INSTANCE_TYPE(jIE);

bool g_MsgManager_thread_quit=false;
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
		Impl::jNet *g_pjNet ;
		jIPacketDispatch* g_pjIPacketDispatch=0;
		namespace Impl
		{

			HANDLE			g_mMsgThreadHandle=0;
			HANDLE			g_mMsgThreadHandle_jIMsgManager=0;
			bool g_mMsgThreadHandle_jIMsgManager_loop=true;
			HANDLE g_hThreadWakeUpEvent=0;
			HANDLE g_hThreadDestroyEvent=0;

			void jNet::DoWakeUp_Msg()
			{
				if(!Get_UseMsgManagerEvent()) return;
				if(Get_Custom_MsgLoop()) return;
				SetEvent(g_hThreadWakeUpEvent);
			}


			static unsigned __stdcall _MsgThread_jIMsgManager( void* )
			{
				for(;g_mMsgThreadHandle_jIMsgManager_loop;)
				{
					nTIME::Get_ITimer()->Update();

					nMech::nEVENT::jIMsgManager::FrameMove();
					Sleep(1);
				}
				return 0;
			}

			static unsigned __stdcall _MsgThread( void* )
			{
				DWORD				EventID					= 0;
				if(g_pjNet->Get_UseMsgManagerEvent())
				{
					HANDLE				hEvent_Destroy_and_Wake[2]			= {g_hThreadDestroyEvent, g_hThreadWakeUpEvent};
					while(1)
					{
						EventID = WaitForMultipleObjects(2, hEvent_Destroy_and_Wake, FALSE, INFINITE);
						switch (EventID)
						{
						case WAIT_OBJECT_0:
							return 0;
							break;

						case WAIT_OBJECT_0 + 1:
							g_pjNet->m_pMM_PacketPump->Run(); 
							//nMech::nEVENT::jIMsgManager::FrameMove();
							break;
						}
					}
				}
				else
				{
					while(!g_MsgManager_thread_quit)
					{
						g_pjNet->m_pMM_PacketPump->Run(); 
						//nMech::nEVENT::jIMsgManager::FrameMove();
						Sleep(1);
					}

				}
				return 0;
			}
			extern "C"
			{

				JNET_OGS_API void* jCreateInterface(jIE* pE)
				{
					g_pjIPacketDispatch= jCREATE_INTERFACE(nMech::nNET::jIPacketDispatch);
					jAssert0(g_pjIPacketDispatch&& _T("jINet::jCreateInterface()"));
					g_pjNet = new jNet(pE);
					nInterface::g_pjINet_OGS = g_pjNet;

					jIVar* pvBegin= jCV(jINet_OGS,Auto_Begin,true,0,"Call Begin() when jINet_OGS.DLL loading time");
					jIVar* pvCoInit = jCV(jINet_OGS,CoInitialize,true,0,"Is call CoInitialize when jINet_OGS::Begin()");
					if(pvBegin->Get_bool()) g_pjNet->Begin(pvCoInit->Get_bool());

					return nInterface::g_pjINet_OGS;
				}
				JNET_OGS_API void jDeleteInterface()
				{
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
				g_pjNet->m_pFunc_OnPacketSize_UsageInfo(0 , g_pjNet->m_iPacketSize_UsageInfo , buf);
				g_pjNet->m_iPacketSize_UsageInfo=0;
#endif
				//g_pjNet->DoWakeUp_Msg();
			}
			jNet::jNet(jIE* pE)
				:m_bCoInit(false)
				,m_peDLL(pE)
				,m_pFunc_OnPacketSize_UsageInfo(0)
				,m_iPacketSize_UsageInfo(0)
			{
				m_pMM_PacketPump = nEVENT::jIMsgManager::Get(_T("_nNET::jNet"),true);
				// Winsock을 사용하기 위한 DLL 로드
				WSADATA WsaData;
				WSAStartup(MAKEWORD(2, 2), &WsaData);	// 2.2 버전을 로드합니다.

				nInterface::g_pjINet_OGS= this;

#define jREAD_Attr(type,var, initVal,help) m_##var = jCV(jINet,var,(type)initVal, 0, help);
				for_each_jNet_VAR(jREAD_Attr);
#undef jREAD_Attr
				m_pMM_Util = nEVENT::jIMsgManager::Get(jS(nNET::jNet),true);
				float sec = pv_OnPacketSize_UsageInfo_TIME->Get_float();
				nEVENT::jIMessage* pM = m_pMM_Util->Regist_TimeBase(0,JOB_PacketSize_Info, 0,sec);
				pM->DoWakeUp();
			}
			jNet::~jNet()
			{
				WSACleanup();
			}

			acstr jNet::GetHostIpString(int idx)
			{
				if(idx >=0 && idx < m_listNetHostIP.size())
					return m_listNetHostIP[idx].c_str();
				return _jA("127.0.0.1");
			}

			void jNet::Begin(bool coInit)
			{
				m_bCoInit = coInit;
				if(m_bCoInit)
					CoInitialize(NULL);

				if(!gethostname(m_szHostName, sizeof(m_szHostName)))
				{
					struct	hostent *hp;
					hp = gethostbyname(m_szHostName);
					if (hp) 
					{
						GetjILog()->Log(_T("network hostname: %s"),nUNI::scb256_t(hp->h_name).getT());
						ja_strcpy(m_szNetHostName, hp->h_name);
						int i = 0;
						while(hp->h_aliases[i]) 
						{
							m_listNetHostAlias.push_back(hp->h_aliases[i]);
							GetjILog()->Log(_T("  alias: %s\n"), hp->h_aliases[i]);
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
							GetjILog()->Log(_T("  ip:%s"),szBuf);
#else
							ja_sprintf(szBuf,_jA("%d.%d.%d.%d"),		//  port:%d  family:%x"),	
								(int)(host_in.sin_addr.S_un.S_un_b.s_b1),
								(int)(host_in.sin_addr.S_un.S_un_b.s_b2),
								(int)(host_in.sin_addr.S_un.S_un_b.s_b3),
								(int)(host_in.sin_addr.S_un.S_un_b.s_b4));
							//		(int)host_in.sin_port,(unsigned int)host_in.sin_family);
							GetjILog()->Log(_T("  ip:%s"),nUNI::scb64_t(szBuf).getT());
#endif
							m_listNetHostIP.push_back(szBuf);
							i++;
						}
					}
				}
				else
					ja_strcpy(m_szHostName,_jA("NULL"));

				if(Get_UseMsgThread())
				{
					if(Get_UseMsgManagerEvent())
					{
						g_hThreadWakeUpEvent= CreateEvent(0, FALSE, FALSE, 0); jAssert0(g_hThreadWakeUpEvent);
					}

					g_hThreadDestroyEvent= CreateEvent(0, FALSE, FALSE, 0);jAssert0(g_hThreadDestroyEvent);
					if(!Get_Custom_MsgLoop())
					{
						unsigned int hMsgWorkerThread	= 0;
						g_MsgManager_thread_quit=false;
						g_mMsgThreadHandle		= (HANDLE)_beginthreadex(NULL, 0, _MsgThread, this, 0, &hMsgWorkerThread	);
						GetjILog()->Log(_T("thread create : jNet::_MsgThread") );
					}
				}
				jIVar* pvIsRUN_MSG_FRAME_MOVE=jCV(jINet_OGS,IsRUN_MSG_FRAME_MOVE
					, false,0
					,"is create thread for nMech::nEVENT::jIMsgManager::FrameMove()");
				if(pvIsRUN_MSG_FRAME_MOVE->Get_bool())
				{
					unsigned int hMsgWorkerThread	= 0;
					g_mMsgThreadHandle_jIMsgManager = (HANDLE)_beginthreadex(NULL, 0, _MsgThread_jIMsgManager, this, 0, &hMsgWorkerThread	);
				}
			}

			void jNet::RunMessageThread(bool isStopThread)
			{
				if(isStopThread)
				{
					if(g_mMsgThreadHandle_jIMsgManager)
					{
						g_mMsgThreadHandle_jIMsgManager_loop = false;
						WaitForSingleObject(g_mMsgThreadHandle_jIMsgManager, INFINITE);
					}

				}
				else
				{
					if(g_mMsgThreadHandle_jIMsgManager) return;
					unsigned int hMsgWorkerThread	= 0;
					g_mMsgThreadHandle_jIMsgManager = (HANDLE)_beginthreadex(NULL, 0, _MsgThread_jIMsgManager, this, 0, &hMsgWorkerThread	);
				}
			}

			void jNet::End()
			{
				DWORD dwExitCode=0;
				g_MsgManager_thread_quit=true;
				if (g_mMsgThreadHandle)
				{
					if(Get_UseMsgManagerEvent())
					{
						SetEvent(g_hThreadDestroyEvent);
						//WaitForSingleObject(g_mMsgThreadHandle, INFINITE);
					}
					 if(g_mMsgThreadHandle!=0)
						TerminateThread(g_mMsgThreadHandle,dwExitCode);
					//CloseHandle(g_mMsgThreadHandle);

					if(g_hThreadWakeUpEvent)
						CloseHandle(g_hThreadWakeUpEvent);
					if(g_hThreadDestroyEvent)
						CloseHandle(g_hThreadDestroyEvent);

					g_mMsgThreadHandle = NULL;
				}
				if(g_mMsgThreadHandle_jIMsgManager)
				{
					g_mMsgThreadHandle_jIMsgManager_loop = false;
					//WaitForSingleObject(g_mMsgThreadHandle_jIMsgManager, INFINITE);
					TerminateThread(g_mMsgThreadHandle_jIMsgManager,dwExitCode);
				}


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
				
			void jNet::_createNetObject(jIE* peNetObj)
			{
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
						if(jGetType<jINetSession_Service>(pvType)) throw _T("jINetSession_Service node is not NULL");
						jINetSession_Service* pObj =CreateClientSession(peNetObj->GetTagName() ,peNetObj);
						jSetType<jINetSession_Service>(pvType,pObj);
						pObj->GetPlugIn()->m_pPHTL = pPHTL;
					}
					else if(pvType->IsContents(_T("P2PSession")))
					{
						if(jGetType<jINetSession_Service>(pvType)) throw _T("jINetSession_Service node is not NULL");
						jINetSession_Service* pObj = CreateNetSession_CS(peNetObj->GetTagName() ,peNetObj) ;
						jSetType<jINetSession_Service>(pvType,pObj);
						jAssert0( jGetType<jINetSession_Service>(pvType));
						pObj->GetPlugIn()->m_pPHTL = pPHTL;
					}
					else if(pvType->IsContents(jS(IOCPSession)))
					{
						if(jGetType<jINetSession_Service>(pvType)) throw _T("IOCPSession Node is not NULL");
						jClient_IOCP* pObj = (jClient_IOCP*)Create_jClient_IOCP(peNetObj->GetTagName(), peNetObj);
						jSetType<jINetSession_Service>(pvType,pObj);
						jAssert0( jGetType<jINetSession_Service>(pvType));
						pObj->GetPlugIn()->m_pPHTL = pPHTL;

						peNetObj->for_each(jxjClient_IOCP_create_node(pObj));
					}
					else if(jt_strstr(pvType->Get_cstr() , _T("Server")))
					{
						if(jGetType<jIServer_IOCP>(pvType)) throw _T("jIServer_IOCP node is not NULL");
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
						jSetType<jIServer_IOCP>(pvType,pObj);
						jAssert0( jGetType<jIServer_IOCP>(pvType));
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
					GetjILog()->Warning(szError);
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
						GetjILog()->Error(_T("%s: NetConfig노드에 TYPE이 지정안되어 있음"),_T(__FUNCTION__));
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
				return jGetType<jINetSession_Service>(pE->GetAttrVar(jS(TYPE)) );
			}

			cstr ip_string_convert(cstr szIP , tname32_t buf)
			{
				//GetjILog()->Log(_T("ip_string_convert , input ip = %s"),szIP);
				aname32_t abuf;
				if(jt_strlen(szIP)==0 || !jt_strcmp(szIP,_T("PUBLIC_IP")))
				{
					jt_strcpy(buf, jT(g_pjINet_OGS->GetUtil()->GetPublicIP(abuf) ) );
				//	GetjILog()->Log(_T("ip_string_convert 1 , return ip = %s"),buf);
					return buf;
				}
				else if(!jt_strcmp(szIP, _T("PRIVATE_IP")))
				{
					jt_strcpy(buf, jT(g_pjINet_OGS->GetUtil()->GetPrivateIP(abuf) ) );
				//	GetjILog()->Log(_T("ip_string_convert 2, return ip = %s"),buf);
					return buf;
				}
				jt_strcpy(buf, szIP);
				//GetjILog()->Log(_T("ip_string_convert 3, return(마지막) ip = %s"),buf);
				return buf;
			}
			void  jNet::_runNetObject(jIE* pE)
			{
				tname32_t ip_buf,ip_buf2;
				if(!pE->GetAttrVar(_T("ENABLE"))->Get_bool()) return;

				jIVar* pvType = pE->GetAttrVar(_T("TYPE"));
				if(pvType->IsContents(_T("TcpSession")) || pvType->IsContents(_T("UdpSession")) )
				{
					jNetSession_Client* pObj = (jNetSession_Client*)jGetType<jINetSession_Service>(pvType);
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
						jAssert0(0);
				}
				else if(pvType->IsContents(jS(IOCPSession)))
				{
					jClient_IOCP* pObj = (jClient_IOCP*)jGetType<jINetSession_Service>(pvType);
					if(!pObj) throw _T("error jGetType<jINetSession_Service>(pvType);");
					pObj->Start(pE);
				}
				else if(pvType->IsContents(_T("TcpUdpServer")) || pvType->IsContents(_T("TcpServer")) || pvType->IsContents(_T("UdpServer")))
				{
					jIServer_IOCP* pObj = (jIServer_IOCP*)jGetType<jIServer_IOCP>(pvType);
					jAssert0(pObj != 0);
					if (!pObj->StartServer(pE) ) throw _T("error jIServer_IOCP");
				}
				else if(pvType->IsContents(_T("P2PSession")) )
				{
					jNetSession_CS* pObj = (jNetSession_CS*)jGetType<jINetSession_Service>(pvType);
					cstr szLocalIP =ip_string_convert(pE->GetAttr(_T("LocalTcpServerIP")),ip_buf);
					jIVar* pvPort = pE->GetAttrVar(_T("LocalTcpServerPort"));
					if( !pObj->StartTcpServer( szLocalIP , pvPort->Get_int() ,pE) )
						throw _T("error jINetSession_Service");
				}
				else 
					jAssert0(0);
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
				if(!pE->GetAttrVar(_T("ENABLE"))->Get_bool()) return;

				jIVar* pvType = pE->GetAttrVar(_T("TYPE"));
				if(pvType->IsContents(_T("TcpSession")) || pvType->IsContents(_T("UdpSession")) )
				{
					jINetSession_Service* pObj = (jINetSession_Service*)jGetType<jINetSession_Service>(pvType);
					if(isRelease)
					{
						SAFE_RELEASE(pObj);
						jSetType<jINetSession_Service>(pvType,0);
						jINetSession_Service* p = jGetType<jINetSession_Service>(pvType);
						assert(!p);

					}
					else
					{
						((jNetSession_Client*)pObj)->EndService();
					}
				}
				else if(pvType->IsContents(jS(IOCPSession)))
				{
					jClient_IOCP* pObj = (jClient_IOCP*)jGetType<jINetSession_Service>(pvType);
					if(!pObj) return;
					if(isRelease)
					{
						pObj->Release();
						jSetType<jINetSession_Service>(pvType,0);
						jINetSession_Service* p = jGetType<jINetSession_Service>(pvType);
						assert(!p);

					}
					else
					{
						//pE->for_each(jxIOCPSession_node_stop(pObj,false));
						pObj->End();
					}
				}
				else if(jt_strstr(pvType->Get_cstr() , _T("Server") ) )
				{
					jIServer_IOCP* pObj = (jIServer_IOCP*)jGetType<jIServer_IOCP>(pvType);
					if(isRelease)
					{
						SAFE_RELEASE(pObj);
						jSetType<jIServer_IOCP>(pvType,0);
					}
					else
					{
						pObj->EndServer();
					}
				}
				else if(pvType->IsContents(_T("P2PSession")) )
				{
					jNetSession_CS* pObj = (jNetSession_CS*)jGetType<jINetSession_Service>(pvType);
					if(isRelease)
					{
						jIE* it = pE->begin();
						jrFOR(it)
						{
							pObj->Stop_ClientSocket(it,true);
						}
						SAFE_RELEASE(pObj);
						jSetType<jINetSession_Service>(pvType,0);
						jINetSession_Service* p = jGetType<jINetSession_Service>(pvType);
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
					jAssert0(0);
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
				nEVENT::jIMessage* pMsg = pMM->Regist_Loop(1,jSchedule_StopLogin,2);
				pMsg->GetArg(0)->SetUserData(peNetList);
				pMsg->GetArg(1)->InitValue(isRelease);
				pMsg->DoWakeUp();

				DoWakeUp_Msg();
			}

			jIServer_IOCP* jNet::GetServer(jIE* peNetObj)
			{
				return jGetType<jIServer_IOCP>(peNetObj->GetAttrVar(jS(TYPE)) );
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
				jAssert0(pV);
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
					jINetSession_Service* pObj = jGetType<jINetSession_Service>(pvType);
					return pObj->GetPlugIn();
				}
				else if(pvType->IsContents(_T("TcpUdpServer")) || pvType->IsContents(_T("TcpServer")) || pvType->IsContents(_T("UdpServer")))
				{
					jIServer_IOCP* pObj = jGetType<jIServer_IOCP>(pvType);
					return pObj->GetPlugIn();
				}
				else 
				{
					peNetConfigNode->DebugPrint(true);
					GetjILog()->Warning(_T("TYPE이 NET CONFIG NODE가 아님"));
				}
				return 0;
			}

			jCONSOLE_CMD_AUTO(net,reload_plugin_sq,0,"jINetPlugIn관련스크립트로딩","<net_config_node> <plugin_name>")
			{
				tstring net_config_node = arg[0];
				tstring plugin_name = arg[1];
				if(!g_pjNet->m_peNetObjList.count(net_config_node))
				{
					GetjILog()->Warning(jFUNC1 _T("net_config_node = %s 항목못찾음"),net_config_node.c_str() );
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
				nString::jSplit(szIP,jS(:),out);
				if(out.size()!=2)
				{
					GetjILog()->Warning(_T("ip string error : %s"),szIP);
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



		}// nNet::Impl
	} //nNET
}//nMech


