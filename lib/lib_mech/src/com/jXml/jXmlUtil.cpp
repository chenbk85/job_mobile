/* 
	filename:	jxSchema.cpp
	coder	:	Cho Wook Rea (mech12@dreamwiz.com)(icq:74456993) 
	compiler:	vc++ 6.0
	date	:	2001-07-05오전 4:40:05
	title	:	
*/
#include "stdafx.h"
#include "jXmlUtil.h"
#include "jxDocument.h"
#include "util/jUtil.h"
#include "util/jRegistry.h"
#include "header/jMemoryChunk.h"

//strcspn
//static void __cdecl dumy_func(cstr , ...){ 	}

namespace nMech
{
	namespace nXML
	{

		jIXmlUtil* jXml::GetXmlUtil()
		{
			static jXmlUtil a;
			return &a;
		}


		//---------------------------------------------------------------
		int jXmlUtil::GetParentPath(jIE* pe , jvector<std::tstring>& out)
			//----------------------------------------------------------------
		{ // 
			jxE* pE = (jxE*)pe;
			if(pE->isRoot()) return 0;
			jxE* it;
			int i=0;
			cstr sz ;
			for(it=pE->_pP ; !it->isRoot() ; it = it->_pP )
			{
				++i;
				sz = it->GetTagName();
				out.insert(out.begin(), sz);
			}
			return i;
		}

		//---------------------------------------------------------------
		int jXmlUtil::GetParentPath(jIE* pe , jvector<StringID>& out)
			//----------------------------------------------------------------
		{ // 
			jxE* pE = (jxE*)pe;
			if(pE->isRoot()) return 0;
			jxE* it;
			int i=0;
			for(it=pE->_pP ; !it->isRoot() ; it = it->_pP )
			{
				++i;
				out.insert(out.begin(), it->GetTagID() );
			}
			return i;
		}


		//---------------------------------------------------------------
		// peMacro는 szFile중에서 매크로 문자를 해당 리소스패스 스트링으로 변환한다.
		bool jXmlUtil::GetMacroString(cstr szIn , jIE* peMacro, TCHAR* szOut)
			//----------------------------------------------------------------
		{
			TCHAR* ch = _tcschr(const_cast<TCHAR*>(szIn), TEXT('%'));
			if(!ch)
			{
				_tcscpy(szOut , szIn);
				return false;
			}

			TCHAR szBuf[1024] ;
			assert(_tcslen(szIn) <1024 );
			_tcscpy(szBuf , szIn);

			ch = _tcschr(szBuf, TEXT('%'));
			TCHAR* ch1 = ch+1;
			*ch=0;
			_tcscpy(szOut , szBuf);
			ch = _tcschr(ch1, TEXT('%'));
			jID* pD = peMacro->GetDoc();
			jIE* pE = pD->Find(jS(MACRO));
			fname_t buf;
			if(!pE)
			{
				jERROR(TEXT("resource MACRO ELEMENT NOT FOUND : [%s:<MACRO>]%s") , pD->GetURL(buf) , szIn );
			}
			if(!ch)
			{
				jERROR(TEXT("resource MACRO error : [%s]%s") , pD->GetURL(buf) , szIn );
			}
			*ch=0;
			ch= ch+1;
			TCHAR szBuf3[256];
			_tcscpy( szBuf3 , ch1);

			jIE* pE1 = pE->Find(szBuf3);
			assert(pE1);
			_tcscat(szOut , pE1->Get_cstr() );
			_tcscat(szOut , ch);
			return true;
		}
		void jXmlUtil::AdjustFileNameByDoc(tfname_t &szName , jIE* it)
		{
			nFileSystem::jFileName fn;
			jt_strcpy(szName , it->Get_cstr());

			TCHAR* ch = jt_strchr(szName , _T('\\'));
			tfname_t buf;
			if(!ch)
			{
				it->GetDoc()->GetURL(buf);
				nFileSystem::jFileName fn(buf);
				jt_sprintf(szName, _T("%s%s"), fn.GetPath(buf), it->Get_cstr() );
			}
			jt_strlwr(szName);

		}

