// tool_FileParserDoc.h : interface of the Ctool_FileParserDoc class
//


#pragma once


class Ctool_FileParserDoc : public CDocument
{
protected: // create from serialization only
	Ctool_FileParserDoc();
	DECLARE_DYNCREATE(Ctool_FileParserDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~Ctool_FileParserDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
};
