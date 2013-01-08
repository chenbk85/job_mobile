/* file : common_ug.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-03-22 17:55:28
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __common_ug_header__
#define __common_ug_header__
#pragma once

#include "t:/svn/MSG/src/svn_version.hpp"
#include "t:/svn/baseball/MOB_lib/DBHelper.h"

//X(ENUM,STRUCT,VAR)
#define for_each_UAnsProtocol(X)\
	X(UANSCONNECT		, UAnsConnect		, ansconnect		)\
	X(UANSCHANNEL		, UAnsChannel		, anschannel		)\
	X(UANSSTORE			, UAnsStore			, ansstore			)\
	X(UANSINFO			, UAnsInfo			, ansinfo			)\
	X(UANSAUTOJOIN		, UAnsAutoJoin		, ansautojoin		)\
	X(UANSLEAVEGAME		, UAnsLeaveGame		, ansleavegame		)\
	X(UANSCLOSE			, UAnsClose			, ansclose			)\
	X(UANSPING			, UAnsPing			, ansping			)\
	X(UANSPLUG			, UAnsPlug			, ansplug			)\
	X(UANSDB			, AnsDB				, ansdb				)\
	X(UANSNOTICE		, UAnsNotice		, ansnotice			)\
	X(UERROR			, UError			, anserror			)\


namespace ug
{
	extern Version& Make(Version& v);

	inline MemberInfo& Make(MemberInfo& v, int32 game_id,acstr avatar_url , acstr nic_name , bool gender_option)
	{
		v.set_game_id(game_id);
		v.set_avatar_url(avatar_url);
		v.set_nick_name(nic_name);
		v.set_gender_option(gender_option);
		return v;
	}

}



#endif // __common_ug_header__
