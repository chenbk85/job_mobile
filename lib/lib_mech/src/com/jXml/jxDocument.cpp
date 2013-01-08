/* 
	coder	:	Cho Wook Rea (4MLMman@hitel.net)(icq:74456993) 
	compiler:	vc++ 6.0
	date	:	2001-07-05오전 7:28:50
	title	:	 xml -> jxml변환용 클래스.

	xml file load 규칙.
	: 
*/
// jxDocument.cpp: implementation of the jxDocument class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "header/jMemoryChunk.h"
#include "interface/jIZipUtil.h"
#include "base/jWindow_Util.h"
#include "jXmlUtil.h"
#include "jxDocument.h"
//#include "base/XFile.h"




#if defined(jMSXML_USE)
#include "jxDocumentEx.h"
#else
#endif
#include "jxDocument_tiny.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

namespace nMech
{
	namespace nXML
	{
		jxDocument::jxDocument():m_REF(0),m_iFlag(0),m_peParentLink(0)
		{
			m_iTagIndex=jx(NULL);
			m_pTagName=nString::Get_jIStringTable()->GetName(m_iTagIndex);
			SetTreeInfo(0,0,0,0,0,0); 
		}

		void jxDocument::DebugPrint(bool isInsert_CR)
			//****************************************************************
		{
			jLOG( TEXT("\nDocument Start : %s") , m_szUrl.c_str() );
			jxElement::DebugPrint(isInsert_CR);
			jLOG( TEXT("\nDocument End : %s") , m_szUrl.c_str() );
		}


		//---------------------------------------------------------------
		bool jxDocument::LoadjXML(cstr szURL)
			//----------------------------------------------------------------
		{
			jCREATE_INTERFACE_AUTO(pUnZip, nMech::nUtil::jIUnZipBuffer);
			if( pUnZip.empty())
			{
				jERROR(_T("nMech::nUtil::jIUnZipBuffer not found"));
				return false;
			}
			m_iRef++;

			nUtil::jMemoryChunk mc;
			FILE* fp=0;
			fp = jt_fopen(szURL , TEXT("rb"));
			if(!fp)
			{
				jWARN(_T("jxDocument::LoadjXML(%s)"), szURL);
				return false;
			}
			bool ret = true;
			CHAR* pZipBuf =0;
			try
			{
				int iZipSize;
				fread(&iZipSize, sizeof(iZipSize), 1, fp);
				pZipBuf = new CHAR[abs(iZipSize)];
				fread(pZipBuf, abs(iZipSize), 1, fp);

				pUnZip->Init(pZipBuf, iZipSize);
				mc.SetBuffer(pUnZip->GetUnZipBuff(),pUnZip->GetUnZipSize());

				assert(mc.GetTotalSize() >0);

				jxElement::readChunk(mc);
				/* *_* by icandoit : 2005-09-02 22:53:28

				m_iRef++;
				jMemoryChunk mc;
				nFileSystem::UFile fp(szURL , TEXT("rb"));
				fread(&mc.m_iTot, sizeof(mc.m_iTot), 1, fp);
				mc.init(mc.m_iTot);
				fread(mc.m_pTop, abs(mc.m_iTot), 1, fp);
				jxElement::readChunk(mc);
				*/ //*_* by icandoit : 2005-09-02 22:53:32
			}
			catch (...)
			{
				ret = false;
				
			}
			SAFE_DELETE(pZipBuf);
			if(fp)	fclose(fp);

			return ret;

		}

