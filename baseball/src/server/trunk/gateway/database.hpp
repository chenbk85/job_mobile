#ifndef __NWM_BASEBALL_GATEWAY_DB_H__
#define __NWM_BASEBALL_GATEWAY_DB_H__
#include "gateway/database.hpp"
#include <boost/scoped_ptr.hpp> 
#include <yaml-cpp/yaml.h>
#include "../game/PT_UserGateServer.pb.h"

#include "stdafx.h"


class Database: 
    public MSG::Database
{
public:
                        Database(MSG::Gateway& gateway);

    virtual             ~Database();

    virtual void        initialize(const std::string& config);
	
    virtual const std::string&
                        get_gameuserinfo();

    virtual bool        load_user_info(int64_t game_id,
                                       const MemberInfo& member_info);

    int32_t             get_service_id();

    virtual bool        get_channel(UAnsChannel& channels,
                                    const std::string& channel_info);

    virtual bool        get_item_info(UAnsStore& store);

    bool                get_notice(UAnsNotice& notice);

    // 클라이언트에서 오는 쿼리를 수행해줌
    // false 리턴하면 게이트웨이가 터지도록 되어있음
    virtual bool        query_from_client(const ReqDB& query,
                                          AnsDB& result);

    virtual bool        query_from_game(const ReqDB& query,
                                        AnsDB& result);

    virtual void        update_game_info(int idx,
                                         const std::string& info);

	void send_to_client(const UserGateServer_Client& sendData);



// ---------------------------------------------------------
// _ORACLE코드 시작
// ---------------------------------------------------------
public:

	// _SIMPLE_ 
	Sys_Error_id_t db_load_tbl_user(s_tbl_user* user, int64_t pp_id, std::string nickname, std::string client_os, std::string client_network);
	Sys_Error_id_t db_game_result( const s_tbl_result& gr, const s_result_round_list_t &rr_list, int32_t end_type);
	Sys_Error_id_t db_game_round_result( int64_t game_log_id, const s_result_round_list_t &rr_list);
	Sys_Error_id_t db_insert_game_round_result( int64_t game_log_id, const s_tbl_roundresult& rr);
	
	int64_t db_select_game_round_log_seq();
	bool m_is_db_ok;
};

extern ::Database*  g_pDB;

#endif

