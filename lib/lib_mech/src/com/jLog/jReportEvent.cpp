// EventLog.cpp: Implementierung der Klasse jReportEvent.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <shellapi.h>
#include "header/jReportEvent_header.h"
#include "interface/jIReportEvent.h"
#include "base/jWindow_Util.h"


//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

namespace nMech
{
	namespace nLOG
	{

		class jReportEvent : public jIReportEvent
		{
		public:
			jINTERFACE_HEADER(jIInterface);
			jINTERFACE_HEADER(jIReportEvent);

			jReportEvent();
			virtual ~jReportEvent();

			HANDLE GetHandle(){return m_hLog;};


#ifdef USE_FIRE_jEventLogASDF
			BOOL FireWithData(EEventType eType, WORD wCategory, DWORD dwEventID, DWORD dwData, LPVOID ptr, ...);
			BOOL Fire(EEventType eType, WORD wCategory, DWORD dwEventID, ...);
#endif

		protected:
			PSID GetUserSID(PSID * ppSid);
			HANDLE m_hLog;
			fname_t m_szDLL;
		};

		jReportEvent::jReportEvent()
		{
			m_szDLL[0]=0;
			m_hLog = NULL;
		}

		jReportEvent::~jReportEvent()
		{
			if (m_hLog != NULL)
			{
				DeregisterEventSource(m_hLog);
				m_hLog = NULL;
			}
		}

		jCTOR_INTERFACE(nMech::nLOG::jIReportEvent,jReportEvent)
		{
			return new jReportEvent;
		}
		jDTOR_INTERFACE(nMech::nLOG::jIReportEvent,jReportEvent)
		{
			delete this;
		}


		jIVar* pv_REPORT_EVENT_DLL = jCV(jILog,REPORT_EVENT_DLL, _T("jReportEvent_header.dll") , 0 ,"report event dll file name");
		bool jReportEvent::Init(cstr szAppName ,cstr szSourceName,DWORD dwCategoryNum)
		{
			jt_sprintf(m_szDLL, _T("%s%s"),g_ExeEnv.m_szModuleDir ,pv_REPORT_EVENT_DLL->Get_cstr());

			// Event Source name.
			//wchar_t *szAppName = L"jServer";
			//wchar_t *szSourceName = L"SampleEventSourceName";
			//DLL that contains the event messages (descriptions).
			//wchar_t *szDLLPath = L"Z:\\job_taebak\\bin\\client\\udebug_vc80\\jLog_ReportEvent.dll"; 
			// This number of categories for the event source.
			//DWORD dwCategoryNum = 1;

			HKEY hk; 
			DWORD dwData, dwDisp; 
			TCHAR szBuf[MAX_PATH]; 
			size_t cchSize = MAX_PATH;

			// Create the event source as a subkey of the log. 
			jt_sprintf(szBuf, _T("SYSTEM\\CurrentControlSet\\Services\\EventLog\\%s\\%s"),szAppName, szSourceName); 

			if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, szBuf, 
				0, NULL, REG_OPTION_NON_VOLATILE,
				KEY_WRITE, NULL, &hk, &dwDisp)) 
			{
				printf("Could not create the registry key."); 
				return false;
			}

			// Set the name of the message file. 

			if (RegSetValueEx(hk,             // subkey handle 
				_T("EventMessageFile"),        // value name 
				0,                         // must be zero 
				REG_EXPAND_SZ,             // value type 
				(LPBYTE) m_szDLL,          // pointer to value data 
				(DWORD) (lstrlen(m_szDLL)+1)*sizeof(TCHAR))) // data size
			{
				printf("Could not set the event message file."); 
				RegCloseKey(hk); 
				return false;
			}

			// Set the supported event types. 

			dwData = EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE | 
				EVENTLOG_INFORMATION_TYPE; 

			if (RegSetValueEx(hk,      // subkey handle 
				_T("TypesSupported"),  // value name 
				0,                 // must be zero 
				REG_DWORD,         // value type 
				(LPBYTE) &dwData,  // pointer to value data 
				sizeof(DWORD)))    // length of value data 
			{
				printf("Could not set the supported types."); 
				RegCloseKey(hk); 
				return false;
			}

			// Set the category message file and number of categories.

			if (RegSetValueEx(hk,              // subkey handle 
				_T("CategoryMessageFile"),     // value name 
				0,                         // must be zero 
				REG_EXPAND_SZ,             // value type 
				(LPBYTE) m_szDLL,          // pointer to value data 
				(DWORD) (lstrlen(m_szDLL)+1)*sizeof(TCHAR))) // data size
			{
				printf("Could not set the category message file."); 
				RegCloseKey(hk); 
				return false;
			}