		//---------------------------------------------------------------
		void jxDocument::SaveAsJXML(cstr szUrl)
			//----------------------------------------------------------------
		{
			jCREATE_INTERFACE_AUTO(pZip, nMech::nUtil::jIZipBuffer);
			if( pZip.empty())
			{
				jERROR(_T("jCREATE_INTERFACE_AUTO(pZip, nMech::nUtil::jIZipBuffer);" ) );
				return;
			}

			nUtil::jMemoryChunk mc;
			mc.init(2048);
			jxElement::writeChunk(mc);

			nFileSystem::jFileName fn(szUrl);
			fname_t szUrl1;
			if(fn.ext[1]!=TEXT('j'))
			{
				fname_t buf;
				_tcscpy(buf, fn.ext);
				fn.ext[1]=TEXT('j');
				_tcscpy(fn.ext+2 , buf+1);
				fname_t szPath1,szName1;
				fn.GetPath(szPath1);
				fn.GetName(szName1);
				jt_sprintf(szUrl1,_T("%s%s"),szPath1,szName1);
				szUrl = szUrl1;

			}
			fname_t szName;
			fn.GetName(szName);
			nFileSystem::jFolder dm;
			
			fname_t buf123;
			GetCurrentDirectory(_countof(buf123), buf123);

			dm.GotoStartDir();

			fname_t szPath;
			nFileSystem::jFileName fn1(szUrl);
			dm.CreateDirForce(fn1.GetPath(szPath));

			GetCurrentDirectory(_countof(buf123), buf123);
			//nFileSystem::UFile fp(szUrl, TEXT("wb"));
			FILE* fp=0;
			fp = jt_fopen(szUrl, _T("wb") );
			if(!fp)
				fp = jt_fopen(szUrl, _T("wb") );
			if(!fp)
			{
				jERROR(_T("jxDocument::SaveAsJXML ( %s)"), szUrl);
				return ;
			}

			int iSize;
			try
			{

				if(m_iCloneRef==-1)
				{
					m_szCloneUrl = szUrl;
				}

				pZip->Init(mc.GetBuffer() , mc.size());

				iSize = pZip->GetZipSize();
				fwrite(&iSize , sizeof(iSize) , 1 , fp);
				fwrite(pZip->GetZipBuff() , abs(iSize), 1 ,fp);

			}
			catch(...)
			{

			}

			fclose(fp);

		}

		//---------------------------------------------------------------
		void jxDocument::CopyTo(jIDocument* pd)
			//----------------------------------------------------------------
		{
			jxD* pD = (jxD*)pd;
			assert(m_iCloneRef!=-1);// 클론문서로 다시 클론 문서를 만들지 못함.
			pD->m_jCommentManager.clear();
			pD->m_iRef=1;
			pD->m_iCloneRef=-1; // -1이면 이문서는 클론문서임.
			pD->m_iSize = m_iSize;
			++m_iCloneRef;
			jxElement::CopyTo(pD);
		}

		//---------------------------------------------------------------
		void jxDocument::ReLoad()
			//----------------------------------------------------------------
		{
			nFileSystem::jFolder dm;
			dm.Goto(g_ExeEnv.m_szStartDir);
			dm.Goto(m_szPath.c_str());
			nFileSystem::jFileName fn(m_szUrl.c_str());
			assert(!m_iCloneRef); // 이문서의 클론객체가 있을때는 reload금지.
			m_iRef = 0;
			clear();

			if(fn.ext[1]==TEXT('j')) // xml파일 로딩위한 루틴. 확장자가 j로 시작하면 jxml파일.
			{
				LoadjXML(m_szUrl.c_str());
			}
			else
			{
			if(0 && g_pXml->GetFlag_eUSE_TINY_XML())
			{
				jxDocument_tiny* pDex;
				pDex = (jxDocument_tiny*)((void*)this);
				pDex->Load(m_szUrl.c_str());
			}
			else
			{
#if defined(jMSXML_USE)
				jxDocumentEx* pDex;
				pDex = (jxDocumentEx*)((void*)this);
#else
				jxDocument_tiny* pDex;
				pDex = (jxDocument_tiny*)((void*)this);
#endif

				pDex->Load(m_szUrl.c_str());
			}

			}

		}


