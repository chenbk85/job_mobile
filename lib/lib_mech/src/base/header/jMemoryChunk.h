/* file : jMemoryChunk.h
Coder : by icandoit (mech12@nate.com)
Date : 2005-06-15 17:02:24
title : 
desc : 

*/

#ifndef __jMemoryChunk_header__
#define __jMemoryChunk_header__
#pragma once
#include "base/jBase.h"


namespace nMech
{
	namespace nUtil
	{
		//---------------------------------------------------------------
		struct JBASE_API jMemoryChunk
			//----------------------------------------------------------------
		{
		private:
			CHAR* m_pTop;
			size_t m_iTot;
			size_t m_iCurrPos;
			bool m_isInit;

		public:

			size_t size() { return m_iCurrPos;	}
			size_t GetTotalSize(){ return m_iTot;}
			CHAR* GetBuffer(){ return m_pTop; 	}
			void SetBuffer(CHAR* v, size_t iSize)
			{ 
				assert(!m_pTop);
				m_pTop = v; 	
				m_iTot =iSize;
				m_iCurrPos=0;
			}
			//void SetTotSize(size_t t){ m_iTot = t; m_iCurrPos=0;	}

			jMemoryChunk():m_isInit(false) ,m_pTop(0), m_iTot(0), m_iCurrPos(0)	{	}

			void init(int itot)
			{
				m_isInit=true;
				m_pTop = new CHAR[itot];
				m_iTot = itot;
				m_iCurrPos = 0;
			}

			void clear()
			{			
				if(m_isInit && m_pTop)
				{
					delete[] m_pTop ; m_pTop=0;		
				}
			}

			~jMemoryChunk(){ clear();}		

			template<typename T> void writeChunk(T val){		_writeChunk(sizeof(val) , &val);	}
			void writeChunk(CHAR* val)	{		_writeChunk( (ja_strlen(val)+1)*sizeof(CHAR) , val );}
			void writeChunk(const CHAR* val)	{	_writeChunk( (ja_strlen(val)+1)*sizeof(CHAR) , const_cast<CHAR*>(val ));}

			void writeChunk(WCHAR* val)	{		_writeChunk( (jw_strlen(val)+1)*sizeof(WCHAR) , val );}
			void writeChunk(const WCHAR* val)	{	_writeChunk( (jw_strlen(val)+1)*sizeof(WCHAR) , const_cast<WCHAR*>(val ));}


			template<typename T> void readChunk(T& val)	{		_readChunk(sizeof(val) , &val);	}

			// 주의 !!! val은 CHAR*의 주소를 넘길것.
			// CHAR* val ;				mc.readChunk(&val);
			void readChunk(CHAR **val)	
			{		
				*val = (CHAR*)(m_pTop+m_iCurrPos);
				m_iCurrPos +=( (ja_strlen(*val)+1)*sizeof(CHAR));
			}
			// 주의 !!! val은 CHAR*의 주소를 넘길것.
			// WCHAR* val ;				mc.readChunk(&val);
			void readChunk(WCHAR **val)	
			{		
				*val = (WCHAR*)(m_pTop+m_iCurrPos);
				m_iCurrPos +=( (jw_strlen(*val)+1)*sizeof(WCHAR));
			}

			// 값을 메모리 청크 에 쓴다.
			void _writeChunk(size_t  iSize, void* pVal);


			// 값을 메모리청크로 부터 읽는다.
			void _readChunk(size_t  iSize , void* pVal)
			{
				assert(m_iCurrPos + iSize <= m_iTot);
				memcpy(pVal , m_pTop+m_iCurrPos , iSize);
				m_iCurrPos +=iSize;
			}

			bool isEnd(){ return m_iCurrPos>=m_iTot;}
			// 현위치를 리턴하고 iSkipSize만큼 현제위치를 전진한다.
			void* skipChunk(size_t iSkipSize)
			{
				assert(m_iCurrPos + iSkipSize <= m_iTot);
				void* pVal = m_pTop+m_iCurrPos;
				m_iCurrPos +=iSkipSize;
				return pVal;
			}

		};

	}//nXML


}//namespace nMech

#endif // __jMemoryChunk_header__
