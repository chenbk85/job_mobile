/* file : BB_Room.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-10 18:43:19
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __BB_Room_header__
#define __BB_Room_header__
#pragma once



//#--------------------------------------------------------------------------
struct BB_Room
//#--------------------------------------------------------------------------
{
	MOB_HEADER_ROOM(BB_Plugin_Connection);
public:
	void User_Join(BB_Plugin_Connection*);
};



#endif // __BB_Room_header__
