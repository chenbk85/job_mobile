/* file : PlugIn_ToBackEnd.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 10:51:11
comp.: wiki.test.com
title : 
desc : 

*/

#ifndef __PlugIn_ToBackEnd_header__
#define __PlugIn_ToBackEnd_header__
#pragma once

struct jUser
{
	aname32_t m_szPWD;
	aname32_t m_szID;
	jIE* m_pE;
	jIPacketSocket_IOCP* m_pS;
};


inline tcstr MakeSessionName(tcstr id,OUT tfname_t buf)
{
	jt_sprintf(buf, _T("TCP_TestServer_%s") , id);
	return buf;
}

class PlugIn_ToBackEnd : public jIPlugIn_Net_SQ<PlugIn_ToBackEnd,jIPlugIn_Connection > 
{
public:
	jPLUGIN_header_code(PlugIn_ToBackEnd)
	virtual int Get_CURR_USER(){return 0;};

	virtual tcstr GetPlugInNicName()
	{ 
		return _T("PlugIn_TestClient");
	}

	jIPacketSocket_IOCP* m_pS_TestServer;

	jIE* FindUser(tcstr szID)
	{
		tfname_t buf;
		return m_pE->Find(MakeSessionName(szID, buf));
	}
	jUser* GetUser(jIE* pE)
	{
		jAUTO_LOCK_CS(m_Users_CS);
		m_Users_it it = m_Users.find(pE);
		if(it ==m_Users.end()) return 0;
		return &it->second;
	}

	jLIST_TYPEDEF_map(jIE* , jUser,m_Users);
	nUtil::jCriticalSection m_Users_CS;

};

DECLARE_INSTANCE_TYPE(PlugIn_ToBackEnd);

extern PlugIn_ToBackEnd* g_pCurrPlugIn;


#endif // __PlugIn_ToBackEnd_header__
