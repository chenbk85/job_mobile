// jBase.cpp : DLL 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#if 1

#include "interface/xml/jIXml.h"
#include "header\\jAutoPtr.h"
#include "header\\juKey.h"
#include "base/jXmlDictionary.h"
#include "header/jCriticalSection.h"
#include "jTestUnit.h"
#include "jc/jcMemoryManager.h"
#include "header/jMemoryChunk.h"
#include "header/nNET_Stream.h"
#include "interface/jIZipUtil.h"
JBASE_API  bool g_isES_DeginerMode=false;
extern HANDLE g_hModule;
//--------------------------------------------------------------------------
// 전역 interface.
//--------------------------------------------------------------------------
#define jSINGLETON_VAR_DEFINE(XXX) struct XXX; JBASE_API XXX* g_p##XXX=0; 
jSINGLETON_LIST(jSINGLETON_VAR_DEFINE);

namespace nMech
{

	SIZE_T GetPrivateBytes_ProcessUsed()  
	{  
		SIZE_T x = 0;  
		MEMORY_BASIC_INFORMATION memInfo;  
		SIZE_T vAddress = 0;  
		ZeroMemory(&memInfo, sizeof(memInfo));  
		while (vAddress < (SIZE_T) 0x8000000 && VirtualQuery((LPCVOID)vAddress, &memInfo, sizeof(memInfo))) {  
			if (memInfo.State == MEM_COMMIT && memInfo.Type == MEM_PRIVATE) {  
				x += memInfo.RegionSize;  
			}  
			vAddress += memInfo.RegionSize;  
		}  
		return x;  
	}  

	JBASE_API void print_memory(cstr szLog)
	{
		MEMORYSTATUS memoryStatus;
		GlobalMemoryStatus(&memoryStatus);
		jLOG_T("[MEMORY][%s]%u process used , %u BYTE memory free", szLog,GetPrivateBytes_ProcessUsed(),memoryStatus.dwAvailVirtual);
	}

	JBASE_API void jBase_Init()
	{
		printf("");
	}
	
		using namespace nFileSystem;

	namespace nINPUT
	{
		//--------------------------------------------------------------------------
		juKey& juKey::Get()
			//--------------------------------------------------------------------------
		{
			static juKey g_juKey;
			return g_juKey;
		}
	}


	//--------------------------------------------------------------------------
	// 임시용 전역변수
	//--------------------------------------------------------------------------
#define __JVAR_DEFINE(x) JBASE_API int x=0;
	jGLOBAL_VAR_LIST(__JVAR_DEFINE);

	//--------------------------------------------------------------------------
	// 전역 document.
	//--------------------------------------------------------------------------
#define _DOC_DEFINE(x) namespace nGLOBAL{ JBASE_API jID* x=0;}
	jGLOBAL_DOC_LIST(_DOC_DEFINE);

	//--------------------------------------------------------------------------
	// 전역 interface.
	//--------------------------------------------------------------------------

#define jNameSpace_Interface_DEFINE(_Name_Space, _interface)\
	namespace _Name_Space{	struct _interface;	}\
	namespace nInterface{	extern JBASE_API _Name_Space::_interface* g_p##_interface=0;	}

		jNameSpace_Interface_DEFINE(nORB,jIOrb);
		jNameSpace_Interface_DEFINE(nGUI,jIGui);
		jNameSpace_Interface_DEFINE(nNET,jINet_OGS);
		jNameSpace_Interface_DEFINE(nLUA1,IScriptSystem);
		jNameSpace_Interface_DEFINE(nLUA,jILua);
		jNameSpace_Interface_DEFINE(nXML_ORB,jIXmlORB);
		jNameSpace_Interface_DEFINE(nEVENT,jIAnimationKeyFactory);
		jNameSpace_Interface_DEFINE(nLOG,jILog);
		jNameSpace_Interface_DEFINE(nCONSOLE,jIConsole);

		jNameSpace_Interface_DEFINE(nTIME,ITimer);
		jNameSpace_Interface_DEFINE(nPAK,jIPak);
		jNameSpace_Interface_DEFINE(nJC,IFrameProfileSystem);
		jNameSpace_Interface_DEFINE(nJC_SOUND,IMusicSystem);
		jNameSpace_Interface_DEFINE(nJC_SOUND,ISoundSystem);
		jNameSpace_Interface_DEFINE(nINPUT,IInput);
		jNameSpace_Interface_DEFINE(nXML,jIXmlEntityManager);


//		jNameSpace_Interface_DEFINE(nLOG,jILog);
	
