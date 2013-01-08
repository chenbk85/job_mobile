/* file : jTypedef_struct.h
Coder : by icandoit ( mech12@nate.com)
Date : 2006-12-13 10:38:00
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jTypedef_struct_header__
#define __jTypedef_struct_header__
#pragma once

namespace nMech
{

#define jUSE_JRECT
#ifdef jUSE_JRECT
	struct jRECT
	{
		union
		{
			struct { LONG lx,ly,lw,lh;};
			struct {int	x,y,w,h;};
			struct {unsigned int  ux,uy,uw,uh;};
		};
		jRECT(){}
		jRECT(bool){clear();}
		jRECT(const RECT& r){ *this = (*(jRECT*)&r);}
		jRECT(const jRECT& r){ memcpy(this,&r,sizeof(r) );}
		void clear(){ x=y=w=h=0;}
		operator RECT(){ return (*(RECT*)(void*)this ) ;}
	};
	extern void jRECT_TestUnit(); // jxVar.cpp에서 테스트함
#endif

	//--------------------------------------------------------------------------
	// jTYPE_ADAPTER 관련
	// 사용법은 jxVar.cpp의 jTYPE_ADAPTER_TestUnit참조
	//--------------------------------------------------------------------------
#if 0
	template <typename my_type, typename target_type>
	struct jTYPE_ADAPTER_ptr
	{
		void SET(const target_type*v){ memcpy(this, v, sizeof(my_type)); }
		jTYPE_ADAPTER_ptr(const target_type*v) { SET(v); }
		my_type &operator =(const target_type* v){ SET(v); return *(my_type*)this;}
		bool operator ==(const target_type* v){ return !memcmp(this, v, sizeof(my_type)) ; }
		bool operator !=(const target_type* v){ return memcmp(this, v, sizeof(my_type)) ; }
	};
	template <typename my_type, typename target_type>
	struct jTYPE_ADAPTER_ref
	{
		void SET(const target_type &v){ memcpy(this, &v, sizeof(my_type)); }
		jTYPE_ADAPTER_ref(const target_type& v) { SET(v); }
		my_type &operator =(const target_type& v){ SET(v); return *(my_type*)this;}
		bool operator ==(const target_type& v){ return !memcmp(this, &v, sizeof(my_type)) ; }
		bool operator !=(const target_type& v){ return memcmp(this, &v, sizeof(my_type)) ; }
		void validate()
		{ 
			if(sizeof(my_type)!=sizeof(target_type))
			{
#ifndef _WIN64
				__asm int 3; 	
#else
				__debugbreak();
#endif
			}
		}
	};


#define jFloat(num, CODE ) struct jFloat##num: public jTYPE_ADAPTER_ptr<jFloat##num, float>\
	{ union{ struct {float CODE;}; float p[num];};};


#define _jcode_ x,y
	jFloat(2,_jcode_);
#undef _jcode_

#define _jcode_ x,y,z
	jFloat(3,_jcode_);
#undef _jcode_

#define _jcode_ x,y,z,w
	jFloat(4,_jcode_);
#undef _jcode_

#else

#define jTYPE_ADAPTER_DECL(my_type, target_type)\
	void SET(const target_type*v){ memcpy(this, v, sizeof(my_type)); }\
	my_type(const target_type*v) { SET(v); }\
	my_type &operator =(const target_type* v){ SET(v); return *(my_type*)this;}\


#define jTYPE_ADAPTER_ptr_op(my_type,target_type)\
	inline bool operator ==(const my_type &a, const target_type* v){ return 0== memcmp(&a, v, sizeof(my_type)) ; }\
	inline bool operator !=(const my_type &a, const target_type* v){ return 0 !=memcmp(&a, v, sizeof(my_type)) ; }\


	struct jFloat2
	{
		jTYPE_ADAPTER_DECL(jFloat2, float)
			union
		{ 
			struct {float x,y;}; 
			float p[2];
		};
	};
	jTYPE_ADAPTER_ptr_op(jFloat2, float);

#endif

	extern void jTYPE_ADAPTER_TestUnit();
	/* *_* by icandoit : 2006-12-13 00:27:32
	// 사용예 
	float a[2];
	jFloat2 b = a; // ok
	float a[3];
	jFloat3 b = a; 
	float a[4];
	jFloat4 b = a;
	*/ //*_* by icandoit : 2006-12-13 00:27:34
}


#endif // __jTypedef_struct_header__
