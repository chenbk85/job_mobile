#include <gateway/database.hpp>
#include <sstream>
#include <boost/format.hpp>
#include <stdlib.h>

#include <yaml-cpp/yaml.h>

#include "stdafx.h"


#define BOOST_TEST_MODULE BaseballServerGate
#include <boost/test/unit_test.hpp>
#include "logdef.h"
using namespace boost::unit_test_framework;


jUser::~jUser()
{
	if(is_inited==false) return;

	s_tbl_user* user = g_jUser.get_tbl_user();
	jRETURN(user);//!!
	fname_t buf;
	user->set_time_last_logout(nOS::current_SYSTEMTIME(buf));

	nProtoHelper::message_file_save(g_jUser.m_MemberInfo.nick_name().c_str()
		,g_jUser.db_id() ,g_jUser.m_GameUserInfo);

	cout << __FUNCTION__;
}


BOOST_AUTO_TEST_CASE( my_test )
{
	// seven ways to detect and report the same error:
	BOOST_CHECK( 4 == 4 );        // #1 continues on error

	BOOST_REQUIRE( 4 == 4 );      // #2 throws on error

	// 	BOOST_ERROR( "Ouch..." );            // #3 continues on error
	// 	BOOST_FAIL( "Ouch..." );             // #4 throws on error
	// 
	// 	BOOST_CHECK_MESSAGE( 4 == 4,  // #6 continues on error
	// 		"add(..) result: " << 4 );

	BOOST_CHECK_EQUAL( 4, 4 );	  // #7 continues on error
}


/* -------------------------------------------------------------------------- */


#if 0
static std::string      db_ip;
static unsigned short   db_port			= 0;
static std::string      db_user			= "";
static std::string      db_password		= "";
static int              db_retry_time	= 0;
static int              db_tries		= 0;
#endif


struct channel
{
	int person;
	int max_user;
	int low_rank;
	int high_rank;
	int enter;
};

static std::vector<struct channel> channels_;

jUser g_jUser;

/* -------------------------------------------------------------------------- */

::Database::Database(MSG::Gateway& gateway):
    MSG::Database(gateway)
{
	g_jUser.clear();
}

/* -------------------------------------------------------------------------- */


::Database::~Database()
{
	LOG_DEBUG("");
}

/* -------------------------------------------------------------------------- */

void test_message_save()
{
	int ppid = 33;
	nProtoHelper::message_init("test",ppid,g_jUser.m_GameUserInfo);
	nProtoHelper::message_file_save("test",ppid,g_jUser.m_GameUserInfo);
	g_jUser.m_GameUserInfo.mutable_game_info()->mutable_m_tbl_user(0)->set_db_id(11111);
	GameUserInfo    _GameUserInfo;
	bool is = nProtoHelper::message_file_load("test",ppid , g_jUser.m_GameUserInfo);
	jCHECK(is);
	jCHECK(g_jUser.m_GameUserInfo.game_info().m_tbl_user(0).db_id() == ppid);
	nProtoHelper::message_print(g_jUser.m_GameUserInfo.game_info().m_tbl_user(0));
}

static Gateway* g_pGate=0;
void _jConsolePrinterFunc( tcstr szString,bool bAdd )
{
	if(g_pGate)
	{
		g_pGate->info("uid=%d, %s",g_jUser.db_id() , szString);
	}
	if(bAdd)
	{
		cout << szString;
	}
	else
	{
		cout << endl << szString;
	}
}


