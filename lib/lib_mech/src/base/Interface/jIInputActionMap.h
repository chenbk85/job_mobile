/* file : jIInputActionMap.h
Coder : by icandoit (mech12@nate.com, icandoit@n_jGame_c.net)
Date : 2006-05-27 18:09:11
title : 
desc : 

*/

#ifndef __jIInputActionMap_header__
#define __jIInputActionMap_header__
#pragma once
#include "base/jMsgManager.h"

namespace nMech
{

	namespace nINPUT
	{
		enum EIMouseMove {eimm_MOUSE_X,eimm_MOUSE_Y,eimm_MOUSE_Z ,EIMouseMove_MAX};

		struct jInputActionObject;
#define jINTERFACE_jIInputActionMap(x) public:	\
	virtual void Update(void*) ##x\
	virtual void Reload() ##x\
	virtual void ChangeMap(cstr szMap) ##x\
	virtual nMech::nEVENT::jIMsgManager* GetMsgManager() ##x \
	virtual void CancelAction(cstr szAction) ##x \
	virtual void CancelAction(jIE* peActoin) ##x \
	virtual jIE* FindAction(cstr szAction) ##x \
	virtual jInputActionObject* GetActionObject(cstr szMap,cstr szAction) ##x \
	virtual jIE* GetPrevAction(float& repvOkTime,int i) ##x \
	virtual void CallAction(cstr szAction, float fTimePushing) ##x \
	virtual jIVar* GetGameKey(cstr gameKey) ##x \
	/* gameKey는 GetCurrKeyNicNameTable()에서의 KeyNicName의 항목이다. \
		사용법 : g_pIInput->KeyPressed((int)pV->GetUserData()); */ \
		virtual jIE* GetCurrKeyNicNameTable() ##x \
		virtual float CurrMouseMoveOffset(EIMouseMove e) ##x \

		jINTERFACE_END(jIInputActionMap);


		//------------------------------------------------------------------------------------
		// jInputAction
		//------------------------------------------------------------------------------------
		struct jInputActionObject
		{ 	//iActiveTime < 0 이면 해당 액션은 지속키 액션이며 지속이 끝나는 시점이다.
			enum EKeyState
			{
				etPressing, // 연속키에서 누르기 시작할때
				etHolding, // 연속키에서 누르고 있을때
				etReleasing,//연속키에서 땔때
				etPulse // 단발성 키
			};
			virtual void Call(float fActiveTime,jIE*,EKeyState eState,void*)=0;
		};

#define jINPUT_arg float m_fActiveTime, nMech::jIE* m_peAction,nMech::nINPUT::jInputActionObject::EKeyState eState,void* pData

#ifndef jINPUT_ACTION_RECEIVER
#define jINPUT_ACTION_RECEIVER(SCOPE,ACTION) \
		struct _jJOIN_4(jInputAction_,SCOPE,_,ACTION) : public nMech::nINPUT::jInputActionObject {cstr GetName()\
		{static fname_t szName=_T(""); if(!szName[0]) jt_sprintf(szName,_T("jInputAction_%s_%s"), _T(#SCOPE),  _T(#ACTION) ); return szName;}\
		_jJOIN_4(jInputAction_,SCOPE,_,ACTION)(){nMech::jBase::RegistNamedPointer(jS(jINPUT),GetName(),this);} \
		void Call(jINPUT_arg);}; \
		static _jJOIN_4(jInputAction_,SCOPE,_,ACTION) _jJOIN_3(g_jInputAction_,SCOPE,ACTION);\
		void _jJOIN_4(jInputAction_,SCOPE,_,ACTION)::Call(jINPUT_arg)

#endif

#define jINPUT_ACTION_RECEIVER_FORWORDING(map)\
	static nMech::nINPUT::jInputActionObject* pAO = \
	nMech::nInterface::g_pIInput->GetInputActionMap()->GetActionObject(_T(#map),m_peAction->GetTagName() );\
	if(pAO) pAO->Call(m_fActiveTime,m_peAction,eState,pData);

	}
}


#endif // __jIInputActionMap_header__
