/* 
	filename:	jMsgCommand.cpp
	coder	:	Cho Wook Rea (chowookrea@hotmail)(icq:74456993) 
	comp.	:	-MAEUMNET-
	compiler:	vc++ 6.0
	date	:	2003-11-18오후 4:32:31
	title	:	
*/
#include "stdafx.h"
#include "base\\jMsgManager.h"
#include "header\\jCriticalSection.h"
#include "Interface\jISystemPlugIn.h"
#include "interface/ITimer.h"
#include "base/jxVar.h"
#include <process.h>
#include "Interface/jIThread.h"

#include <boost/bind.hpp>

namespace nMech
{
	using namespace nThread;
	namespace nEVENT
	{
		//---------------------------------------------------------------
		class JBASE_API  jxVar_Pooled : public nDataStruct::yVectorNode<jxVar_Pooled>
			//----------------------------------------------------------------
		{
		public:
			jxVar m_Var;
			jDECLEAR_YVECTOR_MANAGER(jxVar_Pooled);
			void CopyFrom(const jxVar_Pooled& ){ assert(0);	}
			void Create(){}
			void Destroy()	{	m_Var.clear();	}
		};
		jDEFINE_YVECTOR_MANAGER(jxVar_Pooled,256,10);

		//---------------------------------------------------------------
		class jMessage : public jIMessage,public nDataStruct::yVectorNode<jMessage>
			//----------------------------------------------------------------
		{
		private:

			#define for_each_EMsgRunType(X)\
				X(eNOW_ERASE			,"지워질거")\
				X(eLOOP_MODE			," 특별한 일 없이 무한 루프로 실행됨")\
				X(eCOUNT_BASE			," 지정 횟수만큼만 실행. 2의 10승까지 가능")\
				X(eTIME_BASE			," 일정 시간 간격으로 실행.")\
				X(eTIME_AND_COUNT_BASE	," 일정 시간 간격으로 실행되면서 지정 횟수만큼 실행.")\
				X(eTIME_PERIOD			," 일정 시간동안")\

			jDEFINE_ENUM_CODE2(EMsgRunType);

#if 0
			union{
				struct 
				{
					unsigned int m_c1_isNotSleep : 1;
					unsigned int m_c3_MsgRunType :3;
					unsigned int m_c8_MsgArgCount :4;
					unsigned int m_c10_RunCount : 10;
				};
			};
#else
		bool m_c1_isNotSleep;
		bool m_c1_isActivated;
		uint8 m_c3_MsgRunType;
		uint8 m_c8_MsgArgCount;
		uint8 m_c10_RunCount;

#endif
			void __clearvar()
			{
				m_c1_isActivated=false;
				m_c1_isNotSleep=0;
				m_c3_MsgRunType=0;
				m_c8_MsgArgCount=0;
				m_c10_RunCount=0;
			}
			union
			{
				float m_fTriggerTime;
				float m_fTimePeriod;
			};
			float m_fLastTriggerTime;

		private: // 매크로
			void _doOnce()
			{ 
				m_c3_MsgRunType=eCOUNT_BASE;	
				m_c10_RunCount = 1;
			} //한번만 실행.
			void _doCount(int iCount) 
			{ 
				m_c3_MsgRunType=eCOUNT_BASE; 
				m_c10_RunCount = iCount; 
				jASSERT0(iCount < 1024);
			} // 횟수만큼 실행

			friend class jMsgManager;


		public:
			jDECLEAR_YVECTOR_MANAGER(jMessage );
			jINTERFACE_HEADER(jIMessage);

			//--------------------------------------------------------------------------
			// 메세지 콜백 함수관련
			//--------------------------------------------------------------------------
		private:
			jIMsgManager::MsgFunc_t* mf_Func;
			tcstr m_szFunc;
			jIMessage_CallbackFunc_t *m_CallbackFunc;
			void clear_MessageFunc(){ m_CallbackFunc=0;	}
		public:
			tcstr ToString(tname1024_t buf)
			{
				jt_sprintf(buf, _T("%s(%d)%s,Sleep=%d,Active=%d,iRun=%d,iTime=%f") 
					,m_szFunc,m_c8_MsgArgCount,ToString((EMsgRunType)m_c3_MsgRunType) 
					,!m_c1_isNotSleep , m_c1_isActivated ,m_c10_RunCount, m_fLastTriggerTime);
				return buf;
			}

			void Call_MessageFunc()
			{	
				if( mf_Func )
					mf_Func(this) ;
				else
					m_CallbackFunc(this);
			}


			//--------------------------------------------------------------------------
			// 메세지 인자 관련
			//--------------------------------------------------------------------------

			jxVar_Pooled	*m_pMsgArg,
				*m_pCurrMsgArg;

		public:
			jMessage()
			{
				m_pCurrMsgArg=0;
				__clearvar();
				m_pMsgArg =0;
				mf_Func=0;
				m_fTriggerTime=0;
				m_fLastTriggerTime =0;
			}
		private:
			jxVar_Pooled* NewArg(int i)
			{ 
				jASSERT0(i < 16);
				Destroy(); 
				m_pMsgArg = jxVar_Pooled::_push_back(i); 
				m_c8_MsgArgCount = i; 
				return m_pMsgArg;	
			}
		public:
			void CopyFrom(const jMessage& ){
				jASSERT0(0);
			}
			void Create()
			{ 
				m_c1_isActivated=false;
				if(m_pMsgArg)
				{
					jWARN(_T("WARNING : void jMessage::Create(): m_pMsgArg!=NULL !!!"));
					jWARN(_T("jxVar_Pooled _size()=%d, capacity=%d")
						, jxVar_Pooled::_size()
						, jxVar_Pooled::_capacity()
						);
				}
				//jASSERT0(!m_pMsgArg);	
			}
			void Destroy(){
				m_c1_isActivated=false;
				if(m_c8_MsgArgCount)
				{
					jxVar_Pooled::_erase(m_pMsgArg, m_c8_MsgArgCount);
					m_pMsgArg =0;
				}
				m_fTriggerTime=0;
				m_fLastTriggerTime =0;
				__clearvar();
				m_pCurrMsgArg=0;
				clear_MessageFunc();
			}

		};
		jDEFINE_YVECTOR_MANAGER(jMessage, 30, 20);

