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
	/* Ÿ �������� ������ �����޼����� ��Ʈ������ ���� �޾����� ȣ����.*/ \
	virtual void PutOffItem(jIE* peEQUIP_LIST_Slot,jIXmlEntity*) ##x \
	/* Ÿ �������� ������ ������ ȣ��Ǵ� �ڵ�.*/ \
	virtual jIMessage* CallEvent(jIE* peMsg, xmlid_ct iRunMode) ##x \
	/* Tmp Doc�� EVENT������ �̺�Ʈ ȣ��� ���. iRunMode�� ���� : jPlayer.xml�� <jIEventNode_RunMode>�� �����Ǿ��ִ�. */

jINTERFACE_BASE1_DEFINE(jIClientEntity,jIMessageObject);

#define jINTERFACE_jIClientGameLogic(x) public:	\
	virtual jIClientEntity* FindByServerIndex(int idx) ##x\
	virtual jIClientEntity* FindByXmlEntity(jIXmlEntity*) ##x\
	virtual jIClientEntity* RegistXmlEntity(jIXmlEntity*,bool isMyPlayer=false) ##x \
	virtual bool RemoveEntity(jIXmlEntity*) ##x \
	virtual jIXmlEntity* GetPlayerEntity() ##x \
	virtual void DropItem(jIXmlEntity*, POINT po) ##x \
	/* gui -> client ȣ��� . ���⸦ �ʵ忡 ������ po�� ȭ����ǥ */ \
	virtual jID* GetMessageDoc() ##x \

jINTERFACE_BASE1_DEFINE(jIClientGameLogic,jIMessageObject);

extern JBASE_API jIClientGameLogic* g_pjIClientGameLogic;

#endif // __jIClientGameLogic_header__
