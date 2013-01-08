/* file : RingBuffer.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-06-23 23:45:08

title : 
desc : 

*/

#include "stdafx.h"
#include "jRingBuffer.h"



jCriticalSec::jCriticalSec(void)
{
	InitializeCriticalSection(&m_csSyncObject);
}

jCriticalSec::~jCriticalSec(void)
{
	DeleteCriticalSection( &m_csSyncObject );
}

#if(_WIN32_WINNT >= 0x0400)
BOOL jCriticalSec::TryEnter()
{
	return TryEnterCriticalSection(&m_csSyncObject);
}
#endif

void jCriticalSec::Enter()
{
	::EnterCriticalSection(&m_csSyncObject);
}

void jCriticalSec::Leave()
{
	::LeaveCriticalSection(&m_csSyncObject);
}

jCriticalSec::Owner::Owner( jCriticalSec &crit )
: m_csSyncObject(crit)
{
	m_csSyncObject.Enter();
}

jCriticalSec::Owner::~Owner()
{
	m_csSyncObject.Leave();
}


RingBuffer::RingBuffer(int nBufferSize )
{
	m_pRingBuffer = NULL;
	m_pBeginMark = NULL;
	m_pEndMark = NULL;
	m_pCurrentMark = NULL;
	m_pGettedBufferMark = NULL;
	m_pLastMoveMark = NULL;
	m_nUsedBufferSize = 0;
	m_uiAllUserBufSize = 0;

	if( NULL != m_pBeginMark )
		delete [] m_pBeginMark;

	m_pBeginMark = new BYTE[ nBufferSize ];

	if( NULL == m_pBeginMark )
		throw "RingBuffer";

	m_pEndMark = m_pBeginMark + nBufferSize - 1;
	m_nBufferSize = nBufferSize;

	Initialize();

}

RingBuffer::~RingBuffer(void)
{
	if( NULL != m_pBeginMark )
		delete [] m_pBeginMark;

}

bool RingBuffer::Initialize()
{
	jCriticalSec::Owner lock( m_csRingBuffer );
	{
		m_nUsedBufferSize = 0;
		m_pCurrentMark = m_pBeginMark;
		m_pGettedBufferMark = m_pBeginMark;
		m_pLastMoveMark = m_pEndMark;
		m_uiAllUserBufSize = 0;

	}
	return true;
}

int	RingBuffer::Write(const BYTE* IN pBuffer, int len)
{
	if(len<=0) return len;
	BYTE* p = ForwardMark(len);
	memcpy(p , pBuffer, len);
}


BYTE* RingBuffer::ForwardMark( int nForwardLength )
{
	BYTE* pPreCurrentMark = NULL;
	jCriticalSec::Owner lock( m_csRingBuffer );
	{
		//������ �����÷� üũ
		if( m_nUsedBufferSize + nForwardLength > m_nBufferSize )
			return NULL;
		if( ( m_pEndMark - m_pCurrentMark ) >= nForwardLength )
		{
			pPreCurrentMark = m_pCurrentMark;
			m_pCurrentMark += nForwardLength;
		}
		else
		{
			//��ȯ �Ǳ� �� ������ ��ǥ�� ����
			m_pLastMoveMark = m_pCurrentMark;
			m_pCurrentMark = m_pBeginMark + nForwardLength;
			pPreCurrentMark = m_pBeginMark;
		}

	}
	return pPreCurrentMark;
}

BYTE* RingBuffer::ForwardMark( int nForwardLength 
							  , int nNextLength 
							  , DWORD dwRemainLength )
{
	jCriticalSec::Owner lock( m_csRingBuffer );
	{	
		//������ �����÷� üũ
		if( m_nUsedBufferSize + nForwardLength + nNextLength > m_nBufferSize )
			return NULL;

		if( ( m_pEndMark - m_pCurrentMark ) > ( nNextLength + nForwardLength ) )
			m_pCurrentMark += nForwardLength;

		//���� ������ ���̺��� ������ ���� �޼����� ũ�� ���� �޼����� ó������ 
		//�����Ѵ��� ��ȯ �ȴ�.
		else
		{
			//��ȯ �Ǳ� �� ������ ��ǥ�� ����
			m_pLastMoveMark = m_pCurrentMark;
			CopyMemory( m_pBeginMark , 
				m_pCurrentMark - ( dwRemainLength - nForwardLength ) , 
				dwRemainLength );
			m_pCurrentMark = m_pBeginMark + dwRemainLength;
		}
	}
	return m_pCurrentMark;
}

