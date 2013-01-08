//------------------------------------------------------------------------------------
// Module Name			: Object(.h)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObject
//------------------------------------------------------------------------------------
#ifndef __ObjectRefill_H__
#define __ObjectRefill_H__

//#pragma once

//#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
//#include <google/protobuf/stubs/common.h>
//#include "../../../Protocol Buffers/Poker/Game_Poker.pb.h"
#include "../../../protobuf/gameLogic.pb.h"
#include "../ObjectMgr.h"
//#include "../Object.h"

//using namespace Game_Poker;

class CObjectRefill : public CObjectBase
{
public:
	CObjectRefill(void):CObjectBase(){
		InitObjectRefill();
	} 
	/*
	CObjectRefill(ISGRCContainer* pGRCContainer):CObjectBase(pGRCContainer){
		InitObjectRefill();
	} 
	*/
public:
	virtual ~CObjectRefill(void){ FreeObjectRefill(); }
	void InitObjectRefill(void){}
	void FreeObjectRefill(void){}
public:
	virtual bool CreateObject(void);
public:
	bool IsNewRU(long lUSN);
	bool IsPCBang(long lUSN);
	__int64 NowMaxRefillMoney(long lUSN);
	long GetRefillType(long lUSN);
	bool IsRefillResetDay(long lUSN);
	void RefillCheck();
	int	NowMaxRefillCnt(long lUSN);
	bool DBQGetRefillCnt(long lUSN);
	void DBQSetRefillCnt(long lUSN);
public:
};

#endif