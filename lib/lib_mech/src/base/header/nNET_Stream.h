/* file : Stream.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-08 15:51:09
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef _asdf01928340932_Stream_header__
#define _asdf01928340932_Stream_header__
#pragma once

#ifndef jNOT_USE_nStream_net_string_SQ
#include "header/Namespace.h"
#include "base/jSQ_bind.h"
#endif //jNOT_USE_nStream_net_string_SQ

namespace nMech
{
	namespace nNET
	{
		namespace nStream
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
				size_t	GetTotSize()		{return m_iTot;}

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
					if((iSize1 +m_iCurrLen) > m_iTot)
						throw jFUNC1 _T("iSize1 +m_iCurrLen) > m_iTot");
					memcpy(data, m_buf + m_iCurrLen, iSize1);m_iCurrLen += iSize1;
				}
				void Read_Memory(VOID *data, uint16 length)
				{
					if((length+m_iCurrLen) > m_iTot)
						throw jFUNC1 _T("iSize1 +m_iCurrLen) > m_iTot");
					memcpy(data, m_buf + m_iCurrLen, length);m_iCurrLen += length;
				}
			};//class jNetStreamRead 


			struct _jNetStreamWriteBufferBase
			{
				_jNetStreamWriteBufferBase(uint16 s):m_pExternal(0),iSize(s){}
				_jNetStreamWriteBufferBase(BYTE* pExt,uint16 s):m_pExternal(pExt),iSize(s){}
				const uint16 iSize;
			private:
				BYTE* m_pExternal;
				BYTE m_pInternal[1]; //
			public:
				BYTE *GetBuffer(){ return m_pExternal ? m_pExternal: m_pInternal;}
			};

			template<int MAXLENGTH>
			struct jNetStreamWriteBuffer :public _jNetStreamWriteBufferBase 
			{
			private:
				BYTE  __pBuffer[MAXLENGTH];
			public:
				jNetStreamWriteBuffer() : _jNetStreamWriteBufferBase(0,MAXLENGTH) {}
				jNetStreamWriteBuffer(BYTE* pExt) : _jNetStreamWriteBufferBase(pExt,MAXLENGTH) {}
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
				BYTE* GetBuffer(){ return m_nsb.GetBuffer();}

				jNetStreamWrite(_jNetStreamWriteBufferBase &nsb):m_nsb(nsb){m_iCurrLen			= 0;}

				template<typename T> void Write(const T& data)
				{
					const int iSize1 = sizeof(T);
					_checkOverFlow(iSize1);
					memcpy(m_nsb.GetBuffer() + m_iCurrLen, &data, iSize1);m_iCurrLen += iSize1;
				}
				template<typename T> void WriteArray(const T* data, uint16 length)
				{
					const int iSize1 = length * sizeof(T);
					_checkOverFlow(iSize1);
					memcpy(m_nsb.GetBuffer() + m_iCurrLen, data, iSize1);m_iCurrLen += iSize1;
				}
				void Write_Memory(void *data, uint16 length)
				{
					_checkOverFlow(length);
					memcpy(m_nsb.GetBuffer() + m_iCurrLen, data, length);m_iCurrLen += length;
				}
			};//class jNetStreamWrite 

			inline void Read(jNetStreamRead& st, std::string& data)
			{
				uint16 iLen;
				st.Read<nMech::uint16>(iLen);
				if((st.GetCurrPos()+iLen) >= st.GetTotSize())
					throw jFUNC1 _T("if((st.GetCurrPos()+iLen) >= st.m_iTot)");
				data.resize(iLen);
				st.ReadArray<CHAR>(&data[0] ,iLen);
			}
			inline void Read(jNetStreamRead& st, std::wstring& data)
			{
				uint16 iLen;
				st.Read<nMech::uint16>(iLen);
				if((st.GetCurrPos()+iLen) >= st.GetTotSize())
					throw jFUNC1 _T("if((st.GetCurrPos()+iLen) >= st.m_iTot)");

				data.resize(iLen);
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
				//jASSERT0(iSize>iLen && "jNetStreamRead::Read(jNetStream& st, CHAR* data,uint16 iSize)");
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


			JBASE_API void Read(jNetStreamRead& st,jIE* data);
			JBASE_API void Write(jNetStreamWrite& st,jIE* data);

#ifndef jNOT_USE_nStream_net_string_SQ
			//--------------------------------------------------------------------------
			// net_string
			//--------------------------------------------------------------------------
			template<int iMAX>
			inline void Write_net_string(jNetStreamWrite& st,const net_string& data)
			{
				nUNI::StringConvertBuffer<iMAX> str(&data.s[0]);
				uint16 iLen = (uint16)(jw_strlen(str.getW())+1);
				st.Write<nMech::uint16>(iLen);
				st.WriteArray<WCHAR>(str.getW() , iLen);
			}
			template<int iMAX>
			inline void Read_net_string(jNetStreamRead& st, net_string& str)
			{
				uint16 iLen;
				st.Read<nMech::uint16>(iLen);
				jASSERT0( iMAX>(iLen+1) );
				WCHAR buf[iMAX];
				st.ReadArray<WCHAR>(buf , iLen);
				buf[iLen]=0;
				nUNI::StringConvertBuffer<iMAX> str1(buf);
				str =str1.getT();
			}
#define jDEF_net_string_jNetStream(SIZE)\
	inline void Read(jNetStreamRead& st, net_string##SIZE& str) { Read_net_string<SIZE>(st,str);}\
	inline void Write(jNetStreamWrite& st, const net_string##SIZE& str) { Write_net_string<SIZE>(st,str);}
			for_each_net_string(jDEF_net_string_jNetStream);

#endif //jNOT_USE_nStream_net_string_SQ

		}//namespace nStream

	}//namespace nNET
	typedef nNET::nStream::_jNetStreamWriteBufferBase nswb_t;
	typedef nNET::nStream::jNetStreamWriteBuffer<256> nswb256_t;
	typedef nNET::nStream::jNetStreamWriteBuffer<1024> nswb1024_t;
	typedef nNET::nStream::jNetStreamWriteBuffer<2048> nswb2048_t;
	typedef nNET::nStream::jNetStreamWriteBuffer<4096> nswb4000_t;
	typedef nNET::nStream::jNetStreamWriteBuffer<4096*2-50> nswb8000_t;
	typedef nNET::nStream::jNetStreamWriteBuffer<8192*2-50> nswb16000_t;
	// 50 은 패킷 해더size용
}


#endif // _asdf01928340932_Stream_header__
