/* file : jXmlSaveManager.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-03-16 13:46:57
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jXmlSaveManager_header__
#define __jXmlSaveManager_header__
#pragma once


class T_SERVER_LIB_API jXmlSaveManager
{
public:
	void SaveDoc(jID* pD,bool isUnload=false,float fTimeSec=0);
	void Destory();

};

extern T_SERVER_LIB_API jXmlSaveManager g_jXmlSaveManager;

#endif // __jXmlSaveManager_header__
