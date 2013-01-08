// jXml.cpp : DLL 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "jXml.h"
#include "jxDocument.h"
#include "functor\\_jXmlAutoLoader.h"
#include "base/jXmlDictionary.h"
#include "base/jTestUnit.h"
#include "interface/jIINI_File.h"
#include "base/jWindow_Util.h"
#include <objbase.h>

#if defined(jMSXML_USE)
	#include "jxDocumentEx.h"
#else
#endif
#include "jxDocument_tiny.h"
#include "Interface/xml/jIXmlUtil.h"
//#include "interface/Squirrel/jISquirrel.h"


volatile float __f__=10;



BOOL APIENTRY DllMain( HANDLE hModule, 
											DWORD  ul_reason_for_call, 
											LPVOID lpReserved
											)
{
	++__f__;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


namespace nMech
{
	StringID g_Current_LogLevel_jStringID = jx(jXml);

	namespace nXML
	{
		jXml* g_pXml=0;
		static bool g_isXmlid_init =false;
		
		//--------------------------------------------------------------------------
		// jIXml interface 함수.
		//--------------------------------------------------------------------------


		size_t jXml::size(){ return m_DocList.size();	}
		int& jXml::GetFlag(){ return m_iFlag;}
		jIElement* jXml::FindElementByHandle(uint iHandle){	return jxElement::ms_TreeNodeMemoryManager.GetNode(iHandle);}


		int filter_CoInitialize(unsigned int code, struct _EXCEPTION_POINTERS *ep) 
		{
			jMB("jXml.dll loading : CoInitialize(NULL)","filter_CoInitialize");
			return EXCEPTION_EXECUTE_HANDLER;
		}

		void CoInitialize_xml()
		{
			__try
			{
				::CoInitialize(NULL);
				//::CoInitializeEx(NULL, COINIT_MULTITHREADED);
			}
			__except(filter_CoInitialize(GetExceptionCode(), GetExceptionInformation()))
			{
			}

		}
		extern "C"
		{
			JXML_API void* jCreateInterface(jIE* pE)
			{
#ifdef UNICODE
 				HRESULT hr = CoInitialize( NULL );
				if( FAILED( hr ) )
				{
					jMB("jXml.dll CoInitialize","error");
					// ERROR: COM 초기화 실패
					// 에러 처리
				}
#endif
				//CoInitialize_xml();
				if(g_pXml) 
					return g_pXml;

				g_pXml = new jXml;
				return (jIXml*)g_pXml;
			}
			JXML_API void jDeleteInterface()
			{
				g_pXml->Release();
				SAFE_DELETE(g_pXml);
			}
			__declspec(dllexport) acstr jGetModuleOwnerName()
			{
				return "icandoit";
			}

		}

		jxD* jXml::Insert(tcstr key) // 해당이름으로 오브젝트를 등록하고 주소를 리턴.
		{
			m_DocList_it it = m_DocList.find(key);
			if(it==m_DocList.end())
			{
				jxD& doc = m_DocList[key];
				return &doc;
			}
			return &(it->second);
		}

		//--------------------------------------------------------------------------
		// jXmlCallBackManager
		//--------------------------------------------------------------------------
		void jXmlCallBackManager::SetCallback(cstr callbackName, jXml_Callback_ft fn)
		{
			m_jXml_Callback[callbackName ] = fn;
		}
		void jXmlCallBackManager::RunCallBack(cstr sz , boost::any a)
		{
			m_jXml_Callback_it it= m_jXml_Callback.find(sz);
			if(it!=m_jXml_Callback.end())
			{
				it->second(a);
			}
		}


		//--------------------------------------------------------------------------
		// jXml
		//--------------------------------------------------------------------------
		jIXmlCallBackManager* jXml::GetCallBackManager()
		{
			static jXmlCallBackManager a;
			return &a;
		}

		bool ms_isFirstUseJXML=false;
		bool ms_bXML_SkipAutoSave=false;
		bool ms_isGenerateJXML=false;
		int ms_iSaveFileBackupCount=5;
		bool ms_isDocAotuLoad=false;

		void jXml::SetAutoLoad(bool is)
		{
			ms_isDocAotuLoad = is;
		}
		bool jXml::GetAutoLoad()
		{
			return ms_isDocAotuLoad;
		}

		jIVar::EElementType  jXml::GetTypeByString(cstr szName)///*"EDint" -> EDint */
		{
			return jxVar::GetTypeByString(szName);
		}
		cstr jXml::GetTypeStringByType(jIVar::EElementType eType)/* EDint ->"EDint" */
		{
			return jxVar::GetTypeStringByType(eType);
		}


		jIXml_Param*  jXml::GetInterfaceParam()
		{
			return &m_Param;
		}
		void jXml::SetInterfaceParam(jIXml_Param* param)
		{
			if(&m_Param == param) return;
			#define COPY_PARAM(TYPE,VAR,INIT,HELP) m_Param.VAR = param->VAR;
			jIXml_Param_LIST(COPY_PARAM);
		}


		//---------------------------------------------------------------
		void jXml::RegistXML(bool isShowLog)
			//----------------------------------------------------------------
		{

			fname_t szSystem;
			GetSystemDirectory(szSystem,sizeof(szSystem));
			nFileSystem::jFolder dm(szSystem);
			if(nFileSystem::jFolder::Is_Exist(_T("msxml4.dll")))
			{
				return;
			}
			dm.GotoStartDir();
			dm.Goto(_T("xml\\bin"));
			jRAISE(nFileSystem::jFolder::Is_Exist(_T("msxml4.dll")));
			CopyFile(_T("msxml4.dll"),szSystem, TRUE);
			CopyFile(_T("msxml4a.dll"),szSystem, TRUE);
			CopyFile(_T("msxml4r.dll"),szSystem, TRUE);
			CopyFile(_T("msxml.dll"),szSystem, TRUE);
			CopyFile(_T("msxmlr.dll"),szSystem, TRUE);
			dm.Goto(szSystem);
			afname_t szBuf;
			ja_sprintf(szBuf , ("regsvr32 /s /c msxml4.dll"));
			WinExec(szBuf ,SW_HIDE);	
		}


		jIVar* jXml::CreatejVar()
		{
			return new jxVar;
		}
		void jXml::DeletejVar(jIVar* pV)
		{
			delete pV;
		}


		jXml::~jXml()
		{
		}

		cstr jXml::GetVersion()
		{
			static fname_t buf;
			jt_sprintf(buf ,_T("%s (%s)"),_T(__DATE__), _T(__TIME__));
			return buf;
		}
		void* jXml::GetData(nMech::StringID sz , void* vData)
		{
			if(sz == jx(GET_DOC_AUTOLOAD) )
			{
				if(vData)
				{
					ms_isDocAotuLoad = *(bool*)vData;
				}
				return &ms_isDocAotuLoad;
			}
			return 0;

		}

		//---------------------------------------------------------------
		void jXml::NewFile(tcstr szFile)
			//----------------------------------------------------------------
		{
			nFileSystem::jFolder dir;
			FILE* fp = jt_fopen(szFile, TEXT("wt"));
			if(!fp)
			{
				jERROR(_T("jXml::NewFile ( %s)") , szFile);
				return;
			}
			nFileSystem::jFileName fn(szFile);
			jt_fprintf(fp, TEXT("%s"), TEXT("<?xml version='1.0' encoding=\"euc-kr\"?>\n"));
			jt_fprintf(fp, TEXT("<%s/>"), fn.fname);
			fclose(fp);
		}
		

		//---------------------------------------------------------------
		void jXml::Release()
		//----------------------------------------------------------------
		{
#if 0
			nFileSystem::jFolder dm;
			dm.GotoStartDir();
			fname_t buf;
			sprintf(buf,"xml_element_tag_%s.txt",g_ExeEnv.m_szAppNic);
			nFileSystem::UFile fp(buf,"wt");
			fprintf(fp , "jxElement::capacity = %d", jxElement::ms_TreeNodeMemoryManager.capacity());
			fprintf(fp , "jxElement::size = %d", jxElement::ms_TreeNodeMemoryManager.size());
			fprintf(fp , "jxElement::m_iObjSize = %d", jxElement::ms_TreeNodeMemoryManager.m_iObjSize);
			fprintf(fp , "jxElement::m_iSlotCount = %d", jxElement::ms_TreeNodeMemoryManager.m_iSlotCount);
			fprintf(fp , "jxElement::m_iMakedSlotIndex = %d", jxElement::ms_TreeNodeMemoryManager.m_iMakedSlotIndex);
#else
			nScript::jINI_Data_t pV = g_ExeEnv.Get_INI()->FindData(_T("exe"),_T("MAKE_XMLID"));
			if(pV && pV->Get_bool())
			{
				nFileSystem::jFolder dm;
				dm.GotoStartDir();
				fname_t buf;
				jt_sprintf(buf, _T("xml_element_tag_%s.txt"),g_ExeEnv.m_szAppNic);
				nFileSystem::UFile fp(buf,_T("wt"));
				jt_fprintf(fp , _T("jxElement::capacity = %d"), jxElement::ms_TreeNodeMemoryManager.capacity());
				jt_fprintf(fp , _T("jxElement::size = %d"), jxElement::ms_TreeNodeMemoryManager.size());
				jt_fprintf(fp , _T("jxElement::m_iObjSize = %d"), jxElement::ms_TreeNodeMemoryManager.m_iObjSize);
				jt_fprintf(fp , _T("jxElement::m_iSlotCount = %d"), jxElement::ms_TreeNodeMemoryManager.m_iSlotCount);
				jt_fprintf(fp , _T("jxElement::m_iMakedSlotIndex = %d"), jxElement::ms_TreeNodeMemoryManager.m_iMakedSlotIndex);
				fp.fclose();
				nString::Get_jIStringTable()->SaveToFile(fp);

			}
#endif

			m_DocList_it it;
			jFOR(m_DocList ,it)			{			it->second.UnLoad();		}
			m_DocList.clear();
		}

		jID* jXml::GetObj(cstr szName) // 해당 이름의 오브젝트 리턴.
		{
			tstring szOut = szName;
			transform( szOut.begin(), szOut.end(), szOut.begin(), tolower ); 
			m_DocList_it it = m_DocList.find(szOut);
			if(it == m_DocList.end() )
			{
				return 0;
			}
			return &(it->second);
		}
		void jXml::UnLoad(jIDocument* pD)
		{
			fname_t sz1;
			pD->GetURL(sz1);
			m_DocList_it it = m_DocList.find(sz1);
			if( it==m_DocList.end() ) return ;
			fname_t buf;
			pD->GetURL(buf);
			GetCallBackManager()->RunCallBack(_T("UnLoad"), pD);
			if(it->second.UnLoad())
			{
				m_DocList.erase(it);
			}
		}
		//----------------------------------------------------------------
		jIDocument* jXml::Load(tcstr szFile,nPAK::jIPak*) 
		//----------------------------------------------------------------
		{
			nFileSystem::jFileName fn(szFile);
			try{
				nFileSystem::jFolder dm;

				jxD* pD = (jxD*)GetObj(fn.buffer);
				uint iSize;
				if(!pD)
				{
					pD = &m_DocList[fn.buffer];
					TCHAR buf1[1024];
					pD->m_szPath = fn.GetPath(buf1);
					pD->m_szUrl = fn.GetName(buf1);

					iSize = jxElement::ms_TreeNodeMemoryManager.m_iSize;

					if(fn.ext[1]!=TEXT('j')) // xml파일 로딩위한 루틴. 확장자가 j로 시작하면 jxml파일.
					{
						fname_t buf,bufE,buf2;
						_tcscpy(bufE, fn.ext+1);

						_stprintf( buf, TEXT("%s%s.j%s") ,fn.GetPath(buf2), fn.fname, bufE);
						if(ms_isFirstUseJXML && nFileSystem::jFolder::Is_Exist(buf))
						{
							pD->LoadjXML(buf);
						}
						else
						{
							if(nFileSystem::jFolder::Is_Exist(fn.buffer))
							{
								if(GetFlag_eUSE_TINY_XML())
								{
									jxDocument_tiny* pDex;
									pDex = (jxDocument_tiny*)((void*)pD);
									pDex->Load(fn.buffer);
								}
								else
								{

#if defined(jMSXML_USE)
									jxDocumentEx* pDex;
									pDex = (jxDocumentEx*)((void*)pD);
#else
									jxDocument_tiny* pDex;
									pDex = (jxDocument_tiny*)((void*)pD);
#endif

									pDex->Load(fn.buffer);
								}

								// *_* by icandoit : 2005-08-31 10:50:07
								if(ms_isGenerateJXML )
								{
									pD->SaveAsJXML(buf);
								}
							}
							else if(nFileSystem::jFolder::Is_Exist(buf))
							{
								if( !pD->LoadjXML(buf) )
								{
									m_DocList.erase(fn.buffer);
									jWARN(_T("jxml load fail : %s") , buf);
									return 0;
								}
							}
							else
							{
								UnLoad(pD);
								jLOG(_T("Failed jXml::Load(%s)"), buf);
								return 0;
							}
						}
					}
					else
					{
						if(!pD->LoadjXML(fn.buffer))
						{
							m_DocList.erase(fn.buffer);
							jLOG(_T("Failed jXml::Load(%s)"), fn.buffer);
							return 0;
						}
					}
					pD->m_iSize = jxElement::ms_TreeNodeMemoryManager.m_iSize - iSize ;

#ifdef TORQUE
					void Con::printf(cstr fmt,...);
					Con::printf(TEXT("Loaded %s"),fn.buffer);
#endif
					jLOG(_T("jXml::Load(%s)"), fn.buffer);

				}
				else
				{
				}
				pD->AddRef(); // 참조 수 증가.


				return pD;
			}
			catch(...)
			{

			}
			return 0;

		}

		//----------------------------------------------------------------
		jIDocument* jXml::Load(cstr szFilename, tcstr pXmlBuff) 
			//----------------------------------------------------------------
		{
			fname_t szFile;
			nUtil::nWIN::jRemoveStartDirString(szFilename, szFile);

			nFileSystem::jFileName fn(szFile);
			if(!pXmlBuff)
			{
				jxD* pD = (jxD*)Load(fn.buffer);
				if(pD->GetTagID() == jx(NULL))
				{
					pD->ChangeTagName(fn.fname);
				}
				return pD;
			}
			m_DocList_it it = m_DocList.find(fn.buffer); 
			uint iSize;
			if(it==m_DocList.end())
			{
				it = m_DocList.insert(m_DocList.end(), m_DocList_vt(fn.buffer, jxDocument() ) );
				iSize = jxElement::ms_TreeNodeMemoryManager.m_iSize;


				if(GetFlag_eUSE_TINY_XML())
				{
					jxDocument_tiny* pDex;
					pDex = (jxDocument_tiny*)((void*)&it->second);
					pDex->LoadFromBuffer(pXmlBuff);

				}
				else
				{
#if defined(jMSXML_USE)
					jxDocumentEx* pDex;
					pDex = (jxDocumentEx*)((void*)&it->second);
#else
					jxDocument_tiny* pDex;
					pDex = (jxDocument_tiny*)((void*)&it->second);
#endif
					pDex->LoadFromBuffer(pXmlBuff);

				}



				it->second.m_iSize = jxElement::ms_TreeNodeMemoryManager.m_iSize - iSize ;
				jxD* pD = &(it->second);
				path_t buf1;
				pD->m_szPath = fn.GetPath(buf1);
				pD->m_szUrl = fn.GetName(buf1);
			}
			it->second.AddRef(); // 참조 수 증가.

			if(it->second.GetTagID() == jx(NULL))
			{
				it->second.ChangeTagName(fn.fname);
			}

			return &(it->second);
		}

		jIDocument* jXml::Load(cstr szFilename, FILE* fp)
		{
			fname_t szFile;
			nUtil::nWIN::jRemoveStartDirString(szFilename, szFile);

			m_DocList_it it = m_DocList.find(szFile); 
			if(it!=m_DocList.end())
			{
				it->second.AddRef(); // 참조 수 증가.
				return &(it->second);
			}
			fseek(fp, 0, SEEK_END);
			long iSize = ftell(fp);
			fseek(fp,0,SEEK_SET);
			TCHAR* pBuff = new TCHAR[iSize+1];
			//memset(pBuff, 0, iSize+1);
			fread(pBuff, iSize , 1, fp);
			pBuff[iSize]=0;
			jID* pD = Load(szFile, pBuff);
			delete pBuff;
			return pD;
		}

		//---------------------------------------------------------------
		void jXml::Init()
			//----------------------------------------------------------------
		{
			// *_* by icandoit : 2009-11-27 16:00:13
			// 사용안함
			//assert(m_DocList.empty());
			nString::Get_jIStringTable()->InitByXml();
			TCHAR* sz = _T("<?xml version='1.0' encoding=\"euc-kr\"?>\n\r<EmptyDoc i_READONLY=\"1\"/>");
			g_pXml->Load(_T("EmptyDoc"),sz);
		}

		static int ms_iCloneSize=0;
		//---------------------------------------------------------------
		jIDocument* jXml::Clone(jID* pDoc1)
			//----------------------------------------------------------------
		{
			jxD* pDoc = (jxD*)pDoc1;
			fname_t szClone;
			_stprintf(szClone, TEXT("%s%s.%d.clone"),pDoc->m_szPath.c_str(),pDoc->m_szUrl.c_str(),ms_iCloneSize++);

			m_DocList_it it = m_DocList.insert(m_DocList.end(), m_DocList_vt(szClone, jxDocument() ) );
			assert(it!=m_DocList.end());
			jxD* pDocClone = &(it->second);
			pDocClone->m_szUrl = szClone;
			pDoc->CopyTo(pDocClone);

#ifdef TORQUE
			void Con::printf(cstr fmt,...);
			Con::printf(TEXT("Loaded %s"),fn.buffer);
#endif
			return pDocClone;
		}

		jIE* jXml::CreateElement()
		{
			jIE* pE = jxElement::New();
			jRAISE(pE->GetParent()==0);
			return pE;
		}
		void jXml::DeleteElement(jIE* pE)
		{
			jRAISE(pE->GetParent()==0);
			pE->EraseChild();
			jxElement::parent_t::ms_TreeNodeMemoryManager.Del((jxElement::parent_t::pNode_t)pE);
		}

		jID* jXml::CreateMemoryDoc(cstr szNicName1)
		{
			tstring szNicName =szNicName1;
			transform( szNicName.begin(), szNicName.end(), szNicName.begin(), tolower ); 
			m_DocList_it it = m_DocList.find(szNicName);
			if(it!=m_DocList.end()) return &it->second;

			jxD* pD = &m_DocList[szNicName.c_str()];
			pD->m_szUrl = szNicName;

			pD->m_iTagIndex = nString::Get_jIStringTable()->GetIndex(szNicName.c_str());
			pD->m_pTagName = nString::Get_jIStringTable()->GetName(pD->m_iTagIndex);
			return pD;
		}
	}//namespace nXML
}

