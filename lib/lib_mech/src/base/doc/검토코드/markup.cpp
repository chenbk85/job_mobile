/** 
\file markup.cpp
\brief XML 파일 처리. 완전 표준적인 XML 처리는 아님. 
*/

//-----------------------------------------------------------------------------
// INCLUDES
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "appcommon.h"
#include "markup.h"
#include "performance.h"
#if ISVERSION(SERVER_VERSION)
// 이창용 / 2010-2-13 / 서버 복원 작업
	//#ifndef _UNDEF_WPP_
#include "markup.cpp.tmh"
#endif
	//#endif
//-----------------------------------------------------------

// ---------------------------------------------------------------------------
// DEBUG
// ---------------------------------------------------------------------------
#if !ISVERSION(RETAIL_VERSION)
#define MarkupError(fmt, ...)				LogMessage(ERROR_LOG, fmt, __VA_ARGS__)
#else
#define MarkupError(fmt, ...)
#endif


// ---------------------------------------------------------------------------
// GLOBALS
// ---------------------------------------------------------------------------
// constraints -- mostly to prevent malicious data from causing overflows, etc
#define XML_MAX_FILE_SIZE					(1 * GIGA)	// only applies to when we load the file via CMarkup directly & when we save
#define XML_MAX_COMMENT_LEN					(1 * MEGA)
#define XML_MAX_PARSE_DEPTH					64			// since we parse recursively, prevent blowing call stack
#define XML_MAX_NAME_LEN					256
#define XML_MAX_DATA_LEN					655360	// TRAVIS: FIXME DID TO ALLOW FOR MASSIVE PATHNODE SETS
#define XML_MAX_ELEMENTS					(MEGA * 10)


// ---------------------------------------------------------------------------
// GLOBALS
// ---------------------------------------------------------------------------
static const TCHAR * EMPTY_STRING =				_T("");


