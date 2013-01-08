/* 
	filename:	jMsgManager.h
	coder	:	Cho Wook Rea (chowookrea@hotmail)(icq:74456993) 
	comp.	:	-MAEUMNET-
	compiler:	vc++ 6.0
	date	:	2003-11-18���� 4:32:17
	title	:	
*/


#ifndef __jMsgManager_h__
#define __jMsgManager_h__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000
#include "header\\yVector.h"
#include "header\\m_Manager.h"
#include "Interface/xml/jIVar.h"
#include "Interface/xml/jIVar_op.h"

namespace nMech
{

	class jxVar;
	namespace nEVENT
	{

		class jMessage;
		struct jIMessage;

		typedef void jIMessage_CallbackFunc_t(jIMessage*);
		//typedef boost::function<void (jIMessage*)> jIMessage_CallbackFunc_t;

#define jINTERFACE_jIMessage(x) public:	\
	virtual jMessage *Base() ##x \
	\
	virtual bool IsErase() ##x \
	virtual bool IsLoop() ##x \
	virtual bool IsSleep() ##x \
	\
	/* �޼����� Regist_CountBase�� ȣ��ɶ� ���� ������. 1�̸� ������ ȣ���̴�.*/\
	virtual int GetRemainCount()##x \
	virtual int GetArgCount() ##x \
	virtual jVar GetArg(int i) ##x \
	virtual void SetCallbackFunc(jIMessage_CallbackFunc_t* func)##x \
	\
	virtual void Erase() ##x \
	virtual void DoLoop() ##x \
	virtual void DoSleep() ##x \
	virtual void DoWakeUp() ##x \
	virtual void DoTimeBase(float fTriggerTime)##x /*fTriggerTime ���� �޼����� ȣ���*/\
	virtual void DoCountBase(int iCount)##x /* iCount��ŭ ȣ���� �޼��� ����*/\
	virtual void DoTimePeriod(float fTimePeriod)##x /* fTimePeriod���� �޼��� ȣ���� �ߴ� */\

		jINTERFACE_END(jIMessage);


		typedef void for_each_func_t(tcstr szMM,jIMsgManager* pMM, jIMessage*pM);
		typedef bool find_if_func_t(tcstr szMM,jIMsgManager* pMM, jIMessage*pM);

#define jFUNC_Msg(FUNC) FUNC , jS(FUNC)

		struct JBASE_API jIMsgManager
		{
			typedef void MsgFunc_t (jIMessage*); 

			// isLoop== false�̸� �ѹ��� ����Ǵ� �޼����۾��� �����Ѵ�.
			virtual jIMessage* Regist_Loop(int iOrder , MsgFunc_t* pFunc,tcstr szFunc, int iArgCount, bool isLoop=false)=0;

			// fTriggerTime���� �޼��� �۾��� ȣ��
			virtual jIMessage* Regist_TimeBase(int iOrder , MsgFunc_t* pFunc,tcstr szFunc, int iArgCount , float fTriggerTime)=0;
			// fTimePeriod���� �޼��� �۾��� ȣ��ȣ �ߴ�
			virtual jIMessage* Regist_TimePeriod(int iOrder , MsgFunc_t* pFunc,tcstr szFunc, int iArgCount , float fTimePeriod)=0;


			//fTriggerTime���� �޼����� ȣ���ϵ� runCount��ŭ�� ȣ���ϰ� �޼��� �۾� ���� [ ���� : �� sec ]
			virtual jIMessage* Regist_TimeBaseAndCount(int iOrder, MsgFunc_t* pFunc,tcstr szFunc, int iArgCount , float fTriggerTime,int runCount)=0;
			// runCount��ŭ ȣ��ǰ� �޼��� �۾� ����.
			virtual jIMessage* Regist_CountBase(int iOrder , MsgFunc_t* pFunc,tcstr szFunc, int iArgCount , int runCount)=0;

			// jIMsgManager* Get(cstr szName, ...)���� jIMsgManager��ü ������ �̸��� '_' �� �����ϸ� Run()�� �ݵ�� ȣ��������Ѵ�.
			// ���� jIMsgManager* Get()���� createThread=true�� ȣ��Ǿ��ٸ� Run()�� ȣ�� �� �ʿ䰡 ����.
			virtual void Run()=0;
			virtual void clear()=0;
			virtual uint CurrMsgCount()=0;
			virtual void StopThread()=0;
			virtual void StartThread(bool isWakeThread)=0;
			virtual void StartTimerThread(jIVar* pvTime_msec)=0;
			virtual void WakeThread()=0;
			virtual void for_each(for_each_func_t*)=0;
			virtual jIMessage* find_if(find_if_func_t*)=0;

			// jIMsgManager��ü ����.
			// szName�� _ �� �����ϸ� �� jIMsgManager��ü�� ���� jIMsgManager::Run()�� ȣ�����־�� �۵��Ѵ�.
			// createThread==true�̸� �����Ǵ� jIMsgManager��ü�� szName�̶�� �����带 ������ �� �����忡�� Run()�� ȣ��ȴ�.
			//												�̶� �ݵ�� szName�� _�� �����ؾ��Ѵ�.
			// szName�� _�� �������� ������ static jIMsgManager::FrameMove()�� ȣ��ɶ� �޼����� �۵��ȴ�.
			// isCreate==true�̸� return���� �׻� �����Ѵ�.
			static jIMsgManager* Get(cstr szName, bool isCreate=false,bool createThread=false);


			// ���� �Ʒ��� ���� app xml�� IsRUN_MSG_FRAME_MOVE==0�̸� app���η������� jIMsgManager::FrameMove()�� ȣ������� �۵��Ѵ�.
			// 			<jIConsoleVar>
			// 				<jINet_OGS>
			// 					<i_IsRUN_MSG_FRAME_MOVE FLAG='' HELP='if 1 then create thread for nMech::nEVENT::jIMsgManager::FrameMove()'>1</i_IsRUN_MSG_FRAME_MOVE>
			// 				</jINet_OGS>
			// 			</jIConsoleVar>
			// IsRUN_MSG_FRAME_MOVE==true�̸� "jNet.dll"�� �ε� �ɶ� ���� �����尡 �����Ǹ鼭 �ڵ����� ȣ��ȴ�.
			static void FrameMove();

			static void for_each_all(for_each_func_t*,bool only_jIMsgManager=false);
			static jIMessage* find_if_all(find_if_func_t*,OUT jIMsgManager** ppMM,bool only_jIMsgManager=false);
		};

		//---------------------------------------------------------------
		struct jEventMessage
			//----------------------------------------------------------------
		{
			UINT uMsg;
			WPARAM wParam;
			LPARAM lParam;
			jIE* peSender, *peReceiver;
			jEventMessage():uMsg(0),wParam(0),lParam(0),peSender(0),peReceiver(0) {	}
			jEventMessage(UINT msg , WPARAM w , LPARAM l , jIE*sender,jIE* recv)	{		uMsg = msg ; wParam=w ; lParam=l ; peSender = sender;	peReceiver=recv;}
			void Set(UINT msg , WPARAM w , LPARAM l , jIE*sender,jIE* recv)	{		uMsg = msg ; wParam=w ; lParam=l ; peSender = sender;	peReceiver=recv;}
		};
#define MAKE_POINT(lParam) {short(LOWORD(lParam)), short(HIWORD(lParam)) }
		//#define MAKEWORD(low,high)	((WORD)(((BYTE)(low)) | ((WORD)((BYTE)(high))) << 8))

	}//nEVENT

}

#endif //__jMsgManager_h__
