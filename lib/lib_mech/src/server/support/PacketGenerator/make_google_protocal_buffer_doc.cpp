/* file : make_google_protocal_buffer_doc.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2011-12-23 11:00:11
comp.: www.neowiz.com
title : 
desc : 

*/


#include "stdafx.h"
#include "jMake_jINet_OGS_xml.h"
#include "interface/jIConsoleVar.h"


namespace util
{
	void print_help_comment( tcstr sz, tofstream& of )
	{
		if(!sz) return;
		vector<tstring> out;
		nString::jSplit(sz,_T("\n\r"), out);
		for(size_t i=0;i<out.size();++i)
		{
			of<<_jF("//%1%") % out[i];
		}
	}



	tstring make_cshap_type(tstring sType)
	{
		nSTL::replace(sType,_T("uint") ,_T("UInt"));
		nSTL::replace(sType,_T("int") ,_T("Int"));
		return sType;
	}
	typedef bool is_skip_func_t(jIE* itC,void* p);
	static bool is_global_enum(jIE* itC,void*)
	{
		return itC->GetAttr(jS(SCOPE));
	}
	static bool is_scope_enum(jIE* itC,void*v)
	{
		jIVar* pV = itC->GetAttrVar(jS(SCOPE));
		if(!pV) return true;
		jIE* pE= (jIE*)v;
		if(!pV->IsContents(pE->GetTagName())) 
			return true;

		return false;
	}

	tcstr g_szPROTO_BUF_SERIALIZER_NAME_FOR_IPHONE=0;
	tcstr g_szMESSAGE_TAG=0;
	tcstr g_szMESSAGE_MEMEBER_TAG=0;
	tcstr g_szMEMBER_OPTOIN = 0;
	tcstr g_szMESSAGE_ENUM_TAG =0;


	static tcstr make_cshap_var(fname_t szVar)
	{
		//jt_strlwr(szVar);
		vector<tstring> out;
		nString::jSplit(szVar,_T("_"),out);
		szVar[0]=0;
		for(size_t i=0 ; i < out.size(); ++i)
		{
			out[i][0]= toupper(out[i][0]);
			jt_strcat(szVar, out[i].c_str());
		}
		return szVar;
	}

}
using namespace util;

jLIST_TYPEDEF_vector_typedef(jIE*,element_list);
jLIST_TYPEDEF_map_typedef(tstring,element_list_t,mapGROUP_TAG);

static void _print_google_proto_enum( jIE* peENUM_TYPE_LIST, tofstream& of,is_skip_func_t* is_skip_func,void* p)
{
	if(!peENUM_TYPE_LIST) return;
	jIE* itC;
	int idx=0;
	itC = peENUM_TYPE_LIST->begin();
	jrFOR(itC)
	{
		if(is_skip_func(itC,p))
			continue;
		tcstr sz = itC->GetAttr(jS(USD));
		if(sz) of<<_jF("//%1%") % sz;
		print_help_comment(itC->GetAttr(jS(HELP)), of);
		of<<_jF("enum %1% {") % itC->GetTagName();

		{
			AutoTab a;
			jIE* itVar= itC->begin();
			idx=-1;
			jrFOR(itVar)
			{
				if(idx==-1)
				{
					jIVar* pV = itVar->GetAttrVar(jS(val));
					if(pV)
						idx = pV->Get_int();
					else
						idx = 0;
				}
				tcstr sz = itVar->GetAttr(jS(HELP));
				if(sz)
				{
					of <<_jF("%1% = %2%; //%3%") % itVar->GetTagName() % (idx) % sz;
				}
				else
				{
					of <<_jF("%1% = %2%;") % itVar->GetTagName() % (idx);
				}
				++idx;
			}
		}
		of <<_jF("} // end of enum %1%\n") % itC->GetTagName();
	}
}

