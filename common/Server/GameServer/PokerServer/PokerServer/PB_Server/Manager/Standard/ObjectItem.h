//------------------------------------------------------------------------------------
// Module Name			: Object(.h)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObject
//------------------------------------------------------------------------------------
#ifndef __ObjectItem_H__
#define __ObjectItem_H__

//#pragma once

//#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
//#include <google/protobuf/stubs/common.h>
//#include "../../../Protocol Buffers/Poker/Game_Poker.pb.h"
#include "../../../Protocol Buffers/Poker/AdlGame_Poker.h"
#include "../Object.h"

#include <string>

//using namespace Game_Poker;
using namespace adl;
//using namespace std;

class CObjectItem : public CObjectBase
{
public:
	CObjectItem(void):CObjectBase(){
		InitObjectItem();
	} 
	/*
	CObjectItem(ISGRCContainer* pGRCContainer):CObjectBase(pGRCContainer){
		InitObjectItem();
		
	} 
	*/
public:
	virtual ~CObjectItem(void){ FreeObjectItem(); }
	void InitObjectItem(void){}
	void FreeObjectItem(void){}
public:
	virtual bool CreateObject(void);
public:
	void SendItemNotify(long lUSN);
	void SendItemNotify(__int64 lCurrentTime);
	void SendAssaItemNotify(long lUSN, int nIndex, string& sItem, long lRankType);
	long OnChangeUserItemNotify(long lUSN, const char* szItem, long lSize);
	void Assa38GwangDdang(int nIndex);
	bool DBQuery_Assa38GwangDdang(long lUSN, string sItemType, string sItem);
	void OnRcvTestKeySetting(long lUSN, MsgCS_TestKeySetting* pMsg);
};

#endif