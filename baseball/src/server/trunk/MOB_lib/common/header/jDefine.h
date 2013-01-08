/* file : jDefine.h
Coder : by icandoit (mech12@nate.com)
Date : 2005-06-07 22:42:55
title : 
desc : 

*/

#ifndef __jDefine_header__
#define __jDefine_header__
#pragma once

//#include <assert.h>
//#include <windows.h>



// 32/64 Bit versions.
#define SIGN_MASK(x) ((intptr_t)(x) >> ((sizeof(size_t)*8)-1))

#ifndef _CV
#define _CV(type , var) (*(type*)(void*)&var)
#endif
#ifndef _CVP
#define _CVP(type , var) ((type*)(void*)var)
#endif

#ifndef jS
#define jS(x)  _T(#x)
#endif

#ifndef _jL
#define _jL
#endif

#ifdef DEF_WINDOWS
#	define jFUNC _T(__FUNCTION__)
#	define jFUNC1 _T(__FUNCTION__) 
#else
#	undef __FUNCTION__
#	define __FUNCTION__ __PRETTY_FUNCTION__
#	define jFUNC  __FUNCTION__
#	define jFUNC1  __FUNCTION__
#	define OUT
#	define IN
#	define INOUT
#endif



#define jF jFUNC
#define jF1 jFUNC1

#define _jA(x) #x
#define _jW(x) L ## #x


#define jA(x) scbconvert(x).getA()
#define jT(x) scbconvert(x).getA()
#define jW(x) x

//플로팅에 관한 정의 
#define jFLOAT_ZERO		1.0e-20f	//0 으로 간주되는 값
#define jFLOAT_ERROR	1.0e-10f	// 허용오차	

#define jNEW( x , type ) x = new type;    if( !x ) throw false
#define jNEWi( x , type, i )  x = new type[i]; if( !x ) throw false

#define jDEL(x) if(x){delete (x); x = NULL; }
#define jDELi(x) if( (x) ){delete[] (x); (x) = NULL; }
#define jDEL_REL(x) if( x ){(x)->Release();delete (x); x = NULL; }

//#define ONETIME_CALL(a) struct _##a##_{_##a##_():};_##a##_::_##a##_()
#define ONETIME_CALL(a) struct a##_{ a##_(); ~a##_(); }
#define MY_ASSERT(a) if(!(a)) DEBUG_BREAK;

#define CLASS_CLS()			memset(this , 0 , sizeof(*this) );
#define CLASS_CLS1(p)			memset(((TCHAR*)this)+sizeof(p),0,sizeof(*this)-sizeof(p) );
#define CLASS_CLS2(p1,p2) memset(((TCHAR*)this)+sizeof(p1)+sizeof(p2),0,sizeof(*this)-sizeof(p1)-sizeof(p2) );

#define jCLEAR(X) memset(&X,0,sizeof(X));

#define FILE_LEN(fp) filelength( fileno(fp) )
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0])-1)
#define ArraySize(a) (sizeof(a)/sizeof(a[0]))

#define MECH_TRY try{
#define MECH_CATCH }catch(TCHAR* s){if(_tcslen(s)>255)s[255]=0; ::MessageBox(0 , s ,_T("MECH_CATCH") , MB_OK); } \
	catch(bool){::MessageBox(0 ,  _T("ERROR BOOL EXCEPTION"),_T("MECH_CATCH") , MB_OK);} 
#define MECH_CATCH_END catch(EMechTryType) {;}

#define ONETIME_START() struct a_{a_();};static a_ s_a_;a_::a_()
#define ONETIME_END() struct b_{b_(){}~b_();};static b_ s_b_;b_::~b_()

#define jSTATIC_FUNC_TAG // static member func에서 사용.


#define Naked				__declspec( naked )
#define Naked_Fast  __declspec( naked ) __fastcall
/////////////////////////////////////////////////////
#define _Naked_Start()	\
	__asm{push ebp}	__asm{mov ebp, esp}	\
	__asm{sub esp, __LOCAL_SIZE}
#define  _Naked_End(i)		\
	__asm{mov esp, ebp} __asm{pop ebp} __asm{ret}
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
#define Naked_Start()	_Naked_Start() \
	__asm{ push ebx} __asm{push edi} __asm{push esi}
#define  Naked_End(i)		\
	__asm{ pop esi} __asm{pop edi} __asm{pop ebx}\
	_Naked_End(i)
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
#define Naked_Start_d()	_Naked_Start(); __asm{push edi}
#define  Naked_End_d(i)	__asm{pop edi} _Naked_End(i);
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
#define Naked_Start_b()		_Naked_Start() __asm{push ebx}
#define Naked_End_b(i)		__asm{pop ebx} _Naked_End(i)
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
#define Naked_Start_bd()		Naked_Start_b() __asm{push edi}
#define Naked_End_bd(i)		__asm{pop edi}  Naked_End_b(i)
/////////////////////////////////////////////////////


#define jDXM(X) ( *(D3DXMATRIX*)(void*)&X)
#define jDV3(x) ( *(D3DXVECTOR3*)(void*)&x)
#define jP3(x) ( *(jPoint3*)(void*)&x)
#define jDC4(x) ( *(D3DCOLORVALUE*)(void*)&x)

