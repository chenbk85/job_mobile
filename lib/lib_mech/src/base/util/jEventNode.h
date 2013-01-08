/* file : jEventNode.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2006-01-16 17:15:44
title : 
desc : 

*/

#ifndef __jEventNode_header__
#define __jEventNode_header__

#pragma once
#include "base\\jMsgManager.h"
#include "base/jRtti.h"

namespace nMech
{
	namespace nEVENT
	{
		struct jEventRoot;
		struct jIEventRoot;

		//--------------------------------------------------------------------------
		struct JUTIL_API jIEventNode : public jRttiObj
			//--------------------------------------------------------------------------
		{
			typedef jIEventNode parent_t;
			enum EState
			{
				eDEACTIVATE,
				eDELETED,
				eREADY,//처음 시작상태.
				eGOTO_START, // 시작시 m_iStartTime가 0이 아니면 이상태로 간다.
				eGOTO_RESTART,
				eGOTO_END,
				eEND,
				eTERMINATE_BY_CLIENT // 서브클래스(클라이언트)에서 조건이 됐을때 객체를 소멸시킴
			};
			jIEventRoot* m_pRoot;
			jIMessage* m_pMsg;
			int m_iPassTime;
			jIE* m_peMsg;
			DWORD m_uStartTimeWorld;
			int m_iStartTime;
			int m_iEndTime;
			int m_iLoop;
			EState m_eState;
		private:
			bool m_isQuit;
		public:
			bool IsQuit(){ return m_isQuit;}
			void SetQuit(bool is){ m_isQuit = is;}
			bool IsActive(){ return m_eState!=eDEACTIVATE;}
			void SetActive(bool is);
			virtual void Create(){ m_isQuit = true;}
			virtual void Destroy()	;
			virtual int  FrameMove(); // 1을 리턴하면 모든 메세지처리가 끝났다.

			virtual bool OnInit(jIE* pE,DWORD uWorldStartTime,void* v); //초기화 될때 호출됨 
			virtual void OnPostInit(jIMessage* pMsg)	{		m_pMsg = pMsg ;	}// 해당jIEventNode를 담당하게될 jMessage객체가 생성된후 호출됨.
			virtual bool OnFrameMove(){return 0;} // eGOTO_END상태일때 매프레임별로 호출됨. 리턴값이 1이면 현제 이벤트는 즉시 삭제된다. 
			virtual void OnExcuteStart()=0; // eGOTO_START -> eGOTO_END상태로 넘어가기전에 호출됨.
			virtual void OnExcuteReStart(){} // eGOTO_END -> eGOTO_RESTART로 넘어갈때 호출됨.
			virtual void OnExcuteEnd(){} // eGOTO_END에서 eEND로 넘어갈때 호출됨.
			static jIMessage* CallEvent(jIE* peMsgList,void*,StringID iRunMode=0); //iRunMode = jPlayer.xml에서 <jIEventNode_RunMode>
			static void CancleMessage(jEventRoot* pMsg);
			static void UnRegistKey(void* key);
			//	static void jSchedule(jIMessage* pMsg);
		private:

		};

		struct jIEventRoot
		{
			virtual jEventRoot* Base()=0;
			virtual bool IsClear()=0;
			virtual void SetEventNode(int iOrder , jIEventNode* pEN)=0;
			virtual jIEventNode* GetEventNode(int iOrder)=0;
			virtual void SetActive(bool is)=0;
		};


	}

#ifndef itFOR
#define itFOR(it,ie) for( ; it!=ie ; ++it)
#endif

#define jDECLARE_jIEventNode(x,p) typedef p parent_t; jDECLARE_RTTIOBJ(x);
#define jDEFINE_jIEventNode(x,cnt,slot) jDEFINE_RTTIOBJ(x,nMech::nEVENT::jIEventNode,cnt,slot);

}

#endif // __jEventNode_header__

