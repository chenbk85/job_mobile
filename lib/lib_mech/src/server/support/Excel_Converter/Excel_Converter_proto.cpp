#include "stdafx.h"
#include "Excel_Converter.h"

namespace excel_util
{

	cstr get_proto_type(cstr szType)
	{
		if(szType[0]=='E')
			return jS(int32);

		static jIE* peDEFAULT_PROTO_TYPE_LIST = nGLOBAL::g_pDocApp->Find(jS(DEFAULT_CSHAP_TYPE_LIST));
		jASSERT0(peDEFAULT_PROTO_TYPE_LIST);
		jIE * pE = peDEFAULT_PROTO_TYPE_LIST->Find(szType);
		static std::map<tstring ,tstring> s_get_cshap_type_Cache;
		if(!pE) 
		{
			if(jt_strncmp(szType,jS(Sys_),4)==0)
			{
				return jS(int32);
			}
			if(jt_strncmp(szType,jS(Tbl_),4)==0)
			{
				return jS(int64);
			}

			fname_t szN ;
			jt_strcpy(szN,szType);
			size_t iLen = jt_strlen(szN);
			if(	szType[iLen-4]=='_' 
				&& szType[iLen-3]=='p' 
				&& szType[iLen-2]=='t' 
				&& szType[iLen-1]=='r' 
				)
			{
				szN[iLen-4]=0;
				tstring sNewType = get_proto_type(szN);
				pE = peDEFAULT_PROTO_TYPE_LIST->Persist(szType,sNewType.c_str());
				return pE ? pE->GetAttr(jS(PROTO_TYPE)) : 0;
			}
			TCHAR* sz = jt_strstr(szN,jS(_ptr_vec));
			if(sz)
			{
				*sz=0;
				fname_t buf;
				tstring sNewType = get_proto_type(szN);
				jt_sprintf(buf,_T("List<%s>"),sNewType.c_str());
				s_get_cshap_type_Cache[szType] = buf;
				return s_get_cshap_type_Cache[szType].c_str();
			}

			if(	szType[iLen-4]=='_' 
				&& szType[iLen-3]=='v' 
				&& szType[iLen-2]=='e' 
				&& szType[iLen-1]=='c' 
				)
			{
				szN[iLen-4]=0;
				fname_t buf;
				tstring sNewType = get_proto_type(szN);
				jt_sprintf(buf,_T("List<%s>"),sNewType.c_str());
				s_get_cshap_type_Cache[szType] = buf;
				return s_get_cshap_type_Cache[szType].c_str();
			}
			return szType;
		}
		return pE ? pE->GetAttr(jS(PROTO_TYPE)) : 0;
	}

}//namespace excel_util


void Excel_Converter::make_file_proto()
{
	filesystem::tpath  saveFile(m_save_file_path);
	saveFile /= (m_FileName + jS(.proto) );
	tofstream of(jA(saveFile.string()));

	of << _jFF("// command line : %1%\n\n") %GetCommandLine();
	of << endl;

	static jIVar* pv_LITE_RUNTIME= jCV(proto,LITE_RUNTIME,false,0,"is use  : option optimize_for = LITE_RUNTIME");
	if(pv_LITE_RUNTIME->Get_bool())
	{
		of << _jFF("option optimize_for = LITE_RUNTIME;\n\n");
	}

	//구조체 출력.
	make_file_proto_struct(of, jS(Tbl));
	make_file_proto_struct(of, jS(App));

	of << _jTT("\n\n");

	of.close();

}

