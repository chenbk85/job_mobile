/* file : jIClientGameLogic.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-11-28 12:02:55
title : 
desc : 

*/

#ifndef __jIClientGameLogic_header__
#define __jIClientGameLogic_header__
#pragma once

#include "jMessageObject.h"

struct jIXmlEntity;
struct jINetEntity;
struct jINetClientCallback;

#ifndef jINTERFACE_BASE1_DEFINE
#define jINTERFACE_BASE1_DEFINE( x, y) struct x : public y { jINTERFACE_BASE(x);	};
#endif

#define jINTERFACE_jIClientEntity(x) public:	\
	virtual int GetServerIndex() ##x \
	virtual jIXmlEntity* GetXmlEntity() ##x \
	virtual void SetXmlEntity(jIXmlEntity*) ##x \
	virtual void PutOnItem(jIE* peEQUIP_LIST_Slot,jIXmlEntity*) ##x \
	/* 타 유저들의 아이템 장착메세지를 네트웍으로 부터 받았을때 호출함.*/ \
	virtual void PutOffItem(jIE* peEQUIP_LIST_Slot,jIXmlEntity*) ##x \
	/* 타 유저들의 아이템 헤제시 호출되는 코드.*/ \
	virtual jIMessage* CallEvent(jIE* peMsg, xmlid_ct iRunMode) ##x \
	/* Tmp Doc의 EVENT문서의 이벤트 호출시 사용. iRunMode의 종류 : jPlayer.xml의 <jIEventNode_RunMode>에 나열되어있다. */

jINTERFACE_BASE1_DEFINE(jIClientEntity,jIMessageObject);

#define jINTERFACE_jIClientGameLogic(x) public:	\
	virtual jIClientEntity* FindByServerIndex(int idx) ##x\
	virtual jIClientEntity* FindByXmlEntity(jIXmlEntity*) ##x\
	virtual jIClientEntity* RegistXmlEntity(jIXmlEntity*,bool isMyPlayer=false) ##x \
	virtual bool RemoveEntity(jIXmlEntity*) ##x \
	virtual jIXmlEntity* GetPlayerEntity() ##x \
	virtual void DropItem(jIXmlEntity*, POINT po) ##x \
	/* gui -> client 호출됨 . 무기를 필드에 버릴때 po는 화면좌표 */ \
	virtual jID* GetMessageDoc() ##x \

jINTERFACE_BASE1_DEFINE(jIClientGameLogic,jIMessageObject);

extern JBASE_API jIClientGameLogic* g_pjIClientGameLogic;

#endif // __jIClientGameLogic_header__
