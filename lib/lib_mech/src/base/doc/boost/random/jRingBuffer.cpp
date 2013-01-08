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
		//링버퍼 오버플로 체크
		if( m_nUsedBufferSize + nForwardLength > m_nBufferSize )
			return NULL;
		if( ( m_pEndMark - m_pCurrentMark ) >= nForwardLength )
		{
			pPreCurrentMark = m_pCurrentMark;
			m_pCurrentMark += nForwardLength;
		}
		else
		{
			//순환 되기 전 마지막 좌표를 저장
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
		//링버퍼 오버플로 체크
		if( m_nUsedBufferSize + nForwardLength + nNextLength > m_nBufferSize )
			return NULL;

		if( ( m_pEndMark - m_pCurrentMark ) > ( nNextLength + nForwardLength ) )
			m_pCurrentMark += nForwardLength;

		//남은 버퍼의 길이보다 앞으로 받을 메세지양 크면 현재 메세지를 처음으로 
		//복사한다음 순환 된다.
		else
		{
			//순환 되기 전 마지막 좌표를 저장
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
		//nBackwardLength양만큼 현재 버퍼포인터를 뒤로 보낸다.
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

//사용된 버퍼양 설정(이것을 하는 이유는 SendPost()함수가 멀티 쓰레드에서 돌아가기때문에
//PrepareSendPacket()에서(ForwardMark()에서) 사용된 양을 늘려버리면 PrepareSendPacket한다음에 데이터를
//채워 넣기전에 바로 다른 쓰레드에서 SendPost()가 불린다면 엉뚱한 쓰레기 데이터가 갈 수 있다.
//그걸 방지하기 위해 데이터를 다 채운 상태에서만 사용된 버퍼 사이즈를 설정할 수 있어야한다.
//이함수는 sendpost함수에서 불리게 된다.
void RingBuffer::SetUsedBufferSize( int nUsedBufferSize )
{
	jCriticalSec::Owner lock( m_csRingBuffer );
	{
		m_nUsedBufferSize += nUsedBufferSize;
		m_uiAllUserBufSize += nUsedBufferSize;
	}
}

int	RingBuffer::Read(BYTE* OUT pBuffer, int len)		//내부 buffer에서 값을 읽은 후 데이터를 빼낸다.
{
	jCriticalSec::Owner lock( m_csRingBuffer );
	int readLen=0;
	BYTE* p = _Read(len , &readLen , false);
	memcpy(pBuffer, p, readLen);
	return readLen;


}
int	RingBuffer::Peek(BYTE* OUT pBuffer, int len)					//내부 buffer에는 변화없이 값만 읽어온다.
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
		//마지막까지 다 읽었다면 그 읽어들일 버퍼의 포인터는 맨앞으로 옮긴다.
		if( m_pLastMoveMark == m_pGettedBufferMark )
		{
			m_pGettedBufferMark = m_pBeginMark;
			m_pLastMoveMark = m_pEndMark;
		}

		//현재 버퍼에 있는 size가 읽어들일 size보다 크다면
		if( m_nUsedBufferSize > nReadSize )
		{
			//링버퍼의 끝인지 판단.
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
			//링버퍼의 끝인지 판단.
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

