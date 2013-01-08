/* file : test.h
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-06-23 23:40:08

title : 
desc : 

*/

#ifndef __test_header__
#define __test_header__
#pragma once


namespace nMech
{
	typedef int i32;
	typedef unsigned int u32;
	typedef unsigned __int64 u64;
	typedef double f64;
	typedef float f32;
	inline f64 GetLength( const D3DXVECTOR3* v ) { return sqrt(v->x*v->x + v->y*v->y + v->z*v->z); }
	inline f32 Dot(const D3DXVECTOR3* v0, const D3DXVECTOR3* v1) { return (f32)(v0->x*v1->x+v0->y*v1->y+v0->z*v1->z); } 

	inline f32 trim_0_360(f32 f)
	{ 
		while(f < 0)	f = f+360.f;
		while(f > 360)	f = f-360.f;
		return f;
	}
	inline void swap_max_min(f32 &max,f32 &min) 
	{ 
		if(max < min) 
		{
			f32 temp = max;
			max = min;
			min = temp;
		}
	}


	template <class T> void SWAP( T& a, T& b )
	{
		T c=a;
		a = b; b = c;
	}

	struct jRandom
	{
		u32 m_u32Seed;
		void Init(u32 seed)
		{
			m_u32Seed = seed;
		}
		i32 Rand()			{ return( ((m_u32Seed = m_u32Seed * 214013L + 2531011L) >> 16) & 0x7FFF );}
		i32 SimpleRandom()	{ return( ((m_u32Seed = m_u32Seed + 2531011L) >> 3) & 0x7FFF );}
		i32 ComplexRandom()
		{
			u32 next = m_u32Seed;
			i32  result;

			next *= 1103515245;
			next += 12345;
			result = (u32) (next / 65536) % 2048;

			next *= 1103515245;
			next += 12345;
			result <<= 10;
			result ^= (u32) (next / 65536) % 1024;

			next *= 1103515245;
			next += 12345;
			result <<= 10;
			result ^= (u32) (next / 65536) % 1024;

			m_u32Seed = next;
			return result;
		}
	};

}


#endif // __test_header__
