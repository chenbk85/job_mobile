/* file : jMemoryChunk.h
Coder : by icandoit (mech12@nate.com)
Date : 2005-06-15 17:02:24
title : 
desc : 

*/

#ifndef __jMemoryChunk_header__
#define __jMemoryChunk_header__
#pragma once
#ifdef _DEBUG
extern CDebug asdfasdfasdf;
extern CDebug asdfasdfasdf_read;
#else
#define asdfasdfasdf(x)
#define asdfasdfasdf_read(x)

#endif

//---------------------------------------------------------------
struct jMemoryChunk
	//----------------------------------------------------------------
{
	TCHAR* m_pTop;
	size_t m_iTot;
	size_t m_iCurrPos;
	bool m_isInit;
	size_t size() { return m_iCurrPos;	}
	TCHAR* GetBuffer(){ return m_pTop; 	}
	void SetBuffer(TCHAR* v){ m_pTop = v; 	}
	void SetTotSize(size_t t){ m_iTot = t; m_iCurrPos=0;	}

	jMemoryChunk():m_isInit(false) ,m_pTop(0), m_iTot(0), m_iCurrPos(0)	{	}
	void init(int itot)
	{
		m_isInit=true;
		m_pTop = new TCHAR[itot];
		m_iTot = itot;
		m_iCurrPos = 0;
	}

	~jMemoryChunk()		{			if(m_isInit && m_pTop){delete[] m_pTop ; m_pTop=0;		}}

	void writeChunk(TCHAR val)	
	{
		asdfasdfasdf.SaveValue("tchar : %d",val);
		_writeChunk(sizeof(val) , &val);	
	}
	void writeChunk(uchar val)	{		
		asdfasdfasdf.SaveValue("uchar : %u",val);
		_writeChunk(sizeof(val) , &val);	
	}
	void writeChunk(int val)	{		
		asdfasdfasdf.SaveValue("int : %d",val);
		_writeChunk(sizeof(val) , &val);	
	}
	void writeChunk(uint val)	{		
		asdfasdfasdf.SaveValue("uint : %u",val);
		_writeChunk(sizeof(val) , &val);	}
	void writeChunk(int16 val)	{		
		asdfasdfasdf.SaveValue("uint : %d",val);

		_writeChunk(sizeof(val) , &val);	}
	void writeChunk(uint16 val)	{		
		asdfasdfasdf.SaveValue("uint16 : %u",val);

		_writeChunk(sizeof(val) , &val);	}
	void writeChunk(float val)	{		
		asdfasdfasdf.SaveValue("float : %f",val);

		_writeChunk(sizeof(val) , &val);	}
	void writeChunk(double val)	{		
		asdfasdfasdf.SaveValue("double : %f",val);
		_writeChunk(sizeof(val) , &val);	}
	void writeChunk(TCHAR* val)	{		
		asdfasdfasdf.SaveValue("char*: %s",val);

		_writeChunk(_tcslen(val)+1 , val );}

	void readChunk(TCHAR &val)	{		
		_readChunk(sizeof(val) , &val);	
		asdfasdfasdf_read.SaveValue("TCHAR : %d",val);
	}
	void readChunk(uchar &val)	{		
		_readChunk(sizeof(val) , &val);	
		asdfasdfasdf_read.SaveValue("uchar : %u",val);
	}
	void readChunk(int &val)	{		
		_readChunk(sizeof(val) , &val);	
		asdfasdfasdf_read.SaveValue("int : %d",val);
	}
	void readChunk(uint &val)	{		
		_readChunk(sizeof(val) , &val);	
		asdfasdfasdf_read.SaveValue("uint : %u",val);
	}
	void readChunk(int16 &val)	{		
		_readChunk(sizeof(val) , &val);	
		asdfasdfasdf_read.SaveValue("int16 : %d",val);
	}
	void readChunk(uint16 &val)	{		
		_readChunk(sizeof(val) , &val);	
		asdfasdfasdf_read.SaveValue("uint16 : %u",val);
	}
	void readChunk(float &val)		{		
		_readChunk(sizeof(val) , &val);	
		asdfasdfasdf_read.SaveValue("float : %f",val);
	}
	void readChunk(double &val)	{		
		_readChunk(sizeof(val) , &val);	
		asdfasdfasdf_read.SaveValue("double : %f",val);
	}

	// 주의 !!! val은 TCHAR*의 주소를 넘길것.
	// TCHAR* val ;				mc.readChunk(&val);
	void readChunk(TCHAR **val)	
	{		
		*val = ((TCHAR*)m_pTop+m_iCurrPos);
		m_iCurrPos +=(_tcslen(*val)+1);
		asdfasdfasdf_read.SaveValue("char* : %s",val);
	}
	
	// 값을 메모리 청크 에 쓴다.
	void _writeChunk(size_t  iSize, void* pVal)
	{
		if( m_iCurrPos + iSize > m_iTot)
		{
			size_t  iTot =256;
			if(m_iTot) iTot = m_iTot;
			TCHAR* p = new char[iTot*2];
			m_isInit= true;
			if(m_iTot)memcpy(p , m_pTop, m_iTot);
			if(m_pTop) delete[] m_pTop;
			m_pTop = p;
			m_iTot=iTot*2;
		}
		memcpy(m_pTop+m_iCurrPos  , pVal, iSize );
		m_iCurrPos += iSize;
	}

	// 값을 메모리청크로 부터 읽는다.
	void _readChunk(size_t  iSize , void* pVal)
	{
		assert(m_iCurrPos + iSize <= m_iTot);
		memcpy(pVal , m_pTop+m_iCurrPos , iSize);
		m_iCurrPos +=iSize;
	}



};


#endif // __jMemoryChunk_header__