			if (RegSetValueEx(hk,            // subkey handle 
				_T("CategoryCount"),         // value name 
				0,                       // must be zero 
				REG_DWORD,               // value type 
				(LPBYTE) &dwCategoryNum, // pointer to value data 
				sizeof(DWORD)))          // length of value data 
			{
				printf("Could not set the category count."); 
				RegCloseKey(hk); 
				return false;
			}
			RegCloseKey(hk); 

			// Register to write
			m_hLog = ::RegisterEventSource( NULL, szSourceName);

			return true;
		}//bool jReportEvent::Init(cstr szAppName ,cstr szSourceName,cstr szDLLPath,DWORD dwCategoryNum)

		DWORD jReportEvent::RemoveEventSource(cstr szAppName ,cstr szSourceName)
		{
			DWORD dwError = 0;
			TCHAR szPath[ MAX_PATH ];

			_stprintf( szPath, _T("SYSTEM\\CurrentControlSet\\Services\\EventLog\\%s\\%s"),szAppName, szSourceName );
			return RegDeleteKey( HKEY_LOCAL_MACHINE, szPath );
		}

		cstr jReportEvent::LoadMessage(OUT tname1024_t buf,DWORD dwMsgId, ...)
		{
			DWORD   cchBuffer = 1024;
			buf[0]=0;

			va_list args;
			va_start( args, cchBuffer );

			if (FormatMessage( 
				FORMAT_MESSAGE_FROM_HMODULE,
				m_szDLL,					// Module (e.g. DLL) to search for the Message. NULL = own .EXE
				dwMsgId,				// Id of the message to look up (aus "Messages.h")
				LANG_NEUTRAL,			// Language: LANG_NEUTRAL = current thread's language
				buf,				// Destination buffer
				cchBuffer,				// Character count of destination buffer
				&args					// Insertion parameters
				))
				return buf;
			else
				return _T("jEventLog_null");
		}

		BOOL jReportEvent::Write(EEventType eType, WORD wCategory, DWORD dwEventID, cstr szLog)
		{
			if (m_hLog == NULL)
				return FALSE;

			WORD wType = (WORD) eType;
			PSID sid = NULL;
			BOOL bRet = ReportEvent(m_hLog, wType, wCategory, dwEventID,	0/*GetUserSID(&sid)*/, 1, 0, (LPCTSTR *)&szLog,	NULL);
			if (sid != NULL)
				delete [] sid;

			if(!bRet)
			{
				cstr sz = nUtil::nWIN::GetLastSystemErrorMessage();
				OutputDebugString(_T("ERROR ~~~ jReportEvent::Write"));
				OutputDebugString(sz);
			}
			return bRet;
		}

		BOOL jReportEvent::Write(EEventType eType, WORD wCategory, cstr fmt,...)
		{
			if (m_hLog == NULL)
				return FALSE;

			WORD wType = (WORD) eType;
			//PSID sid = NULL;
			tname1024_t szBuff;
			va_list         vl;
			va_start(vl, fmt);
			jt_vsnprintf(szBuff, 1023,fmt, vl);
			szBuff[1023]=0;
			va_end(vl);
			DWORD dwEventID = EVT_NORMAL;
			tcstr arr = szBuff;
			BOOL bRet = ReportEvent(m_hLog, wType, wCategory, dwEventID ,	0/*GetUserSID(&sid)*/, 1, 0, (LPCTSTR *)&arr,	NULL);

			//if (sid != NULL) delete [] sid;

			if(!bRet)
			{
				cstr sz = nUtil::nWIN::GetLastSystemErrorMessage();
				OutputDebugString(_T("ERROR ~~~ jReportEvent::Write"));
				OutputDebugString(sz);
			}
			return bRet;

		}


