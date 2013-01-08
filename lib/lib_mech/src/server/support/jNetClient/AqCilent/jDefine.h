/* file : jDefine.h
Coder : by icandoit (mech12@nate.com)
Date : 2005-06-07 22:42:55
title : 
desc : 

*/

#ifndef __jDefine_header__
#define __jDefine_header__
#pragma once

#include <assert.h>
#include <windows.h>

// 32/64 Bit versions.
#define SIGN_MASK(x) ((intptr_t)(x) >> ((sizeof(size_t)*8)-1))

#ifndef _CV
#define _CV(type , var) (*(type*)(void*)&var)
#endif
#ifndef _CVP
#define _CVP(type , var) ((type*)(void*)var)
#endif

#ifndef jS
#define jS(x)  TEXT(#x)
#endif

#ifndef _jL
#define _jL
#endif

// _T를 사용한곳에 ansi캐릭터를 사용해야할때
#define _jA

#define jA(x) nUNI::scb256_t(x).getA()
#define jT(x) nUNI::scb256_t(x).getT()
#define jW(x) nUNI::scb256_t(x).getW()


#define jAssert(exp, desc) if(nDEBUG::jMyAssert( (int)(exp) , desc, _T(__LINE__ ),_T(__FILE__) )) { _asm{int 3}}

#define jAssert0(exp) if(!(exp)){jMB(_T(#exp), _T("jAssert0 error") ); exit(1);}

//if(nDEBUG::jMyAssert( (bool)(exp) , _T(#exp), _T(__LINE__) ,_T(__FILE__) )) { _asm{int 3}}

//#else
//	#define jAssert(exp,desc)
//#define jAssert0(exp) 
//#endif
#define TEXTURELOAD_NOW

//플로팅에 관한 정의 
#define jFLOAT_ZERO		1.0e-20f	//0 으로 간주되는 값
#define jFLOAT_ERROR	1.0e-10f	// 허용오차	

/*
// 게임브리오의 enum 값(INVALID)와 중복되어 컴파일오류로 인해 주석처리합니다. - by Client Jun
//리턴값에 이런 것이 있다.
#define INVALID			-1
#define ISVALID(x)		(x>=0)
#define ISINVALID(x)	(x<0)
*/

#define jNEW( x , type ) x = new type;    if( !x ) throw false
#define jNEWi( x , type, i )  x = new type[i]; if( !x ) throw false

#define jDEL(x) if(x){delete (x); x = NULL; }
#define jDELi(x) if( (x) ){delete[] (x); (x) = NULL; }
#define jDEL_REL(x) if( x ){(x)->Release();delete (x); x = NULL; }

//#define ONETIME_CALL(a) struct _##a##_{_##a##_():};_##a##_::_##a##_()
#define ONETIME_CALL(a) struct a##_{ a##_(); ~a##_(); }
#define DEBUG_HERE()  __asm int 3;  // DebugBreak()
#define MY_ASSERT(a) if(!(a)) DEBUG_HERE();

#define CLASS_CLS()			memset(this , 0 , sizeof(*this) );
#define CLASS_CLS1(p)			memset(((TCHAR*)this)+sizeof(p),0,sizeof(*this)-sizeof(p) );
#define CLASS_CLS2(p1,p2) memset(((TCHAR*)this)+sizeof(p1)+sizeof(p2),0,sizeof(*this)-sizeof(p1)-sizeof(p2) );

#define jCLEAR(X) memset(&X,0,sizeof(X));

#define FILE_LEN(fp) filelength( fileno(fp) )
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0])-1)
#define ArraySize(a) (sizeof(a)/sizeof(a[0]))

enum EMechTryType
{ 
	eMECH_TRY_SKIP
};

/*{hush(icq:74456993)2001-08-21오전 2:37:52
MECH_TRY 

MECH_CATCH_STR 
MECH_CATCH_BOOL 
MECH_CATCH_END 

}hush(icq:74456993) 2001-08-21오전 2:37:53*/

#define MECH_TRY try{
#define MECH_CATCH }catch(TCHAR* s){if(_tcslen(s)>255)s[255]=0; ::MessageBox(0 , s ,TEXT("MECH_CATCH") , MB_OK); } \
	catch(bool){::MessageBox(0 ,  TEXT("ERROR BOOL EXCEPTION"),TEXT("MECH_CATCH") , MB_OK);} 
#define MECH_CATCH_END catch(EMechTryType) {;}

#define ONETIME_START() struct a_{a_();};static a_ s_a_;a_::a_()
#define ONETIME_END() struct b_{b_(){}~b_();};static b_ s_b_;b_::~b_()



