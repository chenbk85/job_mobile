// MouseManager.h: interface for the CMouseManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOUSEMANAGER_H__19F3DE40_E931_4E71_A2BF_C2F8406C520E__INCLUDED_)
#define AFX_MOUSEMANAGER_H__19F3DE40_E931_4E71_A2BF_C2F8406C520E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MOUSE_AREA_TAB		0
#define MOUSE_AREA_TABBAR	1
#define MOUSE_AREA_BROWSER	2


struct MOUSECLICKS
{
	DWORD dwMouse;
	int nArea;
	ACCEL accel;
};

class CMouseManager  
{
public:
	typedef CArray<MOUSECLICKS, MOUSECLICKS&> CMouseClicksArray;

	static BOOL Load();
	static void Save();
	
	static int FindMouseCommand(int nArea, DWORD dwMouse);
	static CString GetMouseString(DWORD dwMouse);
	static void AddCommand(DWORD dwMouse, ACCEL accel, int nArea);

	static CMouseClicksArray& GetArray() 
	{
		return m_arrMouse;
	}


protected:
	static CMap<DWORD, DWORD, CString, CString> m_mapStrings;
	static CMouseClicksArray m_arrMouse;
};

#endif // !defined(AFX_MOUSEMANAGER_H__19F3DE40_E931_4E71_A2BF_C2F8406C520E__INCLUDED_)
