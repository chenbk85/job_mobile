/* file : cmd_AqMonitor.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-30 20:55:16
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "AqMonitor.h"
#include "PlugIn_ToBackEnd.h"

jCONSOLE_CMD_AUTO(jSERVER_NAME,set_env,0,"set test environment","<dummy_count> <loginIP> [loginPort=33100]")
{
	#define jCONSOLE_PARAM_set_env(X,Y) X(dummy_count,int)	X(loginIP,tcstr) Y(loginPort,int,33100)
	jCONSOLE_PARAM_END(set_env);

	jBE_ret(false);
	nswb1024_t sendBuf;
	pBE->m_pToTestServer->WritePacket(&WRITE_TM_SET_TEST_ENV(sendBuf,dummy_count, loginIP ,loginPort));
	return true;
}
jCONSOLE_CMD_AUTO(jSERVER_NAME,get_env,0,"get test environment","")
{
	jBE_ret(false);
	nswb1024_t sendBuf;
	pBE->m_pToTestServer->WritePacket(&WRITE_TM2TS_GET_TEST_ENV(sendBuf));
	return true;
}


jCONSOLE_CMD_AUTO(jSERVER_NAME,login,0,"Start LOGIN TEST","<dummy_count_for_delay> <delay_time_msec> [testClientName]")
{
#define jCONSOLE_PARAM_login(X,Y) X(dummy_count_for_delay,int)	X(delay_time_msec,int) Y(testClientName,tcstr,_T("NULL"))
	jCONSOLE_PARAM_END(login);

	jBE_ret(false);
	nswb1024_t sendBuf;
	pBE->m_pToTestServer->WritePacket(&WRITE_TM_TEST_LOGIN_START(sendBuf,dummy_count_for_delay, delay_time_msec ,testClientName));
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,logout,0,"game logout","<dummy_count_for_delay> <delay_time_msec> [testClientName]")
{
#define jCONSOLE_PARAM_logout(X,Y) X(dummy_count_for_delay,int)	X(delay_time_msec,int) Y(testClientName,tcstr,_T("NULL"))
	jCONSOLE_PARAM_END(logout);

	jBE_ret(false);
	nswb1024_t sendBuf;
	pBE->m_pToTestServer->WritePacket(&WRITE_TM_TEST_LOG_OUT(sendBuf,dummy_count_for_delay, delay_time_msec,testClientName));
	return true;
}

#if 0
jCONSOLE_CMD_AUTO(jSERVER_NAME,get_env,0,"Get TestCentralServer test env info","")
{
	PlugIn_TestAdminConsole* pP = PlugIn_TestAdminConsole::Get();
	if(!pBE->m_pToTestServer)
	{
		GetjILog()->Warning(_T("pBE->m_pToTestServer==NULL입니다."));
		return false;
	}
	nswb1024_t sendBuf;
	pBE->m_pToTestServer->WritePacket(&nTestCentralServer::WRITE_TA2TS_GET_TEST_ENV(sendBuf));
	return true;
}

inline void load_file_from_ifstream(std::tstring& s, std::tifstream& is)
{
	s.erase();
	if(is.bad()) return;
	//
	// attempt to grow string buffer to match file size,
	// this doesn't always work...
	s.reserve(is.rdbuf()->in_avail());
	TCHAR c;
	while(is.get(c))
	{
		// use logarithmic growth stategy, in case
		// in_avail (above) returned zero:
		if(s.capacity() == s.size())
			s.reserve(s.capacity() * 3);
		s.append(1, c);
	}
}

inline tcstr  read_file(tcstr  filename , std::tstring& sBuf)
{
	std::tifstream iF(filename);
	load_file_from_ifstream(sBuf, iF);
	iF.close();
	return sBuf.c_str();
}


jCONSOLE_CMD_AUTO(jSERVER_NAME,run_dummy_script,0,"Run sq script in DummyClient(MUST below 2048 CHAR)","<SQ_FILE>")
{
	PlugIn_TestAdminConsole* pP = PlugIn_TestAdminConsole::Get();
	if(!pBE->m_pToTestServer)
	{
		GetjILog()->Warning(_T("pBE->m_pToTestServer==NULL."));
		return false;
	}
	nswb4000_t sendBuf;
	sq_code_t codeS;
	std::tstring code;
	nFileSystem::jFolder dir;
	read_file(arg[0].c_str(), code);
	if(code.size() >= 2048)
	{
		GetjILog()->Warning(_T("FILE SIZE > 2048 !!"));
		return false;
	}
	strcpy(codeS.buf , nUNI::scb2048_t(code.c_str()).getA());
	pBE->m_pToTestServer->WritePacket(&nTestCentralServer::WRITE_TA_RUN_DUMMY_SCRIPT(sendBuf,codeS));
	return true;

}

jCONSOLE_CMD_AUTO(jSERVER_NAME,run_central_script,0,"Run sq script at TestCentralServer (2048 CHAR)","<SQ_FILE>")
{

	PlugIn_TestAdminConsole* pP = PlugIn_TestAdminConsole::Get();
	if(!pBE->m_pToTestServer)
	{
		GetjILog()->Warning(_T("pBE->m_pToTestServer==NULL."));
		return false;
	}
	nswb4000_t sendBuf;
	sq_code_t codeS;
	std::tstring code;
	nFileSystem::jFolder dir;
	read_file(arg[0].c_str(), code);
	if(code.size() >= 2048)
	{
		GetjILog()->Warning(_T("FILE SIZE > 2048"));
		return false;
	}
	strcpy(codeS.buf , nUNI::scb2048_t(code.c_str()).getA());
	pBE->m_pToTestServer->WritePacket(&nTestCentralServer::WRITE_TA_RUN_CENTRAL_SCRIPT(sendBuf,codeS));
	return true;
}




jCONSOLE_CMD_AUTO(jSERVER_NAME,cmd,0,"dummid (all = 모든더미), (0=test server). 공백있으면안됨"
				  ,"<dummyid> <category> <cmd> [1] [2] [3] [4] [5] [6] [7] [8]")
{
	vector<tstring> send_arg;
	for(int i=3; i<arg.size(); ++i)
	{
		send_arg.push_back(arg[i]);
	}

	nswb2048_t buf;

	ta_PLUGIN(pP);
	if(pP && pBE->m_pToTestServer)
		pBE->m_pToTestServer->WritePacket(&nTestCentralServer::WRITE_TA_RUN_CONSOLE_CMD(buf
		, jt_atoi(arg[0].c_str())
		, arg[1].c_str()
		, arg[2].c_str()
		, send_arg
		));

	return true;
}


jCONSOLE_CMD_AUTO(jSERVER_NAME,get_dummy_info,0,"Print dummy client info list to connected testCentralServer","")
{
	GetjILog()->Log(_T("=========== g_DummyList = %d ============="),g_DummyList.size());
	g_DummyList_it it = g_DummyList.begin(), ie = g_DummyList.end();
	fname_t buf;
	for(;it!=ie;++it)
	{
		S_TS2TA_CLIENT_CONNECT_INFO& v = it->second;
		nInterface::g_pjINet_OGS->GetUtil()->Addr2String(v.ip,buf);
		GetjILog()->Log(_T("%s : %s") 
			, jT(v.name)
			, jT(buf) );
		//it->second.DebugPrint(true);
	}
	return true;
}


jCONSOLE_CMD_AUTO(jSERVER_NAME,server_list,0,"서버리스트 보기","<file | console> <isFileOpen>")
{
	ta_PLUGIN(pP);
	nswb256_t buf;
	pBE->m_pS_ToGMServer->WritePacket(&nGMServer::WRITE_O2C_GET_SERVER_LIST(buf, arg[0]==jS(file) ? 1 : 0 , jt_atoi(arg[1].c_str() ) ) );
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
static void jSchedule_Notice(nEVENT::jIMessage* pM)	
{		
	//jmNoticeInfo* p = (jmNoticeInfo*)pM->GetArg(0)->GetUserData();

	//GetjILog()->Log(TEXT("ddd [%d] %s\n"), p->type, (char*)p->msg.c_str());
	GetjILog()->Log(TEXT("jSchedule_Notice\n"));
	if( pM && pM->GetArgCount()== 4 )
	{
		int nType = pM->GetArg(0)->Get_int();
		int nColor = pM->GetArg(1)->Get_int();
		cstr target_server = pM->GetArg(2)->Get_cstr();
		cstr noticeMsg = pM->GetArg(3)->Get_cstr();

		//jCONSOLE_CMD_AUTO(jSERVER_NAME,notice,0,"notice send","<type> <msg> [color] [reserve_min] [repeat_count]")

		//tstring szCommand("gm.notice");
		tname1024_t szOutFile;
		jt_sprintf(szOutFile, _T("$@gm.notice %d %s %s %d"), nType, noticeMsg, target_server, nColor );

		ta_PLUGIN( pF );	
		if( pF )
		{
			nswb1024_t sendBuf;
			if(pF->m_pS_ToGMServer && pF->m_pS_ToGMServer->IsConnected())
			{
				nGMServer::S_OP_ECHO data;
				data.set_msg(szOutFile);
				pF->m_pS_ToGMServer->WritePacket(&nGMServer::WRITE_OP_ECHO(sendBuf,data));
				return;
			}
			else
				GetjILog()->Warning(_T("socket is not connected"));
		}	
	}
	return;
}	

bool  IsReservedTime( cstr szReserveTime )
{	
	fname_t buf;
	SYSTEMTIME st;
	GetLocalTime(&st);	
	jt_sprintf(buf, _T("%d-%02d-%02d,%02d:%02d:%02d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond );	

	int nR = jt_strncmp( buf, szReserveTime, 19 );
	if( nR >= 0 ) /*szReserveTime 값이 현재 시간 보다 작거나 같으면 */
		return true;

	return false;
}