void Excel_Converter::_make_file_proto_cshap_contract_code_FIELD( IN OUT  int &idx ,jIE* peTable, tofstream & of )
{
	jIE* peField = peTable->begin();
	jrFOR(peField)
	{
		cstr name = jC5(peField,name);
		cstr help = jC5(peField,help);
// 		if(is_inherit_node(peField))
// 		{
// 			continue;
// 		}

		jIE* peInherit = nInherit::find_Field_Inherit_Table(peField);
		if(peInherit)
		{
			//jLOG_T("peField : %s, peTable=%s : peInherit=%s size=%d", peField->GetTagName(),peTable->GetTagName(),peInherit->GetTagName() , peInherit->size());
			AutoTab a(this);
			_make_file_proto_cshap_contract_code_FIELD(idx , peInherit, of);
			continue;
		}

		++idx;
		cstr szType = excel_util::get_cshap_type(jC5(peField,data_type)) ;
		if(tstring(jS(optional))==pv_PROTO_MEMBER_OPTION->Get_cstr() )
		{
			of << _jFF("[ProtoMember(%1%, IsRequired = false)]") % idx;
		}
		else
		{
			of << _jFF("[ProtoMember(%1% ,IsRequired = true)]") % idx;
		}

		if(szType[0]=='E')
		{
			szType = jS(int);
		}
		else if(tstring(jS(DATETIME))==szType)
		{
			szType = jS(string);
		}

		jIVar* pvLength = peField->GetAttrVar(jS(Length));
		jLIST_TYPEDEF_map(tstring,tstring,ctor_list);
		if(pvLength)
		{
			of << _jFF("public List<%1%> m_%2% {get; set;}\t// [%3%] %4% ")
				% szType
				% peField->GetTagName() 
				% help 
				% jC5(peField,data_type) 
				;
			ctor_list[ peField->GetTagName() ] = szType;

		}
		else
		{
			of << _jFF("public %1% m_%2% {get; set;}\t// [%3%] %4% ")
				% szType
				% peField->GetTagName() 
				% help 
				% jC5(peField,data_type) 
				;
		}

		if(ctor_list.size())
		{
			ctor_list_it it =ctor_list.begin() ,ie = ctor_list.end();
			for(;it!=ie;++it)
			{
				of << _jFF("public %1%()") % peTable->GetTagName();
				of << _jFF("{");
				of << _jFF("\t%1% = new List<%2%>();") % it->first % it->second;
				of << _jFF("}");
			}
		}
	}

}

void Excel_Converter::_make_file_proto_cshap_contract_code_help(  tofstream & of, cstr szStruct)
{
	//구조체 출력.
	jE eSys = m_eDoc(szStruct);
	if(eSys.empty()) return;


	jIE* peTable  = eSys->begin();
	jrFOR(peTable)
	{
		AutoTab a(this);

		fname_t szT;
		jt_sprintf(szT,_T("s_%s"),peTable->GetTagName());
		jt_strlwr(szT);


		of << _jFF("//------------------------------------------------");
		of << _jFF("//	%1%") % szT;
		of << _jFF("//------------------------------------------------");
		of << _jFF("public static byte[] Serialize(%1% m) ") %szT ;
		of << _jFF("{");
		of << _jFF("	byte[] b = null;");
		of << _jFF("	using (var ms = new MemoryStream())");
		of << _jFF("	{");
		of << _jFF("		%1% protoSerializer = new %1%();")% pv_PROTO_BUF_SERIALIZER_NAME_FOR_IPHONE->Get_cstr();
		of << _jFF("		protoSerializer.Serialize(ms, m);");
		of << _jFF("		b = new byte[ms.Position];");
		of << _jFF("		var fullB = ms.GetBuffer();");
		of << _jFF("		Array.Copy(fullB, b, b.Length);");
		of << _jFF("	}");
		of << _jFF("	return b;");
		of << _jFF("}");
		of << _jFF("public static void Deserialize(ref %1% m, byte[] serializationBytes)")%szT ;
		of << _jFF("{");
		of << _jFF("	using (var ms = new MemoryStream(serializationBytes))");
		of << _jFF("	{");
		of << _jFF("		%1% psz = new %1%();") % pv_PROTO_BUF_SERIALIZER_NAME_FOR_IPHONE->Get_cstr();
		of << _jFF("		m = psz.Deserialize(ms, null, typeof(%1%)) as %1%;")%szT ;
		of << _jFF("	}");
		of << _jFF("}");
		of << _jFF("public static void Decoding_FromSocketData(ref %1% m, byte[] socketData)")%szT;
		of << _jFF("{");
		of << _jFF("	int iSize = 0;");
		of << _jFF("	byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);");
		of << _jFF("	Deserialize(ref m, recvData);");
		of << _jFF("}");

		of << _jFF("\n\n");
	}//jrFOR(peTable)


}


