// HistoryTree.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "HistoryTree.h"
#include <Wininet.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistoryTree

CHistoryTree::CHistoryTree()
{
	m_pMalloc = NULL;
	SHGetMalloc(&m_pMalloc);
	m_bIE4 = FALSE;
}

CHistoryTree::~CHistoryTree()
{
	//	m_wndHisTree.DeleteAllItems();
	m_wndHisTree.m_astrHist.RemoveAll();
    m_pMalloc->Release();
}
void CHistoryTree::Destroy()
{
}



/////////////////////////////////////////////////////////////////////////////
// CHistoryTree message handlers

LPCTSTR CHistoryTree::GetTitle()
{
	strTitle.LoadString(IDS_TITLE_HIS);
	return strTitle;
}

BOOL CHistoryTree::Initialize()
{
	// TODO: Add your command handler code here
	
	m_wndHisTree.DeleteAllItems();
	m_wndHisTree.m_astrHist.RemoveAll();
	
	LPITEMIDLIST pidlHistory = NULL;
	
	   HRESULT hr = SHGetSpecialFolderLocation(NULL, CSIDL_HISTORY, &pidlHistory);
	   if (NOERROR != hr)
	   {
		   // AfxMessageBox("Can't get history folder.");
		   m_bIE4=TRUE;
		   //for ie4 or win95
		   CWaitCursor wc;
		   
		   IUrlHistoryStg2* pUrlHistoryStg2 = NULL;
		   HRESULT hr = CoCreateInstance(CLSID_CUrlHistory,
			   NULL, CLSCTX_INPROC, IID_IUrlHistoryStg2,
			   (void**)&pUrlHistoryStg2);
		   if (SUCCEEDED(hr))
		   {     
			   IEnumSTATURL* pEnum;
			   hr = pUrlHistoryStg2->EnumUrls(&pEnum);
			   ULONG size;
			   STATURL staturl;
			   int ind=1;
			   hr = pEnum->Next(1, &staturl, &size);
			   if(SUCCEEDED(hr))
			   {
				   m_wndHisTree.DeleteAllItems();
				   m_wndHisTree.m_astrHist.RemoveAll();
			   }
			   CTime ttime = CTime::GetCurrentTime();
			   today = ttime.GetDayOfWeek();
			   int t;
			   if(today==1)
				   t=8;
			   else
				   t=today;
			   CTimeSpan tt(t-2,0,0,0);
			   ttime =ttime - tt;
			   
			   CTime t2(ttime.GetYear(), ttime.GetMonth(), ttime.GetDay(),0,0,0);
			   montime = t2;
			   
			   while(size>0)
			   {
				   if(insertUrl(&staturl,ind))
				   {
					   m_wndHisTree.m_astrHist.Add(CString(staturl.pwcsUrl));
					   ind++;
				   }
				   pEnum->Next(1, &staturl, &size);
			   }
			   //open today
			   
			   
			   pEnum->Release();
			   pUrlHistoryStg2->Release();
		   }
		   
		   return FALSE;
	   }
	   
	   IShellFolder* psfDesktop;
	   IShellFolder* psfHistory;
	   
	   hr = SHGetDesktopFolder(&psfDesktop);
	   if (NOERROR != hr)
	   {
		   AfxMessageBox(_T("Can't get desktop."));
		   return FALSE;
	   }
	   
	   hr = psfDesktop->BindToObject(pidlHistory, NULL, IID_IShellFolder,
		   (LPVOID*)&psfHistory);
	   psfDesktop->Release();
	   
	   if (NOERROR != hr)
	   {
		   AfxMessageBox(_T("Can't bind history folder."));
		   return FALSE;
	   }
	   
	   AddHistory(psfHistory, NULL);
	   
	   m_pMalloc->Free(pidlHistory);
	   
	   psfHistory->Release();
	   
	   return TRUE;
}

BOOL CHistoryTree::Create(CWnd* pParent)
{
	if (!m_wndHisTree.Create(WS_BORDER|WS_CHILD|WS_VISIBLE|TVS_SHOWSELALWAYS|TVS_LINESATROOT|
		TVS_FULLROWSELECT |TVS_TRACKSELECT ,
		CRect(0,0,0,0), pParent, 100))
	{
		TRACE0("Failed to create instant bar child\n");
		return 0;		// fail to create
	}

	CWnd* pTT = m_wndHisTree.FromHandle((HWND) m_wndHisTree.SendMessage(TVM_GETTOOLTIPS));
    if (pTT != NULL)
		pTT->SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0,
		SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
	
	CImageList img;

	img.Create(16, 16, ILC_COLORDDB|ILC_MASK, 4, 1);
	HBITMAP hbmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_TREE));
	ImageList_AddMasked(img.GetSafeHandle(), hbmp, RGB(255,0,255));

	m_wndHisTree.SetImageList(&img, TVSIL_NORMAL);
	img.Detach();
	
	m_wndHisTree.m_pHisTree = this;
	
	return TRUE;
}

