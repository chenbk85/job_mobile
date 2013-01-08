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
	virtual void PopupDialogInvite		(cstr szWho , ServerIndex_t id) = 0;	// ��Ƽ�ʴ� �޼��� ���Ž�, ����/���� �޼��� ���
	virtual void PopupDialogApply		(cstr szWho , ServerIndex_t id) = 0;	// ��Ƽ��û �޼��� ���Ž�, ����/���� �޼��� ���
	
	virtual void DisplayMessage			(int partyMessage) {};	// ���� ��Ƽ ���� �޼���
	virtual void DisplayMessage			(xmlid_ct id) {};		// ���� ��Ƽ ���� �޼���
	virtual void UpdatePartyList		() {};					// ��Ƽ���� �߰�/���� �ǰų�, ��Ƽ�� ���� �����
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