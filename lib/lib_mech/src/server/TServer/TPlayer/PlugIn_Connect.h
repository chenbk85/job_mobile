/* file : PlugIn_Connect.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 10:51:11
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __PlugIn_Connect_header__
#define __PlugIn_Connect_header__
#pragma once



class PlugIn_Connect : public jIPlugIn_Net_SQ<PlugIn_Connect,jPlugIn_ConnnectBase > 
{
public:
	jPLUGIN_HEADER_CODE_Connect(PlugIn_Connect);
	virtual tcstr GetPlugInNicName(){ return _T("PlugIn_TPlayer");}

};

DECLARE_INSTANCE_TYPE(PlugIn_Connect);


// Data , pPC , buf, pPlayer
#define aq_READ_PACKET_P2P_PB(PACKET) jPC();nswb1024_t buf;jPlayerObj* pPlayer = ToPlayerObj(pS);jRETURN(pPlayer)\
	READ_PACKET(PACKET);

#define _aq_READ_PACKET_P2P_PB_Data(PACKET,Data)	nswb1024_t buf;\
	PlugIn_Connect*pPC = (PlugIn_Connect*)pPlugIn;\
	jPlayerObj* pPlayer = ToPlayerObj(pS);jRETURN(pPlayer);\
	READ_PACKET_Data(PACKET,Data);

#define aq_READ_PACKET_P2P_PB_Data(PACKET) _aq_READ_PACKET_P2P_PB_Data(PACKET,pPlayer->m_##PACKET)

// xml은 패킷중의 jIE*에 해당하는 변수명.
#define aq_READ_PACKET_P2P_PB_xml(PACKET,xml) S_##PACKET Data; Data.xml=GetjIXml()->CreateElement(); _aq_READ_PACKET_P2P_PB_Data(PACKET,Data)



#endif // __PlugIn_Connect_header__
