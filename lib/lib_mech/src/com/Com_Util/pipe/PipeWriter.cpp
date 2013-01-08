//---------------------------------------------------------------------------
//
//	"Tracer.cpp"
//
//  Puts trace data in a named pipe
//
//	by Holger Kloos
//
//---------------------------------------------------------------------------

#include "stdafx.h"
#include "interface/jIPipe.h"


namespace nMech
{
	namespace nPipe
	{
		class jPipeWriter  : public jIPipeWriter
		{
		public:
			jIPipeWriter_OnDisconnect_t* m_pjIPipeWriter_OnDisconnect;

			jINTERFACE_HEADER(jIInterface);
			jINTERFACE_HEADER(jIPipeWriter);

			jPipeWriter();
			virtual ~jPipeWriter();
		private:
			HANDLE m_hPipe;

		};


		jCTOR_INTERFACE(nMech::nPipe::jIPipeWriter,jPipeWriter)
		{
			return new jPipeWriter;
		}
		jDTOR_INTERFACE(nMech::nPipe::jIPipeWriter,jPipeWriter)
		{
			delete this;
		}

		jPipeWriter::jPipeWriter()
		{
			m_hPipe = INVALID_HANDLE_VALUE;
		}

		jPipeWriter::~jPipeWriter()
		{
			if (m_hPipe != INVALID_HANDLE_VALUE)
			{
				CloseHandle(m_hPipe);
				m_hPipe=0;
			}

		}

		bool jPipeWriter::Connect(cstr szPipeName , jIPipeWriter_OnDisconnect_t*pF)
		{
			m_pjIPipeWriter_OnDisconnect = pF;
			if (m_hPipe != INVALID_HANDLE_VALUE)
			{
				CloseHandle(m_hPipe);
				m_hPipe=0;
			}

			m_hPipe = CreateFile(szPipeName, GENERIC_WRITE, 0, NULL, OPEN_EXISTING
				, FILE_ATTRIBUTE_NORMAL, NULL);
			return m_hPipe != INVALID_HANDLE_VALUE;
		}

		bool jPipeWriter::Write(tcstr pStr, ...) 
		{
			if (m_hPipe == INVALID_HANDLE_VALUE)
				return false;

			TCHAR buffer[1024];

			va_list argList;
			va_start(argList, pStr);

			DWORD nCount = jt_vsnprintf(buffer, sizeof(buffer), pStr, argList);

			va_end(argList);

			if (nCount <= 0)
				return false;

			DWORD nWritten = 0;
			nUNI::scb1024_t buf1(buffer);
			bool is = WriteFile(m_hPipe, (BYTE*)buf1.getA(), nCount, &nWritten, NULL) != FALSE && nWritten == nCount;
			if(!is)
			{
				if(nWritten != nCount)
					jMB("error" , "pipe WriteFile");

				m_pjIPipeWriter_OnDisconnect(this);
			}
			return true;
		}
	}//namespace nPipe
}