void
::Database::initialize(const std::string& config)
{
	g_jUser.m_eEUserGPS = eUGPS_LOGIN;
	g_pGate = &gateway_;

	LOG_DEBUG("");
 	gateway_.info("test %d", 1);
 	gateway_.debug("test %d", 1);
 	gateway_.warning("test %d", 1);
 	gateway_.error("test %d", 1);

	LOG_DEBUG(".");	

	// _ORACLE
	g_pDB = this;

    try
    {
        std::istringstream in(config);

        YAML::Parser parser(in);
        
        YAML::Node doc;

        parser.GetNextDocument(doc);

        // 서비스 정보 읽어오기
        const YAML::Node& service = doc["service"];
//        service["id"] >> service_id;
	service["notice-file"] >> notice_filename_;

    #if 0
 
        // 디비 정보 읽어오기
        const YAML::Node& db = doc["db"];
        db["ip"] >> db_ip;
        db["port"] >> db_port;
        db["user"] >> db_user;
        db["password"] >> db_password;
        db["retry_time"] >> db_retry_time;
        db["tries"] >> db_tries;

        std::cout << "ip : " << db_ip << std::endl;
        std::cout << "port : " << db_port << std::endl;
        std::cout << "user : " << db_user << std::endl;
        std::cout << "password : " << db_password << std::endl;
        std::cout << "retry_time : " << db_retry_time << std::endl;
        std::cout << "tries : " << db_tries << std::endl;

		LOG_DEBUG("ip = " << db_ip);
		LOG_DEBUG("port = " << db_port);
		LOG_DEBUG("user = " << db_user);
		LOG_DEBUG("password = " << db_password);
		LOG_DEBUG("retry_time = " << db_retry_time);
		LOG_DEBUG("tries = " << db_tries);

    #endif

        // 채널 정보 분석 해서 저장 해 놓기
        const YAML::Node& channels = doc["channels"];
        std::cout << "channels : " << std::endl;
        for(unsigned i = 0; i < channels.size(); i++)
        {
            const YAML::Node& c = channels[i];

            int id;

            struct channel info;

            c["id"] >> id;
            c["max_user"] >> info.max_user;
            c["low_rank"] >> info.low_rank;
            c["high_rank"] >> info.high_rank;
            info.enter = 0;
            info.person = 0;

            channels_.push_back(info);

            std::cout << "category=" << id << 
                ":max_user=" << info.max_user << 
                ":low_rank=" << info.low_rank << 
                ":high_rank=" << info.high_rank << 
                ":person=" << info.person <<
                ":Enter=" << info.enter << std::endl;
        }
		
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
		LOG_DEBUG("Exception: " << e.what());
    }
	LOG_DEBUG("");

	extern bool is_db_ok();
	m_is_db_ok = is_db_ok();

}

//



/* -------------------------------------------------------------------------- */

bool
::Database::load_user_info(int64_t ppid,  // UReqConnect에서 호출됨.
						 const MemberInfo& mi)
{
	LOG_DEBUG("");

	string sOrgLogFile = nMech::nInterface::g_pjILog->GetFileName();
	fname_t szLogFile;
	jt_sprintf(szLogFile, "%s_gate_%lld", sOrgLogFile.c_str(), (long long int)ppid);
	nMech::nInterface::g_pjILog->SetFileName(szLogFile);
	LOG_DEBUG("szLogFile = " << szLogFile);

	g_jUser.is_inited=true;
	assert(ppid==mi.game_id());
	cstr szID = mi.nick_name().c_str();

	s_tbl_user* user = 0;
	bool isExist = false;
	if(!m_is_db_ok)
	{
		isExist = nProtoHelper::message_file_load(mi.nick_name().c_str(), ppid , g_jUser.m_GameUserInfo);
		if(!isExist)//디비에 등록이 안된상태. 최초 게임플레이상태.
		{
			LOG_DEBUG("file 생성" );
			//버젼이 다르거나 파일없으면 데이타를 새로 만들어 넣음.
			nProtoHelper::message_init(szID,ppid,g_jUser.m_GameUserInfo);
			mi.SerializeToString(g_jUser.m_GameUserInfo.mutable_member_info()); // pp 정보 저장.
			nProtoHelper::message_file_save(szID,ppid,g_jUser.m_GameUserInfo);
			user = g_jUser.get_tbl_user();
#define i_DEFAULT_ELO_POINT 1000
			if(user)
			{
				user->set_elo_point(i_DEFAULT_ELO_POINT);
			}
			else
			{
				LOG_WARNING("user == NULL");
			}
		}
	}
	else
	{
		nProtoHelper::message_init(szID,ppid,g_jUser.m_GameUserInfo);
		mi.SerializeToString(g_jUser.m_GameUserInfo.mutable_member_info()); // pp 정보 저장.
		user = g_jUser.get_tbl_user();
	}

	g_jUser.m_MemberInfo.CopyFrom(mi);

	LOG_DEBUG("MemberInfo : " << (int)mi.game_id()  << ", " << mi.avatar_url().c_str() << " " << 
			mi.nick_name().c_str() << ", " << (int)mi.gender_option());

	mi.SerializeToString(g_jUser.m_GameUserInfo.mutable_member_info()); // pp 정보 저장.
	DumpGameUserInfo(g_jUser.m_GameUserInfo);
	fname_t szCurrTime;

	user = g_jUser.get_tbl_user();
	jRETURN_ret(false,user);

	user->set_time_last_login(nOS::current_SYSTEMTIME(szCurrTime));

	g_jUser.m_eEUserGPS = eUGPS_DB_LOAD;

	db_load_tbl_user(user, ppid, szID, user->client_os(), user->client_networ());

	/*
	//#--------------------------------------------------------------------------
	// 일일 출석 체크.
	//#--------------------------------------------------------------------------
	nOS::diff_day_t diff = nOS::diff_day(user->time_last_logout().c_str() , user->time_last_login().c_str());
	if(nG::b_IS_GIVE_DAILY_BONUS_TO_ALL->Get_bool())
	{
		diff.first=1;
	}
	if(diff.first || diff.second)
	{
		//출석 보너스 지급.
		g_jUser.m_is_give_daily=true;
		LOG_DEBUG("give daily bonus: time_last_login=%s time_last_logout=%s b_IS_GIVE_DAILY_BONUS_TO_ALL=%d"
			,user->time_last_logout().c_str() ,user->time_last_login().c_str()
			,nG::b_IS_GIVE_DAILY_BONUS_TO_ALL->Get_bool() );
	}
	else
	{
		LOG_DEBUG("NOT give daily bonus : time_last_login=%s time_last_logout=%s "
			,user->time_last_logout().c_str() ,user->time_last_login().c_str() );

	}
	*/

	return true;
}

