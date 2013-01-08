/* file : Excel_Converter_sql.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-06-20 17:11:03
comp.: actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "Excel_Converter.h"


cstr get_printf_tok(jIE* peField)
{
	cstr szType = jC5(peField,data_type);
	jE e = Get_TYPE_INFO(szType);
	cstr szDBType = e.Attr(jS(db_type));
	if(jt_strstr(szDBType, jS(VARCHAR)))
	{
		return jS(s);
	}
	static nXML::jE eODBC = nGLOBAL::g_pDocApp->Find(jS(DB_TYPE_TO_ODBC_API_TYPE));
	if(eODBC.empty())
	{
		tfname_t szPath;
		nGLOBAL::g_pDocApp->GetURL(szPath);
		jERROR_T("%s : not found element <DB_TYPE_TO_ODBC_API_TYPE>",szPath);
		return 0;
	}
	nXML::jE etok = eODBC(szDBType);
	if(etok.empty())
	{
		jWARN(_T("<<< %s >>> (REF : %s -  %s) printf_tok not found. Insert data_type to <DB_TYPE_TO_ODBC_API_TYPE> in App_excel_converter.xml"),szDBType,szType,peField->GetTagName());
		etok = eODBC(jS(UNKOWN));
	}
	return etok->GetAttr(jS(printf_tok));
}


cstr get_CreateTableDBType(jIE* peField)
{
	cstr szType = jC5(peField,data_type);
	jE e = Get_TYPE_INFO(szType);
	szType = e.Attr(jS(db_type));

	if(!jt_strcmp(szType,jS(TVARCHAR)))
	{
#ifdef UNICODE
		szType = jS(NVARCHAR);
#else
		szType = jS(VARCHAR);
#endif
	}
	else if(!jt_strcmp(szType,jS(TTEXT)))
	{
#ifdef UNICODE
		szType = jS(NTEXT);
#else
		szType = jS(TEXT);
#endif
	}
	return szType;
}

void Excel_Converter::_make_file_sql_create_for_BaseTable( jIE* peField, tofstream &of )
{
	cstr szType = get_CreateTableDBType(peField);
	if(!jt_strcmp(szType,jS(UNDEFINED)))
	{
		return;
	}

	cstr szH = jC5(peField,help);
	if(jt_strlen(szH))
		of << _jFF("-- %1% : %2%") % jC5(peField,name) % szH ;
	else
		of << _jFF("-- %1%") % jC5(peField,name);


	if(peField->GetOrder()==0)
		of << _jFF("\t %1% \t %2% \t %3%") % jC5(peField,name_eng) % szType % jC5(peField,type_note) ;
	else
		of << _jFF(",\t %1% \t %2% \t %3%") % jC5(peField,name_eng) % szType % jC5(peField,type_note) ;
}


void Excel_Converter::make_file_sql_create()
{
	if( m_eUse.empty() ) return;
	filesystem::tpath  saveFile(m_save_file_path );
	saveFile /= jS(sql\\);
	tstring strPath = jT(saveFile.string());
	nFileSystem::jFolder dir;
	dir.CreateDirForce(strPath.c_str());
	dir.Goto(strPath.c_str());

	jIE* peTable = m_eUse->begin();

	jrFOR(peTable)
	{
		tstring fileName = tstring(jS(Create_)) + peTable->GetTagName() + jS(.sql);
		tofstream of(jA(fileName));
		
		tstring sDROP;
		if(pv_DB_VENDER->IsContents(jS(MYSQL)))
		{
			sDROP = _T("DROP TABLE IF EXISTS %1%;");
		}
		else
		{
			sDROP = _T("IF OBJECT_ID ('%1%', 'U') IS NOT NULL DROP TABLE %1%;");
		}

		if(!pv_IS_DROP_TABLE->Get_bool())
		{
			sDROP = tstring(_T("--**-- ")) + sDROP;
		}
		of << endl << endl << Tab()<< boost::tformat(sDROP) % peTable->GetTagName();

		of << _jFF("CREATE TABLE %1% (") % peTable->GetTagName();

		std::vector<nXML::jE> out;
		nInherit::get_Inherit_Info(out, peTable);
		{
			AutoTab b(this);

			for(size_t iOut=0; iOut< out.size() ; ++iOut)
			{
				jIE* peBaseTale = out[iOut];
				jIE* peField = peBaseTale->begin();
				jrFOR(peField)
				{
					_make_file_sql_create_for_BaseTable(peField,of);
				}
			}
		}

		jIE* peField = peTable->begin();
		jrFOR(peField)
		{
			_make_file_sql_create_for_BaseTable(peField, of);
		}
		of << _jFF(");");
	}
	dir.Goto(_T(".."));
	WinExec("__merge_create_sql.bat",SW_HIDE);
	//WinExec("del /q create_all.sql",SW_HIDE);
	//WinExec("copy /y .\\sql\\Create_*.sql create_all.sql" , SW_HIDE);

}


extern std::map<tstring , tstring> g_sqlstring_fmt;

void Excel_Converter::make_file_sql_insert()
{
	return;
	if( m_eUse.empty() ) return;
	filesystem::tpath  saveFile(m_save_file_path );
	saveFile /= jS(sql\\);
	tstring strPath = jT(saveFile.string());
	nFileSystem::jFolder dir;
	dir.CreateDirForce(strPath.c_str());
	dir.Goto(strPath.c_str());

	jIE* it = m_eUse->begin();


	jrFOR(it)
	{
		tstring fileName = tstring(jS(Insert_)) + it->GetTagName() + jS(.cpp);
		tofstream of(jA(fileName));
		of<< _jFF("void make_Insert_table(WCHAR* szSQL, nAQ::%1%* p )\n{\n") % it->GetTagName();

		of << _jFF("jw_sprintf(szSQL, L\"INSERT INTO %1% ( \\") % it->GetTagName();
		jIE* peField = it->begin();
		peField= peField->GetRight();
		jrFOR(peField)
		{
			if(peField->GetOrder()==1)
				of << _jFF("%1%\\") % peField->GetTagName();
			else
				of << _jFF(",%1%\\") % peField->GetTagName();
		}
		
		of << _jTT(") VALUES ( \\");
		peField = it->begin();
		peField= peField->GetRight();
		jrFOR(peField)
		{
			cstr szType = jC5(peField,data_type);
			jE e = Get_TYPE_INFO(szType);
			cstr szPrintTOk = get_printf_tok(peField);
			tstring szTok = tstring(_T("%")) + szPrintTOk;
			cstr szCTk = get_CreateTableDBType(peField);
			if(jt_strstr(szCTk,jS(VARCHAR)) )
			{
				if(jt_strstr(szCTk,jS(NVARCHAR)))
				{
					if(peField->GetOrder()== (it->size()-1))
						of << _jFF("N'%1%')\"") % szTok;
					else
						of << _jFF("N'%1%',\\") % szTok;

				}
				else
				{
					if(peField->GetOrder()== (it->size()-1))
						of << _jFF("'%1%')\"") % szTok;
					else
						of << _jFF("'%1%',\\") % szTok;
				}
			}
			else
			{
				if(peField->GetOrder()== (it->size()-1))
					of << _jFF("%1%)\"") % szTok;
				else
					of << _jFF("%1%,\\") % szTok;
			}
		}

		peField = it->begin();
		peField= peField->GetRight();
		jrFOR(peField)
		{
			cstr szType = jC5(peField,data_type);
			jE e = Get_TYPE_INFO(szType);
			e = e(-1);
			if( e->IsName(jS(fname) ) || e->IsName(jS(string) ) )
			{
				if(e->IsName(jS(string) ) )
					of<< _jFF(",jT(p->Get_%1%()") % peField->GetTagName();
				else
				{
					of<< _jFF(",jT(p->Get_%1%())") % peField->GetTagName();
				}
			}
			else
			{
				if(!jt_strcmp(get_CreateTableDBType(peField) , jS(BIGINT)))
				{
					of <<_jFF(",p->Get_%1%().m_db_id") % peField->GetTagName();
				}
				else if(!jt_strcmp(get_CreateTableDBType(peField) , jS(SQL_C_TYPE_TIMESTAMP)))
				{
					of <<_jFF(",jUPDATE_SQL_C_TYPE_TIMESTAMP(p->Get_%1%())") % peField->GetTagName();
				}
				else
				{
					of <<_jFF(",p->Get_%1%() ") % peField->GetTagName();
				}
			}
		}
		of << _jTT(");");
		of << _jTT("\n}");
		of.close();
	}
	dir.Goto(_T(".."));
	//WinExec("del /q create_all.sql",SW_HIDE);
	//WinExec("copy /y .\\sql\\Create_*.sql create_all.sql" , SW_HIDE);
}//void Excel_Converter::make_file_sql_insert()


void Excel_Converter::make_file_sql_update()
{
	if( m_eUse.empty() ) return;
	filesystem::tpath  saveFile(m_save_file_path );
	saveFile /= jS(sql\\);
	tstring strPath = jT(saveFile.string());
	nFileSystem::jFolder dir;
	dir.CreateDirForce(strPath.c_str());
	dir.Goto(strPath.c_str());

	jIE* it = m_eUse->begin();
	jrFOR(it)
	{
		tstring fileName = tstring(jS(Update_)) + it->GetTagName() + jS(.cpp);
		tofstream of(jA(fileName));

		of << Tab() <<_jFF("void make_update_table(WCHAR*szSQL , nAQ::%1%* p)") % it->GetTagName();
		of << Tab() <<_jFF("{");


		of << Tab() <<_jFF("jw_sprintf(szSQL, L\"UPDATE %1% SET\\") % it->GetTagName();
		jIE* peField = it->begin();
		peField = peField->GetRight();
		cstr sz_printf_tok =0;
		jrFOR(peField)
		{
			cstr sz_printf_tok = get_printf_tok(peField);
			if(!sz_printf_tok)
				return;

			if(tstring(_T("s")) == sz_printf_tok)
			{
				if(tstring(get_CreateTableDBType(peField))==jS(NVARCHAR))
				{
					if(peField->GetOrder()==1)
						of << Tab() <<_jFF("[%2%]=N'%1%%3%' \\") %_T("%") % peField->GetTagName() % sz_printf_tok;
					else
						of << Tab() <<_jFF(",[%2%]=N'%1%%3%' \\") %_T("%") % peField->GetTagName() % sz_printf_tok;
				}
				else
				{
					if(peField->GetOrder()==1)
						of << Tab() <<_jFF("[%2%]='%1%%3%' \\") %_T("%") % peField->GetTagName() % sz_printf_tok;
					else
						of << Tab() <<_jFF(",[%2%]='%1%%3%' \\") %_T("%") % peField->GetTagName() % sz_printf_tok;
				}
			}
			else
			{
				if(peField->GetOrder()==1)
					of << Tab() <<_jFF("[%2%]=%1%%3% \\") %_T("%") % peField->GetTagName() % sz_printf_tok;
				else
					of << Tab() <<_jFF(",[%2%]=%1%%3% \\") %_T("%") % peField->GetTagName() % sz_printf_tok;
			}

		}

		sz_printf_tok = get_printf_tok(it->begin());
		if(!sz_printf_tok) return;
		of << Tab() <<_jFF(" WHERE [%2%]=%1%%3% \"") % _T("%") % it->begin()->GetTagName() % sz_printf_tok;
		peField = it->begin();
		peField = peField->GetRight();
		jrFOR(peField)
		{
			if(!jt_strcmp(get_CreateTableDBType(peField) , jS(SQL_C_SBIGINT)))
			{
				of << Tab() <<_jFF("\t,p->Get_%1%().m_db_id") % peField->GetTagName();
			}
			else if(!jt_strcmp(get_CreateTableDBType(peField) , jS(SQL_C_TYPE_TIMESTAMP)))
			{
				of << Tab() <<_jFF("\t,jUPDATE_SQL_C_TYPE_TIMESTAMP(p->Get_%1%())") % peField->GetTagName();
			}
			else
				of << Tab() <<_jFF("\t,p->Get_%1%()") % peField->GetTagName();
		}
		of << Tab() <<_jFF("\t,p->Get_%1%().m_db_id") % it->begin()->GetTagName();
		of << Tab() <<_jTT(");\n");
		of << _jTT("}\n\n");

		of << _jTT("/*");

		peField = it->begin();
		jrFOR(peField)
		{
			cstr szCreateDBType = get_CreateTableDBType(peField);
			if(peField->GetOrder()==0)
				of << _jFF("\t@%1%\t%2%") % peField->GetTagName() % szCreateDBType;
			else
				of << _jFF("\t,@%1%\t%2%") % peField->GetTagName() % szCreateDBType;
		}
		of << _jTT("*/");

		of.close();

	}
	dir.Goto(_T(".."));
}//void Excel_Converter::make_file_sql_update()


void Excel_Converter::make_file_sql_sample_data()
{

}

void Excel_Converter::make_file_sql_select()
{
	if( m_eUse.empty() ) return;
	filesystem::tpath  saveFile(m_save_file_path );
	saveFile /= jS(sql\\);
	tstring strPath = jT(saveFile.string());
	nFileSystem::jFolder dir;
	dir.CreateDirForce(strPath.c_str());
	dir.Goto(strPath.c_str());

	jIE* it = m_eUse->begin();

	jrFOR(it)
	{
		tstring fileName = tstring(jS(sample_)) + it->GetTagName() + jS(.sql);
		tofstream of(jA(fileName));

		of<<_jTT("SELECT \\") ;
		jIE* peField = it->begin();
		jrFOR(peField)
		{
			if(peField->GetOrder() == (it->size()-1) )
				of << _jFF("%1% FROM %2%") % peField->GetTagName() % it->GetTagName();
			else
				of << _jFF("%1% , \\") % peField->GetTagName();
		}

		of << endl <<endl;
#if 0
		of<< _jFF("INSERT INTO %1% values ( ") % it->GetTagName() ;
		peField= it->begin();
		jrFOR(peField)
		{
			
		}
#endif
	}

}


