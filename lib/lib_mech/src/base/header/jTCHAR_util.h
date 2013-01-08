/* 
	filename:	jTCHAR_util.h
	coder	:	Cho Hyun Min (by icandoit) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	4337-09-15 오후 1:36:45
	title	:	
*/


#ifndef __jTCHAR_util_h__
#define __jTCHAR_util_h__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000

//-----------------------------------------------------------------------------
// UNICODE support for converting between CHAR, TCHAR, and WCHAR strings
//-----------------------------------------------------------------------------
#include "header/m_stltag.h"

namespace nMech
{

	namespace nUNI
	{
		// ansi용은 CHAR를 사용
		// UNICODE용 스트링은  WCHAR사용
		// 범용 스트링은 TCHAR사용

#ifdef UNICODE
		class jStringA;
		typedef jStringA jStringT;
#else
		class jStringW;
		typedef jStringW jStringT;
#endif


		// dest string의 글자수를 기준으로 변환
		//-----------------------------------------------------------------------------
		// Name: char2wchar_Cch()
		// Desc: This is a UNICODE conversion utility to convert a CHAR nUNI::tstring into a
		//       WCHAR nUNI::tstring. 
		//       cchDestCharactorLen is the size in TCHARs of wstrDest.  Be careful not to 
		//       pass in sizeof(strDest) 
		//-----------------------------------------------------------------------------
		inline HRESULT char2wchar_Cch( WCHAR* wstrDest, const CHAR* strSource, 
			int cchDestCharactorLen )
		{
			if( wstrDest==NULL || strSource==NULL || cchDestCharactorLen < 1 )
				return E_INVALIDARG;

			int nResult = MultiByteToWideChar( CP_ACP, 0, strSource, -1, 
				wstrDest, cchDestCharactorLen );
			wstrDest[cchDestCharactorLen-1] = 0;

			if( nResult == 0 )
				return E_FAIL;
			return S_OK;
		}



		//-----------------------------------------------------------------------------
		// Name: jTCHAR_Util_ConvertWideStringToAnsi()
		// Desc: This is a UNICODE conversion utility to convert a WCHAR nUNI::tstring into a
		//       CHAR nUNI::tstring. 
		//       cchDestCharactorLen is the size in TCHARs of strDest
		//-----------------------------------------------------------------------------
		inline HRESULT wchar2char_Cch( CHAR* strDest, const WCHAR* wstrSource, 
			int cchDestCharactorLen )
		{
			if( strDest==NULL || wstrSource==NULL || cchDestCharactorLen < 1 )
				return E_INVALIDARG;

			int nResult = WideCharToMultiByte( CP_ACP, 0, wstrSource, -1, strDest, 
				cchDestCharactorLen*sizeof(CHAR), NULL, NULL );
			strDest[cchDestCharactorLen-1] = 0;

			if( nResult == 0 )
				return E_FAIL;
			return S_OK;
		}

		//-----------------------------------------------------------------------------
		// Name: jTCHAR_Util_ConvertGenericStringToAnsi()
		// Desc: This is a UNICODE conversion utility to convert a TCHAR nUNI::tstring into a
		//       CHAR nUNI::tstring. 
		//       cchDestCharactorLen is the size in TCHARs of strDest
		//-----------------------------------------------------------------------------
		inline HRESULT tchar2char_Cch( CHAR* strDest, const TCHAR* tstrSource, 
			int cchDestCharactorLen )
		{
			if( strDest==NULL || tstrSource==NULL || cchDestCharactorLen < 1 )
				return E_INVALIDARG;

#ifdef _UNICODE
			return wchar2char_Cch( strDest, tstrSource, cchDestCharactorLen );
#else
			strncpy( strDest, tstrSource, cchDestCharactorLen );
			strDest[cchDestCharactorLen-1] = '\0';
			return S_OK;
#endif   
		}




		//-----------------------------------------------------------------------------
		// Name: jTCHAR_Util_ConvertGenericStringToWide()
		// Desc: This is a UNICODE conversion utility to convert a TCHAR nUNI::tstring into a
		//       WCHAR nUNI::tstring. 
		//       cchDestCharactorLen is the size in TCHARs of wstrDest.  Be careful not to 
		//       pass in sizeof(strDest) 
		//-----------------------------------------------------------------------------
		inline HRESULT tchar2wchar_Cch( WCHAR* wstrDest, const TCHAR* tstrSource, 
			int cchDestCharactorLen )
		{
			if( wstrDest==NULL || tstrSource==NULL || cchDestCharactorLen < 1 )
				return E_INVALIDARG;

#ifdef _UNICODE
			jw_strncpy_s( wstrDest, cchDestCharactorLen,tstrSource, cchDestCharactorLen );
			wstrDest[cchDestCharactorLen-1] = _TEXT('\0');
			return S_OK;
#else
			return char2wchar_Cch( wstrDest, tstrSource, cchDestCharactorLen );
#endif    
		}