#ifndef jFOR
#define jFOR( a , it) for( it = (a).begin() ; it != (a).end(); ++it)
#define pFOR(a,it) for(it=(a);it;it=it->GetParent() )
#define rFOR(a,it) for(it=(a);it;it=it->GetRight())
#define cFOR(a,it) for(it=(a)->begin();it;it=it->GetRight())
#define lFOR(a,it) for(it=(a);it;it=it->GetLeft() )
#define jrFOR(it) for(; it ; it=it->GetRight() )
#define eFOR(it) for( ; it.full() ; it = it->GetRight() )
#endif // jFOR

#define ___jJOIN___(x,y) x##y
#define _jJOIN_(x,y) ___jJOIN___(x,y)
#define _jJOIN_2(x,y) _jJOIN_(x,y)
#define _jJOIN_3(x,y,z) _jJOIN_2(_jJOIN_(x,y),z)
#define _jJOIN_4(x,y,z,z1) _jJOIN_3(_jJOIN_(x,y),z,z1)
#define _jJOIN_5(x,y,z,z1,z2) _jJOIN_4(_jJOIN_(x,y),z,z1,z2)

#define ___jWIDEN2___(x) L ## x
#ifdef UNICODE
#define jTEXT(x) ___jWIDEN2___(#x)
#else
#define jTEXT(x) #x
#endif

#define __WFILE__ WIDEN(__FILE__)

#define CONCAT_3_(x, y)					x##y
#define CONCAT_2_(x, y)					CONCAT_3_(x, y)
#define CONCAT(x, y)					CONCAT_2_(x, y)
#define UIDEN(x)						CONCAT(x, __LINE__)

#define SQL_OK(res)		((res) == SQL_SUCCESS || (res) == SQL_SUCCESS_WITH_INFO)
#define SQL_ERR(res)	(!SQL_OK(res))
#define SAFE_STR(str)	((str == NULL) ? _T("") : str)


#ifndef ja_strcpy1
#	define ja_strcpy1(var,sz) strncpy_s(var,sz,sizeof(var)-1);var[sizeof(var)-1]=0;
#	define ja_strncpy1(var,sz,n) strncpy(var,sz,n-1);var[n-1]=0;

#	define jt_strcpy1(var,sz) jt_strncpy_s(var,sz,sizeof(var)-1);var[sizeof(var)-1]=0;
#	define jt_strncpy1(var,sz,n) jt_strncpy(var,sz,n-1);var[n-1]=0;

#	define jw_strcpy1(var,sz) jw_strncpy_s(var,sz,sizeof(var)/2-1);var[sizeof(var)/2-1]=0;
#	define jw_strncpy1(var,sz,n) jw_strncpy(var,sz,n-1);var[n-1]=0;
#endif

// #pragma warning(disable : 4251)

#define jD3DCOLOR_ARGB(a,r,g,b) 	((uint)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)			{ if(p) { delete (p);		(p)=NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);		(p)=NULL; } }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release();	(p)=NULL; } }
#endif

#ifndef SAFE_RELEASE_FORCE
#define SAFE_RELEASE_FORCE(p)			{ if(p) { (p)->Release(1);	(p)=NULL; } }
#endif


#ifndef CLAMP
#define CLAMP(X, mn, mx) (X<mn ? mn : X<mx ? X : mx)
#endif

#ifndef LERP
#define LERP(A, B, Alpha) (A + Alpha * (B-A))
#endif

//runtime에서 NUM만큼만 실행되는 코드
#define jCALL_RUNTIME(NUM) static size_t  UIDEN(jCALL_RUNTIME)=0; UIDEN(jCALL_RUNTIME)+=1; if(UIDEN(jCALL_RUNTIME) <= NUM)

// 호출될때마다 한번만 실행되는 코드
#define jONCE			for (int UIDEN(_once) = 0; UIDEN(_once)++ == 0;)
#define jTWICE			for (int UIDEN(_twice) = 2; UIDEN(_twice)-- > 0;)
#define jONCE_END		break
#define jTWICE_END		break


// EXE로딩시 한번만 호출하는 코드
#define jONCE_RUN(jcls_x) struct UIDEN(jcls_x) { 	UIDEN(jcls_x)(); };static UIDEN(jcls_x) _jJOIN_2(UIDEN(jcls_x),_var); UIDEN(jcls_x)::UIDEN(jcls_x)()
#define jONCE_RUN_CTOR(jcls_x) struct jcls_x { 	jcls_x(); ~jcls_x(); };static jcls_x s_##jcls_x; jcls_x::jcls_x()
#define jONCE_RUN_DTOR(jcls_x) jcls_x::~jcls_x()





