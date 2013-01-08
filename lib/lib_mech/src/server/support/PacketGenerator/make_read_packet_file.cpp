/* file : make_read_packet_file.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-17 19:17:33
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jMake_jINet_OGS_xml.h"
#include "interface/jIConsoleVar.h"

using namespace nMake_Xml;


//--------------------------------------------------------------------------
struct _jxWriteReadPacket
	//--------------------------------------------------------------------------
{
	tofstream& of;
	_jxWriteReadPacket(tofstream& fp1):of(fp1){ }
	void operator ()(jIE* it)
	{
		if(_write_CODE(of, it, _T("READ_FILE")) )		return ;
		of<<_jT("");
		tcstr szHelp = it->GetAttr(_T("HELP"));
		if(szHelp)
		{
			of<<_jF("/*\t[[ %1% ]]*/")%szHelp;
		}

		of<<_jF("inline void READ_%1%(BYTE *buffer, S_%1% &param)") % it->GetTagName();
		of<<_jT("{");
		AddTab();
		{
			of<<_jT("nMech::nNET::nUTIL::CStream st;");
			of<<_jT("st.SetBuffer(buffer);\n");

			jIE* itC = it->begin();
			jrFOR(itC)
			{
				jIVar* pvLen = itC->GetAttrVar(_T("Length"));
				if(pvLen)
				{
					fname_t sz123;jt_sprintf(sz123 , _T("%d"),pvLen->Get_int());

					if(pvLen->Get_int()>0)
					{
						if(itC->GetAttrVar(_T("TYPE") )->IsContents(_T("CHAR") ))
						{
							of<<_jF("nMech::uint16 %1%_len_=0; st.Read<nMech::uint16>(&%1%_len_); assert(%1%_len_<%2%);") 
								%itC->GetTagName()% sz123;
							of<<_jF("st.ReadArray<CHAR>(param.%1%, %1%_len_); param.%1%[%1%_len_]=0;")% itC->GetTagName();
						}
						else if(itC->GetAttrVar(_T("TYPE") )->IsContents(_T("WCHAR")))
						{
							of<<_jF("nMech::uint16 %1%_len_=0; st.Read<nMech::uint16>(&%1%_len_);assert(%1%_len_<%2%);") 
								% itC->GetTagName() % sz123;
							of<<_jF("st.ReadArray<WCHAR>(param.%1%, %1%_len_); param.%1%[%1%_len_]=0;")%itC->GetTagName();
						}
						else
						{
							of<<_jF("st.ReadArray<%1%>(param.%2%, %3%);")
								%itC->GetAttr(_T("TYPE"))%itC->GetTagName() %sz123;
						}
					}
					else
					{
						of<<_jF("nMech::uint16 tempSize%1%;")%itC->GetTagName();
						of<<_jF("st.Read<nMech::uint16>(&tempSize%1%);")%itC->GetTagName();
						of<<_jF("param.%1%.resize(tempSize%1%);")%itC->GetTagName();
						of<<_jF("for(nMech::uint16 iTemp%1%=0;iTemp%1%<tempSize%1%; ++iTemp%1%){")%itC->GetTagName();
						of<<_jF("\tStream.Read<%1%>(&param.%2%[iTemp%2%]);")%itC->GetAttr(_T("TYPE"))%itC->GetTagName();
						of<<_jF("}");
					}
				}
				else
				{
					of<<_jF("st.Read<%1%>(&param.%2%);") % itC->GetAttr(_T("TYPE")) % itC->GetTagName();
				}
				tcstr szHelp = itC->GetAttr(_T("HELP"));
				if(szHelp)
				{
					of<<_jF("/*\t[[ %1% ]]*/") %szHelp;
				}
			}
			jIVar* pv = it->GetAttrVar(_T("DebugPrint"));
			int debugMode = g_bDebugPrint;
			if(pv) debugMode = pv->Get_int();

			if(g_bDebugPrint == 3)
			{
				of<<_jT("");
				of<<_jF("#ifndef jNOT_USE_DebugPrint_%1%")%g_szName_HEADER_NameSpace;
				of<<_jT("\tparam.DebugPrint(true);") ;
				of<<_jT("#endif") ;
			}
			else if(debugMode)
			{
				of<<_jT("");
				of<<_jF("#ifndef jNOT_USE_DebugPrint_%1%"),g_szName_HEADER_NameSpace;
				of<<_jF("IF_jILogTest2(jx(%1%),jx(%2%))\t{\t\t")%g_szName_HEADER_NameSpace%it->GetTagName();
				of<<_jF("param.DebugPrint(%1%);")% (debugMode==2? _T("true"):_T("false"));
				of<<_jT("}" );
				of<<_jT("#endif");
			}
			else
			{
			}

			of<<_jT("assert(st.GetLength()<=nMech::nNET::MAX_BUFFER_LENGTH);")  ;

		}
		DecTab();
		of<<_jT("}");
	}
};//struct _jxWriteReadPacket

void make_read_packet_file(int argc, _TCHAR* argv[])
{
	jIE* it;
	tofstream of(jA(sReadPacketFileName));
	//of<<_jF("//from(%1%)\n//TIME= %1%\n"), argv[ARG_HEADER_XML_FILE],szCurrentFileName);
	of<<_jF("//from(%1%)")%argv[ARG_HEADER_XML_FILE];

	of<<_jT("#pragma once\n") ;
	it = g_pDocTargetFile->BaseI()->begin();
	jrFOR(it)
	{
		if(_write_CODE(of, it, _T("READ_FILE") )	 )
			continue;
		if(it->IsName(PROTOCAL_LIST))
		{
			//of<<_jF("namespace n%1%\n{"),g_szName_HEADER_NameSpace );
			it->for_each_child(_jxWriteReadPacket(of));
			//of<<_jF("};\n"), g_szName_HEADER_NameSpace );
		}
	}
}