		//---------------------------------------------------------------
		void jxDocument::SaveAsXML(cstr szUrlBuf)	
			//----------------------------------------------------------------
		{		
			nFileSystem::jFolder dm;	
			dm.Goto(g_ExeEnv.m_szStartDir);
			nFileSystem::jFileName fn(szUrlBuf);
			fname_t szPath;
			dm.CreateDirForce(fn.GetPath(szPath));
			fname_t szjXml;
			if(!jt_strcmp(fn.ext,_T(".jxml")))
			{
				jt_sprintf(szjXml , _T("%s%s%s.xml"),fn.drive,fn.dir,fn.fname);
				szUrlBuf = szjXml;
			}
			if(m_iCloneRef==-1)
			{
				m_szCloneUrl = szUrlBuf;
			}
			jXmlFile fp123;
			jXmlFile* fp=&fp123;
			
			fp->fp = 0;
			fp->xfp = 0;

#ifdef UNICODE
//  			CXFile xfp(szUrlBuf,FALSE,TRUE,TRUE);
//  			fp->xfp = &xfp;
#else
			fp->fp= jt_fopen(szUrlBuf,_T("wt"));
			if(!fp->fp) throw szUrlBuf;
#endif


			if(fp->fp)
			{
				jt_fprintf(fp->fp, TEXT("%s"), TEXT("<?xml version='1.0' encoding=\"euc-kr\"?>\n"));
			}
			else
			{
#ifdef UNICODE
				name1024_t bufX;
				jt_sprintf(bufX, TEXT("%s"), TEXT("<?xml version='1.0' encoding=\"euc-kr\"?>\n") );
				fp->str +=bufX;
				//fp->xfp->Write(bufX, jt_strlen(bufX));
#endif
			}
			jxElement::SaveXML(fp);		
#ifdef UNICODE
			void xml_save(const WCHAR* szFile , const WCHAR* szXML);
			//::CoInitialize(NULL);
			xml_save(szUrlBuf, fp->str.c_str());
			//CoUninitialize();
// 			fp->xfp->Close();
#else
			fclose(fp->fp);
#endif

		}
		extern bool ms_bXML_SkipAutoSave;
		//---------------------------------------------------------------
		bool jxDocument::UnLoad()
			//----------------------------------------------------------------
		{
			if(!m_iSize) return true;
			if(m_iRef>0)
				--m_iRef;

			// FILE:z:\server\src\core\jCommon\Interface\xml\jIXml.txt 참고
			jIVar* pV = GetAttrVar(TEXT("SAVE_TYPE"));
			if(pV && pV->IsContents(_T("AUTOSAVE")) && !ms_bXML_SkipAutoSave )
			{
				fname_t buf;
				nFileSystem::jFolder dm;
				dm.GotoStartDir();
				dm.Goto(m_szPath.c_str());
				nUtil::nWIN::DoFileBackup( m_szUrl.c_str() , pV->Get_bool() , buf);
				dm.GoBack();
				dm.GoBack();
				Save();
			}
			jxElement::clear();
			m_iSize=0;
			return true;
		}



		/*{chowookrea@hotmail(icq74456993)2003-12-02오후 7:05:02
		// 만들어진 jxml파일을 다시 출력하기 위한 루틴.
		fn.Init(szFileName);
		jxD* pjD = g_jXmlManager.Load(fn.buffer);
		pjD->DebugPrint(); // 콘솔에 내용출력.
		jxE* pee  = pjD->FindElement("AXIS_Z_COLOR");
		jvector<std::tstring> out;
		GetParentPath(pee, out);
		pee =pjD->FindByBlood("AXIS_Z_COLOR",out);
		}chowookrea@hotmail(icq74456993) 2003-12-02오후 7:05:04*/
		//---------------------------------------------------------------
		// 핏줄로 부터 해당 이름을 찾는다.
		jIElement* jxDocument::FindByBlood(cstr szElement , const jvector<std::tstring> &aBlood)
			//----------------------------------------------------------------
		{
			typedef jvector<std::tstring>::const_iterator  itc_t;
			itc_t it= aBlood.begin(),ie = aBlood.end() ;
			cstr sz;
			jIE* pE = this;
			for(; it!=ie; ++it)
			{
				sz = it->c_str();
				pE = pE->Find(sz);
				if(!pE) return 0;
			}
			pE = pE->Find(szElement);
			return pE;
		}


