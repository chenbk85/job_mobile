/* file : TServerClient_CommonHeader_End.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-09-17 16:57:46
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __AqServerClient_CommonHeader_End_header__
#define __AqServerClient_CommonHeader_End_header__
#pragma once


struct jHeroItem
{
	itemid_t m_iid;// 1���� ����. 0�� ������ ������ ��Ÿ����.
};

struct jHeroSkill
{
	skillid_t m_skid;// 1���� ����. 0�� ������ ������ ��Ÿ����.
};
namespace nMech
{
	inline void jDebugPrint(tcstr szName, jHeroItem& msg){}
	inline void jDebugPrint(tcstr szName, vector<jHeroItem>& msg)	{		jLOG1(_T("%s.size()=%d") , szName,msg.size());	}
	inline void jDebugPrint(tcstr szName, jHeroSkill& msg){}
	inline void jDebugPrint(tcstr szName, vector<jHeroSkill>& msg)	{		jLOG1(_T("%s.size()=%d") , szName,msg.size());	}

};
DECLARE_INSTANCE_TYPE(jHeroItem);
DECLARE_INSTANCE_TYPE(jHeroSkill);

#endif // __AqServerClient_CommonHeader_End_header__
