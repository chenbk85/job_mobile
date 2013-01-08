// jPacketDispather.cpp : DLL 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "base/jbase.h"
#include "interface/xml/jIXml.h"
#include "jPacketDispatch.h"


namespace nMech
{

	namespace nNET
	{
		jPacketDispatch g_jPacketDispatch;

		jCTOR_INTERFACE(nMech::nNET::jIPacketDispatch,jPacketDispatch)
		{
			return &g_jPacketDispatch;
		}
		jDTOR_INTERFACE(nMech::nNET::jIPacketDispatch,jPacketDispatch)
		{
		}

		jPacketDispatch::jPacketDispatch()
		{
		}

		jPacketDispatch::~jPacketDispatch()
		{
		}


		static void for_each_func_RegistPlugInEvent(jNamedEventNode* pHT,jIE* pePlugInNode,jIPacketDispatchTable* pTable)
		{
			fname_t szPluginName;
			jt_sprintf(szPluginName,_T("jNamedEvent_%s"), pePlugInNode->GetTagName() );
			_jNamed_Event_Handler* pAO = (_jNamed_Event_Handler*)jBase::FindNamedPointer(szPluginName,pHT->m_szName);
			if(!pAO) return;
			jLOG(_T("Regist OK: %s - %s"),szPluginName,pHT->m_szName);
			pTable->insert(pHT->m_id,pAO);
		}
		jIPacketDispatchTable* jPacketDispatch::Regist_NamedEvent_Direct(tcstr szPlugInName,tcstr szHEADER)
		{
			nXML::jE eRoot = GetjIXml()->CreateElement();
			nXML::jE ePlugInNode = eRoot;
			ePlugInNode->ChangeTagName(jS(NULL));
			ePlugInNode.AttrP(jS(TYPE)).T() = jS(PlugInList);

			ePlugInNode = ePlugInNode[szPlugInName];
			ePlugInNode.AttrP(jS(HEADER)).T() = szHEADER;
			jIPacketDispatchTable* pPDT = Regist_NamedEvent(ePlugInNode);
			pPDT->m_pE = 0;
			GetjIXml()->DeleteElement(eRoot);
			return pPDT;
		}
		jIPacketDispatchTable* jPacketDispatch::Regist_NamedEvent_ByTag_Direct(tcstr szPlugInName,tcstr szHEADER)
		{
			nXML::jE ePlugInNode = GetjIXml()->CreateElement();
			ePlugInNode->ChangeTagName(jS(NULL));
			ePlugInNode.AttrP(jS(TYPE)).T() = jS(PlugInList);

			ePlugInNode = ePlugInNode[szPlugInName];
			ePlugInNode = ePlugInNode[jS(NULL)];
			ePlugInNode.AttrP(jS(HEADER)).T() = szHEADER;
			jIPacketDispatchTable* pPDT = Regist_NamedEvent(ePlugInNode);
			pPDT->m_pE = 0;
			GetjIXml()->DeleteElement(ePlugInNode);
			return pPDT;
		}
		jIPacketDispatchTable* jPacketDispatch::Regist_NamedEvent(jIE* pePlugInNode)
		{
			tcstr szObjName = pePlugInNode->GetTagName();
			jIE* pP = pePlugInNode->GetParent();
			if(pP && pP->GetAttrVar(jS(TYPE))->IsContents(jS(PlugInList)) )
			{

			}
			else
			{
				pePlugInNode->DebugPrint(true);
				jERROR(_T("잘못된 인자. 속성 TYPE이 없거나 값이 PlugInList이 아님 ") );
				return 0;
			}
			jIPacketDispatchTable* pTable = this->find(szObjName);
			if(pTable) return pTable;
			jNamedEventTable* pHT = GetNamedEventTable(pePlugInNode->GetAttr(_T("HEADER")) );
			if(!pHT) 
			{
				jERROR(_T("jNamedEventTable is not found : %s"),pePlugInNode->GetAttr(_T("HEADER")));
				return 0;
			}

			pTable = this->push_back(szObjName);
			pTable->m_pE = pePlugInNode;
			pTable->m_pHT = pHT;
			pHT->for_each(for_each_func_RegistPlugInEvent,pePlugInNode,pTable);
			pePlugInNode->SetUserData(jS(jIPacketDispatchTable),pTable);
			return pTable;
		}

		//--------------------------------------------------------------------------
		static void for_each_func_RegistPlugInEvent_P2P_CLIENT(jNamedEventNode* pHT,jIE* peSocketNode,jIPacketDispatchTable* pTable)
			//--------------------------------------------------------------------------
		{
			fname_t szPluginName;

			jt_sprintf(szPluginName,_T("jNamedEvent_%s_%s"),peSocketNode->GetParent()->GetTagName() ,peSocketNode->GetAttr(jS(HEADER)));
			_jNamed_Event_Handler* pAO = (_jNamed_Event_Handler*)jBase::FindNamedPointer(szPluginName,pHT->m_szName);
			jvRETURN(pAO, _T("%s : %s is not found"),szPluginName , pHT->m_szName);
			jLOG(_T("Regist OK: %s - %s"),szPluginName,pHT->m_szName);
			pTable->insert(pHT->m_id,pAO);
		}
		//--------------------------------------------------------------------------
		jIPacketDispatchTable* jPacketDispatch::Regist_NamedEvent_ByTag(jIE* peSocketNode)
		//--------------------------------------------------------------------------
		{
			jIE* pP = peSocketNode->GetParent()->GetParent();
			tcstr szHEADER = peSocketNode->GetAttr(jS(HEADER));
			if(!szHEADER)
			{
				peSocketNode->DebugPrint(true);
				jERROR_T("attribute HEADER ==NULL");
				return 0;
			}
			std::tstring szObjName ;
			if(pP && pP->GetAttrVar(jS(TYPE))->IsContents(jS(PlugInList)) )
			{
				szObjName = std::tstring( peSocketNode->GetParent()->GetTagName() ) + szHEADER;
			}
			else
			{
				peSocketNode->DebugPrint(true);
				jERROR(_T("잘못된 인자.") );
			}

			jIPacketDispatchTable* pTable = this->find(szObjName.c_str());
			if(pTable)  return pTable;
			jNamedEventTable* pHT = GetNamedEventTable(szHEADER);
			if(!pHT) 
			{
				jERROR(_T(" not found HEADER(%s). please check ->netconfig's xml") , szHEADER );
				return 0;
			}

			pTable = this->push_back(szObjName.c_str());
			pTable->m_pE = peSocketNode;
			pTable->m_pHT = pHT;

			pHT->for_each(for_each_func_RegistPlugInEvent_P2P_CLIENT,peSocketNode,pTable);

			peSocketNode->SetUserData(jS(jIPacketDispatchTable),pTable);
			return pTable;
		}

		jNamedEventTable* jPacketDispatch::GetNamedEventTable(tcstr szPlugIn_HEADER)
		{
			jNamedEventTable* v = (jNamedEventTable*)jBase::FindNamedPointer(_T("nNET"),szPlugIn_HEADER);
			if(!v) return 0;
			return v;
		}

		jIPacketDispatchTable* jPacketDispatch::Find(tcstr szPlugInName,tcstr szHEADER)
		{
			tstring szObjName =szPlugInName;
			if(szHEADER)szObjName += szHEADER;
			return this->find(szObjName.c_str());
		}


	} //nNET

}//nMech