void RingBuffer::BackwardMark( int nBackwardLength )
{
	jCriticalSec::Owner lock( m_csRingBuffer );
	{
		//nBackwardLength�縸ŭ ���� ���������͸� �ڷ� ������.
		m_nUsedBufferSize -= nBackwardLength;
		m_pCurrentMark -= nBackwardLength;
	}
}

void RingBuffer::ReleaseBuffer( int nReleaseSize )
{
	jCriticalSec::Owner lock( m_csRingBuffer );
	{
		m_nUsedBufferSize -= nReleaseSize;
	}
}

//���� ���۾� ����(�̰��� �ϴ� ������ SendPost()�Լ��� ��Ƽ �����忡�� ���ư��⶧����
//PrepareSendPacket()����(ForwardMark()����) ���� ���� �÷������� PrepareSendPacket�Ѵ����� �����͸�
//ä�� �ֱ����� �ٷ� �ٸ� �����忡�� SendPost()�� �Ҹ��ٸ� ������ ������ �����Ͱ� �� �� �ִ�.
//�װ� �����ϱ� ���� �����͸� �� ä�� ���¿����� ���� ���� ����� ������ �� �־���Ѵ�.
//���Լ��� sendpost�Լ����� �Ҹ��� �ȴ�.
void RingBuffer::SetUsedBufferSize( int nUsedBufferSize )
{
	jCriticalSec::Owner lock( m_csRingBuffer );
	{
		m_nUsedBufferSize += nUsedBufferSize;
		m_uiAllUserBufSize += nUsedBufferSize;
	}
}

int	RingBuffer::Read(BYTE* OUT pBuffer, int len)		//���� buffer���� ���� ���� �� �����͸� ������.
{
	jCriticalSec::Owner lock( m_csRingBuffer );
	int readLen=0;
	BYTE* p = _Read(len , &readLen , false);
	memcpy(pBuffer, p, readLen);
	return readLen;


}
int	RingBuffer::Peek(BYTE* OUT pBuffer, int len)					//���� buffer���� ��ȭ���� ���� �о�´�.
{
	jCriticalSec::Owner lock( m_csRingBuffer );
	int readLen=0;
	BYTE* p = _Read(len , &readLen , true);
	if(readLen)
		memcpy(pBuffer, p, readLen);
	return readLen;
}

BYTE* RingBuffer::_Read( int nReadSize , int* pReadSize ,bool isPeek)
{
	BYTE* pRet = NULL;
	{
		//���������� �� �о��ٸ� �� �о���� ������ �����ʹ� �Ǿ����� �ű��.
		if( m_pLastMoveMark == m_pGettedBufferMark )
		{
			m_pGettedBufferMark = m_pBeginMark;
			m_pLastMoveMark = m_pEndMark;
		}

		//���� ���ۿ� �ִ� size�� �о���� size���� ũ�ٸ�
		if( m_nUsedBufferSize > nReadSize )
		{
			//�������� ������ �Ǵ�.
			if( ( m_pLastMoveMark - m_pGettedBufferMark ) >= nReadSize )
			{
				*pReadSize = nReadSize;
				pRet = m_pGettedBufferMark;
				if(!isPeek)
					m_pGettedBufferMark += nReadSize;
			}
			else
			{
				*pReadSize = (int)( m_pLastMoveMark - m_pGettedBufferMark );
				pRet = m_pGettedBufferMark;
				if(!isPeek)
					m_pGettedBufferMark += *pReadSize;
			}
		}
		else if( m_nUsedBufferSize > 0 )
		{
			//�������� ������ �Ǵ�.
			if( ( m_pLastMoveMark - m_pGettedBufferMark ) >= m_nUsedBufferSize )
			{
				*pReadSize = m_nUsedBufferSize;
				pRet = m_pGettedBufferMark;
				if(!isPeek)
					m_pGettedBufferMark += m_nUsedBufferSize;
			}
			else
			{
				*pReadSize = (int)( m_pLastMoveMark - m_pGettedBufferMark );
				pRet = m_pGettedBufferMark;
				if(!isPeek)
					m_pGettedBufferMark += *pReadSize;
			}
		}
	}
	return pRet;
}