#define jBIT_0		0x00000001
#define jBIT_1		0x00000002
#define jBIT_2		0x00000004
#define jBIT_3		0x00000008
#define jBIT_4		0x00000010
#define jBIT_5		0x00000020
#define jBIT_6		0x00000040
#define jBIT_7		0x00000080
#define jBIT_8		0x00000100
#define jBIT_9		0x00000200
#define jBIT_10		0x00000400
#define jBIT_11		0x00000800
#define jBIT_12		0x00001000
#define jBIT_13		0x00002000
#define jBIT_14		0x00004000
#define jBIT_15		0x00008000
#define jBIT_16		0x00010000
#define jBIT_17		0x00020000
#define jBIT_18		0x00040000
#define jBIT_19		0x00080000
#define jBIT_20		0x00100000
#define jBIT_21		0x00200000
#define jBIT_22		0x00400000
#define jBIT_23		0x00800000
#define jBIT_24		0x01000000
#define jBIT_25		0x02000000
#define jBIT_26		0x04000000
#define jBIT_27		0x08000000
#define jBIT_28		0x10000000
#define jBIT_29		0x20000000
#define jBIT_30		0x40000000
#define jBIT_31		0x80000000


#define MASK_OFF			0x00000000
#define MASK_ON				0xffffffff



#define jSET_FLAG(var , bit)\
	bool GetFlag##var(){ return m_iFlag &bit; }\
	void SetFlag##var(bool is){ if(is) m_iFlag |=bit; 	else		m_iFlag &=~(bit); }

#define jFLAG_ENUM(enum_bit)\
	bool GetFlag_##enum_bit() const { return m_iFlag &enum_bit; }\
	void SetFlag_##enum_bit(bool is){ if(is) m_iFlag |=enum_bit; 	else		m_iFlag &=~(enum_bit); }


#define jFLAG_ENUM_VAL(val, enum_bit)\
	bool GetFlag_##enum_bit() const { return val &enum_bit; }\
	void SetFlag_##enum_bit(bool is){ if(is) val |=enum_bit; 	else		val &=~(enum_bit); }

namespace nMech
{
	inline int jGETFLAG(int var, int bit) { return (var & bit);}
	inline void jSETFLAG(int& var, int bit, bool is) {	if(is) var|=bit;	else var &=~bit;}

	//--------------------------------------------------------------------------
	class jFlagHelper
	//--------------------------------------------------------------------------
	{
		/*
		int m_iFlag = 0;
		bool myOldValue=jGETFLAG(m_iFlag,jBIT_12);
		bool myNewValue = true;
		jFlagHelper  flagTinyXml(m_iFlag, jBIT_12, myNewValue);
		jEQUAL(flagTinyXml.Get() , myNewValue);
		flagTinyXml.Set(false);
		jEQUAL(flagTinyXml.Get() , false);
		flagTinyXml.Reset();
		jEQUAL(flagTinyXml.Get() , myOldValue);
		*/
	private:
		int &m_iFlag;
		int m_iBit;
		bool m_bNewVal;
		bool m_bOldVal;
	public:
#pragma warning(disable : 4800)
		jFlagHelper(int& flag, int bit, bool bNewVal)	:m_iFlag(flag),m_iBit(bit), m_bNewVal(bNewVal)	
		{	
			m_bOldVal = (bool)jGETFLAG(flag, bit);
			Set();
		}
		bool Get(){ return (bool)jGETFLAG(m_iFlag,m_iBit);}
#pragma warning(default : 4800)

		~jFlagHelper(){ Reset();}
		void Set(bool is)	{		jSETFLAG(m_iFlag, m_iBit, is);}
		void Set()	{		jSETFLAG(m_iFlag, m_iBit, m_bNewVal);}
		void Reset() { jSETFLAG(m_iFlag, m_iBit, m_bOldVal);}
	};

	template<typename T>	struct jChangeHelper
	{
		T& m_TargetVar;
		T m_savedValue;
		jChangeHelper(T &oldValue,T newValue): m_TargetVar(oldValue),m_savedValue(oldValue){ m_TargetVar = newValue;}
		~jChangeHelper(){ m_TargetVar= m_savedValue; }
	};

}


#define jSET_GET(type, var) type m_##var;type Get_##var(){return m_##var;};void Set_##var(type val){m_##var=val;}


// use -> jSET_FLAG(MouseOver, jBIT_0);



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
#ifndef jT
#define jT(x,y) ( *(x*)(void*)&y)
#define jTp(x,y) ( (x*)(void*)&y)
#define jTc(x,y) ( (x*)y)
#endif

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