// macro for structure alignement
#ifdef LINUX
#define DEFINE_ALIGNED_DATA( type, name, alignment ) type name __attribute__ ((aligned(alignment)));
#define DEFINE_ALIGNED_DATA_STATIC( type, name, alignment ) static type name __attribute__ ((aligned(alignment)));
#define DEFINE_ALIGNED_DATA_CONST( type, name, alignment ) const type name __attribute__ ((aligned(alignment)));
#else
#define DEFINE_ALIGNED_DATA( type, name, alignment ) _declspec(align(alignment)) type name;
#define DEFINE_ALIGNED_DATA_STATIC( type, name, alignment ) static _declspec(align(alignment)) type name;
#define DEFINE_ALIGNED_DATA_CONST( type, name, alignment ) const _declspec(align(alignment)) type name;
#endif



#ifndef DEBUG_BREAK
#ifndef _WIN64
	#if defined(WIN32) 
	#define DEBUG_BREAK _asm { int 3 }
	#else 
	#define DEBUG_BREAK
	#endif
#else
	#define DEBUG_BREAK __debugbreak();
#endif

#endif



/*
#pragma warning(disable : 4267)
#pragma warning(default : 4267)

// bool , int 관련
#pragma warning(disable : 4805)
#pragma warning(default : 4805)

DLL 맴버변수관련
#pragma warning(disable : 4251)
#pragma warning(default : 4251)


//--------------------------------------------------------------------------
구조체 크기조정
//--------------------------------------------------------------------------
#pragma pack(1)
 1바이트 정렬을 합니다.
#pragma pack()
 기본 정렬을 합니다.(4 or 8 바이트 정렬)  

*/




//////////////////////////////////////////////////////////////////////////
// #pragma message TODO(msg) 재정의 - 해야할 일

#define jLINE1(x) #x
#define jLINE(x) jLINE1(x)
#define jTODO(msg)   message ( __FILE__ "(" jLINE(__LINE__)  "): [jTODO] " #msg )
#define jNOTE(msg)   message ( __FILE__ "(" jLINE(__LINE__)  "): [jNOTE] " #msg )

// 사용법 :
// #pragma TODO( "해야할 일" )
/*
http://www.npteam.net/311
#pragma를 이용해서 프로젝트에 할일을 F4 단축키로 찾아갈 수 있게 하는 방법

사용법 윗 부분을 복사해서 stdafx.h.. 등의 위치에 복사한 후 소스코드 중간에
#pragma TODO( "WM_TIMER - 타이머 처리 미구현" )

이와 같이 추가하면 컴파일 후 Build 창에 내용이 표시된다. 

출처 : TTF블로그(http://www.npteam.net)
*/


//using namespace nMech;

#define jDECL_VAR(TYPE,VAR,INIT_VAL,HELP) TYPE VAR;


// #ifdef _WIN32
// inline void jMB(const CHAR*x,const CHAR*y) {::MessageBoxA(0, x,y, MB_OK);}
// inline void jMB(const WCHAR*x,const WCHAR*y) {::MessageBoxW(0, x,y, MB_OK);}
// #endif

#define jSET_LOCALE() std::locale::global( std::locale( g_ExeEnv.GetDefaultLocale() ) ); 
#define jSET_LOCALE1(LANG) std::locale::global( std::locale( LANG ) ); 


#define jPLUS(X,TYPE) ( X=(TYPE)(X+1))
#define jMINUS(X,TYPE) ( X=(TYPE)(X-1))
template<typename T> T jPlus(T &x,int val=1){x = (T)(x+val);return x;}
template<typename T> T jMinus(T &x,int val=1){x = (T)(x-val);return x;}



#define jSPREED_SYSTEMTIME(t) t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond
#define jSPREED_SYSTEMTIME_PTR(t) &t.wYear,&t.wMonth,&t.wDay,&t.wHour,&t.wMinute,&t.wSecond
#ifdef DEF_WINDOWS
#define jPRINTF_SYSTEMTIME "%02d-%02d-%02d %02d:%02d:%03d"
#else
#define jPRINTF_SYSTEMTIME "%02hd-%02hd-%02hd %02hd:%02hd:%03hd"
#endif


#define for_each_12(X) X(1) X(2)
#define for_each_123(X) X(1) X(2) X(3)
#define for_each_1234(X) X(1) X(2) X(3) X(4) 
#define for_each_12345(X) X(1) X(2) X(3) X(4) X(5)
#define for_each_123456(X) X(1) X(2) X(3) X(4) X(5) X(6)
#define for_each_1234567(X) X(1) X(2) X(3) X(4) X(5) X(6) X(7)
#define for_each_12345678(X) X(1) X(2) X(3) X(4) X(5) X(6) X(7) X(8)
#define for_each_123456789(X) X(1) X(2) X(3) X(4) X(5) X(6) X(7) X(8) X(9)


//--------------------------------------------------------------------------
// bit flag 구문
//--------------------------------------------------------------------------
#include "jDefine_flag.h"

//--------------------------------------------------------------------------
// LAMDA 구문
//--------------------------------------------------------------------------
#include "jDefine_lamda.h"

//--------------------------------------------------------------------------
// 로그 매크로.
//--------------------------------------------------------------------------
#include "jDefine_log.h"

//--------------------------------------------------------------------------
// enum 매크로
//--------------------------------------------------------------------------
#include "jDefine_enum.h"

#endif // __jDefine_header__