// ---------------------------------------------------------------------------
// FUNCTIONS
// ---------------------------------------------------------------------------
#define XMLStrCmp(a, b)						PStrCmp(a, b)


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
static inline unsigned int XMLStrLen(
	const TCHAR * str)
{
	return (unsigned int)PStrLen(str);
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
static void XMLStrLenAndCRC(
	const TCHAR * str,
	unsigned int & len,
	DWORD & crc)
{
	crc = 0;
	if (!str)
	{
		len = 0;
		return;
	}
	const TCHAR * cur = str;
	while (*cur)
	{
		crc = STR_HASH_ADDC(crc, *cur);
		cur++;
	}
	len = (unsigned int)(cur - str);
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
unsigned int XMLStrPrintf(
	TCHAR * buf,
	unsigned int buflen,
	const TCHAR * format,
	...)
{
	va_list args;
	va_start(args, format);

	unsigned int len = _vsctprintf(format, args);		// _vsctprintf doesn't count terminating '\0'
	if (len + 1 > buflen)
	{
		return 0;
	}
	PStrVprintf(buf, buflen, format, args);
	return len;
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
BOOL XMLFileWrite(
	HANDLE file,
	const TCHAR * buf,
	unsigned int len)
{
	DWORD bytes_written;
	if (!WriteFile(file, buf, len, &bytes_written, NULL))
	{
		return FALSE;
	}
	if (bytes_written != len)
	{
		return FALSE;
	}
	return TRUE;
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
BOOL XMLFilePrint(
	HANDLE file,
	const TCHAR * format,
	...)
{
	enum
	{
		SAVE_BUFFER_LEN = 4096,
	};
	TCHAR buf[SAVE_BUFFER_LEN];

	va_list args;
	va_start(args, format);

	unsigned int len = _vsctprintf(format, args);		// _vsctprintf doesn't count terminating '\0'
	if (len + 1 > SAVE_BUFFER_LEN)
	{
		return FALSE;
	}
	PStrVprintf(buf, SAVE_BUFFER_LEN, format, args);

	return XMLFileWrite(file, buf, len);
}


// ---------------------------------------------------------------------------
// CMarkup::Element FUNCTIONS
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// return TRUE if element is empty (no data or children)
// ---------------------------------------------------------------------------
BOOL CMarkup::Element::IsEmpty(
	void) const
{
	return (m_dataLen == 0 && GetFirstChild() == NULL);
}


// ---------------------------------------------------------------------------
// return the next (named) sibling
// the purpose of this is to skip over any comments or pinstructions
// ---------------------------------------------------------------------------
CMarkup::Element * CMarkup::Element::GetNextSibling(
	void) const
{
	Element * cur = m_sibNext;
	while (cur)
	{
		if (cur->m_tagLen > 0)
		{
			break;
		}
		cur = cur->m_sibNext;
	}
	return cur;
}


// ---------------------------------------------------------------------------
// return the prev (named) sibling
// the purpose of this is to skip over any comments or pinstructions
// ---------------------------------------------------------------------------
CMarkup::Element * CMarkup::Element::GetPrevSibling(
	void) const
{
	Element * cur = m_sibPrev;
	while (cur)
	{
		if (cur->m_tagLen > 0)
		{
			break;
		}
		cur = cur->m_sibPrev;
	}
	return cur;
}


// ---------------------------------------------------------------------------
// return the first (named) child
// this skips over any children which are comments or pinstructions
// ---------------------------------------------------------------------------
CMarkup::Element * CMarkup::Element::GetFirstChild(
	void) const
{
	Element * cur = m_childFirst;
	while (cur)
	{
		if (cur->m_tagLen > 0)
		{
			break;
		}
		cur = cur->m_sibNext;
	}
	return cur;	
}


// ---------------------------------------------------------------------------
// find an attribute by name
// ---------------------------------------------------------------------------
CMarkup::Element * CMarkup::Element::FindAttrib(
	const TCHAR * attribname) const
{
	ASSERT_RETNULL(attribname);

	if (m_attribCount <= 2)
	{
		Element * attrib = m_attribFirst;
		while (attrib)
		{
			if (XMLStrCmp(attrib->m_tagStart, attribname) == 0)
			{
				break;
			}
			attrib = attrib->m_sibNext;
		}
		return attrib;
	}

	unsigned int len;
	DWORD crc;
	XMLStrLenAndCRC(attribname, len, crc);

	Element * attrib = m_attribFirst;
	while (attrib)
	{
		if (attrib->m_tagCRC == crc && XMLStrCmp(attrib->m_tagStart, attribname) == 0)
		{
			break;
		}
		attrib = attrib->m_sibNext;
	}
	return attrib;
}


// ---------------------------------------------------------------------------
// set the tag for an element by copy
// ---------------------------------------------------------------------------
BOOL CMarkup::Element::SetTag(
	const TCHAR * tagname,
	int flags /* = 0 */)
{
	m_Flags |= flags;
	if (TESTBIT(m_Flags, Element::FLAG_FREE_TAG))
	{
		FREE(g_ScratchAllocator, m_tagStart);
		m_tagStart = NULL;
		m_tagLen = 0;
		m_tagCRC = 0;
	}
	if (!tagname)
	{
		m_tagStart = NULL;
		m_tagLen = 0;
		m_tagCRC = 0;
		return FALSE;
	}
	XMLStrLenAndCRC(tagname, m_tagLen, m_tagCRC);
	ASSERT_DO(m_tagLen < XML_MAX_NAME_LEN)
	{
		m_tagStart = NULL;
		m_tagLen = 0;
		m_tagCRC = 0;
		return FALSE;
	}
	m_tagStart = (TCHAR *)MALLOC(g_ScratchAllocator, (m_tagLen + 1) * sizeof(TCHAR));
	ASSERT_RETFALSE(MemoryCopy(m_tagStart, (m_tagLen + 1) * sizeof(TCHAR), tagname, (m_tagLen + 1) * sizeof(TCHAR)));
	SETBIT(m_Flags, Element::FLAG_FREE_TAG);
	return TRUE;
}


// ---------------------------------------------------------------------------
// set the data for an element by copy
// ---------------------------------------------------------------------------
BOOL CMarkup::Element::SetData(
	const TCHAR * data,
	int flags /* = 0 */)
{
	m_Flags |= flags;
	if (TESTBIT(m_Flags, Element::FLAG_FREE_DATA))
	{
		FREE(g_ScratchAllocator, m_dataStart);
		m_dataStart = NULL;
		m_dataLen = 0;
	}
	if (!data)
	{
		m_dataStart = NULL;
		m_dataLen = 0;
		return FALSE;
	}
	m_dataLen = XMLStrLen(data);
	ASSERT_DO(m_dataLen < XML_MAX_DATA_LEN)
	{
		m_dataStart = NULL;
		m_dataLen = 0;
		return FALSE;
	}
	m_dataStart = (TCHAR *)MALLOC(g_ScratchAllocator, (m_dataLen + 1) * sizeof(TCHAR));
	ASSERT_RETFALSE(MemoryCopy(m_dataStart, (m_dataLen + 1) * sizeof(TCHAR), data, (m_dataLen + 1) * sizeof(TCHAR)));
	SETBIT(m_Flags, Element::FLAG_FREE_DATA);
	return TRUE;
}


// ---------------------------------------------------------------------------
// get the tag for an element by copy
// ---------------------------------------------------------------------------
BOOL CMarkup::Element::GetTag(
	TCHAR * str,
	unsigned int buflen,
	unsigned int * len) const
{
	if (len)
	{
		*len = m_tagLen;
	}
	if (!str)
	{
		return FALSE;
	}
	ASSERT_DO(buflen > m_tagLen)
	{
		str[0] = 0;
		return FALSE;
	}
	if (!m_tagStart)
	{
		str[0] = 0;
		return TRUE;
	}
	ASSERT_RETFALSE(MemoryCopy(str, buflen * sizeof(TCHAR), m_tagStart, (m_tagLen + 1) * sizeof(TCHAR)));
	if (len)
	{
		*len = m_tagLen;
	}
	return TRUE;
}


// ---------------------------------------------------------------------------
// get the data for an element by copy
// ---------------------------------------------------------------------------
BOOL CMarkup::Element::GetData(
	TCHAR * str,
	unsigned int buflen,
	unsigned int * len) const
{
	if (len)
	{
		*len = m_dataLen;
	}
	if (!str)
	{
		return FALSE;
	}
	ASSERT_DO(buflen > m_dataLen)
	{
		str[0] = 0;
		return FALSE;
	}
	if (!m_dataStart)
	{
		str[0] = 0;
		return TRUE;
	}
	ASSERT_RETFALSE(MemoryCopy(str, buflen * sizeof(TCHAR), m_dataStart, (m_dataLen + 1) * sizeof(TCHAR)));
	return TRUE;
}


// ---------------------------------------------------------------------------
// CMarkup::ElementPool FUNCTIONS
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// initialize the element pool
// ---------------------------------------------------------------------------
void CMarkup::ElementPool::Init(
	void)
{
	m_Garbage = NULL;
	m_ElemBlocks = NULL;
	m_nFreeNode = -1;
	m_nCount = 0;
}

		
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CMarkup::ElementPool::Destroy(
	void)
{
	ElementBlock * next = m_ElemBlocks;
	ElementBlock * curr = NULL;
	while ((curr = next) != NULL)
	{
		next = curr->next;

		// free all allocated text data
		Element * elem = (Element *)(((char *)curr) + sizeof(ElementBlock));
		for (int ii = 0; ii < m_nFreeNode; ++ii, ++elem)
		{
			if (TESTBIT(elem->m_Flags, Element::FLAG_FREE_DATA) && elem->m_dataStart)
			{
				FREE(g_ScratchAllocator, elem->m_dataStart);
			}
			if (TESTBIT(elem->m_Flags, Element::FLAG_FREE_TAG) && elem->m_tagStart)
			{
				FREE(g_ScratchAllocator, elem->m_tagStart);
			}
		}
		m_nFreeNode = ELEMENT_BLOCK_SIZE;

		FREE(g_ScratchAllocator, curr);
	}
	m_ElemBlocks = NULL;
	m_nFreeNode = -1;
	m_Garbage = NULL;
	m_nCount = 0;
}

		
// ---------------------------------------------------------------------------
// get an element from the garbage list
// ---------------------------------------------------------------------------
CMarkup::Element * CMarkup::ElementPool::GetFromGarbage(
	void)
{
	Element * elem = m_Garbage;
	m_Garbage = elem->m_sibNext;
	return elem;
}


// ---------------------------------------------------------------------------
// allocate a new block of elements
// ---------------------------------------------------------------------------
void CMarkup::ElementPool::AllocateBlock(
	void)
{
	ElementBlock * block = (ElementBlock *)MALLOC(g_ScratchAllocator, sizeof(ElementBlock) + sizeof(Element) * ELEMENT_BLOCK_SIZE);
	block->next = m_ElemBlocks;
	m_ElemBlocks = block;
	m_nFreeNode = 0;
}


// ---------------------------------------------------------------------------
// get a free element from the block list
// ---------------------------------------------------------------------------
CMarkup::Element * CMarkup::ElementPool::GetFromBlock(
	void)
{
	ASSERT_RETNULL(m_nCount < XML_MAX_ELEMENTS);

	ASSERT(m_nFreeNode >= 0 && m_nFreeNode < ELEMENT_BLOCK_SIZE);

	Element * ptr = (Element *)(((char *)m_ElemBlocks) + sizeof(ElementBlock));
	ptr += m_nFreeNode;
	
	m_nFreeNode++;
	if (m_nFreeNode >= ELEMENT_BLOCK_SIZE)
	{
		m_nFreeNode = -1;
	}

	m_nCount++;
	return ptr;
}


// ---------------------------------------------------------------------------
// get a free element from the pool (zero the element)
// ---------------------------------------------------------------------------
CMarkup::Element * CMarkup::ElementPool::GetFree(
	void)
{
	Element * ptr = NULL;

	if (m_Garbage)
	{
		ptr = GetFromGarbage();
	}
	else 
	{
		if (m_nFreeNode < 0)
		{
			AllocateBlock();
		}
		ptr = GetFromBlock();
		if (!ptr)
		{
			return NULL;
		}
	}
	ptr->Init();
	return ptr;
}


// ---------------------------------------------------------------------------
// recycle an element back to the element pool
// ---------------------------------------------------------------------------
void CMarkup::ElementPool::Recycle(
	Element * element)
{
	if (TESTBIT(element->m_Flags, Element::FLAG_FREE_TAG))
	{
		FREE(g_ScratchAllocator, element->m_tagStart);
	}
	if (TESTBIT(element->m_Flags, Element::FLAG_FREE_DATA))
	{
		FREE(g_ScratchAllocator, element->m_dataStart);
	}

	element->m_sibNext = m_Garbage;
	m_Garbage = element;
	element->m_Flags = 0;
	SETBIT(element->m_Flags, Element::FLAG_GARBAGE);
}


// ---------------------------------------------------------------------------
// XML CURSOR FUNCTIONS
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CMarkup::Cursor::Clear(
	void)
{
	m_ParentPos = NULL;
	m_MainPos = NULL;
	m_ChildPos = NULL;
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CMarkup::Cursor::MoveParentPos(
	Element * pos)
{
	m_ParentPos = pos;
	m_MainPos = NULL;
	m_ChildPos = NULL;
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CMarkup::Cursor::MoveMainPos(
	Element * pos)
{
	Element * set_child_to = NULL;

	if (pos)
	{
		ASSERT_RETURN(pos->m_Parent);

		if (pos == m_ParentPos)	// moving to our parent, so child pos should be set to the old main pos
		{
			set_child_to = m_MainPos;
		}
		m_ParentPos = pos->m_Parent;
	}
	m_MainPos = pos;
	m_ChildPos = set_child_to;
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CMarkup::Cursor::MoveChildPos(
	Element * pos)
{
	if (pos)
	{
		ASSERT_RETURN(pos->m_Parent);
		if (pos->m_Parent->m_Parent)
		{
			m_ParentPos = pos->m_Parent->m_Parent;
		}
		m_MainPos = pos->m_Parent;
	}
	m_ChildPos = pos;
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CMarkup::Cursor::ClearMainPos(
	void)
{
	m_MainPos = NULL;
	m_ChildPos = NULL;
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CMarkup::Cursor::ClearChildPos(
	void)
{
	m_ChildPos = NULL;
}


// ---------------------------------------------------------------------------
// XML CURSORPOOL FUNCTIONS
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CMarkup::CursorPool::Clear(
	void)
{
	memclear(m_Cursors, sizeof(Cursor) * XML_MAX_CURSORS);
	Cursor * cur = m_Cursors;
	for (unsigned int ii = 0; ii < XML_MAX_CURSORS; ++ii, ++cur)
	{
		cur->m_Counter = XML_INVALID_CURSOR;
	}
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
unsigned int CMarkup::CursorPool::GetFreeCursor(
	void)
{
	Cursor * cur = m_Cursors;
	for (unsigned int ii = 0; ii < XML_MAX_CURSORS; ++ii, ++cur)
	{
		if (cur->m_Counter == XML_INVALID_CURSOR)
		{
			return ii + 1;
		}
	}
	ASSERT(0);
	return 0;
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CMarkup::CursorPool::ReleaseCursor(
	unsigned int index)
{
	ASSERT_RETURN(index > 0 && index <= XML_MAX_CURSORS);
	m_Cursors[index - 1].m_Counter = XML_INVALID_CURSOR;
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
CMarkup::Cursor * CMarkup::CursorPool::GetCursor(
	unsigned int index)
{
	ASSERT_RETNULL(index > 0 && index <= XML_MAX_CURSORS);
	return m_Cursors + index - 1;
}


// ---------------------------------------------------------------------------
// XML FUNCTIONS
// ---------------------------------------------------------------------------

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
BOOL CMarkup::StringToXMLEscapedString(
	char * dest,
	int destLen,
	const char * src)
{
	if(!dest || destLen <= 0 || !src)
		return FALSE;

	while(src[0])
	{
		switch(src[0])
		{
		case '<':
			if(destLen < 5)
				return FALSE;
			dest[0] = '&'; dest[1] = 'l'; dest[2] = 't'; dest[3] = ';';
			dest += 4;
			destLen -= 4;
			break;
		case '>':
			if(destLen < 5)
				return FALSE;
			dest[0] = '&'; dest[1] = 'g'; dest[2] = 't'; dest[3] = ';';
			dest += 4;
			destLen -= 4;
			break;
		case '&':
			if(destLen < 6)
				return FALSE;
			dest[0] = '&'; dest[1] = 'a'; dest[2] = 'm'; dest[3] = 'p'; dest[4] = ';';
			dest += 5;
			destLen -= 5;
			break;
		case '\'':
			if(destLen < 7)
				return FALSE;
			dest[0] = '&'; dest[1] = 'a'; dest[2] = 'p'; dest[3] = 'o'; dest[4] = 's'; dest[5] = ';';
			dest += 6;
			destLen -= 6;
			break;
		case '\"':
			if(destLen < 7)
				return FALSE;
			dest[0] = '&'; dest[1] = 'q'; dest[2] = 'u'; dest[3] = 'o'; dest[4] = 't'; dest[5] = ';';
			dest += 6;
			destLen -= 6;
			break;
		default:
			if(destLen < 2)
				return FALSE;
			dest[0] = src[0];
			++dest;
			--destLen;
		}
		++src;
	}
	dest[0] = 0;
	return TRUE;
}

// ---------------------------------------------------------------------------
// Init
// ---------------------------------------------------------------------------
void CMarkup::Init(
	void)
{
	m_Document = NULL;
	m_Flags = 0;
	m_ParseCur = NULL;
	m_ElementTree = NULL;
	m_Filename[0] = 0;
	m_ElementPool.Init();
	m_Cursor.Clear();
	m_CursorPool.Clear();
	m_ModifyCounter = 0;
}


// ---------------------------------------------------------------------------
// constructor
// ---------------------------------------------------------------------------
CMarkup::CMarkup(
	void)
{
	Init();
}


// ---------------------------------------------------------------------------
// clear in preparation for reading a new document w/o destroying the object
// ---------------------------------------------------------------------------
void CMarkup::Clear(
	void)
{
	if (m_Document && TESTBIT(m_Flags, FLAG_FREE_DOCUMENT))
	{
		FREE(g_ScratchAllocator, m_Document);
		m_Document = NULL;
	}
	m_ParseCur = NULL;
	ElementDelete(m_ElementTree);
	m_ElementTree = NULL;
	m_Cursor.Clear();
	m_CursorPool.Clear();
	m_ModifyCounter = 0;
}


// ---------------------------------------------------------------------------
// Init
// ---------------------------------------------------------------------------
void CMarkup::Free(
	void)
{
	if (m_Document && TESTBIT(m_Flags, FLAG_FREE_DOCUMENT))
	{
		FREE(g_ScratchAllocator, m_Document);
		m_Document = NULL;
	}
	m_ElementPool.Destroy();
}


// ---------------------------------------------------------------------------
// destructor
// ---------------------------------------------------------------------------
CMarkup::~CMarkup(
	void)
{
	Free();
}


// ---------------------------------------------------------------------------
// add a new element to the end of the parent's child list
// ---------------------------------------------------------------------------
CMarkup::Element * CMarkup::ElementAdd(
	Element * parent)
{
	Element * elem = m_ElementPool.GetFree();
	if (!elem)
	{
		return NULL;
	}
	elem->m_Parent = parent;
	if (parent)
	{
		elem->m_sibPrev = parent->m_childLast;
		parent->m_childLast = elem;
		parent->m_childCount++;
	}
	if (elem->m_sibPrev)
	{
		elem->m_sibPrev->m_sibNext = elem;
	}
	else if (parent)
	{
		parent->m_childFirst = elem;
	}

	m_ModifyCounter++;

	return elem;
}


// ---------------------------------------------------------------------------
// add a new element to the end of the parent's child list
// ---------------------------------------------------------------------------
CMarkup::Element * CMarkup::ElementAdd(
	Element * parent,
	const TCHAR * tagname,
	const TCHAR * data,
	DWORD flags /* = 0 */)
{
	Element * elem = ElementAdd(parent);
	if (!elem)
	{
		return NULL;
	}
	elem->SetTag(tagname);
	elem->SetData(data);
	elem->m_Flags |= flags;

	m_ModifyCounter++;

	return elem;
}


// ---------------------------------------------------------------------------
// add a new element after the given element
// ---------------------------------------------------------------------------
CMarkup::Element * CMarkup::ElementInsertAfter(
	Element * prev)
{
	ASSERT_RETNULL(prev && prev->m_Parent);
	Element * elem = m_ElementPool.GetFree();
	if (!elem)
	{
		return NULL;
	}
	elem->m_Parent = prev->m_Parent;
	elem->m_sibPrev = prev;
	elem->m_sibNext = prev->m_sibNext;
	prev->m_sibNext = elem;
	if (elem->m_sibNext)
	{
		elem->m_sibNext->m_sibPrev = elem;
	}
	else
	{
		elem->m_Parent->m_childLast = elem;
	}

	m_ModifyCounter++;

	return elem;
}


// ---------------------------------------------------------------------------
// add a new element after the given element
// ---------------------------------------------------------------------------
CMarkup::Element * CMarkup::ElementInsertAfter(
	Element * prev,
	const TCHAR * tagname,
	const TCHAR * data,
	DWORD flags /* = 0 */)
{
	Element * elem = ElementInsertAfter(prev);
	if (!elem)
	{
		return NULL;
	}
	elem->SetTag(tagname);
	elem->SetData(data);
	elem->m_Flags |= flags;

	m_ModifyCounter++;

	return elem;
}


// ---------------------------------------------------------------------------
// add a new element before the given element
// ---------------------------------------------------------------------------
CMarkup::Element * CMarkup::ElementInsertBefore(
	Element * next)
{
	ASSERT_RETNULL(next && next->m_Parent);
	Element * elem = m_ElementPool.GetFree();
	if (!elem)
	{
		return NULL;
	}
	elem->m_Parent = next->m_Parent;
	elem->m_sibPrev = next->m_sibPrev;
	elem->m_sibNext = next;
	next->m_sibPrev = elem;
	if (elem->m_sibPrev)
	{
		elem->m_sibPrev->m_sibNext = elem;
	}
	else
	{
		elem->m_Parent->m_childFirst = elem;
	}

	elem->m_Parent->m_childCount++;
	m_ModifyCounter++;

	return elem;
}


// ---------------------------------------------------------------------------
// add a new element before the given element
// ---------------------------------------------------------------------------
CMarkup::Element * CMarkup::ElementInsertBefore(
	Element * next,
	const TCHAR * tagname,
	const TCHAR * data,
	DWORD flags /* = 0 */)
{
	Element * elem = ElementInsertBefore(next);
	if (!elem)
	{
		return NULL;
	}
	elem->SetTag(tagname);
	elem->SetData(data);
	elem->m_Flags |= flags;

	m_ModifyCounter++;

	return elem;
}


// ---------------------------------------------------------------------------
// recycle an element, first unhook it from parse tree
// ---------------------------------------------------------------------------
void CMarkup::ElementDelete(
	Element * elem)
{
	if (!elem)
	{
		return;
	}

	ASSERT(!TESTBIT(elem->m_Flags, Element::FLAG_ATTRIBUTE));

	// release all children
	while (elem->m_childFirst)
	{
		ElementDelete(elem->m_childFirst);
	}

	// release all attribs
	while (elem->m_attribFirst)
	{
		AttribDelete(elem->m_attribFirst);
	}

	if (TESTBIT(elem->m_Flags, Element::FLAG_FREE_TAG))
	{
		FREE(g_ScratchAllocator, elem->m_tagStart);
		elem->m_tagStart = NULL;
	}

	if (TESTBIT(elem->m_Flags, Element::FLAG_FREE_DATA))
	{
		FREE(g_ScratchAllocator, elem->m_dataStart);
		elem->m_dataStart = NULL;
	}

	// unhook from siblings & parent
	if (elem->m_sibPrev)
	{
		elem->m_sibPrev->m_sibNext = elem->m_sibNext;
	}
	else if (elem->m_Parent)
	{
		elem->m_Parent->m_childFirst = elem->m_sibNext;
	}
	if (elem->m_sibNext)
	{
		elem->m_sibNext->m_sibPrev = elem->m_sibPrev;
	}
	else if (elem->m_Parent)
	{
		elem->m_Parent->m_childLast = elem->m_sibPrev;
	}

	if (elem->m_Parent)
	{
		elem->m_Parent->m_childCount--;
	}
	m_ElementPool.Recycle(elem);

	m_ModifyCounter++;
}


// ---------------------------------------------------------------------------
// recycle an attribute, first unhook it from the parse tree
// ---------------------------------------------------------------------------
void CMarkup::AttribDelete(
	Element * attrib)
{
	if (!attrib)
	{
		return;
	}

	ASSERT(!TESTBIT(attrib->m_Flags, Element::FLAG_ATTRIBUTE));

	ASSERT(attrib->m_childFirst == NULL);
	ASSERT(attrib->m_attribFirst == NULL);

	// unhook from siblings & parent
	if (attrib->m_sibPrev)
	{
		attrib->m_sibPrev->m_sibNext = attrib->m_sibNext;
	}
	else if (attrib->m_Parent)
	{
		attrib->m_Parent->m_attribFirst = attrib->m_sibNext;
	}
	if (attrib->m_sibNext)
	{
		attrib->m_sibNext->m_sibPrev = attrib->m_sibPrev;
	}
	else if (attrib->m_Parent)
	{
		attrib->m_Parent->m_attribLast = attrib->m_sibPrev;
	}

	if (attrib->m_Parent)
	{
		attrib->m_Parent->m_attribCount--;
	}
	m_ElementPool.Recycle(attrib);
}


// ---------------------------------------------------------------------------
// add a new attrib node
// ---------------------------------------------------------------------------
CMarkup::Element * CMarkup::ElementAddAttrib(
	Element * elem)
{
	Element * attrib = m_ElementPool.GetFree();
	if (!attrib)
	{
		return NULL;
	}
	SETBIT(attrib->m_Flags, Element::FLAG_ATTRIBUTE);
	attrib->m_Parent = elem;
	attrib->m_sibPrev = elem->m_attribLast;
	elem->m_attribLast = attrib;
	if (attrib->m_sibPrev)
	{
		attrib->m_sibPrev->m_sibNext = attrib;
	}
	else
	{
		elem->m_attribFirst = attrib;
	}
	attrib->m_Parent->m_attribCount++;
	return attrib;
}


// ---------------------------------------------------------------------------
// add or set an attrib for a particular element
// ---------------------------------------------------------------------------
BOOL CMarkup::ElementSetAttrib(
	Element * elem,
	const TCHAR * attribname,
	const TCHAR * value)
{
	ASSERT_RETFALSE(attribname && attribname[0]);
	if (!elem)
	{
		return FALSE;
	}
	Element * attrib = elem->FindAttrib(attribname);
	if (attrib)
	{
		attrib->SetData(value);
	}
	else
	{
		attrib = ElementAddAttrib(elem);
		if (!attrib)
		{
			return FALSE;
		}
		attrib->SetTag(attribname);
		attrib->SetData(value);
	}
	return TRUE;
}


// ---------------------------------------------------------------------------
// PUBLIC XML FUNCTIONS
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// load a file
// ---------------------------------------------------------------------------
BOOL CMarkup::Load(
	const WCHAR * filename)
{
	HANDLE file = INVALID_HANDLE_VALUE;
	TCHAR * buffer = NULL;

	file = CreateFileW(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (file == INVALID_HANDLE_VALUE)
	{
		MarkupError(_T("unable to open file [%ls]\n"), filename);
		goto error;
	}

	LARGE_INTEGER llFilesize;
	if (!GetFileSizeEx(file, &llFilesize))
	{
		MarkupError(_T("unable to open file [%ls]\n"), filename);
		goto error;
	}
	if (llFilesize.HighPart > 0)
	{
		MarkupError(_T("unable to open file [%ls] -- File Too Big\n"), filename);
		goto error;
	}
	DWORD filesize = llFilesize.LowPart;
	if (filesize > XML_MAX_FILE_SIZE)
	{
		MarkupError(_T("unable to open file [%ls] -- File Too Big\n"), filename);
		ASSERT(filesize < XML_MAX_FILE_SIZE);
		goto error;
	}

	buffer = (TCHAR *)MALLOC(g_ScratchAllocator, filesize);
	if (!buffer)
	{
		MarkupError(_T("unable to allocate buffer for file read\n"));
		goto error;
	}

	DWORD bytes_read = 0;
	ASSERT(ReadFile(file, buffer, filesize, &bytes_read, NULL));
	if (bytes_read != filesize)
	{
		MarkupError(_T("unable to open file [%ls] -- Error reading file\n"), filename);
		goto error;
	}

	CloseHandle(file);
	file = INVALID_HANDLE_VALUE;
	
	// CHB 2007.01.15 - Well, just convert to TCHAR for now.
	TCHAR FilenameT[_countof(m_Filename)];
	PStrCvt(FilenameT, filename, _countof(FilenameT));
	BOOL result = SetDoc(buffer, FilenameT);
	SETBIT(m_Flags, FLAG_FREE_DOCUMENT);

	return result;

error:
	if (buffer)
	{
		FREE(g_ScratchAllocator, buffer);
	}
	if (file != INVALID_HANDLE_VALUE)
	{
		CloseHandle(file);
	}

	return FALSE;
}

BOOL CMarkup::Load(
	const char * filename)
{
	WCHAR buf[MAX_PATH];
	PStrCvt(buf, filename, _countof(buf));
	return Load(buf);
}


// ---------------------------------------------------------------------------
// parse a document & create the element tree
// ---------------------------------------------------------------------------
BOOL CMarkup::SetDoc(
	TCHAR * document,
	const TCHAR * documentname /* = NULL */)
{
#if ISVERSION(DEVELOPMENT)
	char timer_dbgstr[MAX_PATH];
	PStrPrintf(timer_dbgstr, MAX_PATH, "XML::SetDoc(%s)", (documentname ? documentname : "Unknown"));
	TIMER_STARTEX(timer_dbgstr, DEFAULT_PERF_THRESHOLD_LARGE);
#endif

	Clear();

	if (!document)
	{
		return FALSE;
	}

	if (documentname)
	{
		PStrCopy(m_Filename, documentname, MAX_PATH);
	}

	m_Document = document;
	TCHAR *szBufferOffset = m_Document;
	if(PStrICmp(m_Document, _T("<!DOCTYPE"), 9)==0)
	{
		TCHAR* pDelim = PStrChr( m_Document, _T('>') );
		szBufferOffset= pDelim + 1;
	}
	TCHAR * str = szBufferOffset;
	// start things off by eating up '<'
	if (!ParseOpenTag(str))
	{
		Clear();
		MarkupError(_T("'<' expected\n"));
		return FALSE;
	}

	if (!*str)
	{
		Clear();
		MarkupError(_T("unexpected end of file\n"));
		return FALSE;
	}
	Element * elem = m_ElementPool.GetFree();
	if (!elem)
	{
		MarkupError(_T("Exceeded maximum number of elements\n"));
		return FALSE;
	}
	elem->Init();

	while (*str)
	{
		if (ParseElement(elem, str) == NULL)
		{
			ElementDelete(elem);
			Clear();
			return FALSE;
		}
		if (!TESTBIT(elem->m_Flags, Element::FLAG_COMMENT) &&
			!TESTBIT(elem->m_Flags, Element::FLAG_PROGRAM_INSTRUCTION))
		{
			break;
		}
	}
	m_ElementTree = elem;
	return TRUE;
}


// ---------------------------------------------------------------------------
// return TRUE if the document is a well formed one
// ---------------------------------------------------------------------------
BOOL CMarkup::IsWellFormed(
	void) const
{
	return (m_ElementTree != NULL);
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
BOOL CMarkup::FindElem(
	const TCHAR * pathname)
{
	if (m_Cursor.m_MainPos != NULL)
	{
		// go to sibling
		Element * next = m_Cursor.m_MainPos->GetNextSibling();
		if (!next)
		{
			return FALSE;
		}
		m_Cursor.MoveMainPos(next);
		return TRUE;
	}

	// go to root
	if (!m_ElementTree)
	{
		return FALSE;
	}

	// just get first child if no pathname
	if (pathname == NULL || !pathname[0])
	{
		Element * cur = m_ElementTree->GetFirstChild();
		if (!cur)
		{
			return FALSE;
		}
		m_Cursor.MoveMainPos(cur);
		return TRUE;
	}

	// do regular strcmp if <= 2 children
	if (m_ElementTree->m_childCount <= 2)
	{
		Element * cur = m_ElementTree->GetFirstChild();
		while (cur)
		{
			if (XMLStrCmp(pathname, cur->m_tagStart) == 0)
			{
				m_Cursor.MoveMainPos(cur);
				return TRUE;
			}
			cur = cur->GetNextSibling();
		}
		return FALSE;
	}
	
	// compare by crc if > 2 children
	unsigned int len;
	DWORD crc;
	XMLStrLenAndCRC(pathname, len, crc);

	Element * cur = m_ElementTree->GetFirstChild();
	while (cur)
	{
		if (cur->m_tagCRC == crc && XMLStrCmp(pathname, cur->m_tagStart) == 0)
		{
			m_Cursor.MoveMainPos(cur);
			return TRUE;
		}
		cur = cur->GetNextSibling();
	}
	return FALSE;
}


// ---------------------------------------------------------------------------
// if pathname is NULL or empty, go to next sibling child element
// otherwise, go to next sibling child element with matching tag name
// if the current child position is valid, start looking from next
// change current child position only if found
// ---------------------------------------------------------------------------
BOOL CMarkup::FindChildElem(
	const TCHAR * pathname /* = NULL */,
	const BOOL bByName /* = FALSE */,
	const BOOL bDeepSearch /* = FALSE */)
{
	if (!m_Cursor.m_MainPos)
	{
		FindElem();
	}

	if (!m_Cursor.m_MainPos || m_Cursor.m_MainPos->IsEmpty())
	{
		return FALSE;
	}

	Element * cur = m_Cursor.m_ChildPos;
	if (cur)
	{
		cur = cur->GetNextSibling();
	}
	else
	{
		cur = m_Cursor.m_MainPos->GetFirstChild();
	}

	if (!cur)
	{
		return FALSE;
	}

	// goto cur if no pathname
	if (pathname == NULL || pathname[0] == 0)
	{
		m_Cursor.MoveChildPos(cur);
		return TRUE;
	}

	// if children <= 2 do regular string compare
	if (m_Cursor.m_MainPos->m_childCount <= 2)
	{
		while (cur)
		{
			if (XMLStrCmp(pathname, cur->m_tagStart) == 0)
			{
				m_Cursor.MoveChildPos(cur);
				return TRUE;
			}
			cur = cur->GetNextSibling();
		}
		return FALSE;
	}

	// compare by crc 
	unsigned int len;
	DWORD crc;
	XMLStrLenAndCRC(pathname, len, crc);
	while (cur)
	{
		if (bByName)
		{
			Element * pName = cur->FindAttrib("name");
			if (pName && pName->m_tagStart)
			{
				if (XMLStrCmp(pathname, pName->m_dataStart) == 0)
				{
					m_Cursor.MoveChildPos(cur);
					return TRUE;
				}
			}
		}
		else
		{
			if (cur->m_tagCRC == crc && XMLStrCmp(pathname, cur->m_tagStart) == 0)
			{
				m_Cursor.MoveChildPos(cur);
				return TRUE;
			}
		}

		// do a deep (recursive) search, if requested
		if (bDeepSearch)
		{
			if (cur->GetFirstChild())
			{
				Element * pPrev = cur->m_Parent;
				m_Cursor.MoveMainPos(cur);

				if (FindChildElem(pathname, bByName, bDeepSearch))
				{
					return TRUE;
				}

				if (pPrev)
				{
					m_Cursor.MoveMainPos(pPrev);
				}
			}
		}

		cur = cur->GetNextSibling();
	}
	return FALSE;
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
BOOL CMarkup::FindPrevElem(
	const TCHAR * tagname /* = NULL */)
{
	if (!m_Cursor.m_MainPos)
	{
		return FALSE;
	}

	Element * cur = m_Cursor.m_MainPos->GetPrevSibling();
	if (!cur)
	{
		return FALSE;
	}
	
	if (!tagname || tagname[0] == 0)
	{
		m_Cursor.MoveMainPos(cur);
		return TRUE;
	}

	while (cur)
	{
		if (XMLStrCmp(tagname, cur->m_tagStart) == 0)
		{
			m_Cursor.MoveMainPos(cur);
			return TRUE;
		}
		cur = cur->GetPrevSibling();
	}
	return FALSE;
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
BOOL CMarkup::FindPrevChildElem(
	const TCHAR * tagname /* = NULL */)
{
	if (!m_Cursor.m_MainPos || !m_Cursor.m_ChildPos)
	{
		return FALSE;
	}

	Element * cur = m_Cursor.m_ChildPos->GetPrevSibling();
	if (!cur)
	{
		return FALSE;
	}
	
	if (!tagname || tagname[0] == 0)
	{
		m_Cursor.MoveChildPos(cur);
		return TRUE;
	}

	while (cur)
	{
		if (XMLStrCmp(tagname, cur->m_tagStart) == 0)
		{
			m_Cursor.MoveChildPos(cur);
			return TRUE;
		}
		cur = cur->GetPrevSibling();
	}
	return FALSE;
}


// ---------------------------------------------------------------------------
// move to first child position of current position 
// if at root, this moves to first child of root
// ---------------------------------------------------------------------------
BOOL CMarkup::IntoElem(
	void)
{
	if (!m_Cursor.m_ChildPos)
	{
		FindChildElem();
	}

	if (m_Cursor.m_ChildPos)
	{
		m_Cursor.MoveMainPos(m_Cursor.m_ChildPos);
		return TRUE;
	}

	return FALSE;
}


// ---------------------------------------------------------------------------
// move up one
// ---------------------------------------------------------------------------
BOOL CMarkup::OutOfElem(
	void)
{
	if (!m_Cursor.m_ParentPos)
	{
		if (m_Cursor.m_MainPos && m_Cursor.m_MainPos->m_Parent)
		{
			m_Cursor.MoveMainPos(m_Cursor.m_MainPos->m_Parent);
			return TRUE;
		}
		return FALSE;
	}

	m_Cursor.MoveMainPos(m_Cursor.m_ParentPos);
	return TRUE;
}


// ---------------------------------------------------------------------------
// reset all positions
// ---------------------------------------------------------------------------
void CMarkup::ResetPos(
	void)
{
	m_Cursor.Clear();
	m_Cursor.MoveParentPos(m_ElementTree);
}


// ---------------------------------------------------------------------------
// reset just the child position
// ---------------------------------------------------------------------------
void CMarkup::ResetChildPos(
	void)
{
	m_Cursor.MoveChildPos(NULL);
}


// ---------------------------------------------------------------------------
// reset the main & child position, but maintain the parent
// ---------------------------------------------------------------------------
void CMarkup::ResetMainPos(
	void)
{
	m_Cursor.MoveMainPos(NULL);
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
unsigned int CMarkup::SavePos(
	void)
{
	int pos = m_CursorPool.GetFreeCursor();
	if (pos == 0)
	{
		return 0;
	}
	Cursor * cursor = m_CursorPool.GetCursor(pos);
	*cursor = m_Cursor;
	cursor->m_Counter = m_ModifyCounter;

	return pos;
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
BOOL CMarkup::RestorePos(
	unsigned int pos, 
	BOOL release /* = FALSE */)
{
	Cursor * cursor = m_CursorPool.GetCursor(pos);
	if (!cursor || cursor->m_Counter == CursorPool::XML_INVALID_CURSOR)
	{
		return FALSE;
	}

	BOOL result = FALSE;
	if (m_ModifyCounter == cursor->m_Counter)
	{
		m_Cursor = *cursor;
		result = TRUE;
	}

	if (release)
	{
		ReleasePos(pos);
	}
	return result;
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CMarkup::ReleasePos(
	unsigned int pos)
{
	Cursor * cursor = m_CursorPool.GetCursor(pos);
	if (!cursor)
	{
		return;
	}

	cursor->m_Counter = CursorPool::XML_INVALID_CURSOR;
}


// ---------------------------------------------------------------------------
// return a const ptr to the tagname for the main pos element
// ---------------------------------------------------------------------------
const TCHAR * CMarkup::GetTagName(
	void) const
{
	if (!m_Cursor.m_MainPos || !m_Cursor.m_MainPos->m_tagStart)
	{
		return EMPTY_STRING;
	}
	return m_Cursor.m_MainPos->m_tagStart;
}


// ---------------------------------------------------------------------------
// copy tagname for the main pos element
// ---------------------------------------------------------------------------
BOOL CMarkup::GetTagName(
	TCHAR * str,
	unsigned int buflen,
	unsigned int * len /* = NULL */) const
{
	if (!m_Cursor.m_MainPos)
	{
		ASSERT_RETFALSE(buflen > 0);
		str[0] = 0;
		if (len)
		{
			*len = 0;
		}
		return FALSE;
	}
	return m_Cursor.m_MainPos->GetTag(str, buflen, len);
}


// ---------------------------------------------------------------------------
// return a const ptr to the tagname for the child pos element
// ---------------------------------------------------------------------------
const TCHAR * CMarkup::GetChildTagName(
	void) const
{
	if (!m_Cursor.m_ChildPos || !m_Cursor.m_ChildPos->m_tagStart)
	{
		return EMPTY_STRING;
	}
	return m_Cursor.m_ChildPos->m_tagStart;
}


// ---------------------------------------------------------------------------
// copy tagname for the child pos element
// ---------------------------------------------------------------------------
BOOL CMarkup::GetChildTagName(
	TCHAR * str,
	unsigned int buflen,
	unsigned int * len /* = NULL */) const
{
	if (!m_Cursor.m_ChildPos)
	{
		ASSERT_RETFALSE(buflen > 0);
		str[0] = 0;
		if (len)
		{
			*len = 0;
		}
		return FALSE;
	}
	return m_Cursor.m_ChildPos->GetTag(str, buflen, len);
}


// ---------------------------------------------------------------------------
// return a const ptr to the data for the main pos element
// ---------------------------------------------------------------------------
const TCHAR * CMarkup::GetData(
	void) const
{
	if (!m_Cursor.m_MainPos || !m_Cursor.m_MainPos->m_dataStart)
	{
		return EMPTY_STRING;
	}
	return m_Cursor.m_MainPos->m_dataStart;
}


// ---------------------------------------------------------------------------
// copy data for the main pos element
// ---------------------------------------------------------------------------
BOOL CMarkup::GetData(
	TCHAR * str,
	unsigned int buflen,
	unsigned int * len /* = NULL */) const
{
	if (!m_Cursor.m_MainPos)
	{
		ASSERT_RETFALSE(buflen > 0);
		str[0] = 0;
		if (len)
		{
			*len = 0;
		}
		return FALSE;
	}
	return m_Cursor.m_MainPos->GetData(str, buflen, len);
}


// ---------------------------------------------------------------------------
// return a const ptr to the data for the child pos element
// ---------------------------------------------------------------------------
const TCHAR * CMarkup::GetChildData(
	void) const
{
	if (!m_Cursor.m_ChildPos || !m_Cursor.m_ChildPos->m_dataStart)
	{
		return EMPTY_STRING;
	}
	return m_Cursor.m_ChildPos->m_dataStart;
}


// ---------------------------------------------------------------------------
// copy data for the child pos element
// ---------------------------------------------------------------------------
BOOL CMarkup::GetChildData(
	TCHAR * str,
	unsigned int buflen,
	unsigned int * len /* = NULL */) const
{
	if (!m_Cursor.m_ChildPos)
	{
		ASSERT_RETFALSE(buflen > 0);
		str[0] = 0;
		if (len)
		{
			*len = 0;
		}
		return FALSE;
	}
	return m_Cursor.m_ChildPos->GetData(str, buflen, len);
}


// ---------------------------------------------------------------------------
// find a element by name, set cursor to that element, and return a const ptr
// to the data for that element
// ---------------------------------------------------------------------------
const TCHAR * CMarkup::FindGetData(
	const TCHAR * pathname)
{
	if (!FindElem(pathname))
	{
		return EMPTY_STRING;
	}
	return GetData();
}


// ---------------------------------------------------------------------------
// return true if the main pos has the attrib by name
// does a linear search!
// ---------------------------------------------------------------------------
BOOL CMarkup::HasAttrib(
	const TCHAR * attribname) const
{
	if (!m_Cursor.m_MainPos)
	{
		return FALSE;
	}
	return (m_Cursor.m_MainPos->FindAttrib(attribname) != NULL);
}


// ---------------------------------------------------------------------------
// return true if the main pos has the attrib by name
// does a linear search!
// ---------------------------------------------------------------------------
BOOL CMarkup::HasChildAttrib(
	const TCHAR * attribname) const
{
	if (!m_Cursor.m_ChildPos)
	{
		return FALSE;
	}
	return (m_Cursor.m_ChildPos->FindAttrib(attribname) != NULL);
}


// ---------------------------------------------------------------------------
// return the data associated with an attribute of the main pos, 
// does a linear search!
// ---------------------------------------------------------------------------
const TCHAR * CMarkup::GetAttrib(
	const TCHAR * attribname) const
{
	if (!m_Cursor.m_MainPos)
	{
		return EMPTY_STRING;
	}
	Element * attrib = m_Cursor.m_MainPos->FindAttrib(attribname);
	if (!attrib || !attrib->m_dataStart)
	{
		return EMPTY_STRING;
	}
	return attrib->m_dataStart;
}


// ---------------------------------------------------------------------------
// return the data associated with an attribute of the child pos, 
// does a linear search!
// ---------------------------------------------------------------------------
const TCHAR * CMarkup::GetChildAttrib(
	const TCHAR * attribname) const
{
	if (!m_Cursor.m_ChildPos)
	{
		return EMPTY_STRING;
	}
	Element * attrib = m_Cursor.m_ChildPos->FindAttrib(attribname);
	if (!attrib || !attrib->m_dataStart)
	{
		return EMPTY_STRING;
	}
	return attrib->m_dataStart;
}


// ---------------------------------------------------------------------------
// return the name of the nth attribute
// ---------------------------------------------------------------------------
const TCHAR * CMarkup::GetAttribName(
	unsigned int n) const
{
	if (!m_Cursor.m_MainPos)
	{
		return EMPTY_STRING;
	}

	unsigned int ii = 0;
	Element * cur = m_Cursor.m_MainPos->m_attribFirst;
	while (cur)
	{
		if (ii == n)
		{
			if (!cur->m_tagStart)
			{
				return EMPTY_STRING;
			}
			return cur->m_tagStart;
		}
		ii++;
		cur = cur->m_sibNext;
	}
	return EMPTY_STRING;
}


// ---------------------------------------------------------------------------
// XML creation functions
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// constant strings
// ---------------------------------------------------------------------------
static const TCHAR * STAG_OPEN = _T("<");
static const unsigned STAG_OPEN_LEN = XMLStrLen(STAG_OPEN);
static const TCHAR * ATTRIB_SPACE = _T(" ");
static const unsigned ATTRIB_SPACE_LEN = XMLStrLen(ATTRIB_SPACE);
static const TCHAR * ATTRIB_EQ = _T("=\"");
static const unsigned ATTRIB_EQ_LEN = XMLStrLen(ATTRIB_EQ);
static const TCHAR * ATTRIB_END = _T("\"");
static const unsigned ATTRIB_END_LEN = XMLStrLen(ATTRIB_END);
static const TCHAR * ETAG_EMPTY = _T("/>\r\n");
static const unsigned ETAG_EMPTY_LEN = XMLStrLen(ETAG_EMPTY);
static const TCHAR * ETAG = _T(">");
static const unsigned ETAG_LEN = XMLStrLen(ETAG);
static const TCHAR * ETAG_NL = _T(">\r\n");
static const unsigned ETAG_NL_LEN = XMLStrLen(ETAG_NL);
static const TCHAR * CDATA_START = _T("![CDATA[");
static const unsigned CDATA_START_LEN = XMLStrLen(CDATA_START);
static const TCHAR * CDATA_END = _T("]]>");
static const unsigned CDATA_END_LEN = XMLStrLen(CDATA_END);
static const TCHAR * NEWLINE = _T("\r\n");
static const unsigned NEWLINE_LEN = XMLStrLen(NEWLINE);
static const TCHAR * ETAG_START = _T("</");
static const unsigned ETAG_START_LEN = XMLStrLen(ETAG_START);
static const TCHAR * ETAG_END = _T(">\r\n");
static const unsigned ETAG_END_LEN = XMLStrLen(ETAG_END);


// ---------------------------------------------------------------------------
// save an element to a file
// ---------------------------------------------------------------------------
BOOL CMarkup::Save(
	void * x,
	const Element * elem,
	FP_XML_OUTPUT fp) const
{
	// write STag
	if (elem->m_tagStart && elem->m_tagStart[0])
	{
		if (!fp(x, STAG_OPEN, STAG_OPEN_LEN))
		{
			return FALSE;
		}
		if (!fp(x, elem->m_tagStart, elem->m_tagLen))
		{
			return FALSE;
		}

		// write all attributes
		Element * attrib = elem->m_attribFirst;
		while (attrib)
		{
			if (attrib->m_tagStart && attrib->m_tagStart[0] && attrib->m_dataStart && attrib->m_dataStart[0])
			{
				if (!fp(x, ATTRIB_SPACE, ATTRIB_SPACE_LEN))
				{
					return FALSE;
				}
				if (!fp(x, attrib->m_tagStart, attrib->m_tagLen))
				{
					return FALSE;
				}
				if (!fp(x, ATTRIB_EQ, ATTRIB_EQ_LEN))
				{
					return FALSE;
				}
				if (!fp(x, attrib->m_dataStart, attrib->m_dataLen))
				{
					return FALSE;
				}
				if (!fp(x, ATTRIB_END, ATTRIB_END_LEN))
				{
					return FALSE;
				}
			}
			attrib = attrib->m_sibNext;
		}

		if (elem->IsEmpty())
		{
			if (!fp(x, ETAG_EMPTY, ETAG_EMPTY_LEN))
			{
				return FALSE;
			}
		}
		else if (elem->m_childFirst == NULL)
		{
			if (!fp(x, ETAG, ETAG_LEN))
			{
				return FALSE;
			}
		}
		else
		{
			if (!fp(x, ETAG_NL, ETAG_NL_LEN))
			{
				return FALSE;
			}
		}
	}

	// write data
	if (elem->m_dataStart && elem->m_dataStart[0])
	{
		if (!TESTBIT(elem->m_Flags, Element::FLAG_CDATA))
		{
			if (!fp(x, elem->m_dataStart, elem->m_dataLen))
			{
				return FALSE;
			}			
		}
		else
		{
			if (!fp(x, CDATA_START, CDATA_START_LEN))
			{
				return FALSE;
			}
			if (!fp(x, elem->m_dataStart, elem->m_dataLen))
			{
				return FALSE;
			}			
			if (!fp(x, CDATA_END, CDATA_END_LEN))
			{
				return FALSE;
			}
		}

		if (elem->m_childFirst)
		{
			if (!fp(x, NEWLINE, NEWLINE_LEN))
			{
				return FALSE;
			}
		}
	}

	// write all children
	const Element * child = elem->m_childFirst;
	while (child)
	{
		Save(x, child, fp);
		child = child->m_sibNext;
	}

	// write ETag
	if (elem->m_tagStart && elem->m_tagStart[0] && !elem->IsEmpty())
	{
		if (!fp(x, ETAG_START, ETAG_START_LEN))
		{
			return FALSE;
		}
		if (!fp(x, elem->m_tagStart, elem->m_tagLen))
		{
			return FALSE;
		}
		if (!fp(x, ETAG_END, ETAG_END_LEN))
		{
			return FALSE;
		}
	}
	return TRUE;
}


// ---------------------------------------------------------------------------
// write to file
// ---------------------------------------------------------------------------
BOOL fpXMLFileWrite(
	void * x,
	const TCHAR * buf,
	unsigned int size)
{
	return XMLFileWrite((HANDLE)x, buf, size * sizeof(TCHAR));
}


// ---------------------------------------------------------------------------
// save a xml file to disk
// ---------------------------------------------------------------------------
BOOL CMarkup::Save(
	const WCHAR * filename) const
{
	ASSERT_RETFALSE(m_ElementTree);

	HANDLE file = INVALID_HANDLE_VALUE;

	WCHAR fullname[MAX_PATH];
	FileGetFullFileName(fullname, filename, _countof(fullname));

	file = CreateFileW(fullname, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (file == INVALID_HANDLE_VALUE)
	{
		//MarkupError(_T("unable to open file [%s]\n"), fullname);
		goto error;
	}

	TCHAR * buffer = NULL;
	unsigned int buflen = 0;
	if (!SaveToBuffer(buffer, buflen))
	{
		MarkupError("error writing to file [%s]\n", WIDE_CHAR_TO_ASCII_FOR_DEBUG_TRACE_ONLY(fullname));
		goto error;
	}

	if (!XMLFileWrite(file, buffer, buflen))
	{
		MarkupError("error writing to file [%s]\n", WIDE_CHAR_TO_ASCII_FOR_DEBUG_TRACE_ONLY(fullname));
		goto error;
	}

	FREE(g_ScratchAllocator, buffer);
/*
	if (!Save((void *)file, m_ElementTree, fpXMLFileWrite))
	{
		MarkupError(_T("error writing to file [%s]\n"), filename);
		goto error;
	}
*/

	CloseHandle(file);
	return TRUE;

error:
	if (file != INVALID_HANDLE_VALUE)
	{
		CloseHandle(file);
	}

	return FALSE;
}

BOOL CMarkup::Save(
	const char * filename) const
{
	WCHAR buf[MAX_PATH];
	PStrCvt(buf, filename, _countof(buf));
	return Save(buf);
}


// ---------------------------------------------------------------------------
// calculate save size
// ---------------------------------------------------------------------------
BOOL fpXMLGetSize(
	void * x,
	const TCHAR * buf,
	unsigned int size)
{
	UNREFERENCED_PARAMETER(buf);

	unsigned int * ptr = (unsigned int *)x;
	*ptr += size * sizeof(TCHAR);
	return TRUE;
}


// ---------------------------------------------------------------------------
// calculate save size
// ---------------------------------------------------------------------------
unsigned int CMarkup::GetSaveSize(
	void) const
{
	if (!m_ElementTree)
	{
		return 0;
	}

	unsigned int size = 0;
	if (!Save(&size, m_ElementTree, fpXMLGetSize))
	{
		MarkupError(_T("error calculating size of document\n"));
		return 0;
	}

	return size;
}


// ---------------------------------------------------------------------------
// write to buffer
// ---------------------------------------------------------------------------
BOOL fpXMLWriteToBuf(
	void * x,
	const TCHAR * buf,
	unsigned int size)
{
	TCHAR ** ptr = (TCHAR **)x;
	ASSERT_RETFALSE(MemoryCopy(*ptr, size * sizeof(TCHAR), buf, size * sizeof(TCHAR)));
	*ptr += size;
	return TRUE;
}


// ---------------------------------------------------------------------------
// write to a buffer
// ---------------------------------------------------------------------------
BOOL CMarkup::SaveToBuffer(
	TCHAR *& buf,
	unsigned int & buflen) const
{
	if (!m_ElementTree)
	{
		return FALSE;
	}
	unsigned int size = GetSaveSize();
	if (buf && size > buflen)
	{
		MarkupError(_T("buffer too small for save\n"));
		return FALSE;
	}
	else
	{
		if (size > XML_MAX_FILE_SIZE)
		{
			MarkupError(_T("file size exceeds XML_MAX_FILE_SIZE\n"));
			ASSERT(size < XML_MAX_FILE_SIZE);
			return FALSE;
		}
		buflen = size;
		buf = (TCHAR *)MALLOC(g_ScratchAllocator, buflen * sizeof(TCHAR));
	}

	TCHAR * cur = buf;
	if (!Save(&cur, m_ElementTree, fpXMLWriteToBuf))
	{
		MarkupError(_T("error streaming document\n"));
		return FALSE;
	}

	return TRUE;
}


// ---------------------------------------------------------------------------
// add an element after main pos
// ---------------------------------------------------------------------------
BOOL CMarkup::AddElem(
	const TCHAR * tagname,
	const TCHAR * data /* = NULL */,
	DWORD flags /* = 0 */)
{
	if (!m_Cursor.m_ParentPos)
	{
		if (!m_ElementTree)
		{
			m_ElementTree = ElementAdd(NULL);
			m_Cursor.MoveParentPos(m_ElementTree);
		}
		else
		{
			return FALSE;
		}
	}
	Element * elem = NULL;
	if (!m_Cursor.m_MainPos)
	{
		elem = ElementAdd(m_Cursor.m_ParentPos, tagname, data, flags);
	}
	else
	{
		elem = ElementInsertAfter(m_Cursor.m_MainPos, tagname, data, flags);
	}
	if (!elem)
	{
		return FALSE;
	}
	m_Cursor.MoveMainPos(elem);
	return TRUE;
}


// ---------------------------------------------------------------------------
// add an element before main pos
// ---------------------------------------------------------------------------
BOOL CMarkup::InsertElem(
	const TCHAR * tagname,
	const TCHAR * data /* = NULL */,
	DWORD flags /* = 0 */)
{
	if (!m_Cursor.m_ParentPos)
	{
		return FALSE;
	}
	Element * elem = NULL;
	if (!m_Cursor.m_MainPos)
	{
		elem = ElementAdd(m_Cursor.m_ParentPos, tagname, data, flags);
	}
	else
	{
		elem = ElementInsertBefore(m_Cursor.m_MainPos, tagname, data, flags);
	}
	if (!elem)
	{
		return FALSE;
	}
	m_Cursor.MoveMainPos(elem);
	return TRUE;
}


// ---------------------------------------------------------------------------
// add an element after the child pos
// ---------------------------------------------------------------------------
BOOL CMarkup::AddChildElem(
	const TCHAR * tagname,
	const TCHAR * data /* = NULL */,
	DWORD flags /* = 0 */)
{
	if (!m_Cursor.m_MainPos)
	{
		return FALSE;
	}
	Element * elem = NULL;
	if (!m_Cursor.m_ChildPos)
	{
		elem = ElementAdd(m_Cursor.m_MainPos, tagname, data, flags);
	}
	else
	{
		elem = ElementInsertAfter(m_Cursor.m_ChildPos, tagname, data, flags);
	}
	if (!elem)
	{
		return FALSE;
	}
	m_Cursor.MoveChildPos(elem);
	return TRUE;
}


// ---------------------------------------------------------------------------
// insert a child element before the current child pos
// ---------------------------------------------------------------------------
BOOL CMarkup::InsertChildElem(
	const TCHAR * tagname,
	const TCHAR * data /* = NULL */,
	DWORD flags /* = 0 */)
{
	if (!m_Cursor.m_MainPos)
	{
		return FALSE;
	}
	Element * elem = NULL;
	if (!m_Cursor.m_ChildPos)
	{
		elem = ElementAdd(m_Cursor.m_MainPos, tagname, data, flags);
	}
	else
	{
		elem = ElementInsertBefore(m_Cursor.m_ChildPos, tagname, data, flags);
	}
	if (!elem)
	{
		return FALSE;
	}
	m_Cursor.MoveChildPos(elem);
	return TRUE;
}


// ---------------------------------------------------------------------------
// set the data for an attrib by copy, return FALSE if it already exists
// ---------------------------------------------------------------------------
BOOL CMarkup::AddAttrib(
	const TCHAR * attribname,
	const TCHAR * value)
{
	return SetAttrib(attribname, value);
}


// ---------------------------------------------------------------------------
// set the data for an attrib by copy, return FALSE if it already exists
// ---------------------------------------------------------------------------
BOOL CMarkup::AddChildAttrib(
	const TCHAR * attribname,
	const TCHAR * value)
{
	return SetChildAttrib(attribname, value);
}


// ---------------------------------------------------------------------------
// XML modification functions
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// delete current main position
// ---------------------------------------------------------------------------
BOOL CMarkup::RemoveElem(
	void)
{
	if (!m_Cursor.m_MainPos)
	{
		return FALSE;
	}
	Element * elem = m_Cursor.m_MainPos;
	m_Cursor.MoveMainPos(elem->GetPrevSibling());
	ElementDelete(elem);

	return TRUE;
}


// ---------------------------------------------------------------------------
// delete the current child position
// ---------------------------------------------------------------------------
BOOL CMarkup::RemoveChildElem(
	void)
{
	if (!m_Cursor.m_ChildPos)
	{
		return FALSE;
	}
	Element * elem = m_Cursor.m_ChildPos;
	m_Cursor.MoveChildPos(elem->GetPrevSibling());
	ElementDelete(elem);

	return TRUE;
}


// ---------------------------------------------------------------------------
// set the data for the main position element by copy
// ---------------------------------------------------------------------------
BOOL CMarkup::SetData(
	const TCHAR * data,
	int flags /* = 0 */)
{
	if (!m_Cursor.m_MainPos)
	{
		return FALSE;
	}
	m_Cursor.m_MainPos->SetData(data, flags);
	m_Cursor.m_MainPos->m_Flags |= flags;
	return TRUE;
}


// ---------------------------------------------------------------------------
// set the data for the child position element by copy
// ---------------------------------------------------------------------------
BOOL CMarkup::SetChildData(
	const TCHAR * data,
	int flags /* = 0 */)
{
	if (!m_Cursor.m_ChildPos)
	{
		return FALSE;
	}
	m_Cursor.m_ChildPos->SetData(data, flags);
	m_Cursor.m_ChildPos->m_Flags |= flags;
	return TRUE;
}


// ---------------------------------------------------------------------------
// set the value for an attrib of the main position
// (or add it if it doesn't exist)
// return FALSE if there's no main position
// ---------------------------------------------------------------------------
BOOL CMarkup::SetAttrib(
	const TCHAR * attribname,
	const TCHAR * value)
{
	return ElementSetAttrib(m_Cursor.m_MainPos, attribname, value);
}


// ---------------------------------------------------------------------------
// set the value for an attrib of the child position
// (or add it if it doesn't exist)
// return FALSE if there's no child position
// ---------------------------------------------------------------------------
BOOL CMarkup::SetChildAttrib(
	const TCHAR * attribname,
	const TCHAR * value)
{
	return ElementSetAttrib(m_Cursor.m_ChildPos, attribname, value);
}


// ---------------------------------------------------------------------------
// remove a main position attrib by name
// ---------------------------------------------------------------------------
BOOL CMarkup::RemoveAttrib(
	const TCHAR * attribname)
{
	if (!m_Cursor.m_MainPos)
	{
		return FALSE;
	}
	Element * attrib = m_Cursor.m_MainPos->FindAttrib(attribname);
	if (!attrib)
	{
		return FALSE;
	}
	AttribDelete(attrib);

	return TRUE;
}


// ---------------------------------------------------------------------------
// remove a main position attrib by name
// ---------------------------------------------------------------------------
BOOL CMarkup::RemoveChildAttrib(
	const TCHAR * attribname)
{
	if (!m_Cursor.m_ChildPos)
	{
		return FALSE;
	}
	Element * attrib = m_Cursor.m_ChildPos->FindAttrib(attribname);
	if (!attrib)
	{
		return FALSE;
	}
	AttribDelete(attrib);

	return TRUE;
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
BOOL CMarkup::FindSetData(
	const TCHAR * pathname,
	const TCHAR * data,
	int flags /* = 0 */)
{
	if (!FindElem(pathname))
	{
		return FALSE;
	}
	return SetData(data, flags);
}


// ---------------------------------------------------------------------------
// XML parsing functions
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// return the line parsing stopped at using m_ParseCur
// ---------------------------------------------------------------------------
unsigned int CMarkup::GetParseErrorLine(
	void) const
{
	int line = 0;
	TCHAR * cur = m_Document;
	while (cur < m_ParseCur)
	{
		if (*cur == _T('\n'))
		{
			++line;
		}
		++cur;
	}
	return line;
}

#if !ISVERSION(SERVER_VERSION)
#undef MarkupError
#define MarkupError Error
// ---------------------------------------------------------------------------
// print a parsing error message 
// ---------------------------------------------------------------------------
void CMarkup::Error(
	TCHAR * format,
	...) const
{
	enum
	{
		MAX_ERROR_STRING = 4096,
	};
	static const TCHAR * default_error_string = _T("illegal error string\n");

	va_list args;
	va_start(args, format);

	unsigned int len = _vsctprintf(format, args) + 1;		// _vsctprintf doesn't count terminating '\0'
	if (len > MAX_ERROR_STRING)
	{
		ASSERTV_MSG(default_error_string);
		LogMessage(ERROR_LOG, default_error_string);
		return;
	}

	char buffer[MAX_ERROR_STRING];	
	PStrVprintf(buffer, MAX_ERROR_STRING, format, args);

	if (m_ParseCur > m_Document)
	{
		unsigned int line = GetParseErrorLine();
		if (line > 0)
		{
			if (m_Filename[0])
			{
				PStrPrintf(buffer + len - 1, MAX_ERROR_STRING - len, "\n\n[file:%s line:%d]\n", m_Filename, line);
			}
			else
			{
				PStrPrintf(buffer + len - 1, MAX_ERROR_STRING - len, "\n\n[line:%d]\n", line);
			}
		}
	}
	ASSERTV_MSG(buffer);
	LogMessage(ERROR_LOG, buffer);
}
#endif //!SERVER_VERSION


// ---------------------------------------------------------------------------
// skip white space, positions cursor at first non-wspace character
// ---------------------------------------------------------------------------
BOOL CMarkup::ParseSkipWhiteSpace(
	TCHAR *& str)
{
	// skip leading whitespace
_skipwhitespace:
	switch (*str)
	{
	case 0:
		m_ParseCur = str;
		return FALSE;
	case _T('\t'):
	case _T('\r'):
	case _T('\n'):
	case _T(' '):
		++str;
		goto _skipwhitespace;
	}
	m_ParseCur = str;
	return TRUE;
}


// ---------------------------------------------------------------------------
// eats a '<'.  returns FALSE if first non-wspace character isn't a '<'
// sets m_chPrevChar to '<'
// positions str at character after '<'
// ---------------------------------------------------------------------------
BOOL CMarkup::ParseOpenTag(
	TCHAR *& str)
{
	if (!ParseSkipWhiteSpace(str))
	{
		return FALSE;
	}
	if (*str != _T('<'))
	{
		return FALSE;
	}
	str++;
	m_chPrevChar = _T('<');
	return TRUE;
}


// ---------------------------------------------------------------------------
// consume a tag name, (alpha) [alnum | _ | .]*
// null terminates character after name, setting m_chPrevChar
// sets str to character *after* terminator, unless m_chPrevChar == 0
// returns FALSE if invalid tagname
// ---------------------------------------------------------------------------
BOOL CMarkup::ParseTagName(
	Token & token,
	TCHAR *& str)
{
#ifndef _UNICODE			// need to provide unicode solution
	static const BOOL XML_VALID_NAME_CHAR[] =
	{
		FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, //   0
		FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, //   8
		FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, //  16 
		FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, //  24
		FALSE, FALSE, FALSE,  TRUE,  TRUE,  TRUE,  TRUE, FALSE, //  32   !"#$%&'
		 TRUE,  TRUE,  TRUE,  TRUE, FALSE,  TRUE,  TRUE, FALSE, //  40  ()*+,-./
		 TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE, //  48  01234567
		 TRUE,  TRUE,  TRUE,  TRUE, FALSE, FALSE, FALSE, FALSE, //  56  89:;<=>?
		 TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE, //  64  @ABCDEFG
		 TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE, //  72  HIJKLMNO
		 TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE, //  80  PQRSTUVW
		 TRUE,  TRUE,  TRUE,  TRUE, FALSE,  TRUE,  TRUE,  TRUE, //  88  XYZ[\]^_
		 TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE, //  96  `abcdefg
		 TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE, // 104  hijklmno
		 TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE, // 112  pqrstuvw
		 TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE, FALSE, // 120  xyz{|{~
		FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, // 128
		FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, // 136
		FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, // 144
		FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, // 152
		FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, // 160
		FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, // 168
		FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, // 176
		FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, // 184
		FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, // 192
		FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, // 200
		FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, // 208
		FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, // 216
		FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, // 224
		FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, // 232
		FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, // 240
		FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, // 248
	};
#endif

	if (!ParseSkipWhiteSpace(str))
	{
		return FALSE;
	}

	// leading character is alpha
	if (!isalpha((unsigned char)(*str)))
	{
		return FALSE;
	}
	token.m_Start = str;
	DWORD crc = STR_HASH_ADDC(0, *str);
	++str;

	while (XML_VALID_NAME_CHAR[*str])
	{
		crc = STR_HASH_ADDC(crc, *str);
		++str;
	}
	token.m_nLen = (unsigned int)(str - token.m_Start);
	token.m_dwCRC = crc;
	m_chPrevChar = *str;
	*str = 0;
	if (m_chPrevChar != 0)
	{
		str++;
	}
	return TRUE;
}


// ---------------------------------------------------------------------------
// consume everything up to the expect string
// sets str to character after expect string
// return FALSE if expected string not found
// ---------------------------------------------------------------------------
BOOL CMarkup::ParseScanTo(
	TCHAR *& str,
	const TCHAR * expect)
{
	m_ParseCur = str;

	while (*str)
	{
		if (*str != *expect)
		{
			++str;
			continue;
		}

		// matched first character, now check rest of string
		str++;
		TCHAR * str_a = str;
		const TCHAR * str_b = expect + 1;
		while (*str_b && *str_a == *str_b)
		{
			str_a++;
			str_b++;
		}
		if (!*str_b)
		{
			// str_a now points to character after expect string
			str = str_a;
			return TRUE;
		}
	}

	MarkupError(_T("expected '%s'\n"), expect);
	return FALSE;
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
int CMarkup::ParseGetDataEntity(
	TCHAR *& str)
{
	if (str[1] == _T('l') && str[2] == _T('t') && str[3] == _T(';'))
	{
		str[0] = _T('<');
		return 4;
	}
	else if (str[1] == _T('a') && str[2] == _T('m') && str[3] == _T('p') && str[4] == _T(';'))
	{
		str[0] = _T('&');
		return 5;
	}
	else if (str[1] == _T('g') && str[2] == _T('t') && str[3] == _T(';'))
	{
		str[0] = _T('>');
		return 4;
	}
	else if (str[1] == _T('q') && str[2] == _T('u') && str[3] == _T('o') && str[4] == _T('t') && str[5] == _T(';'))
	{
		str[0] = _T('\"');
		return 6;
	}
	else if (str[1] == _T('a') && str[2] == _T('p') && str[3] == _T('o') && str[4] == _T('s') && str[5] == _T(';'))
	{
		str[0] = _T('\'');
		return 6;
	}
	return 0;
}


// ---------------------------------------------------------------------------
// consume either an element's data block or a '<' which may indicate
// either a child element or an end tag.  check m_chPrevChar.
// add the data block to the element (fail if it already has one)
// null terminate the data block, setting m_chPrevChar.
// set str at character *after* terminator (or after '<')
// return FALSE if neither a data block is read nor a '<' is consumed
// ---------------------------------------------------------------------------
BOOL CMarkup::ParseGetData(
	CMarkup::Token & token,
	TCHAR *& str)
{
	if (m_chPrevChar == _T('<'))
	{
		token.m_Start = NULL;
		token.m_nLen = 0;
		return TRUE;
	}

	m_ParseCur = str;

_scan:
	switch (*str)
	{
	case 0:						// fail if we hit a terminator
		return FALSE;			

	case _T('\t'):				// consume whitespace
	case _T('\r'):
	case _T('\n'):
	case _T(' '):
		++str;
		goto _scan;

	case _T('<'):				// found a '<', eat it
		token.m_Start = NULL;	
		token.m_nLen = 0;
		m_chPrevChar = _T('<');
		++str;
		return TRUE;

	case _T('&'):
		token.m_Start = str;
		goto _scan2;

	default:
		{
			token.m_Start = str;
			++str;
_scan2:							// eat up the data block, until we get to a '<'
			switch (*str)
			{
			case 0:				// fail if we hit terminator
				return FALSE;	

			case _T('<'):		// end when we hit the '<'
				token.m_nLen = (unsigned int)(str - token.m_Start);
				m_chPrevChar = _T('<');
				*str = 0;
				++str;
				return TRUE;

			case _T('&'):
				{
					int len = ParseGetDataEntity(str);
					if (len > 0)
					{
						TCHAR * deststr = str + 1;
						str += len;
_scan3:
						switch (*str)
						{
						case 0:						// fail if we hit a terminator
							return FALSE;			

						case _T('<'):		// end when we hit the '<'
							token.m_nLen = (unsigned int)(deststr - token.m_Start);
							*deststr = 0;
							m_chPrevChar = _T('<');
							++str;
							return TRUE;

						case _T('&'):
							{
								len = ParseGetDataEntity(str);
								if (len > 0)
								{
									deststr[0] = str[0];
									++deststr;
									str += len;
									goto _scan3;
								}
							}
							// fall through
						default:
							*deststr = *str;
							++deststr;
							++str;
							goto _scan3;
						}
					}
				}
				// fall through
			default:			// keep eating
				++str;
				goto _scan2;
			}
		}
	}
}


// ---------------------------------------------------------------------------
// by this point we've already consumed the </ part of the end tag
// note that according to the xml standard, there are no spaces between
// <, /, and the name of the tag, but there can be spaces after the
// name and the closing >
// ETag ::= '</' Name S? '>'
// str is positioned after '>'
// clear m_chPrevChar
// FALSE is returned if the tag doesn't match or it isn't valid
// ---------------------------------------------------------------------------
BOOL CMarkup::ParseEndTag(
	Element * elem,
	TCHAR *& str)
{
	m_ParseCur = str;

	// match the tag
	TCHAR * cur = elem->m_tagStart;
	while (*cur)
	{
		if (*str != *cur)
		{
			return FALSE;
		}
		++str;
		++cur;
	}

	// consume whitespace
	if (!ParseSkipWhiteSpace(str))
	{
		return FALSE;
	}

	// validate '>'
	if (*str != _T('>'))
	{
		return FALSE;
	}
	++str;
	m_chPrevChar = _T('>');
	return TRUE;
}


// ---------------------------------------------------------------------------
BOOL CMarkup::ParseGetToken(
	Token & token,
	TCHAR *& str)
{
	if (!ParseSkipWhiteSpace(str))
	{
		return FALSE;
	}

	if (*str != _T('\"'))
	{
		TCHAR * start = str;
		// go until special character or whitespace
_continuescan:
		switch (*str)
		{
		case 0:
		case _T('\t'):
		case _T('\n'):
		case _T('\r'):
		case _T(' '):
		case _T('<'):
		case _T('>'):
		case _T('='):
		case _T('\\'):
		case _T('/'):
		case _T('?'):
		case _T('!'):
			break;
		default:
			++str;
			goto _continuescan;
		}
		if (str == start)
		{
			str++;
		}
		token.m_Start = start;
		token.m_nLen = (unsigned int)(str - start);
		token.m_bIsString = FALSE;
	}
	else
	{	
		// quoted string, skip past open quote
		str++;
		TCHAR * start = str;
		// go until closing quote
		while (*str && *str != _T('\"'))
		{
			str++;
		}
		if (!*str)
		{
			return FALSE;
		}
		// set up token
		token.m_Start = start;
		token.m_nLen = (unsigned int)(str - start);
		str++;			// next is one past end quote
		token.m_bIsString = TRUE;
	}
	return TRUE;
}


// ---------------------------------------------------------------------------
// parse from attribute section of start tag to end of STag or EmptyElemTag
// Attribute ::= Name Eq AttValue
// AttValue is either a "" string or a '' string
// WFC: each Attribute name must be unique within the element
// this consumes the '>' for STag or the '/>' for EmptyElemTag
// str is positioned after the '>' and m_chPrevChar is set to '>'
// returns FALSE if anything is invalid
// set isempty to TRUE if this is an EmptyElemTag
// ---------------------------------------------------------------------------
BOOL CMarkup::ParseAttributes(
	Element * elem,
	TCHAR *& str,
	BOOL & isempty)
{
nextattribute:
	if (!ParseSkipWhiteSpace(str))
	{
		return FALSE;
	}

	if (str[0] == _T('>'))
	{
		++str;
		m_chPrevChar = _T('>');
		return TRUE;
	}
	if (str[0] == _T('/'))
	{
		if (str[1] != _T('>'))
		{
			MarkupError(_T("Unexpected end of start tag\n"));
			return FALSE;
		}
		str += 2;
		m_chPrevChar = _T('>');
		isempty = TRUE;
		return TRUE;
	}

	// attribute name
	Token token;
	if (!ParseTagName(token, str))
	{
		MarkupError(_T("Invalid attribute name\n"));
		return FALSE;
	}

	if (token.m_nLen <= 0)
	{
		MarkupError(_T("Invalid attribute name\n"));
		return FALSE;
	}

	if (token.m_nLen >= XML_MAX_NAME_LEN)
	{
		MarkupError(_T("Attribute name exceeds maximum allowed size\n"));
		ASSERT(token.m_nLen < XML_MAX_NAME_LEN);
		return FALSE;
	}

	// m_chPrevChar must be '='
	if (m_chPrevChar != _T('='))
	{
		MarkupError(_T("Expected '=' after attribute name\n"));
		return FALSE;
	}

	TCHAR * valStart = NULL;
	// parse the attribute value
	switch (*str)
	{
	case _T('\''):
		++str;
		// set start of attribute value here
		valStart = str;
		while (*str && *str != _T('\''))
		{
			str++;
		}
		break;

	case _T('\"'):
		++str;
		// set start of attribute value here
		valStart = str;
		while (*str && *str != _T('\"'))
		{
			str++;
		}
		break;

	default:
		MarkupError(_T("Expected quoted string for attribute value\n"));
		return FALSE;
	}

	if (valStart == NULL)
	{
		MarkupError(_T("Missing attribute value\n"));
		return FALSE;
	}
	if (*str == 0)
	{
		MarkupError(_T("Missing end quote after attribute value\n"));
		return FALSE;
	}
	m_chPrevChar = *str;
	*str = 0;
	unsigned int valLen = (unsigned int)(str - valStart);
	if (valLen >= XML_MAX_DATA_LEN)
	{
		MarkupError(_T("Attribute value exceeds maximum allowed size\n"));
		ASSERT(valLen < XML_MAX_DATA_LEN);
		return FALSE;
	}

	// add the attribute to the elem here
	Element * attrib = ElementAddAttrib(elem);
	if (!attrib)
	{
		MarkupError(_T("Exceeded maximum number of elements\n"));
		return FALSE;
	}
	attrib->m_tagStart = token.m_Start;
	attrib->m_tagLen = token.m_nLen;
	attrib->m_tagCRC = token.m_dwCRC;
	attrib->m_dataStart = valStart;
	attrib->m_dataLen = valLen;

	++str;

	goto nextattribute;
}


// ---------------------------------------------------------------------------
// the '<' should have already been eaten at this point, and ought to be the
// m_chPrevChar
// STag ::= '<' Name (S Attribute)* S? '>'
// EmptyElemTag  ::= '<' Name (S Attribute)* S? '/>'
// this consumes the entire STag starting from the name
// str is positioned after the '>' and m_chPrevChar is set to '>'
// returns FALSE if STag is at all invalid
// if this is an EmptyElemTag, sets isempty to TRUE
// ---------------------------------------------------------------------------
BOOL CMarkup::ParseStartTag(
	Element * elem,
	TCHAR *& str,
	BOOL & isempty)
{
	// xml tag name
	Token token;
	if (!ParseTagName(token, str))
	{
		MarkupError(_T("Invalid element name\n"));
		return FALSE;
	}
	if (token.m_nLen >= XML_MAX_NAME_LEN)
	{
		MarkupError(_T("Element name exceeds maximum allowed size\n"));
		ASSERT(token.m_nLen < XML_MAX_NAME_LEN);
		return FALSE;
	}
	elem->m_tagStart = token.m_Start;
	elem->m_tagLen = token.m_nLen;
	elem->m_tagCRC = token.m_dwCRC;

	// the prev char can be one of (S | '/' | '>')
	switch (m_chPrevChar)
	{
	case 0:
		MarkupError(_T("Unexpected end of start tag\n"));

	case _T('\t'):			// if it was wspace, just continue on
	case _T('\n'):
	case _T('\r'):
	case _T(' '):
		break;

	case _T('/'):			// empty element indicator
		if (*str != _T('>'))
		{
			MarkupError(_T("Unexpected end of start tag\n"));
			return FALSE;
		}
		++str;
		m_chPrevChar = _T('>');
		isempty = TRUE;
		return TRUE;

	case _T('>'):			// close tag
		return TRUE;

	default:
		MarkupError(_T("Invalid character in start tag\n"));
		return FALSE;
	}

	// parse attribs
	return ParseAttributes(elem, str, isempty);
}


// ---------------------------------------------------------------------------
// parse an element, cursor should be positioned after the '<', which
// should be the m_chPrevChar we can't eat it here because, for example, 
// a data content item will overwrite the following '<' with a 0.
// m_chPrevChar should be set properly on exit if result is valid
// return the new element on success
// ---------------------------------------------------------------------------
CMarkup::Element * CMarkup::ParseElement(
	Element * parent,
	TCHAR *& str)
{
	if (!*str)
	{
		return NULL;
	}

	// add the element
	Element * elem = ElementAdd(parent);
	if (!elem)
	{
		MarkupError("Exceeded maximum number of elements\n");
		return NULL;
	}
	// xml tag name
	BOOL isempty = FALSE;

	// xml declaration | program instruction, save & ignore
	if (str[0] == _T('?'))		
	{
		++str;

		TCHAR * start = str;
		if (!ParseScanTo(str, _T("?>")))
		{
			ElementDelete(elem);
			return NULL;
		}
		str[-2] = 0;
		SETBIT(elem->m_Flags, Element::FLAG_PROGRAM_INSTRUCTION);
		elem->m_dataStart = start;
		elem->m_dataLen = (unsigned int)(str - start - 2);
		if (elem->m_dataLen >= XML_MAX_COMMENT_LEN)
		{
			ElementDelete(elem);
			MarkupError("program instruction exceeded max size\n");
			return NULL;
		}
		if (!ParseOpenTag(str))
		{
			ElementDelete(elem);
			MarkupError("expected '<'\n");
			return NULL;
		}
		return elem;
	}
	// xml comment, save & ignore
	if (str[0] == _T('!') && str[1] == _T('-') && str[2] == _T('-'))
	{
		str += 3;
		TCHAR * start = str;
		if (!ParseScanTo(str, _T("-->")))
		{
			ElementDelete(elem);
			MarkupError("expected '-->'\n");
			return NULL;
		}
		str[-3] = 0;
		SETBIT(elem->m_Flags, Element::FLAG_COMMENT);
		elem->m_dataStart = start;
		elem->m_dataLen = (unsigned int)(str - start - 3);
		if (elem->m_dataLen >= XML_MAX_COMMENT_LEN)
		{
			ElementDelete(elem);
			MarkupError("program instruction exceeded max size\n");
			return NULL;
		}
		if (!ParseOpenTag(str))
		{
			MarkupError("expected '<'\n");
			return NULL;
		}
		return elem;
	}

	if (!ParseStartTag(elem, str, isempty))
	{
		ElementDelete(elem);
		return NULL;
	}

	// return if empty element
	if (isempty)
	{
		// if the root is empty, don't go looking for a '<'
		if (parent != m_ElementTree && !ParseOpenTag(str))
		{
			MarkupError("expected '<'\n");
			return NULL;
		}
		return elem;
	}

	// read contents (children, data)
	while (TRUE)
	{
		// read data and/or eat '<' (at the end of this, the m_chPrevChar is *always* '<')
		Token token;
		if (!ParseGetData(token, str))
		{
			ElementDelete(elem);
			return NULL;
		}

		// set the data
		if (token.m_nLen >= XML_MAX_DATA_LEN)
		{
			MarkupError("Element data exceeded maximum allowed size.\n");
			ASSERT(token.m_nLen < XML_MAX_DATA_LEN);
			ElementDelete(elem);
			return NULL;
		}

		if (token.m_nLen > 0)
		{
			elem->m_dataStart = token.m_Start;
			elem->m_dataLen = token.m_nLen;
		}

		if (str[0] == _T('/'))		// end tag
		{
			++str;
			if (!ParseEndTag(elem, str))
			{
				MarkupError(_T("expected end of tag '%s'\n"), elem->m_tagStart);
				ElementDelete(elem);
				return NULL;
			}
			return elem;
		}

		// parse a  child element
		if (!ParseElement(elem, str))
		{
			ElementDelete(elem);
			return NULL;
		}
	}
}


