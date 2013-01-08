/* file : make_packet_header_file.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-21 10:28:09
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jMake_jINet_OGS_xml.h"
using namespace nMake_Xml;


void _make_struct_mystring_set_get(tofstream &of, jIE* itC)
{
	AddTab();
	AddTab();
	AddTab();

	// my_string에 대한 set get함수생성
	jIVar* pvT = itC->GetAttrVar(jS(TYPE));
	jIVar* pvLen = itC->GetAttrVar(_T("Length"));
	if(pvLen)
	{
		if(pvLen->Get_int()>0)
		{
			if(is_char_type(pvT) )
			{
			}
		}
	}
	else
	{
		if(is_mystring_type(pvT))
		{
			fname_t sz1;
			jt_strcpy(sz1, pvT->Get_cstr() );
			TCHAR* sz = jt_strchr(sz1,'_');
			*sz = 0;
			sz = sz1+5;
			int str_len = jt_atoi(sz);
			tcstr funca=_T("a");
			tcstr funcA=_T("A");
			if(sz1[0]==_T('t'))
			{
				funca = _T("t");
				funcA = _T("T");
			}
			else if(sz1[0] == 'w')
			{
				funca = _T("w");
				funcA = _T("W");
			}
			
			fname_t szLen;
			jt_sprintf(szLen,_T("%d"),str_len);

			of<<_jF("void set_%1%(tcstr sz){j%3%_strncpy(%1%,nUNI::scb1024_t(sz).get%4%(), %2%);	%1%[%2%-1]=0;}") 
				% itC->GetTagName() % szLen % funca % funcA;
			of<< _jF("tcstr get_%2%(fname_t _buf){jt_strncpy(_buf, nUNI::scb%1%_t(%2%).getT() , %1%);_buf[%1%-1]=0;return _buf;}") 
				% szLen % itC->GetTagName();
			//of<< _jF("net_string%1% _sq_get_%2%(){return net_string%1%(nUNI::scb%1%_t(%2%).getT());}") % str_len % itC->GetTagName();
		}
	}
	DecTab();
	DecTab();
	DecTab();

}//void _make_struct_mystring_set_get(tofstream &of, jIE* itC)

static void _make_packet_struct_mamber(tofstream& of,jIE* it, jIE* itC,tcstr sz123)
{
	tcstr szHelp = itC->GetAttr(_T("HELP"));
	jIVar* pvLen = itC->GetAttrVar(_T("Length"));
	tcstr szType =itC->GetAttr(_T("TYPE"));
	jIVar* pvT = itC->GetAttrVar(jS(TYPE));

	if(szHelp)
	{
		of<<_jF("/*[[ %1% ]]*/")%szHelp;
	}
	if(pvLen)
	{
		if(pvLen->Get_int()>0)
		{
			fname_t sz123;jt_sprintf(sz123 , _T("%d"),pvLen->Get_int());
			of<<_jF("%1% %2%[%3%];") % szType % itC->GetTagName() % sz123;

			of<<_jF("#ifndef jNOT_USE_PACKET_SET_GET_FUNC_%1%") % g_szName_HEADER_NameSpace;
			{
				if(pvT->IsContents(jS(CHAR)) || pvT->IsContents(jS(WCHAR)) )
				{
					if(pvT->IsContents(jS(WCHAR)))
					{
						of<<_jF("tcstr \tget_%1%(){ static TCHAR buf[%2%];jt_strcpy(buf,nUNI::scb1024_t(%1%).getT()); return buf;}")
							% itC->GetTagName() % sz123;
						of<<_jF("void \tset_%1%(tcstr sz){ jw_strcpy(%1%,nUNI::scb1024_t(sz).getW());}")
							% itC->GetTagName();
					}
					else
					{
						of<<_jF("tcstr \tget_%1%(){ static TCHAR buf[%2%];jt_strcpy(buf,nUNI::scb1024_t(%1%).getT()); return buf;}")
							% itC->GetTagName() % sz123;
						of<<_jF("void \tset_%1%(tcstr sz){ ja_strcpy(%1%,nUNI::scb1024_t(sz).getA());}")
							% itC->GetTagName();
					}
				}
				else if(pvT->IsContents(jS(TCHAR)))
				{
					of<<_jF("tcstr \tget_%1%(){ return %1%;}") % itC->GetTagName();
					of<<_jF("void \tset_%1%(tcstr sz){ jt_strncpy(%1%, sz,%2%-1); %1%[%2%-1]=0; }") % itC->GetTagName() % sz123;
				}
				else
				{
					if(jt_strstr(pvT->Get_cstr(), jS(net_string)) || jt_strstr(pvT->Get_cstr(), jS(string))  )
					{
						of<<_jF("tcstr get_%2%(int i){ return %2%[i];}") % szType % itC->GetTagName();
						of<<_jF("void \tset_%2%(int i, tcstr v){ %2%[i] = v;}") % szType % itC->GetTagName();
					}
					else
					{
						of<<_jF("%1%* get_%2%(int i){ return &%2%[i];}") % szType % itC->GetTagName();
						of<<_jF("void \tset_%2%(int i, %1%* v){ %2%[i] = *v;}") % szType % itC->GetTagName();
					}
					of<<_jF("size_t capacity_%2%(){ return %1%;}") % sz123 % itC->GetTagName();
				}
			}
			of<<_jF("#endif //jNOT_USE_PACKET_SET_GET_FUNC_%1%") % g_szName_HEADER_NameSpace;

		}
		else
		{
			tcstr szType2 = szType;
			bool is_tcstr=false;
			if(jt_strstr(szType,jS(tstring)) )
			{
				szType2 = jS(tcstr);
				is_tcstr = true;
			}
			of<<_jF("std::vector<%1%> %2%;") % szType % itC->GetTagName();

			of<<_jF("#ifndef jNOT_USE_PACKET_SET_GET_FUNC_%1%") % g_szName_HEADER_NameSpace;
			{
				if(is_tcstr )
				{
					of<<_jF("tcstr get_%2%(int i){ return %2%[i].c_str();}") % szType2 % itC->GetTagName();
					of<<_jF("void \tset_%2%(int i, tcstr v){ %2%[i] = v;}") % szType2 % itC->GetTagName();
					of<<_jF("void insert_%2%(tcstr v){ %2%.push_back(v);}") % szType2 % itC->GetTagName();
				}
				else
				{
					of<<_jF("%1%* get_%2%(int i){ return &%2%[i];}") % szType2 % itC->GetTagName();
					of<<_jF("void \tset_%2%(int i, %1%* v){ %2%[i] = *v;}") % szType2 % itC->GetTagName();
					of<<_jF("void insert_%2%(%1%* v){ %2%.push_back(*v);}") % szType2 % itC->GetTagName();
				}

				of<<_jF("void clear_%2%(){ %2%.clear();}") % szType % itC->GetTagName();
				of<<_jF("size_t size_%2%(){ return %2%.size();}") % sz123 % itC->GetTagName();

			}
			of<<_jF("#endif //jNOT_USE_PACKET_SET_GET_FUNC_%1%") % g_szName_HEADER_NameSpace;
		}
	}
	else
	{
		of<<_jF("%1% %2%;") % szType % itC->GetTagName();
		of<<_jF("#ifndef jNOT_USE_PACKET_SET_GET_FUNC_%1%") % g_szName_HEADER_NameSpace;
		{
			_make_struct_mystring_set_get(of,itC);
		}
		of<<_jF("#endif //jNOT_USE_PACKET_SET_GET_FUNC_%1%") % g_szName_HEADER_NameSpace;
	}
	of<<endl;

}