#ifdef USE_FIRE_jEventLogASDF
		BOOL jReportEvent::Fire(EEventType eType, WORD wCategory, DWORD dwEventID, ...)
		{
			WORD wType = (WORD) eType;
			PSID sid = NULL;
			va_list args;
			va_start( args, dwEventID );

			int iCount = 0;

			while(1)
			{
				char*p = va_arg( args, char*);
				if (*p != '\0')
					iCount++;
				else
					break;
			}

			va_start( args, dwEventID );

			if (m_hLog == NULL)
				return FALSE;

			BOOL bRet = ReportEvent(m_hLog, wType, wCategory, dwEventID,	GetUserSID(&sid), iCount, 0, (LPCTSTR *)args,	NULL);
			va_end(args);
			if (sid != NULL)
				delete [] sid;
			return bRet;
		}

		BOOL jReportEvent::FireWithData(EEventType eType, WORD wCategory, DWORD dwEventID, DWORD dwData, LPVOID ptr,...)
		{
			WORD wType = (WORD) eType;
			PSID sid = NULL;
			va_list args;
			va_start( args, ptr );

			int iCount = 0;

			while(1)
			{
				char *p = va_arg( args, char *);
				if (*p != '\0')
					iCount++;
				else
					break;
			}

			va_start( args, ptr );

			if (m_hLog == NULL)
				return FALSE;

			BOOL bRet = ReportEvent(m_hLog, wType, wCategory, dwEventID,	GetUserSID(&sid), iCount, dwData, (LPCTSTR *)args,	ptr);
			va_end(args);
			if (sid != NULL)
				delete [] sid;
			return bRet;
		}

