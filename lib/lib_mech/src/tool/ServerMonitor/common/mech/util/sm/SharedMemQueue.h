// SharedMemQueue.h: interface for the CSharedMemQueue class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _SHAREDMEM_Hasldkfsalkf2398iosdfjk
#define _SHAREDMEM_Hasldkfsalkf2398iosdfjk

#include <windows.h>
#ifdef DF_CLIENT_TEAM
#define jUSE_jOptMutex
#endif
#ifdef jUSE_jOptMutex
#include "Optex.h"
#else
#define JBASE_API_NULL
#endif

namespace nMech
{
	typedef unsigned short uint16;
}


namespace nMech
{
	namespace nUtil
	{
		namespace nSharedMem
		{
			typedef uint16 jPacketNum_t;// 패킷번호의 자료형
			typedef uint16 jPacketLen_t;// 패킷크기의 자료형.
			struct jPacket_Info	
			{		
				jPacketLen_t len;		
				jPacketNum_t num;	
			};
			struct jPacket_Base : public jPacket_Info	
			{	
				BYTE* buf;	
				jPacketLen_t GetLen(){ return len;}
				jPacketNum_t GetNum(){ return num;}
			};
			
			// DEFINE Shared Memory Queue Flag
			enum ESmqFlag
			{
				E	= 0,
				R	= 1,
				W	= 2,
				WR	= 3
			};

			// DEFINE Shared Memory Queue Return VALUE
			enum ESmq_Ret_Value
			{
				SMQ_BROKEN		= 10000,
				SMQ_FULL		= 10001,
				SMQ_EMPTY		= 10002,
				SMQ_PKTSIZEOVER = 10003,
				SMQ_WRITING		= 10004,
				SMQ_READING		= 10005
			};

			// DEFINE Shared Memory Costumizing
			const int MAX_PKTSIZE		=(1024*8);

#pragma pack(1)

			struct jSmqHeader
			{
				LONG Front;
				LONG Rear;
				short	nCount;

				BYTE FrontMode;
				BYTE RearMode;

				int  WritePid;
				int	 ReadPid;

				DWORD CreatePid;
				DWORD OtherPid;
			};

			struct jSmqPacket
			{
				short nSize;
				BYTE pData[MAX_PKTSIZE];

				jSmqPacket()
				{
					nSize	= 0;
					memset( pData, 0, sizeof(pData) );
				}

				jSmqPacket(short _nSize, void* _pData)
				{
					nSize	= _nSize;
					memcpy( pData, (char*)_pData, _nSize );
				}
			};

			struct jSmqPacket_UNIT
			{
				ESmqFlag Flag;
				DWORD size;
				jSmqPacket pPacket;

				jSmqPacket_UNIT()
				{
					Flag = E;
					size = 0;
				}
			};

#pragma pack()

#ifdef jUSE_jOptMutex


			class COptEx
			{
				nUtil::jOptMutex *m_cs;

			public:
				COptEx(nUtil::jOptMutex& cs)
				{
					m_cs = &cs;
					OPTEX_Enter(m_cs, INFINITE);
				}

				~COptEx()
				{
					OPTEX_Leave(m_cs);
				}
			};
#endif

			JBASE_API_NULL class CSharedMemQueue  
			{
			private:
				HANDLE	m_hMMFile;
				char*	m_lpMMFile;

				BOOL	m_bMMFCreate;
				int		m_nMaxCount;
				DWORD	m_wOffset;
				LONG	m_lReference;
				jSmqHeader*	m_pHeader;
				int		PID;
#ifdef jUSE_jOptMutex
				nUtil::jOptMutex	m_OptexDB;
#else
				nUtil::jCriticalSection m_CS;
#endif

				//CFile	m_SMQLogFile;
				//int		m_iSMQLogFileDay;

			public:
				CSharedMemQueue();
				virtual ~CSharedMemQueue();

				BOOL InitailizeMMF(DWORD dwOffsetsize, int maxcount, LPCTSTR lpname);
			private:
				int GetData(jSmqPacket& pPacket);
				int PutData(char* pBuf, int size);
			public:

				bool ReadPacket(jPacket_Base& pP);
				int WritePacket(jPacket_Base& pP);

				inline LONG GetFrontPointer() {return m_pHeader->Front;};
				inline LONG GetRearPointer() {return m_pHeader->Rear;};
				inline DWORD GetProcessId() {return m_pHeader->CreatePid;};
				inline BYTE GetFrontMode() {return m_pHeader->FrontMode;};
				inline BYTE GetRearMode() {return m_pHeader->RearMode;};
				inline int GetCount();// {return m_pHeader->nCount;};

			};
		}//nSharedMem
	}// nUTIL
}// nMech

#endif // #ifndef _SHAREDMEM_Hasldkfsalkf2398iosdfjk