static void _make_packet_struct_DebugPrint(tofstream& of, jIE* it)
{
	of<<_jF("void DebugPrint(bool isPrintAll)");
	of<<_jT("{");
	{
		AutoTab a;
		of<<_jF("using namespace nMech::nInterface;");

		jIVar* pv = it->GetAttrVar(_T("DebugPrint"));
		int debugMode = g_bDebugPrint;
		if(pv) debugMode = pv->Get_int();
		if(g_bDebugPrint==3 || !debugMode)
		{
			of<<_jF("jLOG(_T(\"< %1% > =\"));") % it->GetTagName();
		}
		of<<_jT("if(!isPrintAll)return;");

		jIE* itC = it->begin();
		jrFOR(itC)
		{
			jIVar* pvLen = itC->GetAttrVar(_T("Length"));
			cstr szType = itC->GetAttr(_T("TYPE"));
			of<<_jF("jDebugPrint(_T(\"%1%\"),%2%);") % itC->GetTagName() % itC->GetTagName();
		}
	}
	of<<_jF("}");

}

static void _make_READ_PACKET(tofstream &of, jIE* it)
{
	of<<_jT("");
	of<<_jF("inline bool READ_%1%(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_%1% &param)") % it->GetTagName();
	of<<_jT("{");
	{
		AutoTab a;
		of<<_jT("try{");
		of<<_jT("nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);\n");

		jIE* itC = it->begin();
		jrFOR(itC)
		{
			jIVar* pvLen = itC->GetAttrVar(_T("Length"));
			jIVar* pvT = itC->GetAttrVar(_T("TYPE") );
			if(pvLen)
			{
				if(pvLen->Get_int()>0)
				{
					fname_t sz123;jt_sprintf(sz123 , _T("%d"),pvLen->Get_int());
					if(is_char_type(pvT))
					{
						of<<_jF("nStream::Read(st,param.%1%, %2%);") %itC->GetTagName()% sz123;
					}
					else
					{
						of<<_jF("nStream::ReadArray<%1%>(st,param.%2%, %3%);")
							%itC->GetAttr(_T("TYPE"))%itC->GetTagName() %sz123;
					}
				}
				else
				{
					of<<_jF("nMech::uint16 tempSize%1%;")%itC->GetTagName();
					of<<_jF("nStream::Read(st,tempSize%1%);")%itC->GetTagName();
					of<<_jF("param.%1%.resize(tempSize%1%);")%itC->GetTagName();
					of<<_jF("for(nMech::uint16 iTemp%1%=0;iTemp%1%<tempSize%1%; ++iTemp%1%){")%itC->GetTagName();
					of<<_jF("nStream::Read(st,param.%2%[iTemp%2%]);")%itC->GetAttr(_T("TYPE"))%itC->GetTagName();
					of<<_jF("}");
				}
			}
			else
			{
				if(is_mystring_type(pvT) )
				{
					fname_t sz1;
					jt_strcpy(sz1, pvT->Get_cstr() );
					TCHAR* sz = jt_strchr(sz1,'_');
					*sz = 0;
					sz = sz1+5;
					int str_len = jt_atoi(sz);
					fname_t szLen;
					jt_sprintf(szLen,_T("%d"),str_len);

					of<<_jF("nStream::Read(st,param.%1%, %2%);") %itC->GetTagName()% szLen;
				}
				else
					of<<_jF("nStream::Read(st,param.%1%);") % itC->GetTagName();
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
			//of<<_jF("jLOG_T(_T(\"[%1%:%2%]\"));")%g_szName_HEADER_NameSpace%it->GetTagName();
			of<<_jT("\tif(pS)pS->DebugPrint();");
			of<<_jT("\tparam.DebugPrint(true);") ;
			of<<_jT("#endif") ;
		}
		else if(debugMode)
		{
			of<<_jT("");
			of<<_jF("#ifndef jNOT_USE_DebugPrint_%1%")%g_szName_HEADER_NameSpace;
			of<<_jF("IF_jILogLT(jx(%1%),jx(%2%))\t{\t\t")%g_szName_HEADER_NameSpace%it->GetTagName();
			//of<<_jF("jLOG_T(_T(\"[%1%:%2%]\"));")%g_szName_HEADER_NameSpace%it->GetTagName();
			of<<_jT("if(pS)pS->DebugPrint();");
			of<<_jF("param.DebugPrint(%1%);")% (debugMode==2? _T("true"):_T("false"));
			of<<_jT("}" );
			of<<_jT("#endif");
		}
		else
		{
		}

		of<<_jT("if(st.GetCurrPos()>data_size) throw _T(\"st.GetCurrPos()>data_size\");")  ;
		of<<_jF("}catch(tcstr sz){jWARN_T(\"%1% : %2% (data_size=%3% \" , sz,data_size); return false;}") 
			% it->GetTagName() % _T("%s") % _T("%u");
		of<<_jT("return true;");
	}
	of<<_jT("}");
}//static void _make_READ_PACKET(tofstream &of, jIE* it)

static void _make_WRITE_PACKET(tofstream& of, jIE* it)
{
	of<<_jF("inline jPacket_Base WRITE_%1%(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_%1% &param)")%it->GetTagName();
	of<<_jT("{");
	{
		AutoTab a;
		of<<_jT("try{");
		{
			AutoTab a;
			of<<_jT("nMech::nNET::nStream::jNetStreamWrite st(buffer);");

			jIE* itC = it->begin();
			jrFOR(itC)
			{
				jIVar* pvLen = itC->GetAttrVar(_T("Length"));
				if(pvLen)
				{
					fname_t sz123;jt_sprintf(sz123 , _T("%d"),pvLen->Get_int());
					if(pvLen->Get_int() > 0)
					{
						jIVar* pvT = itC->GetAttrVar(_T("TYPE") );
						if(pvT->IsContents(jS(CHAR))  || pvT->IsContents(_T("WCHAR")) || pvT->IsContents(_T("TCHAR")))
						{
							of<<_jF("nStream::Write(st,param.%1%);")%itC->GetTagName() ;
						}
						else
						{
							of<<_jF("nStream::WriteArray<%1%>(st,param.%2%, %3%);")% itC->GetAttr(_T("TYPE"))% itC->GetTagName() % sz123;
						}
					}
					else
					{
						of<<_jF("nMech::uint16 tempSize%1%= (nMech::uint16)param.%1%.size();")%itC->GetTagName();
						of<<_jF("nStream::Write(st,tempSize%1%);")%itC->GetTagName();
						of<<_jF("for(nMech::uint16 iTemp%1%=0;iTemp%1%<tempSize%1%; ++iTemp%1%){") %itC->GetTagName();
						of<<_jF("nStream::Write(st,param.%2%[iTemp%2%]);")%itC->GetAttr(_T("TYPE"))%itC->GetTagName();
						of<<_jF("}");
					}
				}
				else
				{
					of<<_jF("nStream::Write(st,param.%1%);") % itC->GetTagName() ;
				}
				tcstr szHelp = itC->GetAttr(_T("HELP"));
				if(szHelp)
				{
					of<<_jF("/*[[ %1% ]]*/") % szHelp;
				}
			}

			of<<_jT("if(st.size()>st.capacity() ) throw _T(\"st.size()>st.capacity\");");

			of<<_jT("");
			of<<_jF("jPacket_Base pk; pk.num = pk_%1%;") % it->GetTagName();
			of<<_jT("pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;");		
		}//of<<_jT("try{");
		of<<_jF("}catch(tcstr sz){ jERROR(_T(\" %1% :data overflow: %2%\"),sz); }")% it->GetTagName() % jS(%s);
		of<<_jF("catch(nStream::jNetStreamWrite_error i){ jERROR(_T(\" %1% :overflow: (curr=%2%d,capa=%2%d,size=%2%d)\"),i.currLen,i.capa , i.isize); }")% it->GetTagName() % jS(%);
		of<<_jT("jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;");
	}
	of<<_jT("};");

	of<<_jT("");
	//--------------------------------------------------------------------------
	of<<_jF("inline jPacket_Base WRITE_%1%(nNET::nStream::_jNetStreamWriteBufferBase &buffer ")%it->GetTagName();
	//--------------------------------------------------------------------------
	jIE* itC = it->begin();
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
			if(is_mystring_type(pvT))
			{
				fname_t sz1;
				jt_strcpy(sz1, pvT->Get_cstr() );
				of<<__jF(",  %1%cstr _%2%")% sz1[0] %itC->GetTagName();
			}
			else
			{
				if(jt_strchr(pvT->Get_cstr(),'*'))
				{
					of<<__jF(", const %1% _%2%")% pvT->Get_cstr() %itC->GetTagName();
				}
				else
				{
					of<<__jF(", const %1% &_%2%")% pvT->Get_cstr() %itC->GetTagName();
				}
			}
		}
	}
	of<<_T(")" );

	of<<_jT("{");
	{ // jPacket_Base WRITE_%1%()의 바디 시작
		AutoTab a;
		of<<_jT("try{");
		{
			AutoTab a;

			of<<_jT("nMech::nNET::nStream::jNetStreamWrite st(buffer);");
			itC = it->begin();
			jrFOR(itC)
			{
				jIVar* pvLen = itC->GetAttrVar(_T("Length"));
				if(pvLen)
				{
					fname_t sz123;jt_sprintf(sz123 , _T("%d"),pvLen->Get_int());
					if(pvLen->Get_int()>0)
					{
						jIVar* pvT = itC->GetAttrVar(_T("TYPE") );
						if(pvT->IsContents(jS(CHAR) ) || pvT->IsContents(_T("WCHAR") ) || pvT->IsContents(_T("TCHAR") ) )
						{
							of<<_jF("nStream::Write(st,_%1%);") % itC->GetTagName();
						}
						else
						{
							of<<_jF("nStream::WriteArray<%1%>(st,_%2%, %3%);")
								% itC->GetAttr(_T("TYPE"))% itC->GetTagName() %sz123;
						}
					}
					else
					{
						of<<_jF("nMech::uint16 tempSize%1% = (nMech::uint16)_%1%.size();")%itC->GetTagName();
						of<<_jF("nStream::Write(st,tempSize%1%);")%itC->GetTagName();
						of<<_jF("for(nMech::uint16 iTemp%1%=0;iTemp%1%<tempSize%1%; ++iTemp%1%){")%itC->GetTagName();
						of<<_jF("nStream::Write(st,_%2%[iTemp%2%]);")%itC->GetAttr(_T("TYPE"))%itC->GetTagName();
						of<<_jT("}");

					}
				}
				else
				{
					of<<_jF("nStream::Write(st,_%1%);") % itC->GetTagName() ;
				}
				tcstr szHelp = itC->GetAttr(_T("HELP"));
				if(szHelp)
				{
					of<<_jF("/*[[ %1% ]]*/")%szHelp;
				}
			}//jrFOR(itC)
		}//of<<_jT("try{");
		
		of<<_jT("if(st.size()>st.capacity() ) throw _T(\"st.size()>st.capacity\");");
		of<<_jT("");
		of<<_jF("jPacket_Base pk; pk.num = pk_%1%;")%it->GetTagName();
		of<<_jT("pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;") ;

		of<<_jF("}catch(tcstr sz){ jERROR(_T(\" %1% :data overflow: %2%\"),sz); }")% it->GetTagName() % jS(%s);
		of<<_jF("catch(nStream::jNetStreamWrite_error i){ jERROR(_T(\" %1% :overflow: (curr=%2%d,capa=%2%d,size=%2%d)\"),i.currLen,i.capa , i.isize); }")% it->GetTagName() % jS(%);
		of<<_jT("jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;");

	}//// jPacket_Base WRITE_%1%()의 바디 끝

	of<<_jT("};\n");
}//void _make_WRITE_PACKET(tofstream& of, jIE* it)