		//--------------------------------------------------------------------------
		// jIMessage 인터페이스들
		//--------------------------------------------------------------------------
		jMessage* jMessage::Base(){ return this;}
		bool jMessage::IsErase(){ return m_c3_MsgRunType==eNOW_ERASE;}
		bool jMessage::IsLoop() { return m_c3_MsgRunType==eLOOP_MODE; }
		bool jMessage::IsSleep(){ return !m_c1_isNotSleep;	}
		void jMessage::Erase()//이메세지를 다음 실행 할때는 삭제한다.
		{ 
			m_c3_MsgRunType=eNOW_ERASE;	
		} 
		void jMessage::DoLoop()
		{ 
			jASSERT0(m_c3_MsgRunType!=eNOW_ERASE);
			m_c3_MsgRunType=eLOOP_MODE; 
		}
		void jMessage::DoSleep()
		{ 
			//jASSERT0(m_c3_MsgRunType!=eNOW_ERASE);
			m_c1_isNotSleep=0;
		}
		void jMessage::DoWakeUp()
		{
			jASSERT0(m_c3_MsgRunType!=eNOW_ERASE);
			m_c1_isActivated=true;
			m_c1_isNotSleep=1;
			switch(m_c3_MsgRunType)
			{
			case eTIME_BASE:
			case eTIME_AND_COUNT_BASE:
				{
					m_fLastTriggerTime = nTIME::Get_ITimer()->GetCurrTime();
					break;
				}
			}
		}

		int jMessage::GetRemainCount(){ return m_c10_RunCount;}
		int jMessage::GetArgCount(){ return m_c8_MsgArgCount;}