void _make_google_protobuf_cshop_net_cpp_header( tstring & _sProtoFileName, mapGROUP_TAG_t mapGROUP_TAG, int iVer )
{
	int idx=0;
	//#--------------------------------------------------------------------------
	// #define for_each문생성.
	//#--------------------------------------------------------------------------
	{
		//jMB("asdf","asdf");
		tstring sProto_foreach_file =  _sProtoFileName + _T(".proto.h");
		tofstream of2(jA(sProto_foreach_file));
		of2.imbue(locale(jA(pv_file_locale->Get_cstr())));

		mapGROUP_TAG_it itGROUP;
		jFOR(mapGROUP_TAG,itGROUP)
		{

			tcstr szTag = jt_strchr(itGROUP->first.c_str(),'.');
			++szTag;
			jASSERT(szTag);
			tstring sGROUP_NAME = tstring(szTag); //+ g_szName_HEADER_NameSpace;




			of2 << _jF("// X(DOMAIN,NAME,ORDER) ");
			of2 << _jF("#define for_each_%1%(X)\\") % sGROUP_NAME;
			{
				AutoTab a;
				{
					AutoTab a;
					element_list_it itEL;
					idx=2;
					jFOR(itGROUP->second,itEL)
					{
						jIE* pE = *itEL;
						of2 << _jF("X(%3%,%1%,%2%)\\") % pE->GetTagName() % (idx+iVer) % sGROUP_NAME;
						++idx;
					}
					of2 << endl;
				}

				of2 << "  " << endl << endl;
			}
		}

		// 구조체의 맴버변수들에 대한 for_each문
		jFOR(mapGROUP_TAG,itGROUP)
		{
			tcstr szTag = jt_strchr(itGROUP->first.c_str(),'.');
			++szTag;
			jASSERT(szTag);
			tstring sGROUP_NAME = tstring(szTag); //+ g_szName_HEADER_NameSpace;
			{
				AutoTab a;
				{
					AutoTab a;
					element_list_it itEL;
					jFOR(itGROUP->second,itEL)
					{
						jIE* pE = *itEL;

						cstr szUSD = pE->GetAttr(jS(USD));
						if(!szUSD) szUSD = jS(NULL);
						of2 << _jF("// X(STRUCT,ORDER,TYPE,MEMVER)  //%1%") % szUSD;
						of2 << _jF("#define for_each_%1%___%2%(X)\\") % sGROUP_NAME %  pE->GetTagName();

						jIE* it = pE->begin();
						idx=0;
						jrFOR(it)
						{
							of2 << _jF("X(%1%,%2%,%3%,%4%)\\") % pE->GetTagName() % (idx) 
								% it->GetAttr(jS(TYPE)) % it->GetTagName();
							++idx;
						}
						of2 << endl;
					}
					of2 << endl;
					of2 << endl;
				}

				of2 << "  " << endl << endl;
			}
		}

	}
}//int _make_google_protobuf_cshop_net_cpp_header( tstring & _sProtoFileName, mapGROUP_TAG_t mapGROUP_TAG, int idx, int iVer )



void _make_google_protobuf_cshap_net_help( tstring & _sProtoFileName, mapGROUP_TAG_t mapGROUP_TAG )
{
	//#--------------------------------------------------------------------------
	// PT_BaseballServer.proto.help.cs  c# 핼프코드 생성.
	//#--------------------------------------------------------------------------
	{
		//jMB("asdf","asdf");
		tstring sProto_foreach_file =  _sProtoFileName + _T(".proto_cshap_net.help.cs");
		tofstream of2(jA(sProto_foreach_file));
		of2.imbue(locale(jA(pv_file_locale->Get_cstr())));

		of2 << _jF("// 주의 http://code.google.com/p/protobuf-csharp-port/ 를 사용할때 쓰는 핼프코드 \n");

		of2 << _jF("using System;\n");

		of2 << _jF("namespace nPROTO");
		of2 << _jF("{");
		mapGROUP_TAG_it itGROUP;
		jFOR(mapGROUP_TAG,itGROUP)
		{
			tcstr szTag = jt_strchr(itGROUP->first.c_str(),'.');
			++szTag;
			jASSERT(szTag);
			tstring sGROUP_NAME = tstring(szTag); //+ g_szName_HEADER_NameSpace;


			of2 << _jF("    public class Helper_%1%") % sGROUP_NAME;
			of2 << _jF("	{");
			element_list_it itEL;
			jFOR(itGROUP->second,itEL)
			{
				jIE* pE = *itEL;
				of2 << _jF("		public static %1%%2% Make_%2%(") % g_szMESSAGE_TAG % pE->GetTagName();
				jIE* itVar= pE->begin();
				if(itVar)
				{
					of2 << __jF("%1% %2%") % util::make_cshap_type(itVar->GetAttr(jS(TYPE)) )% itVar->GetTagName();
					itVar=itVar->GetRight();
					jrFOR(itVar)
					{
						of2 << __jF(",%1% %2%") % util::make_cshap_type(itVar->GetAttr(jS(TYPE)) ) % itVar->GetTagName();
					}
				}
				of2 << __jF(")");
				of2 << _jF("		{");
				of2 << _jF("			return new %1%%2%.Builder()") % g_szMESSAGE_TAG % pE->GetTagName();
				itVar= pE->begin();
				jrFOR(itVar)
				{
					fname_t szMESSAGE_TAG2;
					jt_strcpy(szMESSAGE_TAG2,itVar->GetTagName());
					make_cshap_var(szMESSAGE_TAG2);
					of2 << _jF("				.Set%1%(%2%)") % szMESSAGE_TAG2 % itVar->GetTagName();
				}
				of2 << _jF("				.Build();");
				of2 << _jF("		}");

				//MReqPing1
				fname_t szMemberName;

				fname_t szMESSAGE_MEMEBER_TAG2;
				jt_strcpy(szMESSAGE_MEMEBER_TAG2, g_szMESSAGE_MEMEBER_TAG);
				if(jt_strlen(szMESSAGE_MEMEBER_TAG2))
				{
					make_cshap_var(szMESSAGE_MEMEBER_TAG2);
				}

				fname_t szMemberName2;
				jt_strcpy(szMemberName2 , pE->GetTagName());
				{
					make_cshap_var(szMemberName2);
				}

				jt_sprintf(szMemberName,_T("%s%s"),szMESSAGE_MEMEBER_TAG2 ,szMemberName2 );


				of2 << _jF("		public static %1% Build(%2%%3% v)") %sGROUP_NAME% g_szMESSAGE_TAG % pE->GetTagName();
				of2 << _jF("		{");
				of2 << _jF("			return new %1%.Builder().SetType(%1%.Types.Type.%2%).Set%3%(v).Build();")
					%sGROUP_NAME% pE->GetTagName() % szMemberName;
				of2 << _jF("		}");

				of2 << _jF("		public static %1% Build_%2%(")%sGROUP_NAME% pE->GetTagName();
				itVar = pE->begin();
				if(itVar)
				{
					of2 << __jF("%2% %1%") % itVar->GetTagName() % make_cshap_type(itVar->GetAttr(jS(TYPE)));
					itVar=itVar->GetRight();
					jrFOR(itVar)
					{
						of2 << __jF(",%2% %1%") % itVar->GetTagName() % make_cshap_type(itVar->GetAttr(jS(TYPE)));
					}
				}
				of2 << __jF(")");

				of2 << _jF("		{");
				of2 << _jF("			return Build(Make_%1%(")% pE->GetTagName();
				itVar = pE->begin();
				if(itVar)
				{
					of2 << __jF("%1%") % itVar->GetTagName();
					itVar=itVar->GetRight();
					jrFOR(itVar)
					{
						of2 << __jF(",%1%") % itVar->GetTagName();
					}
				}
				of2 << __jF("));");
				of2 << _jF("		}");

				of2 << endl << endl;
			}
			of2 << _jF("	}//class Helper_%1%")% sGROUP_NAME;
			of2 << endl << endl;


		}//jFOR(mapGROUP_TAG,itGROUP)
		of2 << _jF("}//namespace nPROTO");


	}//// PT_BaseballServer.proto.help.cs  c# 핼프코드 생성.
}//void _make_google_protobuf_cshap_net_help( tstring & _sProtoFileName, mapGROUP_TAG_t mapGROUP_TAG )


