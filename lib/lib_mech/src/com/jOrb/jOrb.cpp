// jOrb.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "jOrb.h"
#include "PlugIn_Orb.h"
#include "base/jWindow_Util.h"
#include "header/jAutoPtr.h"
#include "interface/xml/jIXmlUtil.h"

jOrb g_jOrb;


void jOrb::_Create(jIE* pE)
{

}
void jOrb::_Delete()
{
	for(size_t i=0; i<m_UsingService.size();++i)
	{
		if(m_UsingService[i]==jS(NULL))
			continue;

		tname256_t szRegPath;
		jt_sprintf(szRegPath, _T("SOFTWARE\\jGame\\ORB\\Ver01\\%s"), m_UsingService[i].c_str());
		nFunctor::jIE_AutoPtr pE;
#ifndef UNICODE
		cstr szURL = jS(address_list_ansi123);
#else
		cstr szURL = jS(address_list_unicode123);
#endif
		pE->ChangeTagName(szURL);
		GetjIXml()->GetXmlUtil()->LoadFromRegistry(pE,szRegPath,szURL);
		nXML::jE e = (jIE*)pE;
		jIE* pe1 = pE->Find(Get_Uniq_AppNicName());
		if(pe1)	pe1->Erase();
		GetjIXml()->GetXmlUtil()->SaveToRegistry(pE,szRegPath,szURL);

	}
}
jID* jOrb::GetDoc()
{
	return m_eNetConfig->GetDoc();
}
void jOrb::Start(jIOrb_system_callback_t* func,tcstr szOrbServerList,tcstr szMyServiceName ,tcstr netConfigXml)
{
	if(!nInterface::g_pjINet_OGS)
	{
		jMB("<jINet b_ENABLE='1'>jNet.dll</jINet>를 추가하시오", "nInterface::g_pjINet_OGS==NULL");
		exit(1);
	}
	m_pMM = nEVENT::jIMsgManager::Get(_T("_nNET::jNet"),true);

	//--------------------------------------------------------------------------
	// Orb_NetConfig.xml 세팅
	//--------------------------------------------------------------------------
	m_jIOrb_system_callback = func;
	m_docOrbConfig = GetjIXml()->Load(netConfigXml);
	m_eNetConfig = m_docOrbConfig(jS(ORB_NET));
	jASSERT0(m_eNetConfig.full());

	//--------------------------------------------------------------------------
	// 자신의 Orb서비스용 소켓 시작
	//--------------------------------------------------------------------------
	bool isMyService = szMyServiceName && jt_strlen(szMyServiceName) && jt_strcmp(szMyServiceName,jS(NULL));
	if( isMyService )
	{
		nXML::jE eMyServiceOrbNode = m_docOrbConfig(jS(ORB_APP_LIST))(szMyServiceName);
		cstr szIP = eMyServiceOrbNode.Attr(jS(IP))->Get_cstr();
		cstr szPort = jt_strchr(szIP,':');
		++szPort;
		int iPort = jt_atoi(szPort);
		m_eNetConfig(jS(PlugIn_Orb)).AttrP(jS(UdpLocalPort)).T() = iPort;
	}
	nInterface::g_pjINet_OGS->CreateNetObject(m_eNetConfig);
	nInterface::g_pjINet_OGS->RunNetObject(m_eNetConfig);
	while(!g_pCurrPlugIn){jLOG(_T("Wait for ORB udp opening"));}

	fname_t szMyIP;
	g_pCurrPlugIn->m_pClientSession->Get_ClientSocket(0)->GetAddressString(szMyIP);

	//--------------------------------------------------------------------------
	// ORB 서버에 접속
	//--------------------------------------------------------------------------
	nswb256_t send_buf;
	nString::jSplit(szOrbServerList,_T("; \t\n"),m_UsingService);
	for(size_t i =0; i<m_UsingService.size() ; ++i)
	{
		if(m_UsingService[i]==jS(NULL))
			continue;
		jIE* peTarget = m_docOrbConfig(jS(ORB_APP_LIST))->FindByDepth(1, m_UsingService[i].c_str() );
		if(!peTarget)
		{
			jWARN(_T("ORB_APP_LIST : %s is not found"), m_UsingService[i].c_str() );
			continue;
		}
		tcstr szAddr = peTarget->GetAttr(jS(IP));
		jIP_Address ip = nNET::jSOCKADDR_IN::String2Addr(szAddr);
		g_pCurrPlugIn->Write_Packet(ip,WRITE_H_HELLO(send_buf,peTarget->GetTagName(),Get_Uniq_AppNicName(),false));

		// Orb server의 레지스트리에 나의 ip와 port를 등록해둔다.
		tname256_t szRegPath;
		jt_sprintf(szRegPath, _T("SOFTWARE\\jGame\\ORB\\Ver01\\%s"), m_UsingService[i].c_str());
		nFunctor::jIE_AutoPtr pE;
#ifndef UNICODE 
		pE->ChangeTagName(jS(address_list_ansi123));
		GetjIXml()->GetXmlUtil()->LoadFromRegistry(pE,szRegPath,jS(address_list_ansi123));
		nXML::jE e = (jIE*)pE;
		e[Get_Uniq_AppNicName()].T() = szMyIP;
		GetjIXml()->GetXmlUtil()->SaveToRegistry(pE,szRegPath,jS(address_list_ansi123));
#else
		pE->ChangeTagName(jS(address_list_unicode123));
		GetjIXml()->GetXmlUtil()->LoadFromRegistry(pE,szRegPath,jS(address_list_unicode123));
		nXML::jE e = (jIE*)pE;
		e[Get_Uniq_AppNicName()].T() = szMyIP;
		GetjIXml()->GetXmlUtil()->SaveToRegistry(pE,szRegPath,jS(address_list_unicode123));
#endif
	}

	//--------------------------------------------------------------------------
	// 실행중인 클라이언트에 접속
	//--------------------------------------------------------------------------
	if(!isMyService) return;

	tname256_t szRegPath;
	jt_sprintf(szRegPath, _T("SOFTWARE\\jGame\\ORB\\Ver01\\%s"), szMyServiceName);

	nFunctor::jIE_AutoPtr pE;
#ifndef UNICODE
	pE->ChangeTagName(jS(address_list_ansi123));
	bool is = GetjIXml()->GetXmlUtil()->LoadFromRegistry(pE,szRegPath, jS(address_list_ansi123));
#else
	pE->ChangeTagName(jS(address_list_unicode123));
	bool is = GetjIXml()->GetXmlUtil()->LoadFromRegistry(pE,szRegPath, jS(address_list_unicode123));
#endif
	if(!is || !pE->size()) return;

	jIE* it = pE->begin();
	pE->DebugPrint(true);
	jrFOR(it)
	{
		if(!jt_strlen(it->Get_cstr())) 
			continue;
		jIP_Address ip = nNET::jSOCKADDR_IN::String2Addr(it->Get_cstr());
		g_pCurrPlugIn->Write_Packet(ip,WRITE_H_HELLO(send_buf,szMyServiceName,Get_Uniq_AppNicName(),true));
	}
}