static void jSchedule_Notice_ReserveDate(nEVENT::jIMessage* pM)	
{		
	GetjILog()->Log(TEXT("jSchedule_Notice_ReserveDate\n"));
	if( pM && pM->GetArgCount()== 7 )
	{
		//예약 시간이 되었다면
		if( IsReservedTime( pM->GetArg(6)->Get_cstr() ) )
		{
			int nType = pM->GetArg(0)->Get_int();
			int nColor = pM->GetArg(1)->Get_int();
			int nMin = pM->GetArg(2)->Get_int();
			int nCount = pM->GetArg(3)->Get_int();			
			cstr target_server = pM->GetArg(4)->Get_cstr();
			cstr msg = pM->GetArg(5)->Get_cstr();			

			ta_PLUGIN( pF );	
			if( pF )
			{
				nEVENT::jIMessage* p = pF->m_pMM->Regist_TimeBaseAndCount( 0, jSchedule_Notice, 4, nMin * 5.0f, nCount );	
				if( p )
				{								
					// .T() 그들의 형으로 바꾼다.
					p->GetArg(0).T() = (int)nType;
					p->GetArg(1).T() = (int)(nColor);
					p->GetArg(2).T() = target_server;
					p->GetArg(3).T() = (msg);					
				}
				p->DoWakeUp();

			}
			//기존 날짜예약을 체크하기 위한 스케쥴링 메세지 삭제
			pM->Erase();
		}			
	}
	return;
}	
/////////////////////////////////////////////////////////////////////////////////////////////////

