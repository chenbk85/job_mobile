#include <stdafx.h>
#include <windows.h>
#include "header/jDefine.h"

#include "jLog_ReportEvent.h"
using namespace nMech;


bool jRegist_EventDLL(cstr szLogCategory ,cstr szSourceName,cstr szDLLPath)
{
	// Event Source name.
	//wchar_t *szLogCategory = L"jServer";
	//wchar_t *szSourceName = L"SampleEventSourceName";
	//DLL that contains the event messages (descriptions).
	//wchar_t *szDLLPath = L"Z:\\job_taebak\\bin\\client\\udebug_vc80\\jLog_ReportEvent.dll"; 
	// This number of categories for the event source.
	DWORD dwCategoryNum = 1;

	HKEY hk; 
	DWORD dwData, dwDisp; 
	TCHAR szBuf[MAX_PATH]; 
	size_t cchSize = MAX_PATH;

	// Create the event source as a subkey of the log. 
	jt_sprintf(szBuf, L"SYSTEM\\CurrentControlSet\\Services\\EventLog\\%s\\%s",szLogCategory, szSourceName); 

	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, szBuf, 
		0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_WRITE, NULL, &hk, &dwDisp)) 
	{
		printf("Could not create the registry key."); 
		return false;
	}

	// Set the name of the message file. 

	if (RegSetValueEx(hk,             // subkey handle 
		L"EventMessageFile",        // value name 
		0,                         // must be zero 
		REG_EXPAND_SZ,             // value type 
		(LPBYTE) szDLLPath,          // pointer to value data 
		(DWORD) (lstrlen(szDLLPath)+1)*sizeof(TCHAR))) // data size
	{
		printf("Could not set the event message file."); 
		RegCloseKey(hk); 
		return false;
	}

	// Set the supported event types. 

	dwData = EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE | 
		EVENTLOG_INFORMATION_TYPE; 

	if (RegSetValueEx(hk,      // subkey handle 
		L"TypesSupported",  // value name 
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
		L"CategoryMessageFile",     // value name 
		0,                         // must be zero 
		REG_EXPAND_SZ,             // value type 
		(LPBYTE) szDLLPath,          // pointer to value data 
		(DWORD) (lstrlen(szDLLPath)+1)*sizeof(TCHAR))) // data size
	{
		printf("Could not set the category message file."); 
		RegCloseKey(hk); 
		return false;
	}

	if (RegSetValueEx(hk,            // subkey handle 
		L"CategoryCount",         // value name 
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
	return true;
}



void __cdecl wmain(int argc, LPWSTR *argv)
{
	tcstr szLogCategory = L"jServer";               // The event log name.
	tcstr szSourceName = L"SampleEventSourceName";  // The event source name.
	jRegist_EventDLL(szLogCategory,szSourceName,_T("Z:\\job_taebak\\bin\\client\\udebug_vc80\\jLog_ReportEvent.dll"));

	DWORD dwEventID = MSG_BAD_COMMAND;               // The event identifier.
	WORD cInserts = 1;                               // The count of insert strings.
	LPCWSTR szMsg = L"insertString";                 // The insert strings.

	HANDLE h; 

	// Get a handle to the event log.
	h = RegisterEventSource(NULL,  // Use local computer. 
		szSourceName);           // Event source name. 
	if (h == NULL) 
	{
		printf("Cannot register the event source."); 
		return;
	}

	// Report the event.

	if (!ReportEvent(h,           // Event log handle. 
		EVENTLOG_ERROR_TYPE,  // Event type. 
		NULL,                 // Event category.  
		dwEventID,            // Event identifier. 
		NULL,                 // No user security identifier. 
		cInserts,             // Number of substitution strings. 
		0,                    // No data. 
		&szMsg,               // Pointer to strings. 
		NULL))                // No data. 
	{
		printf("Cannot report the event."); 
	}

	DeregisterEventSource(h); 
	return;
}


