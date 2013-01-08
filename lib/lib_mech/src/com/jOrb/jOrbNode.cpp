/* file : jOrbNode.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-10-29 19:02:34
comp.: pantavision.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jOrbNode.h"
#include "header/jMemoryChunk.h"

jDEFINE_YVECTOR_MANAGER(jOrbNode,10,2);

bool jOrbNode::IsRemoteServerMode() { return m_isRemoteServerMode;}
tcstr jOrbNode::GetRemoteAppName(){ return m_sName.c_str();}
jID* jOrbNode::GetProtocalDoc(){ return m_pDocProtocal;}
jIE* jOrbNode::GetService(){ return m_peOrbService;}

bool jOrbNode::IsRemoteOk()
{
	fname_t szBuf;
	int i =GetWindowText(GetRemoteWnd(), szBuf , sizeof(szBuf));
	if(i)
		return true;

	nswb256_t buf;
	m_IsAlive.Reset();
	Write_Packet(WRITE_ORB_IS_ALIVE(buf));
	return m_IsAlive.Wait(5000);
}

/*
void jOrbNode::Send(tcstr name,nUtil:: jMemoryChunk& mc)
{
	nswb16000_t buf;
	std::vector<BYTE> v;
	v.resize(mc.size());
	memcpy(&v[0] , mc.GetBuffer(),mc.size());
	Write_Packet(WRITE_ORB_SEND_DATA(buf, name,v));
}
*/
void jOrbNode::Send(jIE* peProtocal)
{
	S_ORB_SEND_XML pk;
	pk.xml = peProtocal;
	nswb16000_t buf;
	Write_Packet(WRITE_ORB_SEND_XML(buf, pk));
}

void jOrbNode::Init(jIPacketSocket_IOCP* pS, jIP_Address& ip)
{
	m_IsAlive.Init();
	m_pS = pS;
	m_uid = ip;
}

//---------------------------------------------------------------
jIE* jOrbNode::FindProtocal(cstr szName)
//----------------------------------------------------------------
{
	return m_pDocProtocal->BaseI()->FindByDepth(2, szName);
}

void jOrbNode::LocalCall(jIE* pE)
{
	_localCall(pE->GetTagName(),pE);

}


//---------------------------------------------------------------
// 임의의 xml데이타인 pE(자식포함)를 원격지에 보낸다.
// pePROTOCAL가 있으면 해당 orb함수가 호출된다.
// pE의 xpath에 해당하는 원격지의 노드가 없으면 pE의 데이타를 추가시킨다.
void jOrbNode::Send_H_COPY_XML_ELEMENT(jIE* pE,cstr szPROTOCAL,bool isInsertMode)
//----------------------------------------------------------------
{
	fname_t szDoc;
	TCHAR szXPath[1024];
	jID* pD = 	pE->GetParent()->XPathToString(szXPath , 0);
	pD->GetURL(szDoc);
	nswb16000_t buf;
	char idx = pE->GetOrder();
	S_H_COPY_XML_ELEMENT pk;
	pk.set_szDoc(szDoc);
	pk.set_szOrbFunc(  (szPROTOCAL && jt_strlen(szPROTOCAL)) ? szPROTOCAL : _T("NULL" ));
	pk.set_szXPath(szXPath);
	pk.isInsertMode = isInsertMode;
	pk.idx = idx;
	pk.xml = pE;
	Write_Packet(WRITE_H_COPY_XML_ELEMENT(buf,pk));
}

//---------------------------------------------------------------
// 원격지에 해당하는 pE를 찾아 삭제시킴
// pePROTOCAL가 있으면 해당 orb함수가 호출된다.
void jOrbNode::Send_XMLDel(jIE* pE,jIA* pA, cstr szPROTOCAL)
//----------------------------------------------------------------
{
	fname_t szDoc;
	TCHAR szXPath[1024];
	jID* pD = 	pE->XPathToString(szXPath , pA);
	pD->GetURL(szDoc);
	nswb2048_t buf;
	Write_Packet(WRITE_H_DEL_XML_ELEMENT(buf, szDoc,szXPath,(szPROTOCAL&&jt_strlen(szPROTOCAL))? jA(szPROTOCAL): "NULL" ));
}


// 원격지로 doc을 save하는 명령을 날린다.
void jOrbNode::SendSaveDoc(jID* pD)
{
	fname_t buf1;
	cstr szSaveDoc;
	pD->GetURL(buf1);
	TCHAR* ch = jt_strchr(buf1,'=');
	if(ch)
	{
		szSaveDoc = ++ch;
	}
	else
	{
		szSaveDoc  = buf1;
	}

	if(!IsRemoteOk())
	{
		jLOG(_T("%s saved by local") ,szSaveDoc );
		pD->Save();
		return;
	}
	nswb1024_t buf;
	Write_Packet(WRITE_H_SAVE_DOC(buf,szSaveDoc));
	jLOG(_T("Called to orb target to saving  %s ") ,szSaveDoc );
}

/* *_* by icandoit : 2005-08-19 14:45:36
//---------------------------------------------------------------
HWND hXmlWnd = g_orbToObjTool->GetRemoteWnd();
if(hXmlWnd )
{
if(!g_pvAdjustPosition ||g_pvAdjustPosition->intValue())
mech::jMoveWindowTo(hXmlWnd , m_hWnd );
}

*/ //*_* by icandoit : 2005-08-19 14:45:40

