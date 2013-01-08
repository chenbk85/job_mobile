// ---------------------------------------------------------------------------
// FILE: markup.h
// ---------------------------------------------------------------------------
#ifndef _MARKUP_H_
#define _MARKUP_H_


// ---------------------------------------------------------------------------
// TYPEDEFS
// ---------------------------------------------------------------------------
typedef BOOL (* FP_XML_OUTPUT)(void * x, const TCHAR * buf, unsigned int size);


// ---------------------------------------------------------------------------
// FUNCTIONS
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// WARNING: not standard XML in that we don't convert \r\n to \n
// ---------------------------------------------------------------------------
class CMarkup
{
public:
	// navigation
	BOOL			Load(const char * filename);
	BOOL			Load(const WCHAR * filename);
	BOOL			SetDoc(TCHAR * document, const TCHAR * documentname = NULL);
	BOOL			IsWellFormed(void) const;
	BOOL			FindElem(const TCHAR * pathname = NULL);
	BOOL			FindChildElem(const TCHAR * pathname = NULL, const BOOL bByName = FALSE, const BOOL bDeepSearch = FALSE);
	BOOL			FindPrevElem(const TCHAR * tagname = NULL);
	BOOL			FindPrevChildElem(const TCHAR * tagname = NULL);
	BOOL			IntoElem(void);
	BOOL			OutOfElem(void);
	void			ResetPos(void);
	void			ResetChildPos(void);
	void			ResetMainPos(void);
	unsigned int	SavePos(void);
	BOOL			RestorePos(unsigned int pos, BOOL release = FALSE);
	void			ReleasePos(unsigned int pos);
	const TCHAR *	GetTagName(void) const;
	BOOL			GetTagName(TCHAR * str, unsigned int buflen, unsigned int * len = NULL) const;
	const TCHAR *	GetChildTagName(void) const;
	BOOL			GetChildTagName(TCHAR * str, unsigned int buflen, unsigned int * len = NULL) const;
	const TCHAR *	GetData(void) const;
	BOOL			GetData(TCHAR * str, unsigned int buflen, unsigned int * len = NULL) const;
	const TCHAR *	GetChildData(void) const;
	BOOL			GetChildData(TCHAR * str, unsigned int buflen, unsigned int * len = NULL) const;
	const TCHAR *	FindGetData(const TCHAR * pathname);
	BOOL			HasAttrib(const TCHAR * attribname) const;
	BOOL			HasChildAttrib(const TCHAR * attribname) const;
	const TCHAR *	GetAttrib(const TCHAR * attribname) const;
	const TCHAR *	GetChildAttrib(const TCHAR * attribname) const;
	const TCHAR *	GetAttribName(unsigned int n) const;

//	int				FindNode(int nodetype = 0);
//	int				GetNodeType(void);
//	BOOL			SavePos(TCHAR * posname = NULL);
//	BOOL			RestorePos(TCHAR * posname = NULL);
//	TCHAR *			GetElemPath(void);
//	TCHAR *			GetChildElemPath(void);

	// creation
	BOOL			Save(const char * filename) const;
	BOOL			Save(const WCHAR * filename) const;
	unsigned int	GetSaveSize(void) const;
	BOOL			SaveToBuffer(TCHAR *& buf, unsigned int & buflen) const;
	BOOL			AddElem(const TCHAR * tagname, const TCHAR * data = NULL, DWORD flags = 0);
	BOOL			InsertElem(const TCHAR * tagname, const TCHAR * data = NULL, DWORD flags = 0);
	BOOL			AddChildElem(const TCHAR * tagname, const TCHAR * data = NULL, DWORD flags = 0);
	BOOL			InsertChildElem(const TCHAR * tagname, const TCHAR * data = NULL, DWORD flags = 0);
	BOOL			AddAttrib(const TCHAR * attribname, const TCHAR * value);
	BOOL			AddChildAttrib(const TCHAR * attribname, const TCHAR * value);
//	BOOL			AddNode(int nodetype, TCHAR * text);
//	BOOL			InsertNode(int nodetype, TCHAR * text);
//	BOOL			AddSubDoc(TCHAR * subdoc);
//	BOOL			InsertSubDoc(TCHAR * subdoc);
//	TCHAR *			GetSubDoc(void);
//	BOOL			AddChildSubDoc(TCHAR * subdoc);
//	BOOL			InsertChildSubDoc(TCHAR * subdoc);
//	TCHAR *			GetChildSubDoc(void);
//	BOOL			SetElemContent(TCHAR * content);
//	TCHAR *			GetElemContent(void);