		//----------------------------------------------------------
		// xpath 형식 : @는 속성이다.  "attname@1.2.3"   // 첫번째자식의 2번째자식의 3번째
		//								parent에 root는 포함안됨.
		jIE* jxDocument::GetXPathNode(cstr szXPath , jIAttribute** pA )
		{
			jvector<std::tstring> outAtt, outE;

			if(!_tcslen(szXPath))
				return this;

			jxE* peFind = (jxE*)this;
			size_t len = _tcslen(szXPath)-1;
			if(szXPath[len]==TEXT('@'))
			{
				fname_t buf;
				_tcscpy(buf, szXPath);
				buf[len]=0;
				jxAttributeList::iterator it = peFind->m_AttMap.find( buf);
				if(pA) *pA = &(*it);
			}
			else
			{
				nString::jSplit(szXPath , TEXT("@"), outAtt);
				assert(outAtt.size()<=2);
				cstr sz = outAtt[outAtt.size()-1].c_str();
				if(_tcslen(sz))
				{
					nString::jSplit(outAtt[outAtt.size()-1] , TEXT(".") , outE);

					size_t tot = outE.size();
					for( ; tot >0 ; --tot)
					{
						cstr sz = outE[tot-1].c_str();
						peFind = (jxE*)peFind->FindByOrder(_tstoi(sz));
						if(!peFind) 
						{
							tfname_t buf;
							GetURL(buf);
							jWARN(_T("에러 : jxDocument(%s)::GetXPathNode(%s)"),buf, szXPath);
							return  0;
						}
					}
				}
				if( outAtt.size() == 2 )
				{
					cstr sz = outAtt[0].c_str();
					if(pA) *pA = peFind->GetAttrNode( sz );
				}
				else
				{
					if(pA) *pA = 0;
				}
			}
			return peFind;
		}

		//---------------------------------------------------------------
		// xpath 형식 : @는 속성이다.  "attname@element.parent2.parent1.parent"  
		//								parent에 root는 포함안됨.
		jIE* jxDocument::GetSXPathNode(cstr szXPath , jIAttribute** pA )
			//----------------------------------------------------------------
		{
			jvector<std::tstring> outAtt, outE;

			if(!_tcslen(szXPath))
				return this;

			jxE* peFind = this;
			size_t len = _tcslen(szXPath)-1;
			if(szXPath[len]==TEXT('@'))
			{
				fname_t buf;
				_tcscpy(buf, szXPath);
				buf[len]=0;
				jxAttributeList::iterator it = peFind->m_AttMap.find( buf);
				if(pA) *pA = &(*it);
			}
			else
			{
				nString::jSplit(szXPath , TEXT("@"), outAtt);
				assert(outAtt.size()<=2);
				cstr sz = outAtt[outAtt.size()-1].c_str();
				if(_tcslen(sz))
				{
					nString::jSplit(outAtt[outAtt.size()-1] , TEXT(".") , outE);

					size_t tot = outE.size();
					for( ; tot >0 ; --tot)
					{
						cstr sz = outE[tot-1].c_str();
						TCHAR* szMulti = jt_strchr(const_cast<TCHAR*>(sz),_T(':') );
						if(!szMulti)
						{
							peFind = (jxE*)peFind->FindByDepth(1,sz);
						}
						else
						{
							tfname_t szBuf;
							jt_strcpy(szBuf, sz);
							szMulti = jt_strchr(szBuf,':');
							*szMulti = 0;
							++szMulti;
							if(!jt_strlen(szMulti))
							{
								peFind = (jxE*)peFind->FindByDepth(1,szBuf);
							}
							else
							{
								int iOr1 = jt_atoi(szMulti);
								jxE* peFind1 = (jxE*)peFind->FindByOrder(iOr1);
								if(peFind1)
								{
									peFind = peFind1;
								}
								else
								{
									peFind = (jxE*)peFind->FindByDepth(1,szBuf);
								}
							}
						}
						if(!peFind) return 0;
					}
				}
				if( outAtt.size() == 2 )
				{
					cstr sz = outAtt[0].c_str();
					if(pA) *pA = peFind->GetAttrNode( sz );
				}
				else
				{
					if(pA) *pA = 0;
				}
			}
			return peFind;
		}


