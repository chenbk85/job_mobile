/* file : jEventNode.cpp
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2006-01-16 17:16:15
title : 
desc : 

*/

#include "stdafx.h"
#include "jEventNode.h"
#include "interface\\jILog.h"
#include "interface/xml/jIXml.h"
#include "Mmsystem.h"
#include "interface/itimer.h"
#include "base/jXmlDictionary.h"


namespace nMech
{
	namespace nEVENT
	{
		static jIMsgManager* s_pEvent_MsgManager;

		struct jEventRoot : public jIEventRoot,public nDataStruct::yVectorNode<jEventRoot>
		{
			jDECLEAR_YVECTOR_MANAGER(jEventRoot);
			void Create()
			{
				m_isActive=true;
				m_EventNodeList.clear(); 
				m_peEventList=0; 
				m_pEventKey=0;
			}
			void Destroy()
			{
				m_EventNodeList_it it = m_EventNodeList.begin() , ie = m_EventNodeList.end();
				itFOR(it,ie)
				{
					jIEventNode * pEvent = *it;
					if(!pEvent) continue;
					jRTTI::Del(pEvent);
					*it = 0;
				}
				m_EventNodeList.clear();
				jIF_LOG(jx(EVR))
				{
					TCHAR buf[1024];
					m_peEventList->SXPathToString(buf,0);
					jLOG(jFUNC1 _T(" %s"), buf);
				}
				if(m_pMsg)
				{
					m_pMsg->Erase();
					m_pMsg->GetArg(0)->SetUserData(0);
				}
				m_pEventKey=0;
			}
			void CopyFrom(const jEventRoot& y)
			{
				assert(0);
			}

			jIMessage* Init(jIE* peMsgList , void* eventKey ,StringID iRunMode)
			{
				m_pEventKey = eventKey;
				m_iRunMode = iRunMode;
				m_peEventList= peMsgList; 
				m_EventNodeList.resize(peMsgList->size());
				jIE* it = peMsgList->begin();
				DWORD uCurrTime = timeGetTime();/*(int)nTIME::Get_ITimer()->GetCurrTime()*1000;//*/ 

				m_pMsg = s_pEvent_MsgManager->Regist_Loop(0,jFUNC_Msg(jSchedule),1);
				m_pMsg->GetArg(0)->SetUserData(static_cast<jIEventRoot*>(this));
				m_pMsg->DoWakeUp();

				jrFOR(it)
				{
					if( it->IsContents(g_XmlNULL) ) continue;

					jIEventNode* pEvent = (jIEventNode*)jRTTI::New(it->GetTagName() , _T("jIEventNode"));
					if(!pEvent) continue;
					m_EventNodeList[it->GetOrder()] = pEvent;
					pEvent->m_pRoot = this;
					if(!pEvent->OnInit(it , uCurrTime,eventKey))
					{
						m_EventNodeList[it->GetOrder()]=0;
						jRTTI::Del(pEvent);
					}
					pEvent->OnPostInit(m_pMsg);

				}
				return m_pMsg;
			}

			static void jSchedule(jIMessage* pMsg);

			virtual jEventRoot* Base(){ return this;}
			virtual bool IsClear();
			virtual void SetActive(bool is)
			{
				m_isActive = is;
				m_EventNodeList_it it = m_EventNodeList.begin() , ie = m_EventNodeList.end();
				for( ; it != ie ; ++it)
				{
					jIEventNode * pEvent = *it;
					if(!pEvent) continue;
					pEvent->SetActive(is);
				}
			}
			virtual void SetEventNode(int iOrder , jIEventNode* pEN)	{		m_EventNodeList[iOrder] = pEN;	}
			virtual jIEventNode* GetEventNode(int iOrder)
			{
				if( (m_EventNodeList.size() <= iOrder) || 0 > iOrder) return 0;
				return m_EventNodeList[iOrder];
			}
			jIE* m_peEventList;

		private:
			StringID m_iRunMode;
			jIMessage* m_pMsg;
			void* m_pEventKey;
			bool m_isActive;
			jLIST_TYPEDEF_vector(jIEventNode* , m_EventNodeList);
		};

		jDEFINE_YVECTOR_MANAGER(jEventRoot,128,10);

		jLIST_TYPEDEF_YVECTOR_typedef(jEventRoot, jEventRoot_yvector);

