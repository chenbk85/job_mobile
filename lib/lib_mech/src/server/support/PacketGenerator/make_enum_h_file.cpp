/* file : make_enum_h_file.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-17 18:32:02
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jMake_jINet_OGS_xml.h"
#include "interface/jIConsoleVar.h"

using namespace nMake_Xml;


//--------------------------------------------------------------------------
struct _jxMake_call_sq_func
	//--------------------------------------------------------------------------
{
	tofstream& of;
	_jxMake_call_sq_func(tofstream& fp1):of(fp1){ }
	void operator ()(jIE* it)
	{
		of<<_jF("void call_sq_%1%(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);") % it->GetTagName();
	}
};


acstr szFIle1234asdf;

//--------------------------------------------------------------------------
struct _jxWriteEnumFile
	//--------------------------------------------------------------------------
{
	tofstream& of;
	_jxWriteEnumFile(tofstream& fp1,acstr sz):of(fp1){ szFIle1234asdf = sz ;}
	void operator ()(jIE* it)
	{

		if(_write_CODE(of, it, _T("ENUM_FILE")) )		return ;
		jIVar* pvCustomNumber = it->GetAttrVar(jS(CustomNumber));
		if(pvCustomNumber)
		{
			name_t buf;
			jt_sprintf(buf, _T("%u"), pvCustomNumber->Get_uint());
			of<<_jF("%1%=%2%,") % it->GetTagName() % buf;
		}
		else
		{
			cstr szVer = g_pDocTargetFile->BaseI()->GetAttr(_T("VERSION"));
			of<<_jF("%1%=/*nMech::nNET::EProtocal_jINet_OGS_END+*/%2%+%3%,") % it->GetTagName() % szVer % (it->GetOrder()+1);
		}

		tcstr sz123= it->GetAttr(_T("HELP"));
		if(sz123)
		{
			tstring sHelp= sz123;
			tstring sRep = m_sTabBuf + _T("$%^&*");
			nSTL::replace(sHelp,_T("\n"),sRep);
			nSTL::replace(sHelp,_T("$%^&*"),_T("\n"));

			of<<_jF("/*[[ %1% ]]*/") % sHelp;
		}
		jIE* itC = it->begin();
		jrFOR(itC)
		{
			cstr szTy12 = itC->GetAttr(_T("TYPE"));
			jIVar* pvLen = itC->GetAttrVar(_T("Length"));
			cstr tag = itC->GetTagName();
			if(pvLen)
			{
				fname_t sz123;jt_sprintf(sz123 , _T("%d"),pvLen->Get_int());
				of<<_jF("/* %1% %2%[%3%];*/")% szTy12 %tag   % sz123;
			}
			else
			{
				of<<_jF("/* %1% %2%;*/") % szTy12 % tag ;
			}
			tcstr szHelp = itC->GetAttr(_T("HELP"));
			if(szHelp)
			{
				of<<_jF("/*[[ %1% ]]*/") %szHelp ;
			}
		}
		of<<_jT("");
	}
};


struct _jxWrite_include_packetHeader
{
	tofstream& of;
	_jxWrite_include_packetHeader(tofstream& fp1):of(fp1){ }
	void operator ()(jIE* it)
	{
		of<<_jF("#include \"%1%/%2%.hpp\"")% g_szName_HEADER_NameSpace %it->GetTagName();
	}

};

struct _jxMake_UMLNOTE_enum_list_GENCODE_to_enum_headerfile
{
	tofstream& of;
	_jxMake_UMLNOTE_enum_list_GENCODE_to_enum_headerfile(tofstream& fp1):of(fp1){ }
	void operator ()(jIE* it)
	{
		of<<_jF("#define for_each_%1%_%2%(ENUM)\\")% g_szName_HEADER_NameSpace % it->GetTagName();
		of<<endl << _T("\t");
		AddTab();
		jIE* itE = it->begin();
		jrFOR(itE)
		{
			of<<__jF("ENUM(%1%)  ") % itE->GetTagName();
		}
		DecTab();
	}
};

struct _jxMake_UMLNOTE_enum_list_to_enum_headerfile
{
	tofstream& of;
	_jxMake_UMLNOTE_enum_list_to_enum_headerfile(tofstream& fp1):of(fp1){ }
	void operator ()(jIE* it)
	{
		of<<_jF("// from %1%") % it->GetAttr(jS(USD_FILE));
		of<<_jF("enum %1%")% it->GetTagName();
		of<<_jT("{");
		AddTab();

		of<<_jF("eBEGIN_%1%,") %it->GetTagName();

		jIE* itE = it->begin();
		jrFOR(itE)
		{
			tcstr help  = itE->GetAttr(jS(help));
			jIVar* val = itE->GetAttrVar(jS(val));
			if(val)
			{
				of<<_jF("e%1%=%3%, //%2%") % itE->GetTagName() % help % val->Get_int();
			}
			else
				of<<_jF("e%1%, //%2%") % itE->GetTagName() % help;
		}

		of<<_jF("eEND_%1%") %it->GetTagName();

		DecTab();
		of<<_jT("};\n");
	}
};



