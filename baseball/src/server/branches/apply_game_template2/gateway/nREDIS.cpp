/* file : nREDIS.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-04-18 15:05:25
comp.: www.neowiz.com
title : 
desc : 

*/

#include <gateway/database.hpp>
#include <sqlrelay/sqlrclient.h>
#include <sstream>
#include <boost/format.hpp>
#include <stdlib.h>
#include "protocol/ug.pb.h"

#include "stdafx.h"
#include "nREDIS.h"

using namespace std;
using namespace MSG;


namespace nREDIS
{
// 	bool req_team_match(IN ETotalGameType eType,IN jUser* pUser,OUT s_ans_team_match* sd)
// 	{
// 		sd->set_game_type(eType);
// 		nProtoHelper::message_init(*sd->mutable_opposite_team());
// 		nProtoHelper::message_init(*sd->mutable_opposite_user());
// 		nProtoHelper::message_init(*sd->mutable_opposite_better());
// 		nProtoHelper::message_init(*sd->mutable_opposite_pitcher());
// 		return true;
// 	}
}
