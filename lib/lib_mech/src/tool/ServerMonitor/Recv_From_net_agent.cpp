/* file : Recv_From_net_agent.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-05-12 21:01:52
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "./grid/jServerMonitor.h"
#include "./net/protocal/PT_MonitorServer_Enum.h"
using namespace nMech::nNET::nMonitorServer;


jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(A2M_SERVER_CONNECTED)
	{
		// BYTE buf[1024]  ,jServerMonitor* pSM = g_pjServerMonitor
		READ_PACKET_jSM(A2M_SERVER_CONNECTED);
		cstr szServerTypeHelp = ToServerTypeHelp(Data.eServerType.c_str());

		jIE* peSERVER_ZONE = pSM->find_peSERVER_ZONE_by_socket(pS);
		jRETURN(peSERVER_ZONE);

		jIE* peSERVER_MENU = peSERVER_ZONE->FindByFirstAttr(jS(HELP),jIVar::EDcstr , jS(SERVER_MENU));
		jRETURN(peSERVER_MENU);
		jIE* peSERVER_MENU_NODE = nSM::find_Control(peSERVER_MENU,szServerTypeHelp);
		jRETURN(peSERVER_MENU_NODE);

		jIE* peSERVER_MENU_HEIGHT = nSM::find_Control(peSERVER_MENU_NODE, jS(SERVER_MENU_HEIGHT));
		jRETURN(peSERVER_MENU_HEIGHT);
		jIVar* pV = nGLOBAL::g_pDocApp->Find(jS(Grid_Config))->Find(jS(ServerMenuNode_Height))->GetVar();
		peSERVER_MENU_HEIGHT->GetVar()->Set_int(pV->Get_int());

		pSM->updateCellMessage(peSERVER_MENU_HEIGHT);

		jIE* peStatus = peSERVER_MENU_NODE->FindByFirstAttr(jS(Label),jIVar::EDcstr, jS(state));
		jRETURN(peStatus);
		pSM->server_state_cell_change(Data.eServerState.c_str(),peStatus);

	}

	void set_A2M_NOTIFY_SERVER_INFO(jServerMonitor* pSM , jIE* peSERVER_ZONE,tcstr szServerTypeHelp , tcstr szServerState, wcstr info)
	{
		jIE* peSERVER_MENU = nSM::find_Control(peSERVER_ZONE,jS(SERVER_MENU));
		jRETURN(peSERVER_MENU);
		jIE* peServer = nSM::find_Control(peSERVER_MENU, szServerTypeHelp);
		jRETURN(peServer);
		jIE* peStatus = peServer->FindByFirstAttr(jS(Label),jIVar::EDcstr, jS(state));
		jRETURN(peStatus);
		pSM->server_state_cell_change(szServerState,peStatus);

		// <Cell i2_ColRow='7;2' Alignment='RIGHT' Label='PID' Value='0' />
		jIE* peSERVER_INFO_CELL = peServer->FindByFirstAttr(jS(HELP),jIVar::EDcstr, jS(SERVER_INFO_CELL));
		jRETURN(peSERVER_INFO_CELL);

		vector<wstring> out;
		nString::jSplitW(info,L"~",out);
		for(size_t i=0; i< out.size(); ++i)
		{
			vector<wstring> outVar;
			nString::jSplitW(out[i].c_str() ,L"=",outVar);
			jCONTINUE(outVar.size()==2);
			jIE* peLabel = find_server_info_label(peSERVER_INFO_CELL,jT(outVar[0].c_str()));
			if(peLabel)
			{
				nUNI::scb2048_t str(outVar[1]);
				if(outVar[1].size()>32)
				{
					nXML::jE e = peLabel;
					e.AttrP(jS(Note)).T() = str.getT();
					peLabel->GetAttrVar(jS(Value))->FromString(jT(outVar[0].c_str()));
				}
				else
				{
					peLabel->GetAttrVar(jS(Value))->FromString(str.getT());
				}
				//peLabel->GetAttrVar(jS(Value))->Set_cstr(jT(outVar[1].c_str()) );
			}
		}
		pSM->updateCellMessage(peSERVER_INFO_CELL);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(A2M_NOTIFY_SERVER_INFO)
	{
		// BYTE buf[1024]  ,jServerMonitor* pSM = g_pjServerMonitor
		READ_PACKET_jSM(A2M_NOTIFY_SERVER_INFO);
		tcstr szServerTypeHelp = ToServerTypeHelp(Data.eServerType.c_str() ) ;
		jIE* peSERVER_ZONE = pSM->find_peSERVER_ZONE_by_socket(pS);
		set_A2M_NOTIFY_SERVER_INFO(pSM , peSERVER_ZONE,szServerTypeHelp , Data.eState.c_str() , Data.info.c_str() );
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(A2M_CALL_CMD_RS)
	{
		// BYTE buf[1024]  ,jServerMonitor* pSM = g_pjServerMonitor
		READ_PACKET_jSM(A2M_CALL_CMD_RS);
		vector<wstring> arg;
		nString::jSplitW(Data.cmd, L" " , arg);
		jRETURN(arg.size());

		if(Data.eServerType==jS(eST_AGENT))
		{
			if(arg[0]==L"server_kill")
			{
				jRETURN(arg.size()==2);
				cstr szServer = nSM::GetServerTypeHelp(jT(arg[1].c_str()));
				jIE* peSERVER_ZONE = pSM->find_peSERVER_ZONE_by_socket(pS);
				jRETURN(peSERVER_ZONE);
				jIE* peSERVER_MENU = peSERVER_ZONE->FindByFirstAttr(jS(HELP), jIVar::EDcstr, jS(SERVER_MENU));
				jRETURN(peSERVER_MENU);
				jIE* peServer = nSM::find_Control(peSERVER_MENU,szServer);
				jRETURN(peServer);
				jIE* pe_process_button= nSM::find_Control(peServer,jS(process_button));
				jRETURN(pe_process_button);
				pe_process_button->GetAttrVar(jS(Value))->Set_cstr(_T("run Process") );
				pSM->updateCellMessage(pe_process_button);

				jIE* peStatus= nSM::find_Control(peServer,jS(STATUS_CELL));
				pSM->server_state_cell_change(jS(eSS_Offline), peStatus);
			}
		}
		else
		{
			vector<wstring> out;
			nString::jSplitW(Data.cmd, L"#" , out);
			jRETURN(out.size());
			if(out[0]==L"REFRESH_EServerState")
			{
				cstr szServer = ToServerTypeHelp(Data.eServerType.c_str() );
				jIE* peSERVER_ZONE = pSM->find_peSERVER_ZONE_by_socket(pS);
				jRETURN(peSERVER_ZONE);
				jIE* peSERVER_MENU = peSERVER_ZONE->FindByFirstAttr(jS(HELP), jIVar::EDcstr, jS(SERVER_MENU));
				jRETURN(peSERVER_MENU);
				jIE* peServer = nSM::find_Control(peSERVER_MENU,szServer);
				jRETURN(peServer);
				jIE* peStatus= nSM::find_Control(peServer,jS(STATUS_CELL));
				pSM->server_state_cell_change(jT(out[1].c_str()), peStatus);
			}
		}
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(A2M_MYTHOLOGY_MENU_RS)
	{
		// BYTE buf[1024]  ,jServerMonitor* pSM = g_pjServerMonitor
		READ_PACKET_jSM(A2M_MYTHOLOGY_MENU_RS);
		jIE* peSERVER_ZONE = pSM->find_peSERVER_ZONE_by_socket(pS);
		jRETURN(peSERVER_ZONE);
		jIE* peSERVER_MENU_NODE = find_SERVER_MENU_NODE(peSERVER_ZONE, Data.eServerType.c_str() );
		jRETURN(peSERVER_MENU_NODE);
		jIE* peStatus = nSM::find_Control(peSERVER_MENU_NODE,jS(STATUS_CELL));
		jRETURN(peStatus);
		pSM->server_state_cell_change(jT(Data.cmd), peStatus);
	}

	
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(A2M_PROCESS_STATUS_NOTIFY)
	{
		// BYTE buf[1024]  ,jServerMonitor* pSM = g_pjServerMonitor
		READ_PACKET_jSM(A2M_PROCESS_STATUS_NOTIFY);
		jIE* peSERVER_ZONE = pSM->find_peSERVER_ZONE_by_socket(pS);
		jRETURN(peSERVER_ZONE);
		jIE* peSERVER_MENU = peSERVER_ZONE->FindByFirstAttr(jS(HELP), jIVar::EDcstr, jS(SERVER_MENU));
		jRETURN(peSERVER_MENU);

		cstr szServer = nSM::GetServerTypeHelp(jT(Data.eServerType));
		jIE* peServer = nSM::find_Control(peSERVER_MENU,szServer);
		jRETURN(peServer);
		jIE* pe_process_button= nSM::find_Control(peServer,jS(process_button));
		jRETURN(pe_process_button);

		if(Data.eState=="eSS_Offline")
		{
			pe_process_button->GetAttrVar(jS(Value))->Set_cstr(_T("run Process") );
		}
		else
		{
			pe_process_button->GetAttrVar(jS(Value))->Set_cstr(_T("kill Process") );
		}
		pSM->updateCellMessage(pe_process_button);

		jIE* peStatus= nSM::find_Control(peServer,jS(STATUS_CELL));
		pSM->server_state_cell_change(jT(Data.eState), peStatus);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(A2M_PROCESS_INFO_NOTIFY)
	{
		// BYTE buf[1024]  ,jServerMonitor* pSM = g_pjServerMonitor
		READ_PACKET_jSM(A2M_PROCESS_INFO_NOTIFY);

		jIE* peSERVER_ZONE = pSM->find_peSERVER_ZONE_by_socket(pS);
		pSM->SetProcessInfo( peSERVER_ZONE , jT(Data.eServerType) , Data.name.c_str() , Data.value.c_str() );

	}
	
#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// BYTE buf[1024]  ,jServerMonitor* pSM = g_pjServerMonitor
		READ_PACKET_jSM(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_ToFrontEnd)

