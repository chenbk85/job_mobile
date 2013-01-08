// ---------------------------------------------------------------------------
// FILE: markupUnicode.h
// ---------------------------------------------------------------------------
#pragma once


// ---------------------------------------------------------------------------
// TYPEDEFS
// ---------------------------------------------------------------------------
typedef BOOL (* FP_WCHAR_XML_OUTPUT)(void * x, const WCHAR * buf, unsigned int size);


// ---------------------------------------------------------------------------
// FUNCTIONS
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// WARNING: not standard XML in that we don't convert \r\n to \n
// ---------------------------------------------------------------------------
class CUnicodeMarkup
{
public:
	// navigation
	BOOL			Load(const WCHAR * filename);
	BOOL			SetDoc(WCHAR * document, const WCHAR * documentname = NULL);
	BOOL			IsWellFormed(void) const;
	BOOL			FindElem(const WCHAR * pathname = NULL);
	BOOL			FindChildElem(const WCHAR * pathname = NULL);
	BOOL			FindPrevElem(const WCHAR * tagname = NULL);
	BOOL			FindPrevChildElem(const WCHAR * tagname = NULL);
	BOOL			IntoElem(void);
	BOOL			OutOfElem(void);
	void			ResetPos(void);
	void			ResetChildPos(void);
	void			ResetMainPos(void);
	unsigned int	SavePos(void);
	BOOL			RestorePos(unsigned int pos, BOOL release = FALSE);
	void			ReleasePos(unsigned int pos);
	const WCHAR *	GetTagName(void) const;
	BOOL			GetTagName(WCHAR * str, unsigned int buflen, unsigned int * len = NULL) const;
	const WCHAR *	GetChildTagName(void) const;
	BOOL			GetChildTagName(WCHAR * str, unsigned int buflen, unsigned int * len = NULL) const;
	const WCHAR *	GetData(void) const;
	BOOL			GetData(WCHAR * str, unsigned int buflen, unsigned int * len = NULL) const;
	const WCHAR *	GetChildData(void) const;
	BOOL			GetChildData(WCHAR * str, unsigned int buflen, unsigned int * len = NULL) const;
	const WCHAR *	FindGetData(const WCHAR * pathname);
	BOOL			HasAttrib(const WCHAR * attribname) const;
	BOOL			HasChildAttrib(const WCHAR * attribname) const;
	const WCHAR *	GetAttrib(const WCHAR * attribname) const;
	const WCHAR *	GetChildAttrib(const WCHAR * attribname) const;
	const WCHAR *	GetAttribName(unsigned int n) const;

//	int				FindNode(int nodetype = 0);
//	int				GetNodeType(void);
//	BOOL			SavePos(WCHAR * posname = NULL);
//	BOOL			RestorePos(WCHAR * posname = NULL);
//	WCHAR *			GetElemPath(void);
//	WCHAR *			GetChildElemPath(void);

	// creation
	BOOL			Save(WCHAR * filename) const;
	unsigned int	GetSaveSize(void) const;
	BOOL			SaveToBuffer(WCHAR *& buf, unsigned int & buflen) const;
	BOOL			AddElem(const WCHAR * tagname, const WCHAR * data = NULL, DWORD flags = 0);
	BOOL			InsertElem(const WCHAR * tagname, const WCHAR * data = NULL, DWORD flags = 0);
	BOOL			AddChildElem(const WCHAR * tagname, const WCHAR * data = NULL, DWORD flags = 0);
	BOOL			InsertChildElem(const WCHAR * tagname, const WCHAR * data = NULL, DWORD flags = 0);
	BOOL			AddAttrib(const WCHAR * attribname, const WCHAR * value);
	BOOL			AddChildAttrib(const WCHAR * attribname, const WCHAR * value);
//	BOOL			AddNode(int nodetype, WCHAR * text);
//	BOOL			InsertNode(int nodetype, WCHAR * text);
//	BOOL			AddSubDoc(WCHAR * subdoc);
//	BOOL			InsertSubDoc(WCHAR * subdoc);
//	WCHAR *			GetSubDoc(void);
//	BOOL			AddChildSubDoc(WCHAR * subdoc);
//	BOOL			InsertChildSubDoc(WCHAR * subdoc);
//	WCHAR *			GetChildSubDoc(void);
//	BOOL			SetElemContent(WCHAR * content);
//	WCHAR *			GetElemContent(void);

	// modification
	BOOL			RemoveElem(void);
	BOOL			RemoveChildElem(void);
	BOOL			SetData(const WCHAR * data, int flags = 0);
	BOOL			SetChildData(const WCHAR * data, int flags = 0);
	BOOL			SetAttrib(const WCHAR * attribname, const WCHAR * value);
	BOOL			SetChildAttrib(const WCHAR * attribname, const WCHAR * value);
	BOOL			RemoveAttrib(const WCHAR * attribname);
	BOOL			RemoveChildAttrib(const WCHAR * attribname);
	BOOL			FindSetData(const WCHAR * pathname, const WCHAR * data, int flags = 0);
//	BOOL			RemoveNode(void);

	// string helpers
	static BOOL CUnicodeMarkup::StringToXMLEscapedString(WCHAR * dest, int destLen, const WCHAR * src);

	void			Init(void);
	void			Free(void);

	CUnicodeMarkup(
		void);

	~CUnicodeMarkup(
		void);

protected:
	struct Element
	{
		WCHAR *				m_tagStart;
		unsigned int		m_tagLen;
		DWORD				m_tagCRC;
		WCHAR *				m_dataStart;
		unsigned int		m_dataLen;
		Element *			m_Parent;
		Element *			m_childFirst;
		Element *			m_childLast;
		unsigned int		m_childCount;
		Element *			m_sibPrev;
		Element *			m_sibNext;
		Element *			m_attribFirst;
		Element *			m_attribLast;
		unsigned int		m_attribCount;

