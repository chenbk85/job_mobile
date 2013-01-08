#ifndef _asdf01928340932_Stream_header__
#define _asdf01928340932_Stream_header__
#pragma once

namespace nMech
{

	//--------------------------------------------------------------------------
	class jNetStreamRead 
		//--------------------------------------------------------------------------
	{
	private:
		uint8	*m_buf;
		uint16	m_iCurrLen;
		uint16	m_iTot;


	public:
		jNetStreamRead(uint8 *buffer,uint16 tot)
			:m_buf(buffer), m_iTot(tot)
		{
			m_iCurrLen			= 0;
		}
		void rewind()
		{
			m_iCurrLen			= 0;
		}

		uint32	GetCurrPos(VOID)	{	return m_iCurrLen;}

		uint8* ReadVirtual(uint16 iRead)
		{ 
			uint16 curr = m_iCurrLen;
			m_iCurrLen += iRead;
			return m_buf+curr;
		}

		template<typename T> void Read(T& data)
		{
			memcpy(&data, m_buf + m_iCurrLen, sizeof(T));m_iCurrLen += sizeof(T);
		}
		template<typename T> void ReadArray(T * data,uint16 length)
		{
			const int iSize1 = length * sizeof(T);
			memcpy(data, m_buf + m_iCurrLen, iSize1);m_iCurrLen += iSize1;
		}
		void Read_Memory(VOID *data, uint16 length)
		{
			memcpy(data, m_buf + m_iCurrLen, length);m_iCurrLen += length;
		}
	};//class jNetStreamRead 


	struct _jNetStreamWriteBufferBase
	{
		_jNetStreamWriteBufferBase(uint16 s):iSize(s){}
		const uint16 iSize;
		BYTE pBuffer[1];
	};

	template<int MAXLENGTH>
	struct jNetStreamWriteBuffer :public _jNetStreamWriteBufferBase 
	{
	private:
		BYTE  __pBuffer[MAXLENGTH];
	public:
		jNetStreamWriteBuffer() : _jNetStreamWriteBufferBase(MAXLENGTH) {}
	};

	struct jNetStreamWrite_error
	{
		jNetStreamWrite_error(uint16 iCurrLen, uint16 iCapacity,uint16 iSize)
			:currLen(iCurrLen) , capa(iCapacity),isize(iSize) {}
		uint16 currLen;
		uint16 capa;
		uint16 isize;
	};

	//--------------------------------------------------------------------------
	class jNetStreamWrite 
		//--------------------------------------------------------------------------
	{
	private:
		_jNetStreamWriteBufferBase &m_nsb;
		uint16	m_iCurrLen;

		void _checkOverFlow(uint16 iSize)
		{
			if( ( m_iCurrLen + iSize ) >capacity()) 
				throw jNetStreamWrite_error(m_iCurrLen, capacity(), iSize);
		}
	public:

		uint16 capacity(){ return m_nsb.iSize;}
		uint16 size(){ return m_iCurrLen;}
		void rewind(){ m_iCurrLen= 0;}
		BYTE* GetBuffer(){ return m_nsb.pBuffer;}

		jNetStreamWrite(_jNetStreamWriteBufferBase &nsb):m_nsb(nsb){m_iCurrLen			= 0;}

		template<typename T> void Write(const T& data)
		{
			const int iSize1 = sizeof(T);
			_checkOverFlow(iSize1);
			memcpy(m_nsb.pBuffer + m_iCurrLen, &data, iSize1);m_iCurrLen += iSize1;
		}
		template<typename T> void WriteArray(const T* data, uint16 length)
		{
			const int iSize1 = length * sizeof(T);
			_checkOverFlow(iSize1);
			memcpy(m_nsb.pBuffer + m_iCurrLen, data, iSize1);m_iCurrLen += iSize1;
		}
		void Write_Memory(void *data, uint16 length)
		{
			_checkOverFlow(length);
			memcpy(m_nsb.pBuffer + m_iCurrLen, data, length);m_iCurrLen += length;
		}
	};//class jNetStreamWrite 

	inline void Read(jNetStreamRead& st, std::string& data)
	{
		uint16 iLen;
		st.Read<nMech::uint16>(iLen);
		data.resize(iLen+1);
		st.ReadArray<CHAR>(&data[0] ,iLen);
	}
	inline void Read(jNetStreamRead& st, std::wstring& data)
	{
		uint16 iLen;
		st.Read<nMech::uint16>(iLen);
		data.resize(iLen+1);
		st.ReadArray<WCHAR>(&data[0] ,iLen);
	}
	inline void Read(jNetStreamRead& st, WCHAR* data,uint16 iSize)
	{
		uint16 iLen;
		st.Read<nMech::uint16>(iLen);
		if(iSize <=iLen)
		{
			throw _T("jNetStreamRead::Read(jNetStreamRead& st, WCHAR* data,uint16 iSize)");
		}
		st.ReadArray<WCHAR>(data ,iLen);
		data[iLen]=0;
	}
	inline void Read(jNetStreamRead& st, CHAR* data,uint16 iSize)
	{
		uint16 iLen;
		st.Read<nMech::uint16>(iLen);
		if(iSize <=iLen)
		{
			throw _T("jNetStreamRead::Read(jNetStreamRead& st, WCHAR* data,uint16 iSize)");
		}
		//jAssert0(iSize>iLen && "jNetStreamRead::Read(jNetStream& st, CHAR* data,uint16 iSize)");
		st.ReadArray<CHAR>(data ,iLen);
		data[iLen]=0;
	}


	inline void Write(jNetStreamWrite& st,wcstr data)
	{
		uint16 iLen = (uint16)jw_strlen(data);
		st.Write<uint16>(iLen);
		st.WriteArray<WCHAR>(data,iLen);
	}
	inline void Write(jNetStreamWrite& st,acstr data)
	{
		uint16 iLen = (uint16)ja_strlen(data);
		st.Write<uint16>(iLen);
		st.WriteArray<CHAR>(data,iLen);
	}
	inline void Write(jNetStreamWrite& st,const std::string& data) {	Write(st,data .c_str() );	}
	inline void Write(jNetStreamWrite& st,const std::wstring& data){	Write(st,data .c_str());	}

	template<typename T> inline void Read(jNetStreamRead& st,T &data){ st.Read<T>(data);}
	template<typename T> inline void Write(jNetStreamWrite& st,const T &data){ st.Write<T>(data);}
	template<typename T> inline void ReadArray(jNetStreamRead& st,T *data,uint16 iSize){ st.ReadArray<T>(data,iSize);}
	template<typename T> inline void WriteArray(jNetStreamWrite& st,const T *data,uint16 iSize){ st.WriteArray<T>(data,iSize);}


	typedef _jNetStreamWriteBufferBase nswb_t;
	typedef jNetStreamWriteBuffer<256> nswb256_t;
	typedef jNetStreamWriteBuffer<1024> nswb1024_t;
	typedef jNetStreamWriteBuffer<2048> nswb2048_t;
	typedef jNetStreamWriteBuffer<4096> nswb4000_t;
	typedef jNetStreamWriteBuffer<4096*2-50> nswb8000_t;
	typedef jNetStreamWriteBuffer<8192*2-50> nswb16000_t;
}


#endif // _asdf01928340932_Stream_header__
