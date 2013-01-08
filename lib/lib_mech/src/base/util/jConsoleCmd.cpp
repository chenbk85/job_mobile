/* file : jConsoleCmd.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-03-07 15:33:43
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jConsoleCmd.h"
#include "header/uString_stl.h"
#include "interface/Squirrel/jISquirrel.h"
#include "base/jSQ_bind.h"
#include "interface/jIOrb.h"
#include "base/jMsgManager.h"
#include <objbase.h>

namespace nMech
{
	namespace nCONSOLE
	{
		jID* g_pDocCmdList;

		jSINGTON_INTERFACE_DEFINE(JUTIL_API , jConsoleCmd, jIConsoleCmd)
		{
			//HRESULT hr = CoInitialize( NULL );

			g_pDocCmdList = GetjIXml()->CreateMemoryDoc(jS(jConsoleCmd));
		}

		jConsoleCmd::_jConsoleCmdData::_jConsoleCmdData(tcstr ca,tcstr co, boost_func_cmd_t& fn, int fg, tcstr h ,tcstr ah)
			:m_Func(fn), m_iFlag(fg)
		{
			m_iCallCnt=0;
			m_sCategory=ca;
			m_sCommand=co;
			m_szHelp=h;
			m_szArgHelp = ah;

			std::vector<std::tstring> out;
			nString::jSplit(m_szArgHelp, _T(" \t"), out);
			m_argCnt =0;
			m_argSkip = 0;
			for(size_t i=0; i< out.size() ; ++i)
			{
				if(out[i][0]=='<')
				{
					++m_argCnt;
				}
				if(out[i][0]=='[')
				{
					++m_argCnt;
					++m_argSkip;
				}
			}
		}
		void jConsoleCmd::_jConsoleCmdData::PrintHelp()
		{
			PrintArgHelp();
			jLOG(_T("\tHELP: %s"),m_szHelp);
		}
		void jConsoleCmd::_jConsoleCmdData::PrintArgHelp()
		{
			jLOG(_T("%s.%s %s"),m_sCategory,m_sCommand,m_szArgHelp);
		}
		void next_char(TCHAR* ch)
		{

			for(++ch;(*ch!=' ' || *ch!='\t');++ch)
			{
				if(*ch==0)
					return;
			}
		}
		bool jConsoleCmd::_jConsoleCmdData::checkArg(tcstr szArg,std::vector<std::tstring>& out)
		{
			if(!szArg)
			{
				if( (m_argCnt-m_argSkip) ==0) return true;
			}
			else
			{
				if(!jt_strchr(szArg,'\"'))
				{
					nString::jSplit(szArg, _T(" \t"), out);
				}
				else
				{
					tstring str1 = szArg;
					nSTL::trim(str1);
					tname1024_t buf;
					jt_strcpy(buf, str1.c_str());
					TCHAR* ch = buf;
					TCHAR* szA = ch;
					for(;ch&&*ch;++ch)
					{
						if(*ch=='\"')
						{
							++ch;
							szA = ch; 
							ch = jt_strchr(ch,'\"');
							if(!ch)  
								return false;
							*ch = 0;
							out.push_back(szA);
							next_char(ch);
							if(*ch=='\"')
								continue;
							if(*ch)
							{
								szA = ch;
								continue;
							}
							else
							{
								szA=0;
								break;
							}
						}
						else if(*ch==' ' || *ch=='\t')
						{
							*ch=0;
							out.push_back(szA);
							++ch;
							next_char(ch);
							if(*ch=='\"')
							{
								--ch;
								continue;
							}
							if(*ch)
							{
								szA = ch;
							}
							else
							{
								szA=0;
								break;
							}
						}
					}
					if(szA && *szA)
					{
						out.push_back(szA);
					}
				}
				if(out.size() <= (size_t)m_argCnt && out.size() >= ((size_t)m_argCnt-m_argSkip) ) return true;
			}

			PrintArgHelp();
			return false;
		}


		//--------------------------------------------------------------------------
		void jConsoleCmd::Regist(tcstr szCategory, tcstr szCommand,jConsole_Command_func_t* pFunc
			,int nFlag,tcstr szHelp,tcstr szArgHelp)
		//--------------------------------------------------------------------------
		{
			if(!szCategory) szCategory=_T("DEFAULT");
			if(m_CmdList[szCategory].count(szCommand))
			{
				jWARN(_T("중복등록 jConsoleCmd::RegistCommand(%s,%s)"), szCategory, szCommand);
				//return ;
			}
			cmd_pt pt = m_CmdList[szCategory].insert( 
				cmd_vt(szCommand,_jConsoleCmdData(szCategory,szCommand,boost_func_cmd_t(pFunc),nFlag,szHelp,szArgHelp) ) 
				);

			if(pt.second)
			{
				nXML::jE e = g_pDocCmdList->BaseI();
				_jConsoleCmdData& cmd= pt.first->second;
				e = e[cmd.m_sCategory][cmd.m_sCommand];
				e.AttrP(jS(m_szHelp)).T() = cmd.m_szHelp;
				e.AttrP(jS(m_szArgHelp)).T() = cmd.m_szArgHelp;
				e.AttrP(jS(m_argCnt)).T() = cmd.m_argCnt;
				e.AttrP(jS(m_argSkip)).T() = cmd.m_argSkip;
			}
		}

		//--------------------------------------------------------------------------
		void jConsoleCmd::Regist_SQ(tcstr szCategory, tcstr szCommand,tcstr szScript
			,int nFlag,tcstr szHelp,tcstr szArgHelp)
		//--------------------------------------------------------------------------
		{
			if(!szCategory) szCategory=_T("DEFAULT");
			if(m_CmdList[szCategory].count(szCommand))
			{
				jERROR(_T("중복등록 jConsoleCmd::Regist_SQ(%s,%s)"), szCategory, szCommand);
			}
			assert(0);
		}

		enum {e_szArg,e_m_CmdList_vt,e_szThread,eMAX};
		jSTATIC_FUNC_TAG void jConsoleCmd::JOB_jxRunCommand(nEVENT::jIMessage* pM)
		{
			tcstr szArg = pM->GetArg(e_szArg)->Get_cstr();
			jConsoleCmd::_jConsoleCmdData* pCCD = (jConsoleCmd::_jConsoleCmdData*)pM->GetArg(e_m_CmdList_vt)->GetUserData();
			tcstr szThread = pM->GetArg(e_szThread)->Get_cstr();

			std::vector<std::tstring> out;
			jLOG(_T("JOB_jxRunCommand: ~%s~%s.%s %s"),szThread,pCCD->m_sCategory,pCCD->m_sCommand,szArg);
			jRETURN(pCCD->checkArg(szArg,out));

			bool is =pCCD->m_Func(out);
			if(is)
			{
				++pCCD->m_iCallCnt;
			}
		}

		//--------------------------------------------------------------------------
		bool jConsoleCmd::Run(tcstr szCategory, tcstr szCommand,tcstr szArg,bool stealth, tcstr szThread)
		//--------------------------------------------------------------------------
		{
			//--------------------------------------------------------------------------
			struct _jxRunCommand
			//--------------------------------------------------------------------------
			{
				tcstr szCommand;
				tcstr szArg;
				tcstr szThread;

				_jxRunCommand(tcstr sz,tcstr a,tcstr t):szCommand(sz),szArg(a),szThread(t){}
				bool operator()(m_CmdList_vt& vt){ return operator()(vt.second);}
				bool operator()(cmd_t& cmd)
				{
					cmd_it it = cmd.find(szCommand);
					jRETURN_ret(false,it!=cmd.end());

					std::vector<std::tstring> out;
					jRETURN_ret(false,it->second.checkArg(szArg,out));

					if(szThread)
					{
						nEVENT::jIMsgManager* pMM = nEVENT::jIMsgManager::Get(szThread,true,true);
						jvRETURN_ret(false,pMM,_T("szThread=%s"),szThread);
						nEVENT::jIMessage* pM = pMM->Regist_Loop(0,jFUNC_Msg(JOB_jxRunCommand),eMAX,false);
						pM->GetArg(e_szArg).T() = szArg;
						pM->GetArg(e_m_CmdList_vt)->SetUserData(&it->second);
						pM->GetArg(e_szThread).T() = szThread;
						pM->DoWakeUp();
						return true;
					}

					bool is =it->second.m_Func(out);
					if(is)
					{
						++it->second.m_iCallCnt;
					}
					return is;
				}
			};//struct _jxRunCommand

			if(!stealth)
			{
				jLOG(_T("@> %s.%s %s"),szCategory, szCommand, szArg);
			}

			tname32_t szThreadName;
			if(szThread && szThread[0]!='_') //jIMsgManger의 스레드는 _로 시작해야 함.
			{
				jt_sprintf(szThreadName,_T("_%s"),szThread);
				szThread = szThreadName;
			}

			if(szCategory && jt_strlen(szCategory) )
			{
				m_CmdList_it itCategory = m_CmdList.find(szCategory);
				jRETURN_ret(false,itCategory!=m_CmdList.end() );
				_jxRunCommand a(szCommand,szArg,szThread);
				return a(itCategory->second);
			}

			m_CmdList_it it = jFIND_IF(m_CmdList , _jxRunCommand(szCommand,szArg,szThread)); // 명령이 있으면 찾아서 호출
			if(it==m_CmdList.end())return false;
			return true;
		}
		bool jConsoleCmd::ParseCmd_Now(tcstr szCommand_InputLine )
		{
			const bool checkCase=false;
			if(szCommand_InputLine[0]=='!')
				if(nCONSOLE::Get_jIConsoleVar()->ParseCmd(szCommand_InputLine)) return true;

			if(szCommand_InputLine[0]=='@')
			{
				if(_parse_ConsoleCmd(szCommand_InputLine,checkCase) ) return true;
			}
			else if(szCommand_InputLine[0]=='#')
			{
				if(_parse_Squirrel(szCommand_InputLine,checkCase) ) return true;
			}

			m_listParser_it it = m_listParser.begin(),ie=m_listParser.end();
			for(;it!=ie;++it)
			{
				if( it->second(szCommand_InputLine))
					return true;
			}
			return false;
		}

		enum {e_CONSOLECMD,e_JOB_ParseCmd_CMD,e_JOB_ParseCmd_MAX};
		jSTATIC_FUNC_TAG void JOB_ParseCmd(nEVENT::jIMessage* pM)
		{
			jConsoleCmd* pCC = (jConsoleCmd*)pM->GetArg(e_CONSOLECMD)->GetUserData();
			tcstr szArg = pM->GetArg(e_JOB_ParseCmd_CMD)->Get_cstr();
			jLOG(_T("JOB_ParseCmd : %s"),szArg);
			pCC->ParseCmd_Now(szArg);
		}

		bool jConsoleCmd::ParseCmd(tcstr szCommand_InputLine ,float fTriggerTime)
		{
			if(fTriggerTime==0)
			{
				return ParseCmd_Now(szCommand_InputLine);
			}
			nEVENT::jIMsgManager* pMM = nEVENT::jIMsgManager::Get(_T("jConsoleCmd"),true);//jINet의 네트웍 패킷  dispatch스레드를 사용.
			jRETURN_ret(false , pMM);
			nEVENT::jIMessage* pM = pMM->Regist_TimeBaseAndCount(0,jFUNC_Msg(JOB_ParseCmd),e_JOB_ParseCmd_MAX,fTriggerTime,1);
			jRETURN_ret(false, pM);
			pM->GetArg(e_CONSOLECMD)->SetUserData(this);
			pM->GetArg(e_JOB_ParseCmd_CMD).T() = szCommand_InputLine;
			pM->DoWakeUp();
			jLOG(jFUNC1 _T("scheduled(time=%f) : %s"),fTriggerTime , szCommand_InputLine);
			return true;
		}

		static tcstr get_thread_name(tcstr szCommand_InputLine,tstring &sThread,tcstr szDefaultThreadName)
		{
			if(szCommand_InputLine[0]=='~')
			{
				sThread = szDefaultThreadName;
				++szCommand_InputLine;
				tname32_t szBuf;
				jt_strncpy(szBuf,szCommand_InputLine,30);
				szBuf[31]=0;
				TCHAR* ch = jt_strchr(szBuf,'~');
				size_t iOffset = (ch-szBuf);
				if(ch && iOffset<16)//스레드 이름은 16자 이하만 지원.
				{
					*ch=0;
					sThread = szBuf;
					szCommand_InputLine+=(iOffset+1);
				}
			}
			return szCommand_InputLine;
		}
#if 1
		void JOB_parse_Squirrel(nEVENT::jIMessage* pM)
		{
			try
			{
				cstr szSQ= pM->GetArg(0)->Get_cstr();
				GetjISQ()->VM_RunScript(GetjISQ()->VM_CompileBuffer(szSQ));
			}
			jSQ_CATCH_ERROR();
		}

		bool jConsoleCmd::_parse_Squirrel(tcstr szCommand_InputLine , bool checkCase)
		{
			++szCommand_InputLine;
			tstring sThread= jS(_jISQ);
			szCommand_InputLine = get_thread_name(szCommand_InputLine,sThread,sThread.c_str());

			static nEVENT::jIMsgManager* pMM = nEVENT::jIMsgManager::Get(sThread.c_str(),true,true);
			jRETURN_ret(false,pMM);
			nEVENT::jIMessage* pM = pMM->Regist_Loop(0,jFUNC_Msg(JOB_parse_Squirrel),1);
			pM->GetArg(0).T() = szCommand_InputLine;
			pM->DoWakeUp();
			return true;
		}

#else
		void JOB_parse_Squirrel(nEVENT::jIMessage* pM)
		{
			try
			{
				SQObject _o;
				_o._type = (SQObjectType)pM->GetArg(0)->Get_int();
				_o._unVal.pUserPointer = pM->GetArg(1)->GetUserData();
				SquirrelObject obj(_o);
				GetjISQ()->VM_RunScript(obj);
			}
			jSQ_CATCH_ERROR();
		}
		
		bool jConsoleCmd::_parse_Squirrel(tcstr szCommand_InputLine , bool checkCase)
		{
			try
			{
				++szCommand_InputLine;
				SquirrelObject obj = GetjISQ()->VM_CompileBuffer(szCommand_InputLine);

				static nEVENT::jIMsgManager* pMM = nEVENT::jIMsgManager::Get(jS(_jISQ),true,true);
				jRETURN_ret(false,pMM);
				nEVENT::jIMessage* pM = pMM->Regist_Loop(0,jFUNC_Msg(JOB_parse_Squirrel),2);
				pM->GetArg(0).T() = (int)obj.GetObjectHandle()._type;
				pM->GetArg(1)->SetUserData(obj.GetObjectHandle()._unVal.pUserPointer);
				pM->DoWakeUp();

				return true;
			}
			jSQ_CATCH_ERROR();
			return false;

		}
#endif
		bool jConsoleCmd::_parse_ConsoleCmd(tcstr szCommand_InputLine , bool checkCase)
		{
			szCommand_InputLine = szCommand_InputLine+1;
			tstring sThread;
			szCommand_InputLine = get_thread_name(szCommand_InputLine,sThread,jS(_jConsoleCmd));
			
			std::vector<std::tstring> outHelp,outCate;
			nString::jSplit(szCommand_InputLine , _T(" ") , outHelp);
			if(std::tstring(_T("?")) == outHelp[0] || tstring(_T("help")) == outHelp[0] )
			{
				if(outHelp.size()==1)
				{
					jFOR_EACH(m_CmdList,_jxPrintCmd());
				}
				else
				{
					if(!jt_strchr(outHelp[1].c_str(), '.'))
					{
						jFOR_EACH(m_CmdList,_jxPrintCmd_arg(outHelp[1].c_str(),0));
					}
					else
					{
						if(outHelp[1][0]=='.')
						{
							jFOR_EACH(m_CmdList,_jxPrintCmd_arg(0, &outHelp[1][1] ));
						}
						else
						{
							nString::jSplit(outHelp[1], _T(".") , outCate);
							jFOR_EACH(m_CmdList,_jxPrintCmd_arg(outCate[0].c_str(), outCate[1].c_str() ) );
						}
					}
				}
				return false;
			}

			tstring arg = szCommand_InputLine;
			nSTL::trim(arg);
			tstring cmd = arg;
			if(!arg.size()) return false;

			// 명령과 인자를 분리
			const std::tstring& whitespaces=_T(" \t\r\n");
			size_t begin = arg.find_first_of(whitespaces);
			jASSERT0(begin!=0);
			if(begin == tstring::npos)
			{
				//한줄 전체가 명령어 이다.
				arg.clear();
			}
			else
			{
				cmd = arg.substr(0,begin);
				arg = arg.substr(begin+1,arg.size()-1);
				nSTL::trim_left(arg);
			}

			//명령과 카테고리 분리
			tcstr szCmd;
			tstring sCategory;
			begin = cmd.find_first_of('.');
			if(begin==tstring::npos)
			{
				assert(sCategory.size()==0);
				szCmd = cmd.c_str();
			}
			else
			{
				sCategory = cmd.substr(0, begin);
				szCmd = &cmd[begin+1];
			}

			return Run(sCategory.c_str() , szCmd, arg.c_str(),false,sThread.size()?sThread.c_str():0);
		}
		//--------------------------------------------------------------------------
		void jConsoleCmd::GetCmdList(tcstr szCommandStringPart,vector<std::tstring>& outBuffer,bool checkCase)
		//--------------------------------------------------------------------------
		{
			outBuffer.clear();
			if(!szCommandStringPart) return;
			size_t len = jt_strlen(szCommandStringPart);
			if(!len) return;

			strncmp_func_t *STRCMP = checkCase ? jt_strncmp : jt_strnicmp;

			std::vector<std::tstring> out;
			nString::jSplit(szCommandStringPart, _T(". ") , out );

			//									"test." 인 경우 out.size()==1 이므로
			if(out.size()!=2 || szCommandStringPart[len-2] == '.')
			{
				// 글자 그대로 검색하여 카테고리나 명령이름과 부분 일치하면 리스트를 만들어 리턴.
				jFOR_EACH(m_CmdList, _jxFind_command_part(std::tstring(szCommandStringPart ), outBuffer, STRCMP) );
				return ;
			}

			//카테고리부터 검색
			m_CmdList_it itCa = m_CmdList.begin(), ieCa = m_CmdList.end();
			for(; itCa != ieCa; ++itCa)
			{
				if(!STRCMP( itCa->first.c_str() , out[0].c_str() , out[0].size() ))
				{
					tstring category = itCa->first + _T(".");
					outBuffer.push_back(category);
				}

				jFOR_EACH(itCa->second, _jxFind_command_part(out[1], outBuffer,STRCMP) );
			}

		}

		//--------------------------------------------------------------------------
		bool jConsoleCmd::UnRegist(tcstr szCategory, tcstr szCommand)
		//--------------------------------------------------------------------------
		{
			jASSERT0(szCategory);

			m_CmdList_it itCategory = m_CmdList.find(szCategory);
			if(itCategory==m_CmdList.end()) return false;
			cmd_it it = itCategory->second.find(szCommand);
			if(it==itCategory->second.end()) return false;
			itCategory->second.erase(it);
			return true;
		}

		::size_t jConsoleCmd::GetSize()
		{
			::size_t count=0;
			jFOR_EACH(m_CmdList,_jxCountCmd(count) );
			return count;
		}
		
		void jConsoleCmd::Regist_ConsoleParser(tcstr key, console_parser_t *func)
		{
			if( m_listParser.count(key) )
				jWARN(_T("jConsoleCmd::Regist_ConsoleParser 중복등록 발생: %s"),key);
			m_listParser[key] = func;
		}
		void jConsoleCmd::UnRegist_ConsoleParser(tcstr key)
		{
			m_listParser_it it = m_listParser.find(key);
			if(it!=m_listParser.end()) m_listParser.erase(it);
			else 
				jWARN(_T("jConsoleCmd::UnRegist_ConsoleParser, not found : %s"),key);
		}

		void jConsoleCmd::ResetAutoCompletion()
		{
			m_matches.clear();
			m_iCurrTabCount = 0;
			m_sPrevTab = _T("");
		}

		tcstr jConsoleCmd::ProcessCompletion(tcstr szInputBuffer)
		{
			static jID* pD = GetjIXml()->GetObj(jS(jConsoleCmd));
			static tstring _s_szInput;
			_s_szInput = szInputBuffer;
			bool isCategoryMatch=false;

			if ( m_sPrevTab == szInputBuffer)
			{	
				if(m_matches.size())
				{
					if( m_iCurrTabCount >= m_matches.size() )
						m_iCurrTabCount=0;
					jIE* it = m_matches[m_iCurrTabCount];
					if(it->size())
					{
						m_sPrevTab = _s_szInput = it->GetTagName();
					}
					else
					{
						fname_t buf;
						tcstr szA = it->GetAttr(jS(m_szArgHelp));
						jt_sprintf(buf, _T("%s.%s "), it->GetParent()->GetTagName(),it->GetTagName(),szA);
						m_sPrevTab = _s_szInput = buf;
					}

						++m_iCurrTabCount;
					return _s_szInput.c_str();
				}
			}
			// 탭입력이 아니면 
			m_iCurrTabCount = 0;
			m_matches.clear();


			// 맨처음 @만 입력했을때.
			if(_s_szInput == _T(""))
			{
				isCategoryMatch=true;
				jIE* it = pD->BaseI()->begin();
				jrFOR(it)
				{
					m_matches.push_back(it);
					jLOG(_T("@$3%s"), it->GetTagName() );
				}
				m_iCurrTabCount=1;
				m_sPrevTab = _s_szInput = pD->BaseI()->begin()->GetTagName();
				return _s_szInput.c_str();
			}

			TCHAR* szMatchingCategory = &_s_szInput[0];
			TCHAR* szMatchingSubCmd = jt_strchr(&_s_szInput[0], '.');
			if(szMatchingSubCmd)
			{
				*szMatchingSubCmd = 0;
				++szMatchingSubCmd;
			}

			//--------------------------------------------------------------------------
			//매치 리스트 만들기
			//--------------------------------------------------------------------------
			if(!szMatchingSubCmd)
			{
				//category만 매치 하여 찾음.
				jIE* pE = pD->BaseI()->begin();
				jrFOR(pE)
				{
					if(!jt_strnicmp(pE->GetTagName() , szMatchingCategory ,jt_strlen(szMatchingCategory)) )
					{
						m_matches.push_back(pE);
						jLOG(_T("@$3%s"), pE->GetTagName() );
					}
				}
			}
			else
			{
				jIE* pE = pD->BaseI()->Find(szMatchingCategory);
				if(!pE)
					return _s_szInput.c_str();

				pE = pE->begin();
				jrFOR(pE)
				{
					if(!jt_strnicmp(pE->GetTagName() , szMatchingSubCmd ,jt_strlen(szMatchingSubCmd)) )
					{
						m_matches.push_back(pE);
						tcstr szA = pE->GetAttr(jS(m_szArgHelp));
						jLOG(_T("@$3%s.%s $5%s"), pE->GetParent()->GetTagName(),pE->GetTagName(),szA);
					}
				}
			}

			if(!m_matches.size()) 
				return _s_szInput.c_str();

			jIE* it = *m_matches.begin();
			fname_t buf;
			if(it->size())
			{
				jt_sprintf(buf, _T("%s"), it->GetTagName())	;
			}
			else
			{
				tcstr szA = it->GetAttr(jS(m_szArgHelp));
				jt_sprintf(buf, _T("%s.%s "), it->GetParent()->GetTagName(),it->GetTagName(),szA);
			}
			m_sPrevTab = _s_szInput = buf;
			m_iCurrTabCount=1;
			return _s_szInput.c_str();
		}

		tcstr jConsoleCmd::AutoComplete( tcstr  substr )
		{
			return 0;
		}
		tcstr	jConsoleCmd::AutoCompletePrev( tcstr  substr )
		{
			return 0;
		}


	}//nCONSOLE


}


using namespace nMech;
using namespace nMech::nCONSOLE;

jORB_HANDLER(ORB_ConsoleMonitor,CONSOLE_COMMAND_jIConsoleCmd)
{
	nCONSOLE::Get_jIConsoleCmd()->ParseCmd(m_peArg->Get_cstr());
}

jORB_HANDLER(ORB_ConsoleMonitor,CMD_COMPLETE_jIConsoleCmd)
{
	cstr szCmd = m_peArg->Get_cstr() + 1;
	jIE* pePacket = m_pOrb->FindProtocal(_T("CMD_COMPLETE_OK") );
	jIVar* pvNEW = m_peArg->GetAttrVar(jS(NEW));
	
	if(szCmd[-1]=='@')
	{
		jConsoleCmd* pCC = (jConsoleCmd*)Get_jIConsoleCmd();
		if(pvNEW->Get_bool())
			pCC->ResetAutoCompletion();

		tstring sz = tstring(_T("@")) + pCC->ProcessCompletion(szCmd);
		pePacket->Set_cstr(sz.c_str());
	}
	else
	{
		jWARN(_T("not support"));
		return ;
	}
	m_pOrb->Send(pePacket);

}
