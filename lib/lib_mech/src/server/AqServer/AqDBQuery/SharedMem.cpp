// SharedMem.cpp: implementation of the CSharedMemQueue class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "tchar.h"
#include "SharedMem.h"
#include <process.h>
#include <cstdio>
#include "base/jFileDebugger.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
namespace nMech
{

	namespace nUtil
	{
		namespace nSharedMem
		{

			//////////////////////////////////////////////////////////////////////
			// Construction/Destruction
			//////////////////////////////////////////////////////////////////////

			CSharedMemQueue::CSharedMemQueue()
			{
				m_hMMFile = NULL;
				m_lpMMFile = NULL;
				m_bMMFCreate = FALSE;
				m_nMaxCount = 0;
				m_wOffset = 0;
				m_pHeader = NULL;
				PID = 0;

				OPTEX_Initialize(&m_OptexDB);
			}

			CSharedMemQueue::~CSharedMemQueue()
			{
				if( m_lpMMFile )
					UnmapViewOfFile(m_lpMMFile);

				if( m_hMMFile )
					CloseHandle(m_hMMFile);

				OPTEX_Delete(&m_OptexDB);

				//if(m_SMQLogFile.m_hFile != CFile::hFileNull) 
				//	m_SMQLogFile.Close();
			}

			BOOL CSharedMemQueue::InitailizeMMF(DWORD dwOffsetsize, int maxcount, LPCTSTR lpname, BOOL bCreate )
			{
				if( maxcount < 1 )
					return FALSE;

				PID = _getpid();

				DWORD dwfullsize = dwOffsetsize * maxcount + sizeof(jSmqHeader);

				m_nMaxCount = maxcount;
				m_wOffset = dwOffsetsize;

				if( bCreate )
					m_hMMFile = CreateFileMapping( (HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, dwfullsize, lpname );
				else
				{
					m_hMMFile = OpenFileMapping( FILE_MAP_ALL_ACCESS, TRUE, lpname );
					if( m_hMMFile == NULL )
					{					
						m_hMMFile = CreateFileMapping( (HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, dwfullsize, lpname );
					}
				}

				if( m_hMMFile == NULL ) 
				{
					GetjILog()->Error(_T("Shared Memory Open Fail!!\n"));
					return FALSE;
				}

				if( (m_lpMMFile = (char *)MapViewOfFile(m_hMMFile, FILE_MAP_WRITE, 0, 0, 0)) == NULL )
					return FALSE;

				m_bMMFCreate = bCreate;
				m_pHeader = (jSmqHeader *)m_lpMMFile;
				m_lReference = (LONG)(m_lpMMFile + sizeof(jSmqHeader));

				if( bCreate ) {
					memset( m_lpMMFile, 0x00, dwfullsize );
					m_pHeader->Rear = m_pHeader->Front = 0;
					m_pHeader->nCount = 0;
					m_pHeader->RearMode = m_pHeader->FrontMode = E;
					m_pHeader->CreatePid = PID;
				}
				else
					m_pHeader->OtherPid = PID;

				//----------------------------------------------------------------------
				//	Logfile initialize
				//----------------------------------------------------------------------
				/*CTime time=CTime::GetCurrentTime();
				char strLogFile[50];		memset(strLogFile, 0x00, 50);
				wsprintf(strLogFile, "SMQLog-%d-%d-%d.txt", time.GetYear(), time.GetMonth(), time.GetDay());
				m_SMQLogFile.Open( strLogFile, CFile::modeWrite | CFile::modeCreate | CFile::modeNoTruncate | CFile::shareDenyNone );
				m_SMQLogFile.SeekToEnd();*/

				return TRUE;
			}

			int CSharedMemQueue::GetCount()
			{
				int nCount = m_pHeader->Rear - m_pHeader->Front;
				if(nCount < 0)
					nCount = m_nMaxCount + nCount;
				return (DWORD)nCount;
			}

			int CSharedMemQueue::PutData(char* pBuf, int size)
			{
				if( size > (signed int)(m_wOffset) )
				{
					GetjILog()->Warning(_T("DataSize Over.. - %d bytes\n"), size );
					return SMQ_PKTSIZEOVER;
				}

				if( GetCount() >= (m_nMaxCount-1) )
					return SMQ_FULL;

				COptEx cs(m_OptexDB);

				jSmqPacket_UNIT* pQueue = (jSmqPacket_UNIT*)(m_lReference + (m_pHeader->Rear * m_wOffset));
				BYTE BlockMode = pQueue->Flag;

				if(BlockMode != E)
				{
					return SMQ_WRITING;
				}

				pQueue->Flag = WR;
				pQueue->pPacket.nSize = size;
				memcpy(pQueue->pPacket.pData, pBuf, size);

				m_pHeader->Rear = (m_pHeader->Rear + 1) % m_nMaxCount;

				return 1;
			}

			int CSharedMemQueue::GetData(jSmqPacket& packet)
			{
				COptEx cs(m_OptexDB);

				jSmqPacket_UNIT* pQueue = (jSmqPacket_UNIT*)(m_lReference + (m_pHeader->Front * m_wOffset));

				BYTE BlockMode = pQueue->Flag;
				DWORD size = pQueue->size;

				if(BlockMode == E && size == 0)
				{
					return SMQ_EMPTY;
				}
				if(size > m_wOffset)
				{
					throw _T("CSharedMemQueue::GetData() : size > MAX_PKTSIZE");
				}

				packet = pQueue->pPacket;
				memset( (void*)pQueue, 0x00, m_wOffset );
				m_pHeader->Front = (m_pHeader->Front + 1) % m_nMaxCount;

				return packet.nSize;
			}

			nDebug::jFileDebugger g_WRITE_DB(_T("c:\\g_WRITE_DB_") jsSERVER_NAME _T(".txt"));
			nDebug::jFileDebugger g_READ_DB(_T("c:\\g_READ_DB_")  jsSERVER_NAME _T(".txt"));

			bool CSharedMemQueue::ReadPacket(jPacket_Base& pk)
			{
				jSmqPacket sp;
				//if( GetData(sp) == SMQ_EMPTY) return false;
				if( GetData(sp) > MAX_PKTSIZE) return false;

				pk.len = sp.nSize-sizeof(pk.num);
				memcpy(&pk.num, sp.pData, sizeof(pk.num));
				memcpy(pk.buf , sp.pData+sizeof(pk.num) , pk.len);
#if 0
				static uint64 g_iSeq=0;
				g_READ_DB.Write(jsSERVER_NAME _T("ReadPacket : %I64d : num=%d, len=%d"), g_iSeq++,pk.num, pk.len);
#endif
				return true;
			}

			int CSharedMemQueue::WritePacket(jPacket_Base& pk)
			{
#if 0
				static uint64 g_iSeq=0;
				g_WRITE_DB.Write(jsSERVER_NAME _T("WritePacket : %I64d : num=%d, len=%d"), g_iSeq++,pk.num, pk.len);
#endif
				jAssert0(pk.len <MAX_PKTSIZE);
				CHAR sendBuf[nMech::nUtil::nSharedMem::MAX_PKTSIZE];
				CHAR* pCurr = sendBuf;
				memcpy(pCurr, &pk.num, sizeof(pk.num));

				pCurr+=sizeof(pk.num);
				memcpy(pCurr, pk.buf, pk.len);

				int len = pk.len + sizeof(pk.num);
				return PutData(sendBuf, len);
			}

		}//nSharedMem
	}// nUTIL
}// nMech