void Excel_Converter::_make_file_proto_cshap_contract_code_STRUCT(  tofstream & of, cstr szStruct,cshap_contract_type_list_t& type_list)
{
	//구조체 출력.
	jE eSys = m_eDoc(szStruct);
	if(eSys.empty()) return;


	jIE* peTable  = eSys->begin();
	jrFOR(peTable)
	{
		AutoTab a(this);

		fname_t szT;
		jt_sprintf(szT,_T("s_%s"),peTable->GetTagName());
		jt_strlwr(szT);
		type_list.insert(szT);
		Print_Title(of, peTable->GetAttr(jS(HELP)) );

		of << _jFF("[ProtoContract]");
		of << _jFF("public class %1%") % szT ;
		of << _jFF("{");

		cstr szNew=_T("");
		{
			AutoTab a(this);

			int idx=0;
// 			{
// 				std::vector<nXML::jE> out;
// 				nInherit::get_Inherit_Info(out, peTable);
// 				{
// 					AutoTab b(this);
// 
// 					for(size_t iOut=0; iOut< out.size() ; ++iOut)
// 					{
// 						jIE* peBaseTable = out[iOut];
// 						jIE* peField = peBaseTable->begin();
// 						_make_file_proto_cshap_contract_code_FIELD(idx,peBaseTable,of);
// 					}
// 				}
// 			}

			_make_file_proto_cshap_contract_code_FIELD(idx,peTable, of);

		}
		of << _jFF("}//public class %1%\n") % szT;
		of << _jFF("\n\n");
	}//jrFOR(peTable)


}

void Excel_Converter::make_file_proto_cshap_contract_code_help_cs()
{
	//prot.help.cs 생성. 시리얼라이즈/디시리얼라이즈 함수.
	filesystem::tpath  saveFile(m_save_file_path);
	saveFile /= (m_FileName + jS(.proto.excel.help.cs) );
	tofstream of(jA(saveFile.string()));

	of << _jFF("// THIS CODE IS USED FOR unity3d + google protocal buffer + c# + iphone");
	//of << _jFF("// www.frictionpointstudios.com/blog/2011/3/31/using-protobuf-net-serialization-in-unity-iphone.html");
	//of << _jFF("// code.google.com/p/protobuf-net/downloads/detail?name=iDevice%20alpha%201.zip");
	of << _jFF("// by icandoit@neowiz.com");

	of << _jFF("// command line : %1%\n\n") %GetCommandLine();
	of << endl;

	{
		static jIE* pePROTO_CONTRACT_NAMESPACE = nGLOBAL::g_pDocApp->Find(jS(PROTO_CONTRACT_NAMESPACE));
		jRETURN(pePROTO_CONTRACT_NAMESPACE);
		jIE* pE = pePROTO_CONTRACT_NAMESPACE->begin();
		jrFOR(pE)
		{
			of << _jFF("using %1%;")% pE->Get_cstr();
		}
	}
	of << _jFF("using System.Runtime.Serialization;");
	of << _jFF("using System.IO;\n");



	of << _jTT("// above code is created by app_xml <PROTO_CONTRACT_NAMESPACE>");
	of << _jTT("");
	of << _jTT("");

	of << _jFF("namespace %1%") % g_Excel_Converter->m_Namespace;
	//of << _jFF("namespace nPROTO");
	of << _jTT("{");
	{
		AutoTab a(this);
		of << _jFF("public class %1%_proto_helper") %m_FileName;
		of << _jFF("{");
		{
			AutoTab b(this);
			_make_file_proto_cshap_contract_code_help(of,jS(Tbl));
			_make_file_proto_cshap_contract_code_help(of,jS(Sys));
		}
		of << _jFF("}//class %1%_proto_helper") %m_FileName;
	}

	of << _jFF("}// namespace %1%") % g_Excel_Converter->m_Namespace;
	//of << _jFF("}// namespace nPROTO");
	of << _jTT("\n\n");

	of.close();

}
void Excel_Converter::make_file_proto_cshap_contract_code()
{
	filesystem::tpath  saveFile(m_save_file_path);
	saveFile /= (m_FileName + jS(.proto_contract.cs) );
	tofstream of(jA(saveFile.string()));

	of << _jFF("// THIS CODE IS USED FOR unity3d + google protocal buffer + c# + iphone");
	//of << _jFF("// www.frictionpointstudios.com/blog/2011/3/31/using-protobuf-net-serialization-in-unity-iphone.html");
	//of << _jFF("// code.google.com/p/protobuf-net/downloads/detail?name=iDevice%20alpha%201.zip");
	of << _jFF("// by icandoit@neowiz.com");

	of << _jFF("// command line : %1%\n\n") %GetCommandLine();
	of << endl;

	{
		static jIE* pePROTO_CONTRACT_NAMESPACE = nGLOBAL::g_pDocApp->Find(jS(PROTO_CONTRACT_NAMESPACE));
		jRETURN(pePROTO_CONTRACT_NAMESPACE);
		jIE* pE = pePROTO_CONTRACT_NAMESPACE->begin();
		jrFOR(pE)
		{
			of << _jFF("using %1%;")% pE->Get_cstr();
		}
	}
	of << _jTT("// above code is created by app_xml <PROTO_CONTRACT_NAMESPACE>");
	of << _jTT("");
	of << _jTT("");

	of << _jFF("namespace %1%") % g_Excel_Converter->m_Namespace;
	//of << _jFF("namespace nPROTO");
	of << _jTT("{");



	{
		AutoTab a(this);
		of << _jTT("\n");
		of << _jTT("//TYPE_INFO_NS");
		nXML::jE e = g_eTYPE_INFO_NS(jS(min_max_type));
		if(e.empty())
		{
			jWARN(_T("g_eTYPE_INFO_NS(jS(min_max_type)) == NULL : %s" ) , g_eTYPE_INFO_NS->GetTagName());
		}
		else
		{
			make_file_cshap_using(of, e);
		}
		of << _jTT("\n\n");
	}


	cshap_contract_type_list_t type_list;
	_make_file_proto_cshap_contract_code_STRUCT(of,jS(Tbl),type_list);
	_make_file_proto_cshap_contract_code_STRUCT(of,jS(Sys),type_list);
	jE eEnum = m_eDoc(jS(enum));
	if(eEnum.full())
	{
		jIE* it = eEnum->begin();
		jrFOR(it)
		{
			type_list.insert(it->GetTagName());
		}
	}

	{
		AutoTab a(this);
		of << _jFF("public class %1%_proto_contract") % m_FileName ;
		of << _jFF("{");
		of << _jFF("	public static ArrayList GetTypes()");
		of << _jFF("	{");
		of << _jFF("		ArrayList list = new ArrayList();");
		of << _jFF("		");

		cshap_contract_type_list_it it = type_list.begin(),ie = type_list.end();
		for(;it!=ie; ++it)
		{
			of << _jFF("		list.Add(typeof(%1%));") % *it;
		}

		of << _jFF("		return list;");
		of << _jFF("	}");
		of << _jFF("}");

	}

	of << _jFF("}// namespace %1%") % g_Excel_Converter->m_Namespace;
	//of << _jFF("}// namespace nPROTO");
	of << _jTT("\n\n");

	of.close();
}


