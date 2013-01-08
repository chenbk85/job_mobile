/* file : recv_Common.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-31 15:00:28
comp.: wiki.aqrius.com
title : 
desc : 

*/

jCONSOLE_CMD_AUTO(jSERVER_NAME,log_console,0,"On/off console log ","<bool>")
{
#define jCONSOLE_PARAM_log_console(X,Y) X(is,bool)
	jCONSOLE_PARAM_END(log_console);
	jSET_CON_FLAG(exe,LOG_OFF,is);
	return true;
}


jCONSOLE_CMD_AUTO(jSERVER_NAME,change_CmdParser,0,"change CmdParser to PlugIn_Server(default) or PlugIn_Connect","[PS | PC]")
{
#define jCONSOLE_PARAM_change_CmdParser(X,Y) Y(szPlugIn,tcstr,_T("PS"))
	jCONSOLE_PARAM_END(change_CmdParser);

	if(tstring(szPlugIn)==jS(PS))
	{
		g_pCurrPlugIn_CmdParser = PlugIn_Server::Get();
		return true;
	}
	else if(tstring(szPlugIn)==jS(PC))
	{
		g_pCurrPlugIn_CmdParser = PlugIn_Connect::Get();
		return true;
	}
	jWARN("unknown param : %s", szPlugIn);
	return false;
}


jCONSOLE_CMD_AUTO(jSERVER_NAME,prompt,0,"set prompt DBQuery(DQ) / Central(PS) / Connection(PC)","<DQ | PS | PC>")
{
#define jCONSOLE_PARAM_prompt(X,Y) X(target,tcstr)
	jCONSOLE_PARAM_END(prompt);

	g_SG.SetParserType(target);
	return true;
}





jCONSOLE_CMD_AUTO(jSERVER_NAME,user_list, 0 ,"print user list" , "<file | con> [file_tag]")
{
	#define jCONSOLE_PARAM_user_list(X,Y) X(outType,tcstr) Y(file_tag,tcstr,0)
	jCONSOLE_PARAM_END(user_list);

	vector<tstring> users;
	g_PL.for_each(to_string_vector(users));

	bool is = g_TCommon.output_string_to_file_or_con(outType, jsSERVER_NAME jS(_user_list), file_tag, users);
	jLOG1(_T("tot user= %d"),users.size());
	return is;
}





jCONSOLE_CMD_AUTO(jSERVER_NAME,print_jServerInfo ,0,"print jServerInfo list","<file | con> [file_tag]")
{
#define jCONSOLE_PARAM_print_jServerInfo(X,Y) X(outType,tcstr) Y(file_tag,tcstr,0)
	jCONSOLE_PARAM_END(print_jServerInfo);

	vector<tstring> outList;
	tname1024_t buf;
	ToString(&g_SG.m_MyInfo ,buf);
	tstring str =_T("m_MyInfo : ");
	str +=buf;
	outList.push_back(str);
	outList.push_back(_T("\nm_mapServerInfo="));

	#define jLAMDA_colllect_jServerInfo(X,Z) Z(vector<tstring>&,outList)
	jLAMDA_for_each(colllect_jServerInfo,jServerInfo*)
	{
		tname1024_t buf; 
		ToString(it,buf);
		outList.push_back(buf);
	}
	jLAMDA_end();

	g_SG.ServerInfo_for_each(colllect_jServerInfo(outList));
	outList.push_back(_T("\njIGridNode="));

	#define jLAMDA_collect_jIGridNode(X,Z) Z(vector<tstring>&,outList)
	jLAMDA_for_each(collect_jIGridNode,jIGridNode*)
	{
		jSI(it);

		jIE* pE = it->m_pS->Get_jIE();
		cstr szSock=_T("NULL");
		if(pE)
		{
			szSock=pE->GetTagName();
		}
		tname1024_t szBuf;
		tname1024_t szBuf1;
		jt_sprintf(szBuf1 , _T("%s.%s(%s) %s") , it->m_pPlugIn->m_pE->GetTagName(),it->GetGridName(), szSock, ToString(si,szBuf) );
		outList.push_back(szBuf1);
	}
	jLAMDA_end();
	g_SG.for_each(collect_jIGridNode(outList));

	return g_TCommon.output_string_to_file_or_con(outType, jsSERVER_NAME, file_tag, outList);

}
