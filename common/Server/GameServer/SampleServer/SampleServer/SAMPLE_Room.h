/* file : SAMPLE_Room.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-10 18:43:19
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __SAMPLE_Room_header__
#define __SAMPLE_Room_header__
#pragma once



//#--------------------------------------------------------------------------
struct SAMPLE_Room
//#--------------------------------------------------------------------------
{
	MOB_HEADER_ROOM(SAMPLE_Plugin_Connection);
public:
	//이후에 로직을 구현 하면 된다.
	void User_Join(SAMPLE_Plugin_Connection*);
};



#endif // __SAMPLE_Room_header__