CWnd* CHistoryTree::GetWindow()
{
	return (CWnd*)&m_wndHisTree;
}


//for ie4 and win95
BOOL CHistoryTree::insertUrl(LPSTATURL pSUrl, int ind)
{
	//get host
	CString url(pSUrl->pwcsUrl);
	CString host;
	CString l = url.Left(5);
	int i;
	if(l == _T("https"))
	{
		host = url.Right(url.GetLength()-8);
		i=host.Find('/');
		if(i>0)
			host=host.Left(i);
	}
	if(l == _T("http:"))
	{
		host = url.Right(url.GetLength()-7);
		i=host.Find('/');
		if(i>0)
			host=host.Left(i);
	}
	else if(l == _T("ftp:/"))
	{
		host = url.Right(url.GetLength()-6);
		i=host.Find('/');
		if(i>0)
			host=host.Left(i);
	}
	else if(l == _T("file:"))
	{
		host.LoadString(IDS_MY_COMPUTER);
	}
	else
		return FALSE;
	
	//get date
	CTime ttime(pSUrl->ftLastVisited);
	CTime ttime2(pSUrl->ftLastUpdated);
	if( ttime < ttime2)
		ttime=ttime2;
	
	CTime filetime(ttime.GetYear(), ttime.GetMonth(), ttime.GetDay(),0,0,0);
	
	int d;
	int week = 0, data;
	CString root;
	CTimeSpan ts = montime-filetime;
	if(filetime < montime)
	{
		week = int(ts.GetDays() + 6)/7;
	}
	
	if(week>1)
	{
		CString tw;
		tw.Format(_T("%i"), week);
		root.LoadString(IDS_WEEKS_AGO);
		root = tw + root;
		data = -week-7;
	}
	else if(week==1)
	{
		root.LoadString(IDS_LAST_WEEK);
		data = -8;
	}
	else
	{
		d=filetime.GetDayOfWeek();
		if(d==today)
			root.LoadString(IDS_TODAY);
		else
			root.LoadString(IDS_SUNDAY+d-1);
		data = -9+d;
		if(d==1)
			data=-1;
	}
	
	HTREEITEM hitem;
	hitem = FindAndInsert(NULL, root, 0,0, data);
	
	hitem = FindAndInsert(hitem, host, 1,3);
	
	CString temp;
	temp = pSUrl->pwcsTitle;
	if(temp.IsEmpty())
	{
		temp=pSUrl->pwcsUrl;
		i=temp.ReverseFind('/');
		temp=temp.Right(temp.GetLength()-i-1);
	}
	HTREEITEM hnode = m_wndHisTree.InsertItem(temp, 2, 2, hitem);
	m_wndHisTree.SetItemData(hnode, ind);
	
	return TRUE;
}

HTREEITEM CHistoryTree::FindAndInsert(HTREEITEM  hRoot, LPCTSTR text, int nImg, int nOImg,int data)
{
	HTREEITEM hit, hnode = NULL, pre=TVI_FIRST;
	BOOL found=FALSE;
	hit = m_wndHisTree.GetChildItem(hRoot);
	if(data>=0)
		while(hit!=NULL && !found)
		{
			if(m_wndHisTree.GetItemText(hit).CompareNoCase(text)==1)
			{
				hnode = m_wndHisTree.InsertItem(text, nImg, nOImg, hRoot,TVI_SORT);
				found = TRUE;
			}
			else if(m_wndHisTree.GetItemText(hit).CompareNoCase(text)==0)
			{
				found = TRUE;
				hnode = hit;
			}
			else
				hit = m_wndHisTree.GetNextSiblingItem(hit);
		}
		else //compare with data
			while(hit!=NULL && !found)
			{
				if((signed)m_wndHisTree.GetItemData(hit)>data)
				{
					hnode = m_wndHisTree.InsertItem(text, nImg, nOImg, hRoot,pre);
					found = TRUE;
				}
				else if((signed)m_wndHisTree.GetItemData(hit)==data)
				{
					found = TRUE;
					hnode = hit;
				}
				else
				{
					pre=hit;
					hit = m_wndHisTree.GetNextSiblingItem(hit);
				}
			}
			
			if(!found)
				hnode = m_wndHisTree.InsertItem(text, nImg, nOImg, hRoot,TVI_LAST);
			
			m_wndHisTree.SetItemData(hnode, data);
			
			return hnode;
}
//end

