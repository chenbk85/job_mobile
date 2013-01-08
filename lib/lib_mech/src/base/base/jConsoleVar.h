/* file : jConsoleVar.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-01-29 17:31:02
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef _jConsoleVar_heade23412389dsfjsar_
#define _jConsoleVar_heade23412389dsfjsar_

#include "header/jSington.h"
#include "header/jInterface.h"

#include "interface/xml/jIXml.h"

#include "base/jMsgManager.h"

//forward declaration
namespace nMech
{
	namespace nCONSOLE
	{
		using namespace nXML;
		//--------------------------------------------------------------------------
		class jConsoleVar : public jIConsoleVar
		//--------------------------------------------------------------------------
		{
			jSINGTON_INTERFACE_DECLEAR(JBASE_API , jConsoleVar,jIConsoleVar);
			jINTERFACE_HEADER(jIConsoleVar);

		public:

			jE					m_DocConsoleVar;
			nEVENT::jIMsgManager* m_pConMsgManager;
			jIVar* m_pvSaveToFile;

			jE createElement(tcstr szCategory,tcstr sName, int nFlags, tcstr help ,bool& outIsExist )
			{
				assert(m_DocConsoleVar.full());	
				if(!szCategory) 
					szCategory=_T("DEFAULT") ;

				outIsExist = m_DocConsoleVar(szCategory)(sName).full();
				jE e = m_DocConsoleVar[szCategory][sName];
				
				if(!outIsExist || (nFlags & eCPP_ONLY_DEFINE)) // cpp모듈에서 정의 되는것이면 무조건 덥어 쒸운다.
				{
					SetFlag(e, nFlags);

					jVar vHelp;
					vHelp = e.Attr(_T("HELP") );
					if(vHelp.empty())
					{
						vHelp = e.AttrP(_T("HELP") );
						vHelp.T()= _T("");
					}

					if( jt_strlen(vHelp->Get_cstr()) < 1)
					{
						vHelp->InitValue(help);
					}
					else if(vHelp->IsContents(help))
					{

					}
					else
					{
#if 0
						tstring sHelp = vHelp->Get_cstr();
						sHelp+= _T(" \n[CODE HELP] ");
						sHelp += help;
						vHelp.T() = sHelp;
#endif
					}
				}
				return e;
			}

			template<typename T>
			jVar createVar(tcstr szCategory,tcstr sName, T value	,int nFlags, tcstr help  )
			{
				bool outIsExist= false;
				jE e = createElement(szCategory , sName, nFlags, help,outIsExist);

				// 기존에 존제하지않거나 eCPP_ONLY_DEFINE가 정의 되었을때만 값을 덥어 쒸운다.
				if( !outIsExist || (nFlags & eCPP_ONLY_DEFINE) ) 
					e.Var()->InitValue(value);

				return e.Var();
			}

		private: // ----------------------------------------------------------
			tstring													m_sPrevTab;
			int															m_iCurrTabCount;
			jLIST_TYPEDEF_vector(jIE*,m_matches);

		};//class jConsoleVar : public jIConsoleVar

		inline jID* jConsoleVar::GetDoc(){ return m_DocConsoleVar;}

		//--------------------------------------------------------------------------
		// m_DocConsoleVar에 콘솔xml파일의 내용을 덥어 쒸운다.
		// eCPP_ONLY_DEFINE ,eDONT_SAVE2FILE로 생성된 콘솔변수에는 덥어 쒸우지 않는다.
		struct _jxLoadCVar
		//--------------------------------------------------------------------------
		{
			jConsoleVar* m_pCV;
			_jxLoadCVar(jConsoleVar* pCV): m_pCV(pCV){}
			void operator()(jE itE)
			{
				if(itE->GetType() == jIVar::ETelement) return;
				jIE* pP = itE->GetParent();
				
				while(pP)//상위부모에 jMX_SKIP_THIS 속성이 세팅되면 자식들 모두 스킵
				{
					jIVar* pV = pP->GetAttrVar(_T("jMX_SKIP_THIS") );
					if(pV && pV->Get_bool()) return;
					pP = pP->GetParent(); 
				}
				
				jE eConsoleXML = m_pCV->m_DocConsoleVar[itE->GetParent()->GetTagID()][itE->GetTagID()];
				if( eConsoleXML.Var()->GetType() == jIVar::ETelement)
				{	
					//새로 생성된것 즉 m_DocConsoleVar에 등록 안되어 있는 변수는 help와 flag정보를 m_DocConsoleVar에 복사
					itE->CopyTo(eConsoleXML);
					return;
				}

				// cpp모듈내부에서 정의된 콘솔변수이다.
				int iFlag = m_pCV->GetFlag(eConsoleXML);
				if( ( is_does_not_load_console_xml(iFlag) ) )
				{	// 콘솔xml파일의 내용을 m_DocConsoleVar에 복사하지 않음.
					return;
				}

				// 콘솔xml에서 순수 정의된 변수이므로 m_DocConsoleVar에 복사한다.
				itE.AttrP(_T("HELP"))->CopyTo(eConsoleXML.AttrP(_T("HELP")));
			}
		};
	}//namespace nCONSOLE
}

#endif //_jConsoleVar_heade23412389dsfjsar_