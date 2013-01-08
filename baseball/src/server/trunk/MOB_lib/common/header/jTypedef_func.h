/* file : jTypedef_func.h
Coder : by icandoit ( mech12@nate.com)
Date : 2006-11-29 12:42:52
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jTypedef_func_header__
#define __jTypedef_func_header__
#pragma once

namespace nMech
{
#ifdef __cplusplus

#ifndef FLOOR_DEF

#define FLOOR_DEF
	//////////////////////////////////////////////
	inline int Floor(float value)
		//////////////////////////////////////////////
	{	
		return (value < 0) ? ((int)(value)-1) : ((int)value); 
	}

	inline int FloorFixed(int value)
	{	
		return ( value < 0 ) ? ((value>>16) - 1) : (value>>16); 
	}

	//inline int Float2Fixed(float value){	return ((int)(value * 65536.0f));}

#endif

	// Useful templates
	template< class T > inline T Max( const T A, const T B )
	{
		return (A>=B) ? A : B;
	}
	template< class T > inline T Min( const T A, const T B )
	{
		return (A<=B) ? A : B;
	}
	template< class T > inline T Square( const T A )
	{
		return A*A;
	}

	template <class T>
	static inline void Snap( T &a, T min, T max )
	{
		if( a < min ) 		a = min;
		if( a > max ) 	a = max;
	}

	template< class T > inline T Clamp( const T X, const T Min, const T Max )
	{
		return X<Min ? Min : X<Max ? X : Max;
	}
	template< class T > inline T Align( const T Ptr, int Alignment )
	{
		return (T)(((DWORD)Ptr + Alignment - 1) & ~(Alignment-1));
	}
	template< class T > inline void Exchange( T& A, T& B )
	{
		const T Temp = A;
		A = B;
		B = Temp;
	}
	template <class T> void SWAP( T& a, T& b )
	{
		T c=a;
		a = b; b = c;
	}

	template< class T > T Lerp( T A, T B, float Alpha )
	{
		return A + Alpha * (B-A);
	}
	template< class T > inline T Abs( const T A )
	{
		return (A>=(T)0) ? A : -A;
	}

#endif
}


#endif // __jTypedef_func_header__
