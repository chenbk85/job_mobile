/* file : jDefine_enum.h
Coder : by icandoit ( mech12@nate.com)
Date : 2011-07-25 14:14:06
comp.: neobian.co.kr
title : 
desc : 

*/

#ifndef __jDefine_enum_header__
#define __jDefine_enum_header__
#pragma once


#define _ENUM_COMMON_FUNCTION_(ENUM)\
	inline ENUM FromHelpString(const tstring& str, ENUM e){ return FromHelpString(str.c_str(), e);}\
	inline ENUM FromString(const tstring& str, ENUM e){ return FromString(str.c_str(), e);}\
	inline tcstr ToStringFromHelpString(tcstr str,ENUM e){return ToString(FromHelpString(str,e) );}\
	inline tcstr ToHelpStringFromString(tcstr str,ENUM e){return ToHelpString(FromString(str,e) );}\
	inline tcstr ToStringFromHelpString(const tstring &str,ENUM e){return ToString(FromHelpString(str.c_str(),e) );}\
	inline tcstr ToHelpStringFromString(const tstring &str,ENUM e){return ToHelpString(FromString(str.c_str(),e) );}\
	inline bool IsValid(ENUM e){ cstr sz=ToString(e); return jt_strcmp(sz,jS(NULL) ); }\


#define _ENUM_ToHelpString(eVAR,iVal,help) if(eVAR==eInputVal) return _T(help);
#define _ENUM_ToString(eVAR,iVal,help) if(eVAR==eInputVal) return _T(#eVAR);
#define _ENUM_FromString(eVAR,iVal,help) if(jt_strcmp(str,_T(#eVAR))==0) return eVAR;
#define _ENUM_FromHelpString(eVAR,iVal,help) if(jt_strcmp(str,_T(help))==0) return eVAR;
#define _ENUM_field_declare(eVAR,iVal,help)	eVAR=iVal,

