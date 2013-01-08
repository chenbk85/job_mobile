/* file : PlugIn_ToFrontEnd.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:42
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"

/*
void jMsg_job(nEVENT::jIMessage* pM)
{
	pM->GetArg(0)->Get_int();
	pM->GetArg(1)->Get_cstr();
	pM->GetArg(2)->Get_float();
}
*/

jPLUGIN_FRONT_END_cpp_code_Start(PlugIn_ToFrontEnd,AqClientUser_T)
{
	m_pMM->Regist_TimeBase(0 , jMsg_C4_USER_CONNECTION_NOTIFY, 0,pv_C4_USER_CONNECTION_NOTIFY->Get_float())->DoWakeUp();
	m_eWorldInfo = GetjIXml()->CreateElement();
	m_eWorldInfo.SetType(jIVar::ETelement);
	m_eWorldInfo->ChangeTagName(jS(WorldCache));

	/*  Regist_TimeBase(int iOrder , MsgFunc_t* pFunc, int iArgCount , float fTriggerTime) -- 타이머(등록된 시간 후에 함수 실행)
	iOrder : order 주로 0으로 셋팅 (사용안함)
	pFunc : 메세지 처리 함수
	iArgCount : 인자 수
	fTriggerTime: timer 
	nEVENT::jIMessage* pM=m_pMM->Regist_TimeBase(0 , jMsg_job, 3, 5.0f);
	pM->GetArg(0)->InitValue(23);
	pM->GetArg(1)->InitValue(_T(jS(asdf)));
	pM->GetArg(1)->InitValue(3.f);
	pM->DoWakeUp();
	*/
}
jPLUGIN_cpp_code_Stop(PlugIn_ToFrontEnd)
{
	GetjIXml()->DeleteElement(m_eWorldInfo);
	m_mapCastleInfo_it it = m_mapCastleInfo.begin(),ie=m_mapCastleInfo.end();
	for(;it!=ie;++it)
	{
		GetjIXml()->DeleteElement(it->second);
	}


}
jPLUGIN_FRONT_END_cpp_code_End(PlugIn_ToFrontEnd,AqClientUser_T);

PlugIn_ToFrontEnd::PlugIn_ToFrontEnd()
{
}

bool PlugIn_ToFrontEnd::ParseCmd(tcstr szCommand)
{
	//nswb1024_t buf;
	std::tstring str = _T("FromAqCentral:");
	str += szCommand;
	net_string256 sendStr = str.c_str();
	//jPacket_Base pk = nTestCentralServer::WRITE_TS_ECHO(buf, sendStr );
	//jIPacketSocket_IOCP* p =0;
	//send_all(&pk, p );	
	return false;
}

void jSocketDebugger(jIPacketSocket_IOCP* pS)
{

}

// CIocp의 가상함수들
VOID PlugIn_ToFrontEnd::OnIoConnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoConnected_fromClient(T);
}


VOID PlugIn_ToFrontEnd::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoDisconnected_fromClient(T);

	erase(pUser);
}


jE PlugIn_ToFrontEnd::Get_CastleInfo(Sys_Castle_id_t csid)
{ 
	m_mapCastleInfo_it it = m_mapCastleInfo.find(csid);
	if(it==m_mapCastleInfo.end())
	{
		jIE* pE = GetjIXml()->CreateElement();
		fname_t sz;
		jt_sprintf(sz ,jS(Castle) _T("_%d") , csid);
		pE->ChangeTagName(sz);
		pE->GetVar()->SetType(jIVar::ETelement);
		m_mapCastleInfo[csid] = pE;
		return pE;
	}
	return it->second;
}
