#include "stdafx.h"
#include "Registry.h"

CRegistry::CRegistry(VOID)
{
	mRootKey	= NULL;
	mIsOpened	= FALSE;
}

CRegistry::~CRegistry(VOID)
{
}

BOOL CRegistry::Open(HKEY rootKey, LPCTSTR subKey)
{
	if (!subKey)
		return FALSE;

	if (mIsOpened)
		return FALSE;

	if (RegOpenKey(rootKey, subKey, &mRootKey) != ERROR_SUCCESS)
		return FALSE;

	mIsOpened = TRUE;

	return TRUE;
}

BOOL CRegistry::Close(VOID)
{
	if (RegCloseKey(mRootKey) != ERROR_SUCCESS)
		return FALSE;

	mIsOpened = FALSE;

	return TRUE;
}

BOOL CRegistry::CreateKey(HKEY rootKey, LPCTSTR subKey)
{
	if (!subKey)
		return FALSE;
	
	if (mIsOpened)
		return FALSE;

	if (RegCreateKey(rootKey, subKey, &mRootKey) != ERROR_SUCCESS)
		return FALSE;

	mIsOpened = TRUE;

	return TRUE;
}

BOOL CRegistry::DeleteKey(HKEY rootKey, LPCTSTR subKey)
{
	if (!subKey)
		return FALSE;

	if (RegDeleteKey(rootKey, subKey) != ERROR_SUCCESS)
		return FALSE;

	return TRUE;
}

BOOL CRegistry::SetValue(LPCTSTR valueName, LPCTSTR value)
{
	if (!valueName || !value)
		return FALSE;

	if (!mIsOpened)
		return FALSE;

	if (RegSetValueEx(mRootKey, valueName, 0, REG_SZ, (BYTE*) value, (DWORD) _tcslen(value) * sizeof(TCHAR))
		!= ERROR_SUCCESS)
		return FALSE;

	return TRUE;
}

BOOL CRegistry::SetValueForMultiSz(LPCTSTR valueName, LPCTSTR value, DWORD byteLength)
{
	if (!valueName || !value)
		return FALSE;

	if (!mIsOpened)
		return FALSE;

	if (RegSetValueEx(mRootKey, valueName, 0, REG_MULTI_SZ, (BYTE*) value, byteLength)
		!= ERROR_SUCCESS)
		return FALSE;

	return TRUE;
}

BOOL CRegistry::SetValue(LPCTSTR valueName, DWORD value)
{
	if (!valueName)
		return FALSE;

	if (!mIsOpened)
		return FALSE;

	if (RegSetValueEx(mRootKey, valueName, 0, REG_DWORD, (BYTE*) &value, sizeof(DWORD))
		!= ERROR_SUCCESS)
		return FALSE;

	return TRUE;
}

BOOL CRegistry::GetValue(LPCTSTR valueName, LPCTSTR value, LPDWORD bufferLength)
{
	DWORD ValueType = 0;

	if (!valueName || !value || !bufferLength)
		return FALSE;

	if (!mIsOpened)
		return FALSE;

	if (RegQueryValueEx(mRootKey, valueName, 0, &ValueType, (BYTE*) value, bufferLength)
		!= ERROR_SUCCESS)
		return FALSE;

	return TRUE;
}

BOOL CRegistry::GetValue(LPCTSTR valueName, LPDWORD value)
{
	DWORD	ValueType		= 0;
	DWORD	BufferLength	= sizeof(DWORD);

	if (!valueName || !value)
		return FALSE;

	if (!mIsOpened)
		return FALSE;

	if (RegQueryValueEx(mRootKey, valueName, 0, &ValueType, (BYTE*) value, &BufferLength)
		!= ERROR_SUCCESS)
		return FALSE;

	return TRUE;
}

BOOL CRegistry::DeleteValue(LPCTSTR valueName)
{
	if (!valueName)
		return FALSE;

	if (!mIsOpened)
		return FALSE;

	if (RegDeleteValue(mRootKey, valueName) != ERROR_SUCCESS)
		return FALSE;

	return TRUE;
}
