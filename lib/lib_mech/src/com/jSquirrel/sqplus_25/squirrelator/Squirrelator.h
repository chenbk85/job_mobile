/*
Copyright (c) 2003 Alberto Demichelis

This software is provided 'as-is', without any 
express or implied warranty. In no event will the 
authors be held liable for any damages arising from 
the use of this software.

Permission is granted to anyone to use this software 
for any purpose, including commercial applications, 
and to alter it and redistribute it freely, subject 
to the following restrictions:

		1. The origin of this software must not be 
		misrepresented; you must not claim that 
		you wrote the original software. If you 
		use this software in a product, an 
		acknowledgment in the product 
		documentation would be appreciated but is 
		not required.

		2. Altered source versions must be plainly 
		marked as such, and must not be 
		misrepresented as being the original 
		software.

		3. This notice may not be removed or 
		altered from any source distribution.

*/
#ifndef _SQUIRRELATOR_H_
#define _SQUIRRELATOR_H_

#include <squirrel.h>
#include <new.h>

template <typename T>
struct Squirrelator
{
	typedef int(T::*THIS_FUNC)(HSQUIRRELVM);

	struct SquirrelatorFunc{
		const THIS_FUNC func;
		const SQChar *name;
	};

	static int Thunk(HSQUIRRELVM v)
	{
		T* _this;
		THIS_FUNC func;
		sq_getuserdata(v,1,(SQUserPointer *)&_this,NULL);
		sq_getuserpointer(v,-1,(SQUserPointer *)&func);
		return (_this->*func)(v);
	}
	static void Register(HSQUIRRELVM v,const SQChar *contructor_name)
	{
		sq_pushstring(v,contructor_name,-1);
		sq_newtable(v);
		int i=0;
		while(T::FuncMap[i].name!=NULL){
			sq_pushstring(v,T::FuncMap[i].name,-1);
			sq_pushuserpointer(v,*((SQUserPointer *)&T::FuncMap[i].func));
			sq_newclosure(v,Thunk,1);
			sq_rawset(v,-3);
			i++;
		}
		sq_newclosure(v,Construct,1);
		sq_rawset(v,-3);
	}
	static int Construct(HSQUIRRELVM v)
	{
		Squirrelator<T>* obj=(Squirrelator<T>*)sq_newuserdata(v,sizeof(T));
		new(obj) T;
		sq_push(v,-2);
		sq_setdelegate(v,-2);
		sq_setreleasehook(v,-1,_ReleaseFunc);
		return 1;
	}
	static int _ReleaseFunc(SQUserPointer p,int size)
	{
		((T*)p)->~T();
		return 0;
	}
};

#define DECLARE_SCRIPTABLE(classname) static const Squirrelator<classname>::SquirrelatorFunc FuncMap[];
#define BEGIN_FUNCTIONS_MAP(classname) const Squirrelator<classname>::SquirrelatorFunc classname::FuncMap[]={ 

#define FUNCTION_ENTRY(calssname,name) {&calssname::name,#name}, 

#define END_FUNCTIONS_MAP() \
	{NULL,NULL} \
	}; 

#endif _SQUIRRELATOR_H_