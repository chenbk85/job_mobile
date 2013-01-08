// jConsoleVar.cpp : DLL 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "interface/xml/jIXml.h"
#include "jConsoleVar.h"
#include "base/jXmlDictionary.h"
#include "interface/jIINI_File.h"
#include <boost/bind.hpp>
using namespace nMech;


#define find_leaf_by_noCase_CHECK_jMX_SKIP_THIS
#include "functor/find_leaf_by_noCase.h"

#include "interface/jIOrb.h"

namespace nMech
{
	namespace nCONSOLE
	{
		jIVar* pvSAVE_CONSOLE_VAR_XML=0;
		using namespace nMech::nXML;
		void iteration_ini_exe(cstr szName , jIVar* pV,jConsoleVar* pCV)
		{
			bool isExist=false;
			jE e = pCV->createElement(_T("exe") , szName, eFROM_DEFINED_INI /*| eDONT_SAVE2FILE */, _T("from ini file") ,isExist);
			//jASSERT0(!isExist && "iteration_ini_exe에서 ini변수초기화중 콘솔에 먼저 초기화된 값이 있음");
			pV->CopyTo ( e.Var());
		}
		jSINGTON_INTERFACE_DEFINE(JBASE_API , jConsoleVar, jIConsoleVar)
		{
			m_DocConsoleVar = GetjIXml()->CreateMemoryDoc(_T("jIConsoleVar") );
			//m_pConMsgManager = nEVENT::jIMsgManager::Get(_T("jIConsoleVar"),true);
		}
		//////////////////////////////////////////////////////////////////////////
		void jConsoleVar::Release()
		{
			
			if(pvSAVE_CONSOLE_VAR_XML && pvSAVE_CONSOLE_VAR_XML->Get_bool()&& !g_ExeEnv.m_is_dont_save_file)
				SaveToFile();

			if(m_DocConsoleVar.full())
				GetjIXml()->UnLoad(m_DocConsoleVar);
			m_DocConsoleVar.clear();
		}

		struct _jxDel_dont_save_var
		{
			jIE::EReturnType operator()(jIE* it)
			{
				if(!it->GetVar()->IsType(jIVar::ETelement)) return jIE::eCONTINUE;
				if(!it->size()) return jIE::eCONTINUE;
				if(it->begin()->GetVar()->IsType(jIVar::ETelement)) return jIE::eSKIP_CHILD;

				jIE* itC = it->begin();
				for(; itC ;  )
				{
					tcstr sz = itC->GetAttr(jS(FLAG));
					if(jt_strlen(sz))
					{
						if(jt_strstr(sz,jS(eDONT_SAVE2FILE)))
						{
							jIE* itTemp = itC->GetRight();
							itC->Erase();
							itC = itTemp;
						}
					}
					if(itC)
						itC=itC->GetRight();
				}
				return jIE::eSKIP_CHILD;
			}
		};

