/* file : jQueueManger.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-04 15:36:27
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "header/jCriticalSection.h"
#include "header/MultiThreadSync.h"
#include "jQueueManger.h"

#define __lock_this__ jAUTO_LOCK_CS1(m_CS);
//#define __lock_this__ 

#define iPER_LOG_COUNT 10

namespace nMech
{
	namespace nNET
	{
		namespace nUTIL
		{
			//F(DATA_SIZE , OBJ_SIZE, SLOT_SIZE)
			#define for_each_QUEUE_SIZE_SLOT_INFO(F)\
				F(64,512,128) \
				F(128,512,128) \
				F(256,512,128) \
				F(512,128,128) \
				F(1024,128,128) \
				F(2048,32,128) \
				F(4096,16,128) \
				F(8096,8,128) \
				F(16384,8,128) \

			// ¡÷¿« : 16384 == MAX_BUFFER_LENGTH

#define DECL_jNetQueueData(DATA_SIZE, OBJ_SIZE, SLOT_SIZE) \
			struct jNetQueueData_##DATA_SIZE : public _jNetQueueData ,public nDataStruct::ySimpleNode<jNetQueueData_##DATA_SIZE> \
			{\
				jDECLEAR_SIMPLE_MEMORY(jNetQueueData_##DATA_SIZE);\
				enum{ eDATA_SIZE= DATA_SIZE, };\
				BYTE	Data[eDATA_SIZE];\
				void Create(){m_pObj=0;} \
				void Destroy(){m_pObj=0;}\
				void CopyFrom(const jNetQueueData_##DATA_SIZE& o){jASSERT0(0);}\
				virtual int GetBufferSize(){ return eDATA_SIZE;}\
				virtual BYTE* GetBuffer(){ return Data;}\
			};\
			jDEFINE_SIMPLE_MEMORY(jNetQueueData_##DATA_SIZE, OBJ_SIZE,SLOT_SIZE);\
			static _jNetQueueData* _new_data_##DATA_SIZE(){return jNetQueueData_##DATA_SIZE::_push_back();}\
			static void _delete_data_##DATA_SIZE(_jNetQueueData* p){ jNetQueueData_##DATA_SIZE::_erase(static_cast<jNetQueueData_##DATA_SIZE*>(p)); }

			for_each_QUEUE_SIZE_SLOT_INFO(DECL_jNetQueueData);

			static _data_size_alloc_info g_data_size_alloc_info[]=
			{
				#define DEF_jNetQueueData_SIZE_ARRAY(DATA_SIZE,A,B) { DATA_SIZE,_new_data_##DATA_SIZE ,_delete_data_##DATA_SIZE },
				for_each_QUEUE_SIZE_SLOT_INFO(DEF_jNetQueueData_SIZE_ARRAY)
				{0,0,0}
			};

			_data_size_alloc_info *jCircularQueueBuffer::get_data_size_alloc_info(int iLen)
			{
				const int g_iTot = ARRAY_SIZE(g_data_size_alloc_info);
				for(int i=0; i< g_iTot ; ++i)
				{
					_data_size_alloc_info *it = g_data_size_alloc_info+i;
					if(it->iSize >= iLen) 
						return it;
				}
				return 0;
			}

			_jNetQueueData*		jCircularQueueBuffer::push_back(int iSize)
			{
#ifdef _DEBUG_jCircularQueueBuffer_COUNT
				jLOG(jFUNC1 _T("(%d) begin mQueueHead(%d) mQueueTail(%d) ,m_iSizeQueue(%d), iSize=%d"),m_iPushCount++,mQueueHead ,mQueueTail ,m_iSizeQueue ,iSize);
#endif
				

				_jNetQueueData *pCurr;
				{
					//__lock_this__
					DWORD iTempTail = (mQueueTail + 1) % m_iSizeQueue;
					jvRETURN_ret(0, iTempTail != mQueueHead , _T("size = %d, iTempTail=%d"),iSize,iTempTail)	;

					_data_size_alloc_info* pInfo = get_data_size_alloc_info(iSize);
					jvRETURN_ret(0,pInfo,_T("get_data_size_alloc_info(%d)"),iSize);
// #ifdef _DEBUG
// 					jLOG(jFUNC1 _T("pInfo->iSize = %d"),pInfo->iSize);
// #endif
					pCurr = pInfo->new_func();
					jvRETURN_ret(0, pCurr , _T("alloc error : size = %d"),iSize);
					m_QueueBuffer[iTempTail] = pCurr;
					mQueueTail = iTempTail;
				}
#ifdef DEBUG
				memset(pCurr->GetBuffer(),0,pCurr->GetBufferSize());
#endif

#ifdef _DEBUG_jCircularQueueBuffer_COUNT
				jLOG(jFUNC1 _T("(%d) end mQueueHead(%d) mQueueTail(%d) ,m_iSizeQueue(%d), iSize=%d"),m_iPushCount-1,mQueueHead ,mQueueTail ,m_iSizeQueue ,iSize);
#endif

				return pCurr;

			}
			_jNetQueueData* jCircularQueueBuffer::pop_front()
			{
#ifdef _DEBUG_jCircularQueueBuffer_COUNT
				jLOG(jFUNC1 _T("(%d) mQueueHead(%d) mQueueTail(%d) ,m_iSizeQueue(%d)"),m_iPopCount++,mQueueHead ,mQueueTail ,m_iSizeQueue);
#endif
				//__lock_this__
#if 1
				if (mQueueHead == mQueueTail) return 0;
#else
				jvRETURN_ret(0,mQueueHead != mQueueTail,_T("%d != %d"),mQueueHead , mQueueTail);
#endif

				DWORD TempHead = (mQueueHead + 1) % m_iSizeQueue;
				_jNetQueueData* pCurr = m_QueueBuffer[TempHead];
				m_QueueBuffer[TempHead]=0;
				mQueueHead = TempHead;
// #ifdef _DEBUG
// 				jLOG(jFUNC1 _T("GetBufferSize()=%d"),pCurr->GetBufferSize());
// #endif

				return pCurr;
			}

			void jCircularQueueBuffer::_PostCreate(int iSizeQueue)
			{
				jCircularQueueBuffer_IOCP_NEW_DELELTE_DEBUG();
				jASSERT0(!m_QueueBuffer);
				m_iSizeQueue = iSizeQueue;
				typedef _jNetQueueData* _jNetQueueData_p;
				m_QueueBuffer= new _jNetQueueData_p[m_iSizeQueue];

				memset(m_QueueBuffer, 0, sizeof(_jNetQueueData_p)*m_iSizeQueue );
				mQueueHead	= 0;
				mQueueTail	= 0;
#ifdef _DEBUG_jCircularQueueBuffer_COUNT
				m_iPushCount=0;
				m_iPopCount=0;
#endif
			}
			void jCircularQueueBuffer::_PostDelete()
			{
				if(!m_QueueBuffer) return;
				jRETURN(isReady());

				jCircularQueueBuffer_IOCP_NEW_DELELTE_DEBUG();

				End();
				__lock_this__
					SAFE_DELETE_ARRAY(m_QueueBuffer);

			}

			jCircularQueueBuffer::~jCircularQueueBuffer(VOID)
			{
				_PostDelete();
			}

			bool jCircularQueueBuffer::Begin(VOID)
			{
				jRETURN_ret(FALSE,isReady());
				jCircularQueueBuffer_IOCP_NEW_DELELTE_DEBUG();

				__lock_this__
				memset(m_QueueBuffer, 0, sizeof(_jNetQueueData*)*m_iSizeQueue) ;
				mQueueHead	= 0;
				mQueueTail	= 0;
				return TRUE;
			}

			bool jCircularQueueBuffer::End(VOID)
			{
				jRETURN_ret(0,isReady());

				jCircularQueueBuffer_IOCP_NEW_DELELTE_DEBUG();

				__lock_this__
				for(int i=0; i< m_iSizeQueue; ++i)
				{
					_jNetQueueData* it = m_QueueBuffer[i];
					if(it)
					{
						get_data_size_alloc_info(it->m_iLength)->delete_func(it);
					}
				}
				memset(m_QueueBuffer, 0, sizeof(_jNetQueueData*)*m_iSizeQueue);
				return true;
			}

			BYTE* jCircularQueueBuffer::Push(void *object, BYTE *data, jPacketLen_t dataLength)
			{
				jRETURN_ret(0,isReady());
				jRETURN_ret(0,(object && data));
				__lock_this__
				_jNetQueueData* pCurr =push_back(dataLength);
				jRETURN_ret(0,pCurr);

				pCurr->m_pObj		= object;
				pCurr->m_iLength	= dataLength;
				BYTE* pBuff = pCurr->GetBuffer();
				memcpy(pBuff, data, dataLength);
				return pBuff;
			}

			BYTE* jCircularQueueBuffer::Push(void *object, jPacketNum_t dwProtocol, BYTE *data, jPacketLen_t dataLength)
			{
				jRETURN_ret(0,isReady());
				jRETURN_ret(0,(object && data) );
				__lock_this__
				_jNetQueueData* pCurr =push_back(dataLength);
				jRETURN_ret(0,pCurr);
				pCurr->m_pObj		= object;
				pCurr->m_iLength	= dataLength;
				pCurr->dwProtocolNumber	= dwProtocol;
				BYTE* pBuff = pCurr->GetBuffer();
				memcpy(pBuff, data, dataLength);
				return pBuff;
			}

			BYTE *jCircularQueueBuffer::Push(void *object, BYTE *data, jPacketLen_t dataLength, jIP_Address* pIP)
			{
				jRETURN_ret(0,isReady());
				jRETURN_ret(0,(object && data) );
				__lock_this__

				_jNetQueueData* pCurr =push_back(dataLength);
				jRETURN_ret(0,pCurr);
				pCurr->m_pObj		= object;
				pCurr->m_iLength	= dataLength;
				if(pIP) pCurr->RemoteAddress=*pIP;
				BYTE* pBuff = pCurr->GetBuffer();
				memcpy(pBuff, data, dataLength);
				return pBuff;
			}

			BYTE *jCircularQueueBuffer::Push(void *object, jPacketNum_t dwProtocol, BYTE *data, jPacketLen_t dataLength, jIP_Address* pIP)
			{
				jRETURN_ret(0,isReady());
				jRETURN_ret(0,(object && data) );
				__lock_this__

				_jNetQueueData* pCurr =push_back(dataLength);
				jRETURN_ret(0,pCurr);
				pCurr->m_pObj		= object;
				pCurr->m_iLength	= dataLength;
				pCurr->dwProtocolNumber	= dwProtocol;
				if(pIP) pCurr->RemoteAddress=*pIP;

				BYTE* pBuff = pCurr->GetBuffer();
				memcpy(pBuff, data, dataLength);
				return pBuff;
			}

			bool jCircularQueueBuffer::Pop(VOID)
			{
				jRETURN_ret(0,isReady());

				__lock_this__
				_jNetQueueData* pCurr = pop_front();
				jRETURN_P_ret(iPER_LOG_COUNT,0,pCurr);
				get_data_size_alloc_info(pCurr->m_iLength)->delete_func(pCurr);
				return true;
			}

			bool jCircularQueueBuffer::Pop(VOID **object, BYTE *data, jPacketLen_t &dataLength)
			{
				jRETURN_ret(0,isReady());
				jRETURN_ret(0,(object && data) );
				__lock_this__

				_jNetQueueData* pCurr = pop_front();
				jRETURN_P_ret(iPER_LOG_COUNT,0,pCurr);

				dataLength	= pCurr->m_iLength;
				*object		= pCurr->m_pObj;
				memcpy(data, pCurr->GetBuffer(), pCurr->m_iLength);
				get_data_size_alloc_info(pCurr->m_iLength)->delete_func(pCurr);
				return true;
			}

			bool jCircularQueueBuffer::Pop(VOID **object, jPacketNum_t &dwProtocol, BYTE *data, jPacketLen_t &dataLength)
			{
				jRETURN_ret(0,isReady());
				jRETURN_ret(0,(object && data) );
				__lock_this__

				_jNetQueueData* pCurr = pop_front();
				jRETURN_P_ret(iPER_LOG_COUNT,0,pCurr);

				dataLength	= pCurr->m_iLength;
				*object		= pCurr->m_pObj;
				dwProtocol	= pCurr->dwProtocolNumber;
				memcpy(data, pCurr->GetBuffer(), pCurr->m_iLength);
				get_data_size_alloc_info(pCurr->m_iLength)->delete_func(pCurr);
				return true;
			}

			bool jCircularQueueBuffer::Pop(VOID **object, BYTE *data, jPacketLen_t &dataLength, jIP_Address* pIP)
			{
				jRETURN_ret(0,isReady());
				jRETURN_ret(0,(object && data) );
				__lock_this__

				_jNetQueueData* pCurr = pop_front();
				jRETURN_P_ret(iPER_LOG_COUNT,0,pCurr);

				dataLength	= pCurr->m_iLength;
				*object		= pCurr->m_pObj;
				if(pIP)*pIP= pCurr->RemoteAddress;

				memcpy(data, pCurr->GetBuffer(), pCurr->m_iLength);
				get_data_size_alloc_info(pCurr->m_iLength)->delete_func(pCurr);
				return true;
			}
			bool jCircularQueueBuffer::Pop(VOID **object, jPacketNum_t &dwProtocol, BYTE *data, jPacketLen_t &dataLength, jIP_Address* pIP)
			{
				jRETURN_ret(0,isReady());
				jRETURN_ret(0,(object && data) );
				__lock_this__

				_jNetQueueData* pCurr = pop_front();
				if(!pCurr) 
					return 0;
				//jRETURN_P_ret(iPER_LOG_COUNT,0,pCurr);

				dataLength	= pCurr->m_iLength;
				*object		= pCurr->m_pObj;
				dwProtocol	= pCurr->dwProtocolNumber;
				if(pIP) *pIP= pCurr->RemoteAddress;
				memcpy(data, pCurr->GetBuffer(), pCurr->m_iLength);
				get_data_size_alloc_info(pCurr->m_iLength)->delete_func(pCurr);
				return true;
			}

		}//namespace nUTIL
	}//namespace nNET
}
