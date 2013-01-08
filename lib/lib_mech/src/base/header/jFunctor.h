/* 
	filename:	jFunctor.h
	coder	:	Cho Hyun Min (icandoit@wemade.com) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	2005-02-28 오후 12:04:32
	title	:	


	사용예.

	struct A
	{
	int i;
	void myFunc(jIE* pE)
	{
	int i=0;
	i++;
	}
	};

	struct B
	{
	int b;
	typedef jFunctor1<jIE*> OnSetCallback;
	OnSetCallback m_calback;
	};

	void main()
	{
		A aa;
		B bb;
		bb.m_calback = jFunctor(aa,&A::myFunc);
		bb.m_calback(0);

	}

*/


#ifndef __jFunctor_h__
#define __jFunctor_h__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000

// Modified by Timur Davidenko...

//**************** callback.hpp **********************
// Copyright 1994 Rich Hickey
/* Permission to use, copy, modify, distribute and sell this software
 * for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Rich Hickey makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
*/

// 08/31/96 Rich Hickey
// Added ==, != and <
//  They are not inline, source is in file callback.cpp
//  Note: You must compile and link in callback.obj if you use them
// C++ doesn't allow ptr-to-func to void * anymore -> changed to void (*)(void)
// Added compiler workarounds for MS VC++ 4.2
// Prefixed all macros with RHCB
// Note: derivation from _jFunctorBase is now public, and access functions
// (for func, callee etc) are provided >>for implementation use only<<

// 06/12/94 Rich Hickey
// 3rd major revision
// Now functors are concrete classes, and should be held by value
// Virtual function mechanism removed
// Generic jFunctor() mechanism added for building functors
// from both stand-alone functions and object/ptr-to-mem-func pairs

/*
To use:

If you wish to build a component that provides/needs a callback, simply
specify and hold a Functor of the type corresponding to the args
you wish to pass and the return value you need. There are 10 Functors
from which to choose:

jFunctor0
jFunctor1<P1>
jFunctor2<P1,P2>
jFunctor3<P1,P2,P3>
jFunctor4<P1,P2,P3,P4>
Functor0wRet<RT>
Functor1wRet<P1,RT>
Functor2wRet<P1,P2,RT>
Functor3wRet<P1,P2,P3,RT>
Functor4wRet<P1,P2,P3,P4,RT>

These are parameterized by their args and return value if any. Each has
a default ctor and an operator() with the corresponding signature.

They can be treated and used just like ptr-to-functions.

If you want to be a client of a component that uses callbacks, you
create a Functor by calling jFunctor().

There are three flavors of jFunctor - you can create a jFunctor from:

a ptr-to-stand-alone function
an object and a pointer-to-member function.
a pointer-to-member function (which will be called on first arg of jFunctor)

Note: this last was not covered in the article - see CBEXAM3.CPP

jFunctor( ptr-to-function)
jFunctor( reference-to-object,ptr-to-member-function)
jFunctor( ptr-to-member-function)

The jFunctor system is 100% type safe. It is also type flexible. You can
build a jFunctor out of a function that is 'type compatible' with the
target jFunctor - it need not have an exactly matching signature. By
type compatible I mean a function with the same number of arguments, of
types reachable from the jFunctor's argument types by implicit conversion.
The return type of the function must be implicitly convertible to the
return type of the jFunctor. A jFunctor with no return can be built from a
function with a return - the return value is simply ignored.
(See ethel example below)

All the correct virtual function behavior is preserved. (see ricky
example below).

If you somehow try to create something in violation
of the type system you will get a compile-time or template-instantiation-
time error.

The Functor base class and translator
classes are artifacts of this implementation. You should not write
code that relies upon their existence. Nor should you rely on the return
value of jFunctor being anything in particular.

All that is guaranteed is that the Functor classes have a default ctor,
a ctor that can accept 0 as an initializer,
an operator() with the requested argument types and return type, an
operator that will allow it to be evaluated in a conditional (with
'true' meaning the jFunctor is set, 'false' meaning it is not), and that
Functors can be constructed from the result of jFunctor(), given
you've passed something compatible to jFunctor(). In addition you
can compare 2 functors with ==, !=, and <. 2 functors with the same
'callee' (function, object and/or ptr-to-mem-func) shall compare
equal. op < forms an ordering relation across all callee types -> the
actual order is not meaningful or to be depended upon.

/////////////////////// BEGIN Example 1 //////////////////////////
#include <iostream.h>
#include "callback.hpp"

//do5Times() is a function that takes a jFunctor and invokes it 5 times

void do5Times(const jFunctor1<int> &doIt)
	{
	for(int i=0;i<5;i++)
		doIt(i);
	}

//Here are some standalone functions

void fred(int i){cout << "fred: " << i<<endl;}
int ethel(long l){cout << "ethel: " << l<<endl;return l;}

//Here is a class with a virtual function, and a derived class

class B{
public:
	virtual void ricky(int i)
	   {cout << "B::ricky: " << i<<endl;}
};

class D:public B{
public:
	void ricky(int i)
	   {cout << "D::ricky: " << i<<endl;}
};

void main()
	{
	//create a typedef of the jFunctor type to simplify dummy argument
	typedef jFunctor1<int> *FtorType;

	jFunctor1<int> ftor;	//a jFunctor variable
	//make a jFunctor from ptr-to-function
	ftor = jFunctor( fred );
	do5Times(ftor);
	//note ethel is not an exact match - ok, is compatible
	ftor = jFunctor( ethel );
	do5Times(ftor);

	//create a D object to be a callback target
	D myD;
	//make jFunctor from object and ptr-to-member-func
	ftor = jFunctor( myD,&B::ricky );
	do5Times(ftor);
	}
/////////////////////// END of example 1 //////////////////////////

/////////////////////// BEGIN Example 2 //////////////////////////
#include <iostream.h>
#include "callback.hpp"

//Button is a component that provides a jFunctor-based
//callback mechanism, so you can wire it up to whatever you wish

class Button{
public:
	//ctor takes a jFunctor and stores it away in a member

	Button(const jFunctor0 &uponClickDoThis):notify(uponClickDoThis)
		{}
	void click()
		{
		//invoke the jFunctor, thus calling back client
		notify();
		}
private:
	//note this is a data member with a verb for a name - matches its
	//function-like usage
	jFunctor0 notify;
};

class CDPlayer{
public:
	void play()
		{cout << "Playing"<<endl;}
	void stop()
		{cout << "Stopped"<<endl;}
};

void main()
	{
	CDPlayer myCD;
	Button playButton(jFunctor((jFunctor0*)0,myCD,&CDPlayer::play));
	Button stopButton(jFunctor((jFunctor0*)0,myCD,&CDPlayer::stop));
	playButton.click();	//calls myCD.play()
	stopButton.click();  //calls myCD.stop()
	}
/////////////////////// END of example 2 //////////////////////////

*/

//******************************************************************
///////////////////////////////////////////////////////////////////*
//WARNING - no need to read past this point, lest confusion ensue. *
//Only the curious need explore further - but remember				 *
//about that cat!																	 *
///////////////////////////////////////////////////////////////////*
//******************************************************************