		//--------------------------------------------------------------------------
		struct jEventManager
			//--------------------------------------------------------------------------
		{
			jLIST_TYPEDEF_map(void*,jEventRoot_yvector_t , m_mapERByEventKey);
			jEventManager()
			{
				s_pEvent_MsgManager = jIMsgManager::Get(_T("jIEventNode"),true);
			}

			jIMessage* CallEvent(jIE* peMsgList,void* eventKey,StringID iRunMode) //iRunMode = jPlayer.xml에서 <jIEventNode_RunMode>
			{

				if(iRunMode==jx(NULL))
				{
					jIVar* pvRunMode = peMsgList->PersistAttr(_T("EventRunMode"),jIVar::EDStringID,_T("DEFAULT"));
					iRunMode = pvRunMode->Get_StringID();
				}

				jEventRoot_yvector_t* pEventRoot_yvector= &m_mapERByEventKey[eventKey];
				jIF_LOG(jx(ER_Start))
				{
					jLOG(jFUNC1 _T("%s : prev Event cnt = %d"), peMsgList->GetTagName() , pEventRoot_yvector->size());
				}
				if(iRunMode == jx(CANCEL_PREV_EVENT) )
				{
					pEventRoot_yvector->clear();
				}

				if(!peMsgList) return 0;

				jEventRoot* pEventRoot = pEventRoot_yvector->push_back();
				jIMessage* pMsg = pEventRoot->Init(peMsgList ,eventKey,iRunMode);

				if( iRunMode == jx(WAIT_PREV_EVENT))
				{
					if(pEventRoot_yvector->size()>1)
					{
						//pMsg->DoSleep();
						pEventRoot->SetActive(false);
					}
				}
				return pMsg;

			}
			void UnRegistKey(void* eventKey)
			{
				m_mapERByEventKey_it it = m_mapERByEventKey.find(eventKey);
				if(m_mapERByEventKey.end() != it)
				{
					it->second.clear();
					m_mapERByEventKey.erase(it);
				}

			}
		};

		jEventManager g_jEventManager;

		//--------------------------------------------------------------------------
		void jEventRoot::jSchedule(jIMessage* pMsg)
			//--------------------------------------------------------------------------
		{

			jIEventRoot* pEventRoot = (jIEventRoot*)pMsg->GetArg(0)->GetUserData();
			if(!pEventRoot) return;
			jEventRoot* pER = pEventRoot->Base();
			if(!pER->m_isActive)
			{
				pMsg->DoLoop();
				return;
			}

			bool isClear=true;
			m_EventNodeList_it it = pER->m_EventNodeList.begin() , ie = pER->m_EventNodeList.end();
			itFOR(it,ie)
			{
				jIEventNode * pEvent = *it;
				if(!pEvent) continue;
				if(pEvent->FrameMove() || pEvent->IsQuit() )
				{
					jIF_LOG(jx(EVR))
					{
						jLOG(_T("%s_%s : Destroy"), pEvent->m_peMsg->GetParent()->GetTagName(), pEvent->m_peMsg->GetTagName());
					}
					jRTTI::Del(pEvent);
					*it = 0;
				}
				else
					isClear= false;
			}
			if( isClear ) 
			{
				jEventRoot* pNextER = pER->_pR;
				for ( ; pNextER ; pNextER=pNextER->_pR)
				{
					if( pNextER->m_iRunMode != jx(WAIT_PREV_EVENT)) continue;
					jIMessage* pMsg = pNextER->m_pMsg;
					assert(pMsg);
					//pMsg->DoWakeUp();

					pNextER->SetActive(true);
					jIF_LOG(jx(EVR))
					{
						jLOG(jFUNC1 _T("Activeate : %s"), pNextER->m_peEventList->GetTagName());
					}
					break;
				}

				g_jEventManager.m_mapERByEventKey[pER->m_pEventKey].erase(pER);
				jIF_LOG(jx(EVR))
				{
					//jLOG(_T("jEventRoot %s : Destroy"), pER->m_peEventList->GetTagName() );
				}
			}
		}

		//--------------------------------------------------------------------------
		bool jEventRoot::IsClear()
			//--------------------------------------------------------------------------
		{
			m_EventNodeList_it it = m_EventNodeList.begin() , ie = m_EventNodeList.end();
			for( ; it != ie ; ++it)
			{
				if( *it != 0)
				{
					return false;
				}
			}
			return true;
		}

		//--------------------------------------------------------------------------
		void jIEventNode::Destroy()	
			//--------------------------------------------------------------------------
		{		
			m_eState = eDELETED;	
		}

		//--------------------------------------------------------------------------
		bool jIEventNode::OnInit(jIE* pE,DWORD uWorldStartTime ,void* v)
			//--------------------------------------------------------------------------
		{
			m_isQuit=false;
			m_pMsg = 0;
			m_iPassTime=0;
			m_peMsg = pE;
			m_uStartTimeWorld = uWorldStartTime;
			jIVar* pV ;
			pV = m_peMsg->GetAttrVar(_T("StartTime"));
			m_iStartTime = pV? pV->intValue() : 0;
			pV = m_peMsg->GetAttrVar(_T("EndTime"));
			m_iEndTime = pV ? pV->intValue() : 0;

			pV= pE->GetAttrVar(_T("Loop"));
			m_iLoop = pV ? pV->intValue() : 0 ;
			m_eState = eREADY;
			return true;
		}