jCONSOLE_CMD_AUTO(jSERVER_NAME,notice_reserve_file,0,"gmtool :send notice by xml file", "<r:\\xml\\AqNotice.xml> <tag>")
{
	jCONSOLE_PARAM_END(xml_common_load_list);
	XML_COMMON_LOAD_9898( pD, pE, file.c_str(), tag.c_str() );

	//예약 정보 얻어오기
	if(pE->GetType()!= jIVar::EDcstr)
	{
		GetjILog()->Warning(_T("notice contents not found : "));
		return false;
	}
	jIVar_Attribute(int , repeat_count, 1, pE);
	jIVar_Attribute(int , reserve_min, 0, pE);
	jIVar_Attribute(int , color, 0, pE);
	jIVar_Attribute(int , type, 0, pE);
	jIVar_Attribute(cstr, date_time, _T(""), pE);
	jIVar_Attribute(cstr, target_server, _T("RL"), pE);

	ta_PLUGIN( pF );	
	nEVENT::jIMessage* p = NULL;
	// 예약 날짜시간이 있다면 
	if ( jt_strlen(date_time) > 0 )
	{
		// 2009/03/26 HMC
		// 1분 만다 체크 카운트는 99999 가 의미 하는 부분은 무한으로 돈다.(기존 구조를 활용하기 위해 )
		// 초기 99999 로 돌다. 실제 예약 시간이 되면예약 카운트로 값이 변경됩니다.
		// ex) 99999 -> 예약시간 완료 -> 99999 에서 예약카운트값 2 로 변경

		p = pF->m_pMM->Regist_TimeBaseAndCount( 0, jSchedule_Notice_ReserveDate,7, 10.0f, 99999);	
		if( p )
		{		
			p->GetArg(0).T() =(int)type;
			p->GetArg(1).T() =(int)color;
			p->GetArg(2).T() =(int)reserve_min;
			p->GetArg(3).T() =(int)repeat_count;
			p->GetArg(4).T() =target_server;
			p->GetArg(5).T() =pE->Get_cstr();		
			p->GetArg(6).T() =date_time;
			p->DoWakeUp();

		}
	}	
	else
	{
		p = pF->m_pMM->Regist_TimeBaseAndCount( 0, jSchedule_Notice, 4, reserve_min * 5.0f, repeat_count);	
		if( p )
		{			
			p->GetArg(0).T() = (int)type;
			p->GetArg(1).T() = (int)color;
			p->GetArg(2).T() = target_server;
			p->GetArg(3).T() = pE->Get_cstr();
			p->DoWakeUp();

		}
	}		

	GetjIXml()->UnLoad(pD);

	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,notice_file,0,"gmtool :send notice by xml file", "<r:\\xml\\AqNotice.xml> <tag>")
{
	using namespace nGMServer;

	jCONSOLE_PARAM_END(xml_common_load_list);
	XML_COMMON_LOAD_9898( pD, pE, file.c_str(), tag.c_str() );

	nUtil::jMemoryChunk mc;
	mc.init(4000);
	pE->writeChunk(mc);

	jCREATE_INTERFACE_AUTO(pZip, nMech::nUtil::jIZipBuffer);
	if( pZip.empty())
	{
		GetjILog()->Error(_T("jCREATE_INTERFACE_AUTO(pZip, nMech::nUtil::jIZipBuffer);" ) );
		return false;
	}
	pZip->Init(mc.GetBuffer() , mc.size());

	S_O2C_NtyNotice pk;
	pk.xml_len = pZip->GetZipSize();
	if(pk.xml_len >4000)
	{
		GetjILog()->Warning(_T("xml message is long : %d"),pk.xml_len);
		return true;
	}

#if 0
	if(pk.xml_len>0)
	{
		jCREATE_INTERFACE_AUTO(pUnZip, nMech::nUtil::jIUnZipBuffer);
		if( pUnZip.empty())
		{
			GetjILog()->Warning(_T("nMech::nUtil::jIUnZipBuffer not found"));
			return false;
		}
		pUnZip->Init(pZip->GetZipBuff() , abs(pk.xml_len));
		//mc.SetBuffer(pUnZip->GetUnZipBuff(),pUnZip->GetUnZipSize());
		jAssert0(mc.size() == pUnZip->GetUnZipSize());
		int ret = memcmp(mc.GetBuffer() , pUnZip->GetUnZipBuff(), mc.size());
		jAssert0(ret==0);
		pE->EraseChild();
		nUtil::jMemoryChunk mc1;
		mc1.SetBuffer(pUnZip->GetUnZipBuff() , pUnZip->GetUnZipSize());

		pE->readChunk(mc1);
		pE->DebugPrint(true);

	}

#endif


	pk.xmlBuffer.resize(abs(pk.xml_len));
	memcpy(&pk.xmlBuffer[0], pZip->GetZipBuff() , abs(pk.xml_len));

	nswb4000_t buf;
	PlugIn_TestAdminConsole* pP = PlugIn_TestAdminConsole::Get();
	pBE->m_pS_ToGMServer->WritePacket(&WRITE_O2C_NtyNotice(buf, pk));
	GetjIXml()->UnLoad(pD);
	return true;
}
jCONSOLE_CMD_AUTO(jSERVER_NAME,add_user,0,"gmtool : add gm account ", "<level> <id> <pwd> <note>")
{
	nswb1024_t buf;
	PlugIn_TestAdminConsole::Get()->m_pS_ToGMServer->WritePacket(
		&WRITE_O2C_ReqAddAccount(buf, jt_atoi(arg[0].c_str()) , jA(arg[1]) , jA(arg[2]) , jW(arg[3]) ) );
	return true;
}
jCONSOLE_CMD_AUTO(jSERVER_NAME,del_user,0,"gmtool : delete gm account ", "<id>")
{
	nswb1024_t buf;
	PlugIn_TestAdminConsole::Get()->m_pS_ToGMServer->WritePacket(
		&WRITE_O2C_DelAccount(buf, jA(arg[0]) ) );
	return true;
}
jCONSOLE_CMD_AUTO(jSERVER_NAME,get_accounts,0,"gmtool : get gm account list", "")
{
	nswb1024_t buf;
	PlugIn_TestAdminConsole::Get()->m_pS_ToGMServer->WritePacket(&WRITE_O2C_Get_Account_List(buf) );
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,user_list,0,"Print user info list","< file | console > [file_not_open]")
{
#define jCONSOLE_PARAM_user_list(X,Y) X(outType,tstring) Y(file_not_open,bool,false)
	jCONSOLE_PARAM_END(user_list);

	ta_PLUGIN(pP);

	::g_cmdInterface.SetType( jmCmdInfoInterface::eVLT_USER_LIST, outType, file_not_open );

	nswb256_t buf;
	pBE->m_pS_ToGMServer->WritePacket(&nGMServer::WRITE_O2C_GET_USER_LIST(buf));	
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,user_block_list,0,"Print user BlockInfo List", "<file | console > [file_not_open]")
{
#define jCONSOLE_PARAM_userblock_list(X,Y) X(outType,tstring) Y(file_not_open,bool,false)
	jCONSOLE_PARAM_END(userblock_list);

	ta_PLUGIN(pP);

	::g_cmdInterface.SetType( jmCmdInfoInterface::eVLT_USER_BLOCKLIST, outType, file_not_open );

	nswb256_t buf;
	pBE->m_pS_ToGMServer->WritePacket(&nGMServer::WRITE_O2C_BLOCK_USER_LIST(buf));
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,user_block,0,"Block User", "<NickName> < new | add | clear > <day>")
{
	if( arg.size() < 3 )
		return false;

	uint8 nSubType = OP_UserBlockInfo::eBST_NONE;
	if( arg[1] == jS(new))
		nSubType = OP_UserBlockInfo::eBST_NEW;
	else if( arg[1] == jS(add) )
		nSubType = OP_UserBlockInfo::eBST_ADD;
	else if( arg[1] == jS(clear) )
		nSubType = OP_UserBlockInfo::eBST_CLEAR;
	else
		return false;

	ta_PLUGIN(pP);
	nswb256_t buf;

	vector<OP_UserBlockInfo>  blockInfo;
	blockInfo.resize(1);
	jw_strncpy( blockInfo[0].nickName, jW(arg[0].c_str()), 32-1);
	blockInfo[0].nType = OP_UserBlockInfo::eBT_USER;
	blockInfo[0].nSubType = nSubType;
	blockInfo[0].timeInfo.day = jt_atoi( arg[2].c_str());

	pBE->m_pS_ToGMServer->WritePacket(&nGMServer::WRITE_O2C_BLOCK_USER(buf, blockInfo ));
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,user_block_file,0,"Block User From File", "<R:\\xml\\AQUserBlockList.xml> <tag>")
{
	jCONSOLE_PARAM_END(xml_common_load_list);
	XML_COMMON_LOAD_9898( pD, pE, file.c_str(), tag.c_str() );

	ta_PLUGIN(pP);
	nGMServer::S_O2C_BLOCK_USER sendPk;
	nswb4000_t buf;

	pE = pE->begin();
	jrFOR(pE)
	{			
		jIVar_Attribute(int, time_day, 0, pE);
		jIVar_Attribute(int, time_day_add, 0, pE);		

		OP_UserBlockInfo tmInfo;
		jw_strncpy( tmInfo.nickName , jW(pE->Get_cstr()), 32-1 );
		tmInfo.timeInfo.day = time_day + time_day_add;
		tmInfo.nType = OP_UserBlockInfo::eBT_USER;
		if( time_day > 0 )
			tmInfo.nSubType = OP_UserBlockInfo::eBST_NEW;
		else if( time_day_add > 0 )
			tmInfo.nSubType = OP_UserBlockInfo::eBST_ADD;
		else
			tmInfo.nSubType = OP_UserBlockInfo::eBST_CLEAR;

		sendPk.blockInfo.push_back( tmInfo );
		// 전송시 제한 필요 
		if( sendPk.blockInfo.size() >= 40 )
		{
			pBE->m_pS_ToGMServer->WritePacket(&nGMServer::WRITE_O2C_BLOCK_USER(buf, sendPk ));	
			sendPk.blockInfo.clear();
		}
	}	
	if( !sendPk.blockInfo.empty())
		pBE->m_pS_ToGMServer->WritePacket(&nGMServer::WRITE_O2C_BLOCK_USER(buf, sendPk ));	

	GetjIXml()->UnLoad(pD);
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,user_block_chat,0,"gmtool : Block User", "<NickName> < new | add | clear > < L | R | LR > <minute>")
{

#define jCONSOLE_PARAM_user_block_chat_list(X,Y) X(id,tstring) 	X(type,tstring) X(area,tstring) Y(mtime,int,0)
	jCONSOLE_PARAM_END(user_block_chat_list);

	uint8 nSubType = OP_UserBlockInfo::eBST_NONE;
	if( type == jS(new))
		nSubType = OP_UserBlockInfo::eBST_NEW;
	else if( type == jS(add) )
		nSubType = OP_UserBlockInfo::eBST_ADD;
	else if( type == jS(clear) )
		nSubType = OP_UserBlockInfo::eBST_CLEAR;
	else
		return false;
	if( area != jS(L) && area != jS(R) && area != jS(LR))
		return false;

	ta_PLUGIN(pP);
	nswb256_t buf;

	vector<OP_UserBlockInfo>  blockInfo;
	blockInfo.resize(1);
	jw_strncpy( blockInfo[0].nickName, jW(id.c_str()), 32-1);
	blockInfo[0].nType = OP_UserBlockInfo::eBT_CHAT;		// 2 채팅블럭
	blockInfo[0].nSubType = nSubType;	 
	ja_strncpy( blockInfo[0].szArea, area.c_str(), 2 );		
	blockInfo[0].timeInfo.day = mtime;

	pBE->m_pS_ToGMServer->WritePacket(&nGMServer::WRITE_O2C_BLOCK_USER(buf, blockInfo ));
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,user_block_chat_file,0,"Block User From File", "<R:\\xml\\AqUserChatBlockList.xml> <tag>")
{
	jCONSOLE_PARAM_END(xml_common_load_list);
	XML_COMMON_LOAD_9898( pD, pE, file.c_str(), tag.c_str() );

	ta_PLUGIN(pP);
	nGMServer::S_O2C_BLOCK_USER sendPk;
	nswb4000_t buf;

	pE = pE->begin();
	jrFOR(pE)
	{			
		jIVar_Attribute(int, block_mintime, 0, pE);
		jIVar_Attribute(int, block_mintime_add, 0, pE);		
		jIVar_Attribute(cstr, zone,_T(""), pE);

		OP_UserBlockInfo tmInfo;
		jw_strncpy( tmInfo.nickName , jW(pE->Get_cstr()), 32-1 );
		tmInfo.timeInfo.minute = block_mintime + block_mintime_add;
		ja_strncpy( tmInfo.szArea, zone, 2 );		
		tmInfo.nType = OP_UserBlockInfo::eBT_CHAT;
		if( block_mintime > 0 )
			tmInfo.nSubType = OP_UserBlockInfo::eBST_NEW;
		else if( block_mintime_add > 0 )
			tmInfo.nSubType = OP_UserBlockInfo::eBST_ADD;
		else
			tmInfo.nSubType = OP_UserBlockInfo::eBST_CLEAR;

		sendPk.blockInfo.push_back( tmInfo );

		// 전송시 제한 필요 
		if( sendPk.blockInfo.size() >= 40 )
		{
			pBE->m_pS_ToGMServer->WritePacket(&nGMServer::WRITE_O2C_BLOCK_USER(buf, sendPk ));	
			sendPk.blockInfo.clear();
		}
	}	
	if( !sendPk.blockInfo.empty())
		pBE->m_pS_ToGMServer->WritePacket(&nGMServer::WRITE_O2C_BLOCK_USER(buf, sendPk ));	

	GetjIXml()->UnLoad(pD);
	return true;
}

