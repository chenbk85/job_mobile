/* file : make_struct_h_file.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-17 19:12:48
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jMake_jINet_OGS_xml.h"
#include "interface/jIConsoleVar.h"

using namespace nMake_Xml;


//--------------------------------------------------------------------------
struct _jxWrite_UserStruct
	//--------------------------------------------------------------------------
{
	tofstream& of;
	_jxWrite_UserStruct(tofstream& fp1):of(fp1){ }
	void operator ()(jIE* it)
	{
		if(_write_CODE(of, it, _T("STRUCT_FILE")) )		return ;

		of<<_jF("struct %1%\n\t{") % it->GetTagName();
		tcstr szHelp = it->GetAttr(_T("HELP"));
		if(szHelp)
		{
			of<<_jF("/*\t[[ %1% ]]*/") % szHelp;
		}

		jIE* itC = it->begin();
		AddTab();
		jrFOR(itC)
		{
			jIVar* pvLen = itC->GetAttrVar(_T("Length"));
			if(pvLen)
			{
				fname_t sz123;jt_sprintf(sz123 , _T("%d"),pvLen->Get_int());

				if(pvLen->Get_int() > 0)
					of<<_jF("%1% %1%[%d];") % itC->GetAttr(_T("TYPE")) % itC->GetTagName() % sz123;
				else
				{
					of<<_jF("std::vector<%1%> %1%;") % itC->GetAttr(_T("TYPE")) % itC->GetTagName();
				}
			}
			else
			{
				of<<_jF("%1% %2%;") % itC->GetAttr(_T("TYPE")) % itC->GetTagName();
			}
			tcstr szHelp = itC->GetAttr(_T("HELP"));
			if(szHelp)
			{
				of<<_jF("/*\t[[ %1% ]]*/") %szHelp;
			}
		}
		DecTab();
		of<<_jT("};");
	}
};

//--------------------------------------------------------------------------
struct _jxWriteStruct
//--------------------------------------------------------------------------
{
	tofstream& of;
	_jxWriteStruct(tofstream& fp1):of(fp1){ }
	void operator ()(jIE* it)
	{
		of<<_jT("");
		if(_write_CODE(of, it, _T("STRUCT_FILE") ) )		return ;
		//if(!it->size()) return;

		of<<_jF("struct S_%1%\n{") %it->GetTagName();
		AddTab();
		{
			tcstr szHelp = it->GetAttr(_T("HELP"));
			if(szHelp)
			{
				of<<_jF("/*[[ %1% ]]*/") % szHelp;
			}

			jIE* itC = it->begin();
			jrFOR(itC)
			{
				jIVar* pvLen = itC->GetAttrVar(_T("Length"));
				if(pvLen)
				{
					fname_t sz123;jt_sprintf(sz123 , _T("%d"),pvLen->Get_int());

					if(pvLen->Get_int()>0)
						of<<_jF("%1% %2%[%3%];") % itC->GetAttr(_T("TYPE")) % itC->GetTagName() % sz123;
					else
					{
						of<<_jF("std::vector<%1%> %2%;") % itC->GetAttr(_T("TYPE")) % itC->GetTagName();
					}
				}
				else
				{
					of<<_jF("%1% %2%;") % itC->GetAttr(_T("TYPE")) % itC->GetTagName();
				}
				tcstr szHelp = itC->GetAttr(_T("HELP"));
				if(szHelp)
				{
					of<<_jF("/*[[ %1% ]]*/")%szHelp;
				}

			}

			// debugger 출력용 프린트
			of<<_jF("#ifndef jNOT_USE_DebugPrint_%1%") % g_szName_HEADER_NameSpace;

			of<<_jF("void DebugPrint(bool isPrintAll)\n\t{");
			{
				AddTab();
				of<<_jF("using namespace nMech::nInterface;");
				jIVar* pv = it->GetAttrVar(_T("DebugPrint"));
				int debugMode = g_bDebugPrint;
				if(pv) debugMode = pv->Get_int();
				if(g_bDebugPrint==3 || !debugMode)
				{
					of<<_jF("jLOG(_T(\"< %1% > =\"));") % it->GetTagName();
				}
				of<<_jT("if(!isPrintAll)return;");

				itC = it->begin();
				jrFOR(itC)
				{
					jIVar* pvLen = itC->GetAttrVar(_T("Length"));
					cstr szType = itC->GetAttr(_T("TYPE"));
					of<<_jF("jDebugPrint(_T(\"%1%\"),%2%);") % itC->GetTagName() % itC->GetTagName();
				}
				DecTab();
			}
			of<<_jF("}");
			of<<_jT("#endif");

		}
		DecTab();

		of<<_jT("};");
	}
};//struct _jxWriteStruct


void make_struct_h_file(tstring& sStructureFileName,int argc, _TCHAR* argv[])
{
	jIE* it;

	tofstream of(jA(sStructureFileName));
	of.imbue(locale(jA(pv_file_locale->Get_cstr())));

	//of<<_jF("//from(%1%)\n//TIME= %1%\n"), argv[ARG_HEADER_XML_FILE],szCurrentFileName);
	of<<_jF("//from(%1%)")%argv[ARG_HEADER_XML_FILE];

	of<<_jT("#pragma once\n") ;
	it = g_pDocTargetFile->BaseI()->begin();
	jrFOR(it)
	{
		if(_write_CODE(of, it, _T("STRUCT_FILE") ) )
			continue;
		else if(it->IsName(STRUCT_LIST))
		{
			of<<_jT("//----------------------------------------") ;
			of<<_jT("//패킷용 구조체 내부에서 사용하는 자료형정의") ;
			of<<_jT("//----------------------------------------");
			//of<<_jF("\n#pragma pack(1)\n");
			it->for_each_child(_jxWrite_UserStruct(of));
			//of<<_jF("\n#pragma pack()\n");
		}
		else if(it->IsName(PROTOCAL_LIST))
		{
			of<<_jT("\n\n");
			of<<_jT("//----------------------------------------" );
			of<<_jT("//패킷용 구조체 정의" ) ;
			of<<_jT("//----------------------------------------" );
			//of<<_jF("\n#pragma pack(1)\n");
			it->for_each_child(_jxWriteStruct(of));
			//of<<_jF("\n#pragma pack()\n");
		}
	}
}