//////////////////////////////
// COMPILER BUG WORKAROUNDS:
// As of version 4.02 Borland has a code generation bug
// returning the result of a call via a ptr-to-function in a template

#ifdef __BORLANDC__
#define RHCB_BC4_RET_BUG(x) RT(x)
#else
#define RHCB_BC4_RET_BUG(x) x
#endif

namespace nMech
{
	namespace nHEADER
	{


// MS VC++ 4.2 still has many bugs relating to templates
// This version works around them as best I can - however note that
// MS will allow 'void (T::*)()const' to bind to a non-const member function
// of T. In addition, they do not support overloading template functions
// based on constness of ptr-to-mem-funcs.
// When _MSC_VER is defined I provide only the const versions,however it is on
// the user's head, when calling jFunctor with a const T, to make sure
// that the pointed-to member function is also const since MS won't enforce it!

// Other than that the port is completely functional under VC++ 4.2

// One MS bug you may encounter during _use_ of the callbacks:
// If you pass them by reference you can't call op() on the reference
// Workaround is to pass by value.

/*
// MS unable to call operator() on template class reference
template <class T>
class Functor{
public:
	void operator()(T t)const{};
};

void foo(const Functor<int> &f)
	{
	f(1);	//error C2064: term does not evaluate to a function

	//works when f is passed by value
	}
*/

// Note: if you are porting to another compiler that is having trouble you
// can try defining some of these flags as well:


#if defined(_MSC_VER)	
#define jRHCB_CANT_PASS_MEMFUNC_BY_REFERENCE	//like it says
//#define _jRHCB_CANT_OVERLOAD_ON_CONSTNESS		//of mem funcs
#define jRHCB_CANT_INIT_REFERENCE_CTOR_STYLE	//int i;int &ir(i); //MS falls down
//#define _jRHCB_WONT_PERFORM_PTR_CONVERSION		//of 0 to ptr-to-any-type
#endif


// Don't touch this stuff
#if defined(jRHCB_CANT_PASS_MEMFUNC_BY_REFERENCE)
#define jRHCB_CONST_REF
#else
#define jRHCB_CONST_REF const &
#endif

#if defined(jRHCB_CANT_INIT_REFERENCE_CTOR_STYLE)
#define _jRHCB_CTOR_STYLE_INIT =
#else
#define _jRHCB_CTOR_STYLE_INIT
#endif

#if defined(_jRHCB_WONT_PERFORM_PTR_CONVERSION)
#define _jRHCB_DUMMY_INIT int
#else
#define _jRHCB_DUMMY_INIT DummyInit *
#endif


////////////////////////////// THE CODE //////////////////////////

//change these when your compiler gets bool
typedef bool	RHCB_BOOL;

#include <string.h> //for memstuff
#include <stddef.h> //for size_t

//typeless representation of a function and optional object

class _jFunctorBase {
public:
	//Note: ctors are protected
	
	//for evaluation in conditionals - can the jFunctor be called?
	operator RHCB_BOOL()const{return callee||func;}
	
	//Now you can put them in containers _and_ remove them!
	//Source for these 3 is in callback.cpp
	friend bool	operator==(const _jFunctorBase &lhs,const _jFunctorBase &rhs);
	friend bool	operator!=(const _jFunctorBase &lhs,const _jFunctorBase &rhs);
	friend bool	operator<(const _jFunctorBase &lhs,const _jFunctorBase &rhs);
	
	//The rest below for implementation use only !
	
	class DummyInit{
	};
	
	typedef void (_jFunctorBase::*PMemFunc)();
	typedef void (*PFunc)();
	enum {MEM_FUNC_SIZE = sizeof(PMemFunc)};
	
	PFunc	getFunc() const {return func;}
	void *getCallee() const {return callee;}
	const char *getMemFunc() const {return memFunc;}
	
	protected:
		////////////////////////////////////////////////////////////////
		// Note: this code depends on all ptr-to-mem-funcs being same size
		// If that is not the case then make memFunc as large as largest
		////////////////////////////////////////////////////////////////
	union{
		PFunc func;
		char memFunc[MEM_FUNC_SIZE*2]; // Make sure we support multiple inheritace.
	};
	void *callee;
		