bool jOrbNode::ShowTool()
{
	HWND hWnd = GetRemoteWnd();
	if(!hWnd)	
	{
		return false;
	}

	if( IsWindowVisible(hWnd) )
	{
		::ShowWindow(GetRemoteWnd() ,SW_HIDE );
		BringWindowToTop(GetLocalWnd());
		::ShowWindow( GetLocalWnd() ,SW_SHOWNORMAL );
	}
	else 
	{
		BringWindowToTop(GetRemoteWnd());
		::ShowWindow(GetRemoteWnd(), SW_SHOWNORMAL);
	}
	return true;
}

void jOrbNode::_localCall(tcstr szOrbFunc, jIE* peData)
{
	if(!jt_strlen(szOrbFunc) || !jt_strcmp(szOrbFunc,jS(NULL) )) return;
	nXML::jE e = m_pDocProtocal->BaseI()->FindByDepth(2,szOrbFunc);
	jIORB_protocal_handler_t* pAO =0;
	if(e.full())
	{
		pAO = (jIORB_protocal_handler_t*)e->GetUserData(jS(ORB_HANDLER));
	}
	if(!pAO )
	{
		tname256_t szName;
		jt_sprintf(szName, _T("ORB_HANDLER_%s"),GetService()->GetTagName());
		pAO = (jIORB_protocal_handler_t*)jBase::FindNamedPointer(szName,szOrbFunc);
		if(!pAO)
		{
			g_jOrb.m_jIOrb_system_callback(nORB::eUNHANDLED_PACKET, this,szOrbFunc);
			return;
		}
		else
		{
			if(e.full())
				e->SetUserData(jS(ORB_HANDLER),pAO);
		}
	}
	pAO(this,peData);
}


//---------------------------------------------------------------
// pE의 tagname 이나 컨텐츠또는 pA의 컨텐츠 수정사항만 적용함 (자식의 내용은 적용안함)
//CHANGE_XMLNODE가 있으면 호출됨
void jOrbNode::Notify_H_CHANGE_XML_NODE(jIE* pE, jIA* pA )
{
	fname_t szDoc;
	TCHAR szXPath[1024];
	jID* pD = 	pE->GetParent()->XPathToString(szXPath, 0);
	pD->GetURL(szDoc);

	TCHAR* szDoc1 = jt_strchr(szDoc,'=');
	if(szDoc1)
	{
		++szDoc1;
	}
	else
	{
		szDoc1 = szDoc;
	}

	char idx = pE->GetOrder();

	jIVar* pvSend;
	fname_t szTag;
	if(pA)
	{
		pvSend=  pA->GetVar();
		jt_strcpy(szTag, pA->GetTagName());
	}
	else
	{
		pvSend = pE->GetVar();
		jt_strcpy(szTag ,pE->GetTagName());
	}

	int iType = pvSend->GetType();
	fname_t szVar;
	if(iType!=jIVar::ETelement)
	{
		pvSend->ToString(szVar);
	}
	else
	{
		szVar[0]=0;
	}
	nswb2048_t buf;
	Write_Packet(WRITE_H_CHANGE_XML_NODE(buf,szDoc1,szXPath,idx ,pA,szTag,iType,szVar));
}


void jOrbNode::Notify_H_GET_UPDATE_XML_NODE(jIE* pE, jIA* pA )
{
	fname_t szDoc;
	TCHAR szXPath[1024];
	jID* pD = 	pE->GetParent()->XPathToString(szXPath, 0);
	pD->GetURL(szDoc);
	TCHAR* szDoc1 = jt_strchr(szDoc,'=');
	if(szDoc1)	{		++szDoc1;	}	else	{		szDoc1 = szDoc;	}

	char idx = pE->GetOrder();
	fname_t szTag;
	if(pA)
	{
		jt_strcpy(szTag, pA->GetTagName());
	}
	else
	{
		jt_strcpy(szTag ,pE->GetTagName());
	}
	nswb2048_t buf;
	Write_Packet(WRITE_H_GET_UPDATE_XML_NODE(buf,szDoc1,szXPath,idx ,pA,szTag));
}

void jOrbNode::SetNotifyEvent(cstr id,Notify_callback_cr_t event )
{
	m_mapXmlDownEvent[id] = event;
}

void jOrbNode::call_XmlEvent(cstr name,jID* pD)
{
	m_mapXmlDownEvent_it it = m_mapXmlDownEvent.find(name);
	if(it!=m_mapXmlDownEvent.end())
	{
		it->second(this , pD , tstring(name));
	}
}

HWND jOrbNode::GetRemoteWnd()
{
	return m_hWndTarget;

}

HWND jOrbNode::GetLocalWnd()
{
	return g_jOrb.m_hWnd;
}



void jOrbNode::Notify_DownloadXml(cstr szXml,Notify_callback_cr_t event)
{
	SetNotifyEvent(szXml, event );
	nswb1024_t buf;
	Write_Packet(WRITE_H_GET_XML(buf, szXml));
}

void jOrbNode::Send_H_SEND_LOG(tcstr szMsg,uint8 type)
{
	nswb2048_t buf;
	Write_Packet(WRITE_H_SEND_LOG(buf, type,szMsg));
}