//http://code.google.com/p/protobuf-net/ 를 사용시.
void _make_google_protobuf_net_help( tstring & _sProtoFileName, mapGROUP_TAG_t mapGROUP_TAG )
{
	//#--------------------------------------------------------------------------
	// PT_BaseballServer.proto.help.cs  c# 핼프코드 생성.
	//#--------------------------------------------------------------------------
	{
		//jMB("asdf","asdf");
		tstring sProto_foreach_file =  _sProtoFileName + _T(".proto.help.cs");
		tofstream of2(jA(sProto_foreach_file));
		of2.imbue(locale(jA(pv_file_locale->Get_cstr())));

		of2 << _jF("// 주의 http://code.google.com/p/protobuf-net/ 를 사용할때 쓰는 핼프코드 \n");

		static jIE* pe_include_namespace= nUSD_FILE::g_pDocProtocalPrototype->Find(jS(protobuf_net))->Find(jS(include_namespace));
		{
			jIE* it = pe_include_namespace->begin();
			jrFOR(it)
			{
				of2 << _jF("using %1%; //from ProtocalPrototype.xml : protobuf_net : include_namespace") % it->Get_cstr();
			}
		}
		of2 << endl;

		tcstr szHEADER = g_pDocTargetFile->BaseI()->GetAttr(jS(HEADER)) ;
		//of2 << _jF("using PT_%1%;// from ProtocalDefine.xml \n") % szHEADER;

		//of2 << _jF("namespace %1%")% _sProtoFileName;
		of2 << _jF("namespace nPROTO");
		of2 << _jF("{");
		mapGROUP_TAG_it itGROUP;
		jFOR(mapGROUP_TAG,itGROUP)
		{
			tcstr szTag = jt_strchr(itGROUP->first.c_str(),'.');
			++szTag;
			jASSERT(szTag);
			tstring sGROUP_NAME = tstring(szTag); //+ g_szName_HEADER_NameSpace;


			of2 << _jF("    public partial class %1%")%_sProtoFileName;
			of2 << _jF("	{");
			element_list_it itEL;
			jFOR(itGROUP->second,itEL)
			{
				jIE* pE = *itEL;
				tcstr szMsg= pE->GetTagName();

				of2 << _jF("//////////////////////////////////////////////////");
				of2 << _jF("///#-- %1%") % szMsg;
				of2 << _jF("//////////////////////////////////////////////////");
				of2 << _jF("		public static %1%%2% Make_%2%(") % g_szMESSAGE_TAG % szMsg;
				jIE* itVar= pE->begin();
				if(itVar)
				{
					jIVar* pvLength = itVar->GetAttrVar(jS(Length));
					if(pvLength)
					{
						of2 << __jF("List<%1%> %2%") % util::make_cshap_type(itVar->GetAttr(jS(TYPE)) )% itVar->GetTagName();
					}
					else
					{
						of2 << __jF("%1% %2%") % util::make_cshap_type(itVar->GetAttr(jS(TYPE)) )% itVar->GetTagName();
					}

					itVar=itVar->GetRight();
					jrFOR(itVar)
					{
						jIVar* pvLength = itVar->GetAttrVar(jS(Length));
						if(pvLength)
						{
							of2 << __jF(",List<%1%> %2%") % util::make_cshap_type(itVar->GetAttr(jS(TYPE)) )% itVar->GetTagName();
						}
						else
						{
							of2 << __jF(",%1% %2%") % util::make_cshap_type(itVar->GetAttr(jS(TYPE)) )% itVar->GetTagName();
						}
					}
				}
				of2 << __jF(")");
				of2 << _jF("		{");
				of2 << _jF("			%1%%2% v = new %1%%2%();") % g_szMESSAGE_TAG % szMsg;
				itVar= pE->begin();
				jrFOR(itVar)
				{
					fname_t szMESSAGE_TAG2;
					jt_strcpy(szMESSAGE_TAG2,itVar->GetTagName());
					make_cshap_var(szMESSAGE_TAG2);
					of2 << _jF("			v.%2% = %2%;") % szMESSAGE_TAG2 % itVar->GetTagName();
				}
				of2 << _jF("			return v;");
				of2 << _jF("		}");

				//MReqPing1
				fname_t szMemberName;

				fname_t szMESSAGE_MEMEBER_TAG2;
				jt_strcpy(szMESSAGE_MEMEBER_TAG2, g_szMESSAGE_MEMEBER_TAG);
				if(jt_strlen(szMESSAGE_MEMEBER_TAG2))
				{
					make_cshap_var(szMESSAGE_MEMEBER_TAG2);
				}

				fname_t szMemberName2;
				jt_strcpy(szMemberName2 , szMsg);
				{
					make_cshap_var(szMemberName2);
				}

				jt_sprintf(szMemberName,_T("%s%s"),szMESSAGE_MEMEBER_TAG2 ,szMemberName2 );


				of2 << _jF("		public static %1% Build(%2%%3% v)") %sGROUP_NAME% g_szMESSAGE_TAG % szMsg;
				of2 << _jF("		{");
				of2 << _jF("			%1% v2 = new %1%();")%sGROUP_NAME;
 				of2 << _jF("			v2.type = %1%.Type.%2%;")%sGROUP_NAME% szMsg;
 				of2 << _jF("			v2.m_%2% = v;")%sGROUP_NAME% szMsg;
				of2 << _jF("			return v2;");
				of2 << _jF("		}");

				of2 << _jF("		public static %1% Build_%2%(")%sGROUP_NAME% szMsg;
				itVar = pE->begin();
				if(itVar)
				{
					jIVar* pvLength = itVar->GetAttrVar(jS(Length));
					if(pvLength)
					{
						of2 << __jF("List<%1%> %2%") % util::make_cshap_type(itVar->GetAttr(jS(TYPE)) )% itVar->GetTagName();
					}
					else
					{
						of2 << __jF("%1% %2%") % util::make_cshap_type(itVar->GetAttr(jS(TYPE)) )% itVar->GetTagName();
					}
					itVar=itVar->GetRight();
					jrFOR(itVar)
					{
						jIVar* pvLength = itVar->GetAttrVar(jS(Length));
						if(pvLength)
						{
							of2 << __jF(",List<%1%> %2%") % util::make_cshap_type(itVar->GetAttr(jS(TYPE)) )% itVar->GetTagName();
						}
						else
						{
							of2 << __jF(",%1% %2%") % util::make_cshap_type(itVar->GetAttr(jS(TYPE)) )% itVar->GetTagName();
						}
					}
				}
				of2 << __jF(")");

				of2 << _jF("		{");
				of2 << _jF("			return Build(Make_%1%(")% szMsg;
				itVar = pE->begin();
				if(itVar)
				{
					of2 << __jF("%1%") % itVar->GetTagName();
					itVar=itVar->GetRight();
					jrFOR(itVar)
					{
						of2 << __jF(",%1%") % itVar->GetTagName();
					}
				}
				of2 << __jF("));");
				of2 << _jF("		}");

				//#--------------------------------------------------------------------------
				// serialize , deserialize함수
				//#--------------------------------------------------------------------------
				AutoTab b,c;
				of2 << _jF("public static byte[] Serialize(%1%%2% m)") %g_szMESSAGE_TAG%szMsg;
				of2 << _jF("{");
				of2 << _jF("	byte[] b = null;");
				of2 << _jF("	using (var ms = new MemoryStream())");
				of2 << _jF("	{");
				of2 << _jF("		%1% protoSerializer = new %1%();")%g_szPROTO_BUF_SERIALIZER_NAME_FOR_IPHONE;
				of2 << _jF("		protoSerializer.Serialize(ms, m);");
				of2 << _jF("		b = new byte[ms.Position];");
				of2 << _jF("		var fullB = ms.GetBuffer();");
				of2 << _jF("		Array.Copy(fullB, b, b.Length);");
				of2 << _jF("	}");
				of2 << _jF("	return b;");
				of2 << _jF("}");
				of2 << _jF("public static void Deserialize(ref %1%%2% m, byte[] serializationBytes)")%g_szMESSAGE_TAG%szMsg;
				of2 << _jF("{");
				of2 << _jF("	using (var ms = new MemoryStream(serializationBytes))");
				of2 << _jF("	{");
				of2 << _jF("		%1% psz = new %1%();")%g_szPROTO_BUF_SERIALIZER_NAME_FOR_IPHONE;
				of2 << _jF("		m = psz.Deserialize(ms, null, typeof(%1%%2%)) as %1%%2%;")%g_szMESSAGE_TAG%szMsg;
				of2 << _jF("	}");
				of2 << _jF("}");
				of2 << _jF("public static void Decoding_FromSocketData(ref %1%%2% m, byte[] socketData)")%g_szMESSAGE_TAG%szMsg;
				of2 << _jF("{");
				of2 << _jF("	int iSize = 0;");
				of2 << _jF("	byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);");
				of2 << _jF("");
				of2 << _jF("	Deserialize(ref m, recvData);");
				of2 << _jF("}");
				of2 << _jF("");


				of2 << endl << endl;
			}//jFOR(itGROUP->second,itEL)
			of2 << _jF("	}//class %1%") %_sProtoFileName;
			of2 << endl << endl;


		}//jFOR(mapGROUP_TAG,itGROUP)
		of2 << _jF("}//namespace nPROTO");
		//of2 << _jF("}//namespace %1%") %_sProtoFileName;


	}//// PT_BaseballServer.proto.help.cs  c# 핼프코드 생성.
}//void _make_google_protobuf_net_help( tstring & _sProtoFileName, mapGROUP_TAG_t mapGROUP_TAG )