#define jONCE_RUN(jcls_x) struct jcls_x { 	jcls_x(); };static jcls_x s_##jcls_x; jcls_x::jcls_x()
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
#if defined(WIN32) || defined(WIN64)
#define DEBUG_BREAK _asm { int 3 }
#else
#define DEBUG_BREAK
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

#define LINE1(x) _T(#x)
#define LINE(x) LINE1(x)
#define TODO(msg) message ( _T(__FILE__) _T("(") LINE(__LINE__) _T("): [TODO] ") jS(msg) )

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


#ifdef _WIN32
inline void jMB(const CHAR*x,const CHAR*y) {::MessageBoxA(0, x,y, MB_OK);}
inline void jMB(const WCHAR*x,const WCHAR*y) {::MessageBoxW(0, x,y, MB_OK);}
#endif


#define jSET_LOCALE() std::locale::global( std::locale( g_ExeEnv.GetDefaultLocale() ) ); 
#define jSET_LOCALE1(LANG) std::locale::global( std::locale( LANG ) ); 

#ifdef _UNICODE
#define jt__argv __wargv
#else
#define jt__argv __argv
#endif




#define jPLUS(X,TYPE) ( X=(TYPE)(X+1))
#define jMINUS(X,TYPE) ( X=(TYPE)(X-1))
template<typename T> T jPlus(T &x,int val=1){x = (T)(x+val);return x;}
template<typename T> T jMinus(T &x,int val=1){x = (T)(x-val);return x;}




//--------------------------------------------------------------------------
// LAMDA 구문
//--------------------------------------------------------------------------

#define _jLAMDA_MEMBER_(TYPE,VAL) TYPE VAL;
#define _jLAMDA_ARG_X(TYPE ,VAL) TYPE _##VAL,
#define _jLAMDA_ARG_Z(TYPE ,VAL) TYPE _##VAL
#define _jLAMDA_SET_ARG_X(TYPE,VAL) VAL(_##VAL),
#define _jLAMDA_SET_ARG_Z(TYPE,VAL) VAL(_##VAL)

#define jLAMDA_CTOR(STRUCT)	struct STRUCT{jLAMDA_##STRUCT(_jLAMDA_MEMBER_,_jLAMDA_MEMBER_); \
	STRUCT(){};\
	STRUCT( jLAMDA_##STRUCT(_jLAMDA_ARG_X,_jLAMDA_ARG_Z)):\
	jLAMDA_##STRUCT(_jLAMDA_SET_ARG_X,_jLAMDA_SET_ARG_Z)\

#define jLAMDA_for_each0(NAME,IT_TYPE) struct NAME{	void operator()(IT_TYPE it)
#define jLAMDA_for_each(STRUCT,IT)	struct STRUCT{jLAMDA_##STRUCT(_jLAMDA_MEMBER_,_jLAMDA_MEMBER_); \
	STRUCT( jLAMDA_##STRUCT(_jLAMDA_ARG_X,_jLAMDA_ARG_Z)):\
	jLAMDA_##STRUCT(_jLAMDA_SET_ARG_X,_jLAMDA_SET_ARG_Z){}\
	void operator()(IT it)

#define jLAMDA_find_if0(NAME,IT_TYPE) struct NAME{	bool operator()(IT_TYPE it)
#define jLAMDA_find_if(STRUCT,IT)	struct STRUCT{jLAMDA_##STRUCT(_jLAMDA_MEMBER_,_jLAMDA_MEMBER_); \
	STRUCT( jLAMDA_##STRUCT(_jLAMDA_ARG_X,_jLAMDA_ARG_Z)):\
	jLAMDA_##STRUCT(_jLAMDA_SET_ARG_X,_jLAMDA_SET_ARG_Z){}\
	bool operator()(IT it)


#define jLAMDA_end() };


/* 사용예

// X(lamda환경변수들) , Z(lamdb환경변수의 마지막)
#define jLAMDA_jServerUserCountInfo(X,Z) \
		X(serverid_t ,sid)\
		Z(uint16,totClient)
		jLAMDA_CTOR(jServerUserCountInfo)
		{
		}
		jLAMDA_end()


#define jLAMDA_copy_jServerInfo(X,Z) \
		Z(vector<jServerInfo>&,servers)
		jLAMDA_for_each(copy_jServerInfo,jAqServerNode*)
		{
			servers.push_back(it->m_info);
		}
		jLAMDA_end()


		pPC->for_each(copy_jServerInfo(servers));

*/


#endif // __jDefine_header__
