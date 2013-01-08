/* file : jAnimationKey.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-01-18 15:13:02
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jAnimationKey_header__
#define __jAnimationKey_header__
#pragma once

#include "interface/jIAnimationKey.h"
#include "base/jMsgManager.h"
#include "base/jRtti.h"
#include "base/jxVar.h"

/*
ANIMATION_TYPE : loop or play
PLAY_TIME : �ѷ����� �÷��̵Ǵ� �ð�
PLAYCOUNT : ENABLE�Ǿ� �÷��� �ɶ�����÷��̵���
*/

namespace nMech
{
	namespace nEVENT
	{

		class JUTIL_API jAni_KeyList  : public jRttiObj , public jIAni_KeyList
		{
		public :
			typedef jAni_KeyList parent_t ;

			jAni_KeyList();
			virtual void Create();
			virtual void Destroy();
			virtual void* GetInterfaceRTTI(StringID id);
			virtual void* GetInterfaceKeyList(StringID id){	return GetInterfaceRTTI(id);	}
			virtual jIE* CurrVal(){ return m_peCurrVal;}
			virtual void Init(jIE* pE,void* pOwner);
			virtual void SetAnimationPos(float fRange,float fPlayTimeLen) ;
			virtual void Play(){}
			virtual void Stop(){}
			virtual bool FrameMove(){return false;}// true �����ϸ� FrameMove�Լ����� �ߴ��Ѵ�.
			jIE* GetIE(){ return m_pE;}
			void SetAnimationCallback(float fRange,cstr szAniName, jIAni_KeyList::Callback_t&  cb);

		private:
			void set_curr_KEY_index(size_t idx); // ���� ��ġ�� ������ �����Ѵ�. -> m_pvCurrNode[0], [1]

		protected:

			float m_fCurrFact; // ���� �����Ǵ� ��ġ
			jIE* m_peCurrNodes[2];// ���� �� �� ����
			jIE* m_peCurrVal; // ���� ������ ��

#define for_each_jAnimationKeyList_member(x) x(KeyControl)

			for_each_jAnimationKeyList_member(_jKey_member_define);

			jIE* m_pE;
		};

	}

}

#endif // __jAnimationKey_header__
