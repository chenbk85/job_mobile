/* file : jAnimationKey.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2007-01-18 15:13:05
comp.: pantavision.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include <math.h>
#include "jAnimationKey.h"
#include "interface/xml/jIXml.h"
#include "base/jRtti.h"
#include "interface/jILog.h"
#include "interface/ITimer.h"

//#define _jAnimationKeyFactory_LOG



namespace nMech
{
	namespace nEVENT
	{


#define for_each_KEY_ANIMATION_LIST_member(x)\
	x(DefaultAnimation)\
	x(AnimationPos)\

#define for_each_AnimationNameNode_member(x)\
	x(ANIMATION_TYPE) \
	x(PLAY_TIME) \
	x(PLAYCOUNT)\


		inline jIAni_KeyList* get_KL(jIE* pE)
		{
			return xGET_USER_DATA(jIAni_KeyList,pE);
		}


		inline jIAni_KEY_ANIMATION_LIST* get_KAL(jIE* it)
		{
			return xGET_USER_DATA(jIAni_KEY_ANIMATION_LIST,it);
		}

		//--------------------------------------------------------------------------
		class  jAni_KEY_ANIMATION_LIST : public jIAni_KEY_ANIMATION_LIST
			//--------------------------------------------------------------------------
		{
			jIE* m_pE;
			void* m_pVoid;
			jIE* m_peCurrAnimation;

			int m_iCurrCount; // play count
			float m_fCurrAnimation_StartTime;// 현제 루프의 애니메이션 플레이 경과시간
			jIMessage* m_pMsg;
			jIAni_KEY_ANIMATION_LIST_AniCallback_t m_CB[2];

		public :
			jINTERFACE_HEADER(jIAni_KEY_ANIMATION_LIST);


			for_each_KEY_ANIMATION_LIST_member(_jKey_member_define);
			for_each_AnimationNameNode_member(_jKey_member_define);

			jAni_KEY_ANIMATION_LIST(jIE* pE, void* pOwner)
			{
				m_peCurrAnimation=0;
				m_pVoid = pOwner;

				m_iCurrCount =0;
				m_fCurrAnimation_StartTime=0;
				m_pMsg=0;

				for_each_AnimationNameNode_member(_jKey_member_ctor);

				m_pE = pE;
				for_each_KEY_ANIMATION_LIST_member(_jKey_member_init);
				pE = m_pE->FindByDepth(1, m_pvDefaultAnimation->Get_StringID());
				if(pE && pE->size())
				{
					setAnimation(pE);
				}
			}

		private:
			friend void jSchedule_jAnimationKeyList(jIMessage* pMsg);
			void clear_CurrAnimation();
			void setAnimation(jIE* pE); // pE가 NULL이면 현제에니메이션을 클리어한다.

			void loop_stop()
			{
				if( !m_pMsg) return;
				m_pMsg->Erase();
				m_pMsg=0;
			}
		};

		jIE* jAni_KEY_ANIMATION_LIST::GetIE(){ 	return m_pE;}
		jIE* jAni_KEY_ANIMATION_LIST::GetCurrAnimation(){ 	return m_peCurrAnimation;}
		void jAni_KEY_ANIMATION_LIST::Release()
		{
			loop_stop();
			m_pvAnimationPos->Set_float(0);
			clear_CurrAnimation();
			delete this;
		}

		void jAni_KEY_ANIMATION_LIST::SetAnimationCallback(cstr szAniName, float fRange
			, jIAni_KEY_ANIMATION_LIST_AniCallback_t&  cb)
		{


		}

		jIE* jAni_KEY_ANIMATION_LIST::SetAnimation(jIE* peAniNode)
		{
			setAnimation(peAniNode);
			return peAniNode;
		}

		jIE* jAni_KEY_ANIMATION_LIST::SetAnimation(StringID szName)
		{ 
			if(szName==jx(NULL)) setAnimation(0);
			jIE* peAni = m_pE->FindByDepth(1, szName);
			setAnimation(peAni);
			return peAni;
		}


		jIE* jAni_KEY_ANIMATION_LIST::SetAnimation(cstr szName)
		{ 
			if(szName==0)
			{
				setAnimation(0);
				return 0;
			}
			jIE* peAni = m_pE->FindByDepth(1, szName);
			setAnimation(peAni);
			return peAni;
		}


		void jAni_KEY_ANIMATION_LIST::SetAnimationPos(float fRange)
		{
			if(!m_peCurrAnimation) return;
			if(fRange <0) fRange= 0;
			else if(fRange >1) fRange=1;

			m_pvAnimationPos->Set_float(fRange);

			jIE* it = m_peCurrAnimation->begin();
			jrFOR(it)
			{
				if(it->size()<=1) continue;
				jIAni_KeyList* pKL = get_KL(it);
				if(pKL) pKL->SetAnimationPos(m_pvAnimationPos->Get_float() , m_pvPLAY_TIME->Get_float());
			}
		}
		void jSchedule_jAnimationKeyList(jIMessage* pMsg)
		{
			jAni_KEY_ANIMATION_LIST* pAKL = (jAni_KEY_ANIMATION_LIST*)pMsg->GetArg(0)->GetUserData();
			if(pAKL->m_pMsg!=pMsg)
			{
				pMsg->Erase();
				return;
			}

			if( pAKL->FrameMove( ) )
			{
				pAKL->m_pMsg=0;
				pMsg->Erase();
			}
		}

		void jAni_KEY_ANIMATION_LIST::Play()
		{ 
			if(!m_peCurrAnimation) return;

			if( m_pMsg)
			{
				if( m_pMsg->IsSleep())
				{
					m_pMsg->DoWakeUp();

					float fPass = m_pvAnimationPos->Get_float()* m_pvPLAY_TIME->Get_float();
					m_fCurrAnimation_StartTime = nTIME::Get_ITimer()->GetCurrTime() - fPass;
					return;
				}
			}
			m_fCurrAnimation_StartTime = nTIME::Get_ITimer()->GetCurrTime();
			loop_stop();
			m_pMsg = nInterface::g_pjIAnimationKeyFactory->GetMsgManager()->Regist_Loop(0, jFUNC_Msg(jSchedule_jAnimationKeyList),1,true);
			m_pMsg->GetArg(0)->SetUserData(this);
			m_pMsg->DoWakeUp();



			m_iCurrCount = m_pvPLAYCOUNT->Get_int();

#ifdef _jAnimationKeyFactory_LOG
			jLOG(_T("jAni_KEY_ANIMATION_LIST::Play()"));
#endif
			m_pMsg->DoWakeUp();

		}
		void jAni_KEY_ANIMATION_LIST::Stop()
		{
			if( m_pMsg)
			{
				if(!m_pMsg->IsSleep())
				{
					m_pMsg->DoSleep();
				}
			}
		}

		bool jAni_KEY_ANIMATION_LIST::FrameMove()
		{ // true 리턴하면 FrameMove함수콜을 중단한다.


			if(!m_peCurrAnimation) return true;
			if(m_iCurrCount<=0) return true;

			float fCurrTime = nTIME::Get_ITimer()->GetCurrTime();
			float fPass = fCurrTime - m_fCurrAnimation_StartTime;
			//jLOG(_T("jAni_KeyList::FrameMove(currTime = %f)   pass = %f"),fCurrTime, fPass);
			if(fPass > m_pvPLAY_TIME->Get_float())
			{
#ifdef _jAnimationKeyFactory_LOG
				jLOG(_T("jAni_KeyList::FrameMove() = 루프 완료"));
#endif

				m_fCurrAnimation_StartTime=fCurrTime;
				if( m_pvANIMATION_TYPE->Get_StringID() == jx(PLAY))
				{
					if( m_iCurrCount >0)
					{
						--m_iCurrCount;
					}
				}
			}

			if(m_iCurrCount <=0 ) // 맨마지막까지 갔음
			{
				SetAnimationPos(1);
				return true ;
			}
			else 
				SetAnimationPos( fPass / m_pvPLAY_TIME->Get_float() );

			return false;
		}


		//--------------------------------------------------------------------------
		// class jAni_KeyList
		//--------------------------------------------------------------------------
		jAni_KeyList::jAni_KeyList()
		{
			m_peCurrVal = GetjIXml()->CreateElement();
		}

		void jAni_KeyList::Init(jIE* pE, void* pOwner)
		{
			m_pE = pE;
			for_each_jAnimationKeyList_member(_jKey_member_init);
			if(m_pE->size())
			{
				m_pE->begin()->CopyTo(m_peCurrVal);
			}

		}
		void* jAni_KeyList::GetInterfaceRTTI(StringID id)
		{

			if(id == jx(jAni_KeyList))
			{
				return this;
			}
			else if(id == jx(jIAni_KeyList))
			{
				return static_cast<jIAni_KeyList*>(this);
			}
			else if(id==jx(jRttiObj))
			{
				return static_cast<jRttiObj*>(this);
			}
			return jRttiObj::GetInterfaceRTTI(id);
		}

		void jAni_KeyList::SetAnimationCallback(float fRange,cstr szAniName, jIAni_KeyList::Callback_t&  cb)
		{

		}

		void jAni_KeyList::Create()
		{	
			memset(m_peCurrNodes , 0, sizeof(m_peCurrNodes));
			m_fCurrFact=0;
			m_pE=0;
			for_each_jAnimationKeyList_member(_jKey_member_ctor);
		};

		void jAni_KeyList::Destroy()
		{
			jASSERT0(!m_peCurrVal->GetParent());
			m_peCurrVal->EraseChild();
			m_peCurrVal->GetVar()->clear();
		}

		void jAni_KeyList::set_curr_KEY_index(size_t idx)
		{
			if(idx <= 0)
			{
				idx = 0;
			}
			else if( idx >= m_pE->size())
			{
				idx = m_pE->size()-1;
			}

			jIE* pe = m_pE->FindByOrder(idx);
			m_peCurrNodes[0] = pe;
			if( pe->GetRight())	pe = pe->GetRight();
			m_peCurrNodes[1] = pe;
		}


		void jAni_KeyList::SetAnimationPos(float fRange,float fPlayTimeLen)
		{
			if(m_pE->size() <=1)
			{
				return;
			}

			float fCurrAnimation_PassedTime = fRange* fPlayTimeLen;
			float fTimePer_KEY_Range= fPlayTimeLen / (m_pE->size()-1) ;
			float fCurrTimePoint = fCurrAnimation_PassedTime / fTimePer_KEY_Range;
			float fCurrNode_Index = floor(fCurrTimePoint);
			float fCurrNode_LerpRatio = (fCurrTimePoint -fCurrNode_Index);
#if 0
			jLOG(_T("fTimePer_KEY_Range = %f  fCurrAnimation_PassedTime =%f fCurrTimePoint=%f , fCurrNode_Index=%f,  fCurrNode_LerpRatio=%f")
				,fTimePer_KEY_Range 
				,fCurrAnimation_PassedTime
				,fCurrTimePoint
				,fCurrNode_Index
				,fCurrNode_LerpRatio 
				);
#endif

			set_curr_KEY_index(fCurrNode_Index);

			if(m_pvKeyControl->Get_StringID() ==jx(LERP))
			{
				m_peCurrVal->Lerp(m_peCurrNodes[0], m_peCurrNodes[1], fCurrNode_LerpRatio );
			}
			else
			{
				if(fCurrNode_LerpRatio > 0.5)
					m_peCurrNodes[1]->CopyTo(m_peCurrVal);
				else
					m_peCurrNodes[0]->CopyTo(m_peCurrVal);
			}

#ifdef _jAnimationKeyFactory_LOG
			fname_t buf;
			jLOG(_T("%s :: SetAnimationPos(range = %f) "), m_pE->GetTagName(),fRange);
			m_peCurrVal->DebugPrint(0);
#endif
		}

		//--------------------------------------------------------------------------
		class jAnimationKeyFactory : public jIAnimationKeyFactory
			//--------------------------------------------------------------------------
		{
			jINTERFACE_HEADER(jIAnimationKeyFactory);
		public:
			jAnimationKeyFactory()
			{
				nInterface::g_pjIAnimationKeyFactory= this;
			}
			jIAni_KeyList* Create_KeyList(jIE* pE, void* pOwner)
			{
				if(!pE->size()) return 0;
				jRttiObj* pObj = jRTTI::New(pE->GetTagName() , _T("jIAni_KeyList"));
				if(!pObj)
				{
					pE->DebugPrint(nInterface::g_pjILog);
					jERROR(_T("jIAni_KeyList의 RTTI를 못찾음 = %s"), pE->GetTagName());
					return 0;
				}
				jIAni_KeyList* pAKL = (jIAni_KeyList*)pObj->GetInterfaceRTTI(jx(jIAni_KeyList));
				pAKL->Init(pE, pOwner);
				pE->SetUserData(jS(jIAni_KeyList),pAKL);

				return pAKL;
			}

			void Delete_KeyList(jIE* pE)
			{

				jIAni_KeyList* pKL = get_KL(pE);
				if(!pKL) return;
				jRttiObj* pObj = (jRttiObj*)pKL->GetInterfaceKeyList(jx(jRttiObj));
				jASSERT0(pObj);
				jRTTI::Del(pObj);
				pE->SetUserData(jS(jIAni_KeyList),0);
			}

		};

		static jAnimationKeyFactory s_jAnimationKeyFactory ;

		float jAnimationKeyFactory::CalculateAniTime(jIE* pe_jIAni_KeyList)
		{
			if(pe_jIAni_KeyList->GetAttrVar(_T("ANIMATION_TYPE"))->Get_StringID() == jx(LOOP))
			{
				return -1;
			}
			float fTime = pe_jIAni_KeyList->GetAttrVar(_T("PLAY_TIME"))->Get_float();
			int iCount = pe_jIAni_KeyList->GetAttrVar(_T("PLAYCOUNT"))->Get_int();
			return fTime * iCount;
		}


		jIAni_KEY_ANIMATION_LIST* jAnimationKeyFactory::Create_KEY_ANIMATION_LIST(jIE* pE, void* pOwner)
		{
			jIAni_KEY_ANIMATION_LIST* pKAL = new jAni_KEY_ANIMATION_LIST(pE, pOwner);
			pE->SetUserData(jS(jIAni_KEY_ANIMATION_LIST),pKAL);
			return pKAL;

		}

		void jAnimationKeyFactory::Delete_KEY_ANIMATION_LIST(jIE* pE)
		{
			jIAni_KEY_ANIMATION_LIST* pKAL  = get_KAL(pE);
			if(!pKAL) return;
			pKAL->Release();
			pE->SetUserData(jS(jIAni_KEY_ANIMATION_LIST),0);
		};


		void jAnimationKeyFactory::ProcessMessage(jIE* peTarget, const tstring& sWho ,const tstring& sMsg)
		{
			if(sWho== _T("KEY_ANIMATION_LIST"))
			{
				if(sMsg ==_T("Play"))
				{
					jIAni_KEY_ANIMATION_LIST* pNode = get_KAL(peTarget);
					if(!pNode) return;
					pNode->Play();
				}
				else if(sMsg==_T("Stop"))
				{
					jIAni_KEY_ANIMATION_LIST* pNode = get_KAL(peTarget);
					if(!pNode) return;
					pNode->Stop();
				}
				else if(sMsg==_T("Play_ThisAni"))
				{
					jIAni_KEY_ANIMATION_LIST* pNode = get_KAL(peTarget->GetParent());
					if(!pNode) return;
					if(pNode->GetCurrAnimation() == peTarget)
					{
						pNode->Play();
					}
					else
					{
						pNode->SetAnimation(peTarget->GetTagName());
					}
				}
				else if(sMsg==_T("Stop_ThisAni"))
				{
					jIAni_KEY_ANIMATION_LIST* pNode = get_KAL(peTarget->GetParent());
					if(!pNode) return;
					pNode->Stop();

				}
				else if(sMsg==_T("Reset"))
				{
					jIAni_KEY_ANIMATION_LIST* pNode = get_KAL(peTarget);
					if(!pNode) return;
					pNode->SetAnimation((cstr)0);
				}
				return;
			}
		}

		jIMsgManager* jAnimationKeyFactory::GetMsgManager()
		{
			static jIMsgManager* pMM = jIMsgManager::Get(_T("jAnimationKeyFactory"),true);
			return pMM;
		}


		jIAni_KEY_ANIMATION_LIST* jAnimationKeyFactory::Get_jIAni_KEY_ANIMATION_LIST(jIE* it)
		{
			if(!it) return 0;
			return get_KAL(it);
		}
		jIAni_KeyList* jAnimationKeyFactory::Get_jIAni_KeyList(jIE* it)
		{
			if(!it) return 0;
			return get_KL(it);
		}


		void jAni_KEY_ANIMATION_LIST::setAnimation(jIE* pE) // pE가 NULL이면 현제에니메이션을 클리어한다.
		{
			if( m_peCurrAnimation != pE)
			{
				clear_CurrAnimation();

				m_peCurrAnimation = pE;
				if(!pE || !pE->size() )
				{
					m_peCurrAnimation=0;
					return;
				}

				for_each_AnimationNameNode_member(_jKey_member_init);
				jIE* it = pE->begin();
				jrFOR(it)
				{
					if(it->size() <=1) continue;
					jIAni_KeyList* pList = s_jAnimationKeyFactory.Create_KeyList(it, m_pVoid);
				}

			}
			if(!m_peCurrAnimation) return;
			SetAnimationPos(0);
			if(m_pvANIMATION_TYPE->Get_StringID() !=jx(MENUAL))
				Play();

		}

		void jAni_KEY_ANIMATION_LIST::clear_CurrAnimation()
		{
			if(!m_peCurrAnimation) return;
			jIE* it = m_peCurrAnimation->begin();
			jrFOR(it)
			{
				s_jAnimationKeyFactory.Delete_KeyList(it);
			}
			for_each_AnimationNameNode_member(_jKey_member_ctor);
		}
	}

}

