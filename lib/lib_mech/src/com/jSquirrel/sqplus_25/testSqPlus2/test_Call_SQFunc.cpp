/* file : test_Call_SQFunc.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-21 18:43:01
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include <boost/ref.hpp>
	
static int g_Creature_id =0;
class Creature {
	int id;
	int health;
public:
	enum {MaxHealth=100};
	Creature() : health(MaxHealth) {id = g_Creature_id++;}
	Creature& operator = (const Creature& c)
	{ 
		health = c.health;
		return *this;
	}
	
	int GetMaxHealth(void) {
		return MaxHealth;
	}
	int GetHealth(void) {
		return health;
	}
	void SetHealth(int newHealth) {
		health = newHealth;
	}
	void Print()
	{
		scprintf(_T("\ncreature(%d) hp = %d\n"),id,health);
	}
};

DECLARE_INSTANCE_TYPE(Creature)



void test_Call_SQFunc()
{
	// === BEGIN example from forum post ===

	SQClassDef<Creature>(_T("Creature")).
		func(&Creature::GetMaxHealth,_T("GetMaxHealth")).
		func(&Creature::GetHealth,_T("GetHealth")).
		func(&Creature::Print, _T("Print")).
		func(&Creature::SetHealth,_T("SetHealth"));

	SquirrelObject testClass = SquirrelVM::CompileBuffer( _T("\
					 function HealthPotionUse(Target) \
					 { \n\
							local curHealth = Target.GetHealth(); \n\
							local maxHealth = Target.GetMaxHealth(); \n\
							\
							if ((maxHealth - curHealth) > 15) \
							{ \n\
								  curHealth += 15; \n\
							} \
							else \
							{ \n\
									curHealth = maxHealth; \n\
							} \n\
							\
							Target.SetHealth(curHealth); \n\
							print(typeof Target); \n\
							Target.Print(); \n\
							return Target; \n\
					 }"));
	Creature frodo;
	frodo.SetHealth(frodo.GetMaxHealth()/2);
	frodo.Print();
	/* 출력

		creature(0) hp = 50

	*/

	SquirrelVM::RunScript(testClass);

	Creature newFrodo = SquirrelFunction<Creature &>(_T("HealthPotionUse"))(frodo); 
	/* 출력

	creature(1) hp = 65

	*/
	scprintf(_T("Frodo's health: %d %d\n"),frodo.GetHealth(),newFrodo.GetHealth());
	// Pass by value and return a copy (Must return by reference due to template system design).
	/*

	Frodo's health: 50 65

	*/


	SquirrelFunction<void>(_T("HealthPotionUse"))(&frodo);                          
	/* 

	creature(0) hp = 65

	*/
	// Pass the address to directly modify frodo.
	scprintf(_T("Frodo's health: %d %d\n"),frodo.GetHealth(),newFrodo.GetHealth());
	/*

	Frodo's health: 65 65

	*/


	SquirrelFunction<void>(_T("HealthPotionUse"))(boost::ref(frodo));                          
	/*

	creature(2) hp = 80

	*/

	// Pass the address to directly modify frodo.
	scprintf(_T("Frodo's health: %d %d\n"),frodo.GetHealth(),newFrodo.GetHealth());
	/*

	Frodo's health: 65 65

	*/

	// === END example from forum post ===






	SquirrelObject defCallFunc = SquirrelVM::CompileBuffer(_T(" \
				function callMe(var) \
				{ \
					print(\"I was called by: \"+var); \
					return 123; \
				}"));
	SquirrelVM::RunScript(defCallFunc);

	SquirrelObject defCallFuncStrRet = SquirrelVM::CompileBuffer(_T(" \
				function callMeStrRet(var) \
				{ \
					print(\"I was called by: \"+var); \
					return var; \
				}"));
	SquirrelVM::RunScript(defCallFuncStrRet);

	SquirrelFunction<void>(_T("callMe"))(_T("Squirrel 1"));

	// Get a function from the root table and call it.
#if 1
	SquirrelFunction<int> callFunc(_T("callMe"));
	int ival = callFunc(_T("Squirrel"));
	scprintf(_T("IVal: %d\n"),ival);

	SquirrelFunction<const SQChar *> callFuncStrRet(_T("callMeStrRet"));
	const SQChar * sval = callFuncStrRet(_T("Squirrel StrRet"));
	/* 출력

	I was called by: Squirrel StrRet

	*/
	scprintf(_T("SVal: %s\n"),sval);
	/*출력

	SVal: Squirrel StrRet

	*/

#endif

	ival = 0;
	SquirrelObject root = SquirrelVM::GetRootTable();

	// Get a function from any table.
	SquirrelFunction<int> callFunc2(root.GetObjectHandle(),_T("callMe"));
	ival = callFunc(456); // Argument count is checked; type is not.
	/* 출력

	I was called by: 456

	*/



}

