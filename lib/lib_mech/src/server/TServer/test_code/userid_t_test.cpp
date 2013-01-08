/* file : userid_t_test.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-09-10 15:50:07
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include <map>


struct player_id_t
{
	union
	{
		struct 
		{
			union
			{
				struct  
				{
					unsigned int m_w_handle: 26;//WorldServer yVectorNode handle
					unsigned int m_statCookie:1;//½ºÅÝÁ¤º¸°¡ ¹Ù²»À»¶§ °ªÀÌ ¹Ù³¦.
					unsigned int m_visualCookie: 1;// ºñÁê¾óÀÌ ¹Ù²¼À»¶§ °ªÀÌ ¹Ù³¦.
				};
				unsigned int m_wid32;//world handle
			};
			union
			{
				struct 
				{
					unsigned short m_dc_handle;//dbcache shared memory handle
					unsigned short	  m_dc_sid;//dbcache server id
				};
				unsigned int m_did;
			};
		};
		__int64 m_id;
	};
	player_id_t(int a, int b, int c){m_w_handle=a;m_dc_handle=b;m_dc_sid=c;}
	bool operator ==(const player_id_t& uid)const {return (m_w_handle==uid.m_w_handle) && (m_did==uid.m_did);}
	bool operator <(const player_id_t& uid)const {return (m_w_handle<uid.m_w_handle) && (m_did<uid.m_did);}
	struct less
	{
		bool operator()( const player_id_t& uid1, const player_id_t& uid2) const
		{
			return (uid1.m_w_handle<uid2.m_w_handle) && (uid1.m_did<uid2.m_did);
		}
	};

};

void test_userid()
{
	typedef std::map<player_id_t,bool> userid_map_t;
}