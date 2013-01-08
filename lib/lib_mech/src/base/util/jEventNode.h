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
				eREADY,//ó�� ���ۻ���.
				eGOTO_START, // ���۽� m_iStartTime�� 0�� �ƴϸ� �̻��·� ����.
				eGOTO_RESTART,
				eGOTO_END,
				eEND,
				eTERMINATE_BY_CLIENT // ����Ŭ����(Ŭ���̾�Ʈ)���� ������ ������ ��ü�� �Ҹ��Ŵ
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
			virtual int  FrameMove(); // 1�� �����ϸ� ��� �޼���ó���� ������.

			virtual bool OnInit(jIE* pE,DWORD uWorldStartTime,void* v); //�ʱ�ȭ �ɶ� ȣ��� 
			virtual void OnPostInit(jIMessage* pMsg)	{		m_pMsg = pMsg ;	}// �ش�jIEventNode�� ����ϰԵ� jMessage��ü�� �������� ȣ���.
			virtual bool OnFrameMove(){return 0;} // eGOTO_END�����϶� �������Ӻ��� ȣ���. ���ϰ��� 1�̸� ���� �̺�Ʈ�� ��� �����ȴ�. 
			virtual void OnExcuteStart()=0; // eGOTO_START -> eGOTO_END���·� �Ѿ������ ȣ���.
			virtual void OnExcuteReStart(){} // eGOTO_END -> eGOTO_RESTART�� �Ѿ�� ȣ���.
			virtual void OnExcuteEnd(){} // eGOTO_END���� eEND�� �Ѿ�� ȣ���.
			static jIMessage* CallEvent(jIE* peMsgList,void*,StringID iRunMode=0); //iRunMode = jPlayer.xml���� <jIEventNode_RunMode>
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