		DWORD				m_Flags;

		enum
		{
			FLAG_FREE_TAG,									// need to free m_tagStart
			FLAG_FREE_DATA,									// need to free m_dataStart
			FLAG_ATTRIBUTE,									// this flag is set if the element is an attribute
			FLAG_CDATA,										// this flag is set
			FLAG_GARBAGE,									// the element is in the garbage list
			FLAG_COMMENT,									// element is a comment
			FLAG_PROGRAM_INSTRUCTION,						// element is a program instruction
		};

		void Init(
			void)
		{
			memclear(this, sizeof(*this));
		}

		BOOL IsEmpty(void) const;

		// navigation
		Element *	GetNextSibling(void) const;
		Element *	GetPrevSibling(void) const;
		Element *	GetFirstChild(void) const;
		Element *	FindAttrib(const WCHAR * attribname) const;
		BOOL		GetTag(WCHAR * str, unsigned int buflen, unsigned int * len) const;
		BOOL		GetData(WCHAR * str, unsigned int buflen, unsigned int * len) const;

		// creation
		BOOL		SetTag(const WCHAR * tagname, int flags = 0);
		BOOL		SetData(const WCHAR * data, int flags = 0);
	};

	struct ElementPool
	{
		enum
		{
			ELEMENT_BLOCK_SIZE = 256,
		};
		struct ElementBlock
		{
			ElementBlock *	next;
		};
		Element *			m_Garbage;
		ElementBlock *		m_ElemBlocks;
		int					m_nFreeNode;
		unsigned int		m_nCount;

		void		AllocateBlock(void);
		Element *	GetFromBlock(void);
		Element *	GetFromGarbage(void);
		Element *	GetFree(void);
		void		Recycle(Element * element);
		void		Init(void);
		void		Destroy(void);
	};

	struct Token
	{
		WCHAR *				m_Start;
		unsigned int		m_nLen;
		BOOL				m_bIsString;
		DWORD				m_dwCRC;
	};

	struct Cursor
	{
		Element *			m_ParentPos;					// cursor into parse tree
		Element *			m_MainPos;						// cursor into parse tree
		Element *			m_ChildPos;						// cursor into parse tree
		unsigned int		m_Counter;						// used to keep track of cursor validity

		void		Clear(void);
		void		MoveParentPos(Element * pos);
		void		MoveMainPos(Element * pos);
		void		MoveChildPos(Element * pos);
		void		ClearMainPos(void);
		void		ClearChildPos(void);
	};

	struct CursorPool
	{
		static const unsigned int XML_MAX_CURSORS =		64;
		static const unsigned int XML_INVALID_CURSOR =	(unsigned int)(-1);

		Cursor				m_Cursors[XML_MAX_CURSORS];

		void			Clear(void);
		unsigned int	GetFreeCursor(void);
		void			ReleaseCursor(unsigned int index);
		Cursor *		GetCursor(unsigned int index);
	};

	enum
	{
		FLAG_FREE_DOCUMENT,									// need to free m_Document
	};

	WCHAR					m_Filename[MAX_PATH];			// filename
	WCHAR *					m_Document;						// pointer to document string, mangled on parse
	WCHAR *					m_ParseCur;						// used only during parsing to keep track of last valid point
	WCHAR					m_chPrevChar;					// used only during parsing to keep track of eaten char
	DWORD					m_Flags;
	ElementPool				m_ElementPool;					// pool of elements
	Element *				m_ElementTree;					// parse structure of xml document
	Cursor					m_Cursor;
	CursorPool				m_CursorPool;					// pool of user cursors
	unsigned int			m_ModifyCounter;				// counter to track modifications to parse tree for cursor validity

	// parsing functions
	unsigned int	GetParseErrorLine(void) const;
	void			Error(char * fmt, ...) const;
	void			Clear(void);
	BOOL			ParseSkipWhiteSpace(WCHAR *& str);
	BOOL			ParseOpenTag(WCHAR *& str);
	BOOL			ParseScanTo(WCHAR *& str, const WCHAR * expect);
	BOOL			ParseTagName(Token & token, WCHAR *& str);
	BOOL			ParseAttributes(Element * elem, WCHAR *& str, BOOL & isempty);
	BOOL			ParseStartTag(Element * elem, WCHAR *& str, BOOL & isempty);
	int				ParseGetDataEntity(WCHAR *& str);
	BOOL			ParseGetData(Token & token, WCHAR *& str);
	BOOL			ParseEndTag(Element * elem, WCHAR *& str);
	BOOL			ParseGetToken(Token & token, WCHAR *& str);
	Element *		ParseElement(Element * parent, WCHAR *& str);

	// element manipulation functions
	Element *		ElementAdd(Element * parent);
	Element *		ElementAdd(Element * parent, const WCHAR * tagname, const WCHAR * data, DWORD flags = 0);
	Element *		ElementInsertAfter(Element * prev);
	Element *		ElementInsertAfter(Element * prev, const WCHAR * tagname, const WCHAR * data, DWORD flags = 0);
	Element *		ElementInsertBefore(Element * next);
	Element *		ElementInsertBefore(Element * next, const WCHAR * tagname, const WCHAR * data, DWORD flags = 0);
	void			ElementDelete(Element * elem);
	Element *		ElementAddAttrib(Element * elem);
	BOOL			ElementSetAttrib(Element * elem, const WCHAR * attribname, const WCHAR * value);
	void			AttribDelete(Element * attrib);

	// other protected functions
	BOOL			Save(void * x, const Element * elem, FP_WCHAR_XML_OUTPUT fp) const;
};