	// modification
	BOOL			RemoveElem(void);
	BOOL			RemoveChildElem(void);
	BOOL			SetData(const TCHAR * data, int flags = 0);
	BOOL			SetChildData(const TCHAR * data, int flags = 0);
	BOOL			SetAttrib(const TCHAR * attribname, const TCHAR * value);
	BOOL			SetChildAttrib(const TCHAR * attribname, const TCHAR * value);
	BOOL			RemoveAttrib(const TCHAR * attribname);
	BOOL			RemoveChildAttrib(const TCHAR * attribname);
	BOOL			FindSetData(const TCHAR * pathname, const TCHAR * data, int flags = 0);
//	BOOL			RemoveNode(void);

	// string helper
	static BOOL		StringToXMLEscapedString(char * dest, int destLen, const char * src);

	void			Init(void);
	void			Free(void);

	CMarkup(
		void);

	~CMarkup(
		void);

protected:
	struct Element
	{
		TCHAR *				m_tagStart;
		unsigned int		m_tagLen;
		DWORD				m_tagCRC;
		TCHAR *				m_dataStart;
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
		Element *	FindAttrib(const TCHAR * attribname) const;
		BOOL		GetTag(TCHAR * str, unsigned int buflen, unsigned int * len) const;
		BOOL		GetData(TCHAR * str, unsigned int buflen, unsigned int * len) const;

		// creation
		BOOL		SetTag(const TCHAR * tagname, int flags = 0);
		BOOL		SetData(const TCHAR * data, int flags = 0);
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
		TCHAR *				m_Start;
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

	TCHAR					m_Filename[MAX_PATH];			// filename
	TCHAR *					m_Document;						// pointer to document string, mangled on parse
	TCHAR *					m_ParseCur;						// used only during parsing to keep track of last valid point
	TCHAR					m_chPrevChar;					// used only during parsing to keep track of eaten char
	DWORD					m_Flags;
	ElementPool				m_ElementPool;					// pool of elements
	Element *				m_ElementTree;					// parse structure of xml document
	Cursor					m_Cursor;
	CursorPool				m_CursorPool;					// pool of user cursors
	unsigned int			m_ModifyCounter;				// counter to track modifications to parse tree for cursor validity

	// parsing functions
	unsigned int	GetParseErrorLine(void) const;
	void			Error(TCHAR * fmt, ...) const;
	void			Clear(void);
	BOOL			ParseSkipWhiteSpace(TCHAR *& str);
	BOOL			ParseOpenTag(TCHAR *& str);
	BOOL			ParseScanTo(TCHAR *& str, const TCHAR * expect);
	BOOL			ParseTagName(Token & token, TCHAR *& str);
	BOOL			ParseAttributes(Element * elem, TCHAR *& str, BOOL & isempty);
	BOOL			ParseStartTag(Element * elem, TCHAR *& str, BOOL & isempty);
	int				ParseGetDataEntity(TCHAR *& str);
	BOOL			ParseGetData(Token & token, TCHAR *& str);
	BOOL			ParseEndTag(Element * elem, TCHAR *& str);
	BOOL			ParseGetToken(Token & token, TCHAR *& str);
	Element *		ParseElement(Element * parent, TCHAR *& str);

	// element manipulation functions
	Element *		ElementAdd(Element * parent);
	Element *		ElementAdd(Element * parent, const TCHAR * tagname, const TCHAR * data, DWORD flags = 0);
	Element *		ElementInsertAfter(Element * prev);
	Element *		ElementInsertAfter(Element * prev, const TCHAR * tagname, const TCHAR * data, DWORD flags = 0);
	Element *		ElementInsertBefore(Element * next);
	Element *		ElementInsertBefore(Element * next, const TCHAR * tagname, const TCHAR * data, DWORD flags = 0);
	void			ElementDelete(Element * elem);
	Element *		ElementAddAttrib(Element * elem);
	BOOL			ElementSetAttrib(Element * elem, const TCHAR * attribname, const TCHAR * value);
	void			AttribDelete(Element * attrib);

	// other protected functions
	BOOL			Save(void * x, const Element * elem, FP_XML_OUTPUT fp) const;
};


#endif // _MARKUP_H_
