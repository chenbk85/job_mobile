// SharedMem.h: interface for the CSharedMemQueue class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _SHAREDMEM_H
#define _SHAREDMEM_H

#include <windows.h>

#include "Optex.h"

namespace nMech
{
	typedef unsigned short uint16;
}

#include "Interface/net/jTypedef_net.h"

namespace nMech
{
	namespace nUtil
	{
		namespace nSharedMem
		{
			typedef nMech::nNET::jPacket_Info  jPacket_Info;
			typedef nMech::nNET::jPacket_Base  jPacket_Base;
			typedef nMech::nNET::jPacketNum_t  jPacketNum_t;
			
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

			class COptEx
			{
				nMech::nUtil::nDB::jOptMutex *m_cs;

			public:
				COptEx(nMech::nUtil::nDB::jOptMutex& cs)
				{
					m_cs = &cs;
					OPTEX_Enter(m_cs, INFINITE);
				}

				~COptEx()
				{
					OPTEX_Leave(m_cs);
				}
			};

			class CSharedMemQueue  
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

				nMech::nUtil::nDB::jOptMutex	m_OptexDB;

				//CFile	m_SMQLogFile;
				//int		m_iSMQLogFileDay;

			public:
				CSharedMemQueue();
				virtual ~CSharedMemQueue();

				BOOL InitailizeMMF(DWORD dwOffsetsize, int maxcount, LPCTSTR lpname, BOOL bCreate = TRUE);
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


#endif // #ifndef _SHAREDMEM_H
