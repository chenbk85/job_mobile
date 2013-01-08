/* file : jString.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-13 21:48:44
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jString_header__
#define __jString_header__
#pragma once

namespace nMech
{
	// === Do not use directly: use one of the predefined sizes below ===
#ifdef UNICODE
	typedef wchar_t jChar;
#else
	typedef char	jChar;
#endif

	struct jStringBase {
		const unsigned char MaxLength; // Real length is MaxLength+1.
		jChar s[1];
		jStringBase(int _MaxLength) : MaxLength(_MaxLength) {}
		operator jChar * () { return &s[0]; }
		operator void * () { return (void *)&s[0]; }
		const jChar * operator = (const jChar * _s) {
			return safeStringCopy(s,_s,MaxLength);
		}
		// Special safe string copy where MaxLength is 1 less than true buffer length.
		// strncpy() pads out nulls for the full length of the buffer specified by MaxLength.
		static inline jChar * safeStringCopy(jChar * d,const jChar * s,int MaxLength) {
			int i=0;
			while (s[i]) {
				d[i] = s[i];
				i++;
				if (i == MaxLength) break;
			} // while
			d[i] = 0; // Null terminate.
			return d;
		} // safeStringCopy
	};


	template<int MAXLENGTH> // MAXLENGTH is max printable characters (trailing NULL is accounted for in jStringBase::s[1]).
	struct jString : jStringBase {
	private:
		jChar ps[MAXLENGTH];
	public:
		jString() : jStringBase(MAXLENGTH) {
			s[0] = 0;
		}
		jString(const jChar * _s) : jStringBase(MAXLENGTH) {
			*this = _s;
		}
		const jChar * operator = (const jChar * _s) {
			return safeStringCopy(s,_s,MaxLength);
		}
		const jChar * operator = (const jString & _s) {
			return safeStringCopy(s,_s.s,MaxLength);
		}
		bool operator == (const jString & _s) {
			return _strcmp(s,_s.s) == 0;
		}
		bool compareCaseInsensitive(const jString & _s) {
			return _stricmp(s,_s.s) == 0;
		}
	};

	// === Fixed size strings for scripting ===

	typedef jString<8>   jString8;
	typedef jString<16>  jString16;
	typedef jString<32>  jString32;
	typedef jString<64>  jString64;
	typedef jString<128> jString128;
	typedef jString<256> jString256;
	typedef jString<1024> jString1024;
	typedef jString<2048> jString2048;

	namespace __nSQ
	{
		enum 
		{
			VAR_TYPE_NONE=-1,VAR_TYPE_INT=0,VAR_TYPE_UINT,VAR_TYPE_FLOAT,VAR_TYPE_BOOL
			,VAR_TYPE_CONST_STRING,VAR_TYPE_STRING,VAR_TYPE_USER_POINTER,VAR_TYPE_INSTANCE
		};
	}

	namespace nSQ 
	{

		template<>
		struct TypeInfo<jStringBase> {
			const jChar * typeName;
			TypeInfo() : typeName(_T("jStringBase")) {}
			enum {TypeID=__nSQ::VAR_TYPE_STRING,Size=sizeof(jStringBase),TypeMask='s'};
			operator ScriptVarType() { return ScriptVarType(TypeID); }
		};

		// === Fixed String Variants ===

		template<int N>
		struct TypeInfo<jString<N> > {
			jChar typeName[24];
			TypeInfo() { scsprintf(typeName,_T("jString<%d>"),N); }
			enum {TypeID=__nSQ::VAR_TYPE_STRING,Size=N*sizeof(jString<N>),TypeMask='s'};
			operator ScriptVarType() { return ScriptVarType(TypeID); }
		};

	}//namespace nSQ 

}//namespace nMech



#endif // __jString_header__
