// MouseManager.cpp: implementation of the CMouseManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MouseManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMap<DWORD, DWORD, CString, CString> CMouseManager::m_mapStrings;
CArray<MOUSECLICKS, MOUSECLICKS&> CMouseManager::m_arrMouse;


BOOL CMouseManager::Load()
{
	BOOL	bSucess = FALSE;
	BYTE*	pData = NULL;
	UINT	uDataSize;

	if (!AfxGetApp()->GetProfileBinary(_T("MouseManager"), _T("State"), (LPBYTE*) &pData, &uDataSize))
	{
		ASSERT (pData == NULL);
		return FALSE;
	}

	ASSERT (pData != NULL);

	try
	{
		CMemFile file (pData, uDataSize);
		CArchive ar (&file, CArchive::load);

		m_arrMouse.Serialize (ar);
		bSucess = TRUE;
	}
	catch (CMemoryException* pEx)
	{
		pEx->Delete ();
		TRACE(_T("Memory exception in CRegistry::Read ()!\n"));
	}
	catch (CArchiveException* pEx)
	{
		pEx->Delete ();
		TRACE(_T("CArchiveException exception in CRegistry::Read ()!\n"));
	}

	delete pData;
	return bSucess;	
}

void CMouseManager::Save()
{
	BOOL bRes = FALSE;
	try
	{
		CMemFile file;

		{
			CArchive ar (&file, CArchive::store);

			m_arrMouse.Serialize (ar);
			ar.Flush ();
		}

		DWORD dwDataSize = (DWORD)file.GetLength ();
		LPBYTE lpbData = file.Detach ();

		if (lpbData == NULL)
		{
			return ;
		}

		bRes = AfxGetApp()->WriteProfileBinary(_T("MouseManager"), _T("State"), lpbData, (UINT) dwDataSize);

		free (lpbData);
	}
	catch (CMemoryException* pEx)
	{
		pEx->Delete ();
		TRACE(_T("Memory exception in CRegistry::Write ()!\n"));
	}
}


int CMouseManager::FindMouseCommand(int nArea, DWORD dwMouse)
{
	for (int i = 0; i < m_arrMouse.GetSize(); i++)
	{
		MOUSECLICKS& mc = m_arrMouse[i];
		if (mc.nArea == nArea && mc.dwMouse == dwMouse)
		{
			int nVirt = (GetKeyState(VK_CONTROL) < 0 ? FCONTROL : 0) |
				(GetKeyState(VK_SHIFT) < 0 ? FSHIFT : 0) |
				(GetKeyState(VK_MENU) < 0 ? FALT : 0);
			
			if (nVirt == mc.accel.fVirt)			
				return mc.accel.cmd;
		}
	}

	return -1;
}

CString CMouseManager::GetMouseString(DWORD dwMouse)
{
	CString strMouse;
	if (!m_mapStrings.Lookup(dwMouse, strMouse))
	{
		VERIFY(strMouse.LoadString(dwMouse));
		m_mapStrings.SetAt(dwMouse, strMouse);
	}	
	return strMouse;	
}

void CMouseManager::AddCommand(DWORD dwMouse, ACCEL accel, int nArea)
{
	MOUSECLICKS mc = {dwMouse, nArea};
	mc.accel = accel;
	
	m_arrMouse.Add(mc);

}
