/* file : jIConsoleCmd.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-03-04 14:00:54
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __jIConsoleCmd_headasdfs9889der__
#define __jIConsoleCmd_headasdfs9889der__
#pragma once

namespace nMech
{
	namespace nCONSOLE
	{


		// arg[0]은 명령 자체가 아니라 명령다음의 첫번째 인자이다.
		#define jCONSOLE_CMD_ARG const std::vector<std::tstring>& arg
		//#define __boost_jCONSOLE_CMD_ARG boost::function<bool (std::vector<std::tstring>&)>
		typedef bool jConsole_Command_func_t(jCONSOLE_CMD_ARG);
		#define jCONSOLE_CMD(X) bool X(jCONSOLE_CMD_ARG)
		
	
		/*주의 : 아래 매크로에서 arg_help에는 인자의 형식이 온다.
			<생략불가능한_인자>		[생략가능한_인자]


			참고1: 인자설명에 공백이 있으면 안된다.

					[생략가능한 인자]  : 틀린 문법이다.
			
			참고2: [생략가능한 인자]는 항상 마지막에 온다.
			
					tcstr arg_help = _T("<config_file> <run_mode> [option1]"); //옳은 문법
					tcstr arg_help = _T("<config_file> [option1] <run_mode>"); //틀린 문법



		*/
		#define jCC(category, cmd, flag,help,arg_help) \
			nMech::nCONSOLE::Get_jIConsoleCmd()->Regist(_T(#category),_T(#cmd),_jJOIN_3(category,_,cmd),flag,_T(help),_T(arg_help))
		#define jCC1(category, cmd, flag,help,arg_help) \
			nMech::nCONSOLE::Get_jIConsoleCmd()->Regist(category,_T(#cmd),_jJOIN_3(category,_,cmd),flag,_T(help),_T(arg_help))
		#define jCCQ(category, cmd, script,flag,help,arg_help) \
			nMech::nCONSOLE::Get_jIConsoleCmd()->Regist_SQ(_T(#category),_T(#cmd),script,flag,_T(help),_T(arg_help))

		#define jCONSOLE_CMD_AUTO(category,cmd,flag,help,arg_help)\
		extern bool _jJOIN_3(category,_,cmd)(jCONSOLE_CMD_ARG);\
				struct _jJOIN_3(category,_jCONSOLE_CMD_AUTO_CLASS_,cmd)\
				{ _jJOIN_3(category,_jCONSOLE_CMD_AUTO_CLASS_,cmd)(){jCC(category,cmd,flag,help,arg_help);} };\
				static _jJOIN_3(category,_jCONSOLE_CMD_AUTO_CLASS_,cmd) _jJOIN_3(category,_jCONSOLE_CMD_AUTO_IMPL_,cmd);\
				bool _jJOIN_3(category,_,cmd)(jCONSOLE_CMD_ARG)


		//--------------------------------------------------------------------------
#define for_each_EConsoleCommandType(X)\
		\
		X(eONLY_DEVELOPER , jBIT_0)\
		/* 개발자용 명령. 서비스릴리즈될때는 작동하지 않음.\

		*/\
		\
		X(eDONT_OVERLOAD, jBIT_1)\
		/*기존 명령을 중복하여 재정의 할수 없다. \

		*/\
		\
		X(eRUN_NEXT_UPDATE,jBIT_2)\
		/* 명령이 바로 호출되지 않고 메인 스레드의 다음 업데이트때 호출됨 \

		*/\

		enum EConsoleCommandType
		{
#define jGEN_ENUM_CMD(VAR,INIT) VAR = INIT,
			for_each_EConsoleCommandType(jGEN_ENUM_CMD)
		};

		typedef bool console_parser_t(tcstr);

		#define jINTERFACE_jIConsoleCmd(X) public:	\
		\
		/* <<<  Console Command 용 인터페이스	>>> \
		참고 :szCategory를 NULL로 세팅해도 됨 사용안해도 된다.*/\
		\
		virtual ::size_t GetSize() ##X \
		virtual void Regist(tcstr szCategory, tcstr szCommand,jConsole_Command_func_t*,int nFlag=0,tcstr szHelp=_T(""),tcstr szArgHelp=_T("")) ##X \
		\
		/* Squirrel 스크립트 등록 */\
		virtual void Regist_SQ(tcstr szCategory, tcstr szCommand,tcstr szScript,int nFlag=0,tcstr szHelp=_T(""),tcstr szArgHelp=_T("")) ##X\
		\
		virtual bool UnRegist(tcstr szCategory, tcstr szCommand) ##X\
		\
		/* szCategory생략 가능*/\
		virtual bool Run(tcstr szCategory, tcstr szCommand,tcstr szArg,bool stealth/*=false*/,tcstr szThread /*=0*/) ##X \
		\
		/* 첫번째 공백 이후의 스트링은 인자로 처리*/\
		virtual bool ParseCmd(tcstr szCommand_InputLine,float fTriggerTime=0.f) ##X \
		\
		virtual void Regist_ConsoleParser(tcstr key, console_parser_t* func)##X\
		virtual void UnRegist_ConsoleParser(tcstr key)##X\
		virtual tcstr AutoComplete( tcstr  substr ) ##X \
		virtual tcstr	AutoCompletePrev( tcstr  substr ) ##X \
		virtual tcstr ProcessCompletion( tcstr szInputBuffer ) ##X \
		virtual void ResetAutoCompletion()##X \
		\
		/* szCommandStringPart로 시작하는 명령 리스트를 outBuffer에 담아 준다.\
		편집 이라고 입력 하면 편집으로 시작하는 카테고리나 명령 리스트를 건네줌.\
		편집.삭제 라고 입력하면 카테고리이름이 편집이고 삭제라고 시작하는 명령리스트를 건네줌*/\
		virtual void GetCmdList(tcstr szCommandStringPart,std::vector<std::tstring>& outBuffer,bool checkCase=true) ##X \

		jINTERFACE_END(jIConsoleCmd);
		jSINGTON_INTERFACE_HEADER(JUTIL_API , jIConsoleCmd);

	}//namespace nCONSOLE
}

#define _jCONSOLE_VAL_int(VAL,TYPE,DEFAULT) TYPE VAL= arg.size()<=e_##VAL?DEFAULT:jt_atoi(arg[e_##VAL].c_str());
#define _jCONSOLE_VAL_int32(VAL,TYPE,DEFAULT) TYPE VAL= arg.size()<=e_##VAL?DEFAULT:jt_atoi(arg[e_##VAL].c_str());
#define _jCONSOLE_VAL_int64(VAL,TYPE,DEFAULT) TYPE VAL= arg.size()<=e_##VAL?DEFAULT:jt_atoi64(arg[e_##VAL].c_str());
#define _jCONSOLE_VAL_float(VAL,TYPE,DEFAULT) TYPE VAL= arg.size()<=e_##VAL?DEFAULT:jt_atof(arg[e_##VAL].c_str());
#define _jCONSOLE_VAL_bool(VAL,TYPE,DEFAULT) TYPE VAL= arg.size()<=e_##VAL?DEFAULT:(arg[e_##VAL]==jS(true)?true:false);
#define _jCONSOLE_VAL_acstr(VAL,TYPE,DEFAULT) nUNI::scb256_t _s_##VAL(arg.size()<=e_##VAL?DEFAULT:arg[e_##VAL]);  TYPE VAL= _s_##VAL.getA();
#define _jCONSOLE_VAL_wcstr(VAL,TYPE,DEFAULT) nUNI::scb256_t _s_##VAL(arg.size()<=e_##VAL?DEFAULT:jW(arg[e_##VAL]));  TYPE VAL= _s_##VAL.getW();
#define _jCONSOLE_VAL_cstr(VAL,TYPE,DEFAULT) TYPE VAL= arg.size()<=e_##VAL?DEFAULT:arg[e_##VAL].c_str();
#define _jCONSOLE_VAL_tcstr(VAL,TYPE,DEFAULT) TYPE VAL= arg.size()<=e_##VAL?DEFAULT:arg[e_##VAL].c_str();

#define _jCONSOLE_ENUM_(VAL,TYPE) e_##VAL,
#define _jCONSOLE_ENUM2_(VAL,TYPE,DEFAULT) e_##VAL,
#define _jCONSOLE_VAL_(VAL,TYPE) _jCONSOLE_VAL_##TYPE(VAL,TYPE,0)
#define _jCONSOLE_VAL2_(VAL,TYPE,DEFAULT) _jCONSOLE_VAL_##TYPE(VAL,TYPE,DEFAULT)
#define jCONSOLE_PARAM_END(LIST) enum{ jCONSOLE_PARAM_##LIST(_jCONSOLE_ENUM_,_jCONSOLE_ENUM2_) };\
								jCONSOLE_PARAM_##LIST(_jCONSOLE_VAL_,_jCONSOLE_VAL2_)

//	jCE(nation,EPlayerNationType);
#define jCCE(var,ENUM) ENUM e##var =eEND_##ENUM;e##var=FromString(var, e##var);jRETURN(e##var!=eEND_##ENUM);
#define jCCE_ret(ret,var,ENUM) ENUM e##var =eEND_##ENUM;e##var=FromString(var, e##var);jRETURN_ret(ret,e##var!=eEND_##ENUM);

/*

jCONSOLE_CMD_AUTO(room,create,0,"create game room","<szID> <gameKind> <maxUser> <channelType> [pwd]")
{
	// X()는 <생략불가능 param>
	// Y()는 [생략가능 param]에 대응된다.
	#define jCONSOLE_PARAM_create(X,Y) \
		X(szID,acstr) \
		X(gameKind,int) \
		X(maxUser,int) \
		X(channelType,tcstr) \
		Y(pwd,acstr,"") 
	jCONSOLE_PARAM_END(create);
}


jCONSOLE_CMD_AUTO(jSERVER_NAME,curr_dummy,0,"현제 더미지정","<szID>")
{
	#define jCONSOLE_PARAM_curr_dummy(X,Y) 	X(szID,acstr)
	jCONSOLE_PARAM_END(curr_dummy);
}
*/


#endif // __jIConsoleCmd_headasdfs9889der__
