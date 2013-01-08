/* file : define_code_BackEndServer.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-09-16 14:25:27
comp.: wiki.aqrius.com
title : 
desc : 

// 프론트엔드와 백엔드서버 모두 include해야함.


*/

#ifndef __jNET_define_code_header9182jioejrfdiotj39844r__
#define __jNET_define_code_header9182jioejrfdiotj39844r__
#pragma once


#define jPC()			PlugIn_Connect*pPC = PlugIn_Connect::Get();	jRETURN(pPC);
#define jPC_ret(ret)	PlugIn_Connect*pPC = PlugIn_Connect::Get();	jRETURN_ret(ret,pPC);
#define jPC_A()			PlugIn_Connect*pPC = PlugIn_Connect::Get();	if(!pPC) {jERROR("pPC==NULL");}

#define jPS()			PlugIn_Server*pPS = PlugIn_Server::Get();	jRETURN(pPS);
#define jPS_ret(ret)	PlugIn_Server*pPS = PlugIn_Server::Get();	jRETURN_ret(ret,pPS);
#define jPS_A()			PlugIn_Server*pPS = PlugIn_Server::Get();	if(!pPS) {jERROR("pPS==NULL"};}


#define READ_PACKET_PS(X)				jPS();	READ_PACKET(X);
#define READ_PACKET_PS_B(X)				jPS();	READ_PACKET(X);										nswb1024_t buf;
#define READ_PACKET_PS_S(X)				jPS();	READ_PACKET(X);				jSI(pS->GetGridNode());
#define READ_PACKET_PS_BS(X)			jPS();	READ_PACKET(X);				jSI(pS->GetGridNode());	nswb1024_t buf;
#define READ_PACKET_PS_Data_S(X,Data)	jPS();	READ_PACKET_Data(X,Data);	jSI(pS->GetGridNode());
#define READ_PACKET_PS_Data_BS(X,Data)	jPS();	READ_PACKET_Data(X,Data);	jSI(pS->GetGridNode());	nswb1024_t buf;
#define READ_PACKET_PS_XML_BS(X,xml)	S_##X Data;Data.xml = GetjIXml()->CreateElement(); READ_PACKET_PS_Data_BS(X); 
// 주의! READ_PACKET_PS_XML =>  xml은 CreateElement()된 것이므로 필요없을땐 DeleteElement()해야한다.

#define READ_PACKET_PC(X)				jPC(); READ_PACKET(X);
#define READ_PACKET_PC_B(X)				jPC(); READ_PACKET(X);									nswb1024_t buf;buf;
#define READ_PACKET_PC_S(X)				jPC(); READ_PACKET(X);			jSI(pS->GetGridNode());
#define READ_PACKET_PC_BS(X)			jPC(); READ_PACKET(X);			jSI(pS->GetGridNode());	nswb1024_t buf;buf; 
#define READ_PACKET_PC_Data_S(X,Data)	jPC(); READ_PACKET_Data(X,Data);jSI(pS->GetGridNode());
#define READ_PACKET_PC_Data_BS(X,Data)	jPC(); READ_PACKET_Data(X,Data);jSI(pS->GetGridNode()); nswb1024_t buf; 
#define READ_PACKET_PC_XML_BS(X,xml)	S_##X Data;Data.xml=GetjIXml()->CreateElement();	READ_PACKET_PC_Data_BS(X,Data);
// 주의! READ_PACKET_PC_XML_BS =>  xml은 CreateElement()된 것이므로 필요없을땐 DeleteElement()해야한다.




#define jPT_MEMBER(NS,X) NS::S_##X m_##X;



// jIGridNode* pGN, szIP,nswb256_t buf
#define jFE_OnIoConnected_fromServer(PACKET)\
	nswb256_t buf;\
	fname_t szIP;\
	jRETURN(pS);\
	jIGridNode* pGN = pS->GetGridNode();\
	jRETURN(pGN);\
	jLOG1(jFUNC1 _T("%s , GRID=%s"), pS->GetAddressString(szIP), nNET::GridName(pGN) );\
	pS->WritePacket(&WRITE_##PACKET(buf,g_SG.m_MyInfo) );\
	pS->SetDebugger(jSocketDebugger);\
	++g_SG.m_MyInfo.m_iTotClient;\



//jIGridNode* pGN ,jServerInfo* si
#define jFE_OnIoDisconnected_fromServer()\
	if(!pS) return;\
	--g_SG.m_MyInfo.m_iTotClient;\
	jIGridNode* pGN = pS->GetGridNode();\
	jRETURN(pGN);\
	jSI(pGN);\
	jLOG1(jFUNC1 _T("%s"), nNET::GridName(pGN));\


// Central과 command외의 모든서버에서 SS2 ?? _ONLINE이 날라왔을때 처리하는 루틴
#define jRecv_SS2server_ONLINE(SERVER_TAG)\
	READ_PACKET_PS_BS(_jJOIN_3(SS2,SERVER_TAG,_ONLINE));\
	if( Data.your_sid != g_SG.m_MyInfo.m_sid)\
	{\
		jERROR("Data.your_sid(%d) != g_SG.m_MyInfo.m_sid(%d)",Data.your_sid, g_SG.m_MyInfo.m_sid);\
		pPS->DoDisconnect(pS);	return;\
	}\
	*si = Data.my;\
	jAssert0(g_SG.m_MyInfo.m_eType!=eCentral && g_SG.m_MyInfo.m_eType!=eCommand);\
	/* central이나 command쪽에서 sid를 발급받는중이므로 다시 정보요청.*/\
	if(g_SG.m_Central.size() || g_SG.m_Command.size())\
	{	if(si->m_sid==0) {pS->WritePacket(&_jJOIN_3(WRITE_,SERVER_TAG,_SERVERINFO_ACK)(buf,g_SG.m_MyInfo));}	}\


// CENTRAL을 제외한 PlugIn_Server::ParseCmd()에서 사용.
#define jPS_COMMON_ParseCmd(SERVER_TAG)\
	{\
		std::tstring str = _T("From(") jS(SERVER_TAG) _T("):"); str += szCommand;\
		if(tstring(jS(PS))==g_SG.GetParserType())\
		{\
			nswb1024_t buf;\
			g_SG.WritePacket(_jJOIN_3(WRITE_,SERVER_TAG,_ECHO)(buf, str.c_str(),0), 0, nNET::eACCEPTED_SOCKET);\
			return false;\
		}\
		g_SG.ParseCmd(str.c_str());\
	}\
	return false;\


#endif // __jNET_define_code_header9182jioejrfdiotj39844r__