		jVar jMessage::GetArg(int i)
		{
			if(i >= m_c8_MsgArgCount)
			{
				jvRETURN_ret(jVar(),i < m_c8_MsgArgCount,_T("%d < %d"),i , m_c8_MsgArgCount);
			}
			if(i==0)	return &m_pMsgArg->m_Var;
			return &m_pMsgArg->Next(i)->m_Var;
		}

		void jMessage::SetCallbackFunc(jIMessage_CallbackFunc_t* func)
		{
			mf_Func=0;
			m_CallbackFunc = func;
		}
		void jMessage::DoTimeBase(float fTriggerTime)
		{
			m_c3_MsgRunType = jMessage::eTIME_BASE;
			m_fTriggerTime = fTriggerTime;
			m_fLastTriggerTime = nTIME::Get_ITimer()->GetCurrTime();
		}
		void jMessage::DoCountBase(int iCount)
		{
			m_c3_MsgRunType = jMessage::eCOUNT_BASE;
			m_c10_RunCount = iCount;
		}
		void jMessage::DoTimePeriod(float fTimePeriod)
		{
			m_c3_MsgRunType = jMessage::eTIME_PERIOD;
			m_fTimePeriod = fTimePeriod;
			m_fLastTriggerTime = nTIME::Get_ITimer()->GetCurrTime();
		}
		
	
		//---------------------------------------------------------------
		class jMsgManager : public jIMsgManager,public nDataStruct::yVectorTag<jMessage>
		//----------------------------------------------------------------
		{

			uint CurrMsgCount(){ return m_aObj.size();	}
			jMessage* new_message(int iOrder , int iArgCount)
			{
				//m_aObj_CS.Lock();
				jMessage* pM = m_aObj.push_back();
				if(iArgCount) 
				{
					pM->NewArg(iArgCount);
					jASSERT0(pM->GetArgCount() == iArgCount);
				}
				//m_aObj_CS.UnLock();
				jASSERT0(pM->GetArgCount() == iArgCount);

				this->WakeThread();

				return pM;
			}
			//nUtil::jCriticalSection m_aObj_CS;

			//--------------------------------------------------------------------------
			// thread관련
			//--------------------------------------------------------------------------
		public:		tstring m_sName;
		private:
			nThread::jIThread* m_pThread;
			void jMsgManager::__jThread_job( nThread::jIThread* pT)
			{
				this->Run();

// *_* by icandoit : 2011-07-25 12:19:25
// jINet의 file send 기능 추가하면서 넣었던 코드인데 test_Server.DLL 테스트 중 오동작해서 맊음.
// 즉 패킷이 없는데 계속 circular queuer 에서 pop_front하기때문.
#if 0
				if(m_aObj.size()) 
				{
					pT->DoWake();
					return;
				}
#endif

				//슬립모드
				if(pT->GetWakeEvent()==0 || pT->GetWakeEvent()==INVALID_HANDLE_VALUE)
				{
					Sleep(3);
				}
			}
			void _startThread(bool isWakeThread,jIVar* pvTime_msec);
		public:
			void jMsgManager::WakeThread()							
			{
				if(m_pThread && m_pThread->GetWakeEvent() )m_pThread->DoWake();
			}
			void jMsgManager::StopThread()							
			{
				SAFE_RELEASE(m_pThread);
			}
			void jMsgManager::StartThread(bool isWakeThread)		{_startThread(isWakeThread,0);}
			void jMsgManager::StartTimerThread(jIVar* pvTime_msec)	{_startThread(false,pvTime_msec);}


			jMsgManager()
			{
				m_pThread=0;
			}
			~jMsgManager()
			{
				//m_pThread는 자동으로 clear됨.
			}

			jIMessage* Regist_Loop(int iOrder , MsgFunc_t* pFunc,tcstr szFunc, int iArgCount,bool isLoop=false)
			{
				//nUtil::jCriticalSection::Auto a(&m_aObj_CS);

				jMessage* pM = new_message(iOrder, iArgCount);
				assert(pM->GetArgCount()==iArgCount);
				if(isLoop)
				{
					pM->m_c3_MsgRunType=jMessage::eLOOP_MODE; 
				}
				else
					pM->_doOnce();
				pM->mf_Func = pFunc;pM->m_szFunc=szFunc;
				assert(pM->GetArgCount()==iArgCount);
				pM->m_c1_isNotSleep=1;
				return (pM);
			}

			jIMessage* Regist_TimeBase(int iOrder , MsgFunc_t* pFunc,tcstr szFunc
				, int  iArgCount , float fTriggerTime)
			{
				//nUtil::jCriticalSection::Auto a(&m_aObj_CS);
				jMessage* pM = new_message(iOrder, iArgCount);
				pM->DoTimeBase(fTriggerTime);
				pM->mf_Func = pFunc;pM->m_szFunc=szFunc;
				pM->m_c1_isNotSleep=1;
				return (pM);
			}

			jIMessage* Regist_TimePeriod(int iOrder , MsgFunc_t* pFunc,tcstr szFunc, int iArgCount , float fTimePeriod)
			{
				//nUtil::jCriticalSection::Auto a(&m_aObj_CS);
				jMessage* pM = new_message(iOrder, iArgCount);
				pM->DoTimePeriod(fTimePeriod);
				pM->mf_Func = pFunc;pM->m_szFunc=szFunc;
				pM->m_c1_isNotSleep=1;
				return (pM);
			}
			jIMessage* Regist_TimeBaseAndCount(int iOrder , MsgFunc_t* pFunc,tcstr szFunc
				, int iArgCount , float fTriggerTime,int runCount)
			{
				//nUtil::jCriticalSection::Auto a(&m_aObj_CS);
				jMessage* pM = new_message(iOrder, iArgCount);
				assert(pM->GetArgCount() == iArgCount);
				pM->m_c3_MsgRunType = jMessage::eTIME_AND_COUNT_BASE;
				pM->m_fTriggerTime = fTriggerTime;
				pM->m_fLastTriggerTime = nTIME::Get_ITimer()->GetCurrTime();
				pM->m_c10_RunCount = runCount;
				pM->mf_Func = pFunc;pM->m_szFunc=szFunc;
				pM->m_c1_isNotSleep=1;
				return (pM);
			}

			jIMessage* Regist_CountBase(int iOrder , MsgFunc_t* pFunc,tcstr szFunc
				, int iArgCount , int runCount)
			{
				//nUtil::jCriticalSection::Auto a(&m_aObj_CS);
				jMessage* pM = new_message(iOrder, iArgCount);
				pM->DoCountBase(runCount);
				pM->mf_Func = pFunc;pM->m_szFunc=szFunc;
				pM->m_c1_isNotSleep=1;
				return (pM);
			}

			virtual void Run();
			virtual void clear()
			{
				//m_aMsgSet.clear();
				nDataStruct::yVectorTag<jMessage>::clear();
			}
			void for_each(for_each_func_t* f)
			{
				m_aObj.for_each(boost::bind(f,m_sName.c_str(),this, jBOOST__PLACEHODER_1 ) );
			}
			jIMessage* find_if(find_if_func_t* f)
			{
				return m_aObj.find_if(boost::bind(f,m_sName.c_str(),this, jBOOST__PLACEHODER_1 ) );
			}

		};//class jMsgManager 

