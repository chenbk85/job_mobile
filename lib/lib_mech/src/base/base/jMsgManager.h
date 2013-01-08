/* 
	filename:	jMsgManager.h
	coder	:	Cho Wook Rea (chowookrea@hotmail)(icq:74456993) 
	comp.	:	-MAEUMNET-
	compiler:	vc++ 6.0
	date	:	2003-11-18오후 4:32:17
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
	/* 메세지가 Regist_CountBase로 호출될때 남은 루프수. 1이면 마지막 호출이다.*/\
	virtual int GetRemainCount()##x \
	virtual int GetArgCount() ##x \
	virtual jVar GetArg(int i) ##x \
	virtual void SetCallbackFunc(jIMessage_CallbackFunc_t* func)##x \
	\
	virtual void Erase() ##x \
	virtual void DoLoop() ##x \
	virtual void DoSleep() ##x \
	virtual void DoWakeUp() ##x \
	virtual void DoTimeBase(float fTriggerTime)##x /*fTriggerTime 마다 메세지가 호출됨*/\
	virtual void DoCountBase(int iCount)##x /* iCount만큼 호출후 메세지 끝냄*/\
	virtual void DoTimePeriod(float fTimePeriod)##x /* fTimePeriod동안 메세지 호출후 중단 */\

		jINTERFACE_END(jIMessage);


		typedef void for_each_func_t(tcstr szMM,jIMsgManager* pMM, jIMessage*pM);
		typedef bool find_if_func_t(tcstr szMM,jIMsgManager* pMM, jIMessage*pM);

#define jFUNC_Msg(FUNC) FUNC , jS(FUNC)

		struct JBASE_API jIMsgManager
		{
			typedef void MsgFunc_t (jIMessage*); 

			// isLoop== false이면 한번만 실행되는 메세지작업을 생성한다.
			virtual jIMessage* Regist_Loop(int iOrder , MsgFunc_t* pFunc,tcstr szFunc, int iArgCount, bool isLoop=false)=0;

			// fTriggerTime마다 메세지 작업을 호출
			virtual jIMessage* Regist_TimeBase(int iOrder , MsgFunc_t* pFunc,tcstr szFunc, int iArgCount , float fTriggerTime)=0;
			// fTimePeriod동안 메세지 작업을 호출호 중단
			virtual jIMessage* Regist_TimePeriod(int iOrder , MsgFunc_t* pFunc,tcstr szFunc, int iArgCount , float fTimePeriod)=0;


			//fTriggerTime마다 메세지를 호출하되 runCount만큼만 호출하고 메세지 작업 끝냄 [ 단위 : 초 sec ]
			virtual jIMessage* Regist_TimeBaseAndCount(int iOrder, MsgFunc_t* pFunc,tcstr szFunc, int iArgCount , float fTriggerTime,int runCount)=0;
			// runCount만큼 호출되고 메세지 작업 끝냄.
			virtual jIMessage* Regist_CountBase(int iOrder , MsgFunc_t* pFunc,tcstr szFunc, int iArgCount , int runCount)=0;

			// jIMsgManager* Get(cstr szName, ...)으로 jIMsgManager객체 생성시 이름이 '_' 로 시작하면 Run()을 반드시 호출해줘야한다.
			// 만약 jIMsgManager* Get()에서 createThread=true로 호출되었다면 Run()을 호출 할 필요가 없다.
			virtual void Run()=0;
			virtual void clear()=0;
			virtual uint CurrMsgCount()=0;
			virtual void StopThread()=0;
			virtual void StartThread(bool isWakeThread)=0;
			virtual void StartTimerThread(jIVar* pvTime_msec)=0;
			virtual void WakeThread()=0;
			virtual void for_each(for_each_func_t*)=0;
			virtual jIMessage* find_if(find_if_func_t*)=0;

			// jIMsgManager객체 생성.
			// szName이 _ 로 시작하면 그 jIMsgManager객체는 따로 jIMsgManager::Run()을 호출해주어야 작동한다.
			// createThread==true이면 생성되는 jIMsgManager객체는 szName이라는 스레드를 생성후 그 스레드에서 Run()이 호출된다.
			//												이때 반드시 szName이 _로 시작해야한다.
			// szName이 _로 시작하지 않으면 static jIMsgManager::FrameMove()가 호출될때 메세지가 작동된다.
			// isCreate==true이면 return값은 항상 성공한다.
			static jIMsgManager* Get(cstr szName, bool isCreate=false,bool createThread=false);


			// 만약 아래와 같이 app xml에 IsRUN_MSG_FRAME_MOVE==0이면 app메인루프에서 jIMsgManager::FrameMove()를 호출해줘야 작동한다.
			// 			<jIConsoleVar>
			// 				<jINet_OGS>
			// 					<i_IsRUN_MSG_FRAME_MOVE FLAG='' HELP='if 1 then create thread for nMech::nEVENT::jIMsgManager::FrameMove()'>1</i_IsRUN_MSG_FRAME_MOVE>
			// 				</jINet_OGS>
			// 			</jIConsoleVar>
			// IsRUN_MSG_FRAME_MOVE==true이면 "jNet.dll"이 로딩 될때 관련 스레드가 생성되면서 자동으로 호출된다.
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