//2009/04/07 HMC
jCONSOLE_CMD_AUTO(jSERVER_NAME,user_item_add,0,"Make Add_item", "<szNickName> <item_sid> <item_quantity>")
{
#define jCONSOLE_PARAM_user_item_add_list(X,Y) X(id,tstring) X(sid,int) X(num,int)
	jCONSOLE_PARAM_END(user_item_add_list);

	ta_PLUGIN(pP);	
	vector<OP_AddItemInfo>  addList;
	nswb256_t buf;

	addList.resize(1);	
	jw_strncpy( addList[0].nickName, jW( id.c_str() ), 32-1);
	addList[0].sid = sid;
	addList[0].num = num;	

	pBE->m_pS_ToGMServer->WritePacket(&nGMServer::WRITE_O2C_ADD_ITEM(buf, addList ));
	return true;
}

//2009/04/09 HMC
jCONSOLE_CMD_AUTO(jSERVER_NAME,user_item_add_file,0,"Make Add_item From File", "<AqUserItemAddList.xml> <tag>")
{
	jCONSOLE_PARAM_END(xml_common_load_list);
	XML_COMMON_LOAD_9898( pD, pE, file.c_str(), tag.c_str() );

	pE = pE->Find(jS(item_list));
	if( !pE )
	{
		GetjILog()->Warning(_T("invalid tag name "));
		return false;
	}

	struct stMakeItemInfo	{	int sid;uint8 quntity;	};
	vector< stMakeItemInfo > makeItemList;
	pE = pE->begin();
	jrFOR(pE)
	{				
		stMakeItemInfo t;
		jIVar_Attribute(int , sid, 0, pE);
		jIVar_Attribute(int , quantity, 0, pE);

		t.sid = sid;
		t.quntity = quantity;
		makeItemList.push_back( t );
	}			

	// 적용 플레이어 리스트 받아오기 
	pE = pD->Find(arg[1].c_str())->Find( jS( apply_user ));
	if(!pE )
	{
		GetjILog()->Warning(_T("invalid apply_user"));
		return false;
	}
	/////////////////////////////////////////////////////////////////////////
	vector<OP_AddItemInfo>  addList;
	ta_PLUGIN(pP);
	nswb4000_t buf;
	/////////////////////////////////////////////////////////////////////////
	pE = pE->begin();
	jrFOR(pE)
	{	
		if( jt_strcmp(pE->GetTagName(), _T("nickname") ) == 0 )
		{
			OP_AddItemInfo addInfo;
			jw_strncpy( addInfo.nickName, jW(pE->Get_cstr()), 32-1 );
			for( int i=0; i < makeItemList.size(); i++ )
			{
				addInfo.sid = makeItemList[i].sid;
				addInfo.num = makeItemList[i].quntity;
				addList.push_back( addInfo );
				if( addList.size() > 40 )
				{					
					//for( int i=0; i < addList.size(); i++ )
					//	GetjILog()->Log(_T("%s/%d/%d"), addList[i].nickName, addList[i].sid, addList[i].num );

					pBE->m_pS_ToGMServer->WritePacket(&nGMServer::WRITE_O2C_ADD_ITEM(buf, addList ));
					addList.clear();
				}
			}								
		}
	}

	if( !addList.empty())
	{
		/*for( int i=0; i < addList.size(); i++ )
		GetjILog()->Log(_T("%s/%d/%d"), addList[i].userID, addList[i].sid, addList[i].num );*/

		pBE->m_pS_ToGMServer->WritePacket(&nGMServer::WRITE_O2C_ADD_ITEM(buf, addList ));
	}

	GetjIXml()->UnLoad(pD);
	return true;
}

