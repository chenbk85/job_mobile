/* file : make_write_packet_file.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-17 19:29:50
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jMake_jINet_OGS_xml.h"
#include "interface/jIConsoleVar.h"

using namespace nMake_Xml;

//--------------------------------------------------------------------------
struct _jxWriteWritePacket
	//--------------------------------------------------------------------------
{
	tofstream& of;
	_jxWriteWritePacket(tofstream& fp1):of(fp1){ }
	void operator ()(jIE* it)
	{
		if(_write_CODE(of, it, _T("WRITE_FILE") ) )		return ;

		of<<_jT("//==========================================================");
		tcstr szHelp = it->GetAttr(_T("HELP"));
		if(szHelp)
		{
			of<<_jF("/*\t[[ %1% ]]*/")%szHelp;
		}
		jIE* itC ;
		of<<_jF("inline jPacket_Base WRITE_%1%(BYTE *buffer, S_%1% &param)")%it->GetTagName();
		of<<_jT("{");
		AddTab();
		{
			of<<_jT("nMech::nNET::nUTIL::CStream st;st.SetBuffer(buffer);");

			itC = it->begin();
			jrFOR(itC)
			{
				jIVar* pvLen = itC->GetAttrVar(_T("Length"));
				if(pvLen)
				{
					fname_t sz123;jt_sprintf(sz123 , _T("%d"),pvLen->Get_int());

					if(pvLen->Get_int() > 0)
					{
						if(itC->GetAttrVar(_T("TYPE") )->IsContents(_T("CHAR")) )
						{
							of<<_jF("nMech::uint16 %1%_len_= (nMech::uint16)ja_strlen(param.%1%);")%itC->GetTagName();
							of<<_jF("assert(%1%_len_<%2%);")%itC->GetTagName()% sz123;
							of<<_jF("st.Write<nMech::uint16>(&%1%_len_);")%itC->GetTagName() ;
							of<<_jF("st.WriteArray<CHAR>(param.%1%, %1%_len_);")%itC->GetTagName();
						}
						else if(itC->GetAttrVar(_T("TYPE") )->IsContents(_T("WCHAR")))
						{
							of<<_jF("nMech::uint16 %1%_len_= (nMech::uint16)jw_strlen(param.%1%);")%itC->GetTagName();
							of<<_jF("assert(%1%_len_<%2%);") %itC->GetTagName()% sz123;
							of<<_jF("st.Write<nMech::uint16>(&%1%_len_);")%itC->GetTagName() ;
							of<<_jF("st.WriteArray<WCHAR>(param.%1%, %1%_len_);")%itC->GetTagName() ;
						}
						else
						{
							of<<_jF("st.WriteArray<%1%>(&param.%2%, %3%);")% itC->GetAttr(_T("TYPE"))% itC->GetTagName() % sz123;
						}
					}
					else
					{
						of<<_jF("nMech::uint16 tempSize%1%= (nMech::uint16)param.%1%.size();")%itC->GetTagName();
						of<<_jF("st.Write<nMech::uint16>(&tempSize%1%);")%itC->GetTagName();
						of<<_jF("for(nMech::uint16 iTemp%1%=0;iTemp%1%<tempSize%1%; ++iTemp%1%){") %itC->GetTagName();
						of<<_jF("st.Write<%1%>(&param.%2%[iTemp%2%]);")%itC->GetAttr(_T("TYPE"))%itC->GetTagName();
						of<<_jF("}");
					}
				}
				else
				{
					of<<_jF("st.Write<%1%>(&param.%2%);")% itC->GetAttr(_T("TYPE")) % itC->GetTagName();
				}
				tcstr szHelp = itC->GetAttr(_T("HELP"));
				if(szHelp)
				{
					of<<_jF("/*[[ %1% ]]*/") % szHelp;
				}
			}

			of<<_jT("");
			of<<_jF("jPacket_Base pk; pk.num = pk_%1%;") % it->GetTagName();
			of<<_jT("pk.buf=buffer;	 pk.len=(jPacketNum_t)st.GetLength();	return pk;");

		}
		DecTab();
		of<<_jT("};");

		of<<_jT("");
		//--------------------------------------------------------------------------
		of<<_jF("inline jPacket_Base WRITE_%1%(BYTE *buffer ")%it->GetTagName();
		//--------------------------------------------------------------------------
		itC = it->begin();
		jrFOR(itC)
		{
			jIVar* pvLen = itC->GetAttrVar(_T("Length"));
			jIVar* pvT = itC->GetAttrVar(jS(TYPE));
			if(pvLen)
			{
				if(pvLen->Get_int()>0)
				{
					of<<__jF(", const %1% *_%2%")% itC->GetAttr(_T("TYPE"))%itC->GetTagName();
				}
				else
				{
					of<<__jF(", const std::vector<%1%> &_%2%")% itC->GetAttr(_T("TYPE"))%itC->GetTagName();
				}
			}
			else
			{
				jIVar* pvT = itC->GetAttrVar(jS(TYPE));
				if(is_mystring_type(pvT))
				{
					fname_t sz1;
					jt_strcpy(sz1, pvT->Get_cstr() );
					of<<__jF(",  %1%cstr _%2%")% sz1[0] %itC->GetTagName();
				}
				else
					of<<__jF(", const %1% _%2%")% itC->GetAttr(_T("TYPE"))%itC->GetTagName();
			}
		}
		of<<_T(")" );

		of<<_jT("{");
		AddTab();
		{
			of<<_jT("nMech::nNET::nUTIL::CStream st;st.SetBuffer(buffer);");
			itC = it->begin();
			jrFOR(itC)
			{
				jIVar* pvLen = itC->GetAttrVar(_T("Length"));
				if(pvLen)
				{
					fname_t sz123;jt_sprintf(sz123 , _T("%d"),pvLen->Get_int());

					if(pvLen->Get_int()>0)
					{
						if(itC->GetAttrVar(_T("TYPE") )->IsContents(_T("CHAR") ) )
						{
							of<<_jF("nMech::uint16 %1%_len_= (nMech::uint16)ja_strlen(_%1%);")%itC->GetTagName();
							of<<_jF("assert(%1%_len_<%2%);")%itC->GetTagName() % sz123;
							of<<_jF("st.Write<nMech::uint16>(&%1%_len_);")%itC->GetTagName();
							of<<_jF("st.WriteArray<CHAR>(_%1%, %1%_len_);")%itC->GetTagName() ;
						}
						else if(itC->GetAttrVar(_T("TYPE") )->IsContents(_T("WCHAR")))
						{
							of<<_jF("nMech::uint16 %1%_len_= (nMech::uint16)jw_strlen(_%1%);")%itC->GetTagName();
							of<<_jF("assert(%1%_len_<%2%);")%itC->GetTagName()% sz123;
							of<<_jF("st.Write<nMech::uint16>(&%1%_len_);")%itC->GetTagName();
							of<<_jF("st.WriteArray<WCHAR>(_%1%, %1%_len_);")%itC->GetTagName() ;
						}
						else
						{
							of<<_jF("st.WriteArray<%1%>(_%2%, %3);")
								% itC->GetAttr(_T("TYPE"))% itC->GetTagName() %sz123;
						}
					}
					else
					{
						of<<_jF("nMech::uint16 tempSize%1% = (nMech::uint16)_%1%.size();")%itC->GetTagName();
						of<<_jF("st.Write<nMech::uint16>(&tempSize%1%);")%itC->GetTagName();
						of<<_jF("for(nMech::uint16 iTemp%1%=0;iTemp%1%<tempSize%1%; ++iTemp%1%){")%itC->GetTagName();
						of<<_jF("st.Write<%1%>(&_%1%[iTemp%1%]);")%itC->GetAttr(_T("TYPE"))%itC->GetTagName();
						of<<_jT("}");

					}
				}
				else
				{
					of<<_jF("st.Write<%1%>(&_%2%);")%itC->GetAttr(_T("TYPE"))%itC->GetTagName() ;
				}
				tcstr szHelp = itC->GetAttr(_T("HELP"));
				if(szHelp)
				{
					of<<_jF("/*[[ %1% ]]*/")%szHelp;
				}
			}
		}
		of<<_jT("");
		of<<_jF("jPacket_Base pk; pk.num = pk_%1%;")%it->GetTagName();
		of<<_jT("pk.buf=buffer;	 pk.len=(jPacketNum_t)st.GetLength();	return pk;") ;
		DecTab();
		of<<_jT("};\n");

	}//void operator ()(jIE* it)
};//struct _jxWriteWritePacket




void make_write_packet_file(int argc, _TCHAR* argv[])
{
	jIE* it;
	tofstream of(jA(sWritePacketFileName));
	//of<<_jF("//from(%1%)\n//TIME= %1%\n"), argv[ARG_HEADER_XML_FILE],szCurrentFileName);
	of<<_jF("//from(%1%)")%argv[ARG_HEADER_XML_FILE];

	of<<_jT("#pragma once\n") ;
	it = g_pDocTargetFile->BaseI()->begin();
	jrFOR(it)
	{
		if(_write_CODE(of, it, _T("WRITE_FILE") ) )		
			continue;
		if(it->IsName(PROTOCAL_LIST))
		{
			it->for_each_child(_jxWriteWritePacket(of));
		}
	}
}
