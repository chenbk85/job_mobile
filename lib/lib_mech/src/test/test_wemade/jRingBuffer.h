/* file : RingBuffer.h
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-06-23 23:45:03

title : 
desc : 

*/

#ifndef __jRingBuffer_header__
#define __jRingBuffer_header__
#pragma once

#define MAX_RINGBUFSIZE				1024 * 100		//Ringbuffer size

class jCriticalSec
{
public :
	class Owner
	{
	public:
		explicit Owner(
			jCriticalSec &crit);

		~Owner();
	private :
		jCriticalSec &m_csSyncObject;
		// No copies do not implement
		Owner(const Owner &rhs);
		Owner &operator=(const Owner &rhs);
	};

	jCriticalSec();
	~jCriticalSec();

#if(_WIN32_WINNT >= 0x0400)
	BOOL TryEnter();
#endif
	void Enter();
	void Leave();

private :

	CRITICAL_SECTION m_csSyncObject;

	jCriticalSec(const jCriticalSec &rhs);
	jCriticalSec &operator=(const jCriticalSec &rhs);
};

class RingBuffer : public jCriticalSec
{
public:
	RingBuffer(int nBufferSize = MAX_RINGBUFSIZE );
	~RingBuffer(void);


	int				Write(const BYTE* IN pBuffer, int len);	//내부 buffer에 쓴다.
	int				Read(BYTE* OUT pBuffer, int len);		//내부 buffer에서 값을 읽은 후 데이터를 빼낸다.
	int				Peek(BYTE* OUT pBuffer, int len);		//내부 buffer에는 변화없이 값만 읽어온다.


	bool IsEmpty() const		{ return 0==m_nUsedBufferSize;}
	bool IsFull() const			{ return m_nBufferSize<=m_nUsedBufferSize;}
	int	GetBufferSize() const	{ return m_nBufferSize; }
	int	GetDataSize() const		{ return m_nUsedBufferSize;}
	int	GetFreeSize() const		{ return m_nBufferSize-m_nUsedBufferSize;}

	//초기화
	bool			Initialize();

	//해당하는 버퍼의 포인터를 반환
	inline BYTE*	GetBeginMark() { return m_pBeginMark; }
	inline BYTE*	GetCurrentMark() { return m_pCurrentMark; }
	inline BYTE*	GetEndMark() { return m_pEndMark; }

	BYTE*			ForwardMark( int nForwardLength );
	BYTE*			ForwardMark( int nForwardLength , int nNextLength , DWORD dwRemainLength );
	void			BackwardMark( int nBackwardLength );

	//사용된 버퍼 해제
	void			ReleaseBuffer( int nReleaseSize );
	//사용된 버퍼 크기 반환
	int				GetUsedBufferSize() { return m_nUsedBufferSize; }
	//사용된 버퍼양 설정(이것을 하는 이유는 SendPost()함수가 멀티 쓰레드에서 돌아가기때문에
	//PrepareSendPacket()에서(ForwardMark()에서) 사용된 양을 늘려버리면 PrepareSendPacket한다음에 데이터를
	//채워 넣기전에 바로 다른 쓰레드에서 SendPost()가 불린다면 엉뚱한 쓰레기 데이터가 갈 수 있다.
	//그걸 방지하기 위해 데이터를 다 채운 상태에서만 사용된 버퍼 사이즈를 설정할 수 있어야한다.
	//이함수는 sendpost함수에서 불리게 된다.
	void			SetUsedBufferSize( int nUsedBufferSize );

	//누적 버퍼 사용양 반환
	int				GetAllUsedBufferSize() { return m_uiAllUserBufSize; }


private:

	BYTE*			m_pRingBuffer;		   //실제 데이터를 저장하는 버퍼 포인터

	BYTE*			m_pBeginMark;			//버퍼의 처음부분을 가리키고 있는 포인터
	BYTE*			m_pEndMark;				//버퍼의 마지막부분을 가리키고 있는 포인터
	BYTE*			m_pCurrentMark;			//버퍼의 현재 부분을 가리키고 있는 포인터
	BYTE*			m_pGettedBufferMark;	//현재까지 데이터를 읽은 버퍼의 포인터
	BYTE*			m_pLastMoveMark;		//ForwardMark되기 전에 마지막 포인터

	int				m_nBufferSize;		//버퍼의 총 크기
	int 			m_nUsedBufferSize;	//현재 사용된 버퍼의 크기
	unsigned int	m_uiAllUserBufSize; //총 처리된 데이터량
	jCriticalSec		m_csRingBuffer;		//동기화 객체


private:
	BYTE*			_Read( int nReadSize , int* pReadSize ,bool isPeek);
	// No copies do not implement
	RingBuffer(const RingBuffer &rhs);
	RingBuffer &operator=(const RingBuffer &rhs);
};



#endif // __jRingBuffer_header__
