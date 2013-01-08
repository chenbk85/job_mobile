/* file : jGlobal.cpp
Coder : by icandoit (mech12@nate.com)
Date : 2005-06-07 23:16:12
title : 
desc : 

*/

#include "stdafx.h"
#include "functor\\_jXmlAutoLoader.h"
#include "Interface/jIDebugCallStack.h"

namespace nMech
{

	struct _jxLoadDll
	{
		void operator()(jIE* pE)
		{
			if(pE->GetType()!= jIVar::EDcstr) return;
			if(!pE->GetAttrVar(jS(ENABLE))->intValue()) return;
			HMODULE hM = ::LoadLibrary( pE->Get_cstr() );
			if(!hM)
			{
				jMB(pE->Get_cstr(), _T("LOADING FAIL") );
				assert(0);
				return;
			}
			jCreateInterface_t* pFunc = (jCreateInterface_t*)::GetProcAddress(hM, "jCreateInterface");
			assert(pFunc);
			void* v = pFunc(pE);
			pE->SetUserData( v );
		}
	};


	struct _jxUnLoadDll
	{
		void operator()(jIE* pE)
		{
			if(pE->GetType()!= jIVar::EDcstr) return;
			if(!pE->GetAttrVar(_T("ENABLE"))->intValue()) return;
			HMODULE hM = ::LoadLibrary( pE->Get_cstr() );
			if(!hM) return;
			typedef void jDeleteInterface_t();
			jDeleteInterface_t* pFunc = (jDeleteInterface_t*)::GetProcAddress(hM, "jDeleteInterface");
			if(pFunc)	pFunc();
			FreeLibrary(hM);
		}
	};

	namespace jGuiLib
	{
		/*{by icandoit4337-10-22 오후 4:52:54
		#define FW_DONTCARE         0
		#define FW_THIN             100
		#define FW_EXTRALIGHT       200
		#define FW_LIGHT            300
		#define FW_NORMAL           400
		#define FW_MEDIUM           500
		#define FW_SEMIBOLD         600
		#define FW_BOLD             700
		#define FW_EXTRABOLD        800
		#define FW_HEAVY            900
		}by icandoit 4337-10-22 오후 4:52:56*/
		jCOMMON_API  DWORD jGetFontWeight(cstr szWeight)
		{
			if(!szWeight) return 0;
			jIE* peWeightVal = nGLOBAL::g_pDocGui->Find(jS(GUI_PARAMETER_FLAG))->Find(jS(WEIGHT));
			return peWeightVal->Find(szWeight)->GetVar()->intValue();
		}

		jCOMMON_API  DWORD  jGetTextFormat(jIVar* pV)
		{
			jIE* pE1 = nGLOBAL::g_pDocGui->Find(jS(GUI_PARAMETER_FLAG))->Find(jS(TEXT_FORMAT));
			int iRet=0;
			jIE* it = pE1->begin();
			jrFOR(it)
			{
				tcstr ch = _tcsstr(pV->Get_cstr() , it->GetTagName());
				if(ch) iRet |= it->GetVar()->intValue();
			}
			return iRet;
		}

		jCOMMON_API void SetTextFormat(jIVarP& pvFormat, cstr sz)
		{
			pvFormat->Set_cstr(sz);
			pvFormat->SetUserData( (void*)(DWORD)jGetTextFormat(pvFormat) );
			//pvFormat->uintValue() = jGetTextFormat(pvFormat);
		}

		jCOMMON_API void SetTextFormat(jIVarP& pvFormat, jIVar* pV)
		{
			pvFormat = pV ;
			pvFormat->SetUserData((void*)(DWORD)jGetTextFormat(pvFormat) );
			//pvFormat->uintValue() = jGetTextFormat(pvFormat);
		}

	};


	namespace nCharSystemLib
	{
		jCOMMON_API void jMakeAniName(jIE* pE, fname_t &buf)
		{
			memset(buf,0,sizeof(buf));
			int iOrder = pE->GetOrder();
			assert(iOrder !=-1);
			for( ; pE->GetDepth() >=2 ; pE = pE->GetParent())
			{
				jt_strcat(buf,pE->GetTagName() );
				if(iOrder !=-1)
				{
					fname_t szNum;
					jt_sprintf(szNum,_T("%d"),iOrder);
					jt_strcat(buf,szNum);
					iOrder=-1;
				}
				jt_strcat(buf,_T("."));
				assert(sizeof(buf) > jt_strlen(buf));
			}
			size_t iLen = jt_strlen(buf);
			assert(iLen>0 && "jMakeAniName(jIE* pE, fname_t &buf)에서 에니메이션이름이 정상적이지 않음");
			buf[iLen-1]=0;
		}
	};

}