		jLIST_TYPEDEF_map(tstring, jMsgManager,s_MsgMap);
		//nUtil::jCriticalSection s_MsgMap_CS;

		jONCE_RUN(jMsgCommand_233)
		{
			jSystemPlugIn_func fn;
			fn.m_OnFrameMove = jIMsgManager::FrameMove;
			fn.m_isFirst_OnFrameMove = true;
			Get_jISystemPlugIn()->Regist(&s_MsgMap,&fn );
		}

		//static
		jSTATIC_FUNC_TAG jIMsgManager* jIMsgManager::Get(tcstr szName, bool isCreate,bool createThread)
		{
			if(createThread)
			{
				if(szName[0]!='_')
				{
					jERROR(_T("jIMsgManager::Get(%s, createTrhead==ture 이지만 이름이 _로 시작하지 않음"),szName);
					return 0;
				}
			}

			jMsgManager* pMM=0;
			s_MsgMap_it it = s_MsgMap.find(szName);
			if(it!=s_MsgMap.end())
			{
				pMM = &it->second;
				return pMM;
			}

			jvRETURN_ret(0, isCreate,_T("%s"),szName);
			{
				//jAUTO_LOCK_CS(s_MsgMap_CS);
				pMM = &s_MsgMap[szName];
			}


			pMM->m_sName = szName;

			if(createThread)
			{
				pMM->StartThread(true);
			}

			return pMM;

		}

