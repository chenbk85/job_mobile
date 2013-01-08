/* file : jConnectUser.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-03-10 12:50:12
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __jConnectUser_header__
#define __jConnectUser_header__
#pragma once


namespace nMech
{
	namespace nNET
	{
		template<typename KEY_TYPE=jIPacketSocket_IOCP*,typename KEY_TYPE_ID_t = uint64>
		struct jConnectUser
		{
			typedef KEY_TYPE_ID_t KEY_TYPE_id_t;
			KEY_TYPE m_pS;
			KEY_TYPE_id_t m_uid;
			std::tstring m_sName;
			tname32_t m_szIP;

			virtual KEY_TYPE_id_t Get_uid(){ return m_uid;}
			virtual KEY_TYPE_id_t GetUID(){ return m_uid; }
			virtual cstr GetUserName(){return m_sName.c_str(); }
			virtual void Write_Packet(jPacket_Base& pk) =0;
		};
	}
}



#endif // __jConnectUser_header__
