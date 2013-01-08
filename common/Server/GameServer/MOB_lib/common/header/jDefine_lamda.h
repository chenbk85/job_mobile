/* file : jDefine_lamda.h
Coder : by icandoit ( mech12@nate.com)
Date : 2011-07-25 14:15:07
comp.: neobian.co.kr
title : 
desc : 

*/

#ifndef __jDefine_lamda_header__
#define __jDefine_lamda_header__
#pragma once


// X는 일반적 파람정의를 의미하고	Z는 맨마지막 파람정의를 의미.
#define _jLAMDA_MEMBER_(TYPE,VAL) TYPE VAL;
#define _jLAMDA_ARG_X(TYPE ,VAL) TYPE _##VAL,
#define _jLAMDA_ARG_Z(TYPE ,VAL) TYPE _##VAL
#define _jLAMDA_SET_ARG_X(TYPE,VAL) VAL(_##VAL),
#define _jLAMDA_SET_ARG_Z(TYPE,VAL) VAL(_##VAL)

#define jLAMDA_begin(STRUCT)	struct STRUCT{jLAMDA_##STRUCT(_jLAMDA_MEMBER_,_jLAMDA_MEMBER_); \
	STRUCT(){};\
	STRUCT( jLAMDA_##STRUCT(_jLAMDA_ARG_X,_jLAMDA_ARG_Z)):\
	jLAMDA_##STRUCT(_jLAMDA_SET_ARG_X,_jLAMDA_SET_ARG_Z){}\


#define jLAMDA_begin2(STRUCT,BASE)	struct STRUCT: public BASE{jLAMDA_##STRUCT(_jLAMDA_MEMBER_,_jLAMDA_MEMBER_); \
	STRUCT( jLAMDA_##STRUCT(_jLAMDA_ARG_X,_jLAMDA_ARG_Z)):\
	jLAMDA_##STRUCT(_jLAMDA_SET_ARG_X,_jLAMDA_SET_ARG_Z){}\

/*
jLAMDA_jStr(X,Z) X(int,iVal) X(float,fVal) Z(cstr,sz)
jLAMDA_begin(jStr)
void func1(){}
void func2(){}
jLAMDA_end();
*/

#define jLAMDA_CTOR(STRUCT)	struct STRUCT{jLAMDA_##STRUCT(_jLAMDA_MEMBER_,_jLAMDA_MEMBER_); \
	STRUCT(){};\
	STRUCT( jLAMDA_##STRUCT(_jLAMDA_ARG_X,_jLAMDA_ARG_Z)):\
	jLAMDA_##STRUCT(_jLAMDA_SET_ARG_X,_jLAMDA_SET_ARG_Z)\

/*

// X(lamda환경변수들) , Z(lamdb환경변수의 마지막)
#define jLAMDA_jServerUserCountInfo(X,Z) \
X(serverid_t ,sid)\
Z(uint16,totClient)
jLAMDA_CTOR(jServerUserCountInfo)
{
}
jLAMDA_end();


*/

#define jLAMDA_for_each0(NAME,IT_TYPE) struct NAME{	void operator()(IT_TYPE it)
#define jLAMDA_for_each(STRUCT,IT)	struct STRUCT{jLAMDA_##STRUCT(_jLAMDA_MEMBER_,_jLAMDA_MEMBER_); \
	STRUCT( jLAMDA_##STRUCT(_jLAMDA_ARG_X,_jLAMDA_ARG_Z)):\
	jLAMDA_##STRUCT(_jLAMDA_SET_ARG_X,_jLAMDA_SET_ARG_Z){}\
	void operator()(IT it)

#define jLAMDA_find_if0(NAME,IT_TYPE) struct NAME{	bool operator()(IT_TYPE it)
#define jLAMDA_find_if(STRUCT,IT)	struct STRUCT{jLAMDA_##STRUCT(_jLAMDA_MEMBER_,_jLAMDA_MEMBER_); \
	STRUCT( jLAMDA_##STRUCT(_jLAMDA_ARG_X,_jLAMDA_ARG_Z)):\
	jLAMDA_##STRUCT(_jLAMDA_SET_ARG_X,_jLAMDA_SET_ARG_Z){}\
	bool operator()(IT it)


#define jLAMDA_end() };


/* 사용예

#define jLAMDA_asdf(X,Z) Z(vector<jServerInfo>&,servers)
jLAMDA_for_each(asdf,jAqServerNode*)
{
servers.push_back(it->m_info);
}
jLAMDA_end();

g_SG.for_each(asdf(servers));

*/


#endif // __jDefine_lamda_header__
