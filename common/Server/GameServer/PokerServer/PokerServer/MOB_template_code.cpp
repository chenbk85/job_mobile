/* file : PK_Plugin_Connection_template_code.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-05 20:12:12
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PK_Plugin_MessageList.h"
#include "PK_Plugin_Connection.h"
#include "PK_Room.h"


// MOB_room_cpp.h호출하기전에 정의해야하는 매크로.
#define MOB_MESSAGE_LIST	for_each_PK_MessageList
#define MOB_IOMODEL_CLASS	PK_Plugin_NetIOModel
#define MOB_CONN_CLASS		PK_Plugin_Connection
#define MOB_ROOM_CLASS		PK_Room
#define MOB_MAX_ROOM_COUNT	iMAX_ROOM_COUNT

#include "MOB_room_cpp.h"