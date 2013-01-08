/* file : jServerGrid_functor.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-29 00:18:23
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jServerGrid_functor_header__
#define __jServerGrid_functor_header__
#pragma once



#define jLAMDA_find_by_name(X,Z) Z(tcstr,szName)
jLAMDA_find_if(find_by_name,jIGridNode*)
{
	jSI_ret(it,false);
	return jt_strcmp(si->m_szName,szName)==0;
}
jLAMDA_end();



//--------------------------------------------------------------------------
//펑터 : 유저를 받을수 있는 서버들을 수집.
//--------------------------------------------------------------------------
typedef std::vector<std::pair<serverid_t,int16>> collect_sid_tot_t;
inline bool server_tot_sort( collect_sid_tot_t::value_type&a, collect_sid_tot_t::value_type& b){return (a.second> b.second);}

#define jLAMDA_collect_free_server(X,Z) Z(collect_sid_tot_t&,servers)
jLAMDA_for_each(collect_free_server,jIGridNode*)
{
	jSI(it);
	if(si->m_iTotClient >= si->m_iMaxClient) return ;
	servers.push_back(std::make_pair(si->m_sid,si->m_iTotClient));
}
jLAMDA_end();


#define jLAMDA_jxGet_channel_list(X,Z) \
	X(tcstr ,szDomain)\
	X(vector<serverid_t>&,channel)\
	X(vector<astring>&,channel_name)\
	Z(vector<uint8>&,buzy_level)
jLAMDA_for_each(jxGet_channel_list, jIGridNode*)
{
	jSI(it);
	if(jt_strcmp(si->m_szDomain,szDomain)!=0) return;
	channel.push_back(si->m_sid);
	channel_name.push_back(jA(si->m_szName));
	buzy_level.push_back(si->Get_buzy_level());
}
jLAMDA_end();

#endif // __jServerGrid_functor_header__
