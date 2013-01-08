/* file : test_Vector3.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-21 14:59:12
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __test_Vector3_header__
#define __test_Vector3_header__
#pragma once

enum {SQ_ENUM_TEST=1234321};


#if 0 // It may be possible to make this method work in the future. If so, the DECLARE_INSTANCE_FUNCS() macro
// would not be needed. The issue is duplicate compiler matching for const SQChar * and Push():
// Push(const SQChar * &) and Push(const SQChar *) both match.
// The typeid() compiler function may not be portable to other compilers.
#include <typeinfo.h>
template<typename TYPE>
inline const SQChar * GetTypeName(const TYPE & n)            { return typeid(TYPE).name(); }
template<typename TYPE>
inline void Push(HSQUIRRELVM v,const TYPE & value)           { CreateCopyInstance(GetTypeName(value),value); }
template<typename TYPE>
inline bool	Match(TypeWrapper<TYPE &>,HSQUIRRELVM v,int idx) { return  GetInstance<TYPE>(v,idx) != NULL; }
template<typename TYPE>
inline TYPE & Get(TypeWrapper<TYPE &>,HSQUIRRELVM v,int idx) { return *GetInstance<TYPE>(v,idx); }
#endif


extern int g_vec_sid;
//--------------------------------------------------------------------------
struct Vector3 
	//--------------------------------------------------------------------------
{
	static float staticVar;
	float x,y,z;
	int ref;
	int id ;
	Vector3() 
	{
		x = 1.f;
		y = 2.f;
		z = 3.f;
		ref=1;
		id = g_vec_sid++;
		scprintf(_T("Vector(id=%d)\n"),id);
	}
	Vector3(float _x,float _y,float _z) : x(_x), y(_y), z(_z) 
	{
		ref=1;
		id= g_vec_sid++;
		scprintf(_T("Vector(id=%d , %5.2f,%5.2f,%5.2f)\n"),id,x,y,z);
	}
	~Vector3() 
	{
		ref--;
		scprintf(_T("~Vector(id=%d, ref=%d)\n"),id,ref);
		id=-1;
	}
	Vector3 Inc(Vector3 & v) 
	{
		scprintf(_T("Vector::Inc\n"));
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	} // Inc
	Vector3 operator+(Vector3 & v) 
	{
		scprintf(_T("Vector::operator +(id=%d, id=%d)\n"),this->id, v.id);
		return Vector3(x+v.x,y+v.y,z+v.z);
	}

	Vector3& operator = (const Vector3& v)
	{
		x=v.x;
		y=v.y;
		z=v.z;
		ref=1;
		scprintf(_T("Vector operator=(id=%d from id=%d)\n"),id, v.id);
		return *this;
	}


	void Print()
	{
		scprintf(_T("Print Vector3(id=%d), %f %f %f\n"),id,x,y,z);
	}
	static void Bind_Squirrel();
};
void test_SquirrelObject_SetGet_Vector3(void);



DECLARE_INSTANCE_TYPE(Vector3)

#endif // __test_Vector3_header__