struct _jxGen_Packet_Header_file
{
	_jxGen_Packet_Header_file(){}

	void operator ()(jIE* it)
	{
		tstring sFile = tstring(it->GetTagName()) + _T(".hpp");
		tofstream of(jA(sFile));	of.imbue(locale(jA(pv_file_locale->Get_cstr())));


		//of<< _jF("// make : %1%") % _T(__TIMESTAMP__);
		of<<_jF("#ifndef %1%___%2%__ \n#define %1%___%2%__") % g_szName_HEADER_NameSpace % it->GetTagName();
		of<< endl;

		//--------------------------------------------------------------------------
		// jxDECL 문 출력
		//--------------------------------------------------------------------------
		of<<_jF("#ifndef %1%") % GET_VAR(jNOTUSE_PACKET_JXDEFINE);

		if(g_isPrint_jxDEFINE )
			of<<_jF("jxDECL_%1%(%1%);") %g_szName_HEADER_NameSpace;

		jIVar* pvDD = it->GetAttrVar(_T("jxDEFINE"));
		bool isPo = !pvDD || pvDD->Get_bool();
		if(g_isPrint_jxDEFINE && isPo)
			of<<_jF("jxDECL_%1%(%2%);") % g_szName_HEADER_NameSpace %it->GetTagName();

		of<<_jF("#endif //%1%") % GET_VAR(jNOTUSE_PACKET_JXDEFINE);
		of<< endl;


		//--------------------------------------------------------------------------
		// ENUM상수 출력
		//--------------------------------------------------------------------------
		of<<_jF("namespace nMech { namespace nNET { namespace n%1%")% g_szName_HEADER_NameSpace;
		of<<_jT("{");
		cstr szVer = g_pDocTargetFile->BaseI()->GetAttr(_T("VERSION"));
		AddTab();
		{
			//패킷 도움말 출력
			tcstr sz123= it->GetAttr(_T("HELP"));
			if(sz123)
			{
				tstring sHelp= sz123;
				tstring sRep = m_sTabBuf + _T("$%^&*");
				nSTL::replace(sHelp,_T("\n"),sRep);
				nSTL::replace(sHelp,_T("$%^&*"),_T("\n"));

				of<<_jF("/*[[ %1% ]]*/") % sHelp;
			}

			jIVar* pvCustomNumber = it->GetAttrVar(jS(CustomNumber));
			// 패킷 번호 출력
			if(pvCustomNumber)
			{
				name_t buf;
				jt_sprintf(buf, _T("%u"), pvCustomNumber->Get_uint());
				of<<_jF("const int pk_%1% = %2%;") % it->GetTagName() % buf;
			}
			else
			{
				of<<_jF("const int pk_%1% = /*nMech::nNET::EProtocal_jINet_OGS_END+*/%2%+%3%;") 
					% it->GetTagName() % szVer % (it->GetOrder()+1);
			}

			//패킷 인자 도움말 출력
			jIE* itC = it->begin();
			jrFOR(itC)
			{
				cstr szTy12 = itC->GetAttr(_T("TYPE"));
				jIVar* pvLen = itC->GetAttrVar(_T("Length"));
				cstr tag = itC->GetTagName();
				if(pvLen)
				{
					fname_t sz123;jt_sprintf(sz123 , _T("%d"),pvLen->Get_int());
					of<<_jF("/* %1% %2%[%3%];*/")% szTy12 %tag   %sz123;
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



			//--------------------------------------------------------------------------
			// 구조체 출력
			//--------------------------------------------------------------------------
			of<<_jF("struct S_%1%;") % it->GetTagName();
			of<<_jF("bool READ_%1%(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_%1% &param);") % it->GetTagName();

			of<<_jF("struct S_%1%") %it->GetTagName();
			of<<_jT("{");
			AddTab();
			{
				jIE* itC = it->begin();
				jrFOR(itC)
				{
					_make_packet_struct_mamber(of,it,itC,sz123);
				}//jrFOR(itC)
				of<<endl;


#if 1
				// debugger 출력용 프린트
				of<<_jF("#ifndef jNOT_USE_DebugPrint_%1%") % g_szName_HEADER_NameSpace;
				{
					_make_packet_struct_DebugPrint(of, it);
				}
				of<<_jT("#endif //jNOT_USE_DebugPrint_");

#endif

				of<<_jT("void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)");
				of<<_jT("{");
				{	
					AutoTab a;
					of<<_jF("READ_%1%(pS,pk->GetLen(),pk->buf,*this);") % it->GetTagName();
				}
				of<<_jT("}");

			}
			DecTab();
			of<<_jT("};");

			//--------------------------------------------------------------------------
			// read packet 함수 구현
			//--------------------------------------------------------------------------
			of<<_jF("#ifndef jNOT_USE_PACKET_READ_FUNC_%1%") % g_szName_HEADER_NameSpace;
			{
				_make_READ_PACKET(of,it);
			}
			of<<_jF("#endif //jNOT_USE_PACKET_READ_FUNC_%1%") % g_szName_HEADER_NameSpace;

			//--------------------------------------------------------------------------
			// write packet 함수 구현
			//--------------------------------------------------------------------------
			of<<endl;

			of<<_jF("#ifndef jNOT_USE_PACKET_WRITE_FUNC_%1%") % g_szName_HEADER_NameSpace;
			{
				_make_WRITE_PACKET(of,it);
			}
			of<<_jF("#endif //jNOT_USE_PACKET_WRITE_FUNC_%1%") % g_szName_HEADER_NameSpace;
		}
		DecTab();
		of<<endl;
		of<<_jF("}/*n%1% */ }/* nNET*/ } //nMech") %g_szName_HEADER_NameSpace;
		of<<_jF("#endif //%1%___%2%__") % g_szName_HEADER_NameSpace % it->GetTagName();

	}

};



void make_packet_header_file(int argc, _TCHAR* argv[])
{
	ClearTab();
	nFileSystem::jFolder dir(false);
	dir.CreateDirForce(g_szName_HEADER_NameSpace);
	dir.Goto(g_szName_HEADER_NameSpace);
	g_pDocTargetFile->Find(jS(PROTOCAL_LIST))->for_each_child(_jxGen_Packet_Header_file());
}


