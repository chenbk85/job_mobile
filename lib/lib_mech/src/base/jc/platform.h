////////////////////////////////////////////////////////////////////////////
//
//  jGame Source File.
//  Copyright (C), jGame, 2002.
// -------------------------------------------------------------------------
//  File name:   platform.h
//  Version:     v1.00
//  Created:     11/12/2002 by Timur.
//  Compilers:   Visual Studio.NET
//  Description: Platform dependend stuff.
//               Include this file instead of windows.h
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#if _MSC_VER > 1000
	#pragma once
#endif // _MSC_VER > 1000


#ifdef _DEBUG
	#include <crtdbg.h>
#endif

#include <tchar.h>
#include "header/jDefine_Cpu_Platform.h"
#include "header/jTypedef_type.h"
#include "header/jTypedef_func.h"
#include "stdio.h"

#ifdef __cplusplus

inline int IsHeapValid ()
{
#if defined(_DEBUG) //&& !defined(RELEASE_RUNTIME)
	return _CrtCheckMemory();
#else
	return true;
#endif
}
#endif

//////////////////////////////////////////////////////////////////////////
// Use our own memory manager.
// No Any STL includes must be before this line.
//////////////////////////////////////////////////////////////////////////
#ifndef NOT_USE_JCGAME_MEMORY_MANAGER
	#define USE_NEWPOOL
	#include <jc/jcMemoryManager.h>
#endif // NOT_USE_JCGAME_MEMORY_MANAGER


#ifdef __cplusplus
// define the standard string
#include <string>
#if defined(WIN64)// || defined(LINUX64)// && defined(_DLL), be careful when changing this to adapt the changes to IXml.h too
namespace nMech
{
	namespace nJC
	{

		namespace jc_std
		{
			template<typename T>
			class char_traits: public ::std::char_traits<T>
			{};
			// to avoid importing the string
			template <typename T>
			class string: public ::std::basic_string<T,char_traits<T> >
			{
			public:
				typedef ::std::basic_string<T,char_traits<T> > Base;
				string(){}
				string (const Base& s): Base(s.c_str()) {}
				string (const string& s): Base(s.c_str()) {}
				string (const T p): Base(p){}
				string (const T* p): Base(p){}
				//string (const_iterator itBegin, const_iterator itEnd): Base(itBegin, itEnd) {}
				string (const T* p, size_t n) : Base(p, n){}
				string (const T* p, const T* q): Base (p, q-p) {}
				string (const Base& s, size_t pos, size_t sz): Base(s,pos,sz) {}
				string& operator = (const Base& s)
				{
					// in Amd64 platform, the STL has reference-counted string
					// because of this, before self-assignment through a pointer,
					// the string gets destructed, which renders the pointer hanging.
					// to correct this, we avoid self-assignment through pointer
					if (s.c_str() != this->c_str())
						assign(s.c_str());
					return *this;
				}
				string& operator = (const T* p)
				{
					// in Amd64 platform, the STL has reference-counted string
					// because of this, before self-assignment through a pointer,
					// the string gets destructed, which renders the pointer hanging.
					// to correct this, we avoid self-assignment through pointer
					if (p != this->c_str())
						assign(p);
					return *this;
				}
				string& operator = (const string& s)
				{
					// in Amd64 platform, the STL has reference-counted string
					// because of this, before self-assignment through a pointer,
					// the string gets destructed, which renders the pointer hanging.
					// to correct this, we avoid self-assignment through pointer
					if (s.c_str() != this->c_str())
						assign (s.c_str());
					return *this;
				}
				void push_back(char c) {(*this) += c;}
				void clear() {this->resize(0);}

				string& operator += (const Base& s) {append(s);return *this;}
				string& operator += (char c) {append(1,c); return *this;}
				string& operator += (const T* p) {append(p);return *this;}
			};
			template <typename T> string<T> operator + (const string<T>& left, const string<T>& right) {return string<T>(left)+=right;}
			template <typename T> string<T> operator + (const typename string<T>::Base& left, const string<T>& right) {return string<T>(left)+=right;}
			template <typename T> string<T> operator + (const string<T>& left, const typename string<T>::Base& right) {return string<T>(left)+=right;}
			template <typename T> string<T> operator + (const T* left, const string<T>& right) {return string<T>(left)+=right;}
			template <typename T> string<T> operator + (const string<T>& left, const T* right) {return string<T>(left)+=right;}
			template <typename T> string<T> operator + (const T left, const string<T>& right) {return string<T>(left)+=right;}
			template <typename T> string<T> operator + (const string<T>& left, const T right) {return string<T>(left)+=right;}
		}

		typedef jc_std::string<char>//std::basic_string<char, jc_std::char_traits<char>, std::allocator<char> >
			string;
		typedef jc_std::string<wchar_t>//std::basic_string<wchar_t, jc_std::char_traits<wchar_t>, std::allocator<wchar_t> >
			wstring;

	}
}
#else	// defined(WIN64)
using namespace std;
//typedef std::string string;
//typedef std::wstring wstring;
#endif // defined(WIN64)


#endif // __cplusplus

#ifndef DEBUG_BREAK
#if defined(WIN32) || defined(WIN64)
#define DEBUG_BREAK _asm { int 3 }
#else
#define DEBUG_BREAK
#endif
#endif

#endif // _PLATFORM_H_