	JBASE_API jBase g_jBase;

	JBASE_API tcstr g_XmlNULL=TEXT("NULL");

	namespace nSQ	{		struct jISquirrel;	}
	static nSQ::jISquirrel* g_pjISQ=0;

	// Example debug hook: called back during script execution.
	static int debug_hook(HSQUIRRELVM v) {
		SQUserPointer up;
		int event_type,line;
		const SQChar *src,*func;
		GetjISQ()->sq_getinteger(v,2,&event_type);
		GetjISQ()->sq_getstring(v,3,&src);
		GetjISQ()->sq_getinteger(v,4,&line);
		GetjISQ()->sq_getstring(v,5,&func);
		GetjISQ()->sq_getuserpointer(v,-1,&up);
		return 0;
	} // debug_hook

#define SQDBG_DEBUG_HOOK _T("_sqdebughook_")

	//--------------------------------------------------------------------------
	JBASE_API nSQ::jISquirrel* GetjISQ()
	{
		enum EGetjISQ_TYPE{ eNOT_LOAD,eLOADED,eDISABLED};
		static EGetjISQ_TYPE s_Init_SQ=eNOT_LOAD;
		if(g_pjISQ) return g_pjISQ;
		static nUtil::jCriticalSection s_cs;
		s_cs.Lock();
		if(s_Init_SQ!=eNOT_LOAD) return 0;
		if(g_pjISQ)	return g_pjISQ;
		nFileSystem::jFolder dm;
		dm.Goto(g_ExeEnv.m_szModuleDir);
		HMODULE hDLL = ::LoadLibrary( _T("jSquirrel.dll") );
		if(!hDLL)
		{
			s_Init_SQ=eDISABLED;
#if 1
			printf("skipped loading jSquirrel.dll \n");
			return 0;
#else
			path_t buf;
			dm.GetCurDir(buf);
			jMB(_T("jSquirrel.dll로딩 실패"),buf);
			throw false;
#endif
		}
		jCreateInterface_t* pFunc = (jCreateInterface_t*)::GetProcAddress(hDLL, "jCreateInterface");
		g_pjISQ = (nSQ::jISquirrel*)pFunc ( 0 );
		assert(g_pjISQ);
		s_Init_SQ=eLOADED;
		s_cs.UnLock();

#ifdef jCV
		jIVar* pvIsStartSQ = jCV(jISquirrel,_IsStartSQ,false,nCONSOLE::eDONT_SAVE2FILE | nCONSOLE::eCPP_ONLY_DEFINE,"");
		pvIsStartSQ->Set_bool(true);
#endif


		cstr sz = g_ExeEnv.m_szAppNic;
#ifdef jCV
		jIVar* pvUseSQ = jCV(exe,UseSquirrelBind,true,0,"use sq scrpit binding module");
		if(pvUseSQ->Get_bool())
		{
			nSQ::Begin_param param;
			param.m_debug_hook_func=debug_hook;
			param.m_enabledebuginfo = SQTrue;
			param.m_SQDBG_DEBUG_HOOK = SQDBG_DEBUG_HOOK;
			GetjISQ()->Begin(&param);
		}
#endif

		return g_pjISQ;
	}



	static HMODULE g_hXmlDLL ;
	static nXML::jIXml* g_pjIXml=0;


	//--------------------------------------------------------------------------
	JBASE_API nXML::jIXml* GetjIXml()\
	{\
	if(g_pjIXml) \
		return g_pjIXml;\
		static nUtil::jCriticalSection s_cs;\
		s_cs.Lock();\
		if(g_pjIXml) \
			return g_pjIXml;\
			nFileSystem::jFolder dm;\
			dm.Goto(g_ExeEnv.m_szModuleDir);\
			HMODULE g_hXmlDLL = ::LoadLibrary( _T("jXml.dll") );\
			if(!g_hXmlDLL ) g_hXmlDLL = ::LoadLibrary( _T("jXml.dll") );\
			jCreateInterface_t* pFunc = (jCreateInterface_t*)::GetProcAddress(g_hXmlDLL, "jCreateInterface");\
			g_pjIXml = (nXML::jIXml*)pFunc ( 0 );\
			assert(g_pjIXml);\
			s_cs.UnLock();\
			return g_pjIXml;\
	}\