BOOL CHistoryTree::Update(int nLevel)
{
	if(m_bIE4)
	{
		HTREEITEM hit, pre=NULL;
		BOOL found=FALSE;
		int d;
		CString text;
		text.LoadString(IDS_TODAY);
		//now only update today.
		if (nLevel == 0)
		{
			//get today item
			hit = m_wndHisTree.GetChildItem(NULL);
			while(hit!=NULL && !found)
			{
				if(m_wndHisTree.GetItemText(hit).CompareNoCase(text)==0)
				{
					found = TRUE;
				}
				else
				{
					pre = hit;
					hit = m_wndHisTree.GetNextSiblingItem(hit);
				}
			}
			int day;
			if(found)
			{
				d = (int)m_wndHisTree.GetItemData(hit);
				day=d+9;
				if(d==-1)
					day=1;
				
				//delete today
				m_wndHisTree.DeleteItem(hit);
				m_wndHisTree.Expand(pre, TVE_COLLAPSE);
			}
			else
				day=today;
			
			//insert history after that day
			CWaitCursor wc;
			
			IUrlHistoryStg2* pUrlHistoryStg2 = NULL;
			HRESULT hr = CoCreateInstance(CLSID_CUrlHistory,
				NULL, CLSCTX_INPROC, IID_IUrlHistoryStg2,
				(void**)&pUrlHistoryStg2);
			if (SUCCEEDED(hr))
			{     
				IEnumSTATURL* pEnum;
				hr = pUrlHistoryStg2->EnumUrls(&pEnum);
				ULONG size;
				STATURL staturl;
				int ind = (int)m_wndHisTree.m_astrHist.GetUpperBound() + 2;
				hr = pEnum->Next(1,&staturl, &size);
				if(!SUCCEEDED(hr))
				{
					return FALSE;
				}
				CTime ttime = CTime::GetCurrentTime();
				today = ttime.GetDayOfWeek();
				CTime lastday;
				
				if(today == day)
				{
					CTime t1(ttime.GetYear(), ttime.GetMonth(), ttime.GetDay(),0,0,0);
					lastday = t1;
				}
				else
				{
					CTimeSpan tsp(1,0,0,0);
					ttime = ttime-tsp;
					CTime t1(ttime.GetYear(), ttime.GetMonth(), ttime.GetDay(),0,0,0);
					lastday = t1;
					ttime = ttime +tsp;
				}
				int t;
				if (today == 1)
					t=8;
				else
					t = today;
				CTimeSpan tt(t-2,0,0,0);
				ttime =ttime - tt;
				
				CTime t2(ttime.GetYear(), ttime.GetMonth(), ttime.GetDay(),0,0,0);
				montime = t2;
				
				while(size>0)
				{
					CTime t3(staturl.ftLastVisited);
					if(t3>=lastday)
					{
						if(insertUrl(&staturl,ind))
						{
							m_wndHisTree.m_astrHist.Add(CString(staturl.pwcsUrl));
							ind++;
						}
					}
					pEnum->Next(1,&staturl, &size);
				}
				//open today
				
				
				pEnum->Release();
				pUrlHistoryStg2->Release();
			}
			return TRUE;
		}
		return TRUE;
	}
	
	//following is for ie5 and win98
	
	//remove the children of Today
	HTREEITEM hit;
	BOOL found=FALSE;
	CString text;
	text.LoadString(IDS_TODAY);
	//get today item
	hit = m_wndHisTree.GetChildItem(NULL);
	while(hit!=NULL && !found)
	{
		if(m_wndHisTree.GetItemText(hit).CompareNoCase(text)==0)
			found = TRUE;
		else
			hit = m_wndHisTree.GetNextSiblingItem(hit);
	}
	if(found)
	{
		//delete today
		m_wndHisTree.DeleteItem(hit);
		//m_wndHisTree.Expand(pre, TVE_COLLAPSE);
	}
	LPITEMIDLIST pidlHistory = NULL;
	
	   HRESULT hr = SHGetSpecialFolderLocation(NULL, CSIDL_HISTORY, &pidlHistory);
	   if (NOERROR != hr)
		   return FALSE;
	   
	   IShellFolder* psfDesktop;
	   IShellFolder* psfHistory;
	   
	   hr = SHGetDesktopFolder(&psfDesktop);
	   if (NOERROR != hr)
		   return FALSE;
	   
	   hr = psfDesktop->BindToObject(pidlHistory, NULL, IID_IShellFolder,
		   (LPVOID*)&psfHistory);
	   psfDesktop->Release();
	   
	   if (NOERROR != hr)
		   return FALSE;
	   
	   AddHistory(psfHistory, NULL,0,0,TRUE);
	   
	   m_pMalloc->Free(pidlHistory);
	   
	   psfHistory->Release();
	   
	   return TRUE;
}