		//--------------------------------------------------------------------------
		void jIEventNode::SetActive(bool is)
			//--------------------------------------------------------------------------
		{
			if(is)
			{
				if(IsActive()) return;
				m_eState = eGOTO_START;
				m_uStartTimeWorld = /*(int)nTIME::Get_ITimer()->GetCurrTime()*1000;// */ timeGetTime();
			}
			else
			{
				m_eState = eDEACTIVATE;
			}
		}

		//--------------------------------------------------------------------------
		int  jIEventNode::FrameMove() // 1을 리턴하면 모든 메세지처리가 끝났다.
			//--------------------------------------------------------------------------
		{
			switch(m_eState )
			{
			case eDEACTIVATE:
				{
					return 0;
				}
			case eREADY:
				{
					//jLOG(_T("%s_%s : eREADY"), m_peMsg->GetParent()->GetTagName(), m_peMsg->GetTagName());
					if(m_iStartTime <= 0 )
					{
						OnExcuteStart();
						m_eState = eGOTO_END;
					}
					else
					{
						m_eState = eGOTO_START;
					}
				}
				return 0;
			case eGOTO_START:
				{
					jIF_LOG(jx(EVR))
					{
						jLOG(jFUNC1 _T("%s_%s : eGOTO_START"), m_peMsg->GetParent()->GetTagName(), m_peMsg->GetTagName());
					}

					DWORD iCurrTime = timeGetTime();/*(int)nTIME::Get_ITimer()->GetCurrTime()*1000;//*/ 
					m_iPassTime = iCurrTime-m_uStartTimeWorld;
					if(m_iPassTime < m_iStartTime) return 0;
					OnExcuteStart();

					m_iPassTime = 0;
					m_uStartTimeWorld = iCurrTime;
					m_eState = eGOTO_END;
				}
				return 0;
			case eGOTO_RESTART:
				{
					jIF_LOG(jx(EVR))
					{
						jLOG(jFUNC1 _T("%s_%s : eGOTO_RESTART"), m_peMsg->GetParent()->GetTagName(), m_peMsg->GetTagName());
					}

					DWORD iCurrTime = /*(int)nTIME::Get_ITimer()->GetCurrTime()*1000;// */ timeGetTime();
					m_iPassTime = iCurrTime-m_uStartTimeWorld;
					if(m_iPassTime < m_iStartTime) return 0;
					OnExcuteReStart();
					m_iPassTime = 0;
					m_uStartTimeWorld = iCurrTime;
					m_eState = eGOTO_END;

				}
				return 0;
			case eGOTO_END:
				{
					//jLOG(_T("%s_%s : eGOTO_END"), m_peMsg->GetParent()->GetTagName(), m_peMsg->GetTagName());
					DWORD iCurrTime = /*(int)nTIME::Get_ITimer()->GetCurrTime()*1000;//*/ timeGetTime();
					m_iPassTime =  iCurrTime- m_uStartTimeWorld;
					if(m_iPassTime > 1000*60 && m_iEndTime<=0)
					{
						return 1;
					}
					int iRet = OnFrameMove();
					if(m_iEndTime<=0)
					{
						return iRet;
					}

					if(m_iPassTime < m_iEndTime) return 0;

					m_iPassTime =0;
					OnExcuteEnd();
					if(m_iLoop >0)
					{
						m_uStartTimeWorld = iCurrTime;
						--m_iLoop;
						m_eState = eGOTO_RESTART;
					}
					else
					{
						m_eState = eEND;
						return 1;
					}
				}
				return 0;
			}
			return 1; // 이 메세지는 즉시삭제됨.
			//jLOG(_T("%s_%s : Goto Destroy"), m_peMsg->GetParent()->GetTagName(), m_peMsg->GetTagName());
		}


		//--------------------------------------------------------------------------
		jIMessage* jIEventNode::CallEvent(jIE* peMsgList, void* eventKey ,StringID iRunMode)
			//--------------------------------------------------------------------------
		{
			return g_jEventManager.CallEvent(peMsgList, eventKey,iRunMode);
		}

		//--------------------------------------------------------------------------
		void jIEventNode::CancleMessage(jEventRoot* pEV)
			//--------------------------------------------------------------------------
		{
			assert(0);
		}

		//--------------------------------------------------------------------------
		void jIEventNode::UnRegistKey(void* key)
			//--------------------------------------------------------------------------
		{
			g_jEventManager.UnRegistKey(key);
		}

	}
}

