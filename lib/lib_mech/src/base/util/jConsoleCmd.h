/* file : jConsoleCmd.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-03-07 15:33:41
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __jConsoleCmd_header__
#define __jConsoleCmd_header__
#pragma once

//#include "header/jBoost.h"
#include "interface/jIConsoleCmd.h"

namespace nMech
{
	namespace nCONSOLE
	{
#define __boost_jCONSOLE_CMD_ARG boost::function<bool (std::vector<std::tstring>&)>
		typedef __boost_jCONSOLE_CMD_ARG boost_func_cmd_t;
		//--------------------------------------------------------------------------
		class jConsoleCmd : public jIConsoleCmd
			//--------------------------------------------------------------------------
		{
		public:
			jSINGTON_INTERFACE_DECLEAR(JUTIL_API , jConsoleCmd,jIConsoleCmd);
			jINTERFACE_HEADER(jIConsoleCmd);

			bool ParseCmd_Now(tcstr szCommand_InputLine );

		private:
			typedef tstring CategoryString_t;
			typedef tstring CommandString_t;
			struct _jConsoleCmdData
			{
				tcstr m_sCategory;
				tcstr m_sCommand;
				tcstr m_szHelp;
				tcstr m_szArgHelp;// 인자 핼프 스트링. 예) <생략불가능한인자> [생략가능한인자]
				uint16 m_argCnt;//허용 인자 갯수
				uint16 m_argSkip; // 허용 인자중에서 생략가능한 인자 갯수
				int m_iFlag;
				boost_func_cmd_t m_Func;
				int m_iCallCnt;
				_jConsoleCmdData(tcstr ca,tcstr co, boost_func_cmd_t& fn, int fg, tcstr h ,tcstr ah);
				virtual void PrintHelp(); // 명령의 모든 설명출력( + 인자설명포함)
				virtual void PrintArgHelp();//명령의 인자 설명만 출력

				bool checkArg(tcstr szArg,std::vector<std::tstring>& out);

			};
			jLIST_TYPEDEF_map_typedef(CommandString_t, _jConsoleCmdData,cmd);
			jLIST_TYPEDEF_map(CategoryString_t, cmd_t, m_CmdList);

			static void JOB_jxRunCommand(nEVENT::jIMessage* pM);
			struct _jxCountCmd
			{
				size_t& count;
				_jxCountCmd(size_t&c):count(c){}
				void operator()(m_CmdList_vt& vt){count += vt.second.size();}
			};


			typedef int strncmp_func_t(tcstr string1,tcstr string2,::size_t count );

			//--------------------------------------------------------------------------
			struct _jxFind_command_part
				//--------------------------------------------------------------------------
			{
				tstring& sCmd;
				std::vector<std::tstring> &buff;
				strncmp_func_t* pFunc;
				_jxFind_command_part(std::tstring& s, vector<std::tstring>& b,strncmp_func_t* pF):sCmd(s) , buff(b),pFunc(pF){}

				void operator()(cmd_vt& vt)
				{
					if( !pFunc(vt.first.c_str() , sCmd.c_str(), sCmd.size()) )
					{
						buff.push_back(std::tstring(vt.second.m_sCategory) + _T(".") +vt.first);
					}
				}
				void operator()(m_CmdList_vt& vt)
				{
					if( !pFunc(vt.first.c_str() , sCmd.c_str(), sCmd.size()) )
					{
						buff.push_back(vt.first + _T("."));
					}
					jFOR_EACH(vt.second, *this);
				}
			};

			struct _jxPrintCmd
			{
				void operator()(m_CmdList_vt& vt){jFOR_EACH(vt.second, *this);}
				void operator()(cmd_vt& vt)
				{
					vt.second.PrintHelp();
				}
			};
			struct _jxPrintCmd_arg
			{
				tcstr szCate;
				tcstr szCmd;
				_jxPrintCmd_arg(tcstr c , tcstr cmd):szCate(c), szCmd(cmd){}
				void operator()(m_CmdList_vt& vt){jFOR_EACH(vt.second, *this);}
				void operator()(cmd_vt& vt)
				{
					_jConsoleCmdData& v = vt.second;
					if(!szCmd) // 커멘드가 NULL이면
					{
						if(!jt_strncmp(v.m_sCategory, szCate , jt_strlen(szCate) ))
							v.PrintHelp();
						return;
					}

					if(!szCate)//카테고리가 NULL이면
					{
						if(!jt_strncmp(v.m_sCommand, szCmd , jt_strlen(szCmd) ))
							v.PrintHelp();
						return;
					}
					if(!jt_strcmp(v.m_sCategory, szCate) )
						if(!jt_strncmp(v.m_sCommand, szCmd , jt_strlen(szCmd) ))
							v.PrintHelp();

					return;
				}
			};


		private:
			bool jConsoleCmd::_parse_ConsoleCmd(tcstr szCommand_InputLine , bool checkCase);
			bool jConsoleCmd::_parse_Squirrel(tcstr szCommand_InputLine , bool checkCase);
			jLIST_TYPEDEF_map(std::tstring,console_parser_t*,m_listParser);

		private: // ----------------------------------------------------------
			tstring													m_sPrevTab;
			int															m_iCurrTabCount;
			jLIST_TYPEDEF_vector(jIE*,m_matches);


		};//class jConsoleCmd


	}//namespace nCONSOLE
}


#endif // __jConsoleCmd_header__
