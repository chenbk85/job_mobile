//////////////////////////////////////////////////////////////////////////
// SafeInt, SafeInt64 class
// Author: Chunmin Ahn (emocreator@gmail.com)
// History: 
//  2008-01: Initial work
//

#pragma once


namespace nMech
{

struct SafeInt
{
	SafeInt()
	{
		InterlockedExchange(&_val, 0);
	}

	SafeInt(int v)
	{
		InterlockedExchange(&_val, v);
	}

	SafeInt(const SafeInt& v)
	{
		InterlockedExchange(&_val, v._val);
	}

	operator int() const
	{
		return _val;
	}

	int operator+=(int v)
	{
		return InterlockedExchangeAdd(&_val, v);
	}

	int operator+=(const SafeInt& v)
	{
		return InterlockedExchangeAdd(&_val, v._val);
	}

	int operator-=(int v)
	{
		return InterlockedExchangeAdd(&_val, -v);
	}

	int operator-=(const SafeInt& v)
	{
		return InterlockedExchangeAdd(&_val, -v._val);
	}

	int operator=(int v)
	{
		return InterlockedExchange(&_val, v);
	}

	SafeInt& operator++()
	{
		InterlockedIncrement(&_val);
		return *this;
	}

	int operator++(int)
	{
		return InterlockedIncrement(&_val);
	}

	SafeInt& operator--()
	{
		InterlockedDecrement(&_val);
		return *this;
	}

	int operator--(int)
	{
		return InterlockedDecrement(&_val);
	}

	volatile LONG _val;
};


inline SafeInt operator+(const SafeInt& l, const SafeInt& r)
{
	SafeInt s(l);
	return s += r._val;
}

inline SafeInt operator-(const SafeInt& l, const SafeInt& r)
{
	SafeInt s(l);
	return s -= r._val;
}


//////////////////////////////////////////////////////////////////////////


struct SafeInt64
{
	SafeInt64()
	{
		InterlockedExchange64(&_val, 0);
	}

	SafeInt64(INT64 v)
	{
		InterlockedExchange64(&_val, v);
	}

	SafeInt64(const SafeInt64& v)
	{
		InterlockedExchange64(&_val, v._val);
	}

	operator INT64() const
	{
		return _val;
	}

	INT64 operator+=(INT64 v)
	{
		return InterlockedExchangeAdd64(&_val, v);
	}

	INT64 operator+=(const SafeInt64& v)
	{
		return InterlockedExchangeAdd64(&_val, v._val);
	}

	INT64 operator-=(INT64 v)
	{
		return InterlockedExchangeAdd64(&_val, -v);
	}

	INT64 operator-=(const SafeInt64& v)
	{
		return InterlockedExchangeAdd64(&_val, -v._val);
	}

	INT64 operator++()
	{
		return InterlockedDecrement64(&_val);
	}

	INT64 operator--()
	{
		return InterlockedIncrement64(&_val);
	}

	volatile INT64 _val;
};


inline SafeInt64 operator+(const SafeInt64& l, const SafeInt64& r)
{
	SafeInt64 s(l);
	return s += r._val;
}

inline SafeInt64 operator-(const SafeInt64& l, const SafeInt64& r)
{
	SafeInt64 s(l);
	return s -= r._val;
}
}//namespace nMech