/*************************************************************** 
Project:	XADL 1.0
File name:	XADLBER.cpp 
Description: 
	builtin type夷됲쉳泥⑹㎏ 吏쒗슀吏э옙占폙ER(Binary Encoding Rule) 梨덌옙占쎌솙��땰�덉쭠�ｌ찓吏�吏뺤쮮占쎌솘占썬깄踰�믭옙
	primary template占쎌솫占퐏pecialized template姨뷀쉪 吏뺤쭬姨붿㎚夷됱㎚梨덊슇 姨붿꺼姨붷퍜
Copyright 吏고씥 since 2003 Neowiz Corp., ALL RIGHTS RESERVED.
Consult your license regarding permissions and restrictions.
***************************************************************/ 

#ifndef XADLBER_H
#define XADLBER_H
// skymind #pragma warning(disable:4267)

//#define XADL_CHECK_INCLUDE_BER_FILE

#ifndef ASSERT
#define EXCEPTION_ASSERT     0xE0000001
#define ASSERT(x) \
	if(!(x)) \
	::RaiseException( EXCEPTION_ASSERT, 0, 0, 0);
#endif


#include <list>
#include <string>
#include <vector>
#include <map>
#include <string.h>

using namespace std;

namespace adl {

//#define ArcListT std::list
//#define ArcVectorT std::vector


////////////////////////////////////////////////////////////
// Compile time Assert

template<unsigned long> struct CompileTimeError;
template<> struct CompileTimeError<true> {};


#define COMPILETIME_ASSERT(expr, msg) \
	{ adl::CompileTimeError<((expr)!=0)> ERROR_##msg; (void)ERROR_##msg; } 

////////////////////////////////////////////////////////////
// Check Type Conpatibility
template <typename T, typename U>
class Conversion
{
	typedef char Small;

	class Big { char dummy[2]; };
	static Small Test(U);
	static Big Test(...);
	static T MakeT();
public:
	enum { exists=sizeof(Test(MakeT()))==sizeof(Small) };
};

////////////////////////////////////////////////////////////
// Type Trait

template<typename T>
class TypeT
{
public:
	enum { IsFundamental=0 };

	enum { MaybeEnum=(sizeof(T)==sizeof(int)) ? 1: 0 };
	enum { HasBER=MaybeEnum }; 

	//enum { HasBER=Conversion<T,int>::exists ? 1 : 0 }; 
};

#define USE_FUNDAMENTAL_TYPE_BER(T)	\
	template<> class TypeT< T>\
	{	\
	public:	\
		enum { IsFundamental=0 }; \
		enum { HasBER=1 }; \
	};

#define USE_FUNDAMENTAL_CONTAINERTYPE_BER(Container)	\
	template<typename T> class TypeT< Container<T>>\
	{	\
	public:	\
		enum { IsFundamental=0 }; \
		enum { HasBER=1 }; \
	};


#define MAKE_FUNDAMENTAL_TYPE(T)	\
	template<> class TypeT< T>\
	{	\
	public:	\
		enum { IsFundamental=1 }; \
		enum { HasBER=1 }; \
	};


// unsigned integer
MAKE_FUNDAMENTAL_TYPE(unsigned char);
MAKE_FUNDAMENTAL_TYPE(unsigned short int);
MAKE_FUNDAMENTAL_TYPE(unsigned int);
MAKE_FUNDAMENTAL_TYPE(unsigned long int);
MAKE_FUNDAMENTAL_TYPE(unsigned long long);

// signed integer
MAKE_FUNDAMENTAL_TYPE(signed char);
MAKE_FUNDAMENTAL_TYPE(short int);
MAKE_FUNDAMENTAL_TYPE(int);
MAKE_FUNDAMENTAL_TYPE(long int);
MAKE_FUNDAMENTAL_TYPE(long long);

// floats
MAKE_FUNDAMENTAL_TYPE(float);
MAKE_FUNDAMENTAL_TYPE(double);
MAKE_FUNDAMENTAL_TYPE(long double);

// other integer
MAKE_FUNDAMENTAL_TYPE(bool);
MAKE_FUNDAMENTAL_TYPE(char);
#ifdef _NATIVE_WCHAR_T_DEFINED
MAKE_FUNDAMENTAL_TYPE(wchar_t);
#endif

template<typename T> class ArcListT;
template<typename T> class ArcPtrListT;
template<typename T> class ArcVectorT;
template<typename T> class ArcPtrVectorT;
template<typename T, int nSize> class ArcArrayT;

// Archible type
//USE_FUNDAMENTAL_CONTAINERTYPE_BER( ArcListT );
//USE_FUNDAMENTAL_CONTAINERTYPE_BER( ArcPtrListT );
//USE_FUNDAMENTAL_CONTAINERTYPE_BER( ArcVectorT );
//USE_FUNDAMENTAL_CONTAINERTYPE_BER( ArcPtrVectorT );
template<typename T, int nSize> class TypeT< ArcArrayT<T, nSize> >
{
public:	
		enum { IsFundamental=0 };
		enum { HasBER=1 };
};


///////////////////////////////////////////////////////////////////////////////////////////
// 	bool, char, SHORT, WORD, int, UINT, long, int, float, double, long long, POINT, RECT
//  GBuf

template<typename T>
class BER 
{
public:
	inline static int Size(T ){ return sizeof(T); }
	static bool Store(unsigned char** ppBuf, unsigned long* pdwLen, const T& val)
    {               

#ifdef XADL_CHECK_INCLUDE_BER_FILE
		COMPILETIME_ASSERT(TypeT<T>::HasBER, adlFILE_b_h__IS_NOT_INCLUDED );
#endif

		if(!(ppBuf) || !(*ppBuf)){
			return false;
		}
		if(*pdwLen<sizeof(T)){
			return false;
		}
		*(T*)(*ppBuf)=val;
		*ppBuf+=sizeof(T);
		*pdwLen-=sizeof(T);
		return true;
	}
	static bool Load(T* pVal, unsigned char** ppBuf, unsigned long* pdwLen)
	{
#ifdef XADL_CHECK_INCLUDE_BER_FILE
		COMPILETIME_ASSERT(TypeT<T>::HasBER, adlFILE_b_h__IS_NOT_INCLUDED );
#endif
		if(!(ppBuf) || !(*ppBuf) || !pdwLen || !pVal){
			return false;
		}
		if(*pdwLen<sizeof(T)){
			return false;
		}
		*pVal=(*(T*)(*ppBuf));
		*ppBuf+=sizeof(T);
		*pdwLen-=sizeof(T);
		return true;
	}
	static bool Copy(T* pVal, const T& val)
	{
#ifdef XADL_CHECK_INCLUDE_BER_FILE
		COMPILETIME_ASSERT(TypeT<T>::HasBER, adlFILE_b_h__IS_NOT_INCLUDED );
#endif
		if(NULL==pVal){
			return false;
		}
		*pVal=val;
		return true;
	}
};



///////////////////////////////////////////////////////////////////////////////
// string
template<>
class BER<string>
{
public:
	static int Size(const string& _obj )
	{ 
		return BER<unsigned long>::Size((int)0) + (int)_obj.size();
	} 
	static bool Store(unsigned char** ppBuf, unsigned long* pdwLen, const string& val)
	{
		if(!(ppBuf) || !(*ppBuf)){
			return false;
		}
		unsigned long dwSize=static_cast<unsigned long>(val.size());
		if(!(*ppBuf))	return false;
		if(*pdwLen<dwSize){
			return false;
		}
		if(!BER<unsigned long>::Store(ppBuf, pdwLen, (int)dwSize)) return false;
		if( 0<dwSize){
			memcpy((void*)(*ppBuf), (void*)val.c_str(), dwSize);
			*ppBuf+=dwSize;
			*pdwLen-=dwSize;
		}
		return true;
	}
	static bool Load(string* pVal, unsigned char** ppBuf, unsigned long* pdwLen)
	{
		if(!(ppBuf) || !(*ppBuf) || !pdwLen || !pVal){
			return false;
		}
		unsigned long dwSize=0;
		if(!BER<unsigned long>::Load((unsigned long*)&dwSize, ppBuf, pdwLen)) return false;
		if(*pdwLen<dwSize){
			return false;
		}
		*pVal=string((char*)(*ppBuf), (int)dwSize);
		*ppBuf+=dwSize;
		*pdwLen-=dwSize;
		return true;
	}
	static bool Copy(string* pVal, const string& val) 
	{
		if(!pVal)
		{
			return false;
		}

		*pVal=val;
		return true;
	}
};

///////////////////////////////////////////////////////////////////////////////
// wstring
template<>
class BER<wstring>
{
public:
	static int Size(const wstring& _obj )
	{ 
		return BER<unsigned long>::Size((int)0) + (int)_obj.size() * 2;
	} 
	static bool Store(unsigned char** ppBuf, unsigned long* pdwLen, const wstring& val)
	{
		if(!(ppBuf) || !(*ppBuf))
		{
			return false;
		}
		unsigned long dwSize=static_cast<unsigned long>(val.size()) * 2;
		if(!(*ppBuf)) return false;
		if(*pdwLen<dwSize){
			return false;
		}
		if(!BER<unsigned long>::Store(ppBuf, pdwLen, (int)dwSize)){
			return false;
		}
		if( 0<dwSize){
			memcpy((void*)(*ppBuf), (void*)val.c_str(), dwSize);
			*ppBuf+=dwSize;
			*pdwLen-=dwSize;
		}
		return true;
	}
	static bool Load(wstring* pVal, unsigned char** ppBuf, unsigned long* pdwLen)
	{
		if(!(ppBuf) || !(*ppBuf) || !pdwLen || !pVal)
		{
			return false;
		}

		unsigned long dwSize=0;
		if(!BER<unsigned long>::Load((unsigned long*)&dwSize, ppBuf, pdwLen)) return false;
		if(*pdwLen<dwSize) 
		{
			return false;
		}
		if( (dwSize & 1UL)==1UL)
			return false;
		*pVal=wstring((wchar_t*)(*ppBuf), (int)(dwSize >> 1));
		*ppBuf+=dwSize;
		*pdwLen-=dwSize;
		return true;
	}
	static bool Copy(wstring* pVal, const wstring& val) 
	{
		if(!pVal)
		{
			return false;
		}

		*pVal=val;
		return true;
	}
};



template<typename T> 
class ContainerTrait
{
public:
	static void MakeReserve(T* _obj, unsigned long dwSize)
	{
		_obj->reserve(dwSize);
	}
};


template<typename T , typename Allocator >
class ContainerTrait< std::list<T, Allocator> >
{
	typedef std::list<T,Allocator>ContainerT;
public:
	static void MakeReserve(ContainerT* , int )
	{
		// do nothing
	}
};


template< 
	typename T ,
	typename Allocator,
	template< typename T, typename Allocator>class Container >
class BER< Container<T, Allocator> >
{
	typedef Container<T,Allocator>ContainerT;
	typedef ContainerTrait<ContainerT> ContainerTraitT;

public:
	static int Size(const ContainerT& _obj )
	{
		unsigned long dwSize=BER<unsigned long>::Size((unsigned long)0);
		typename ContainerT::const_iterator i;
		for(i=_obj.begin(); i!=_obj.end(); i++)
			dwSize+=BER<T>::Size(*i);
		return dwSize;
	}
	static bool Store(unsigned char** ppBuf, unsigned long* pdwSize, const ContainerT& _obj)
	{
		if(!BER<unsigned long>::Store(ppBuf, pdwSize, (unsigned long)_obj.size()))
			return false;
		typename ContainerT::const_iterator i;
		for(i=_obj.begin(); i!=_obj.end(); i++)
			if(!BER<T>::Store(ppBuf, pdwSize, *i ))
				return false;
		return true;
	}
	static bool Load(ContainerT* _obj, unsigned char** ppBuf, unsigned long* pdwSize)
	{
		_obj->clear();
		unsigned long dwSize;
		if(!BER<unsigned long>::Load((unsigned long*)&dwSize, ppBuf, pdwSize))
			return false;
		ContainerTraitT::MakeReserve(_obj,dwSize);
		for(int i=0; i<(int)dwSize ; i++){
			_obj->push_back(T());
			if(!BER<T>::Load(&(_obj->back()), ppBuf, pdwSize))
				return false;
		}
		return true;
	};
	static bool Copy(ContainerT* dest, const ContainerT& src)
	{
		if(NULL==dest)
		{
		}
		dest->clear();
		
		 ContainerTraitT::MakeReserve(dest,static_cast<unsigned long>(src.size()));
		for(typename ContainerT::const_iterator itr=src.begin(); itr!=src.end(); itr++)
		{
			dest->push_back(T());
			if(!BER<T>::Copy(&(dest->back()), *itr))
				return false;
		}
		return true;
	};
};


template< typename K, typename T >
class BER< std::map<K, T> >
{
	typedef std::map<K, T> MapContainerT;
	typedef ContainerTrait<MapContainerT> ContainerTraitT;
public:
	static int Size(const MapContainerT& _obj )
	{
		unsigned long dwSize=BER<unsigned long>::Size((int)0);
		typename MapContainerT::const_iterator i;
		for(i=_obj.begin(); i!=_obj.end(); i++)
		{
			dwSize+=BER<K>::Size(i->first);
			dwSize+=BER<T>::Size(i->second);
		}
		return dwSize;
	}
	static bool Store(unsigned char** ppBuf, unsigned long* pdwSize, const MapContainerT & _obj)
	{
		if(!BER<unsigned long>::Store(ppBuf, pdwSize, (int)_obj.size()))
			return false;
		typename MapContainerT::const_iterator i;
		for(i=_obj.begin(); i!=_obj.end(); i++)
		{
			if(!BER<K>::Store(ppBuf, pdwSize, i->first ))
				return false;
			if(!BER<T>::Store(ppBuf, pdwSize, i->second ))
				return false;
		}
		return true;
	}
	static bool Load(MapContainerT* _obj, unsigned char** ppBuf, unsigned long* pdwSize)
	{
		_obj->clear();
		unsigned long dwSize;
		if(!BER<unsigned long>::Load(&dwSize, ppBuf, pdwSize))
			return false;
		K key;
		T type;
		//ContainerTraitT::MakeReserve(_obj,dwSize);
		for( int i=0; i<dwSize ; i++)
		{
			if(!BER<K>::Load(&key, ppBuf, pdwSize))
				return false;
			if(!BER<T>::Load(&type, ppBuf, pdwSize))
				return false;
			_obj->insert(MapContainerT::value_type(key, type));
		}
		return true;
	}
	static bool Copy(MapContainerT* dest, const MapContainerT& src)
	{
		if(NULL==dest)
		{
		}
		dest->clear();
		
		K key;
		T type;
		//ContainerTraitT::MakeReserve(dest,src.size());

		for(typename MapContainerT::const_iterator itr=src.begin(); itr!=src.end(); itr++)
		{
			if(!BER<K>::Copy(&key, itr->first))
				return false;
			if(!BER<T>::Copy(&type, itr->second))
				return false;
			dest->insert(MapContainerT::value_type(key, type));
		}
		return true;
	};
};


///////////////////////////////////////////////////////////////////////////////
// 	utility template function
template<typename T>
inline int BSize(T& _obj)
{
	return BER<T>::Size(_obj);
}


// Encoding function for char
template<typename T>
inline bool BLoad(T* _obj, unsigned char** ppBuf, int* dwSize)  // for types excluding Payload type
{
	return BER<T>::Load( _obj, ppBuf, dwSize);
}
template<typename T>
inline bool BCopy(T* dest, const T& src)
{
	return BER<T>::Copy( dest, src);
}

template<typename T>
inline bool BLoad(T& _obj, char* lpBuf, int* dwSize)  // for Payload types
{
	return BER<T>::Load( &_obj, &lpBuf, dwSize);
}

template<typename T>
inline bool BCopy(T& dest, const T& src)
{
	return BER<T>::Copy( &dest, src);
}


template<typename T>
inline bool BStore(char* lpBuf, int* dwSize, const T& _obj)
{
	return BER<T>::Store((char*)&lpBuf, dwSize, _obj);
}

// Encoding function for string
template<typename T>
inline bool BLoad(T& _obj, string& sBuf) 
{
	unsigned long dwSize=static_cast<unsigned long>(sBuf.length());
	int dwOrigSize=dwSize;
	//char pData=const_cast<char>((char)sBuf.data());
	unsigned char* pData=(unsigned char*)sBuf.data();
	bool bRet=BER<T>::Load( &_obj, &pData, &dwSize);
	if(bRet)
		sBuf=sBuf.substr(dwOrigSize - dwSize);
	return bRet;
}

template<typename T>
inline bool BStore(string& sBuf, const T& _obj) 
{
	int dwLen=static_cast<unsigned long>(sBuf.length());
	unsigned long dwSize=BER<T>::Size((T&)_obj);
	sBuf.resize(dwLen+dwSize);
	char* lpBuf=(char*)(sBuf.data() + dwLen);
	return BER<T>::Store((unsigned char**)&lpBuf, &dwSize, _obj);
}





}; // namespace adl {

#endif