/* -------------------------------------------------------------------------- */

std::vector<std::string> 
tokenize(const std::string& str,const std::string& delimiters)
{
	std::vector<std::string> tokens;

	// skip delimiters at beginning.
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);

	// find first "non-delimiter".
	std::string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		// found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));

		// skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);

		// find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}

	return tokens;
}


bool 
::Database::get_channel(UAnsChannel& channels,
					  const std::string& channel_info)
{
	std::cerr << "channel info : " << channel_info << std::endl;
	LOG_DEBUG("channel info : " << channel_info);

#if 0
	GameUserInfo info;

	info.ParseFromString(game_user_info);

	int rank = info.game_info().level();

	std::vector<std::string> persons = tokenize(channel_info, ",");     

	for(unsigned i = 0; i < persons.size(); i++)
	{
		channels_[i].person = atoi(persons[i].c_str());
		if ((channels_[i].low_rank <= rank) && 
			(channels_[i].high_rank >= rank))
		{
			channels_[i].enter = 1; 
		}
		else
		{
			channels_[i].enter = 0;
		}
	}
#endif

	channels.clear_channelinfo();

	for(unsigned i = 0; i < channels_.size(); i++)
	{
		Desc* desc = channels.add_channelinfo();
		desc->set_id(i);

		char buffer[200];

		sprintf(buffer, "category=%d:max_user=%d"
			":low_rank=%d:high_rank=%d"
			":person=%d:Enter=%d",
			i,
			channels_[i].max_user,
			channels_[i].low_rank,
			channels_[i].high_rank,
			channels_[i].person,
			channels_[i].enter);

		desc->set_desc(buffer);
	}

	return true; 
}

/* -------------------------------------------------------------------------- */

bool
::Database::get_item_info(UAnsStore& store)
{
	LOG_DEBUG("");

	return false;
}

/* -------------------------------------------------------------------------- */

