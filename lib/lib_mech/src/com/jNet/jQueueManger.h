/* file : jQueueManger.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-04 15:36:25
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __jQueueManger_header__
#define __jQueueManger_header__
#pragma once

#include "header/yVector.h"
#include "interface/net/jTypedef_net.h"

//#define jCircularQueueBuffer_IOCP_NEW_DELELTE_DEBUG() printf("************ " __FUNCTION__ "\n");
#define jCircularQueueBuffer_IOCP_NEW_DELELTE_DEBUG()

namespace nMech
{
	namespace nNET
	{
		namespace nUTIL
		{
			struct _jNetQueueData;
			typedef _jNetQueueData* _new_data_func_t();
			typedef void _delete_data_func_t(_jNetQueueData*);
			struct _data_size_alloc_info
			{
				int iSize;
				_new_data_func_t* new_func;
				_delete_data_func_t* delete_func;
			};

			//--------------------------------------------------------------------------
			struct _jNetQueueData
			//--------------------------------------------------------------------------
			{
				void *m_pObj;
				jPacketLen_t	m_iLength; // GetBuffer()에 저장 된 데이타 사이즈
				jPacketNum_t	dwProtocolNumber;
				jIP_Address RemoteAddress;
				virtual int GetBufferSize()=0; // 실제 메모리 사이즈 , 256, 1024, 2048 ....
				virtual BYTE* GetBuffer()=0; 
			};

			class jCircularQueueBuffer 
			{
#ifdef _DEBUG
//#define _DEBUG_jCircularQueueBuffer_COUNT
#endif
#ifdef _DEBUG_jCircularQueueBuffer_COUNT
				int m_iPushCount;
				int m_iPopCount;
#endif
				nMech::nUtil::jCriticalSection m_CS;
				int m_iSizeQueue;
				_jNetQueueData	**m_QueueBuffer;
				// 데이타는 mQueueTail로 push_back()되어 mQueueHead로 pop_front()된다.
				DWORD		mQueueHead; 
				DWORD		mQueueTail;

				_jNetQueueData*		push_back(int iSize);
				_jNetQueueData*		pop_front();

			public:
				jCircularQueueBuffer(int iSizeQueue):m_QueueBuffer(0){_PostCreate(iSizeQueue);}
				jCircularQueueBuffer():m_QueueBuffer(0){}
				void _PostCreate(int iSizeQueue); //_PostCreate후 반드시 _PostDelete해야함. 생성자의 역활
				void _PostDelete();//소멸하기전에 꼭 콜하자. 소멸자의 역활
				~jCircularQueueBuffer(VOID);
				bool		Begin(void);
				bool		End(void);
				bool isReady(){ return m_QueueBuffer;}
				bool empty(){	return (mQueueHead == mQueueTail);}

				BYTE*		Push(void *object, BYTE *data, jPacketLen_t dataLength);
				BYTE*		Push(void *object, BYTE *data, jPacketLen_t dataLength, jIP_Address* pIP);
				BYTE*		Push(void *object, jPacketNum_t dwProtocol, BYTE *data, jPacketLen_t dataLength);
				BYTE*		Push(void *object, jPacketNum_t dwProtocol, BYTE *data, jPacketLen_t dataLength, jIP_Address* pIP);

				bool		Pop(void **object, BYTE *data, jPacketLen_t &dataLength);
				bool		Pop(void **object, BYTE *data, jPacketLen_t &dataLength, jIP_Address* pIP);
				bool		Pop(void **object, jPacketNum_t &dwProtocol, BYTE *data, jPacketLen_t &dataLength);
				bool		Pop(void **object, jPacketNum_t &dwProtocol, BYTE *data, jPacketLen_t &dataLength, jIP_Address* pIP);
				bool		Pop(void);
				static		_data_size_alloc_info *get_data_size_alloc_info(int iLen);
			};//class jCircularQueueBuffer 

		}//namespace nUTIL
	}//namespace nNET
}

#endif // __jQueueManger_header__