		jID* jXmlUtil::Var2Doc(jIVar* pV) // pV의 값으로 문서를 로딩하여 리턴
		{
			if(!pV) return 0;
			jID* pD = (jID*)pV->GetUserData();
			if(pD) return pD;
			pD =GetjIXml()->Load(pV->Get_cstr());
			if(!pD) return 0;
			pV->SetUserData(pD);
			return pD;
		}

		//---------------------------------------------------------------
		void jXmlUtil::SetXPath(jIE* pePacket , jIE* pE, jIA* pA)
		{
			jIE* pePa = pePacket->Find(jS(XPATH));
			pePa->SetXPathContents(pE, pA);
		}

		//---------------------------------------------------------------
		jID* jXmlUtil::GetXPath(jIE* pePacket, jIE**pE, jIA**pA)
		{
			jIE* pePA = pePacket->Find(jS(XPATH) );
			return pePA->XPathFromThis(pE, pA);
		}
		bool jXmlUtil::LoadFromRegistry(jIE* pE,tcstr szRegPath,tcstr szRegName)
		{
			nMech::nUtil::CRegistry reg;
			reg.Open(szRegPath,HKEY_LOCAL_MACHINE);
			if(!reg[szRegName].Exists() || !reg[szRegName].IsBinary() || !reg[szRegName].GetBinaryLength()) 
				return false;

			bool isRet=false;
			size_t len = reg[szRegName].GetBinaryLength();
			BYTE *pBuf =  new BYTE[len+1];
			try
			{
				reg[szRegName].GetBinary(pBuf,len);
				nUtil::jMemoryChunk mc;
				mc.SetBuffer((CHAR*)pBuf,len);
				pE->readChunk(mc);
				isRet=true;
			}
			catch (...)
			{
				jWARN(_T("%s - %s loading error"), szRegPath, szRegName);
			}
			SAFE_DELETE_ARRAY(pBuf);
			return isRet;
		}
		void jXmlUtil::SaveToRegistry(jIE* pE,tcstr szRegPath,tcstr szRegName)
		{
			const uint16 g_MAX_XML_PACKET= 16000;
			nUtil::jMemoryChunk mc;
			mc.init(g_MAX_XML_PACKET);
			pE->writeChunk(mc);

			nMech::nUtil::CRegistry reg;
			reg.Open(szRegPath,HKEY_LOCAL_MACHINE);
			reg[szRegName].SetBinary((BYTE*)mc.GetBuffer() , mc.size());
		}

		jIVar* jXmlUtil::GetOverrideAttr(jIE* pE ,cstr szAttr,jIVar::EElementType eType , cstr szDefault,jIE* peOverride,int iParentDepth)
		{
			jIVar* pV =  pE->GetAttrVar(szAttr);//pE->PersistAttr(szAttr,eType, cstr szDefault);
			jIVar* pvOverride=0;
			if(!pV && peOverride)
			{
				int i=0;
				if(iParentDepth<0)
					i = 999;

				for( ; !peOverride->isRoot(); peOverride=peOverride->GetParent() , ++i)
				{
					pvOverride = peOverride->GetAttrVar(szAttr);
					if(pvOverride) break;
					if(i > iParentDepth) // iPreantDepth == 0 이면 자신만 찾고, 1이상이면 갯수만큼의 부모에게서 찾는다.
						break;
				}
			}
			if(pvOverride)
			{
				fname_t buf;
				pV = pE->PersistAttr(szAttr,eType, pvOverride->ToString(buf));
				pV->FromString(buf);
			}
			else
			{
				pV = pE->PersistAttr(szAttr,eType, szDefault);
			}
			return pV;
		}


	}
}