	_jFunctorBase() : callee(0),func(0) {}
	_jFunctorBase(const void *c,PFunc f, const void *mf,size_t sz) : callee((void *)c)
	{
		if (c)	//must be callee/memfunc
		{
			memcpy(memFunc,mf,sz);
			if(sz<MEM_FUNC_SIZE)	//zero-out the rest, if any, so comparisons work
			{
				memset(memFunc+sz,0,MEM_FUNC_SIZE-sz);
			}
		}
		else	//must be ptr-to-func
		{
			func = f;
		}
	}
};


/************************* no arg - no return *******************/
class jFunctor0:public _jFunctorBase{
public:
	jFunctor0(_jRHCB_DUMMY_INIT = 0){}
	void operator()()const
		{
		thunk(*this);
		}
protected:
	typedef void (*Thunk)(const _jFunctorBase &);
	jFunctor0(Thunk t,const void *c,PFunc f,const void *mf,size_t sz):
		_jFunctorBase(c,f,mf,sz),thunk(t){}
private:
	Thunk thunk;
};

template <class Callee, class MemFunc>
class _jBMemberTranslator0:public jFunctor0{
public:
	_jBMemberTranslator0(Callee &c,const MemFunc &m):
		jFunctor0(thunk,&c,0,&m,sizeof(MemFunc)){}
	static void thunk(const _jFunctorBase &ftor)
		{
		Callee *callee = (Callee *)ftor.getCallee();
		MemFunc &memFunc _jRHCB_CTOR_STYLE_INIT
			(*(MemFunc*)(void *)(ftor.getMemFunc()));
		(callee->*memFunc)();
		}
};

template <class Func>
class _jBFunctionTranslator0:public jFunctor0{
public:
	_jBFunctionTranslator0(Func f):jFunctor0(thunk,0,(PFunc)f,0,0){}
	static void thunk(const _jFunctorBase &ftor)
		{
		(Func(ftor.getFunc()))();
		}
};

#if !defined(_jRHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class Callee,class RT,class CallType>
inline _jBMemberTranslator0<Callee,RT (CallType::*)()>
jFunctor( Callee &c,RT (CallType::* jRHCB_CONST_REF f)())
{
	typedef RT (CallType::*MemFunc)();
	return _jBMemberTranslator0<Callee,MemFunc>(c,f);
}
#endif

template <class Callee,class RT,class CallType>
inline _jBMemberTranslator0<const Callee,RT (CallType::*)()const>
jFunctor(const Callee &c,RT (CallType::* jRHCB_CONST_REF f)()const)
{
	typedef RT (CallType::*MemFunc)()const;
	return _jBMemberTranslator0<const Callee,MemFunc>(c,f);
}

template <class RT>
inline _jBFunctionTranslator0<RT (*)()>
jFunctor(RT (*f)())
{
	return _jBFunctionTranslator0<RT (*)()>(f);
}

/************************* no arg - with return *******************/
/*
template <class RT>
class Functor0wRet:public _jFunctorBase{
public:
	Functor0wRet(_jRHCB_DUMMY_INIT = 0){}
	RT operator()()const
		{
		return RHCB_BC4_RET_BUG(thunk(*this));
		}
protected:
	typedef RT (*Thunk)(const _jFunctorBase &);
	Functor0wRet(Thunk t,const void *c,PFunc f,const void *mf,size_t sz):
		_jFunctorBase(c,f,mf,sz),thunk(t){}
private:
	Thunk thunk;
};

template <class RT,class Callee, class MemFunc>
class CBMemberTranslator0wRet:public Functor0wRet<RT>{
public:
	CBMemberTranslator0wRet(Callee &c,const MemFunc &m):
			Functor0wRet<RT>(thunk,&c,0,&m,sizeof(MemFunc)){}
			static RT thunk(const _jFunctorBase &ftor)
			{
				Callee *callee = (Callee *)ftor.getCallee();
				MemFunc &memFunc _jRHCB_CTOR_STYLE_INIT
					(*(MemFunc*)(void *)(ftor.getMemFunc()));
				return RHCB_BC4_RET_BUG((callee->*memFunc)());
			}
};

template <class RT,class Func>
class CBFunctionTranslator0wRet:public Functor0wRet<RT>{
public:
	CBFunctionTranslator0wRet(Func f):Functor0wRet<RT>(thunk,0,(PFunc)f,0,0){}
	static RT thunk(const _jFunctorBase &ftor)
		{
		return (Func(ftor.getFunc()))();
		}
};

#if !defined(_jRHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class RT,class Callee,class CallType>
inline CBMemberTranslator0wRet<RT,Callee,RT (CallType::*)()>
jFunctor( Callee &c,RT (CallType::* jRHCB_CONST_REF f)())
{
	typedef RT (CallType::*MemFunc)();
	return CBMemberTranslator0wRet<RT,Callee,MemFunc>(c,f);
}
#endif

template <class RT,class Callee,class CallType>
inline CBMemberTranslator0wRet<RT,const Callee,RT (CallType::*)()const>
jFunctor( const Callee &c,RT (CallType::* jRHCB_CONST_REF f)()const)
{
	typedef RT (CallType::*MemFunc)()const;
	return CBMemberTranslator0wRet<RT,const Callee,MemFunc>(c,f);
}

template <class RT>
inline CBFunctionTranslator0wRet<RT,RT (*)()>
jFunctor( RT (*f)() )
{
	return CBFunctionTranslator0wRet<RT,RT (*)()>(f);
}

/************************* one arg - no return *******************/
template <class P1>
class jFunctor1:public _jFunctorBase {
public:
	jFunctor1(_jRHCB_DUMMY_INIT = 0){}
	void operator()(P1 p1)const
		{
		thunk(*this,p1);
		}
	//for STL
	typedef P1 argument_type;
	typedef void result_type;
protected:
	typedef void (*Thunk)(const _jFunctorBase &,P1);
	jFunctor1(Thunk t,const void *c,PFunc f,const void *mf,size_t sz):
		_jFunctorBase(c,f,mf,sz),thunk(t){}
private:
	Thunk thunk;
};

template <class P1,class Callee, class MemFunc>
class _jBMemberTranslator1:public jFunctor1<P1>{
public:
	_jBMemberTranslator1(Callee &c,const MemFunc &m):
			jFunctor1<P1>(thunk,&c,0,&m,sizeof(MemFunc)){}
			static void thunk(const _jFunctorBase &ftor,P1 p1)
			{
				Callee *callee = (Callee *)ftor.getCallee();
				MemFunc &memFunc _jRHCB_CTOR_STYLE_INIT
					(*(MemFunc*)(void *)(ftor.getMemFunc()));
				(callee->*memFunc)(p1);
			}
};

template <class P1,class Func>
class _jBFunctionTranslator1:public jFunctor1<P1>{
public:
	_jBFunctionTranslator1(Func f):jFunctor1<P1>(thunk,0,(PFunc)f,0,0){}
	static void thunk(const _jFunctorBase &ftor,P1 p1)
		{
		(Func(ftor.getFunc()))(p1);
		}
};

#if !defined(_jRHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class P1,class Callee,class CallType>
inline _jBMemberTranslator1<P1,Callee,void (CallType::*)(P1)>
jFunctor(Callee &c,void (CallType::* jRHCB_CONST_REF f)(P1))
{
	typedef void (CallType::*MemFunc)(P1);
	return _jBMemberTranslator1<P1,Callee,MemFunc>(c,f);
}
#endif

template <class Callee,class CallType,class P1,class RT>
inline _jBMemberTranslator1<P1,const Callee,RT (CallType::*)(P1)const>
jFunctor(const Callee &c,RT (CallType::* jRHCB_CONST_REF f)(P1)const)
{
	typedef RT (CallType::*MemFunc)(P1)const;
	return _jBMemberTranslator1<P1,const Callee,MemFunc>(c,f);
}

template <class RT,class P1>
inline _jBFunctionTranslator1<P1,RT (*)(P1)>
jFunctor( RT (*f)(P1) )
{
	return _jBFunctionTranslator1<P1,RT (*)(P1)>(f);
}

template <class P1,class MemFunc>
class _jBMemberOf1stArgTranslator1:public jFunctor1<P1>{
public:
	_jBMemberOf1stArgTranslator1(const MemFunc &m):
			jFunctor1<P1>(thunk,(void *)1,0,&m,sizeof(MemFunc)){}
			static void thunk(const _jFunctorBase &ftor,P1 p1)
			{
				MemFunc &memFunc _jRHCB_CTOR_STYLE_INIT
					(*(MemFunc*)(void *)(ftor.getMemFunc()));
				(p1.*memFunc)();
			}
};

#if !defined(_jRHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class RT,class P1,class CallType>
inline _jBMemberOf1stArgTranslator1<P1,RT (CallType::*)()>
jFunctor( RT (CallType::* jRHCB_CONST_REF f)())
{
	typedef RT (CallType::*MemFunc)();
	return _jBMemberOf1stArgTranslator1<P1,MemFunc>(f);
}
#endif

template <class RT,class P1,class CallType>
inline _jBMemberOf1stArgTranslator1<P1,RT (CallType::*)()const>
jFunctor( RT (CallType::* jRHCB_CONST_REF f)()const)
{
	typedef RT (CallType::*MemFunc)()const;
	return _jBMemberOf1stArgTranslator1<P1,MemFunc>(f);
}
/************************* one arg - with return *******************/
/*
template <class P1,class RT>
class Functor1wRet:public FunctorBase{
public:
	Functor1wRet(RHCB_DUMMY_INIT = 0){}
	RT operator()(P1 p1)const
		{
		return RHCB_BC4_RET_BUG(thunk(*this,p1));
		}
	//for STL
	typedef P1 argument_type;
	typedef RT result_type;
protected:
	typedef RT (*Thunk)(const FunctorBase &,P1);
	Functor1wRet(Thunk t,const void *c,PFunc f,const void *mf,size_t sz):
		FunctorBase(c,f,mf,sz),thunk(t){}
private:
	Thunk thunk;
};

template <class P1,class RT,class Callee, class MemFunc>
class CBMemberTranslator1wRet:public Functor1wRet<P1,RT>{
public:
	CBMemberTranslator1wRet(Callee &c,const MemFunc &m):
			Functor1wRet<P1,RT>(thunk,&c,0,&m,sizeof(MemFunc)){}
			static RT thunk(const FunctorBase &ftor,P1 p1)
			{
				Callee *callee = (Callee *)ftor.getCallee();
				MemFunc &memFunc RHCB_CTOR_STYLE_INIT
					(*(MemFunc*)(void *)(ftor.getMemFunc()));
				return RHCB_BC4_RET_BUG((callee->*memFunc)(p1));
			}
};

template <class P1,class RT,class Func>
class CBFunctionTranslator1wRet:public Functor1wRet<P1,RT>{
public:
	CBFunctionTranslator1wRet(Func f):
			Functor1wRet<P1,RT>(thunk,0,(PFunc)f,0,0){}
			static RT thunk(const FunctorBase &ftor,P1 p1)
			{
				return (Func(ftor.getFunc()))(p1);
			}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class Callee,class RT,class CallType,class P1>
inline CBMemberTranslator1wRet<P1,RT,Callee,RT (CallType::*)(P1)>
functor( Callee &c,RT (CallType::* RHCB_CONST_REF f)(P1))
{
	typedef RT (CallType::*MemFunc)(P1);
	return CBMemberTranslator1wRet<P1,RT,Callee,MemFunc>(c,f);
}
#endif

template <class Callee,class RT,class CallType,class P1>
inline CBMemberTranslator1wRet<P1,RT,const Callee,RT (CallType::*)(P1)const>
functor( const Callee &c,RT (CallType::* RHCB_CONST_REF f)(P1)const )
{
	typedef RT (CallType::*MemFunc)(P1)const;
	return CBMemberTranslator1wRet<P1,RT,const Callee,MemFunc>(c,f);
}

template <class RT,class P1>
inline CBFunctionTranslator1wRet<P1,RT,RT (*)(P1)>
functor( RT (*f)(P1) )
{
	return CBFunctionTranslator1wRet<P1,RT,RT (*)(P1)>(f);
}

template <class P1,class RT,class MemFunc>
class CBMemberOf1stArgTranslator1wRet:public Functor1wRet<P1,RT>{
public:
	CBMemberOf1stArgTranslator1wRet(const MemFunc &m):
			Functor1wRet<P1,RT>(thunk,(void *)1,0,&m,sizeof(MemFunc)){}
			static RT thunk(const FunctorBase &ftor,P1 p1)
			{
				MemFunc &memFunc RHCB_CTOR_STYLE_INIT
					(*(MemFunc*)(void *)(ftor.getMemFunc()));
				return RHCB_BC4_RET_BUG((p1.*memFunc)());
			}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class P1,class RT,class CallType>
inline CBMemberOf1stArgTranslator1wRet<P1,RT,RT (CallType::*)()>
functor( RT (CallType::* RHCB_CONST_REF f )())
{
	typedef RT (CallType::*MemFunc)();
	return CBMemberOf1stArgTranslator1wRet<P1,RT,MemFunc>(f);
}
#endif

template <class P1,class RT,class CallType>
inline CBMemberOf1stArgTranslator1wRet<P1,RT,RT (CallType::*)()const>
functor( RT (CallType::* RHCB_CONST_REF f)()const )
{
	typedef RT (CallType::*MemFunc)()const;
	return CBMemberOf1stArgTranslator1wRet<P1,RT,MemFunc>(f);
}

/************************* two args - no return *******************/
template <class P1,class P2>
class jFunctor2:public _jFunctorBase{
public:
	jFunctor2(_jRHCB_DUMMY_INIT = 0){}
	void operator()(P1 p1,P2 p2)const
		{
		thunk(*this,p1,p2);
		}
	//for STL
	typedef P1 first_argument_type;
	typedef P2 second_argument_type;
	typedef void result_type;
protected:
	typedef void (*Thunk)(const _jFunctorBase &,P1,P2);
	jFunctor2(Thunk t,const void *c,PFunc f,const void *mf,size_t sz):
		_jFunctorBase(c,f,mf,sz),thunk(t){}
private:
	Thunk thunk;
};

template <class P1,class P2,class Callee, class MemFunc>
class _jBMemberTranslator2:public jFunctor2<P1,P2>{
public:
	_jBMemberTranslator2(Callee &c,const MemFunc &m):
			jFunctor2<P1,P2>(thunk,&c,0,&m,sizeof(MemFunc)){}
			static void thunk(const _jFunctorBase &ftor,P1 p1,P2 p2)
			{
				Callee *callee = (Callee *)ftor.getCallee();
				MemFunc &memFunc _jRHCB_CTOR_STYLE_INIT
					(*(MemFunc*)(void *)(ftor.getMemFunc()));
				(callee->*memFunc)(p1,p2);
			}
};

template <class P1,class P2,class Func>
class _jBFunctionTranslator2:public jFunctor2<P1,P2>{
public:
	_jBFunctionTranslator2(Func f):jFunctor2<P1,P2>(thunk,0,(PFunc)f,0,0){}
	static void thunk(const _jFunctorBase &ftor,P1 p1,P2 p2)
		{
		(Func(ftor.getFunc()))(p1,p2);
		}
};

#if !defined(_jRHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class Callee,class RT,class CallType,class P1,class P2>
inline _jBMemberTranslator2<P1,P2,Callee,RT (CallType::*)(P1,P2)>
jFunctor( Callee &c,RT (CallType::* jRHCB_CONST_REF f)(P1,P2) )
{
	typedef RT (CallType::*MemFunc)(P1,P2);
	return _jBMemberTranslator2<P1,P2,Callee,MemFunc>(c,f);
}
#endif

template <class Callee,class RT,class CallType,class P1,class P2>
inline _jBMemberTranslator2<P1,P2,const Callee,
RT (CallType::*)(P1,P2)const>
jFunctor( const Callee &c,RT (CallType::* jRHCB_CONST_REF f)(P1,P2)const)
{
	typedef RT (CallType::*MemFunc)(P1,P2)const;
	return _jBMemberTranslator2<P1,P2,const Callee,MemFunc>(c,f);
}

template <class RT,class P1,class P2>
inline _jBFunctionTranslator2<P1,P2,RT (*)(P1,P2)>
jFunctor( RT (*f)(P1,P2))
{
	return _jBFunctionTranslator2<P1,P2,RT (*)(P1,P2)>(f);
}

template <class P1,class P2,class MemFunc>
class _jBMemberOf1stArgTranslator2:public jFunctor2<P1,P2>{
public:
	_jBMemberOf1stArgTranslator2(const MemFunc &m):
			jFunctor2<P1,P2>(thunk,(void *)1,0,&m,sizeof(MemFunc)){}
			static void thunk(const _jFunctorBase &ftor,P1 p1,P2 p2)
			{
				MemFunc &memFunc _jRHCB_CTOR_STYLE_INIT
					(*(MemFunc*)(void *)(ftor.getMemFunc()));
				(p1.*memFunc)(p2);
			}
};

#if !defined(_jRHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class P1,class P2,class RT,class CallType>
inline _jBMemberOf1stArgTranslator2<P1,P2,RT (CallType::*)(P1)>
jFunctor( RT (CallType::* jRHCB_CONST_REF f)(P1))
{
	typedef RT (CallType::*MemFunc)(P1);
	return _jBMemberOf1stArgTranslator2<P1,P2,MemFunc>(f);
}
#endif

template <class P1,class P2,class RT,class CallType>
inline _jBMemberOf1stArgTranslator2<P1,P2,RT (CallType::*)(P1)const>
jFunctor( RT (CallType::* jRHCB_CONST_REF f)(P1)const)
{
	typedef RT (CallType::*MemFunc)(P1)const;
	return _jBMemberOf1stArgTranslator2<P1,P2,MemFunc>(f);
}


/************************* two args - with return *******************/
/*
template <class P1,class P2,class RT>
class Functor2wRet:public FunctorBase{
public:
	Functor2wRet(RHCB_DUMMY_INIT = 0){}
	RT operator()(P1 p1,P2 p2)const
		{
		return RHCB_BC4_RET_BUG(thunk(*this,p1,p2));
		}
	//for STL
	typedef P1 first_argument_type;
	typedef P2 second_argument_type;
	typedef RT result_type;
protected:
	typedef RT (*Thunk)(const FunctorBase &,P1,P2);
	Functor2wRet(Thunk t,const void *c,PFunc f,const void *mf,size_t sz):
		FunctorBase(c,f,mf,sz),thunk(t){}
private:
	Thunk thunk;
};

template <class P1,class P2,class RT,class Callee, class MemFunc>
class CBMemberTranslator2wRet:public Functor2wRet<P1,P2,RT>{
public:
	CBMemberTranslator2wRet(Callee &c,const MemFunc &m):
			Functor2wRet<P1,P2,RT>(thunk,&c,0,&m,sizeof(MemFunc)){}
			static RT thunk(const FunctorBase &ftor,P1 p1,P2 p2)
			{
				Callee *callee = (Callee *)ftor.getCallee();
				MemFunc &memFunc RHCB_CTOR_STYLE_INIT
					(*(MemFunc*)(void *)(ftor.getMemFunc()));
				return RHCB_BC4_RET_BUG((callee->*memFunc)(p1,p2));
			}
};

template <class P1,class P2,class RT,class Func>
class CBFunctionTranslator2wRet:public Functor2wRet<P1,P2,RT>{
public:
	CBFunctionTranslator2wRet(Func f):
			Functor2wRet<P1,P2,RT>(thunk,0,(PFunc)f,0,0){}
			static RT thunk(const FunctorBase &ftor,P1 p1,P2 p2)
			{
				return (Func(ftor.getFunc()))(p1,p2);
			}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class Callee,class RT,class CallType,class P1,class P2>
inline CBMemberTranslator2wRet<P1,P2,RT,Callee,
RT (CallType::*)(P1,P2)>
functor( Callee &c,RT (CallType::* RHCB_CONST_REF f)(P1,P2))
{
	typedef RT (CallType::*MemFunc)(P1,P2);
	return CBMemberTranslator2wRet<P1,P2,RT,Callee,MemFunc>(c,f);
}
#endif

template <class Callee,class RT,class CallType,class P1,class P2>
inline CBMemberTranslator2wRet<P1,P2,RT,const Callee,
RT (CallType::*)(P1,P2)const>
functor( const Callee &c,RT (CallType::* RHCB_CONST_REF f)(P1,P2)const)
{
	typedef RT (CallType::*MemFunc)(P1,P2)const;
	return CBMemberTranslator2wRet<P1,P2,RT,const Callee,MemFunc>(c,f);
}

template <class RT,class P1,class P2>
inline CBFunctionTranslator2wRet<P1,P2,RT,RT (*)(P1,P2)>
functor( RT (*f)(P1,P2))
{
	return CBFunctionTranslator2wRet<P1,P2,RT,RT (*)(P1,P2)>(f);
}

template <class P1,class P2,class RT,class MemFunc>
class CBMemberOf1stArgTranslator2wRet:public Functor2wRet<P1,P2,RT>{
public:
	CBMemberOf1stArgTranslator2wRet(const MemFunc &m):
			Functor2wRet<P1,P2,RT>(thunk,(void *)1,0,&m,sizeof(MemFunc)){}
			static RT thunk(const FunctorBase &ftor,P1 p1,P2 p2)
			{
				MemFunc &memFunc RHCB_CTOR_STYLE_INIT
					(*(MemFunc*)(void *)(ftor.getMemFunc()));
				return RHCB_BC4_RET_BUG((p1.*memFunc)(p2));
			}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class P1,class P2,class RT,class CallType>
inline CBMemberOf1stArgTranslator2wRet<P1,P2,RT,RT (CallType::*)(P1)>
functor( RT (CallType::* RHCB_CONST_REF f)(P1))
{
	typedef RT (CallType::*MemFunc)(P1);
	return CBMemberOf1stArgTranslator2wRet<P1,P2,RT,MemFunc>(f);
}
#endif

template <class P1,class P2,class RT,class CallType>
inline CBMemberOf1stArgTranslator2wRet<P1,P2,RT,RT (CallType::*)(P1)const>
functor( RT (CallType::* RHCB_CONST_REF f)(P1)const)
{
	typedef RT (CallType::*MemFunc)(P1)const;
	return CBMemberOf1stArgTranslator2wRet<P1,P2,RT,MemFunc>(f);
}


/************************* three args - no return *******************/
template <class P1,class P2,class P3>
class jFunctor3:public _jFunctorBase{
public:
	jFunctor3(_jRHCB_DUMMY_INIT = 0){}
	void operator()(P1 p1,P2 p2,P3 p3)const
		{
		thunk(*this,p1,p2,p3);
		}
protected:
	typedef void (*Thunk)(const _jFunctorBase &,P1,P2,P3);
	jFunctor3(Thunk t,const void *c,PFunc f,const void *mf,size_t sz):
		_jFunctorBase(c,f,mf,sz),thunk(t){}
private:
	Thunk thunk;
};

template <class P1,class P2,class P3,class Callee, class MemFunc>
class _jBMemberTranslator3:public jFunctor3<P1,P2,P3>{
public:
	_jBMemberTranslator3(Callee &c,const MemFunc &m):
			jFunctor3<P1,P2,P3>(thunk,&c,0,&m,sizeof(MemFunc)){}
			static void thunk(const _jFunctorBase &ftor,P1 p1,P2 p2,P3 p3)
			{
				Callee *callee = (Callee *)ftor.getCallee();
				MemFunc &memFunc _jRHCB_CTOR_STYLE_INIT
					(*(MemFunc*)(void *)(ftor.getMemFunc()));
				(callee->*memFunc)(p1,p2,p3);
			}
};

template <class P1,class P2,class P3,class Func>
class _jBFunctionTranslator3:public jFunctor3<P1,P2,P3>{
public:
	_jBFunctionTranslator3(Func f):jFunctor3<P1,P2,P3>(thunk,0,(PFunc)f,0,0){}
	static void thunk(const _jFunctorBase &ftor,P1 p1,P2 p2,P3 p3)
		{
		(Func(ftor.getFunc()))(p1,p2,p3);
		}
};

#if !defined(_jRHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class Callee,class RT,class CallType,class P1,class P2,class P3>
inline _jBMemberTranslator3<P1,P2,P3,Callee,
RT (CallType::*)(P1,P2,P3)>
jFunctor( Callee &c,RT (CallType::* jRHCB_CONST_REF f)(P1,P2,P3))
{
	typedef RT (CallType::*MemFunc)(P1,P2,P3);
	return _jBMemberTranslator3<P1,P2,P3,Callee,MemFunc>(c,f);
}
#endif

template <class Callee,class RT,class CallType,class P1,class P2,class P3>
inline _jBMemberTranslator3<P1,P2,P3,const Callee,
RT (CallType::*)(P1,P2,P3)const>
jFunctor( const Callee &c,RT (CallType::* jRHCB_CONST_REF f)(P1,P2,P3)const)
{
	typedef RT (CallType::*MemFunc)(P1,P2,P3)const;
	return _jBMemberTranslator3<P1,P2,P3,const Callee,MemFunc>(c,f);
}

template <class RT,class P1,class P2,class P3>
inline _jBFunctionTranslator3<P1,P2,P3,RT (*)(P1,P2,P3)>
jFunctor( RT (*f)(P1,P2,P3))
{
	return _jBFunctionTranslator3<P1,P2,P3,RT (*)(P1,P2,P3)>(f);
}

template <class P1,class P2,class P3,class MemFunc>
class _jBMemberOf1stArgTranslator3:public jFunctor3<P1,P2,P3>{
public:
	_jBMemberOf1stArgTranslator3(const MemFunc &m):
			jFunctor3<P1,P2,P3>(thunk,(void *)1,0,&m,sizeof(MemFunc)){}
			static void thunk(const _jFunctorBase &ftor,P1 p1,P2 p2,P3 p3)
			{
				MemFunc &memFunc _jRHCB_CTOR_STYLE_INIT
					(*(MemFunc*)(void *)(ftor.getMemFunc()));
				(p1.*memFunc)(p2,p3);
			}
};

#if !defined(_jRHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class P1,class P2,class P3,class RT,class CallType>
inline _jBMemberOf1stArgTranslator3<P1,P2,P3,RT (CallType::*)(P1,P2)>
jFunctor( RT (CallType::* jRHCB_CONST_REF f)(P1,P2))
{
	typedef RT (CallType::*MemFunc)(P1,P2);
	return _jBMemberOf1stArgTranslator3<P1,P2,P3,MemFunc>(f);
}
#endif

template <class P1,class P2,class P3,class RT,class CallType>
inline _jBMemberOf1stArgTranslator3<P1,P2,P3,RT (CallType::*)(P1,P2)const>
jFunctor( RT (CallType::* jRHCB_CONST_REF f)(P1,P2)const)
{
	typedef RT (CallType::*MemFunc)(P1,P2)const;
	return _jBMemberOf1stArgTranslator3<P1,P2,P3,MemFunc>(f);
}


/************************* three args - with return *******************/
/*
template <class P1,class P2,class P3,class RT>
class Functor3wRet:public FunctorBase{
public:
	Functor3wRet(RHCB_DUMMY_INIT = 0){}
	RT operator()(P1 p1,P2 p2,P3 p3)const
		{
		return RHCB_BC4_RET_BUG(thunk(*this,p1,p2,p3));
		}
protected:
	typedef RT (*Thunk)(const FunctorBase &,P1,P2,P3);
	Functor3wRet(Thunk t,const void *c,PFunc f,const void *mf,size_t sz):
		FunctorBase(c,f,mf,sz),thunk(t){}
private:
	Thunk thunk;
};

template <class P1,class P2,class P3,
class RT,class Callee, class MemFunc>
class CBMemberTranslator3wRet:public Functor3wRet<P1,P2,P3,RT>{
public:
	CBMemberTranslator3wRet(Callee &c,const MemFunc &m):
			Functor3wRet<P1,P2,P3,RT>(thunk,&c,0,&m,sizeof(MemFunc)){}
			static RT thunk(const FunctorBase &ftor,P1 p1,P2 p2,P3 p3)
			{
				Callee *callee = (Callee *)ftor.getCallee();
				MemFunc &memFunc RHCB_CTOR_STYLE_INIT
					(*(MemFunc*)(void *)(ftor.getMemFunc()));
				return RHCB_BC4_RET_BUG((callee->*memFunc)(p1,p2,p3));
			}
};

template <class P1,class P2,class P3,class RT,class Func>
class CBFunctionTranslator3wRet:public Functor3wRet<P1,P2,P3,RT>{
public:
	CBFunctionTranslator3wRet(Func f):
			Functor3wRet<P1,P2,P3,RT>(thunk,0,(PFunc)f,0,0){}
			static RT thunk(const FunctorBase &ftor,P1 p1,P2 p2,P3 p3)
			{
				return (Func(ftor.getFunc()))(p1,p2,p3);
			}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class P1,class P2,class P3,class RT,class Callee,class CallType>
inline CBMemberTranslator3wRet<P1,P2,P3,RT,Callee,
RT (CallType::*)(P1,P2,P3)>
functor( Callee &c,RT (CallType::* RHCB_CONST_REF f)(P1,P2,P3))
{
	typedef RT (CallType::*MemFunc)(P1,P2,P3);
	return CBMemberTranslator3wRet<P1,P2,P3,RT,Callee,MemFunc>(c,f);
}
#endif

template <class Callee,class RT,class CallType,class P1,class P2,class P3>
inline CBMemberTranslator3wRet<P1,P2,P3,RT,const Callee,
RT (CallType::*)(P1,P2,P3)const>
functor( const Callee &c,RT (CallType::* RHCB_CONST_REF f)(P1,P2,P3)const)
{
	typedef RT (CallType::*MemFunc)(P1,P2,P3)const;
	return CBMemberTranslator3wRet<P1,P2,P3,RT,const Callee,MemFunc>(c,f);
}

template <class RT,class P1,class P2,class P3>
inline CBFunctionTranslator3wRet<P1,P2,P3,RT,RT (*)(P1,P2,P3)>
functor( RT (*f)(P1,P2,P3) )
{
	return CBFunctionTranslator3wRet<P1,P2,P3,RT,RT (*)(P1,P2,P3)>(f);
}

template <class P1,class P2,class P3,class RT,class MemFunc>
class CBMemberOf1stArgTranslator3wRet:public Functor3wRet<P1,P2,P3,RT>{
public:
	CBMemberOf1stArgTranslator3wRet(const MemFunc &m):
			Functor3wRet<P1,P2,P3,RT>(thunk,(void *)1,0,&m,sizeof(MemFunc)){}
			static RT thunk(const FunctorBase &ftor,P1 p1,P2 p2,P3 p3)
			{
				MemFunc &memFunc RHCB_CTOR_STYLE_INIT
					(*(MemFunc*)(void *)(ftor.getMemFunc()));
				return RHCB_BC4_RET_BUG((p1.*memFunc)(p2,p3));
			}
};

#if !defined(RHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class P1,class P2,class P3,class RT,class CallType>
inline CBMemberOf1stArgTranslator3wRet<P1,P2,P3,RT,RT (CallType::*)(P1,P2)>
functor( RT (CallType::* RHCB_CONST_REF f)(P1,P2))
{
	typedef RT (CallType::*MemFunc)(P1,P2);
	return CBMemberOf1stArgTranslator3wRet<P1,P2,P3,RT,MemFunc>(f);
}
#endif

template <class P1,class P2,class P3,class RT,class CallType>
inline CBMemberOf1stArgTranslator3wRet<P1,P2,P3,RT,
RT (CallType::*)(P1,P2)const>
functor( RT (CallType::* RHCB_CONST_REF f)(P1,P2)const)
{
	typedef RT (CallType::*MemFunc)(P1,P2)const;
	return CBMemberOf1stArgTranslator3wRet<P1,P2,P3,RT,MemFunc>(f);
}


/************************* four args - no return *******************/
template <class P1,class P2,class P3,class P4>
class jFunctor4:public _jFunctorBase{
public:
	jFunctor4(_jRHCB_DUMMY_INIT = 0){}
	void operator()(P1 p1,P2 p2,P3 p3,P4 p4)const
		{
		thunk(*this,p1,p2,p3,p4);
		}
protected:
	typedef void (*Thunk)(const _jFunctorBase &,P1,P2,P3,P4);
	jFunctor4(Thunk t,const void *c,PFunc f,const void *mf,size_t sz):
		_jFunctorBase(c,f,mf,sz),thunk(t){}
private:
	Thunk thunk;
};

template <class P1,class P2,class P3,class P4,
class Callee, class MemFunc>
class _jBMemberTranslator4:public jFunctor4<P1,P2,P3,P4>{
public:
	_jBMemberTranslator4(Callee &c,const MemFunc &m):
			jFunctor4<P1,P2,P3,P4>(thunk,&c,0,&m,sizeof(MemFunc)){}
			static void thunk(const _jFunctorBase &ftor,P1 p1,P2 p2,P3 p3,P4 p4)
			{
				Callee *callee = (Callee *)ftor.getCallee();
				MemFunc &memFunc _jRHCB_CTOR_STYLE_INIT
					(*(MemFunc*)(void *)(ftor.getMemFunc()));
				(callee->*memFunc)(p1,p2,p3,p4);
			}
};

template <class P1,class P2,class P3,class P4,class Func>
class _jBFunctionTranslator4:public jFunctor4<P1,P2,P3,P4>{
public:
	_jBFunctionTranslator4(Func f):
			jFunctor4<P1,P2,P3,P4>(thunk,0,(PFunc)f,0,0){}
			static void thunk(const _jFunctorBase &ftor,P1 p1,P2 p2,P3 p3,P4 p4)
			{
				(Func(ftor.getFunc()))(p1,p2,p3,p4);
			}
};

#if !defined(_jRHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class Callee,class RT,class CallType,class P1,class P2,class P3,class P4>
inline _jBMemberTranslator4<P1,P2,P3,P4,Callee,
RT (CallType::*)(P1,P2,P3,P4)>
jFunctor( Callee &c,RT (CallType::* jRHCB_CONST_REF f)(P1,P2,P3,P4))
{
	typedef RT (CallType::*MemFunc)(P1,P2,P3,P4);
	return _jBMemberTranslator4<P1,P2,P3,P4,Callee,MemFunc>(c,f);
}
#endif

template <class Callee,class RT,class CallType,class P1,class P2,class P3,class P4>
inline _jBMemberTranslator4<P1,P2,P3,P4,const Callee,
RT (CallType::*)(P1,P2,P3,P4)const>
jFunctor( const Callee &c,RT (CallType::* jRHCB_CONST_REF f)(P1,P2,P3,P4)const)
{
	typedef RT (CallType::*MemFunc)(P1,P2,P3,P4)const;
	return _jBMemberTranslator4<P1,P2,P3,P4,const Callee,MemFunc>(c,f);
}

template <class RT,class P1,class P2,class P3,class P4>
inline _jBFunctionTranslator4<P1,P2,P3,P4,RT (*)(P1,P2,P3,P4)>
jFunctor( RT (*f)(P1,P2,P3,P4))
{
	return _jBFunctionTranslator4<P1,P2,P3,P4,RT (*)(P1,P2,P3,P4)>(f);
}

template <class P1,class P2,class P3,class P4,class MemFunc>
class _jBMemberOf1stArgTranslator4:public jFunctor4<P1,P2,P3,P4>{
public:
	_jBMemberOf1stArgTranslator4(const MemFunc &m):
			jFunctor4<P1,P2,P3,P4>(thunk,(void *)1,0,&m,sizeof(MemFunc)){}
			static void thunk(const _jFunctorBase &ftor,P1 p1,P2 p2,P3 p3,P4 p4)
			{
				MemFunc &memFunc _jRHCB_CTOR_STYLE_INIT
					(*(MemFunc*)(void *)(ftor.getMemFunc()));
				(p1.*memFunc)(p2,p3,p4);
			}
};

#if !defined(_jRHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class P1,class P2,class P3,class P4,class RT,class CallType>
inline _jBMemberOf1stArgTranslator4<P1,P2,P3,P4,RT (CallType::*)(P1,P2,P3)>
jFunctor( RT (CallType::* jRHCB_CONST_REF f)(P1,P2,P3))
{
	typedef RT (CallType::*MemFunc)(P1,P2,P3);
	return _jBMemberOf1stArgTranslator4<P1,P2,P3,P4,MemFunc>(f);
}
#endif

template <class P1,class P2,class P3,class P4,class RT,class CallType>
inline _jBMemberOf1stArgTranslator4<P1,P2,P3,P4,
RT (CallType::*)(P1,P2,P3)const>
jFunctor( RT (CallType::* jRHCB_CONST_REF f)(P1,P2,P3)const)
{
	typedef RT (CallType::*MemFunc)(P1,P2,P3)const;
	return _jBMemberOf1stArgTranslator4<P1,P2,P3,P4,MemFunc>(f);
}


/************************* four args - with return *******************/
/*
template <class P1,class P2,class P3,class P4,class RT>
class Functor4wRet:public _jFunctorBase{
public:
	Functor4wRet(_jRHCB_DUMMY_INIT = 0){}
	RT operator()(P1 p1,P2 p2,P3 p3,P4 p4)const
		{
		return RHCB_BC4_RET_BUG(thunk(*this,p1,p2,p3,p4));
		}
protected:
	typedef RT (*Thunk)(const _jFunctorBase &,P1,P2,P3,P4);
	Functor4wRet(Thunk t,const void *c,PFunc f,const void *mf,size_t sz):
		_jFunctorBase(c,f,mf,sz),thunk(t){}
private:
	Thunk thunk;
};

template <class P1,class P2,class P3,class P4,class RT,class Callee, class MemFunc>
class CBMemberTranslator4wRet:public Functor4wRet<P1,P2,P3,P4,RT>{
public:
	CBMemberTranslator4wRet(Callee &c,const MemFunc &m):
			Functor4wRet<P1,P2,P3,P4,RT>(thunk,&c,0,&m,sizeof(MemFunc)){}
			static RT thunk(const _jFunctorBase &ftor,P1 p1,P2 p2,P3 p3,P4 p4)
			{
				Callee *callee = (Callee *)ftor.getCallee();
				MemFunc &memFunc _jRHCB_CTOR_STYLE_INIT
					(*(MemFunc*)(void *)(ftor.getMemFunc()));
				return RHCB_BC4_RET_BUG((callee->*memFunc)(p1,p2,p3,p4));
			}
};

template <class P1,class P2,class P3,class P4,class RT,class Func>
class CBFunctionTranslator4wRet:public Functor4wRet<P1,P2,P3,P4,RT>{
public:
	CBFunctionTranslator4wRet(Func f):
			Functor4wRet<P1,P2,P3,P4,RT>(thunk,0,(PFunc)f,0,0){}
			static RT thunk(const _jFunctorBase &ftor,P1 p1,P2 p2,P3 p3,P4 p4)
			{
				return (Func(ftor.getFunc()))(p1,p2,p3,p4);
			}
};

#if !defined(_jRHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class P1,class P2,class P3,class P4,class RT,class Callee,class CallType>
inline CBMemberTranslator4wRet<P1,P2,P3,P4,RT,Callee,
RT (CallType::*)(P1,P2,P3,P4)>
jFunctor( Callee &c,RT (CallType::* jRHCB_CONST_REF f)(P1,P2,P3,P4))
{
	typedef RT (CallType::*MemFunc)(P1,P2,P3,P4);
	return CBMemberTranslator4wRet<P1,P2,P3,P4,RT,Callee,MemFunc>(c,f);
}
#endif

template <class Callee,class RT,class CallType,class P1,class P2,class P3,class P4>
inline CBMemberTranslator4wRet<P1,P2,P3,P4,RT,const Callee,
RT (CallType::*)(P1,P2,P3,P4)const>
jFunctor( const Callee &c,RT (CallType::* jRHCB_CONST_REF f)(P1,P2,P3,P4)const)
{
	typedef RT (CallType::*MemFunc)(P1,P2,P3,P4)const;
	return CBMemberTranslator4wRet<P1,P2,P3,P4,RT,const Callee,MemFunc>(c,f);
}

template <class RT,class P1,class P2,class P3,class P4>
inline CBFunctionTranslator4wRet<P1,P2,P3,P4,RT,RT (*)(P1,P2,P3,P4)>
jFunctor( RT (*f)(P1,P2,P3,P4) )
{
	return CBFunctionTranslator4wRet
		<P1,P2,P3,P4,RT,RT (*)(P1,P2,P3,P4)>(f);
}


template <class P1,class P2,class P3,class P4,class RT,class MemFunc>
class CBMemberOf1stArgTranslator4wRet:public Functor4wRet<P1,P2,P3,P4,RT>{
public:
	CBMemberOf1stArgTranslator4wRet(const MemFunc &m):
			Functor4wRet<P1,P2,P3,P4,RT>(thunk,(void *)1,0,&m,sizeof(MemFunc)){}
			static RT thunk(const _jFunctorBase &ftor,P1 p1,P2 p2,P3 p3,P4 p4)
			{
				MemFunc &memFunc _jRHCB_CTOR_STYLE_INIT
					(*(MemFunc*)(void *)(ftor.getMemFunc()));
				return RHCB_BC4_RET_BUG((p1.*memFunc)(p2,p3,p4));
			}
};

#if !defined(_jRHCB_CANT_OVERLOAD_ON_CONSTNESS)
template <class P1,class P2,class P3,class P4,class RT,class CallType>
inline CBMemberOf1stArgTranslator4wRet<P1,P2,P3,P4,RT,
RT (CallType::*)(P1,P2,P3)>
jFunctor( RT (CallType::* jRHCB_CONST_REF f)(P1,P2,P3))
{
	typedef RT (CallType::*MemFunc)(P1,P2,P3);
	return CBMemberOf1stArgTranslator4wRet<P1,P2,P3,P4,RT,MemFunc>(f);
}
#endif

template <class P1,class P2,class P3,class P4,class RT,class CallType>
inline CBMemberOf1stArgTranslator4wRet<P1,P2,P3,P4,RT,
RT (CallType::*)(P1,P2,P3)const>
jFunctor( RT (CallType::* jRHCB_CONST_REF f)(P1,P2,P3)const)
{
	typedef RT (CallType::*MemFunc)(P1,P2,P3)const;
	return CBMemberOf1stArgTranslator4wRet<P1,P2,P3,P4,RT,MemFunc>(f);
}
*/

///////////////////////////////////////////////////////////////////////////////
//
// Inlines.
//
///////////////////////////////////////////////////////////////////////////////
inline bool operator==(const _jFunctorBase &lhs,const _jFunctorBase &rhs)
{
	if (!lhs.callee)	{
		if (rhs.callee) return false;
		return lhs.func == rhs.func;
	}	else {
		if (!rhs.callee) return false;
		return lhs.callee == rhs.callee &&
			!memcmp(lhs.memFunc,rhs.memFunc,_jFunctorBase::MEM_FUNC_SIZE);
		}
}

inline bool operator!=(const _jFunctorBase &lhs,const _jFunctorBase &rhs)
{
	return !(lhs == rhs);
}

inline bool operator<(const _jFunctorBase &lhs,const _jFunctorBase &rhs)
{
	//must order across funcs and callee/memfuncs, funcs are first
	if(!lhs.callee)
		{
		if(rhs.callee)
			return true;
		else
			return lhs.func < rhs.func;
		}
	else
		{
		if(!rhs.callee)
			return false;
		if(lhs.callee != rhs.callee)
			return lhs.callee < rhs.callee;
		else
			return memcmp(lhs.memFunc,rhs.memFunc,_jFunctorBase::MEM_FUNC_SIZE)<0;
		}
}

//////////////////////////////////////////////////////////////////////////
template <class FUNCTOR>
class jFunctorsList
{
public:
	// Add jFunctor to list.
	void Add( const FUNCTOR &f )
	{
		m_functors.push_back( f );
	}
	// Remvoe jFunctor from list.
	void Remove( const FUNCTOR &f )
	{
		Container::iterator it = std::find( m_functors.begin(),m_functors.end(),f );
		if (it != m_functors.end())
		{
			m_functors.erase( it );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// Call all functors in this list.
	// Also several template functions for multiple parameters.
	//////////////////////////////////////////////////////////////////////////
	void Call()
	{
		for (Container::iterator it = m_functors.begin(); it != m_functors.end(); ++it)
		{
			(*it)();
		}
	}

	template <class T1>
	void Call( const T1 &param1 )
	{
		for (Container::iterator it = m_functors.begin(); it != m_functors.end(); ++it)
		{
			(*it)( param1 );
		}
	}

	template <class T1,class T2>
	void Call( const T1 &param1,const T2 &param2 )
	{
		for (Container::iterator it = m_functors.begin(); it != m_functors.end(); ++it)
		{
			(*it)( param1,param2 );
		}
	}

	template <class T1,class T2,class T3>
	void Call( const T1 &param1,const T2 &param2,const T3 &param3 )
	{
		for (Container::iterator it = m_functors.begin(); it != m_functors.end(); ++it)
		{
			(*it)( param1,param2,param3 );
		}
	}

private:
	typedef std::list<FUNCTOR> Container;
	Container m_functors;
};

	}//nHEADER

}//namespace nMech

#endif //__jFunctor_h__