void CHistoryTree::AddHistory(IShellFolder *pFolder, HTREEITEM root, int nImg, int nOImg, BOOL bNeedCmp)
{
	USES_CONVERSION;
	
	if(pFolder == NULL)
		return;
	
	//enum history
	IEnumIDList* pItems = NULL;
	LPITEMIDLIST pidlNext = NULL;
	CString lpszName;
	//TCHAR lpszFileName[MAX_PATH];
	LPTSTR lpszURL = NULL;
	
	DWORD dwEntrySize=0;
	
	// Enumerate all object in the given folder
	HRESULT hr = pFolder->EnumObjects(NULL, SHCONTF_FOLDERS|SHCONTF_NONFOLDERS|SHCONTF_INCLUDEHIDDEN , &pItems);
	while (NOERROR == hr)
	{
		hr = pItems->Next(1, &pidlNext, NULL);
		if (NOERROR == hr)
		{
			GetName(pFolder, pidlNext, SHGDN_NORMAL, lpszName);
			
			//add folder
			BOOL found = FALSE;
			if(bNeedCmp)
			{
				HTREEITEM hit;
				//get today item
				hit = m_wndHisTree.GetChildItem(root);
				while(hit!=NULL && !found)
				{
					if(m_wndHisTree.GetItemText(hit).CompareNoCase(lpszName)==0)
						found = TRUE;
					else
						hit = m_wndHisTree.GetNextSiblingItem(hit);
				}
			}
			if(!found)
			{
				HTREEITEM hItem;
				if(nImg==0)
					hItem = m_wndHisTree.InsertItem(lpszName, nImg, nOImg, root ,TVI_LAST);
				else
					hItem = m_wndHisTree.InsertItem(lpszName, nImg, nOImg, root ,TVI_SORT);
				
				if(nImg==2)
					ResolveHistory(pFolder, pidlNext, &lpszURL);
				if (lpszURL)
				{
					// Add the URL to the array and free lpszURL
					// since it was created with IMalloc::Alloc
					m_wndHisTree.m_astrHist.Add(lpszURL);
					m_wndHisTree.SetItemData(hItem, m_wndHisTree.m_astrHist.GetSize());
					
					//is the url cached?
					dwEntrySize = 0;
					if(_tcsncmp(lpszURL, _T("file:"), 5) != 0)
					{
#if _MSC_VER < 1300
						if (!GetUrlCacheEntryInfoExA(T2A(lpszURL), NULL, &dwEntrySize, NULL, NULL, NULL, 0))
#else
						if (!GetUrlCacheEntryInfoEx(lpszURL, NULL, &dwEntrySize, NULL, NULL, NULL, 0))
#endif
						{
							if (GetLastError() == ERROR_FILE_NOT_FOUND)
							{
								m_wndHisTree.SetItemState(hItem, TVIS_CUT, TVIS_CUT);
							}
						}
					}
					
					m_pMalloc->Free(lpszURL);
					lpszURL = NULL;
				}
			}
			
			if (pidlNext)
				m_pMalloc->Free(pidlNext);
		}
	}
	if (pItems)
		pItems->Release();
}

BOOL CHistoryTree::ResolveHistory(IShellFolder* pFolder, LPCITEMIDLIST pidl, LPTSTR* lpszURL)
{
	IShellLink* pShellLink;
	
	*lpszURL = NULL;  // Assume failure
	
	// Get a pointer to the IShellLink interface from the given folder
	HRESULT hr = pFolder->GetUIObjectOf(NULL, 1, &pidl, IID_IShellLink, NULL, (LPVOID*)&pShellLink);
	if (SUCCEEDED(hr))
	{
		WIN32_FIND_DATA wfd;      
		
		hr = pShellLink->Resolve(AfxGetApp()->m_pMainWnd->m_hWnd, SLR_NO_UI); 
		if (NOERROR == hr)
		{
			// Get the path to the link target. 
			*lpszURL = (LPTSTR)m_pMalloc->Alloc(MAX_PATH);  // Must remember to Free later
			
			hr = pShellLink->GetPath(*lpszURL, MAX_PATH - 1, (WIN32_FIND_DATA*)&wfd, SLGP_UNCPRIORITY);
		}
		pShellLink->Release();
	}
	
	if(SUCCEEDED(hr))
		return TRUE;
	else
		return FALSE;
}
