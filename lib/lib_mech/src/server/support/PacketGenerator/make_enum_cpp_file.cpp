/* file : make_enum_cpp_file.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-17 18:28:09
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jMake_jINet_OGS_xml.h"
#include "interface/jIConsoleVar.h"

using namespace nMake_Xml;

bool is_char_type(jIVar* pvT)
{
	return pvT->IsContents(jS(CHAR)) || pvT->IsContents(jS(WCHAR)) 	|| pvT->IsContents(jS(TCHAR));
}
bool is_mystring_type(jIVar* pV)
{
	tcstr sz = pV->Get_cstr();
	if(!jt_strncmp(sz, jS(aname) , jt_strlen(jS(aname))) ) return true;
	if(!jt_strncmp(sz, jS(tname) , jt_strlen(jS(tname))) ) return true;
	if(!jt_strncmp(sz, jS(wname) , jt_strlen(jS(wname))) ) return true;
	return false;
}
struct _jxMake_WritePacket
{
	tofstream &of;
	_jxMake_WritePacket(tofstream& of1): of(of1){}
	void operator()(jIE*it)
	{

		of<< _jF("static void _S_%1%_WritePacket(S_%1%* pThis, jIPacketSocket_IOCP* pS)") % it->GetTagName() ;
		of<< _jF("{");
		{AutoTab a;
		of<<_jF("nswb%1%_t sendBuf; ") % pv_ScriptSide_SendBufSize->Get_cstr();
		of<<__jF("pS->WritePacket(&WRITE_%2%(sendBuf,*pThis));") % g_szName_HEADER_NameSpace % it->GetTagName();
		}
		of<<_jF("}");

		of<< _jF("static void _S_%1%_WriteToPacket(S_%1%* pThis, jIPacketSocket_IOCP* pS,jIP_Address* pIP)") % it->GetTagName();
		of<< _jF("{");
		{AutoTab a;
		of<<_jF("nswb%1%_t sendBuf; ") % pv_ScriptSide_SendBufSize->Get_cstr();
		of<<__jF("pS->WriteToPacket(pIP,&WRITE_%2%(sendBuf,*pThis));") % g_szName_HEADER_NameSpace % it->GetTagName();
		}
		of<<_jF("}");

		of<<_jF("void call_sq_%1%(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP)") % it->GetTagName();
		of<<_jT("{");
		{AutoTab a;
			of<<_jT("SquirrelObject* pO = (SquirrelObject*)v;");
			of<<_jF("S_%1% param;") % it->GetTagName();
			of<<_jF("SquirrelFunction<void> func(*pO,_T(\"jNET_EVENT_%1%\"));")	 % it->GetTagName();
			of<<_jF("if(!func.func.IsNull()) func(pS,pk,pIP,&param);");
		}
		of<<_jT("}");

		jIE* itC = it->begin();
		jrFOR(itC)	
		{
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

					of<<_jF("jSQ_gfn_DEF2(SquirrelObject, S_%2% , get_%3%)(S_%2%* pThis)") % str_len % it->GetTagName() % itC->GetTagName();
					of<<_jT("{");
					AddTab();
					of<<_jF("fname_t buf;return (pThis->get_%2%(buf));") % str_len % itC->GetTagName();
					DecTab();
					of<<_jT("}");

				}

			}
		}//jrFOR(itC)	구조체의 변수들



		//of<< _jF("int del_%1%(SQUserPointer up, SQInteger size){SQ_DELETE_CLASS(S_%1%);}")								% it->GetTagName();
		//of<< _jF("int	new_%1%(HSQUIRRELVM v)\n\t\t{return PostConstruct<S_%1%>(v,new S_%1%(),del_%1%);}")		% it->GetTagName();

		of<<endl;
	}
};


struct _jxMakeLuaRegist
{
	tofstream &of;
	_jxMakeLuaRegist(tofstream& of1): of(of1){}
	void operator()(jIE*it)
	{
		of<< _jF("jSQ_Class(S_%1%)") % it->GetTagName();
		AddTab();
		//of<<_jF("jSQ_gfn(S_%1%,Send,\"\",\"\")") % it->GetTagName();
		jIE* itC = it->begin();
		jrFOR(itC)	
		{
			jIVar* pvT = itC->GetAttrVar(jS(TYPE));
			jIVar* pvLen = itC->GetAttrVar(_T("Length"));
			if(pvLen)
			{
				if(pvLen->Get_int()>0)
				{
					if(is_char_type(pvT) )
					{
						of<<_jF("jSQ_fn(get_%1%,\"\",\"tcstr\")" ) % itC->GetTagName();
						of<<_jF("jSQ_fn(set_%1%,\"tcstr sz\",\"\")" ) % itC->GetTagName();
					}
					else
					{
						of<<_jF("jSQ_fn(get_%1%,\"int i\",\"return %2%*\")" ) % itC->GetTagName() % pvT->Get_cstr();
						of<<_jF("jSQ_fn(set_%1%,\"int i,%2%* v\",\"\")" ) % itC->GetTagName() % pvT->Get_cstr();
						of<<_jF("jSQ_fn(capacity_%1%,\"\",\"return size_t\")" ) % itC->GetTagName();
					}
				}
				else
				{
					of<<_jF("jSQ_fn(get_%1%,\"int i\",\"return %2%*\")" ) % itC->GetTagName() % pvT->Get_cstr();
					of<<_jF("jSQ_fn(set_%1%,\"int i,%2%* data\",\"\")" ) % itC->GetTagName() % pvT->Get_cstr();
					of<<_jF("jSQ_fn(insert_%1%,\"%2%* data\",\"\")" ) % itC->GetTagName() % pvT->Get_cstr();
					of<<_jF("jSQ_fn(clear_%1%,\"\",\"\")" ) % itC->GetTagName();
					of<<_jF("jSQ_fn(size_%1%,\"\",\"return size_t\")" ) % itC->GetTagName();
				}
			}
			else
			{
				if(is_mystring_type(pvT))
				{
					of<<_jF("jSQ_gfn(S_%1%,get_%2%, \"\",\"return net_string\")") % it->GetTagName() % itC->GetTagName();
					of<<_jF("jSQ_fn(set_%1%,\"tcstr sz\",\"\")" ) % itC->GetTagName();
				}
				else
					of<<_jF("jSQ_var(%1%,\"%2%\")") % itC->GetTagName() % pvT->Get_cstr();
			}
		}
		of<<_jF("jSQ_gfn(S_%1%,WritePacket,\"jIPacketSocket_IOCP* pS\",\"\")") % it->GetTagName() ;
		of<<_jF("jSQ_gfn(S_%1%,WriteToPacket,\"jIPacketSocket_IOCP* pS,jIP_Address *pIP\",\"\")") % it->GetTagName() ;
		of<<_jF("jSQ_fn(ReadPacket,\"jIPacketSocket_IOCP* pS,jPacket_Base* pk\",\"\")") ;
		of<<_jF("jSQ_fn(DebugPrint,\"bool isPrintAll\",\"\")") ;

		//of<<_jF("jSQ_sgfn(new_%1%, \"constructor\", \"\")") % it->GetTagName();
		DecTab();
		of<<_jT("jSQ_end();");
		of<< endl;
	}
};

//--------------------------------------------------------------------------
void make_enum_cpp_file(tstring &sEnumCppFileName ,int argc, _TCHAR* argv[])
//--------------------------------------------------------------------------
{
	jIE* itC;

	tofstream of(jA(sEnumCppFileName));
	of.imbue(locale(jA(pv_file_locale->Get_cstr())));

	jIE* pePROTOCAL_LIST = g_pDocTargetFile->Find(jS(PROTOCAL_LIST));
	of<<_jF("//from(%1%)\n") % argv[ARG_HEADER_XML_FILE];
	of<<_jT("#include \"stdafx.h\"") ;
	of<<_jT("#include \"interface/net/jPlugInHelpTable.h\"");


	tstring sProtocalEnum= tstring(argv[ARG_CREATE_TAG])+ tstring(_T("_")) + g_szName_HEADER_NameSpace + _T("_Enum.h");
	of<<_jF("#include \"%1%\"\n\n")%sProtocalEnum;

	jIE* peCode = g_pDocTargetFile->Find(jS(CODE));

	
	if(peCode&& jt_strlen(peCode->Get_cstr()))
	{
		of<<_jF("#include \"%1%\"") % peCode->Get_cstr();
	}


	if(pv_Use_Squirrel->Get_bool())
	{
		of<< endl;

		of<<_jF("#ifndef %1%") % GET_VAR(jNOTUSE_SQ_CODE);
		of<<_jF("using namespace nMech::nNET::n%1%;") % g_szName_HEADER_NameSpace;
		itC = pePROTOCAL_LIST->begin();
		jrFOR(itC)
		{
			of<<_jF("DECLARE_INSTANCE_TYPE(S_%1%);") % itC->GetTagName();
		}
		of<<_jF("#endif // %1%")% GET_VAR(jNOTUSE_SQ_CODE);
		of<<endl;
	}


	of<<_jF("namespace nMech{ namespace nNET	{ namespace n%1%") % g_szName_HEADER_NameSpace;
	of<<_jT("{");
	{
		AddTab();
		//--------------------------------------------------------------------------
		// PlugIn help table문 출력 
		of<<_jF("PT_%1%_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList=0;") %g_szName_HEADER_NameSpace;
		of<<endl;

		//if(g_bDebugPrint)
		{
			if(pv_Use_Squirrel->Get_bool())
			{
				of<<_jF("#ifndef %1%")%GET_VAR(jNOTUSE_SQ_CODE);
				pePROTOCAL_LIST->for_each_child(_jxMake_WritePacket(of));
				of<<_jF("#endif //%1%")%GET_VAR(jNOTUSE_SQ_CODE);
				of<<endl;
			}

			of<<_jF("jONCE_RUN_CTOR(__%1%__)") %g_szName_HEADER_NameSpace;
			of<<_jT("{");
			AddTab();

			of<<_jF("static jNamedEventTable_impl phtl;");
			itC = pePROTOCAL_LIST->begin();
			jrFOR(itC)
			{
				fname_t szThread;
				tcstr thread_name = itC->GetAttr(jS(thread_name));
				if(!thread_name) 
				{
					jt_strcpy_s(szThread,_T("0"));
				}
				else
				{
					jt_sprintf(szThread , _T("jS(%s)") , thread_name);
				}
				of<<_jF("phtl.Insert(%1%,jS(%1%),%2%);") % itC->GetTagName() % szThread;
			}
			of<<endl;
			of<<_jT("g_pPlugInHelpTableList = &phtl;");
			
			of<<_jF("nMech::jBase::RegistNamedPointer(_T(\"nNET\"),_T(\"%1%\"),g_pPlugInHelpTableList);")%g_szName_HEADER_NameSpace;
			itC = pePROTOCAL_LIST->begin();
			jrFOR(itC)
			{
				of<<_jF("jRAISE_PACKET(pk_%1% == %1%);") % itC->GetTagName();
			}
			of<<endl;

			if(pv_Use_Squirrel->Get_bool())
			{
				of<<_jF("#ifndef %1%")%GET_VAR(jNOTUSE_SQ_CODE);
				pePROTOCAL_LIST->for_each_child(_jxMakeLuaRegist(of));
				of<<_jF("#endif //%1%")%GET_VAR(jNOTUSE_SQ_CODE);
				of<<endl;
			}

			DecTab();
			of<<_jT("}");
			of<<_jF("jONCE_RUN_DTOR(__%1%__)") %g_szName_HEADER_NameSpace;
			of<<_jT("{");
			of<<_jF("nMech::jBase::UnRegistNamedPointer(_T(\"nNET\"),_T(\"%1%\"));")%g_szName_HEADER_NameSpace;
			of<<_jT("}");

			of<< endl;

		}

		of<<endl;
		DecTab();
	}
	of<<_jF("}/* n%1% */ }/*nNET*/ } //nMech\n\n") % g_szName_HEADER_NameSpace;
	DecTab();
	

	//--------------------------------------------------------------------------
	// jxDEFINE문 출력
	of<<_jF("#ifndef %1%") % GET_VAR(jNOT_USE_PACKET_PLUGIN_HELP);
	if(!g_pv_jxDEFINE || g_pv_jxDEFINE->Get_bool())
		of<<_jF("jxDEFINE_%1%(%1%);") % g_szName_HEADER_NameSpace;

	itC = pePROTOCAL_LIST->begin();
	jrFOR(itC)
	{
		jIVar* pvDD = itC->GetAttrVar(_T("jxDEFINE") );
		if(g_isPrint_jxDEFINE && (!pvDD || pvDD->Get_bool() ) ) 
			of<<_jF("jxDEFINE_%1%(%2%);") % g_szName_HEADER_NameSpace %itC->GetTagName();
	}
	of<<_jF("#endif // %1%") % GET_VAR(jNOT_USE_PACKET_PLUGIN_HELP);

	if(pv_Use_Squirrel->Get_bool())
	{
		//make_enum_cpp_SQ_file(argc,argv);
	}
}