		//-----------------------------------------------------------------------------
		// Name: jTCHAR_Util_ConvertAnsiStringToGeneric()
		// Desc: This is a UNICODE conversion utility to convert a CHAR nUNI::tstring into a
		//       TCHAR nUNI::tstring. 
		//       cchDestCharactorLen is the size in TCHARs of tstrDest.  Be careful not to 
		//       pass in sizeof(strDest) on UNICODE builds
		//-----------------------------------------------------------------------------
		inline HRESULT char2tchar_Cch( TCHAR* tstrDest, const CHAR* strSource, 
			int cchDestCharactorLen )
		{
			if( tstrDest==NULL || strSource==NULL || cchDestCharactorLen < 1 )
				return E_INVALIDARG;

#ifdef _UNICODE
			return char2wchar_Cch( tstrDest, strSource, cchDestCharactorLen );
#else
			strncpy( tstrDest, strSource, cchDestCharactorLen );
			tstrDest[cchDestCharactorLen-1] = '\0';
			return S_OK;
#endif    
		}


		//-----------------------------------------------------------------------------
		// Name: jTCHAR_Util_ConvertAnsiStringToGeneric()
		// Desc: This is a UNICODE conversion utility to convert a WCHAR nUNI::tstring into a
		//       TCHAR nUNI::tstring. 
		//       cchDestCharactorLen is the size in TCHARs of tstrDest.  Be careful not to 
		//       pass in sizeof(strDest) on UNICODE builds
		//-----------------------------------------------------------------------------
		inline  HRESULT wchar2tchar_Cch( TCHAR* tstrDest, const WCHAR* wstrSource, 
			int cchDestCharactorLen )
		{
			if( tstrDest==NULL || wstrSource==NULL || cchDestCharactorLen < 1 )
				return E_INVALIDARG;

#ifdef _UNICODE
			jw_strncpy_s( tstrDest,  cchDestCharactorLen,wstrSource, cchDestCharactorLen );
			tstrDest[cchDestCharactorLen-1] = _TEXT('\0');    
			return S_OK;
#else
			return wchar2char_Cch( tstrDest, wstrSource, cchDestCharactorLen );
#endif
		}

		//-----------------------------------------------------------------------------
		// Name: BYTE helper functions
		// Desc: cchDestCharactorLen is the size in BYTEs of strDest.  Be careful not to 
		//       pass use sizeof() if the strDest is a nUNI::tstring pointer.  
		//       eg.
		//       TCHAR* sz = new TCHAR[100]; // sizeof(sz)  == 4
		//       TCHAR sz2[100];             // sizeof(sz2) == 200
		//-----------------------------------------------------------------------------

		// dest string의 버퍼의 길이를 기준을 변환
		inline HRESULT char2wchar_Cb( WCHAR* wstrDest, const CHAR* strSource, int cbDestBufferSize )
		{		return char2wchar_Cch( wstrDest, strSource, cbDestBufferSize / sizeof(WCHAR) );	}
		inline HRESULT wchar2char_Cb( CHAR* strDest, const WCHAR* wstrSource, int cbDestBufferSize )
		{		return wchar2char_Cch( strDest, wstrSource, cbDestBufferSize / sizeof(CHAR) );	}
		inline HRESULT tchar2char_Cb( CHAR* strDest, const TCHAR* tstrSource, int cbDestBufferSize )
		{		return tchar2char_Cch( strDest, tstrSource, cbDestBufferSize / sizeof(CHAR) );	}
		inline HRESULT tchar2wchar_Cb( WCHAR* wstrDest, const TCHAR* tstrSource, int cbDestBufferSize )
		{		return tchar2wchar_Cch( wstrDest, tstrSource, cbDestBufferSize / sizeof(WCHAR) );	}
		inline HRESULT char2tchar_Cb( TCHAR* tstrDest, const CHAR* strSource, int cbDestBufferSize )
		{		return char2tchar_Cch( tstrDest, strSource, cbDestBufferSize / sizeof(TCHAR) );	}
		inline HRESULT wchar2tchar_Cb( TCHAR* tstrDest, const WCHAR* wstrSource, int cbDestBufferSize )
		{		return wchar2tchar_Cch( tstrDest, wstrSource, cbDestBufferSize / sizeof(TCHAR) );	}

		template< int T>
		class StringConvertBuffer
		{
			enum 
			{
				eBUFFER_SIZE = T,
			};
			WCHAR w_buf[T];
			CHAR a_buf[T];
		public:
			StringConvertBuffer(){ w_buf[0]=0; a_buf[0]=0;}
			StringConvertBuffer(wcstr sz){ set(sz);}
			StringConvertBuffer(acstr sz){ set(sz);}
			StringConvertBuffer(std::string sz){ set(sz.c_str());}
			StringConvertBuffer(std::wstring sz){ set(sz.c_str());}