// FUNC(eVAR,iVal,"help")
#define jDEFINE_ENUM_CODE(ENUM) enum ENUM{ for_each_##ENUM(_ENUM_field_declare)  ENUM##_MAX };\
	inline tcstr ToHelpString(ENUM eInputVal){for_each_##ENUM(_ENUM_ToHelpString); return _T("NULL");};\
	inline tcstr ToString(ENUM eInputVal){for_each_##ENUM(_ENUM_ToString); return _T("NULL");};\
	inline ENUM FromString(tcstr str, ENUM){ for_each_##ENUM(_ENUM_FromString); return ENUM##_MAX;}\
	inline ENUM FromHelpString(tcstr str, ENUM){ for_each_##ENUM(_ENUM_FromString); return ENUM##_MAX;}\
	_ENUM_COMMON_FUNCTION_(ENUM)\



#define _ENUM_ToHelpString2(eVAR,help) if(eVAR==eInputVal) return _T(help);
#define _ENUM_ToString2(eVAR,help) if(eVAR==eInputVal) return _T(#eVAR);
#define _ENUM_FromString2(eVAR,help) if(jt_strcmp(str,_T(#eVAR))==0) return eVAR;
#define _ENUM_FromHelpString2(eVAR,help) if(jt_strcmp(str,_T(help))==0) return eVAR;
#define _ENUM_field_declare2(eVAR,help)	eVAR,

// FUNC(eVAR,"help")
#define jDEFINE_ENUM_CODE2(ENUM) enum ENUM{ for_each_##ENUM(_ENUM_field_declare2)  ENUM##_MAX };\
	inline tcstr ToHelpString(ENUM eInputVal){for_each_##ENUM(_ENUM_ToHelpString2); return _T("NULL");};\
	inline tcstr ToString(ENUM eInputVal){for_each_##ENUM(_ENUM_ToString2); return _T("NULL");};\
	inline ENUM FromString(tcstr str, ENUM){ for_each_##ENUM(_ENUM_FromString2); return ENUM##_MAX;}\
	inline ENUM FromHelpString(tcstr str, ENUM){ for_each_##ENUM(_ENUM_FromHelpString2); return ENUM##_MAX;}\
	_ENUM_COMMON_FUNCTION_(ENUM)\


#define _ENUM_ToHelpString3(eVAR,help,VALUE3) if(eVAR==eInputVal) return _T(help);
#define _ENUM_ToString3(eVAR,help,VALUE3) if(eVAR==eInputVal) return _T(#eVAR);
#define _ENUM_FromString3(eVAR,help,VALUE3) if(jt_strcmp(str,_T(#eVAR))==0) return eVAR;
#define _ENUM_FromHelpString3(eVAR,help,VALUE3) if(jt_strcmp(str,_T(help))==0) return eVAR;
#define _ENUM_field_declare3(eVAR,help,VALUE3)	eVAR,

// FUNC(eVAR,"help",VALUE3)
#define jDEFINE_ENUM_CODE3(ENUM) enum ENUM{ for_each_##ENUM(_ENUM_field_declare3)  ENUM##_MAX };\
	inline tcstr ToHelpString(ENUM eInputVal){for_each_##ENUM(_ENUM_ToHelpString3); return _T("NULL");};\
	inline tcstr ToString(ENUM eInputVal){for_each_##ENUM(_ENUM_ToString3); return _T("NULL");};\
	inline ENUM FromHelpString(tcstr str, ENUM){ for_each_##ENUM(_ENUM_FromHelpString3); return ENUM##_MAX;}\
	inline ENUM FromString(tcstr str, ENUM){ for_each_##ENUM(_ENUM_FromString3); return ENUM##_MAX;}\
	_ENUM_COMMON_FUNCTION_(ENUM)\


#define _ENUM_ToHelpString4(eVAR,help,VALUE3,VALUE4) if(eVAR==eInputVal) return _T(#eVAR) _T(":") _T(help);
#define _ENUM_ToString4(eVAR,help,VALUE3,VALUE4) if(eVAR==eInputVal) return _T(#eVAR);
#define _ENUM_FromString4(eVAR,help,VALUE3,VALUE4) if(jt_strcmp(str,_T(#eVAR))==0) return eVAR;
#define _ENUM_FromHelpString4(eVAR,help,VALUE3,VALUE4) if(jt_strcmp(str,_T(help))==0) return eVAR;
#define _ENUM_field_declare4(eVAR,help,VALUE3,VALUE4)	eVAR,

// FUNC(eVAR,"help",VALUE3,VALUE4)
#define jDEFINE_ENUM_CODE4(ENUM) enum ENUM{ for_each_##ENUM(_ENUM_field_declare4)  ENUM##_MAX };\
	inline tcstr ToHelpString(ENUM eInputVal){for_each_##ENUM(_ENUM_ToHelpString4); return _T("NULL");};\
	inline tcstr ToString(ENUM eInputVal){for_each_##ENUM(_ENUM_ToString4); return _T("NULL");};\
	inline ENUM FromHelpString(tcstr str, ENUM){ for_each_##ENUM(_ENUM_FromHelpString4); return ENUM##_MAX;}\
	inline ENUM FromString(tcstr str, ENUM){ for_each_##ENUM(_ENUM_FromString4); return ENUM##_MAX;}\
	_ENUM_COMMON_FUNCTION_(ENUM)\

/*
jDEFINE_ENUM_CODE ����.

enum EResult_Code{ ... } ���� 

#define for_each_EResult_Code(X)\
X(eOK				,0		," Ȯ�� �Ǿ����ϴ�.")\
X(eERROR			,10		,"Ȯ�κҰ�. �߸��� Ű�Դϴ�.")\
X(eSERVICE_ERROR	,-10	,"���� ����")\
X(eIP_ERROR			,-11	,"���� ���� ������ �ƴ�")\

jDEFINE_ENUM_CODE(EResult_Code);

#define for_each_EResult_Code2(X)\
X(eOK					," Ȯ�� �Ǿ����ϴ�.")\
X(eERROR				,"Ȯ�κҰ�. �߸��� Ű�Դϴ�.")\
X(eSERVICE_ERROR		,"���� ����")\
X(eIP_ERROR				,"���� ���� ������ �ƴ�")\

jDEFINE_ENUM_CODE2(EResult_Code2);



// FUNC(eVAR,help,VAL3,VAL4) �ð� ����
#define for_each_ETimerType(X)\
	X(eTIM12ER_WAITREADY	,"Ŭ���̾�Ʈ ���� ��ٸ�" ,5  ,5  )\
	X(eTIM12ER_START		,"��ŸƮ ��ٸ�"			,10 ,10 )\
	X(eTIM12ER_SELECTSUN	,"�� ����"				,10 ,10 )\
	X(eTIM12ER_ZERO		," "						,99 ,99 )\

jDEFINE_ENUM_CODE4(ETimerType);

��� ���� �ڵ� 

EResult_Code e = eSERVICE_ERROR;
assert( ToString(e) == string("eSERVICE_ERROR") );
assert( ToHelpString(e) == string("eSERVICE_ERROR:���� ����") );
assert( FromString("���� ����", EResult_Code_MAX) == e);

e= (EResult_Code) 1234;
assert( tstring(_T("NULL") ) == ToString(e) );



*/


#endif // __jDefine_enum_header__
