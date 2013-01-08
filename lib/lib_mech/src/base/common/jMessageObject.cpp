/* file : jMessageObject.cpp
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-12-30 10:15:08
title : 
desc : 

*/

#include "stdafx.h"
#include "jMessageObject.h"

namespace nMech
{
	namespace nEVENT
	{

		//--------------------------------------------------------------------------
		jIMsgManager* jIMessageObject_m_pMsgManager=0;
		//--------------------------------------------------------------------------

		jIMsgManager* jIMessageObject::GetMsgManager()
		{ 
			return jIMessageObject_m_pMsgManager;
		}

		//JBASE_API void jMech_Init()¿¡¼­ È£ÃâµÊ.
		void jIMessageObject::Create(cstr szName)
		{
			assert(!jIMessageObject_m_pMsgManager);
			jIMessageObject_m_pMsgManager = jIMsgManager::Get(szName,true);
		}

		static void _jSchedulejIMessageObjectMsg(jIMessage* pMsg)
		{
			jIE* pE = (jIE*)pMsg->GetArg(pMsg->GetArgCount()-1)->GetUserData();
			jIMessageObject* pObj = (jIMessageObject*)pMsg->GetArg(pMsg->GetArgCount()-2)->GetUserData();

			_jIMessage* pF= (_jIMessage*)pE->GetUserData();
			if(!pF) return ;
			pF->Call(pObj, pE, pMsg);
		}

		int jIMessageObject::ProcessMessage(jIE* pE, void* vData )
		{
			if(!pE->GetUserData()) return -1;

			jIMessage* pMsg= GetMsgManager()->Regist_Loop(0,jFUNC_Msg(_jSchedulejIMessageObjectMsg),pE->size()+2);

			pMsg->GetArg(pMsg->GetArgCount()-1)->SetUserData(pE);
			pMsg->GetArg(pMsg->GetArgCount()-2)->SetUserData(this);
			jIE* it = pE->begin();
			jrFOR(it)
			{
				it->GetVar()->CopyTo( pMsg->GetArg(it->GetOrder()) );
			}
			pMsg->DoWakeUp();

			return 0;
		}

		void jIMessageObject::Init(jIE* peMsgList)
		{
			if(!peMsgList) return;
			peMsgList->for_each(_jxORBMsgRegister(peMsgList->GetTagName() , peMsgList->GetDepth()+1) );
		}
	}
}