//2009/04/08 HMC
jCONSOLE_CMD_AUTO(jSERVER_NAME,user_info_change,0,"Modify User info change exp,gamemoney", "<szUserID> <exp | gamemoney> <new_value>")
{
#define jCONSOLE_PARAM_user_info_change_list(X,Y) X(id,tstring) X(type,tstring) X(value,int)
	jCONSOLE_PARAM_END(user_info_change_list);

	ta_PLUGIN(pP);
	nswb256_t buf;
	vector<OP_ChangeUserInfo>  userList;
	userList.resize(1);

	if( type == jS(exp) )
		userList[0].eUCT_Type = OP_ChangeUserInfo::eUCT_EXP;
	else if( type == jS(gamemoney) )
		userList[0].eUCT_Type = OP_ChangeUserInfo::eUCT_GAMEMONEY;
	else
		return false;

	jw_strncpy( userList[0].nickName, jW(id.c_str()), 32-1);
	userList[0].value = value;	

	pBE->m_pS_ToGMServer->WritePacket(&nGMServer::WRITE_O2C_CHANGE_USERINFO(buf, userList ));
	return true;
}

//2009/04/08 HMC
jCONSOLE_CMD_AUTO(jSERVER_NAME,user_info_change_file,0,"[From File] user info change exp,gamemoney", "<AqUserChangeInfoList.xml> <tag>")
{
	jCONSOLE_PARAM_END(xml_common_load_list);
	XML_COMMON_LOAD_9898( pD, pE, file.c_str(), tag.c_str() );
	vector<OP_ChangeUserInfo>  userList;

	pE = pE->begin();
	jrFOR(pE)
	{				
		jIVar_Attribute(int , exp, 0, pE);
		jIVar_Attribute(int , money, 0, pE);

		OP_ChangeUserInfo addInfo;

		jw_strncpy( addInfo.nickName, jW( pE->Get_cstr()), 32-1);

		if( exp > 0 )				
		{
			addInfo.eUCT_Type = OP_ChangeUserInfo::eUCT_EXP;
			addInfo.value = exp;
			userList.push_back( addInfo );
		}		
		if( money > 0)
		{
			addInfo.eUCT_Type = OP_ChangeUserInfo::eUCT_GAMEMONEY;
			addInfo.value = money;
			userList.push_back( addInfo );
		}		
	}			

	/////////////////////////////////////////////////////////////////////////
	ta_PLUGIN(pP);
	nswb4000_t buf;
	/////////////////////////////////////////////////////////////////////////
	if( !userList.empty())
	{
		/*for( int i=0; i < userList.size(); i++ )
		GetjILog()->Log(_T("%s/%d/%d"), userList[i].userID, userList[i].eUCT_Type, userList[i].value );*/

		pBE->m_pS_ToGMServer->WritePacket(&nGMServer::WRITE_O2C_CHANGE_USERINFO(buf, userList ));
	}

	GetjIXml()->UnLoad(pD);
	return true;
}


#endif 
