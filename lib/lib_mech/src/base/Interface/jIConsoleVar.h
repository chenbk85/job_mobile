/* file : jIConsoleVar.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-01-29 17:59:46
comp.: www.actoz.com
title : 
desc : 

FILE:z:\server\src\core\jCommon\Interface\jIConsoleVar.txt

*/

#ifndef _jICONSOLE_VA232eioweuroiwdk2378R_H_
#define _jICONSOLE_VA232eioweuroiwdk2378R_H_


namespace nMech
{
	namespace nCONSOLE
	{

		//--------------------------------------------------------------------------
		//콘솔바에서 지원하는 자료형
#define for_each_jIConsoleVar_type(_ENUM)\
	_ENUM(int)\
	_ENUM(float)\
	_ENUM(tcstr)

		//--------------------------------------------------------------------------
#define for_each_EConsoleVarType(X)\
	\
	X(eDONT_SAVE2FILE , jBIT_0)\
	/* 콘솔XML로 콘솔변수 내용이 저장되지 않는다.\
		INI파일로 부터 로딩한 콘솔변수들은 이플레그를 사용하여 콘솔XML파일에 저장되지 않는다. */\
		\
		X(eCPP_ONLY_DEFINE, jBIT_1)\
		/*이 콘솔변수는 CPP모듈에서만 정의되며 초기값이 세팅됨. \
		콘솔XML에서 값을 수정해도 로딩시 값적용이 안됨.\
		콘솔XML에는 단지 값을 출력하기 위해 저장되는것임.*/\
		\
		X(eFROM_DEFINED_INI,jBIT_2)\
		/* ini파일로 부터 생성된 변수. 기본적으로 read only데이타이다.\
		변수의 값은 ini로 부터 값 적용을 받은후 최종적으로 실행파일 인자로 부터 적용됨*/\
		X(eRUNTIME_READ_ONLY,jBIT_2)\
		/* 런타임에서는 수정불가. INI, XML에서 로딩만 된다.*/\


		enum EConsoleVarType
		{
#define jGEN_ENUM12(VAR,INIT) VAR = INIT,
			for_each_EConsoleVarType(jGEN_ENUM12)
		};


		//처음 로딩시 콘솔 xml 파일에서 콘솔변수값을 로딩하지 않아야 하는지 체크.
		inline bool is_does_not_load_console_xml(int iFlag)
		{
			return ((iFlag & eFROM_DEFINED_INI) || (iFlag & eCPP_ONLY_DEFINE) || (iFlag & eDONT_SAVE2FILE) );
		}

		// 콘솔변수정보를 파일로 저장할때 해당 변수를 저장하지 않는지 체크
		inline bool is_save_to_console_xml(int iFlag)
		{
			return (iFlag & eDONT_SAVE2FILE);
		}


#define jINTERFACE_jIConsoleVar(X) public:	\
	virtual void Init(jID* pDocApp) ##X /* jMech_Init()에서 호출됨 */ \
	virtual void Release() ##X \
	/* Console변수를 담고있는 xml문서를 넘겨줌(jConsoleVar.xml) */\
	virtual jID *GetDoc() ##X \
	\
	/* szCategory=0이면 생략하면 <DEFAULT>카테고리가 지정됨, \
		nFlags는 EConsoleVarType 의 값이 올수 있다*/\
		virtual jIVar *CreateVar(tcstr szCategory,tcstr sName,tcstr sValue	,int nFlags, tcstr help = _T("") )##X \
		/*virtual jIVar *CreateVar(tcstr szCategory,tcstr sName,bool iValue		,int nFlags, tcstr help = _T(""))##X */\
		virtual jIVar *CreateVar(tcstr szCategory,tcstr sName,int iValue		,int nFlags, tcstr help = _T(""))##X \
		virtual jIVar *CreateVar(tcstr szCategory,tcstr sName,float fValue	,int nFlags, tcstr help = _T(""))##X \
		\
		/* noCase == true이면 대소문자 구분안하고 찾는다. */\
		virtual jIVar* GetVar( tcstr szCategory,tcstr name,bool noCase=false)##X \
		\
		/*! Execute a string in the console*/	\
		virtual bool ParseCmd(tcstr szCmd) ##X \
		virtual tcstr AutoComplete( tcstr  substr ) ##X \
		virtual tcstr	AutoCompletePrev( tcstr  substr ) ##X \
		virtual tcstr ProcessCompletion( tcstr szInputBuffer ) ##X \
		virtual void ResetAutoCompletion()##X \
		virtual int GetFlag(jIE* var)##X \
		virtual void SetFlag(jIE* var, int iFlag)##X \
		\
		/* 파일명을 지정하지않으면 xml\user\[app_nic_name]_[username].xml로 저장된다.\
		또한 szFile의 파일 확장자는 xml 또는 jxml로 자동으로 붙는다.\
		[exe][USE_JXML]의 값이 true이면 jxml로 저장됨
		*/\
		virtual void SaveToFile(cstr szFile=0) ##X \

		jINTERFACE_END(jIConsoleVar);
		jSINGTON_INTERFACE_HEADER(JBASE_API , jIConsoleVar);

	}//namespace nCONSOLE
}

#define jGV(category, name) nMech::nCONSOLE::Get_jIConsoleVar()->GetVar(_T(#category),_T(#name))
#define jCV(category, name, value, flag, help) \
	nMech::nCONSOLE::Get_jIConsoleVar()->CreateVar(_T(#category),_T(#name),value,flag,_T(help))
#define jCV1(category, name, value, flag, help) \
	nMech::nCONSOLE::Get_jIConsoleVar()->CreateVar(category,_T(#name),value,flag,_T(help))

#define jCV_DECLARE(cate,var, val, flag,help)	extern jIVar* pv_##var;
#define jCV_DEFINE(cate,var, val, flag,help)	jIVar* pv_##var  = jCV(cate,var, val,flag,help);

#endif //_jICONSOLE_VA232eioweuroiwdk2378R_H_
