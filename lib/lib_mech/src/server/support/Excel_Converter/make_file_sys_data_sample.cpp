/* file : make_file_sys_data_sample.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-29 15:23:48
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "Excel_Converter.h"

void Excel_Converter::make_file_sys_table_sample_SUB_gen_line(int i, nXML::jE e , TCHAR outBuffer[2048])
{
	memset(outBuffer,0,sizeof(outBuffer));
	nXML::jE it = e.begin();
	fname_t buf;
	eFOR(it)
	{
		if( jt_strstr(it(jS(db_type))->Get_cstr(), jS(PK) ) )
		{
			jt_sprintf(buf, _T("%d") , i);
			jt_strcat(outBuffer,buf);
			jt_strcat(outBuffer,_T("\t"));
			continue;
		}
		tcstr szType = it(jS(data_type))->Get_cstr();
		if(jt_strstr(szType,jS(name)) || jt_strstr(szType,jS(string)))
		{
			jt_sprintf(buf, _T("%s_%d"), it->GetTagName(),i);
			jt_strcat(outBuffer,buf);
			jt_strcat(outBuffer,_T("\t"));
			continue;
		}

		nXML::jE eMax = it(jS(max));
		nXML::jE eMin = it(jS(min));
		tcstr szMax = eMax->Get_cstr();
		tcstr szMin = eMin->Get_cstr();
		if(jt_strlen(szMax) && szMax[0]=='E')
		{
			jE enumValue = _IsEnumValue(eMax);
			if(enumValue.full())
			{
				int idx = i % enumValue.size();
				tcstr szEnum = enumValue(idx)->GetTagName();
				jt_sprintf(buf, _T("%s"),szEnum);
				jt_strcat(outBuffer,buf);
				jt_strcat(outBuffer,_T("\t"));
				continue;
			}
			jWARN(_T("enum type을 못찾음 : %s"), szMax);
		}
		if(jt_strstr(szType, jS(int)))
		{
			int iLocal = i;
			if(jt_strlen(szMax))
			{
				int iMax = jt_atoi(szMax);
				if(iLocal> iMax) 
					iLocal = iMax;
			}
			if(jt_strlen(szMin))
			{
				int iMin = jt_atoi(szMin);
				if(iLocal < iMin) 
					iLocal = iMin;
			}
			jt_sprintf(buf, _T("%d") , iLocal);
			jt_strcat(outBuffer,buf);
			jt_strcat(outBuffer,_T("\t"));
			continue;
		}
		if(jt_strstr(szType, jS(bool)))
		{
			jt_strcat(outBuffer, i%2 ? jS(true) : jS(false));
			jt_strcat(outBuffer,_T("\t"));
			continue;
		}
		if(jt_strstr(szType, jS(SYSTEMTIME)))
		{
			jt_sprintf(buf, _T("%d") , i);
			jt_strcat(outBuffer,buf);
			jt_strcat(outBuffer,_T("\t"));
			continue;
		}
		jt_sprintf(buf, _T("undefined_%s_%d") ,it->GetTagName(), i);
		jt_strcat(outBuffer,buf);
		jt_strcat(outBuffer,_T("\t"));
	}
}

void Excel_Converter::make_file_sys_table_sample()
{
	if( m_eSys.empty() ) return;
	nXML::jE it = m_eSys.begin();
	TCHAR buf[2048];
	eFOR(it)
	{
		filesystem::tpath  saveFile(m_save_file_path);
		saveFile /= (tstring(it->GetTagName()) + jS(_sample.txt) );
		tofstream of(jA(saveFile.string()));
#if 0
		of << _T("/*------------------------------------------------------------\n") ;
		of << _jF("Create By %3%  \nVersion = %1% \nDate =  %2%\n") % jCURR_VERSION % _T(__TIMESTAMP__) % g_ExeEnv.m_szExeName;
		of << _jF("\ncommand line : \n%1%\n\n") %GetCommandLine();
		of << _T("-------------------------------------------------------------*/\n");
		of << endl;
#endif
		for(int i =1 ; i <=pv_SysData_Sample_Count->Get_int(); ++i)
		{
			make_file_sys_table_sample_SUB_gen_line(i,it,buf);
			of << buf << endl;
		}
	}
}


