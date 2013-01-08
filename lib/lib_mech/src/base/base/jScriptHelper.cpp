/* file : jScriptHelper.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-16 14:12:49
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "interface/xml/jIXml.h"
#include "interface/jIScriptHelper.h"
#include "juExeEnv.h"

namespace nMech
{
	namespace Impl
	{
		void jScriptHelper_end()	{			Get_jIScriptHelper()->End();		}
		jIVar* save_registed_class_help =0;

		struct jScriptHelper : public jIScriptHelper
		{
			nXML::jE m_eDocHelp;
			nXML::jE m_eCurrEnum;
			nXML::jE m_eCurrClass;
			jScriptHelper()
			{
				m_eDocHelp = GetjIXml()->CreateMemoryDoc(jS(jIScriptHelper) );
				jBase::RegistNamedPointer(jS(jMech_Close),jS(jScriptHelper_end),jScriptHelper_end);
				save_registed_class_help = jCV(jISquirrel,save_registed_class_help,false,0,"make file for sq binding class info");
			}
			void	End()
			{
				if(!save_registed_class_help->Get_bool()) return;
				nFileSystem::jFolder dir;
				std::tstring sFile = std::tstring(_T("xml\\user\\")) + g_ExeEnv.m_szAppNic + _T("sq_bind_help") +g_ExeEnv.m_szUserName + _T(".xml");
				m_eDocHelp->GetDoc()->SaveAsXML(sFile.c_str());
			}

			jID* GetDoc(){ return m_eDocHelp->GetDoc();}

			void	BeginClass(tcstr szClass)
			{
				m_eCurrEnum.clear();
				jASSERT0(m_eCurrClass.empty());
				m_eCurrClass = m_eDocHelp[jS(Class)][szClass];
			}
			void	EndClass()
			{
				m_eCurrClass.clear();
				m_eCurrEnum.clear();
			}

			void  RegistFuncHelp(tcstr szFunc,tcstr szArg, tcstr szHelp , tcstr szOpt) 
			{
				jASSERT0(m_eCurrClass.full());
				nXML::jE e = m_eCurrClass[jS(Function)][szFunc];
				e.AttrP(jS(ARG)).T() = szArg;
				e.AttrP(jS(Option)).T() = szOpt;
				e.T() = szHelp;
			}

			void  RegistVarHelp(tcstr szVar,tcstr szHelp , tcstr szOpt) 
			{
				jASSERT0(m_eCurrClass.full());
				nXML::jE e = m_eCurrClass[jS(Variable)][szVar];
				e.AttrP(jS(Option)).T() = szOpt;
				e.T() = szHelp;
			}

			void	BeginEnum(tcstr szEnumName)
			{	
				jASSERT0(m_eCurrClass.full());
				jASSERT0(m_eCurrEnum.empty());
				m_eCurrEnum = m_eCurrClass[jS(Enum)][szEnumName];
			}

			void  RegistEnumHelp(tcstr szScope, tcstr szEnum, tcstr szHelp ) 
			{
				jASSERT0(m_eCurrEnum.full());
				jASSERT0(m_eCurrClass.full());
				if(m_eCurrEnum.Attr(jS(SCOPE)).empty())
					m_eCurrEnum.AttrP(jS(SCOPE)).T() = szScope;
				m_eCurrEnum[szEnum].T() = szHelp;
			}
			void	RegistEnumTable_ToEnumRoot(tcstr szScope, tcstr szHelp )
			{
				nXML::jE e = m_eDocHelp[jS(Enum)][szScope];
				e.AttrP(jS(HELP)) = szHelp;
			}
			void  RegistEnumField_ToEnumRoot(tcstr szScope, tcstr szEnum, int iVal,tcstr szHelp )
			{
				nXML::jE e = m_eDocHelp[jS(Enum)][szScope][szEnum];
				e.T() = szHelp;
				e.AttrP(jS(Value)).T() = iVal;
			}

			void	RegistGlobalVar(tcstr szCppVar, tcstr scriptVar)
			{
				m_eDocHelp[jS(GlobalVar)][scriptVar].T() = szCppVar;

			}

		};//struct jScriptHelper 

	}//namespace Impl

	JBASE_API jIScriptHelper* Get_jIScriptHelper() 
	{ 
		static Impl::jScriptHelper a;	return &a;	
	}

}