#endif //#ifdef USE_FIRE_jEventLogASDF

		BOOL jReportEvent::LaunchViewer()
		{
			fname_t csVwrExpand, csDefaultDir, csMsg,csVwr;
			long lErr = ExpandEnvironmentStrings(_T("%SystemRoot%\\system32\\eventvwr.msc"),csVwrExpand, sizeof(csVwrExpand));
			if (lErr == 0)
				return FALSE;

			jt_strcpy(csDefaultDir, csVwrExpand );
			TCHAR* ch =jt_strrchr(csDefaultDir, '\\');
			if(ch)
				*ch = 0;

			long hinst = (long)::FindExecutable(csVwrExpand, csDefaultDir, csVwr);
			switch (hinst)
			{
			case 0:
				jMB("The system is out of memory or resources.", "LaunchViewer");
				return FALSE;
			case 31:
				jt_sprintf(csMsg,_T("No association for file type of '%s' found.") , csVwrExpand);
				jMB(csMsg, _T("LaunchViewer") );
				return FALSE;
			case ERROR_FILE_NOT_FOUND:
				jt_sprintf(csMsg,_T("File '%s' not found."), csVwrExpand);
				jMB(csMsg, _T("LaunchViewer"));
				return FALSE;
			case ERROR_PATH_NOT_FOUND:
				jt_sprintf(csMsg ,_T("Path of file '%s' not found."), csVwrExpand);
				jMB(csMsg, _T("LaunchViewer"));
				return FALSE;
			case ERROR_BAD_FORMAT:
				jt_sprintf(csMsg ,_T("The executable file '%s' is invalid (non-Win32?.exe or error in .exe image)."), csVwr);
				jMB(csMsg, _T("LaunchViewer"));
				return FALSE;
			default:
				if (hinst < 32)
				{
					jt_sprintf(csMsg ,_T("Unknown error %d returned from FindExecutable()."), hinst);
					jMB(csMsg, _T("LaunchViewer") );
					return FALSE;
				}
				break;
			}

			hinst = (long)::ShellExecute(NULL, _T("open"), csVwr, tstring(tstring(csVwrExpand) + _T(" /s")).c_str(), csDefaultDir, SW_SHOWNORMAL);
			switch (hinst)
			{
			case 0:
				jMB("The operating system is out of memory or resources.", "LaunchViewer");
				return FALSE;
			case ERROR_FILE_NOT_FOUND:
				jt_sprintf(csMsg,_T("File '%s' not found."), csVwr);
				jMB(csMsg, jS(LaunchViewer));
				return FALSE;
			case ERROR_PATH_NOT_FOUND:
				jt_sprintf(csMsg,_T("Path of file '%s' not found."), csVwr);
				jMB(csMsg, jS(LaunchViewer));
				return FALSE;
			case ERROR_BAD_FORMAT:
				jt_sprintf(csMsg,_T("The executable for file '%s' is invalid (non-Win32?.exe or error in .exe image)."), csVwr);
				jMB(csMsg, jS(LaunchViewer));
				return FALSE;
			case SE_ERR_ACCESSDENIED:
				jt_sprintf(csMsg,_T("The operating system denied access to file '%s'."), csVwr);
				jMB(csMsg, jS(LaunchViewer));
				return FALSE;
			case SE_ERR_ASSOCINCOMPLETE:
				jt_sprintf(csMsg,_T("Name association for file %s' is incomplete or invalid."), csVwr);
				jMB(csMsg, jS(LaunchViewer));
				return FALSE;
			case SE_ERR_DDEBUSY:
				jMB("The DDE transaction could not be completed because other DDE transactions were being processed.", "LaunchViewer");
				return FALSE;
			case SE_ERR_DDEFAIL:
				jMB("The DDE transaction failed.", "LaunchViewer");
				return FALSE;
			case SE_ERR_DDETIMEOUT:
				jMB("The DDE transaction could not be completed because the request timed out.", "LaunchViewer");
				return FALSE;
			case SE_ERR_DLLNOTFOUND:
				jMB("The specified dynamic-link library was not found.", "LaunchViewer");
				return FALSE;
			case SE_ERR_NOASSOC:
				jt_sprintf(csMsg,_T("No association for file type of '%s' found."), csVwr);
				jMB(csMsg, jS(LaunchViewer));
				return FALSE;
			case SE_ERR_OOM:
				jMB("The system is out of memory or resources.", "LaunchViewer");
				return FALSE;
			case SE_ERR_SHARE:
				jMB("A sharing violation occurred.", "LaunchViewer");
				return FALSE;
			default:
				if (hinst < 32)
				{
					jt_sprintf(csMsg,_T("Unknown error %d returned from ShellExecute()."), hinst);
					jMB(csMsg, jS(LaunchViewer));
					return FALSE;
				}
				return TRUE;
			}
			return FALSE;
		}

		PSID jReportEvent::GetUserSID(PSID * ppSid)
		{
			BOOL bRet = FALSE;
			const DWORD INITIAL_SIZE = MAX_PATH;

			fname_t csAccName;
			DWORD size = INITIAL_SIZE;

			::GetUserName(csAccName, &size);

			// Validate the input parameters.
			if (jt_strlen(csAccName)==0 || ppSid == NULL)
			{
				return NULL;
			}


			// Create buffers that may be large enough.
			// If a buffer is too small, the count parameter will be set to the size needed.
			DWORD cbSid = 0;
			DWORD dwErrorCode = 0;
			DWORD dwSidBufferSize = INITIAL_SIZE;
			DWORD cchDomainName = INITIAL_SIZE;
			fname_t csDomainName;
			SID_NAME_USE eSidType;
			HRESULT hr = 0;


			// Create buffers for the SID and the domain name.
			*ppSid = (PSID) new BYTE[dwSidBufferSize];
			if (*ppSid == NULL)
			{
				return NULL;
			}
			memset(*ppSid, 0, dwSidBufferSize);


			// Obtain the SID for the account name passed.
			for ( ; ; )
			{

				// Set the count variables to the buffer sizes and retrieve the SID.
				cbSid = dwSidBufferSize;
				bRet = LookupAccountName(NULL, csAccName, *ppSid, &cbSid, csDomainName, &cchDomainName,&eSidType);
				if (bRet)
				{
					if (IsValidSid(*ppSid) == FALSE)
					{
						fname_t csMsg;
						jt_sprintf(csMsg,_T("The SID for %s is invalid.\n"), csAccName);
						jMB(csMsg, jS(LaunchViewer));
						bRet = FALSE;
					}
					break;
				}
				dwErrorCode = GetLastError();


				// Check if one of the buffers was too small.
				if (dwErrorCode == ERROR_INSUFFICIENT_BUFFER)
				{
					if (cbSid > dwSidBufferSize)
					{
						// Reallocate memory for the SID buffer.
						OutputDebugStringA("The SID buffer was too small. It will be reallocated.\n");
						FreeSid(*ppSid);
						*ppSid = (PSID) new BYTE[cbSid];
						if (*ppSid == NULL)
						{
							return NULL; 
						}
						memset(*ppSid, 0, cbSid);
						dwSidBufferSize = cbSid;
					}
				}
				else
				{
					fname_t csMsg;
					jt_sprintf(csMsg,_T("LookupAccountNameW failed. GetLastError returned: %d\n"), dwErrorCode);
					jMB(csMsg, jS(LaunchViewer));
					hr = HRESULT_FROM_WIN32(dwErrorCode);
					break;
				}
			}

			// If we had an error, free memory of SID
			if (!bRet && *ppSid != NULL)
			{
				delete [] *ppSid;
				*ppSid = NULL; 
			}

			return *ppSid;
		}//PSID jReportEvent::GetUserSID(PSID * ppSid)

	}//namespace nLOG
}//namespace nMech