void _make_google_protobuf_net__contract_cs__group_message( mapGROUP_TAG_t &mapGROUP_TAG, tofstream &of,int iVer)
{
	AutoTab a;
	int idx;
	mapGROUP_TAG_it itGROUP;
	jFOR(mapGROUP_TAG,itGROUP)
	{
		tcstr szTag = jt_strchr(itGROUP->first.c_str(),'.');
		++szTag;
		jASSERT(szTag);
		tstring sGROUP_NAME = tstring(szTag); //+ g_szName_HEADER_NameSpace;
		of << _jF("[ProtoContract]");
		of << _jF("public class %1% {") % sGROUP_NAME;
		{
			AutoTab a;
			of << _jT("public enum Type {");
			{
				AutoTab a;
				of << _jT("NONE = 1,\n");
				element_list_it itEL;
				idx=2;
				jFOR(itGROUP->second,itEL)
				{
					jIE* pE = *itEL;
					of << _jF("%3%%1% = %2%,") % pE->GetTagName() % (idx+iVer) % g_szMESSAGE_ENUM_TAG;
					++idx;
				}
			}
			of << _jF("}");

			of << endl;

			of << _jF("[ProtoMember(1,IsRequired = true)]");
			of << _jF("public Type type {get; set;}\n");

			element_list_it itEL;
			idx=2;

			jFOR(itGROUP->second,itEL)
			{
				jIE* pE = *itEL;
				of << _jF("[ProtoMember(%1%, IsRequired = false)]") % idx;
				of << _jF("public %3%%1% %4%%1% {get; set;}") % pE->GetTagName() % idx % g_szMESSAGE_TAG % g_szMESSAGE_MEMEBER_TAG;
				++idx;
			}
		}
		of << _jF("}\n//end of message %1%\n\n") % sGROUP_NAME;
	}
}
//http://www.frictionpointstudios.com/blog/2011/3/31/using-protobuf-net-serialization-in-unity-iphone.html
void _make_google_protobuf_net__contract_cs( tstring & _sProtoFileName, mapGROUP_TAG_t mapGROUP_TAG ,int iVer )
{
	//#--------------------------------------------------------------------------
	// PT_BaseballServer.proto_contract.cs  c# proto코드
	//#--------------------------------------------------------------------------
	{
		//jMB("asdf","asdf");
		tstring sProto_foreach_file =  _sProtoFileName + _T(".proto_contract.cs");
		tofstream of2(jA(sProto_foreach_file));
		of2.imbue(locale(jA(pv_file_locale->Get_cstr())));

		of2 << _jF("// this code is generated by PacketGenerator(lib_mech)");
		of2 << _jF("// 주의 http://www.frictionpointstudios.com/blog/2011/3/31/using-protobuf-net-serialization-in-unity-iphone.html 를 사용할때 쓰는 코드 \n");

		static jIE* pePROTO_CONTRACT_NAMESPACE= nUSD_FILE::g_pDocProtocalPrototype->Find(jS(PROTO_CONTRACT_NAMESPACE));
		{
			jIE* it = pePROTO_CONTRACT_NAMESPACE->begin();
			jrFOR(it)
			{
				of2 << _jF("using %1%; //from ProtocalPrototype.xml : GOOGLE_PROTOCAL_BUFFER : include_namespace") % it->Get_cstr();
			}
		}

		tcstr szHEADER = g_pDocTargetFile->BaseI()->GetAttr(jS(HEADER)) ;

		//of2 << _jF("namespace %1%") % _sProtoFileName;
		of2 << _jF("namespace nPROTO");
		of2 << _jF("{");
		mapGROUP_TAG_it itGROUP;
		jFOR(mapGROUP_TAG,itGROUP)
		{
			AutoTab b;
			tcstr szTag = jt_strchr(itGROUP->first.c_str(),'.');
			++szTag;
			jASSERT(szTag);
			tstring sGROUP_NAME = tstring(szTag); //+ g_szName_HEADER_NameSpace;


			of2 << _jF("// group : %1%") % sGROUP_NAME;
			element_list_it itEL;
			jFOR(itGROUP->second,itEL)
			{
				of2 << endl ;
				jIE* pE = *itEL;
				of2 << _jF("[ProtoContract]");
				tstring sMessageName = tstring(g_szMESSAGE_TAG) + pE->GetTagName();
				of2 << _jF("public class %1%") % sMessageName;
				of2 << _jF("{");
				jIE* peField= pE->begin();
				int i=1;

				jLIST_TYPEDEF_map(tstring,tstring,ctor_list);

				jrFOR(peField)
				{
					AutoTab c;
					if(tstring(jS(optional)) == g_szMEMBER_OPTOIN)
					{
						of2 << _jF("[ProtoMember(%1%, IsRequired = false)]") % i;
					}
					else
					{
						of2 << _jF("[ProtoMember(%1%, IsRequired = true)]") % i;
					}

					jIVar* pvLength = peField->GetAttrVar(jS(Length));
					tstring sType  =util::make_cshap_type(peField->GetAttr(jS(TYPE)) ) ;
					if(pvLength)
					{
						of2 << _jF("public List<%1%> %2% {get; set;} ") % sType % peField->GetTagName();
						ctor_list[ peField->GetTagName() ] = sType;
					}
					else
					{
						of2 << _jF("public %1% %2% {get; set;} ") % sType % peField->GetTagName();
					}
					++i;
				}
				if(ctor_list.size())
				{
					AutoTab c;

					of2 << _jF("");
					of2 << _jF("public %1%()") % sMessageName;
					of2 << _jF("{");
					ctor_list_it it =ctor_list.begin() ,ie = ctor_list.end();
					for(;it!=ie;++it)
					{
						of2 << _jF("	%1% = new List<%2%>();") % it->first % it->second;
					}
					of2 << _jF("}");
				}

				of2 << _jF("} //public class %1%_%2%") % g_szMESSAGE_TAG % pE->GetTagName();
				of2 << endl ;

			}
			of2 << endl << endl;
		}//jFOR(mapGROUP_TAG,itGROUP)


		//프로토콜 enum 출력.프로토콜 그룹메세지 출력
		_make_google_protobuf_net__contract_cs__group_message(mapGROUP_TAG,of2,iVer);

		of2 << _jF("	");
		of2 << _jF("	public class %1%_proto_contract")%_sProtoFileName;
		of2 << _jF("	{");
		of2 << _jF("	    public static ArrayList GetTypes()");
		of2 << _jF("	    {");
		of2 << _jF("	        ArrayList list = new ArrayList();");

		jFOR(mapGROUP_TAG,itGROUP)
		{
			tcstr szTag = jt_strchr(itGROUP->first.c_str(),'.');
			++szTag;
			jASSERT(szTag);
			tstring sGROUP_NAME = tstring(szTag); //+ g_szName_HEADER_NameSpace;
			of2 << _jF("	        list.Add(typeof(%1%));")%sGROUP_NAME;
			element_list_it itEL;
			jFOR(itGROUP->second,itEL)
			{
				jIE* pE = *itEL;
				of2 << _jF("	        list.Add(typeof(%1%%2%));")% g_szMESSAGE_TAG % pE->GetTagName();
			}
			of2 << _jF("	");
		}

		of2 << _jF("	        return list;");
		of2 << _jF("	    }");
		of2 << _jF("	}");
		of2 << _jF("	");

		of2 << _jF("}//namespace nPROTO");
		//of2 << _jF("}//namespace %1%") % _sProtoFileName;



	}//// PT_BaseballServer.proto.help.cs  c# 핼프코드 생성.
}//void _make_google_protobuf_net__contract_cs( tstring & _sProtoFileName, mapGROUP_TAG_t mapGROUP_TAG )

