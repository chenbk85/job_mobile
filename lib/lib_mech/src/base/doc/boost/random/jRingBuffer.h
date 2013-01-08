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


	int				Write(const BYTE* IN pBuffer, int len);	//���� buffer�� ����.
	int				Read(BYTE* OUT pBuffer, int len);		//���� buffer���� ���� ���� �� �����͸� ������.
	int				Peek(BYTE* OUT pBuffer, int len);		//���� buffer���� ��ȭ���� ���� �о�´�.


	bool IsEmpty() const		{ return 0==m_nUsedBufferSize;}
	bool IsFull() const			{ return m_nBufferSize<=m_nUsedBufferSize;}
	int	GetBufferSize() const	{ return m_nBufferSize; }
	int	GetDataSize() const		{ return m_nUsedBufferSize;}
	int	GetFreeSize() const		{ return m_nBufferSize-m_nUsedBufferSize;}

	//�ʱ�ȭ
	bool			Initialize();

	//�ش��ϴ� ������ �����͸� ��ȯ
	inline BYTE*	GetBeginMark() { return m_pBeginMark; }
	inline BYTE*	GetCurrentMark() { return m_pCurrentMark; }
	inline BYTE*	GetEndMark() { return m_pEndMark; }

	BYTE*			ForwardMark( int nForwardLength );
	BYTE*			ForwardMark( int nForwardLength , int nNextLength , DWORD dwRemainLength );
	void			BackwardMark( int nBackwardLength );

	//���� ���� ����
	void			ReleaseBuffer( int nReleaseSize );
	//���� ���� ũ�� ��ȯ
	int				GetUsedBufferSize() { return m_nUsedBufferSize; }
	//���� ���۾� ����(�̰��� �ϴ� ������ SendPost()�Լ��� ��Ƽ �����忡�� ���ư��⶧����
	//PrepareSendPacket()����(ForwardMark()����) ���� ���� �÷������� PrepareSendPacket�Ѵ����� �����͸�
	//ä�� �ֱ����� �ٷ� �ٸ� �����忡�� SendPost()�� �Ҹ��ٸ� ������ ������ �����Ͱ� �� �� �ִ�.
	//�װ� �����ϱ� ���� �����͸� �� ä�� ���¿����� ���� ���� ����� ������ �� �־���Ѵ�.
	//���Լ��� sendpost�Լ����� �Ҹ��� �ȴ�.
	void			SetUsedBufferSize( int nUsedBufferSize );

	//���� ���� ���� ��ȯ
	int				GetAllUsedBufferSize() { return m_uiAllUserBufSize; }


private:

	BYTE*			m_pRingBuffer;		   //���� �����͸� �����ϴ� ���� ������

	BYTE*			m_pBeginMark;			//������ ó���κ��� ����Ű�� �ִ� ������
	BYTE*			m_pEndMark;				//������ �������κ��� ����Ű�� �ִ� ������
	BYTE*			m_pCurrentMark;			//������ ���� �κ��� ����Ű�� �ִ� ������
	BYTE*			m_pGettedBufferMark;	//������� �����͸� ���� ������ ������
	BYTE*			m_pLastMoveMark;		//ForwardMark�Ǳ� ���� ������ ������

	int				m_nBufferSize;		//������ �� ũ��
	int 			m_nUsedBufferSize;	//���� ���� ������ ũ��
	unsigned int	m_uiAllUserBufSize; //�� ó���� �����ͷ�
	jCriticalSec		m_csRingBuffer;		//����ȭ ��ü


private:
	BYTE*			_Read( int nReadSize , int* pReadSize ,bool isPeek);
	// No copies do not implement
	RingBuffer(const RingBuffer &rhs);
	RingBuffer &operator=(const RingBuffer &rhs);
};



#endif // __jRingBuffer_header__