jOrbNode* jOrb::OrbNode_push_back(jIPacketSocket_IOCP* pS, jIP_Address& ip 
								  , tcstr orbServiceName,tcstr szRemoteName,bool isRemoteServerMode
								  )
{
	jAUTO_LOCK_CS_m_jOr32bNode_CS_;

	jOrbNode* pOrb= findByIP(ip);
	if(!pOrb)
	{
		pOrb = m_jOrbNode.push_back();
	}
	pOrb->Init(pS,ip);
	pOrb->m_isRemoteServerMode= isRemoteServerMode;// 원격지가 orb server이다.
	pOrb->m_sName = szRemoteName;

	pOrb->m_peOrbService= m_docOrbConfig(jS(ORB_APP_LIST))->FindByDepth(1, orbServiceName );
	if(!pOrb->m_peOrbService)
	{
		jWARN(_T("m_peOrbService orbMyName is not found in ORB_APP_LIST: %s"),orbServiceName);
		return 0;
	}
	tcstr szXml = pOrb->m_peOrbService->GetAttr(jS(PROTOCAL));
	jASSERT0(szXml);
	pOrb->m_pDocProtocal = GetjIXml()->Load( szXml );
	if(!pOrb->m_pDocProtocal)
	{
		jWARN(_T("file not found : %s"),szXml );
		return 0;
	}

#define jLAMDA_Init_protocal_handler(X,Z) Z(jOrbNode&,orb)
	jLAMDA_for_each(Init_protocal_handler,jIE*)
	{
		tname256_t szName;
		jt_sprintf(szName, _T("ORB_HANDLER_%s"),orb.GetService()->GetTagName());
		jIORB_protocal_handler_t* pAO = (jIORB_protocal_handler_t*)jBase::FindNamedPointer(szName,it->GetTagName());
		if(!pAO)
		{
			jWARN(jFUNC _T("ORB_HANDLER not found : %s::%s") ,orb.GetService()->GetTagName(), it->GetTagName() );
			return;
		}
		it->SetUserData(jS(ORB_HANDLER), pAO);
		jLOG(_T("ORB_HANDLER regist success: %s::%s"),orb.GetService()->GetTagName(), it->GetTagName() );
	}
	jLAMDA_end();

	jIE* it = pOrb->m_pDocProtocal->BaseI()->begin();
	jrFOR(it)// ToServer , ToClient , Common에 대해서 실행
	{
		if(it->IsName(jS(ToServer)) && pOrb->m_isRemoteServerMode)continue;
		if(it->IsName(jS(ToClient)) && !pOrb->m_isRemoteServerMode)continue;
		it->for_each_child(Init_protocal_handler(*pOrb));
	}

	return pOrb;
}

