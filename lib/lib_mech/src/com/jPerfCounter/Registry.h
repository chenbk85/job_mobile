#pragma once

class CRegistry
{
public:
	CRegistry(VOID);
	virtual ~CRegistry(VOID);
public:
	BOOL Open(HKEY rootKey, LPCTSTR subKey);
	BOOL Close(VOID);

	BOOL CreateKey(HKEY rootKey, LPCTSTR subKey);
	BOOL DeleteKey(HKEY rootKey, LPCTSTR subKey);

	BOOL SetValue(LPCTSTR valueName, LPCTSTR value);
	BOOL SetValue(LPCTSTR valueName, DWORD value);
	BOOL SetValueForMultiSz(LPCTSTR valueName, LPCTSTR value, DWORD byteLength);

	BOOL GetValue(LPCTSTR valueName, LPCTSTR value, LPDWORD bufferLength);
	BOOL GetValue(LPCTSTR valueName, LPDWORD value);

	BOOL DeleteValue(LPCTSTR valueName);
private:
	HKEY	mRootKey;
	BOOL	mIsOpened;
};