void Excel_Converter::_make_file_proto_struct_field( IN OUT  int &idx ,jIE* peTable, tofstream & of )
{
	jIE* peField = peTable->begin();
	jrFOR(peField)
	{

		jIE* peInherit = nInherit::find_Field_Inherit_Table(peField);
		if(peInherit)
		{
			//jLOG_T("peField : %s, peTable=%s : peInherit=%s size=%d", peField->GetTagName(),peTable->GetTagName(),peInherit->GetTagName() , peInherit->size());
			AutoTab a(this);
			_make_file_proto_struct_field(idx , peInherit, of);
			continue;
		}

		cstr name = jC5(peField,name);
		cstr help = jC5(peField,help);
		++idx;
		cstr szType = get_proto_type(jC5(peField,data_type)) ;
		of << _jFF("%6% %1% %2% = %7%; \t// %5% [%3%] %4% ") % szType
			% peField->GetTagName() % name % help %jC5(peField,data_type) % pv_PROTO_MEMBER_OPTION->Get_cstr()
			% idx;
	}
}

//구조체 출력.
void Excel_Converter::make_file_proto_struct(tofstream &of,cstr szStruct)
{
	jE eSys = m_eDoc(szStruct);
	if(eSys.empty()) return;
	jIE* peTable  = eSys->begin();
	jrFOR(peTable)
	{
		fname_t szT;
		jt_strcpy(szT,peTable->GetTagName());
		jt_strlwr(szT);
		Print_Title(of, peTable->GetAttr(jS(HELP)) );

		of << _jFF("message s_%1%") % szT ;
		of << _jFF("{");

		cstr szNew=_T("");
		{
			AutoTab a(this);

 			int idx=0;
// 			{
// 				std::vector<nXML::jE> out;
// 				nInherit::get_Inherit_Info(out, peTable);
// 				{
// 					AutoTab b(this);
// 
// 					for(size_t iOut=0; iOut< out.size() ; ++iOut)
// 					{
// 						jIE* peBaseTable = out[iOut];
// 						jIE* peField = peBaseTable->begin();
// 						_make_file_proto_struct_field(idx,peBaseTable,of);
// 					}
// 				}
// 			}

			_make_file_proto_struct_field(idx,peTable, of);

		}
		of << _jFF("}//massage s_%1%\n") % szT;
		of << _jFF("\n\n");
	}//jrFOR(peTable)

}