	//--------------------------------------------------------------------------
	JBASE_API void GetjIXml_close()
	//--------------------------------------------------------------------------
		{
			if(!g_pjIXml)  return ;
			typedef void jDeleteInterface_t();
			jDeleteInterface_t* pFunc = (jDeleteInterface_t*)::GetProcAddress(g_hXmlDLL, "jDeleteInterface");
			if(pFunc)	pFunc();
			FreeLibrary(g_hXmlDLL);
			g_pjIXml=0;
			g_pjISQ=0;
		}

		//--------------------------------------------------------------------------
		JBASE_API jIVar* jFindConsoleVar(jID* pD, tcstr szName)
			//--------------------------------------------------------------------------
		{
			nFunctor::jIVar_AutoPtr v;
			v->SetType(jIVar::EDcstr);
			v->Set_cstr(szName);
			if(!pD)
			{
				jMB(_T("jConsoleVar.xml이 로딩안됐읍니다."),_T("에러") );
				return 0;
			}
			jIE* pE = pD->BaseI()->FindByFirstAttr(_T("NAME"), v);
			if(pE)	return pE->GetVar();
			return 0;
		}
#if 0
		namespace jBase_TestUnit
		{
			struct __aaa23
			{
				function < void (int)> asdf;
				function < void (int)> asdf2;
				__aaa23(){ memset(this, 0 , sizeof(*this));}
			};
			void TestUnit(jIE* )
			{
				function < void (int)> asdf;
				if(!asdf.empty())	
					asdf(23);

				__aaa23 aaa;
				assert( aaa.asdf.empty());
			}
			jONCE_RUN(jBase_TestUnit23)
			{
				jTESTUNIT_REGIST(jBase_TestUnit);
			}
		};
#endif

		//--------------------------------------------------------------------------
		// RegistNamedPointer
		//--------------------------------------------------------------------------
		jLIST_TYPEDEF_map_typedef(std::tstring , void*, s_NamedPoint);
		jLIST_TYPEDEF_map(std::tstring , s_NamedPoint_t, s_NamedPointList);
		void jBase::RegistNamedPointer(tcstr category, tcstr szName,void* v)
		{
			s_NamedPoint_t* np = &s_NamedPointList[category];
			if( np->count(szName) )
			{
				jWARN(_T("중복정의(%s:%s)"),category,szName);
				//return;
			}
			(*np)[szName] = v;
		}
		void jBase::UnRegistNamedPointer(tcstr category, tcstr szName)
		{
			s_NamedPoint_t* np = &s_NamedPointList[category];
			if( np->count(szName) )
			{
				np->erase(szName);
			}
		}
		void* jBase::FindNamedPointer(tcstr category,tcstr szName)
		{
			s_NamedPoint_t* np = &s_NamedPointList[category];
			s_NamedPoint_it it = np->find(szName);
			if(it==np->end()) return 0;
			return it->second;
		}
		void jBase::for_each_NamedPointer_ByCategory(tcstr category,  for_each_func_NamedPointer_ByCategory_t* pFunc)
		{
			s_NamedPointList_it it = s_NamedPointList.find(category);
			if(it==s_NamedPointList.end() ) return;

			s_NamedPoint_it it1 = it->second.begin(), ie1 = it->second.end();
			for( ;it1!=ie1 ; ++it1)
			{
				if(pFunc&& pFunc( it1->first.c_str(), it1->second )) 
					break;
			}
		}

		void jBase::Regist_InterfaceFactory(tcstr szName, CreateInterface_func_t*pFunc)
		{
			s_NamedPoint_t& np = s_NamedPointList[_T("NamedInterface")];
			if( np.count(szName) )
			{
				jERROR(_T("중복정의 (%s)"),szName);
				return;
			}
			np[szName] = (void*)pFunc;
		}

		nInterface::jIInterface* jBase::CreateInterface(cstr szName)
		{
			s_NamedPoint_t& np = s_NamedPointList[_T("NamedInterface")];
			s_NamedPoint_it it = np.find(szName);
			if( it == np.end() )
				return 0;

			CreateInterface_func_t* pFunc = (CreateInterface_func_t*)it->second;
			return pFunc();
		}

