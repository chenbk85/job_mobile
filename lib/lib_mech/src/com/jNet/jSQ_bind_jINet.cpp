/* file : jSQ_jINet.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-15 12:45:50
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jNet.h"

#define SQPLUS_CONST_OPT
#include "interface/Squirrel/jISquirrel.h"
#include "base/jSQ_bind.h"
#include "Interface/net/jSQ_bind_jINet.h"
#include "jNetGrid.h"


#ifndef jFUNC1 
#define jLogT(type) g_Current_LogLevel_jStringID,jx(type)
#define jLogL g_Current_LogLevel_jStringID,jx(NULL)
#define jFUNC1 _T(__FUNCTION__) _T(">")
#endif //jFUNC1 

using namespace nMech::nNET;

DECLARE_ENUM_TYPE(nNET::ESocket_Type);

//DECLARE_INSTANCE_TYPE(StringID);
DECLARE_INSTANCE_TYPE(jIE);
DECLARE_INSTANCE_TYPE(jINet_OGS);

DECLARE_INSTANCE_TYPE(jNamedEventNode);
DECLARE_INSTANCE_TYPE(jNamedEventTable);

DECLARE_INSTANCE_TYPE(jIPlugIn_Server_IOCP);
DECLARE_INSTANCE_TYPE(jIPlugIn_Connection);

DECLARE_INSTANCE_TYPE(jINetSession_Service);

DECLARE_INSTANCE_TYPE(jIServer_IOCP);


//--------------------------------------------------------------------------
static bool _write_packet_data(nNET::nStream::jNetStreamWrite & Stream, StackHandler &sa,int arg_Start)
//--------------------------------------------------------------------------
{
	for(int i=arg_Start ; i < sa.GetParamCount(); ++i)
	{
		tagSQObjectType type = (tagSQObjectType)sa.GetType(i);
		switch(type)
		{
		case OT_INTEGER:
			{
				int32 iVal = sa.GetInt(i);
				Stream.Write<nMech::int32>(iVal);
				break;
			}
		case OT_FLOAT:
			{
				float iVal = sa.GetInt(i);
				Stream.Write<float>(iVal);
				break;
			}
		case OT_STRING:
			{
				nUNI::scb1024_t t2w(sa.GetString(i));
				nMech::uint16 msg_WCHAR_LEN= (nMech::uint16)jw_strlen(t2w.getW());
				Stream.Write<nMech::uint16>(msg_WCHAR_LEN);
				Stream.WriteArray<WCHAR>(t2w.getW() , msg_WCHAR_LEN);
				break;
			}
		case OT_BOOL:
			{
				bool iVal = sa.GetBool(i);
				Stream.Write<bool>(iVal);
				break;
			}
		case OT_TABLE:
			{
			}
		case OT_ARRAY:
			{
			}
		case OT_INSTANCE:
			{
			}
		default:
			{
				jWARN(_T("unkown type : jSQ_gfn_DEF(bool , jIPacketSocket_IOCP , WritePacket)"));
				return false;
			}
		}
	}
	return true;
}


//jPlugInHelpTable test_HT;

namespace nSQ_jINet
{
	jSQ_gfn_DEF2(tcstr , jNamedEventNode , _tostring)(jNamedEventNode* pT)
	{
		static fname_t buf;
		jt_snprintf(buf,ARRAY_SIZE(buf), _T("%s(%d)"),pT->m_szName,pT->m_id);
		return buf;
	}

	jSQ_gfn_DEF2(tcstr ,jIP_Address,_tostring)(jIP_Address* pT){	static fname_t buf;		return jSOCKADDR_IN::Addr2String(*pT,buf);}
	jSQ_gfn_DEF2(jIP_Address*,jIP_Address,Set)(jIP_Address* pT,tcstr szAddr){*pT=jSOCKADDR_IN::String2Addr(szAddr); return pT;}
	
	void init_SQ()
	{
		jSQ_Interface(jPacket_Base)
			jSQ_fn(GetLen,"","패킷길이")
			jSQ_fn(GetNum,"","패킷넘버")
		jSQ_end();

		jSQ_Class(jIP_Address)
			jSQ_gfn(jIP_Address,_tostring,"","")
			jSQ_gfn(jIP_Address,Set,"tcstr szAddress","127.0.0.1:2344")
		jSQ_end();

		//test_HT.m_id =999;	test_HT.m_szName = jS(asdfasdf);
		jSQ_Interface(jNamedEventNode)
			jSQ_var2(m_id ,VAR_ACCESS_CONSTANT,"")
			jSQ_var2(m_jStringID ,VAR_ACCESS_CONSTANT,"")
			jSQ_var2(m_szName, VAR_ACCESS_READ_ONLY,"")
			jSQ_gfn(jNamedEventNode,_tostring,"","")
		jSQ_end();
		//BindVariable((jPlugInHelpTable*)&test_HT,_T("test_HT"));

		jSQ_Interface(jNamedEventTable)
			jSQ_fn(GetByNum,"int idx","")
			jSQ_fn(GetByID,"StringID id","")
			jSQ_fn(GetByName,"tcstr sz","")
			jSQ_fn(Insert,"int idx,tcstr sz","");
		jSQ_end();
		

		jSQ_Interface(jINet_OGS)
			jSQ_enum_init(ESocket_Type)
			jSQ_enum(nNET,eNULL_SOCKET,"")
			jSQ_enum(nNET,eLISTEN_SOCKET,"")
			jSQ_enum(nNET,eACCEPTED_SOCKET,"")
			jSQ_enum(nNET,eCONNECTING_SOCKET,"")
			jSQ_enum(nNET,eTCP_SOCKET_END,"")
			jSQ_enum(nNET,eUDP_SOCKET,"")
			jSQ_fn( Begin,"","")
			jSQ_fn( End,"","")
			jSQ_fn( CreateNetObject,"jIE* peNetConfig","")
			jSQ_fn( RunNetObject,"jIE* peNetConfig","")
			jSQ_fn( StopNetObject,"jIE* peNetConfig","")
			//jSQ_fn( GetHostName)
			//jSQ_fn( GetHostIpString)
			jSQ_fn( FrameMove,"","")
		jSQ_end();

		jSQ_g_var(nInterface::g_pjINet_OGS,g_pjINet_OGS);
	}
}


namespace nSQ_jIPacketSocket_IOCP
{

	//--------------------------------------------------------------------------
	jSQ_gfn_DEF(bool , jIPacketSocket_IOCP , WritePacket)
	//--------------------------------------------------------------------------
	{
		jSQ_init_pThis(jIPacketSocket_IOCP);// paramCount ,arg_This ,pThis , arg_Start=2
		int iPacketNum = sa.GetInt(arg_Start++);

		nswb4000_t sendBuf;
		nNET::nStream::jNetStreamWrite Stream(sendBuf);

		try
		{
			if(!_write_packet_data(Stream, sa,arg_Start)) return false;
		}
		catch (tcstr sz)
		{
			jWARN_T("%s",sz);
			return false;
		}

		jPacket_Base pk; 
		pk.num = iPacketNum;
		pk.buf=sendBuf.GetBuffer();	 
		pk.len=(jPacketNum_t)Stream.size();
		return pThis->WritePacket(&pk);
	}
	
	//--------------------------------------------------------------------------
	jSQ_gfn_DEF(bool , jIPacketSocket_IOCP , WriteToPacket)
	//--------------------------------------------------------------------------
	{
		jSQ_init_pThis(jIPacketSocket_IOCP);// paramCount ,arg_This ,pThis , arg_Start=2
		jIP_Address* pIP= jSQ_GetArg(jIP_Address,arg_Start++);
		int iPacketNum = sa.GetInt(arg_Start++);
		if(!pIP) return false;

		nswb4000_t sendBuf;
		nNET::nStream::jNetStreamWrite Stream(sendBuf);

		if(!_write_packet_data(Stream, sa,arg_Start)) return false;

		jPacket_Base pk; 
		pk.num = iPacketNum;
		pk.buf=sendBuf.GetBuffer();	 
		pk.len=(jPacketNum_t)Stream.size();
		return pThis->WriteToPacket(pIP,&pk);
	}
	jSQ_gfn_DEF2(bool , jIPacketSocket_IOCP , _tostring)(jIPacketSocket_IOCP* pT)
	{
		static fname_t buf;
		fname_t buf2;
		jt_snprintf(buf, ARRAY_SIZE(buf) , _T("jIPacketSocket_IOCP: %s (name=%s)") 
			, pT->GetAddressString(buf2) , pT->GetName());
		return buf;
	}

	void init_SQ()
	{
		jSQ_Interface(jIPacketSocket_IOCP)
			jSQ_gfn(jIPacketSocket_IOCP,WritePacket,"","")
			jSQ_gfn(jIPacketSocket_IOCP,WriteToPacket,"","")
			jSQ_gfn(jIPacketSocket_IOCP,_tostring,"","")
			jSQ_fn(GetType,"","")
			jSQ_fn(IsConnected,"","")
			jSQ_fn(GetName,"","")
		jSQ_end();

	}
}
namespace jSQ_jINetSession_Service
{
	//--------------------------------------------------------------------------
	jSQ_gfn_DEF(bool , jINetSession_Service , WritePacket)
	//--------------------------------------------------------------------------
	{
		jSQ_init_pThis(jINetSession_Service);// paramCount ,arg_This ,pThis , arg_Start=2
		jIPacketSocket_IOCP* pS = jSQ_GetArg(jIPacketSocket_IOCP,arg_Start++);
		int iPacketNum = sa.GetInt(arg_Start++);

		nswb4000_t sendBuf;
		nNET::nStream::jNetStreamWrite Stream(sendBuf);

		try
		{
			if(!_write_packet_data(Stream, sa,arg_Start)) return false;
		}
		catch (tcstr sz)
		{
			jWARN(_T("%s"),sz);
			return false;
		}

		jPacket_Base pk; 
		pk.num = iPacketNum;
		pk.buf=sendBuf.GetBuffer();	 
		pk.len=(jPacketNum_t)Stream.size();
		return pS->WritePacket(&pk);
	}

	//--------------------------------------------------------------------------
	jSQ_gfn_DEF(bool , jINetSession_Service , WriteToPacket)
	//--------------------------------------------------------------------------
	{
		jSQ_init_pThis(jINetSession_Service);// paramCount ,arg_This ,pThis , arg_Start=2
		jIPacketSocket_IOCP* pS = jSQ_GetArg(jIPacketSocket_IOCP,arg_Start++);
		jIP_Address* pIP= jSQ_GetArg(jIP_Address,arg_Start++);
		int iPacketNum = sa.GetInt(arg_Start++);
		if(!pIP) return false;

		nswb4000_t sendBuf;
		nNET::nStream::jNetStreamWrite Stream(sendBuf);

		if(!_write_packet_data(Stream, sa,arg_Start)) return false;

		jPacket_Base pk; 
		pk.num = iPacketNum;
		pk.buf=sendBuf.GetBuffer();	 
		pk.len=(jPacketNum_t)Stream.size();
		return pS->WriteToPacket(pIP,&pk);
	}


	void init_SQ()
	{
		jSQ_Interface(jINetSession_Service)
			jSQ_fn(GetPlugIn,"","")
			jSQ_fn(Get_ClientSocket,"cstr sz=0","")
			jSQ_gfn( jINetSession_Service , WritePacket
						,"jIPacketSocket_IOCP* pS , int PK_NO, ...","")
			jSQ_gfn( jINetSession_Service , WriteToPacket
						,"jIPacketSocket_IOCP* pS , jIP_Address* pIP, int PK_NO, ...","")
		jSQ_end();

		jSQ_Interface(jIServer_IOCP)
			jSQ_fn(StartServer,"jIE* peNetConfig","cstr szIP,int port ,int maxUser")
			jSQ_fn(DisconnectTcpClient,"jIPacketSocket_IOCP* pS","")
			jSQ_fn(GetUdpListenSocket,"","")
			jSQ_fn(GetPlugIn,"","")
			jSQ_fn(GetUdpSocket,"StringID id","")
			jSQ_fn(AddUdpSocket,"StringID id, cstr szIP,int port","")
		jSQ_end();

	}
}



namespace nSQ_jIPlugIn
{
	void init_SQ()
	{
		jSQ_Interface(jIPlugIn_Net)
			jSQ_var(m_pE,"net config node")
			jSQ_var(m_pPHTL,"jIServer_IOCP")
		jSQ_end();

		jSQ_Interface(jIPlugIn_Server_IOCP)
			jSQ_var(m_pServer,"jIServer_IOCP")
			jSQ_fn(BaseI,"","jIPlugIn_Net*")
		jSQ_end();

		jSQ_Interface(jIPlugIn_Connection)
			jSQ_var(m_pClientSession,"jINetSession_Service*")
			jSQ_fn(BaseI,"","jIPlugIn_Net*")
		jSQ_end();
	}

}

namespace nMech
{
	namespace nNET
	{
		jSQ_REGIST_BIND(nNET)
		{
			nSQ_jINet::init_SQ();
			nSQ_jIPacketSocket_IOCP::init_SQ();
			jSQ_jINetSession_Service::init_SQ();
			nSQ_jIPlugIn::init_SQ();
		}
		namespace Impl
		{
			void jNET_Plugin_callback_OnIoConnected(jIPlugIn_Net* m_pPlugIn, jIPacketSocket_IOCP* pS)
			{
				m_pPlugIn->OnIoConnected(pS);

#if 0 // 멀티스레드 버그 -> 메세지 큐잉 해야함.
				SquirrelObject* pSO = m_pPlugIn->GetSQTable();
				if(pSO)
				{
					try 
					{	
						SquirrelFunction<void> func(*pSO,jS(OnIoConnected));
						if(!func.func.IsNull()) 
						{
							func( m_pPlugIn,pS); 
						}
					} 
					jSQ_CATCH_ERROR();
				}
#endif
			}
			void JOB_jNET_Plugin_callback_OnIoDisconnected(nEVENT::jIMessage* pM)
			{
				jIPlugIn_Net* m_pPlugIn = (jIPlugIn_Net*)pM->GetArg(0)->GetUserData();
				jIPacketSocket_IOCP* pS = (jIPacketSocket_IOCP*)pM->GetArg(1)->GetUserData();
				if(!m_pPlugIn || !pS)
				{
					pM->Erase();
					return;
				}
#if 0 // 멀티스레드 버그 -> 메세지 큐잉 해야함.
				SquirrelObject* pSO = m_pPlugIn->GetSQTable();
				if(pSO)
				{
					try 
					{
						SquirrelFunction<void> func(*pSO,jS(OnIoDisconnected));
						if(!func.func.IsNull()) 
						{
							func(m_pPlugIn,pS); 
						}
					} 
					jSQ_CATCH_ERROR();
				}
#endif
			}

			void jNET_Plugin_callback_OnIoDisconnected(jIPlugIn_Net* m_pPlugIn, jIPacketSocket_IOCP* pIS)
			{
				jPacketSocket_IOCP* pS = (jPacketSocket_IOCP*)pIS;
				m_pPlugIn->OnIoDisconnected(pS);
				nEVENT::jIMessage* pM = g_pjNet->m_pMM_Util->Regist_Loop(0,jFUNC_Msg(JOB_jNET_Plugin_callback_OnIoDisconnected),2,false);
				pM->GetArg(0)->SetUserData(m_pPlugIn);
				pM->GetArg(1)->SetUserData(pS);
				pM->DoWakeUp();
				
				if(pS->m_pGridNode)
				{
					((jNetGrid*)m_pPlugIn->m_pjINetGrid)->deleteGrid(pS);
				}

			}

			void jNET_Plugin_callback_Start(jIPlugIn_Net* m_pPlugIn)
			{
				m_pPlugIn->Start();
				m_pPlugIn->Load_SQ();
				SquirrelObject* pSO = m_pPlugIn->GetSQTable();
				if(pSO)
				{
					try 
					{	
						SquirrelFunction<void> func(*pSO,jS(Start));
						if(!func.func.IsNull()) 
						{	
							func( m_pPlugIn); 
						}
					} 	
					jSQ_CATCH_ERROR();
				}
				GetjILog()->Log(jLogL,_T("Start : %s"),m_pPlugIn->m_pE->GetTagName());
			}
			void jNET_Plugin_callback_Stop(jIPlugIn_Net* m_pPlugIn)
			{
				SquirrelObject* pSO = m_pPlugIn->GetSQTable();
				if(pSO)
				{
					try 
					{	
						SquirrelFunction<void> func(*pSO,jS(Stop));
						if(!func.func.IsNull()) 
						{	
							func( m_pPlugIn); 
						}
					} 	
					jSQ_CATCH_ERROR();
				}
				m_pPlugIn->Stop();
				GetjILog()->Log(jLogL,_T("Stop : %s"),m_pPlugIn->m_pE->GetTagName());
			}

		}//namespace Impl
	}//namespace nNET

}