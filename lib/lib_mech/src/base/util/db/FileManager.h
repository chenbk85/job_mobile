#ifndef _FILEMANAGER_H
#define _FILEMANAGER_H

#include <windows.h>
#include <fstream>
#include <atlstr.h>
#include <atltime.h>


#define MAX_LOG_LENGTH	2048

namespace nMech
{
	namespace nUtil
	{
		namespace nDB
		{

			class CFileManager
			{
				class CSyncObject
				{
					CRITICAL_SECTION *m_cs;

				public:
					CSyncObject(CRITICAL_SECTION& cs)
					{
						m_cs = &cs;
						::EnterCriticalSection(m_cs);
					}

					~CSyncObject()
					{
						::LeaveCriticalSection(m_cs);
					}
				};

				CRITICAL_SECTION	m_cs;
				std::ofstream		m_LogFile;
				int					m_LogFileDay;
				char				m_strFileName[MAX_PATH];
				BOOL				m_bEveryDayNewFile;

			public:
				CFileManager()
				{
					InitializeCriticalSection(&m_cs);
					m_bEveryDayNewFile = TRUE;
				}

				~CFileManager()
				{
					DeleteCriticalSection(&m_cs);

					if(m_LogFile.is_open())
						m_LogFile.close();
				}

				void Initialize(char* strFileName, BOOL bEveryDayNewFile = TRUE)
				{
					CTime cur = CTime::GetCurrentTime();
					m_LogFileDay = cur.GetDay();
					char strLog[MAX_LOG_LENGTH];	memset(strLog, 0x00, MAX_LOG_LENGTH);

					m_bEveryDayNewFile = bEveryDayNewFile;

					memset(m_strFileName, 0, MAX_PATH);
					strcpy(m_strFileName, strFileName);

					sprintf(strLog, "%s-%02d-%02d-%02d.txt", m_strFileName, cur.GetYear(), cur.GetMonth(), cur.GetDay());

					m_LogFile.open( strLog, std::ios_base::out | std::ios_base::app);
				}

				void WriteLogFileA( const char* pData )
				{
					WCHAR strLog[MAX_LOG_LENGTH];	memset(strLog, 0x00, sizeof(strLog));
					mbstowcs(strLog, pData, MAX_LOG_LENGTH);

					WriteLogFileW(strLog);
				}

				void WriteLogFileW( const WCHAR* pData )
				{
					CTime cur = CTime::GetCurrentTime();
					int nDay = cur.GetDay();

					CSyncObject cLogObject(m_cs);

					if( m_bEveryDayNewFile )
					{
						if( m_LogFileDay != nDay )	
						{
							if( m_LogFile.is_open() ) m_LogFile.close();

							char FileName[FILENAME_MAX];
							memset(FileName, 0, sizeof(FileName));
							sprintf(FileName, "%s-%02d-%02d-%02d.txt", m_strFileName, cur.GetYear(), cur.GetMonth(), cur.GetDay());
							m_LogFile.open( FileName, std::ios_base::out | std::ios_base::app);
							m_LogFileDay = nDay;
						}
					}
					CStringW strLog;
					strLog.Format( L"[%02d/%02d/%02d %02d:%02d:%02d] %s", cur.GetYear(), cur.GetMonth(), cur.GetDay(), cur.GetHour()
						, cur.GetMinute(), cur.GetSecond(), pData);

					m_LogFile << CW2A(strLog) 	<< std::endl;
				}
			};
		}// nDB
	}// nUTIL
}// nMech


#endif