bool
::Database::query_from_client(const ReqDB& query, AnsDB& result)
{
	//std::cout << endl << __FUNCTION__ << endl;
// 	gateway_.error("=========================================");
// 	LOG_DEBUG("==jLOG=======================================");


	cstr szQuery = query.query().c_str();
	if(!jt_strcmp(szQuery,jS(ug_game)))
	{
		Client_UserGateServer recvMsg;
		UserGateServer_Client sendMsg;
		recvMsg.ParseFromString(query.options());
		if(g_jUser.m_jPacketRecvTimeControl.is_repeated(recvMsg.type()))
		{
			jWARN("ERR_jPacketRecvTimeControl : packet = %d , uid=%lld"
				,recvMsg.type(),g_jUser.db_id());
			jPREPARE_PACKET_UG2X(sd , ans_ug_error);
			sd->set_sys_error_id(jMAKE_ERR(ERR_jPacketRecvTimeControl));
		}
		else
		{
			switch(recvMsg.type())
			{

	#define parse_Client_UserGateServer(DOMAIN,NAME,ORDER)\
			case Client_UserGateServer_Type_##NAME:\
				{\
					bool CB_Client_UserGateServer(jUser*,const s_##NAME&,UserGateServer_Client&,::Database&);\
					LOG_DEBUG("recv : " #NAME);\
					bool is = CB_Client_UserGateServer(&g_jUser,recvMsg.m_##NAME(),sendMsg,*this);\
					if(!is) return false; \
					break;\
				}\

			for_each_Client_UserGateServer(parse_Client_UserGateServer);
			default:
				{
					jWARN("unkown packet : %d", recvMsg.type());
					return false;
				}
			}
		}
		result.set_seq(query.seq());
		result.set_retcode(0);
		result.set_query(jS(ug_game));
		sendMsg.SerializeToString(result.mutable_result());
		return true;
	}

#define jSEND_TO_CLIENT_AnsDB(retcode , msg) \
	result.set_retcode(retcode);\
	result.set_seq(query.seq());\
	result.set_query(query.query());\
	msg.SerializeToString(result.mutable_result());\


	if(!jt_strcmp(szQuery,jS(ug_echo)))
	{
		LOG_DEBUG("ug_echo : ");
		jCHECK(query.params_size()!=0);
		const DBIn& param = query.params(0);
		jSEND_TO_CLIENT_AnsDB(0, param ); 
		return true;
	}
	if(jt_strstr(szQuery,jS(GameInfo)))
	{
		jCHECK(query.params_size()!=0);
		const DBIn& param = query.params(0);
		jCHECK(param.type()==DBIn::INT);
		int index = ja_atoi(param.val().c_str());

		// repeatable 변수는 맨마지막일때 999를 보냄.
#define parse_GameInfo(TABLE,EXCEL_TABLE,SELECT_FIELD)\
		if(jt_strstr(szQuery ,jS(TABLE) ) )\
		{\
			int iSize = g_jUser.size_##TABLE();\
			if(index==0){LOG_DEBUG(jS(TABLE) << ", size = " << iSize << " req index=" << index );}\
			if(index <0 || index >= iSize )\
			{\
				jSEND_TO_CLIENT_AnsDB(10000 , param);\
				return true;\
			}\
			int32 next_index= index+1;\
			if(next_index >= iSize)\
			{ \
				next_index=9999;\
			}\
			/*nProtoHelper::message_print(g_jUser.get_##TABLE(index),g_jUser.db_id());*/\
			/*LOG_DEBUG("jSEND_ TO_CLIENT_AnsDB : %s > next_index=%d index=%d",#TABLE,next_index, index);*/\
			jSEND_TO_CLIENT_AnsDB(next_index, g_jUser.m_GameUserInfo.game_info().m_##TABLE(index));\
			return true;\
		}\

		for_each_GameInfo_Excel_Table(parse_GameInfo)
		else
		{
			jWARN("if(jt_strstr(szQuery,jS(GameInfo))) ... unkown recv : %s",szQuery);
		}
	}

	result.set_retcode(19999);
	jWARN("unkown client request : %s (server sent retcode:%d",szQuery,result.retcode());
	return true;
}

/* -------------------------------------------------------------------------- */
//BaseballServer 에서 UserGateServer로 날라오는 패킷.
bool
::Database::query_from_game(const ReqDB& recvData, AnsDB& sendMsg)
{
	LOG_DEBUG("");
	jRETURN_ret(false, recvData.seq()==IS_BS2UG_PACKET);
	UserGateServer_BaseballServer sd;
	BaseballServer_UserGateServer rd;
	rd.ParseFromString(recvData.options());

	switch(rd.type())
	{
#define jPARSE_PROTO_MESSAGE_BS2UG(DOMAIN,NAME,ORDER)\
case _jJOIN_3(DOMAIN,_Type_,NAME):\
		{\
		LOG_DEBUG("RECV>"   #DOMAIN  "::"  #NAME  "");\
		bool CB_BaseballServer_UserGateServer(jUser* ,const s_##NAME& ,UserGateServer_BaseballServer&,::Database&);\
		bool is = CB_BaseballServer_UserGateServer(&g_jUser,rd.m_##NAME(),sd,*this);\
		if(!is) return false;\
		break;\
	}\

		for_each_BaseballServer_UserGateServer(jPARSE_PROTO_MESSAGE_BS2UG);

	default:
		jERROR("\n[error] unkown packet");
		return false;
	}

	sendMsg.set_seq(IS_BS2UG_PACKET);
	sendMsg.set_query("UserGateServer_BaseballServer");
	sendMsg.set_retcode(0);
	sd.SerializeToString(sendMsg.mutable_result());
	return true;
}

/* -------------------------------------------------------------------------- */
void make_GamePlayInfo(s_game_play_info& gpi)
{ // Auto join시 ug가 bs에게 유저정보를 전달하는 곳.
	gpi.mutable_m_tbl_user()->CopyFrom(*g_jUser.get_tbl_user());
}


const std::string&
::Database::get_gameuserinfo() //주의! 원래는 MSG에서는 GameUserInfo를 보내게 되어 있으나 s_game_play_info정보를 보낸다.
{
	LOG_DEBUG("");

	s_game_play_info gpi;
	make_GamePlayInfo(gpi);
	static std::string temp;
	gpi.SerializeToString(&temp);
	return temp;
}


/* -------------------------------------------------------------------------- */

void 
::Database::update_game_info(int, const std::string& info)
{
	LOG_DEBUG("");
}

/* -------------------------------------------------------------------------- */


void ::Database::send_to_client(const UserGateServer_Client& sendMsg)
{
	std::string message;
	sendMsg.SerializeToString(&message);
	MSG::Database::send_gateway_protocol(message);
}