		void jMsgManager::_startThread(bool isWakeThread,jIVar* pvTime_msec)
		{
			if(m_sName[0]!='_')
			{
				jERROR(  _T("%s, 이름이 _로 시작하지 않음"),m_sName.c_str());
				return;
			}

			if(m_pThread) return;

			jIThreadManager* pjIThreadManager= jCREATE_INTERFACE(nMech::nThread::jIThreadManager); 
			if(!pjIThreadManager)
			{
				jERROR( jFUNC1 _T("jCREATE_INTERFACE(nMech::nThread::jIThreadManager) == 0"));
				return ;
			}
			tstring sName = m_sName;//tstring(m_sName + jS(jIM));
			if(isWakeThread)
			{
				nThread::thread_func_t f = boost::bind(&jMsgManager::__jThread_job,this,jBOOST__PLACEHODER_1 );
				m_pThread = pjIThreadManager->Run_Wake(f,jS(jIM),sName.c_str() );
				return;
			}
			if(pvTime_msec)
			{
				nThread::thread_func_t f = boost::bind(&jMsgManager::__jThread_job,this,jBOOST__PLACEHODER_1 );
				m_pThread = pjIThreadManager->Run_Timer(f,jS(jIM),sName.c_str() ,pvTime_msec);
				return;
			}

			nThread::thread_func_t f = boost::bind(&jMsgManager::__jThread_job,this,jBOOST__PLACEHODER_1 );
			m_pThread = pjIThreadManager->Run(f,jS(jIM),sName.c_str() , false);
			return ;
		}

		//static 
		jSTATIC_FUNC_TAG void jIMsgManager::FrameMove()
		{
			//jAUTO_LOCK_CS(s_MsgMap_CS);// s_MsgMap에서 erase()는 하지 않으므로 락을 걸필요없다.
			s_MsgMap_it it= s_MsgMap.begin() , ie = s_MsgMap.end();
			for( ; it!=ie; ++it)
			{
				if(it->first[0] == '_')
					//if(!strncmp(it->first.c_str(), "__", 2))//매뉴얼메세지큐. 따로 호출된다.
					continue;
				it->second.Run();
			}

		}

