#if !defined(AFX_FILTERCONTENT_H__ADC84E14_6BC3_4D78_83E1_5A29A4986F23__INCLUDED_)
#define AFX_FILTERCONTENT_H__ADC84E14_6BC3_4D78_83E1_5A29A4986F23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FilterContent.h : header file
//


// {7D4A199C-0182-4332-95D0-65CD3C74AB86}
static const GUID CLSID_FilterContent = 
{ 0x7d4a199c, 0x182, 0x4332, { 0x95, 0xd0, 0x65, 0xcd, 0x3c, 0x74, 0xab, 0x86 } };

#if (_MSC_VER <= 1200) && !defined(_WIN64)

// IA64 Macros:
#ifndef HANDLE_PTR
#define HANDLE_PTR DWORD
#endif

#endif
/////////////////////////////////////////////////////////////////////////////
// CFilterContent command target

class CFilterContent : public CCmdTarget
{
	DECLARE_DYNCREATE(CFilterContent)

	CFilterContent();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilterContent)
	//}}AFX_VIRTUAL
	
	BEGIN_INTERFACE_PART(ClassFactory, IClassFactory)
        STDMETHOD(CreateInstance)( 
            /* [unique][in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        STDMETHOD(LockServer)( 
            /* [in] */ BOOL fLock);
	END_INTERFACE_PART(ClassFactory)


	BEGIN_INTERFACE_PART(InternetProtocol, IInternetProtocol)
		STDMETHOD(Start)(
			LPCWSTR szUrl,
			IInternetProtocolSink *pIProtSink,
			IInternetBindInfo *pIBindInfo,
			DWORD grfSTI,
			HANDLE_PTR dwReserved);
		STDMETHOD(Continue)(PROTOCOLDATA *pStateInfo);
		STDMETHOD(Abort)(HRESULT hrReason,DWORD dwOptions);
		STDMETHOD(Terminate)(DWORD dwOptions);
		STDMETHOD(Suspend)();
		STDMETHOD(Resume)();
		STDMETHOD(Read)(void *pv,ULONG cb,ULONG *pcbRead);
		STDMETHOD(Seek)(
			LARGE_INTEGER dlibMove,
			DWORD dwOrigin,
			ULARGE_INTEGER *plibNewPosition);
		STDMETHOD(LockRequest)(DWORD dwOptions);
		STDMETHOD(UnlockRequest)();


	END_INTERFACE_PART(InternetProtocol)



// Implementation
protected:
	virtual ~CFilterContent();

	// Generated message map functions
	//{{AFX_MSG(CFilterContent)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILTERCONTENT_H__ADC84E14_6BC3_4D78_83E1_5A29A4986F23__INCLUDED_)