jIOrbNode* jOrb::FindByServiceName(tcstr szID)
{
	jAUTO_LOCK_CS_m_jOr32bNode_CS_;
	m_jOrbNode_it it = m_jOrbNode.begin(), ie = m_jOrbNode.end();
	for( ; it!=ie ; ++it)
	{
		if( it->m_peOrbService->IsName(szID)) 
			return it;
	}
	jWARN(_T(" not found : %s"),szID);
	return 0;
}
jIOrbNode* jOrb::FindByRemoteName(tcstr szID)
{
	jAUTO_LOCK_CS_m_jOr32bNode_CS_;
	m_jOrbNode_it it = m_jOrbNode.begin(), ie = m_jOrbNode.end();
	for( ; it!=ie ; ++it)
	{
		if( it->m_sName == szID)
			return it;
	}
	jWARN(_T(" not found : %s"),szID);
	return 0;
}

jOrbNode* jOrb::findByIP(jIP_Address& ip)
{
	jAUTO_LOCK_CS_m_jOr32bNode_CS_;
	m_jOrbNode_it it = m_jOrbNode.begin(), ie = m_jOrbNode.end();
	for( ; it!=ie ; ++it)
	{
		if( it->m_uid== ip) 
			return it;
	}
	return 0;
}
void JOB_jIOrb_system_callback(nEVENT::jIMessage* pM)
{
	g_jOrb.m_jIOrb_system_callback( 
		(nORB::EOrbSystemCallbackType)pM->GetArg(0)->Get_int()
		, (jIOrbNode*)pM->GetArg(1)->GetUserData() 
		, pM->GetArg(2)->Get_cstr() );

}

void jOrb::Call_jIOrb_system_callback(nORB::EOrbSystemCallbackType type,jIOrbNode* pON,tcstr name)
{
	nEVENT::jIMessage* pM = m_pMM->Regist_Loop(0,jFUNC_Msg(JOB_jIOrb_system_callback),3);
	pM->GetArg(0)->InitValue((int)type);
	pM->GetArg(1)->SetUserData(pON);
	pM->GetArg(2)->InitValue(name);
	pM->DoWakeUp();
}

void jOrb::OrbNode_for_each(OrbNode_for_each_ft* f,void*v)
{
	jAUTO_LOCK_CS_m_jOr32bNode_CS_;
	m_jOrbNode_it it = m_jOrbNode.begin(), ie = m_jOrbNode.end();
	for(;it!=ie;++it)
	{
		f(it,v);		
	}

}
void jOrb::SetLocalWnd(HWND hWnd)
{
	if(m_hWnd==hWnd) return;
	m_hWnd= hWnd;
	S_H_NOTIFY_HWND pk;
	pk.hWnd = (uint32)hWnd;
	nswb1024_t buf;
	jAUTO_LOCK_CS_m_jOr32bNode_CS_;
	for( m_jOrbNode_it it = m_jOrbNode.begin() ; it ; ++it)
	{
		it->Write_Packet(WRITE_H_NOTIFY_HWND(buf, pk) );
	}
}

void jOrb::DisconnectAll()
{
	nswb256_t buf;
	jPacket_Base pk = WRITE_H_DISCONNECT(buf);
	jAUTO_LOCK_CS_m_jOr32bNode_CS_;
	for( m_jOrbNode_it it = m_jOrbNode.begin() ; it ; ++it)
	{
		it->Write_Packet(pk);
	}

}

bool jOrb::RunTool(tcstr szOrbName)
{
	jIOrbNode* pOrb = GetOrb_service(szOrbName);
	if(pOrb) 
	{
		pOrb->ShowTool();
		return true;
	}
	jIE* pE = m_docOrbConfig(jS(ORB_APP_LIST))(szOrbName);
	cstr szExe = pE->GetAttr(_T("EXE"));
	if(!szExe) return false;

	nFileSystem::jFolder dm;
	dm.Goto(g_ExeEnv.m_szModuleDir);
	nUtil::nWIN::jCreateProcess(const_cast<TCHAR*>(szExe),true);
	return true;
}