void _make_google_protobuf__group_message( mapGROUP_TAG_t &mapGROUP_TAG, tofstream &of, int iVer )
{
	int idx;
	mapGROUP_TAG_it itGROUP;
	jFOR(mapGROUP_TAG,itGROUP)
	{
		tcstr szTag = jt_strchr(itGROUP->first.c_str(),'.');
		++szTag;
		jASSERT(szTag);
		tstring sGROUP_NAME = tstring(szTag); //+ g_szName_HEADER_NameSpace;
		of << _jF("message %1% {") % sGROUP_NAME;
		{
			AutoTab a;
			of << _jT("enum Type {");
			{
				AutoTab a;
				of << _jT("NONE = 1;\n");
				element_list_it itEL;
				idx=2;
				jFOR(itGROUP->second,itEL)
				{
					jIE* pE = *itEL;
					of << _jF("%3%%1% = %2%;") % pE->GetTagName() % (idx+iVer) % g_szMESSAGE_ENUM_TAG;
					++idx;
				}
			}
			of << _jF("}");

			of << endl;
			of << _jF("required Type type = 1;\n");

			element_list_it itEL;
			idx=2;
			jFOR(itGROUP->second,itEL)
			{
				jIE* pE = *itEL;
				of << _jF("optional %3%%1% %4%%1% = %2%;") % pE->GetTagName() % idx % g_szMESSAGE_TAG % g_szMESSAGE_MEMEBER_TAG;
				++idx;
			}

		}
		of << _jF("}\n//end of message %1%\n\n") % sGROUP_NAME;
	}
}

