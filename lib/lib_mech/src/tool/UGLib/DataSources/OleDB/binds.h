#ifndef __BINDING_CLASSES
#define __BINDING_CLASSES


class Column 
{
protected:
	void*		m_buffer;
	DWORD		m_Length;
	DBSTATUS	m_Status;
	ULONG		m_iOrdinal;
	LONG		m_MaxLength;
	DBTYPE		m_Type;
	BYTE		m_Precision;
	BYTE		m_Scale;

	CString		m_colName;
	BOOL		m_Dirty;

public:
	// ctor & dtor
	Column ();
	virtual ~Column();
	// operations
	const CString& ColumnName() const
		{ return m_colName; }
	DBTYPE Type() const
		{ return m_Type; }
	BOOL GetDirty()
		{ return m_Dirty; }
	void SetDirty(BOOL dirty)
		{ m_Dirty=dirty; }

	BOOL SetBinding(DBCOLUMNINFO* pColInfo);
	BOOL GetBinding(DBBINDING* pDBBind, long baseAddress);



	CString ToString() const;
	BOOL FromString(const CString& str);
};


class Columns
{
protected:
	Column*	m_cols;
// v7.2 - update 02 - 64-bit
#if _MSC_VER < 1400
	ULONG			m_NumCols;
#else 
	DBORDINAL		m_NumCols;
#endif

public:
	Columns() : m_cols(NULL), m_NumCols(0)
		{}
	~Columns();
	HRESULT SetColumnInfo(IColumnsInfo* pIColumnsInfo);
	HRESULT SetColumnBindings(DBBINDING** ppBinds, ULONG* cBound);
	HRESULT SetDirtyColumnBindings(DBBINDING** ppBinds, ULONG* cBound);

	// v7.2 - update 02 - 64-bit - added cast here
	int GetNumCols()
		{ return (int)m_NumCols; }

	Column* operator[](int nIndex);
	void* BaseAddress()
		{ return (void*) &m_cols[0]; }

};

#endif