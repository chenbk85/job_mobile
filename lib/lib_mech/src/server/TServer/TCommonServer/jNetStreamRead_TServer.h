/* file : Aq_Stream.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2009-12-17 08:53:13
comp.: t3.co.kr
title : 
desc : 


서버간에 공유되는 사용자 패킷 패킹/언패킹 구조체들.

참고 :jNetStreamRead_TClient.h

*/

#ifndef __Aq_Stream_header_jNetStreamRead_TServer1234
#define __Aq_Stream_header_jNetStreamRead_TServer1234
#pragma once

#include "header/nNET_Stream.h"

namespace nMech
{
	namespace nNET
	{
		namespace nStream
		{
			inline void Read(jNetStreamRead& st, jServerInfo& data)
			{
				Read(st,data.m_PacketAmount);
				Read(st,data.m_eType);
				aname32_t buf;
				Read(st,buf,32);
				jt_strcpy_s(data.m_szName, jT(buf));
				Read(st,data.m_StartTime);
				Read(st,buf,32);
				jt_strcpy_s(data.m_szDomain, jT(buf));
				Read(st,buf,32);
				jt_strcpy_s(data.m_szIP, jT(buf));
				Read(st,buf,32);
				jt_strcpy_s(data.m_szServiceIP, jT(buf));
				Read(st,data.m_sid);
				Read(st,data.m_service_port);
				Read(st,data.m_service_udp_port);
				Read(st,data.m_iMaxClient);
				Read(st,data.m_iTotClient);
			}
			inline void Write(jNetStreamWrite& st,const jServerInfo& data)
			{
				Write(st,data.m_PacketAmount);
				Write(st,data.m_eType);
				Write(st,(acstr)jA(data.m_szName));
				Write(st,data.m_StartTime);
				Write(st,(acstr)jA(data.m_szDomain));
				Write(st,(acstr)jA(data.m_szIP));
				Write(st,(acstr)jA(data.m_szServiceIP));
				Write(st,data.m_sid);
				Write(st,data.m_service_port);
				Write(st,data.m_service_udp_port);
				Write(st,data.m_iMaxClient);
				Write(st,data.m_iTotClient);
			}
		}//namespace nStream
	}//namespace nNET

}//namespace nMech


#endif // __Aq_Stream_header_jNetStreamRead_TServer1234