void make_google_protocal_buffer_doc(tstring &_sProtoFileName,int argc, _TCHAR* argv[])
{
	int idx=0;
	cstr szVer = g_pDocTargetFile->BaseI()->GetAttr(_T("VERSION"));
	int iVer = jt_atoi(szVer);

	tstring sProtoFileName =  _sProtoFileName + _T(".proto");
	jIE* itC;
	jIE* peENUM_TYPE_LIST = g_pDocTargetFile->Find(jS(ENUM_TYPE_LIST));

	tofstream of(jA(sProtoFileName));
	of.imbue(locale(jA(pv_file_locale->Get_cstr())));

	//g_pDocTargetFile의 구조 참조 -> d:\svn\common\lib\windows\mech\src\server\TestServer\protocal\PT_TestServer.xml
	jIE* pePROTOCAL_LIST = g_pDocTargetFile->Find(jS(PROTOCAL_LIST));

	of<<_jF("//from(%1%)\n") % argv[ARG_HEADER_XML_FILE];
	//of << _jT("// Basic type specification");
	//of << _jT("option optimize_for = LITE_RUNTIME;\n\n");

	static jIE* peGOOGLE_PROTOCAL_BUFFER = nUSD_FILE::g_pDocProtocalPrototype->Find(jS(GOOGLE_PROTOCAL_BUFFER));

	if(!g_szMESSAGE_TAG)
	{
		g_szMESSAGE_TAG = peGOOGLE_PROTOCAL_BUFFER->Find(jS(MESSAGE_TAG))->Get_cstr();
		if(!g_szMESSAGE_TAG)
		{
			g_szMESSAGE_TAG=_T("");
		}
		g_szMESSAGE_MEMEBER_TAG = peGOOGLE_PROTOCAL_BUFFER->Find(jS(MESSAGE_MEMEBER_TAG))->Get_cstr();
		if(!g_szMESSAGE_MEMEBER_TAG)
		{
			g_szMESSAGE_MEMEBER_TAG = _T("");
		}
		g_szMEMBER_OPTOIN = peGOOGLE_PROTOCAL_BUFFER->Find(jS(MEMBER_OPTOIN))->Get_cstr();
		if(!g_szMEMBER_OPTOIN)
		{
			g_szMEMBER_OPTOIN= _T("");
		}

		g_szMESSAGE_ENUM_TAG = peGOOGLE_PROTOCAL_BUFFER->Find(jS(MESSAGE_ENUM_TAG))->Get_cstr();
		if(!g_szMESSAGE_ENUM_TAG)
		{
			g_szMESSAGE_ENUM_TAG= _T("");
		}

		g_szPROTO_BUF_SERIALIZER_NAME_FOR_IPHONE = peGOOGLE_PROTOCAL_BUFFER->Find(jS(PROTO_BUF_SERIALIZER_NAME_FOR_IPHONE))->Get_cstr();
		if(!g_szPROTO_BUF_SERIALIZER_NAME_FOR_IPHONE)
		{
			g_szPROTO_BUF_SERIALIZER_NAME_FOR_IPHONE= _T("");
		}
	}


	tstring sPath = nUSD_FILE::g_pDocProtocalPrototype->GetPath();
	if(peGOOGLE_PROTOCAL_BUFFER)
	{
		tstring sFile = peGOOGLE_PROTOCAL_BUFFER->Find(jS(BEGIN_CODE_FILE))->Get_cstr();
		sPath += sFile;
		tstring sCode;
		if(nFileSystem::read_file(sPath , sCode) && sCode.size())
		{
			of << _jF("//[[begin of %1%\n\n") % sPath;
			of << sCode;
			of << _jF("//]]end of %1%\n\n") % sPath;
		}
	}

	of << endl << endl;
	of << _jT("// Packet type specification\n");

	_print_google_proto_enum(peENUM_TYPE_LIST, of,is_global_enum,0);
	of << endl << endl;

	mapGROUP_TAG_t mapGROUP_TAG;
	itC = pePROTOCAL_LIST->begin();
	jrFOR(itC)
	{
		tcstr sz = itC->GetAttr(jS(USD));
		if(sz) of<<_jF("//%1%") % sz;
		print_help_comment(itC->GetAttr(jS(HELP)), of);


		of<<_jF("message %2%%1% {") % itC->GetTagName() % g_szMESSAGE_TAG;

		{
			AutoTab a;

			_print_google_proto_enum(peENUM_TYPE_LIST, of,is_scope_enum,itC);


			jIE* itVar= itC->begin();
			idx=1;
			jrFOR(itVar)
			{
				if(itVar->GetAttrVar(jS(Length)))
				{
					of <<_jF("repeated %3% %1% = %2%;") % itVar->GetTagName() % (idx) % itVar->GetAttr(jS(TYPE));
				}
				else
				{
					of <<_jF("%4% %3% %1% = %2%;") % itVar->GetTagName() % (idx) % itVar->GetAttr(jS(TYPE)) % g_szMEMBER_OPTOIN;
				}
				++idx;
			}
		}
		tcstr szGROUP_TAG =itC->GetAttr(jS(GROUP_TAG));
		if(szGROUP_TAG)
		{
			vector<tstring> outGROUP_TAG;
			nString::jSplit(szGROUP_TAG,_T("; "),outGROUP_TAG);
			for(size_t i=0; i < outGROUP_TAG.size(); ++i)
			{
				szGROUP_TAG = outGROUP_TAG[i].c_str();
				mapGROUP_TAG[szGROUP_TAG].push_back(itC);
			}
		}
		of<<_jT("}\n");
	}
	of<<endl;

	//메세지 그룹 메세지&enum생성.
	_make_google_protobuf__group_message(mapGROUP_TAG, of, iVer);

	if(peGOOGLE_PROTOCAL_BUFFER)
	{
		tstring sFile = peGOOGLE_PROTOCAL_BUFFER->Find(jS(END_CODE_FILE))->Get_cstr();
		sPath += sFile;
		tstring sCode;
		if(nFileSystem::read_file(sPath , sCode) && sCode.size())
		{
			of << _jF("//[[begin of  %1%\n\n") % sPath;
			of << sCode;
			of << _jF("//]]end of %1%\n\n") % sPath;
		}
	}

	_make_google_protobuf_cshop_net_cpp_header(_sProtoFileName, mapGROUP_TAG, iVer);

	//http://code.google.com/p/protobuf-csharp-port/ 를 사용할때 필요한 help code.
	_make_google_protobuf_cshap_net_help(_sProtoFileName, mapGROUP_TAG);

	//http://code.google.com/p/protobuf-net/ 를 사용시.
	_make_google_protobuf_net_help(_sProtoFileName, mapGROUP_TAG);

	//http://www.frictionpointstudios.com/blog/2011/3/31/using-protobuf-net-serialization-in-unity-iphone.html
	_make_google_protobuf_net__contract_cs(_sProtoFileName, mapGROUP_TAG,iVer);

}