		//--------------------------------------------------------------------------
		void jMsgManager::Run()
			//--------------------------------------------------------------------------
		{
			iterator it = m_aObj.begin(), ie = m_aObj.end(); // 락프리. 락걸필요 없다. 중간에 insert, erase()되어도 됨.
			for( ; it!=ie ; )
			{
				if(it->IsSleep() || !it->m_c1_isActivated)
				{
					++it;
					continue;
				}

				switch( it->m_c3_MsgRunType )
				{
				case jMessage::eNOW_ERASE:
					{
						break;
					}
				case jMessage::eLOOP_MODE:
					{
						if(!it->IsErase())
							it->Call_MessageFunc();

						break;
					}
				case jMessage::eCOUNT_BASE:
					{
						if(it->m_c10_RunCount >0)
						{
							it->Call_MessageFunc();
							--it->m_c10_RunCount;
						}
						if(it->m_c10_RunCount <=0)
						{
							it->Erase();
						}
						break;
					}
				case jMessage::eTIME_BASE:
					{
						float fCurrTime = nTIME::Get_ITimer()->GetCurrTime();
						float fPass = fCurrTime - it->m_fLastTriggerTime	;
						if( fPass >  it->m_fTriggerTime)
						{
							it->Call_MessageFunc();
							it->m_fLastTriggerTime = fCurrTime;
						}
						break;
					}
				case jMessage::eTIME_AND_COUNT_BASE:
					{
						if( it->m_c10_RunCount >0)
						{
							float fCurrTime = nTIME::Get_ITimer()->GetCurrTime();
							float fPass = fCurrTime - it->m_fLastTriggerTime ;
							if( fPass >  it->m_fTriggerTime)
							{
								it->Call_MessageFunc();
								it->m_fLastTriggerTime = fCurrTime;
								--it->m_c10_RunCount;
							}
						}
						if(it->m_c10_RunCount <=0)
							it->Erase();
						break;
					}
				case  jMessage::eTIME_PERIOD:
					{
						float fCurrTime = nTIME::Get_ITimer()->GetCurrTime();
						float fPass = fCurrTime - it->m_fLastTriggerTime ;
						if( fPass <  it->m_fTriggerTime)
						{
							it->Call_MessageFunc();
						}
						else
						{
							it->Erase();
							it->Call_MessageFunc();
						}

						break;
					}
				}//switch( it->m_c3_MsgRunType )

// 				if(it->IsErase())
// 				{
					//jAUTO_LOCK_CS(m_aObj.m_CS);
					//nUtil::jCriticalSection::Auto a(&m_aObj_CS);
					if(it->IsErase())
					{
						it = m_aObj.erase(it);
					}
					else	
						++it;
// 				}
// 				else	
// 					++it;
			}
		}//void jMsgManager::Run()

		//static 
		jSTATIC_FUNC_TAG void jIMsgManager::for_each_all(for_each_func_t* f,bool only_jIMsgManager)
		{
			jRETURN(f);
			s_MsgMap_it it = s_MsgMap.begin(),ie =s_MsgMap.end();
			for(;it!=ie;++it)
			{
				jMsgManager* pMM= &it->second;
				f(it->first.c_str(),pMM,0);
				if(only_jIMsgManager) continue;
				pMM->for_each(f);
			}

		}
	
		jSTATIC_FUNC_TAG jIMessage* jIMsgManager::find_if_all(find_if_func_t* f,OUT jIMsgManager** ppMM,bool only_jIMsgManager)
		{
			jRETURN_ret(0,f);
			s_MsgMap_it it = s_MsgMap.begin(),ie =s_MsgMap.end();
			for(;it!=ie;++it)
			{
				jMsgManager* pMM= &it->second;
				if(f(it->first.c_str(),pMM,0) ) 
				{
					if(ppMM) *ppMM = pMM;
					return 0;
				}
				if(only_jIMsgManager) continue;
				jIMessage* pM = pMM->find_if(f);
				if(!pM) continue;
				if(ppMM)*ppMM=pMM;
				return pM;
			}
			return 0;
		}


		void print_jIMsgManager(tcstr szMM,jIMsgManager* pMM, jIMessage*_pM)
		{
			if(!_pM)
			{
				jLOG_T("<%s>, size=%d",szMM,pMM->CurrMsgCount());
			}
			else
			{
				jMessage* pM = _pM->Base();
				tname1024_t buf;
				jLOG_T("\t%s",pM->ToString(buf));
			}
		}

		JBASE_API bool jIMessage_print(const std::vector<std::tstring>& arg)
		{
			jIMsgManager::for_each_all(print_jIMsgManager);
			jLOG_T("jIMessage.jxVar_Pooled::_size=%d",jxVar_Pooled::_size());
			return true;
		}


	}//nEVENT

}



