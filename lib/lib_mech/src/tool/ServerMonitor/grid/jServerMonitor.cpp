/* file : jServerMonitor.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-04-14 13:40:49
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "resource.h"
#include "jServerMonitor.h"
#include "ServerMonitor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


var_enum(jCV_DEFINE);


jServerMonitor * g_pjServerMonitor =0;

BEGIN_MESSAGE_MAP(jServerMonitor,CUGCtrl)
	//{{AFX_MSG_MAP(jServerMonitor)
	ON_MESSAGE(jWM_USER_UPDATE_CELL, On_jWM_USER_UPDATE_CELL)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


jServerMonitor::jServerMonitor(jIE* pE) : jGridCtrl(pE)
{
	m_isRocked_Monitor=false;
	g_pjIServerMonitor = this;
	g_pjServerMonitor=this;

}
jServerMonitor::~jServerMonitor()
{
	g_pjServerMonitor=0;
}


LRESULT jServerMonitor::On_jWM_USER_UPDATE_CELL( WPARAM w, LPARAM l )
{
	jIE* it = (jIE*)w;
	CUGCell __cell;
	jIVar* pV;

	jAT_IF(ENABLE)
	{
		if(pV->Get_bool()==false)
			return 0;
	}

	#define call_func342(NAME) else if( it->IsName(jS(NAME)) ) xml_##NAME(it,__cell);

	if(0){}
	for_each_XML_FUNC(call_func342)
	else
	{
		jERROR(  _T("unknown func: %s"),it->GetTagName() );
	}

	this->RedrawAll();
	return 0;
}

void jServerMonitor::Reload_xml(jIE* pE)
{
	this->EditCancel();

	int rows = GetNumberRows() - 1;
	int cols = GetNumberCols() - 1;

	for(int col=0;col<=cols;++col)
	{
		for(int row=0;row<=rows;++row)
		{
			CUGCell cell;
			GetCell(col, row, &cell);
			cell.ClearAll();
			SetCell(col, row, &cell);
		}
	}
	this->ResetAll(true);
 	m_peGrid = pE;
 	OnSetup();
	RedrawAll();
}
void set_ServerTypeName(jIE* peServerType,cstr eVAL,cstr HELP,int iVAL)
{
	jIE* it = peServerType->begin();
	jIVar* pV;
	pV=peServerType->GetAttrVar(jS(HELP));
	if(pV)
	{
		tstring str = pV->Get_cstr();
		nSTL::replace(str, jS(Login) , HELP);
		pV->Set_cstr(str.c_str());
	}

#define jLAMDA_set_ServerTypeName234(X,Z) X(cstr ,eVAL) X(cstr ,HELP) Z(int ,iVAL)
	jLAMDA_for_each(set_ServerTypeName234,jIE*)
	{
		jIVar* pV;
		jAT_IF(Value)
		{
			if(pV->IsType(jIVar::EDcstr))
			{
				tstring str = pV->Get_cstr();
				nSTL::replace(str, jS(Login) , HELP);
				pV->Set_cstr(str.c_str());
			}
		}
		jAT_IF(Row)
		{
			int iRow = pV->Get_int() + iVAL;
			pV->Set_int( iRow );
		}
		jAT_IF(ColRow)
		{
			pV->GetInt(1)  = pV->GetInt(1) + iVAL;
		}
		jAT_IF(NAME)
		{
			tstring str = pV->Get_cstr();
			nSTL::replace(str, jS(eLOGIN) , eVAL);
			pV->Set_cstr(str.c_str());
		}
	}
	jLAMDA_end();
	peServerType->for_each(set_ServerTypeName234(eVAL,HELP,iVAL));

}

// ServerType에 따라 서버메뉴를 HIDE/SHOW 시킴
void set_HIDE_SHOW_By_ServerType(jIE* peReserved,jIE* peSERVER_MENU)
{
	return;
#ifndef DF_ENABLE_SERVER_FORM_BY_App_ServerMonitor
	return ;
#endif
	bool isShowZone=true;
	bool isShowLogin=false;
	if(peReserved)
	{
		jIVar* pvServerType = peReserved->GetAttrVar(jS(ServerType));
		if(!pvServerType) // ServerType의 default값은 Zone이다.
		{
			isShowLogin=false;
			isShowZone=true;
		}
		else
		{
			isShowLogin=jt_strstr(pvServerType->Get_cstr() ,jS(Login));
			isShowZone=jt_strstr(pvServerType->Get_cstr() ,jS(Zone));
		}
	}

	if(!isShowLogin)
	{
		jIE* peLogin= peSERVER_MENU->FindByFirstAttr(jS(HELP),jIVar::EDcstr, jS(Login));
		if(peLogin)
		{
			jIE* peSubMenu = peLogin->FindByFirstAttr(jS(HELP),jIVar::EDcstr, jS(SubMenu));
			if(peSubMenu)
			{
				peSubMenu->GetAttrVar(jS(ENABLE))->Set_bool(false);
			}
			jIE* peSERVER_MENU_HEIGHT= peLogin->FindByFirstAttr(jS(HELP),jIVar::EDcstr, jS(SERVER_MENU_HEIGHT));
			if(peSERVER_MENU_HEIGHT)
				peSERVER_MENU_HEIGHT->GetVar()->Set_int(0);
		}
	}
	if(!isShowZone)
	{
		jIE* peZone= peSERVER_MENU->FindByFirstAttr(jS(HELP),jIVar::EDcstr, jS(Zone));
		if(peZone)
		{
			jIE* peSubMenu = peZone->FindByFirstAttr(jS(HELP),jIVar::EDcstr, jS(SubMenu));
			if(peSubMenu)
			{
				peSubMenu->GetAttrVar(jS(ENABLE))->Set_bool(false);
			}
			jIE* peSERVER_MENU_HEIGHT= peZone->FindByFirstAttr(jS(HELP),jIVar::EDcstr, jS(SERVER_MENU_HEIGHT));
			if(peSERVER_MENU_HEIGHT)
				peSERVER_MENU_HEIGHT->GetVar()->Set_int(0);
		}
	}
}

void jServerMonitor::OnSetup()
{
	jIE* it ;
	if(!g_peServerExeList)
		g_peServerExeList = nGLOBAL::g_pDocApp->Find(jS(ServerExeList));

	m_peServerList_FromApp = nGLOBAL::g_pDocApp->Find(jS(ServerList));
	jIE* peConfig = nGLOBAL::g_pDocApp->Find(jS(Grid_Config));
#define _CFG(X) peConfig->Find(jS(X))->GetVar()
#define _CFGi(X) _CFG(X)->Get_int()

	jIE* peSERVER_ZONE_org = m_peGrid->FindByFirstAttr(jS(HELP) , jIVar::EDcstr, jS(SERVER_ZONE));
	jIE* peSERVER_ZONE_root= peSERVER_ZONE_org->GetParent();
	jIE* peROOT_CATEGORY = m_peGrid->FindByFirstAttr(jS(HELP) , jIVar::EDcstr, jS(ROOT_CATEGORY));
	jIE* peRootConfig = peROOT_CATEGORY->FindByFirstAttr(jS(Value) , jIVar::EDcstr, jS(Config));

	int Machine_Count = _CFGi(Machine_Count); 
	int Machine_Row = _CFGi(Machine_Row) + g_peServerExeList->size(); // <ServerExeList>갯수 + Agent Row 수 ( ServerSuit다음에 위치하므로 값이 1이다.)

	jIE* peAGENT_ROW_SET = peSERVER_ZONE_org->FindByFirstAttr(jS(HELP) , jIVar::EDcstr, jS(AGENT_ROW_SET));
	if(peAGENT_ROW_SET)
	{
		jIVar* pV = peAGENT_ROW_SET->GetAttrVar(jS(EndColRow));
		if(pV)
		{
			pV->GetInt(1) = Machine_Row;
		}
	}

	int currRow=0;
	jIE* peExpandCell_org = peSERVER_ZONE_org->begin();
	int iStartRow = peExpandCell_org->GetAttrVar(jS(ColRow))->GetInt(1);
	tstring sName = peExpandCell_org->GetAttr(jS(Value));
	vector<tstring> out;
	nString::jSplit(sName,_T(" "),out);
	sName = out[0];
	int iStart=0;
	if(out.size()>=2 && out[1].size())
	{
		iStart = jt_atoi(out[1].c_str());
	}

	//--------------------------------------------------------------------------
	// login/zone/pbrms 서버 리스트 메뉴
	//--------------------------------------------------------------------------
	jIE* peSERVER_MENU = peSERVER_ZONE_org->FindByFirstAttr(jS(HELP),jIVar::EDcstr,jS(SERVER_MENU));
	jIE* peOrg = peSERVER_MENU->begin();

	jIE* itST = g_peServerExeList->begin()->GetRight();
	jrFOR(itST)
	{
		jIE* peNew = peSERVER_MENU->InsertChildElement(jS(NULL));
		peOrg->CopyTo(peNew);
		//peNew->GetAttrVar(jS(HELP))->Set_cstr(itST->Get_cstr());
		set_ServerTypeName(peNew,itST->GetTagName() , itST->Get_cstr() ,itST->GetOrder());
	}
	assert(g_peServerExeList->size() == peSERVER_MENU->size());

	for(int i=1; i< Machine_Count;++i)
	{
		jIE* peSERVER_ZONE = peSERVER_ZONE_root->InsertChildElement(jS(NULL));
		peSERVER_ZONE_org->CopyTo(peSERVER_ZONE);
		
		// 
		jIE* peExpandCell = peSERVER_ZONE->Find(jS(ExpandCell));
		jIE* it = peExpandCell;
		currRow = iStartRow + i*Machine_Row;
		fname_t szBuf;
		jt_sprintf(szBuf, _T("%s %d"),sName.c_str(), iStart+i);
		jAT(Value)->Set_cstr(szBuf);

		#define jLAMDA_offset_Col(X,Z) Z(int ,currRow)
		jLAMDA_for_each(offset_Col,jIE*)
		{
			jIVar* pV;
			jAT_IF(Row)
			{
				int iRow = currRow + pV->Get_int()-1;
				pV->Set_int( iRow );
			}
			jAT_IF(ColRow)
			{
				int iRow = currRow + pV->GetInt(1)-1;
				pV->GetInt(1)=iRow;
			}
			jAT_IF(StartColRow)
			{
				int iRow = currRow + pV->GetInt(1)-1;
				pV->GetInt(1)=iRow;
			}
			jAT_IF(EndColRow)
			{
				int iRow = currRow + pV->GetInt(1)-1;
				pV->GetInt(1)=iRow;
			}
		}
		jLAMDA_end();
		peSERVER_ZONE->for_each(offset_Col(currRow));
	}
	currRow = currRow+ Machine_Row;
	peRootConfig->GetAttrVar(jS(ColRow))->GetInt(1) = currRow;
	m_peGrid->GetAttrVar(jS(Size))->GetInt(1)= _CFGi(Config_Row) +currRow;

	jIE* peSERVER_ZONE = peSERVER_ZONE_root->begin();
	jIE* peReserved = m_peServerList_FromApp->begin();
	jrFOR(peSERVER_ZONE)
	{
		jIE* peSERVER_MENU = peSERVER_ZONE->FindByFirstAttr(jS(HELP),jIVar::EDcstr, jS(SERVER_MENU));

		if(!peReserved) 
		{
			set_HIDE_SHOW_By_ServerType(0,peSERVER_MENU);
			continue;
		}

		peReserved->SetUserData(jS(peSERVER_ZONE),peSERVER_ZONE);
		peSERVER_ZONE->SetUserData(jS(m_peServerList_FromApp),peReserved);
		cstr szReservedName = peReserved->GetAttr(jS(Name));
		if(szReservedName)
		{
			it = peSERVER_ZONE->Find(jS(ExpandCell));
			fname_t szBuf;
			jt_sprintf(szBuf, _T("[Agent] %s:"),szReservedName);
			jAT(Value)->Set_cstr(szBuf);
		}
		it = peSERVER_ZONE->FindByFirstAttr(jS(Label),jIVar::EDcstr,jS(ip));
		if(it)
		{
			cstr szReservedIP = peReserved->Get_cstr();
			jAT(Value)->Set_cstr(szReservedIP);
		}
		set_HIDE_SHOW_By_ServerType(peReserved,peSERVER_MENU);
		peReserved = peReserved->GetRight();

	}

	struct disable_PbRms_Context
	{
		void operator()(jIE* peSERVER_MENU_NODE, jIPacketSocket_IOCP*)
		{
			jIVar* pV = peSERVER_MENU_NODE->GetAttrVar(jS(HELP));
			jRETURN(pV);
			if(pV->IsContents(jS(Login))) return;
			if(pV->IsContents(jS(Zone))) return;
			jIE* peSERVER_CONTEXT_MENU = nSM::find_Control(peSERVER_MENU_NODE, jS(SERVER_CONTEXT_MENU) );
			jRETURN(peSERVER_CONTEXT_MENU);
			peSERVER_CONTEXT_MENU->GetAttrVar(jS(ENABLE))->Set_bool(false);
		}
	};

	this->for_each_SERVER_MENU(disable_PbRms_Context());


	parent_t::OnSetup();
}
namespace nSM
{
	cstr ToServerStateColor(cstr szServerState)
	{
		jIE* pE = nGLOBAL::g_pDocApp->Find(jS(EServerState_Color));
		jASSERT(pE);
		jIE *peColor = pE->Find(szServerState);
		jRETURN_ret(_T("250;250;250"),peColor);
		return peColor->Get_cstr();
	}

}

void jServerMonitor::server_state_cell_change(cstr szServerState,jIE* it)
{
	jIVar* pV;
	jAT(Value)->Set_cstr(szServerState);
	jAT(TColor)->Set_cstr(jS(ACTIVECAPTION));
	jAT(Border)->Set_cstr(jS(RAISED));
	pV =jAT(BColor);
	pV->SetType(jIVar::EDint3);
	pV->FromString(nSM::ToServerStateColor(szServerState));
	assert( ((jIE*)((WPARAM)it)) == it);
	updateCellMessage(it);

	tstring temp;
	jIE* peServer = parent_SERVER_MENU_NODE(it,temp);
	jRETURN (peServer);

	jIE* pe_process_button = nSM::find_Control(peServer,jS(process_button));
	jRETURN(pe_process_button);
	if(tstring(jS(eSS_Offline))!=szServerState)
		pe_process_button->GetAttrVar(jS(Value))->Set_cstr(_T("kill Process"));
	else
	{
		pe_process_button->GetAttrVar(jS(Value))->Set_cstr(_T("run Process"));
		if(m_isRocked_Monitor)
		{
			cstr agent_ip=_T("UnkownIP");
			cstr process_name=_T("UnkownProcess");

			jONCE
			{
				cstr szServerTypeHelp = peServer->GetAttr(jS(HELP));
				jBREAK(szServerTypeHelp);
				jIE* pE = g_peServerExeList->FindByContents(jS(NULL) ,jIVar::EDcstr , const_cast<TCHAR*>(szServerTypeHelp) );
				jBREAK(pE);
				process_name = pE->GetTagName();

				jIE* peSERVER_ZONE = parent_SERVER_ZONE(it,0);
				jBREAK(peSERVER_ZONE);
				jIE* peIP = nSM::find_Control(peSERVER_ZONE ,jS(AGENT_IP));
				jBREAK(peIP);
				cstr szIP = peIP->GetAttr(jS(Value));
				if(szIP) agent_ip = szIP;
			}
			tfname_t szArg;
			jt_sprintf(szArg,_T("%s %s"),agent_ip, process_name );
			
			tname1024_t szExe;
			jt_sprintf(szExe,_T("%sServerMonitor_ProcessKillEvent.bat"),g_ExeEnv.m_szModuleDir);
			ShellExecute( NULL, _T( "open" ),szExe , szArg, NULL, SW_SHOWNORMAL );
		}
	}

	updateCellMessage(pe_process_button);
}
//--------------------------------------------------------------------------
//jIServerMonitor interface 정의
//--------------------------------------------------------------------------
int32 jServerMonitor::On_X2S_LOGIN(S_X2S_LOGIN& Data,int32 did,jIPacketSocket_IOCP* pS)
{
	fname_t szIP;
	pS->GetAddressString(szIP);
	TCHAR* ch = jt_strchr(szIP,':');
	if(ch)	*ch=0;
	jIE* pE = m_peServerList_FromApp->FindByContents(jS(Machine), jIVar::EDcstr,szIP);
	if(!pE)
	{
		nXML::jE e = m_peServerList_FromApp->InsertChildElement(jS(Machine));
		e.Var().T()=szIP;
		e.AttrP(jS(Name)).T()=jT(Data.name);
		pE = e;
	}
	pE->SetUserData(jS(jIPacketSocket_IOCP),pS);
	jIE* peSERVER_ZONE = (jIE*)pE->GetUserData(jS(peSERVER_ZONE));
	if(!peSERVER_ZONE)
	{
		struct _find_free_SERVER_ZONE
		{
			bool operator() ( jIE* peSERVER_ZONE)
			{
				//m_peServerList_FromApp가 세팅된 peSERVER_ZONE노드는 예약된 노드이므로..
				if( peSERVER_ZONE->GetUserData(jS(m_peServerList_FromApp)) )
					return false;
				
				return !peSERVER_ZONE->GetUserData(jS(jIPacketSocket_IOCP));	
			}
		};
		peSERVER_ZONE = find_if_SERVER_ZONE(_find_free_SERVER_ZONE());
		jRETURN_ret(did, peSERVER_ZONE);
	}
	jASSERT( !peSERVER_ZONE->GetUserData(jS(jIPacketSocket_IOCP)) );

	peSERVER_ZONE->SetUserData(jS(jIPacketSocket_IOCP),pS);

	jIE* peAGENT_NAME = nSM::find_Control(peSERVER_ZONE,jS(AGENT_NAME));
	if(peAGENT_NAME)
	{
		jIVar* pV = peAGENT_NAME->GetAttrVar(jS(Value));
		if(pV)
		{
			fname_t szBuf;
			jt_strcpy(szBuf,pV->Get_cstr());
			TCHAR* ch = jt_strrchr(szBuf,':');
			if(ch) *(ch+1)=0;
			fname_t szName;
			jt_sprintf(szName,_T("%s %s"), szBuf,Data.name);
			pV->Set_cstr(szName);

			updateCellMessage(peAGENT_NAME);
		}
	}
	jIE* peAGENT_IP = nSM::find_Control(peSERVER_ZONE,jS(AGENT_IP));
	if(peAGENT_IP)
	{
		jIVar* pV = peAGENT_IP->GetAttrVar(jS(Value));
		if(pV)
		{
			fname_t szIP;
			pS->GetIP(szIP);
			TCHAR* ch = jt_strchr(szIP,':');
			if(ch)*ch=0;
			pV->Set_cstr(szIP);
			updateCellMessage(peAGENT_IP);
		}
	}

	jIE* it= peSERVER_ZONE->FindByFirstAttr(jS(Label),jIVar::EDcstr,jS(state));
	if(it)
	{
		server_state_cell_change(jS(eSS_StartUp),it);
	}

	jIE* peSERVER_MENU = nSM::find_Control(peSERVER_ZONE, jS(SERVER_MENU));
	jASSERT(peSERVER_MENU);
	for(int i=0; i< Data.servers.size(); ++i)
	{
		jIE* peSERVER_MENU_NODE = peSERVER_MENU->FindByFirstAttr(jS(HELP), jIVar::EDcstr 
			, const_cast<TCHAR*>(nSM::GetServerTypeHelp(jT(Data.servers[i].c_str())) )
		, 1 );
		jCONTINUE(peSERVER_MENU_NODE);
		
		jIE* peSTATUS_CELL= nSM::find_Control(peSERVER_MENU_NODE,jS(STATUS_CELL));
		jCONTINUE(peSTATUS_CELL);
		this->server_state_cell_change(Data.states[i].c_str(),peSTATUS_CELL);
	}

#ifndef DF_ENABLE_SERVER_FORM_BY_App_ServerMonitor

	jIE* peSERVER_MENU = m_peGrid->FindByFirstAttr(jS(HELP),jIVar::EDcstr,jS(SERVER_MENU));
	for( int i =0; i< Data.servers.size() ; ++i)
	{
		vector<astring> out;
		nString::jSplitA(Data.servers[i],"," , out);
		jCONTINUE(out.size()==2);
		jIE* pE= peSERVER_MENU->FindByFirstAttr(jS(HELP),jIVar::EDcstr , jT(out[0].c_str()));
		jCONTINUE(pE);
		jIE* peSERVER_MENU_HEIGHT = pE->FindByFirstAttr(jS(HELP),jIVar::EDcstr , jS(SERVER_MENU_HEIGHT));
		jCONTINUE(peSERVER_MENU_HEIGHT);
		int iH = peSERVER_MENU_HEIGHT->GetVar()->Get_int();
		int is1 = ja_strcmp(out[1].c_str(),"NULL");
		int is2 = ja_strcmp(out[1].c_str(),"null");

		const int min_h = 0;
		if(out[1].size()==0 || is1==0 || is2==0)
		{
			if(iH!=min_h)
			{
				peSERVER_MENU_HEIGHT->GetVar()->Set_int(min_h);
				this->PostMessage(jWM_USER_UPDATE_CELL, (WPARAM)peSERVER_MENU_HEIGHT, 0);
			}
		}
		else
		{
			if(iH==min_h)
			{
				peSERVER_MENU_HEIGHT->GetVar()->Set_int(28);
				this->PostMessage(jWM_USER_UPDATE_CELL, (WPARAM)peSERVER_MENU_HEIGHT, 0);
			}
		}

	}
#endif //DF_ENABLE_SERVER_FORM_BY_App_ServerMonito r
	return did;
}

void jServerMonitor::OnIoDisconnected(int32 did,jIPacketSocket_IOCP* pS)
{
	jIE* peSERVER_ZONE = find_peSERVER_ZONE_by_socket(pS);
	if(!peSERVER_ZONE) return;
	peSERVER_ZONE->SetUserData(jS(jIPacketSocket_IOCP),0);
	jIE* peState= peSERVER_ZONE->FindByFirstAttr(jS(Label),jIVar::EDcstr,jS(state));
	this->server_state_cell_change(jS(eSS_Offline),peState);
	tstring str;
	struct set_OnIoDisconnected
	{
		jServerMonitor* pSM;
		set_OnIoDisconnected(jServerMonitor* pSM_):pSM(pSM_){}
		void operator()(jIE* peSERVER_MENU_NODE,jIPacketSocket_IOCP* pS)
		{
			jIE* peState = nSM::find_Control(peSERVER_MENU_NODE, jS(STATUS_CELL));
			jRETURN(peState);
			g_pjServerMonitor->server_state_cell_change(jS(eSS_Offline), peState);
			jIE* peSubMenu = nSM::find_Control(peSERVER_MENU_NODE,jS(SubMenu));
			jRETURN(peSubMenu);
			peSubMenu->GetAttrVar(jS(ENABLE))->Set_bool(false);
			jIE* peSERVER_MENU_HEIGHT = nSM::find_Control(peSERVER_MENU_NODE,jS(SERVER_MENU_HEIGHT));
			jRETURN(peSERVER_MENU_HEIGHT);
			peSERVER_MENU_HEIGHT->GetVar()->Set_int(0);
			pSM->updateCellMessage(peSERVER_MENU_NODE);
		}
	};
	this->for_each_SERVER_MENU(set_OnIoDisconnected(this), peSERVER_ZONE);
}


void jServerMonitor::SetProcessInfo(jIE* peSERVER_ZONE , tcstr szServerType, wcstr szInfo,wcstr szValue)
{
	jIE* peSERVER_MENU = nSM::find_Control(peSERVER_ZONE,jS(SERVER_MENU));
	jRETURN(peSERVER_MENU);
	cstr szServerTypeHelp = ToServerTypeHelp(szServerType);
	jIE* peServer = nSM::find_Control(peSERVER_MENU, szServerTypeHelp);
	jRETURN(peServer);

	// <Cell i2_ColRow='7;2' Alignment='RIGHT' Label='PID' Value='0' />
	jIE* peSERVER_INFO_CELL = peServer->FindByFirstAttr(jS(HELP),jIVar::EDcstr, jS(SERVER_INFO_CELL));
	jRETURN(peSERVER_INFO_CELL);
	jIE* peLabel = find_server_info_label(peSERVER_INFO_CELL , jT(szInfo));
	if(peLabel)
	{
		nUNI::scb2048_t str(szValue);
		if(jw_strlen(szValue)>32)
		{
			nXML::jE e = peLabel;
			e.AttrP(jS(Note)).T() = str.getT();
			peLabel->GetAttrVar(jS(Value))->FromString(jT(szInfo));
		}
		else
		{
			peLabel->GetAttrVar(jS(Value))->FromString(str.getT());
		}
	}
	updateCellMessage(peLabel);
}


jIE* jServerMonitor::find_peSERVER_ZONE_by_socket(jIPacketSocket_IOCP*pS)
{
	jIE* peSERVER_ZONE= m_peGrid->FindByFirstAttr(jS(HELP) , jIVar::EDcstr, jS(SERVER_ZONE));

	jIE* pE = peSERVER_ZONE;
	jrFOR(pE)
	{
		jIPacketSocket_IOCP* ps = (jIPacketSocket_IOCP*)pE->GetUserData(jS(jIPacketSocket_IOCP));
		if(ps && ps == pS)
			return pE;
	}
	return 0;
}

jIE* parent_SERVER_ZONE(jIE* it, jIPacketSocket_IOCP** ppS)
{
	jIVar* pV;
	for( ; !it->isRoot() ; it = it->GetParent() )
	{
		jAT_IF(HELP)
		{
			if(pV->IsContents(jS(SERVER_ZONE)))
			{
				if(ppS)
				{
					jIPacketSocket_IOCP* pS = (jIPacketSocket_IOCP*)it->GetUserData(jS(jIPacketSocket_IOCP));
					*ppS = pS;
				}
				return it;
			}
		}
	}
	if(ppS) *ppS=0;
	return 0;
}

jIE* parent_SERVER_MENU(jIE* it)
{
	jIVar* pV;
	for( ; !it->isRoot() ; it = it->GetParent() )
	{
		jAT_IF(HELP)
		{
			if(pV->IsContents(jS(SERVER_MENU))) return it;
		}
	}
	return 0;
}


jIE* parent_SERVER_MENU_NODE(jIE* it,OUT tstring& serverName)
{
	serverName=_T("");
	jIVar* pV;
	for( ; !it->isRoot() ; it = it->GetParent() )
	{
		jAT_IF(HELP2)
		{
			if(!pV->IsContents(jS(SERVER_MENU_NODE))) continue;
			serverName = it->GetAttr(jS(HELP));
			return it;
		}
	}
	return 0;
}



jIE* find_SERVER_MENU_NODE(jIE* peSERVER_ZONE, tcstr szServerType )
{
	jCHECK_ServerType(szServerType);
	tcstr sz = ToServerTypeHelp(szServerType);

	jIE* peSERVER_MENU = peSERVER_ZONE->FindByFirstAttr(jS(HELP), jIVar::EDcstr, jS(SERVER_MENU));
	jRETURN_ret(0,peSERVER_MENU);
	jIE* peServer = nSM::find_Control(peSERVER_MENU,sz);
	return peServer;
}

jIE* find_server_info_label(jIE* peSERVER_INFO_CELL , cstr szLabel)
{
	jIE* pE = peSERVER_INFO_CELL->FindByFirstAttr(jS(Label) , jIVar::EDcstr , const_cast<TCHAR*>(szLabel) );
	if(pE) return pE;
	jIE*peProto = peSERVER_INFO_CELL->begin();
	int iStartCol = peProto->GetAttrVar(jS(ColRow))->GetInt(0);
	jIE* peNew = peSERVER_INFO_CELL->InsertChildElement(jS(Cell));
	peProto->CopyTo(peNew);
	jIVar* pV = peNew->GetAttrVar(jS(Label));
	pV->Set_cstr(szLabel);
	pV = peNew->GetAttrVar(jS(ColRow));
	pV->GetInt(0) = iStartCol + peNew->GetOrder();

	return peNew;
}


namespace nSM
{
	cstr GetServerType(cstr szServerTypeHelp)
	{
		jIE* it = g_peServerExeList->FindByContents(jS(NULL), jIVar::EDcstr , const_cast<TCHAR*>(szServerTypeHelp));
		if(!it) return jS(NULL);
		return it->GetTagName();
	}
	cstr GetServerTypeHelp(cstr szServerType)
	{
		jIE* it = g_peServerExeList->Find(szServerType);
		if(!it) return jS(NULL);
		return it->Get_cstr();
	}
}