		//----------------------------------------------------------------
		JBASE_API void jAssertArg( bool is , TCHAR* s , ...)
			//----------------------------------------------------------------
		{
			if(is) return;
			TCHAR            szBuff[1024];
			va_list         vl;
			va_start(vl, s);
			_vstprintf(szBuff, s, vl);
			va_end(vl);

			tfname_t szB;
			_stprintf(szB , TEXT("[Assert]%s"), szBuff);
			int ret = MessageBox(0, szB , TEXT("Do you Debug?"), MB_YESNO );
			if( ret == IDYES)
			{
#ifndef _WIN64
				__asm int 3; 	
#else
				__debugbreak();
#endif
			}
			throw szBuff;
		}

}



namespace nMech
{
	namespace nUtil
	{
		void jMemoryChunk::_writeChunk(size_t  iSize, void* pVal)
		{
			if( m_iCurrPos + iSize > m_iTot)
			{
				size_t  iTot =256;
				if(m_iTot) 
				{
					iTot = m_iTot;
				}
				iTot*=2;
				if(iTot  <= (m_iCurrPos+iSize) )
				{
					iTot += (iSize*2);
				}
				CHAR* p = new CHAR[iTot];
				m_isInit= true;
				if(m_iTot)
					memcpy(p , m_pTop, m_iTot);
				if(m_pTop && m_isInit) 
					delete[] m_pTop;
				m_pTop = p;
				m_iTot=iTot;
			}
			memcpy(m_pTop+m_iCurrPos  , pVal, iSize );
			m_iCurrPos += iSize;
			jASSERT0(m_iCurrPos <=m_iTot);
		}

	}

	JBASE_API void jInitializeCriticalSectionAndSpinCount(CRITICAL_SECTION& cs)
	{
		//#if (_WIN32_WINNT >= 0x0500)
		//#else
		//				InitializeCriticalSection(&mSync);
		//#endif

		ULONG lSpinCount = 2000;
		InitializeCriticalSectionAndSpinCount(&cs, lSpinCount);
	}

	namespace nNET
	{


		namespace nStream
		{
			const uint16 g_MAX_XML_PACKET= 16000;
			JBASE_API void Write(jNetStreamWrite& st,jIE* pE)
			{
				if(!pE)
				{
					st.Write<int>(0);
					return;
				}
				nUtil::jMemoryChunk mc;
				mc.init(g_MAX_XML_PACKET);
				pE->writeChunk(mc);

				jCREATE_INTERFACE_AUTO(pZip, nMech::nUtil::jIZipBuffer);
				if( pZip.empty())
				{
					jERROR(_T("jCREATE_INTERFACE_AUTO(pZip, jIZipBuffer);" ) );
					return;
				}
				pZip->Init(mc.GetBuffer() , mc.size());
				int xml_len = pZip->GetZipSize();
				if(xml_len>=g_MAX_XML_PACKET )
				{
					jERROR(_T("jCREATE_INTERFACE_AUTO(pZip, jIZipBuffer);" ) );
					return;
				}
				st.Write<int>(xml_len);
				st.WriteArray<BYTE>((BYTE*)pZip->GetZipBuff() , abs(xml_len));
			}
			JBASE_API void Read(jNetStreamRead& st,jIE* pE)
			{
				nUtil::jMemoryChunk mc;
				int xml_len;
				st.Read<int>(xml_len);
				if(!xml_len) return;
				if(xml_len>=g_MAX_XML_PACKET )
				{
					jERROR(_T("xml_len>=g_MAX_XML_PACKET" ) );
					return;
				}

				CHAR* pZipBuf = (CHAR*)st.ReadVirtual(abs(xml_len));

				jCREATE_INTERFACE_AUTO(pUnZip, nMech::nUtil::jIUnZipBuffer);
				if( pUnZip.empty())
				{
					jWARN(_T("nMech::nUtil::jIUnZipBuffer not found"));
					return;
				}
				pUnZip->Init(pZipBuf, xml_len);
				mc.SetBuffer(pUnZip->GetUnZipBuff(),pUnZip->GetUnZipSize());
				pE->readChunk(mc);
			}
		}


	}
}//nMech
#endif