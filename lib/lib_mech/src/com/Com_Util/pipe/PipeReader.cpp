/* file : PipeReader.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-01-12 14:53:00
comp.: t3.co.kr
title : 
desc : 

*/



#include "stdafx.h"
#include <process.h>
#include "interface/jIPipe.h"

namespace nMech
{
	namespace nPipe
	{


		class jPipeReader : public jIPipeReader
		{
		public:
			jINTERFACE_HEADER(jIInterface);
			jINTERFACE_HEADER(jIPipeReader);

			jPipeReader();
			virtual ~jPipeReader();
			void _read_pipe();
		private:
			unsigned int m_nID;
			::HANDLE	m_hThread;
			HANDLE m_hPipe;
			jIPipeEvent* m_pPipeEvent;
			tstring m_sPipeName;

		};

		jCTOR_INTERFACE(nMech::nPipe::jIPipeReader,jPipeReader)
		{
			return new jPipeReader;
		}
		jDTOR_INTERFACE(nMech::nPipe::jIPipeReader,jPipeReader)
		{
			delete this;
		}


		jPipeReader::jPipeReader()
		{
			m_nID = 0;
			m_hThread = NULL;
			m_pPipeEvent = 0;
			m_hPipe=0;
		}

		jPipeReader::~jPipeReader()
		{
			if(m_hThread)
				CloseHandle(m_hThread);
			m_hThread=0;
		}

		tcstr jPipeReader::GetPipeName()
		{
			return m_sPipeName.c_str();
		}

		void jPipeReader::_read_pipe()
		{
			m_hPipe = CreateNamedPipe(m_sPipeName.c_str(), PIPE_ACCESS_INBOUND, PIPE_TYPE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 0, 0, 200, NULL);
			if (!ConnectNamedPipe(m_hPipe, NULL))
			{
				m_pPipeEvent->OnDisConnectingPipe();
				return ;
			}

			m_pPipeEvent->OnConnectingPipe();

			DWORD nReaded = 0;
			CHAR buffer[1024];
			while (ReadFile(m_hPipe, buffer, sizeof(buffer)-1, &nReaded, NULL))
			{
				buffer[nReaded] = 0;
				nUNI::scb1024_t buf1(buffer);
				m_pPipeEvent->OnIncomingData((BYTE*)buf1.getT(), nReaded);
			}

			if(m_hThread)
				CloseHandle(m_hThread);
			if(m_hPipe)
				CloseHandle(m_hPipe);
			m_hThread=0;
			m_hPipe=0;
			m_pPipeEvent->OnDisConnectingPipe();
		}

		unsigned int    __stdcall CPipeListener_ThredFkt(void* lpParameter)
		{
			jPipeReader* pThis = (jPipeReader*)lpParameter;
			pThis->_read_pipe(); 
			return 0;
		}

		bool jPipeReader::RunThread(tcstr szPipeName, jIPipeEvent* pEvent)
		{
			jRAISE(pEvent);
			m_sPipeName = szPipeName;
			m_pPipeEvent = pEvent;
			m_pPipeEvent->m_pjIPipeReader = this;
			m_hThread = (HANDLE)_beginthreadex(NULL, 0, &CPipeListener_ThredFkt, this, 0, &m_nID);
			return m_hThread;
		}


	}
}