		void jConsoleVar::SaveToFile(cstr szFile)
		{
			//jMB("asdf","asdf");
			if(m_DocConsoleVar.empty())
			{
				jt_printf(jFUNC1 _T("safe fail. because m_DocConsoleVar.empty()! "));
				return;	
			}

			cstr szPath = g_ExeEnv.GetUserFilePath();
			jIVar* pvUSE_JXML = GetVar(_T("USE_JXML"), _T("exe"));
			fname_t userFile;

			jID* pDocTemp = GetjIXml()->CreateMemoryDoc(jS(__jConsoleVar__23__));
			m_DocConsoleVar->GetDoc()->CopyTo(pDocTemp);

			pDocTemp->BaseI()->for_each_if(_jxDel_dont_save_var());

			if(szFile)
			{
				if(pvUSE_JXML->Get_bool())
				{
					jt_sprintf(userFile,_T("%s.jxml"),szFile);
					pDocTemp->SaveAsXML(szFile);
				}
				else
				{
					jt_sprintf(userFile,_T("%s.xml"),szFile);
					pDocTemp->SaveAsJXML(szFile);
				}
			}
			else
			{
				g_ExeEnv.GetUserXmlFileName(userFile);
				jE docUser = GetjIXml()->Load(userFile);
				if(docUser.empty())
				{
					GetjIXml()->NewFile(userFile);
					docUser = GetjIXml()->Load(userFile);
				}
				nXML::jE ee = docUser[_T("jIConsoleVar")];
				pDocTemp->BaseI()->CopyTo_Child( ee );
				docUser->GetDoc()->Save();
			}
			GetjIXml()->UnLoad(pDocTemp);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*! Initialize the Console
		@param pSystem pointer to the System
		*/
		void jConsoleVar::Init(jID* pDocApp)
		{
			// file://z:\src\base\Interface\jIConsoleVar.txt

			//콘솔 변수 초기화 2단계 : "콘솔xml파일"
			jE doc = pDocApp;
			jVar v = doc(_T("jIConsoleVar"))->PersistAttr(_T("Original_FILE"),_T("xml\\jConsoleVar_default.xml") );
			if(v.empty()) return;

			jID* pDoc = GetjIXml()->Load( v->Get_cstr() );
			if( !pDoc) return;
			pDoc->BaseI()->for_each( _jxLoadCVar(this) );
			GetjIXml()->UnLoad(pDoc);

			//콘솔 변수 초기화 3단계 : APP.XML의 <jIConsoleVar>
			doc(_T("jIConsoleVar"))->for_each(_jxLoadCVar(this) );

			//콘솔 변수 초기화 4단계 : 실행파일닉네임_유저명.XML
			fname_t buf;
			g_ExeEnv.GetUserXmlFileName(buf);
			jE pD;

			pvSAVE_CONSOLE_VAR_XML = jCV(exe,SAVE_CONSOLE_VAR_XML,true,0
				,"true is mean what dont save xml\\user\\AppName_USER.xml");

			if(pvSAVE_CONSOLE_VAR_XML->Get_bool() && !g_ExeEnv.m_is_dont_save_file)
			{
				if( !nFileSystem::jFolder::Is_Exist(buf) )
				{
					GetjIXml()->NewFile(buf);
				}
				pD = GetjIXml()->Load(buf);
			}
			else
			{
				pD = GetjIXml()->CreateMemoryDoc(buf);
			}

			if(pD.empty())
			{
				jMB(_T("파일로딩(또는저장)실패"),buf);
				return;
			}
			pD[_T("jIConsoleVar")]->for_each(_jxLoadCVar(this) );

			// 콘솔 변수의 우선순위 :  실행인자 > ini세팅 > console var xml
			g_ExeEnv.Get_INI()->for_each_Section(_T("exe") , boost::bind(iteration_ini_exe,jBOOST__PLACEHODER_1 ,_2, this) );

		}

		/* szCategory=0이면 생략하면 <DEFAULT>카테고리가 지정됨*/
#define FUNC_CreateVar(TYPE)\
	jIVar* jConsoleVar::CreateVar(tcstr szCategory,tcstr sName,TYPE value,int nFlags, tcstr help  )\
		{\
		return createVar<TYPE>(szCategory,sName, value , nFlags, help);\
		}
		for_each_jIConsoleVar_type(FUNC_CreateVar);


		jIVar* jConsoleVar::GetVar( tcstr szCategory,tcstr name,bool noCase)
		{
			if(!m_DocConsoleVar.full()) return 0;
			jIE* pE;
			if(noCase)
			{
				using namespace nXML::nFunctor;
				pE = m_DocConsoleVar->find_if(find_leaf_by_noCase(name));
			}
			else
			{
				pE = (szCategory) ? m_DocConsoleVar(szCategory) : m_DocConsoleVar;
				if(pE)
					pE = pE->Find(name);
			}
			if(!pE) return 0;
			return pE->GetVar();
		}
		bool jConsoleVar::ParseCmd(tcstr szCmd)
		{
			if(szCmd[0]!='!') return false;
			szCmd = szCmd+1;

			vector<tstring> out ,out1;
			nString::jSplit(szCmd , _T(" \t") , out );
			if(!out.size()) return false;

			nString::jSplit(out[0], _T("."),out1);

			if(!out1.size()) return false;

			cstr szCate=0;
			cstr szVar =0;

			if(out1.size()==2)
			{
				szCate = out1[0].c_str();
				szVar = out1[1].c_str();
			}
			else
			{
				szCate = 0;
				szVar = out1[0].c_str();
			}

			jIVar* pV = Get_jIConsoleVar()->GetVar(szCate,szVar);
			if(!pV) 
			{
				jWARN(_T(" !%s not found"),szCmd);
				return false;
			}

			if(out.size()==2)
			{
				if(out[1][out[1].size()-1] == '\"')
					out[1][out[1].size()-1]=0;
				if(out[1][0]=='\"')
					out[1][0]=0;
					
				pV->FromString(out[1].c_str());
			}
			fname_t buf;
			jLOG(_T("%s = %s") , out[0].c_str() , pV->ToString(buf));
			return true;
		}

		tcstr	jConsoleVar::AutoComplete( tcstr substr ) 
		{
			assert(m_DocConsoleVar.full());

			return 0;
		}
		tcstr	jConsoleVar::AutoCompletePrev( tcstr substr ) 
		{
			assert(m_DocConsoleVar.full());
			return 0;

		}
		int jConsoleVar::GetFlag(jIE* var1)
		{
			jE var(var1);
			jIVar *pV =var.AttrP(_T("FLAG"));
			jASSERT0(pV);
			cstr sz = pV->Get_cstr();
			if( jt_strlen(sz) ==0) return 0;

			int iFlag =0;
#define CHECK_FLAG3(VAR, VAL) if(jt_strstr(sz,_T(#VAR) ))iFlag |=iFlag;
			for_each_EConsoleVarType(CHECK_FLAG3);
			return iFlag;
		}

		void jConsoleVar::SetFlag(jIE* var1, int iFlag)
		{
			jE var(var1);
			jVar pV =var.AttrP(_T("FLAG") );
			jASSERT0(pV.full());
			tstring str;

#define Set_FLAG34(VAR, VAL) if(VAR & iFlag ) { if(str.size()) str+=_T(" | "); str+=_T(#VAR);}
			for_each_EConsoleVarType(Set_FLAG34);
			pV.T() = str;
		}


		void jConsoleVar::ResetAutoCompletion()
		{
			m_matches.clear();
			m_iCurrTabCount = 0;
			m_sPrevTab = _T("");
		}

		tcstr jConsoleVar::ProcessCompletion(tcstr szInputBuffer)
		{
			jIE* peVarRoot = m_DocConsoleVar;
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
				jIE* it = peVarRoot->begin();
				jrFOR(it)
				{
					m_matches.push_back(it);
					jLOG(_T("!$4%s"), it->GetTagName() );
				}
				m_iCurrTabCount=1;
				m_sPrevTab = _s_szInput = peVarRoot->begin()->GetTagName();
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
				jIE* pE = peVarRoot->begin();
				jrFOR(pE)
				{
					if(!jt_strnicmp(pE->GetTagName() , szMatchingCategory ,jt_strlen(szMatchingCategory)) )
					{
						m_matches.push_back(pE);
						jLOG(_T("!$4%s"), pE->GetTagName() );
					}
				}
			}
			else
			{
				jIE* pE = peVarRoot->Find(szMatchingCategory);
				if(!pE)
					return _s_szInput.c_str();

				pE = pE->begin();
				jrFOR(pE)
				{
					if(!jt_strnicmp(pE->GetTagName() , szMatchingSubCmd ,jt_strlen(szMatchingSubCmd)) )
					{
						m_matches.push_back(pE);
						tcstr szA = pE->GetAttr(jS(m_szArgHelp));
						if(!szA)
						{
							szA =_T("");
						}
						tname256_t szBuf32;
						jLOG(_T("!$4%s.%s = $8%s $0[$5%s$0]"), pE->GetParent()->GetTagName(),pE->GetTagName(),pE->GetVar()->ToString(szBuf32),szA);
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
		
		}//tcstr jConsoleVar::ProcessCompletion(tcstr szInputBuffer)





		jORB_HANDLER(ORB_ConsoleMonitor,CMD_COMPLETE_jIConsoleVar)
		{
			cstr szCmd = m_peArg->Get_cstr() + 1;
			jIE* pePacket = m_pOrb->FindProtocal(_T("CMD_COMPLETE_OK") );
			jIVar* pvNEW = m_peArg->GetAttrVar(jS(NEW));

			if(szCmd[-1]=='!')
			{
				nCONSOLE::jConsoleVar* pCC = (nCONSOLE::jConsoleVar*)Get_jIConsoleVar();
				if(pvNEW->Get_bool())
					pCC->ResetAutoCompletion();

				tstring sz = tstring(_T("!")) + pCC->ProcessCompletion(szCmd);
				pePacket->Set_cstr(sz.c_str());
			}
			else
			{
				return;
			}
			m_pOrb->Send(pePacket);

		}

		jORB_HANDLER(ORB_ConsoleMonitor,CONSOLE_COMMAND_jIConsoleVar)
		{
			cstr szCmd = m_peArg->Get_cstr();
			Get_jIConsoleVar()->ParseCmd(szCmd);
		}

	}//namespace nCONSOLE
}

