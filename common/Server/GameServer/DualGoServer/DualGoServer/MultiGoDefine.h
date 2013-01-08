//
//  MultiGoDefine.h
//  DualGoServer
//
//  Created by jin young park on 11. 11. 23..
//  Copyright (c) 2011년 집. All rights reserved.
//
// MultiGoManager.h MultiUser.h LogicMultiCommand.h

#ifndef DualGoServer_MultiGoDefine_h
#define DualGoServer_MultiGoDefine_h

namespace nGS
{
	const int BUFFER_SIZE =1024*2;
    
	struct PPacketHeader
	{
		int data_length;
	};
    
	enum USER_STATE { USER_ROOM_WAIT=0, USER_ROOM_RUN, USER_GAME_READY, USER_STATE_ZERO };
    enum ROOM_STATE { ROOM_RUN = 0, ROOM_WAIT, ROOM_DIE, ROOM_ZERO };
    enum USER_UPDATE_STATE { USERUPDATE = 1, USERZERO};
    
    // #	define for_each_EUserState(X)\
    // 	X(eUSER_ROOM_WAIT		," »Æ¿Œ µ«æ˙Ω¿¥œ¥Ÿ.")\
    // 	X(eUSER_ROOM_RUN		,"»Æ¿Œ∫“∞°. ¿ﬂ∏¯µ» ≈∞¿‘¥œ¥Ÿ.")\
    // 	X(eUSER_GAME_READY		,"º≠∫ÒΩ∫ ø°∑Ø")\
    // 	X(eUSER_STATE_ZERO		,"º≠∫ÒΩ∫ ¡¢±Ÿ æ∆¿Ã«« æ∆¥‘")\
    // 
    // 	jDEFINE_ENUM_CODE2(EUserState);
    
}

using namespace nGS;

#ifndef LOGIC_TEST
#include "config_all_server.h"
#endif

#include "mech_lib/header/jDefine.h"
#include "mech_lib/header/jTypedef_type.h"
#include "mech_lib/header/m_stltag.h"
using namespace nMech;


#define for_each_ECardType(X)\
	X(eJANUARY				,"JANUARY")\
	X(eFEBUARY				,"JANUARY")\
	X(eMARCH				,"MARCH")\
	X(eAPRIL				,"APRIL")\
	X(eMAY					,"MAY")\
	X(eJUNE					,"JUNE")\
	X(eJULY					,"JULY")\
	X(eAUGUST				,"AUGUST")\
	X(eSEPTEMBER			,"SEPTEMBER")\
	X(eOCTOBER				,"OCTOBER")\
	X(eNOVEMBER				,"NOVEMBER")\
	X(eDECEMBER				,"DECEMBER")\
	X(eCARDTYPE_ZERO		,"CARDTYPE_ZERO")\

jDEFINE_ENUM_CODE2(ECardType);



#endif