void make_enum_h_file(tstring& sProtocalEnum,int argc, _TCHAR* argv[])
{


	tofstream of(jA(sProtocalEnum));
	of.imbue(locale(jA(pv_file_locale->Get_cstr())));
	//wostringstream os;
	jIE* it;
	cstr szVer = g_pDocTargetFile->BaseI()->GetAttr(_T("VERSION"));
	if(!szVer) jMB("VERSION속성없음", ("ERROR"));


	of<<_jF("//from(%1%)") % argv[ARG_HEADER_XML_FILE];
	//TIME= %1%\n"), nInterface::g_pITimer->GetCurrentTimeString(szCurrentFileName));
	of<<_jT("#pragma once\n") ;

	if(g_pDocTargetFile->BaseI()->size())
	{
		of<<_jF("#ifndef %1%") % GET_VAR(jNOTUSE_PACKET_JXDEFINE);
		it = g_pDocTargetFile->BaseI()->begin();
		extern jIVar* pv_Server_TAG;

		jrFOR(it)
		{
			if(it->IsName(PROTOCAL_LIST))
			{
				if(g_isPrint_jxDEFINE )
					of<<_jF("jxDECL_%1%(%1%);\n") % g_szName_HEADER_NameSpace;
				jIE* itC = it->begin();
				jrFOR(itC)
				{
					jIVar* pvDD = itC->GetAttrVar(_T("jxDEFINE"));
					bool isPo = !pvDD || pvDD->Get_bool();
					if(g_isPrint_jxDEFINE && isPo)
						of<<_jF("jxDECL_%1%(%2%);") % g_szName_HEADER_NameSpace %itC->GetTagName();
				}
			}
		}
		of<<_jF("#endif //%1%") % GET_VAR(jNOTUSE_PACKET_JXDEFINE);
		of<< endl;

	}

	nXML::jE eEnumList= g_pDocTargetFile->Find(jS(ENUM_TYPE_LIST));
	if(eEnumList.full())
		eEnumList->for_each_child(_jxMake_UMLNOTE_enum_list_GENCODE_to_enum_headerfile(of));


	it = g_pDocTargetFile->BaseI()->begin();
	of<<_jT("namespace nMech { namespace nNET {\n");

	of<<_jF("namespace n%1%")% g_szName_HEADER_NameSpace;
	of<<_jT("{");

	//UMLNOTE enum list 출력
	if(eEnumList.full())
	{
		AddTab();
		eEnumList->for_each_child(_jxMake_UMLNOTE_enum_list_to_enum_headerfile(of));
		DecTab();
	}

	// protocal enum 출력
	AddTab();
	of<<_jF("enum E%1%") % g_szName_HEADER_NameSpace;
	of<<_jT("{");


	jIE* pePROTOCAL_LIST = g_pDocTargetFile->Find(PROTOCAL_LIST);
	AddTab();
	{

		of<<_jF("PT_VERSION	= /*nMech::nNET::EProtocal_jINet_OGS_END+*/%1%,")%szVer;

		pePROTOCAL_LIST->for_each_child(_jxWriteEnumFile(of,jA(sProtocalEnum)));

		of<<_jF("PT_%1%_END") % g_szName_HEADER_NameSpace;

	}
	DecTab();
	of<<_jF("};//enum E%1%\n") % g_szName_HEADER_NameSpace;

	pePROTOCAL_LIST->for_each_child(_jxMake_call_sq_func(of));
	of<<endl;

	of<<_jF("#ifndef %1%") % GET_VAR(jNOT_USE_PACKET_PLUGIN_HELP);
	of<<_jF("\textern PT_%1%_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList;") %
		g_szName_HEADER_NameSpace;
	of<<_jF("#endif // %1%\n") % GET_VAR(jNOT_USE_PACKET_PLUGIN_HELP);

#ifdef jOLD_STYLE_PACKET
	of<<_jF("#include \"%1%\"")% sStructureFileName.c_str();
	of<<_jF("#include \"%1%\"")% sReadPacketFileName.c_str();
	of<<_jF("#include \"%1%\"")% sWritePacketFileName.c_str();
#endif

	DecTab();
	of<<_jT("");
	of<<_jF("}//n%1%") %g_szName_HEADER_NameSpace;

	of<< _jT("}/* nNET*/ } //nMech");
	of<<endl;

#ifndef jOLD_STYLE_PACKET
	of<<_jF("#ifndef %1%") % GET_VAR(jNOTUSE_PACKET_HPP_INCLUDE);
	g_pDocTargetFile->Find(jS(PROTOCAL_LIST))->for_each_child(_jxWrite_include_packetHeader(of));
	of<<_jF("#endif // %1%") % GET_VAR(jNOTUSE_PACKET_HPP_INCLUDE);
#endif

}
