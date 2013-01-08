/* file : jIAnimationKey.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-01-17 22:03:45
comp.: pantavision.co.kr
title : 
desc : 


virtual jIAni_KEY_ANIMATION_LIST* Create_KEY_ANIMATION_LIST(jIE* pE,void*pOwner);
에서 pE는 다음과같은 xml구조를 가지는 노드이다.


<KEY_ANIMATION_LIST f_AnimationPos="0.00000" x_DefaultAnimation="NULL">
	<DEFAULT f_PLAY_TIME="1.00000" x_ANIMATION_TYPE="PLAY" i_PLAYCOUNT="1">
		<jAni_GUI_SIZE b_SCROLLED="1">
			<i2_KEY_SIZE_OFFSET>-61;0</i2_KEY_SIZE_OFFSET>
			<i2_KEY_SIZE_OFFSET>0;0</i2_KEY_SIZE_OFFSET>
		</jAni_GUI_SIZE>
	</DEFAULT>
	<Animation_a f_PLAY_TIME="1.00000" x_ANIMATION_TYPE="LOOP" i_PLAYCOUNT="1">
		<jAni_GUI_SIZE b_SCROLLED="1">
			<i2_KEY_SIZE_OFFSET>0;0</i2_KEY_SIZE_OFFSET>
			<i2_KEY_SIZE_OFFSET>20;0</i2_KEY_SIZE_OFFSET>
		</jAni_GUI_SIZE>
	</Animation_a>
</KEY_ANIMATION_LIST>

*/

#ifndef __jIAnimationKey_header__
#define __jIAnimationKey_header__
#pragma once

namespace nMech
{

	namespace nEVENT
	{
#define _jKey_member_define(MEMBER) jIVar* m_pv##MEMBER;

#define _jKey_member_ctor(MEMBER) m_pv##MEMBER=0;
#define _jKey_member_init(MEMBER) m_pv##MEMBER = pE->GetAttrVar(_T(#MEMBER));\
	if(!m_pv##MEMBER) { pE->GetParent()->DebugPrint(nInterface::g_pjILog);jMB(#MEMBER,"_jKey_member_init error");}

		const float LOOP_jIAni_KeyList = 9999;
		struct jIAni_KeyList
		{

			typedef boost::function<void (jIAni_KeyList*)> Callback_t;
			virtual void Init(jIE* pE, void* pOwner)=0;
			virtual void SetAnimationPos(float fRange,float fPlayTimeLen)=0;
			virtual void* GetInterfaceKeyList(StringID id)=0;
			virtual jIE* CurrVal()	=0; // 현제 보간된 값;
			virtual jIE* GetIE()=0;
			virtual void SetAnimationCallback(float fRange,cstr szAniName, Callback_t&  cb)=0;
		};

		struct jIAni_KEY_ANIMATION_LIST;
		typedef boost::function<void (jIAni_KEY_ANIMATION_LIST* pKAL)> 
			jIAni_KEY_ANIMATION_LIST_AniCallback_t;

#define jINTERFACE_jIAni_KEY_ANIMATION_LIST(x) public: \
	virtual jIE* GetIE()##x \
	virtual jIE* GetCurrAnimation()##x \
	virtual void SetAnimationPos(float fRange)##x \
	virtual void SetAnimationCallback(cstr szAniName, float fRange, jIAni_KEY_ANIMATION_LIST_AniCallback_t&  cb) ##x \
	virtual jIE* SetAnimation(StringID szName)##x \
	virtual jIE* SetAnimation(cstr szName)##x \
	virtual jIE* SetAnimation(jIE* peAniNode)##x \
	virtual void Play()##x \
	virtual void Stop()##x \
	virtual bool FrameMove()##x \
	virtual void Release() ##x \

		jINTERFACE_END(jIAni_KEY_ANIMATION_LIST);

		struct jIMsgManager;
#define jINTERFACE_jIAnimationKeyFactory(x) public: \
	virtual jIAni_KEY_ANIMATION_LIST* Create_KEY_ANIMATION_LIST(jIE* pE,void*pOwner)##x\
	virtual void Delete_KEY_ANIMATION_LIST(jIE*)##x \
	virtual jIMsgManager* GetMsgManager() ##x \
	virtual void ProcessMessage(jIE* peTarget,const std::tstring& type,const std::tstring&msg) ##x \
	virtual jIAni_KEY_ANIMATION_LIST* Get_jIAni_KEY_ANIMATION_LIST(jIE* it)##x\
	virtual jIAni_KeyList* Get_jIAni_KeyList(jIE* it)##x\
	virtual float CalculateAniTime(jIE* pe_jIAni_KeyList) ##x \
	/* return값이 LOOP_jIAni_KeyList이면 무한루프이다. */ \

		jINTERFACE_END(jIAnimationKeyFactory);

	}//nEVENT


	namespace nInterface 
	{
		extern JBASE_API nEVENT::jIAnimationKeyFactory *g_pjIAnimationKeyFactory;
	}


}


#endif // __jIAnimationKey_header__
