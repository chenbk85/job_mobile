/* file : test_Class_Instance.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-21 18:04:20
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"

// === BEGIN Class Instance Test ===

//--------------------------------------------------------------------------
class PlayerManager 
//--------------------------------------------------------------------------
{
public:
	struct Player 
	{
		ScriptStringVar64 name;
		void printName(void) {
			scprintf(_T("Player.name = %s\n"),name.s);
		}
	};
	Player playerVar; // Will be accessed directly.
	Player players[2];
	
	Player * GetPlayer(int player) 
	{ // Must return pointer: a returned reference will behave the same as return by value.
		return &players[player];
	}
	
	PlayerManager() 
	{
		players[0].name = _T("Player1");
		players[1].name = _T("Player2");
		playerVar.name  = _T("PlayerVar");
	}
} playerManager;

DECLARE_INSTANCE_TYPE(PlayerManager)
DECLARE_INSTANCE_TYPE(PlayerManager::Player)

PlayerManager * getPlayerManager(void) 
{ // Must return pointer: a returned reference will behave the same as return by value.
	return &playerManager;
}


//--------------------------------------------------------------------------
void test_Class_Instance()
//--------------------------------------------------------------------------
{
	// === BEGIN Instance Test ===

	SQClassDef<PlayerManager::Player>(_T("PlayerManager::Player")).
		func(&PlayerManager::Player::printName,_T("printName")).
		var(&PlayerManager::Player::name,_T("name"));

	SQClassDef<PlayerManager>(_T("PlayerManager")).
		func(&PlayerManager::GetPlayer,_T("GetPlayer")).
		var(&PlayerManager::playerVar,_T("playerVar"));

	RegisterGlobal(getPlayerManager,_T("getPlayerManager"));
	BindVariable(&playerManager,_T("playerManagerVar"));

	SquirrelObject testGetInstance = GetjISQ()->VM_CompileBuffer(_T("\
								local PlayerManager = getPlayerManager(); \n\
								local oPlayer = PlayerManager.GetPlayer(0); \n\
								print(typeof oPlayer); \n\
								oPlayer.printName(); \n\
								PlayerManager.playerVar.printName(); \n\
								print(PlayerManager.playerVar.name); \n\
								oPlayer = PlayerManager.playerVar; \n\
								oPlayer.name = \"New_Name1\"; \n\
								playerManagerVar.playerVar.printName(); \n\
								oPlayer.name = \"New_Name2\"; \n\
								"));
	GetjISQ()->VM_RunScript(testGetInstance);
	/* ���
	
	instance
	Player.name = Player1
	Player.name = PlayerVar
	PlayerVar
	Player.name = New_Name1

	*/

	scprintf(_T("playerManager.playerVar.name: %s\n"),playerManager.playerVar.name.s);
	/* ���

	playerManager.playerVar.name: New_Name2

	*/

	// === END Instance Test ===

}

