/* file : main.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-03-26 17:55:07
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "Excel_Converter.h"
#include "common/jCommon.h"
#include "common/jInit.h"

jLIST_TYPEDEF_vector(std::tstring, g_Files);

std::map<tstring , tstring> g_sqlstring_fmt;

int asdfaqsf_tmain(int argc, _TCHAR* argv[])
{
	jAssertArg(true,_T(""));
	return 0;
}

#if 1

bool g_isSave_AppDoc=false;
bool g_isGen_table_type=true;
fname_t __szPath;

int _tmain(int argc, _TCHAR* argv[])
{
	jMech_Init();
#ifdef _DEBUG
	 jMB("asdf","asdf");
#endif

	jSET_LOCALE1("kor");
	if(argc==1)
	{
		MessageBox(0,_T("사용법: Excel_Converter.exe [sys_data1.txt] [sys_data2.txt] ..."),_T("인자 없음"), MB_OK);
		return 0;
	}

	g_Cfg = nGLOBAL::g_pDocApp;
	g_Cfg = g_Cfg(_T("Excel_Converter"));
	bool isMake=false;
	isMake = g_Cfg.empty();

	//--------------------------------------------------------------------------
	if(!isMake) //존제한다면 버젼비교
	{
		jVar ver = g_Cfg.Attr(_T("VERSION"));
		if(!ver.full())	isMake =true;
		if(!isMake)
		{
			isMake = ver->Get_int() < jCURR_VERSION;
		}
		if(isMake)
		{
			g_Cfg->EraseChild();
		}
	}

	if(isMake)
	{
		g_Cfg = nGLOBAL::g_pDocApp;
		g_Cfg = g_Cfg[_T("Excel_Converter")];
		g_Cfg.AttrP(_T("VERSION")).SetType(jIVar::EDint) = jCURR_VERSION;
		g_Cfg.AttrP(_T("VERSION_DATE")).SetType(jIVar::EDcstr) = _T(__TIMESTAMP__);
		;
		// 아래 내용을 수정할때는 jCURR_VERSION의 번호를 올려줘야한다.
		nXML::jE eEnum = g_Cfg[_T("enum")];
		//enum해더의 필드
		eEnum.AttrP(_T("RESERVE")).SetType(jIVar::EDcstr) = _T("enum이라는 예약어");
		eEnum.AttrP(_T("NAME")).SetType(jIVar::EDcstr) = _T("enum의 이름");
		eEnum.AttrP(_T("HELP")).SetType(jIVar::EDcstr) = _T("enum의 설명");

		//enum 항목의 필드
		eEnum[_T("name")].SetType(jIVar::EDcstr) =_T("규칙명");
		eEnum[_T("value")].SetType(jIVar::EDcstr) =_T("규칙값");
		eEnum[_T("name_eng")].SetType(jIVar::EDcstr) =_T("규칙영문명");
		eEnum[_T("help")].SetType(jIVar::EDcstr) =_T("설명");


		nXML::jE eSys = g_Cfg[_T("Sys")];
		eSys.AttrP(_T("RESERVE")).SetType(jIVar::EDcstr) = _T("Tbl이라는 예약어");
		eSys.AttrP(_T("NAME")).SetType(jIVar::EDcstr) = _T("Tbl Table의 이름");
		eSys.AttrP(_T("HELP")).SetType(jIVar::EDcstr) = _T("Tbl Table의 설명");

		eSys[_T("name")].SetType(jIVar::EDcstr) = _T("필드명");
		eSys[_T("name_eng")].SetType(jIVar::EDcstr) = _T("필드영문명");
		eSys[_T("data_type")].SetType(jIVar::EDcstr) = _T("자료형");
		eSys[_T("min")].SetType(jIVar::EDcstr) = _T("최소값");
		eSys[_T("max")].SetType(jIVar::EDcstr) = _T("최대값");
		eSys[_T("db_type")].SetType(jIVar::EDcstr) = _T("DB자료형");
		eSys[_T("type_note")].SetType(jIVar::EDcstr) = _T("자료형노트");
		eSys[_T("help")].SetType(jIVar::EDcstr) = _T("설명");

		nXML::jE eUse = g_Cfg[_T("Tbl")];
		eSys->CopyTo_Child(eUse);

		nXML::jE eApp = g_Cfg[_T("App")];
		eSys->CopyTo_Child(eApp);

	}

	jE eDoc = nGLOBAL::g_pDocApp;
	g_eTYPE_INFO = eDoc(jS(TYPE_INFO));

	if(g_eTYPE_INFO.empty() )
	{
		isMake=true;
		if(g_eTYPE_INFO.full())
		{
			//g_eTYPE_INFO->Erase();
		}
		g_eTYPE_INFO = eDoc[jS(TYPE_INFO)];

		#define jTYPE_INFO_DEF(TYPE,SETTYPE,GETTYPE,SIMPLE,is_org_set,is_org_get,db_table_type_val,db_table_type_to_sqlstring)\
		{\
			jE e = currNode[jS(TYPE)];\
			e.AttrP(jS(Setter)).T() = jS(SETTYPE);\
			e.AttrP(jS(Getter)).T() = jS(GETTYPE);\
			e.AttrP(jS(Tag)).T() = jS(SIMPLE);\
			e.AttrP(jS(org_set_get)).SetType(jIVar::EDint2);\
			e.AttrP(jS(org_set_get))->GetInt(0)=is_org_set;\
			e.AttrP(jS(org_set_get))->GetInt(1)=is_org_get;\
			e.AttrP(jS(db_type)).T() = jS(db_table_type_val);\
			g_sqlstring_fmt[jS(TYPE)] = _T(db_table_type_to_sqlstring);\
		}

		jE currNode = g_eTYPE_INFO[jS(fname)];
		jTYPE_INFO_DEF(aname12_t,acstr,acstr,a12,false,true,VARCHAR(12),"'%s'");
		jTYPE_INFO_DEF(aname32_t,acstr,acstr,a32,false,true,VARCHAR(32),"'%s'");
		jTYPE_INFO_DEF(aname64_t,acstr,acstr,a64,false,true,VARCHAR(64),"'%s'");
		jTYPE_INFO_DEF(aname128_t,acstr,acstr,a128,false,true,VARCHAR(128),"'%s'");
		jTYPE_INFO_DEF(aname256_t,acstr,acstr,a256,false,true,VARCHAR(256),"'%s'");
		jTYPE_INFO_DEF(aname1024_t,acstr,acstr,a1024,false,true,VARCHAR(1024),"'%s'");

		jTYPE_INFO_DEF(tname12_t,tcstr,tcstr,t12,false,true,TVARCHAR(12),"'%s'");
		jTYPE_INFO_DEF(tname32_t,tcstr,tcstr,t32,false,true,TVARCHAR(32),"'%s'");
		jTYPE_INFO_DEF(tname64_t,tcstr,tcstr,t64,false,true,TVARCHAR(64),"'%s'");
		jTYPE_INFO_DEF(tname128_t,tcstr,tcstr,t128,false,true,TVARCHAR(128),"'%s'");
		jTYPE_INFO_DEF(tname256_t,tcstr,tcstr,t256,false,true,TVARCHAR(256),"'%s'");
		jTYPE_INFO_DEF(tname1024_t,tcstr,tcstr,t1024,false,true,TVARCHAR(1024),"'%s'");

		jTYPE_INFO_DEF(wname12_t,wcstr,wcstr,w12,false,true,NVARCHAR(12),"'%s'");
		jTYPE_INFO_DEF(wname32_t,wcstr,wcstr,w32,false,true,NVARCHAR(32),"'%s'");
		jTYPE_INFO_DEF(wname64_t,wcstr,wcstr,w64,false,true,NVARCHAR(64),"'%s'");
		jTYPE_INFO_DEF(wname128_t,wcstr,wcstr,w128,false,true,NVARCHAR(128),"'%s'");
		jTYPE_INFO_DEF(wname256_t,wcstr,wcstr,w256,false,true,NVARCHAR(256),"'%s'");
		jTYPE_INFO_DEF(wname1024_t,wcstr,wcstr,w1024,false,true,NVARCHAR(1024),"'%s'");

		jTYPE_INFO_DEF(net_string8,tcstr,tcstr,t8,false,true,TVARCHAR(8),"'%s'");
		jTYPE_INFO_DEF(net_string16,tcstr,tcstr,t16,false,true,TVARCHAR(16),"'%s'");
		jTYPE_INFO_DEF(net_string32,tcstr,tcstr,t32,false,true,TVARCHAR(32),"'%s'");
		jTYPE_INFO_DEF(net_string64,tcstr,tcstr,t64,false,true,TVARCHAR(64),"'%s'");
		jTYPE_INFO_DEF(net_string128,tcstr,tcstr,t128,false,true,TVARCHAR(128),"'%s'");
		jTYPE_INFO_DEF(net_string256,tcstr,tcstr,t256,false,true,TVARCHAR(256),"'%s'");
		jTYPE_INFO_DEF(net_string1024,tcstr,tcstr,t1024,false,true,TVARCHAR(1024),"'%s'");

		currNode = g_eTYPE_INFO[jS(string)];
		jTYPE_INFO_DEF(astring,acstr ,acstr, as,true,false,UNDEFINED,"'%s'");
		jTYPE_INFO_DEF(wstring,wcstr ,wcstr, ws,true,false,UNDEFINED,"'%s'");
		jTYPE_INFO_DEF(tstring,tcstr ,tcstr, ts,true,false,UNDEFINED,"'%s'");

		currNode = g_eTYPE_INFO[jS(simple_type)];
		jTYPE_INFO_DEF(bool,bool,bool,b,true,true,BIT,"%d");
		jTYPE_INFO_DEF(SYSTEMTIME,const SYSTEMTIME_REF,SYSTEMTIME_REF,tm,true,true,DATETIME,"'%d-%d-%d %d:%d:%d'");
		jTYPE_INFO_DEF(undefined_t,undefined_t,undefined_t,undef,true,true,UNDEFINED,"'%s'");

		currNode = g_eTYPE_INFO[jS(min_max_type)];
		jTYPE_INFO_DEF(float,float,float,f,true,true,REAL,"%f");
		jTYPE_INFO_DEF(int8,int8,int8,i8,true,true,TINYINT,"%d");
		jTYPE_INFO_DEF(int16,int16,int16,i16,true,true,SMALLINT,"%d");
		jTYPE_INFO_DEF(int32,int32,int32,i32,true,true,INT,"%d");
		jTYPE_INFO_DEF(int64,int64,int64,i64,true,true,BIGINT,"%d");

		jTYPE_INFO_DEF(uint8,uint8,uint8,i8,true,true,TINYINT,"%u");
		jTYPE_INFO_DEF(uint16,uint16,uint16,i16,true,true,SMALLINT,"%u");
		jTYPE_INFO_DEF(uint32,uint32,uint32,i32,true,true,INT,"%u");
		jTYPE_INFO_DEF(uint64,uint64,uint64,i64,true,true,BIGINT,"%u");
	}

	if(isMake)
		nGLOBAL::g_pDocApp->Save();

	if(argc>=2)
	{
		nFileSystem::jFileName fn(argv[1]);
		fn.GetPath(__szPath);
	}
	jLIST_TYPEDEF_set(std::tstring, listFile);
	for(int i=1; i< argc ; ++i)
	{
		listFile.insert(argv[i]);
	}
	{
		listFile_it it = listFile.begin(), ie = listFile.end();
		tname1024_t szExcel_Enum;
		jt_sprintf(szExcel_Enum,_T("%s.txt"),pv_excel_enum_file_name->Get_cstr());
		for( ; it!=ie; ++it)
		{
			if(jt_strstr(it->c_str(),szExcel_Enum) )
			{
				g_Files.insert(g_Files.begin(),*it);
			}
			else
				g_Files.push_back(*it);
		}
	}

	g_Files_it it = g_Files.begin(), ie = g_Files.end();
	bool is = nInterface::g_pjILog->UpdateLogType(jx(jXml),jx(FILE), false);
	for( ; it!=ie ; ++it)
	{
		if(!nFileSystem::jFolder::Is_Exist(it->c_str()))
		{
			fname_t szDir;
			GetCurrentDirectory(255,szDir);
			tname1024_t szMsg;
			jt_sprintf(szMsg, _T("file not found (currDir %s)"), szDir);
			jMB(it->c_str(),szMsg);
		}
		jt_printf(_T("file : %s\n"), it->c_str());
		tstring sBuf;read_file(it->c_str(), sBuf);
		Excel_Converter ec(sBuf);
		ec.ParseAll();
	}
	nInterface::g_pjILog->UpdateLogType(jx(jXml),jx(FILE), is);


	nCONSOLE::Get_jIConsoleVar()->Release();
	if(g_isSave_AppDoc)
	{
		nGLOBAL::g_pDocApp->Save();
	}
	if(g_isGen_table_type)
	{
		void make_table_type_h_file(cstr);
		make_table_type_h_file(__szPath);
	}

	printf("파싱 성공. 아무키나 누르셈");
	_getch();
	return 0;

}

#endif

#define jF3(X) endl << boost::tformat(_T(X))
void _make_table_type_h_file(tofstream &of ,jIE* e)
{
	nXML::jE eODBC = nGLOBAL::g_pDocApp->Find(jS(DB_TYPE_TO_ODBC_API_TYPE));
	jIE* it = e->begin();
	jrFOR(it)
	{
		cstr szType = it->GetTagName();
		bool isF = !jt_strncmp(szType,jS(float),jt_strlen(jS(float)));
		bool isI = !jt_strncmp(szType,jS(int),jt_strlen(jS(int)));
		bool isU = !jt_strncmp(szType,jS(uint),jt_strlen(jS(uint)));
		if(isF || isI || isU) continue;

		if(szType[0]!='E')
		{
			cstr OrgType = it->GetAttr(jS(Org));
			if(!OrgType) OrgType = it->GetAttr(jS(Setter));
			if(!OrgType)
			{
				jERROR(_T("%s : Org , Setter속성이 없음"),szType);
				continue;
			}
			if(jt_strcmp(szType,OrgType)) // Org 속성이 자신하고 동일하다면 typedef문 을 출력안한다.
			{
				of << jF3("typedef %1% %2%;") % OrgType % szType;
			}
		}
		cstr sz = it->GetAttr(jS(db_type));

		nXML::jE eOT = eODBC(sz);
		if(eOT.empty())
		{
			of << jF3("#define jEXCEL_SQL_TYPE_%1% unkown odbcconvert jTODO : check App_excel_converter.xml") % szType;
		}
		else
		{
			cstr odbc_type = eOT->Get_cstr();
			//of << jF3("#ifndef jEXCEL_SQL_TYPE_%1%") % szType;
			of << jF3("#define jEXCEL_SQL_TYPE_%1% %2%") % szType % odbc_type;
			//of << jF3("#endif //jEXCEL_SQL_TYPE_%1%\n") % szType;
		}
	}
}

void make_table_type_h_file(cstr __szPath)
{
	fname_t szTypeFile;
	jt_sprintf(szTypeFile,_T("%stable_type.h"),__szPath);
	tofstream of(jA(szTypeFile));
	if(of.bad())
	{
		//jERROR(_T("%s를 열수 없음"),szTypeFile);
		jMB(szTypeFile , _T("파일 열수 없슴"));
		return;
	}

	nXML::jE e = g_eTYPE_INFO(jS(min_max_type));
	_make_table_type_h_file(of, e);
	
	e = g_eTYPE_INFO_NS(jS(min_max_type));
	if(e.full())
	{
		_make_table_type_h_file(of, e);
	}
	else
	{
		jWARN(_T("g_eTYPE_INFO_NS(jS(min_max_type)) ==NULL : %s"),g_eTYPE_INFO_NS->GetTagName());

	}
	of << endl << endl;
	of.close();
}