			StringConvertBuffer& set(wcstr buf)
			{
				if(!buf)buf=L"";
				size_t iSize = jw_strlen(buf);
				if(iSize > (ARRAY_SIZE(w_buf)-1))
				{
// 					WCHAR buf12[1024];
// 					jw_sprintf(buf12, L"ERROR StringConvertBuffer& set : jw_strlen=%d , buf_size= %d, ARRAY_SIZE(w_buf)=%d"
// 						,iSize, eBUFFER_SIZE,ARRAY_SIZE(w_buf) );
// 					jMB(buf12,buf);
					jt_printf(_T("ERROR StringConvertBuffer& set : jw_strlen=%d , buf_size= %d, ARRAY_SIZE(w_buf)=%d")
						,iSize, eBUFFER_SIZE,ARRAY_SIZE(w_buf) );
				}
				jw_strncpy(w_buf,buf,eBUFFER_SIZE-1);
				w_buf[eBUFFER_SIZE-1]=0;
				a_buf[0]=0;
				return *this;
			}
			StringConvertBuffer& set(acstr buf)
			{
				if(!buf)buf="";
				size_t iSize = ja_strlen(buf);
				if(iSize> (ARRAY_SIZE(a_buf)-1))
				{
// 					CHAR buf12[1024];
// 					ja_sprintf(buf12, "ERROR StringConvertBuffer& set : jw_strlen=%d , buf_size= %d, ARRAY_SIZE(w_buf)=%d"
// 						,iSize, eBUFFER_SIZE,ARRAY_SIZE(w_buf) );
// 					jMB(buf12,buf);
					jt_printf(_T("ERROR StringConvertBuffer& set : jw_strlen=%d , buf_size= %d, ARRAY_SIZE(w_buf)=%d")
							,iSize, eBUFFER_SIZE,ARRAY_SIZE(w_buf) );

				}
				ja_strncpy(a_buf,buf,eBUFFER_SIZE-1);
				a_buf[eBUFFER_SIZE-1]=0;
				w_buf[0]=0;
				return *this;
			}
			StringConvertBuffer& a2w()	{		if(w_buf[0]==0 && a_buf[0]!=0)		char2wchar_Cb(w_buf, a_buf, sizeof(w_buf)); return *this;	}
			StringConvertBuffer& w2a()	{		if(a_buf[0]==0 && w_buf[0]!=0)		wchar2char_Cb(a_buf, w_buf, sizeof(a_buf));	return *this; }
			StringConvertBuffer& update(){			a2w(); w2a();	return *this;	}
			CHAR* getA(){ 			w2a();			return a_buf;		}
			WCHAR* getW()	{ 			a2w();			return w_buf;		}
			TCHAR* getT()
			{ 
#ifdef UNICODE
				return getW();
#else
				return getA();
#endif
			}
			static void TestUnit(jIE* peTestNode);
		};

#define for_each_scb_t(X) X(2048) X(1024) X(256) X(128) X(64) X(32) X(16)
#define declear_scb_t(SIZE) typedef StringConvertBuffer<SIZE> _jJOIN_3(scb,SIZE,_t);
		for_each_scb_t(declear_scb_t);


		//multi-byte string을 wide-char string으로 변환하는 코드
		//http://cpplog.tistory.com/19http://cpplog.tistory.com/19
		inline std::wstring mbs_to_wcs(std::string const& str, std::locale const& loc = std::locale())
		{
			typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_t;
			codecvt_t const& codecvt = std::use_facet<codecvt_t>(loc);
			std::mbstate_t state = 0;
			std::vector<wchar_t> buf(str.size() + 1);
			char const* in_next = str.c_str();
			wchar_t* out_next = &buf[0];
			codecvt_t::result r = codecvt.in(state, 
				str.c_str(), str.c_str() + str.size(), in_next, 
				&buf[0], &buf[0] + buf.size(), out_next);
			return std::wstring(&buf[0]);
		}

		//wide-char string을 multi-byte string으로 변환하는 코드
		inline std::string 	wcs_to_mbs(std::wstring const& str, std::locale const& loc = std::locale())
		{
			typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_t;
			codecvt_t const& codecvt = std::use_facet<codecvt_t>(loc);
			std::mbstate_t state = 0;
			std::vector<char> buf((str.size() + 1) * codecvt.max_length());
			wchar_t const* in_next = str.c_str();
			char* out_next = &buf[0];
			codecvt_t::result r = codecvt.out(state, 
				str.c_str(), str.c_str() + str.size(), in_next, 
				&buf[0], &buf[0] + buf.size(), out_next);
			return std::string(&buf[0]);
		}
	}//namespace nUNI
}

//#include "header/nUNI_StringA.h"
//#include "header/nUNI_StringW.h"

#endif //__jTCHAR_util_h__
