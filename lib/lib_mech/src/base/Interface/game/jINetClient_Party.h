#ifndef __Masdfkleio2398df89sfhj4li_GIPARTY_H
#define __Masdfkleio2398df89sfhj4li_GIPARTY_H

#include <windows.h>
#include <string>

#pragma once

//------------------------------------------------------------------------------------
// Defines 
//------------------------------------------------------------------------------------
typedef ServerIndex_t 	jPlayerID_t;

//------------------------------------------------------------------------------------
// PartyCommand Object : be called by jIPartySystem
//------------------------------------------------------------------------------------
struct jICallbackParty
{
public:
	//----------------------------------------------------------
	// Interface : event
	//----------------------------------------------------------
	virtual void PopupDialogInvite		(cstr szWho , ServerIndex_t id) = 0;	// 파티초대 메세지 수신시, 수락/거절 메세지 띄움
	virtual void PopupDialogApply		(cstr szWho , ServerIndex_t id) = 0;	// 파티요청 메세지 수신시, 수락/거절 메세지 띄움
	
	virtual void DisplayMessage			(int partyMessage) {};	// 각종 파티 관련 메세지
	virtual void DisplayMessage			(xmlid_ct id) {};		// 각종 파티 관련 메세지
	virtual void UpdatePartyList		() {};					// 파티원이 추가/삭제 되거나, 파티원 정보 변경시
};

//------------------------------------------------------------------------------------
// jIPartySystem : Interface Class
//------------------------------------------------------------------------------------

#define jINTERFACE_jIPartySystem(x) public:	\
	virtual jICallbackParty*				SetCallback	(jICallbackParty *pObj) ##x \
	virtual jICallbackParty*	GetCallback () ##x \
	virtual void InviteResponse		(jPlayerID_t handle, bool accept) ##x \
	virtual void ApplyResponse		(jPlayerID_t handle, bool accept) ##x \
	virtual bool Invite				(int playerID) ##x \
	/* return value=0: you have not power */ \
	virtual bool Apply				(int playerID) ##x \
	/* return value=0: you have not power */ \
	virtual bool Out				(int playerID) ##x \
	/* return value=0: you have not power or you are not party member */ \
	virtual bool Leave				() ##x \
	/* return value=0: you are not party member */ \
	virtual bool Disband			() ##x \
	/* return value=0: you have not power or you are not party member */ \
	virtual jIE* GetPartyList() ##x \
	virtual jIE*		GetLeader		() ##x \

jINTERFACE_DEFINE(jIPartySystem);
//------------------------------------------------------------------------------------

#endif