		void jxDocument::Save() 
		{
			if(GetFlag_IsMemoryDoc()) 
				jERROR(_T("memory doc에 대해 Save()호출 : %s"), m_szUrl);
			nFileSystem::jFileName fn(m_szUrl.c_str());
			(fn.ext[1] == TEXT('j') ) ?			SaveJXML() : SaveXML();
			g_pXml->GetCallBackManager()->RunCallBack(_T("Save"), (jID*)this);
		}
		void jxDocument::SaveJXML()	
		{		
			if(check_DONTSAVE()) return ;

			if(GetFlag_IsMemoryDoc()) 
				jERROR(_T("memory doc에 대해 SaveJXML()호출 : %s"), m_szUrl);

			tstring str ;
			if(m_iCloneRef==-1)
			{
				str = m_szCloneUrl;
			}
			else
				str = m_szPath + m_szUrl;

			SaveAsJXML(str.c_str());	
		}


		jIE* jxDocument::BaseI()
		{ 
			return static_cast<jIE*>((jxE*)this);
		}
		jIE* jxDocument::Find(cstr sz)
		{ 
			return jxElement::Find(sz);
		}
		jIE* jxDocument::Find(nMech::StringID sz)
		{ 
			return jxElement::Find(sz);
		}
		cstr jxDocument::GetPath() 
		{ 
			return  m_szPath.c_str(); 	// xml 파일 경로. 마지막에 \가 붙어있음.
		} 

		cstr jxDocument::GetURL(tfname_t szBuf)
		{
			jt_sprintf(szBuf,TEXT("%s%s"),m_szPath.c_str(),m_szUrl.c_str());
			jRAISE(jt_strlen(szBuf) < 255);
			return szBuf;
		}

		void jxDocument::SaveXML() 
		{
			if(check_DONTSAVE()) return ;

			if(GetFlag_IsMemoryDoc()) 
				jERROR(_T("memory doc에 대해 SaveXML()호출 : %s"), m_szUrl);

			// 원래 폴더로 이동.
			tstring str ;
			if(m_iCloneRef==-1)
			{
				str = m_szCloneUrl;
			}
			else
				str = m_szPath + m_szUrl;
			SaveAsXML(str.c_str());	
		}

		jvector<std::tstring>* jxDocument::FindComment(jIE* pE)	
		{		 
			return m_jCommentManager.Find(pE);	
		}
		void jxDocument::SetComment(jIE* pE,cstr szComment)
		{ 
			m_jCommentManager.SetComment(pE, szComment);
		}
		int& jxDocument::GetFlag()
		{ 
			return m_iFlag;
		}
		jIE* jxDocument::GetParentLink() // xml문서에서 다른 xml문서를 포함하는관계일때 자신을 포함하는 문서를 리턴
		{
			return m_peParentLink;
		}
		void jxDocument::SetParentLink(jIE* pE)
		{
			//if(pE)	assert(!m_peParentLink && "jID::SetParentLink()에서 기존에 링크된 문서가 있읍니다.");
			m_peParentLink = pE;
		}
		void* jxDocument::jGetData(cstr szDataName,void*)
		{

			return 0;
		}

	}
}

