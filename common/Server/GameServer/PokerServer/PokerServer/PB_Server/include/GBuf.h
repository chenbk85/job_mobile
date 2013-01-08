//
// GBuf.h
//

#ifndef GBUF_H
#define GBUF_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///////////////////////////////////////////////////////////////////////////////
// GXBuf

typedef SelfPtrT<IXBuf> GXBuf;

///////////////////////////////////////////////////////////////////////////////
// GBuf

class  GBuf
{
protected:
	LPXBUF m_pXBuf;
public:
	GBuf() { m_pXBuf = ::XbufCreate(); }
	GBuf(const GBuf& buf) { m_pXBuf = ::XbufCreate(buf.m_pXBuf); }
	GBuf(LPXBUF pXBuf, BOOL bCopy) { m_pXBuf = (bCopy ? ::XbufCreate(pXBuf) : pXBuf); }
	GBuf(void* p, DWORD dwLen) { m_pXBuf = ::XbufCreate(); m_pXBuf->AddRight(p, dwLen); }
	~GBuf() { if(m_pXBuf) m_pXBuf->Delete(); }
public:
	void Attach(LPXBUF pXBuf) { if(m_pXBuf) m_pXBuf->Delete(); m_pXBuf = pXBuf; }
	LPXBUF Detach() { LPXBUF pXBuf = m_pXBuf; m_pXBuf = NULL; return pXBuf; }
public:
	inline LPXBUF GetXBuf() const { return m_pXBuf; }
	inline LPXBUF operator->() const { return m_pXBuf; }
	inline operator LPXBUF() const { return m_pXBuf; }
	GBuf& operator=(const GBuf& buf) { m_pXBuf->Copy(buf.m_pXBuf); return(*this); }
public:
	LPCBYTE GetData() const { return m_pXBuf->GetData(); }
	DWORD GetLength() const { return m_pXBuf->GetLength(); }
	void SetLength(DWORD dwLen) { m_pXBuf->SetLength(dwLen); }
	void Reserve(DWORD dwLen) { m_pXBuf->Reserve(dwLen); }
	void AddRight(LPVOID p, DWORD dwLen) { m_pXBuf->AddRight(p, dwLen); }
	void RemoveLeft(DWORD dwSize) { m_pXBuf->RemoveLeft(dwSize); }
	void Clear() { m_pXBuf->RemoveLeft( m_pXBuf->GetLength() ); }
public:
	// Buffer의 멤버인 XMEM의 시작점과 길이를 변경(실제 Data resize는 일어나지 않음에 유의)
	void SetPosLength(const DWORD dwPos, const DWORD dwLen) { m_pXBuf->SetPosLength(dwPos, dwLen); }
	DWORD GetPos() const { return m_pXBuf->GetPos(); }
};

///////////////////////////////////////////////////////////////////////////////
// GBufQ

class GBufQ : public std::list<GBuf>
{
public:
	typedef std::list<GBuf> TBase;
public:
	GBufQ() {};
	GBufQ(const GBuf& ro) { push_back(ro); }
	GBufQ(const GBufQ& rb) : TBase(rb) { }

	DWORD Count() const { return (DWORD)size(); };
	BOOL IsEmpty() const { return(size() == 0); };
	void Clear() { clear(); };

	GBuf& Top() { return front(); };
	GBuf Pop() { ASSERT(!IsEmpty()); GBuf ro = front(); pop_front(); return ro; }
	BOOL Pop(GBuf& ro) { if(IsEmpty()) return FALSE; ro = front(); pop_front(); return TRUE; }
	void Push(const GBuf& ro) { push_back(ro); }
	void Push(const GBufQ& rb) { insert(end(), rb.begin(), rb.end()); }

	GBufQ& operator+=(const GBuf& r) { Push(r); return *this; }
	GBufQ& operator+=(const GBufQ& r) { Push(r); return *this; }
	GBufQ operator+(const GBuf& r) { GBufQ rb(*this);	rb.Push(r); return rb;	}
	GBufQ operator+(const GBufQ& r) { GBufQ rb(*this); rb.Push(r);	return rb; }
};

///////////////////////////////////////////////////////////////////////////////

class GSafeBufQ
{
	IMPLEMENT_TISAFE(GSafeBufQ)
public:
	void Push(const GBuf& buf) {
		TLock lo(this);
		mRcvBufQ.Push(buf); 
	}
	BOOL Pop(GBuf& buf) {
		TLock lo(this);
		if(mRcvBufQ.IsEmpty()) return FALSE;
		mRcvBufQ.Pop(buf);
		return TRUE;
	}
	void Clear()
	{
		TLock lo(this);
		mRcvBufQ.Clear();
	}
protected:
	GBufQ mRcvBufQ;
};

#endif //!GBUF_H
