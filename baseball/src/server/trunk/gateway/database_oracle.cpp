// #include <gateway/database.hpp>

#include <sstream>
#include <boost/format.hpp>
#include <stdlib.h>

#include <yaml-cpp/yaml.h>

// _ORACLE
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "stdafx.h"
#include "protocol/ug.pb.h"
#include "gameLogic.pb.h"
#include "gateway/options.hpp"
#include "msg_db/db_client_interface.h" 
#include <sqlrelay/sqlrclient.h>

#include "msg_db/db_client_interface.h"
#include "logdef.h"

//typedef boost::scoped_ptr<DBClientInterface> DBClientInterface_AutoPtr;
struct DBClientInterface_AutoPtr
{
	DBClientInterface* p; 
	DBClientInterface_AutoPtr()
	{
		p = DBClientInterface::create();
	}
	~DBClientInterface_AutoPtr()
	{
		if(!p) return;
		DBClientInterface::destroy(p);
		p = 0;
	}
	DBClientInterface& operator*()		{return *p;}
	DBClientInterface* operator->()		{return p;}
	DBClientInterface* get()			{return p;}

};

bool is_db_ok()
{
	DBClientInterface* p; 
	p = DBClientInterface::create();
	if(!p) return false;
	DBClientInterface::destroy(p);
	return true;
}



::Database*  g_pDB = NULL;

/*
static std::ostringstream _ss_;

static int 
OracleDebugPrintf(const char* format, ...)
{
    va_list args;
    char buffer[1024];
    
    va_start(args, format);
    int ret = vsprintf(buffer, format, args);
    va_end(args);

    _ss_ << buffer;
    std::cout << buffer;
    
    return ret;
}
*/

// MSG procedure 함수로 교체
Sys_Error_id_t 
::Database::db_load_tbl_user(s_tbl_user* user, int64_t pp_id, std::string nickname, std::string client_os, std::string client_network )
{
	jRETURN_ret(false,user);

	std::cout << "DB debug : " << jFUNC << std::endl;

	DBParams in_params;
	DBParams out_params;

	const char *query = "begin BASEBALL.login("		// 프로시저 이름 확인 후 수정 할 것!
		":in0,:in1,:in2,:in3,:in4,:in5,"
		":out0,:out1,:out2,:out3,:out4,:out5,:out6,:out7,:out8,:out9,:out10,"
		":out11,:out12,:out13,:out14,:out15,:out16,:out17,:out18,:out19"
		"); end;";

	in_params.input_bind_integer("in0", pp_id);
	in_params.input_bind_string("in1", "PMANG");
	in_params.input_bind_string("in2", client_os);
	in_params.input_bind_string("in3", client_network);
	in_params.input_bind_string("in4", "yyyy-mm-dd hh24:mi:ss");
	in_params.input_bind_string("in5", nickname);
	
	out_params.output_bind_integer("out0");		// :o_member_id
	out_params.output_bind_integer("out1");		// :o_disconn_count
	out_params.output_bind_integer("out2");		// :o_tot_win
	out_params.output_bind_integer("out3");		// :o_tot_lose
	out_params.output_bind_integer("out4");		// :o_series_result
	out_params.output_bind_integer("out5");		// :o_max_series_win
	out_params.output_bind_integer("out6");		// :o_season_win
	out_params.output_bind_integer("out7");		// :o_season_lose
	out_params.output_bind_integer("out8");		// :o_tot_homerun
	out_params.output_bind_integer("out9");		// :o_tot_strikeout
	out_params.output_bind_integer("out10");	// :o_season_homerun
	out_params.output_bind_integer("out11");	// :o_season_strike
	out_params.output_bind_integer("out12");	// :o_elo_point 
	out_params.output_bind_integer("out13");	// :o_cash_item_point
	out_params.output_bind_string("out14");		// :o_last_login
	out_params.output_bind_string("out15");		// :o_last_logout
	out_params.output_bind_integer("out16");	// :o_series_attend
	out_params.output_bind_string("out17");		// :o_client_os
	out_params.output_bind_string("out18");		// :o_client_network
	out_params.output_bind_integer("out19");	// :o_playtime
		
	DBClientInterface_AutoPtr db;
	if (!db.get())
	{
		std::cout << "DB debug : DBClientInterface_AutoPtr Create Error  !" << std::endl;
		return make_error("ERR_DB_DBClientInterface_IS_NULL");
	}

	DBClientInterface::Error result = db->execute_procedure(query, in_params, &out_params); 

	if (DBClientInterface::E_SUCCESS != result)
	{
		std::cout << "DB debug : execute_procedure : login : Fail !" << std::endl;
		jWARN("%s", db->get_last_error_string().c_str() );
		return make_error("ERR_DB_QUERY_FAIL");
	}

	// 화면 출력
	std::cerr << "o_member_id : "		<< out_params.get_int("out0") << std::endl;
	std::cerr << "pp_id : "				<< pp_id << std::endl;
	std::cerr << "o_disconn_count : "	<< out_params.get_int("out1") << std::endl;
	std::cerr << "o_tot_win : "			<< out_params.get_int("out2") << std::endl;
	std::cerr << "o_tot_lose : "		<< out_params.get_int("out3") << std::endl;
	std::cerr << "o_series_result : "	<< out_params.get_int("out4") << std::endl;
	std::cerr << "o_max_series_win : "	<< out_params.get_int("out5") << std::endl;
	std::cerr << "o_season_win : "		<< out_params.get_int("out6") << std::endl;
	std::cerr << "o_season_lose : "		<< out_params.get_int("out7") << std::endl;
	std::cerr << "o_tot_homerun : "		<< out_params.get_int("out8") << std::endl;
	std::cerr << "o_tot_strikeout : "	<< out_params.get_int("out9") << std::endl;
	std::cerr << "o_season_homerun : "	<< out_params.get_int("out10") << std::endl;
	std::cerr << "o_season_strike : "	<< out_params.get_int("out11") << std::endl;
	std::cerr << "o_elo_point : "		<< out_params.get_int("out12") << std::endl;
	std::cerr << "o_cash_item_point : " << out_params.get_int("out13") << std::endl;
	std::cerr << "o_last_login : "		<< out_params.get_string("out14") << std::endl;
	std::cerr << "o_last_logout : "		<< out_params.get_string("out15") << std::endl;
	std::cerr << "o_series_attend : "	<< out_params.get_int("out16") << std::endl;
	std::cerr << "o_client_os : "		<< out_params.get_string("out17") << std::endl;
	std::cerr << "o_client_network : "	<< out_params.get_string("out18") << std::endl;
	std::cerr << "o_playtime : "		<< out_params.get_int("out19") << std::endl;

	
	// user->set_db_id(out_params.get_int("out0"));
	user->set_db_id(pp_id);		// db_id == pp_id
	user->set_pp_id(pp_id);
	user->set_discon_tot(out_params.get_int("out1"));
	user->set_win_tot(out_params.get_int("out2"));
	user->set_lose_tot(out_params.get_int("out3"));
	user->set_win_tot_continue(out_params.get_int("out4"));
	user->set_win_tot_continue_max(out_params.get_int("out5"));
	user->set_win_season(out_params.get_int("out6"));
	user->set_lose_season(out_params.get_int("out7"));
	user->set_batter_tot_homerun(out_params.get_int("out8"));
	user->set_pitcher_tot_strikeout(out_params.get_int("out9"));
	user->set_batter_tot_homerun_season(out_params.get_int("out10"));
	user->set_pitcher_tot_strikeout_season(out_params.get_int("out11"));
	user->set_elo_point(out_params.get_int("out12"));
	user->set_cash_item_buy_money_amount(out_params.get_int("out13"));
	user->set_time_last_login(out_params.get_string("out14"));
	user->set_time_last_logout(out_params.get_string("out15"));
	user->set_day_continue_attend(out_params.get_int("out16"));
	user->set_client_os(out_params.get_string("get_string"));
	user->set_client_networ(out_params.get_string("out18"));
	user->set_playtime_tot(out_params.get_int("out19"));

	return true;

}

Sys_Error_id_t 
::Database::db_game_result(const s_tbl_result& gr, const s_result_round_list_t &rr_list, int32_t end_type)
{
	int64_t game_log_id = 0;
	// save_game_result 
	const char *query = "begin BASEBALL.save_game_result("		// 프로시저 이름 확인 후 수정 할 것!
		":in0,:in1,:in2,:in3,:in4,:in5,:in6,:in7,:in8,:in9,:in10,:in11,:in12,:in13,:in14,:in15,:in16,:in17,"
		":out0"
		"); end;";

	std::cout << "DB debug : end_type" << end_type << std::endl;

	// 여기에 라운드 리절트에서 업데이트 할 elo_point, homerun, strike 데이터를 추출하는 함수가 필요!
	db_record	win_record;
	memset( &win_record, 0, sizeof(db_record));
	db_record	lose_record;
	memset( &lose_record, 0, sizeof(db_record));

	g_jUser.db_game_record( rr_list, gr.win_uid(), win_record );
	g_jUser.db_game_record( rr_list, gr.lose_uid(), lose_record );

	DBParams in_params;
	DBParams out_params;

	LOG_DEBUG("win_uid = " << gr.win_uid() );
	LOG_DEBUG("win_better = " << gr.win_better() );
	LOG_DEBUG("win_pitcher = " << gr.win_pitcher() );
	LOG_DEBUG("win_score = " << gr.win_score() );
	LOG_DEBUG("win_elo_point = " << gr.win_elo_point() );
	LOG_DEBUG("win_homerun = " << win_record.homerun );
	LOG_DEBUG("win_strikeout = " << win_record.strike );
	LOG_DEBUG("lose_uid = " << gr.lose_uid() );
	LOG_DEBUG("lose_better = " << gr.lose_better() );
	LOG_DEBUG("lose_pitcher = " << gr.lose_pitcher() );
	LOG_DEBUG("lose_score = " << gr.lose_score() );	
	LOG_DEBUG("lose_elo_point = " << gr.lose_elo_point() );
	LOG_DEBUG("lose_elo_point = " << gr.lose_elo_point() );
	LOG_DEBUG("lose_strike = " << lose_record.strike );

	in_params.input_bind_integer("in0", gr.win_uid());
	in_params.input_bind_string("in1", "PMANG");
	in_params.input_bind_integer("in2", gr.win_better());
	in_params.input_bind_integer("in3", gr.win_pitcher());
	in_params.input_bind_integer("in4", gr.win_score());
	in_params.input_bind_integer("in5", gr.win_elo_point());
	in_params.input_bind_integer("in6", win_record.homerun);
	in_params.input_bind_integer("in7", win_record.strike);
	in_params.input_bind_integer("in8", gr.lose_uid());
	in_params.input_bind_string("in9", "PMANG");
	in_params.input_bind_integer("in10", gr.lose_better());
	in_params.input_bind_integer("in11", gr.lose_pitcher());
	in_params.input_bind_integer("in12", gr.lose_score());
	in_params.input_bind_integer("in13", gr.lose_elo_point());				
	in_params.input_bind_integer("in14", lose_record.homerun);
	in_params.input_bind_integer("in15", lose_record.strike);
	in_params.input_bind_integer("in16", gr.play_time_sec());
	in_params.input_bind_string("in17", "1");					// p_end_stat : 게임 종료 조건
	in_params.input_bind_string("in17", boost::lexical_cast<std::string>(end_type));					// p_end_stat : 게임 종료 조건

	out_params.output_bind_integer("out0");	
	
	DBClientInterface_AutoPtr db;
	if (!db.get())
	{
		LOG_WARNING("DB debug : DBClientInterface_AutoPtr Create Error");
		return make_error("ERR_DB_DBClientInterface_IS_NULL");
	}

	DBClientInterface::Error result = db->execute_procedure(query, in_params, &out_params); 

	if (DBClientInterface::E_SUCCESS != result)
	{
		LOG_WARNING("get_last_error_string = " << db->get_last_error_string().c_str() );
		return make_error("ERR_DB_QUERY_FAIL");
	}

	game_log_id = out_params.get_int("out0");
	
	LOG_DEBUG("game_log_id = " << game_log_id );

	Sys_Error_id_t nDBresult = db_game_round_result(game_log_id, rr_list );

	return nDBresult;
}
// DB 라운드 결과 저장
Sys_Error_id_t 
::Database::db_game_round_result( int64_t game_log_id, const s_result_round_list_t &rr_list )
{
	Sys_Error_id_t nDBresult;

	for(int i=0; i< rr_list.size() ; ++i)
	{
		const s_tbl_roundresult& rr = rr_list.Get(i).m_tbl_roundresult();

		nDBresult = db_insert_game_round_result(game_log_id, rr);
	}

	return nDBresult;
}

int64_t 
::Database::db_select_game_round_log_seq()
{
	int64_t seq_id 	= 0;

	const char* select_query = 
		"select GAME_ROUND_LOG_SEQ.nextval from dual";

	DBClientInterface_AutoPtr db;
	if (!db.get())
	{
		return make_error("ERR_DB_DBClientInterface_IS_NULL");
	}

	DBParams					params;
	std::vector<DBResultRow> 	result_rows;

	if (DBClientInterface::E_SUCCESS != db->execute_query(select_query, params, &result_rows))
	{
		LOG_WARNING("get_last_error_string = " << db->get_last_error_string().c_str() );
		return make_error("ERR_DB_QUERY_FAIL");
	}
	if (result_rows.empty())
	{
		LOG_WARNING("ERR_DB_NO_RECORD");
		return make_error("ERR_DB_NO_RECORD");
	}
	else
	{
		for( unsigned int row = 0; row < result_rows.size(); row++ )
		{
			seq_id = boost::lexical_cast<int>(result_rows[row][0]);
			LOG_DEBUG("seq_id = " << seq_id );
		}	
	}

	return seq_id;
}
// DB 라운드 결과 저장
Sys_Error_id_t 
::Database::db_insert_game_round_result( int64_t game_log_id, const s_tbl_roundresult& rr )
{
	int64_t seq_id 	= db_select_game_round_log_seq();

	if( seq_id == 0 )
	{
		LOG_WARNING("ERR_DB_NO_RECORD: seq_id = " << seq_id);
		return make_error("ERR_DB_QUERY_FAIL");
	}
	const char* insert_query = 
		"INSERT INTO game_round_log(GAME_ROUND_LOG_ID, GAME_LOG_ID, SYS_BATTER_ID, SYS_PITCHER_ID, ROUND_NUM,"
		"PITCHING_TYPE, PITCHING_SPEED, PITCHING_SKILL, PITCHING_CTRL_TIMMING, PITCHING_GESTURE, GESTURE_ERROR_CNT,"
		"BATTING_TYPE, HIT_TIMMING, HIT_TYPE, ATTACK_MEMBER_ID, BATTER_SCORE, RUNNER_CNT )"
		"VALUES(:seq_id, :GAME_LOG_ID, :SYS_BATTER_ID, :SYS_PITCHER_ID, :ROUND_NUM, :PITCHING_TYPE,"
		":PITCHING_SPEED, :PITCHING_SKILL, :PITCHING_CTRL_TIMMING, :PITCHING_GESTURE, :GESTURE_ERROR_CNT, "
		":BATTING_TYPE, :HIT_TIMMING, :HIT_TYPE, :ATTACK_MEMBER_ID, :BATTER_SCORE, :RUNNER_CNT )";
	
	DBClientInterface_AutoPtr db;
	if (!db.get())
	{
		LOG_WARNING("ERR_DB_DBClientInterface_IS_NULL");
		return make_error("ERR_DB_DBClientInterface_IS_NULL");
	}

	DBParams					params;
	std::vector<DBResultRow> 	result_rows;

	params.input_bind_integer("seq_id", seq_id);
	params.input_bind_integer("GAME_LOG_ID", game_log_id);
	params.input_bind_integer("SYS_BATTER_ID", rr.used_batter_id());
	params.input_bind_integer("SYS_PITCHER_ID", rr.used_pitcher_id());
	params.input_bind_integer("ROUND_NUM", rr.round_number());
	params.input_bind_string("PITCHING_TYPE", ToString((EPlayerBreakingBall)rr.used_breakingball()));
	params.input_bind_integer("PITCHING_SPEED", rr.used_breakingball_speed());
	params.input_bind_string("PITCHING_SKILL", ToString((EPitcherAbility)rr.used_pitcherability()) );
	params.input_bind_string("PITCHING_CTRL_TIMMING", ToString((ERhythmJudge)rr.pitching_rhythm_judge()) );
	params.input_bind_string("PITCHING_GESTURE", ToString((EGestureType)rr.used_gesturetype()));
	params.input_bind_integer("GESTURE_ERROR_CNT", rr.gesturetype_input_error());
	params.input_bind_string("BATTING_TYPE", ToString((EBatterHitType)rr.batting_hittype()));
	params.input_bind_string("HIT_TIMMING", ToString((ERhythmJudge)rr.batting_timing_judge()));
	params.input_bind_string("HIT_TYPE", ToString((EBatterHitType)rr.hit_type()));
	params.input_bind_integer("ATTACK_MEMBER_ID", rr.uid_attack());
	params.input_bind_integer("BATTER_SCORE", rr.score());
	params.input_bind_integer("RUNNER_CNT", rr.base_runner_state());

	LOG_DEBUG( "GAME_ROUND_LOG_ID : " << seq_id );
	LOG_DEBUG( "game_log_id : "	<< game_log_id );
	LOG_DEBUG( "rr.used_batter_id() : "<< rr.used_batter_id() );
	LOG_DEBUG( "rr.used_pitcher_id() : "<< rr.used_pitcher_id() );
	LOG_DEBUG( "rr.round_number() : "<< rr.round_number() );
	LOG_DEBUG( "rr.used_breakingball() : "<< rr.used_breakingball() );
	LOG_DEBUG( "rr.used_breakingball_speed() : "<< rr.used_breakingball_speed() );
	LOG_DEBUG( "rr.used_pitcherability() : "<< rr.used_pitcherability() );
	LOG_DEBUG( "rr.pitching_rhythm_judge() : "<< rr.pitching_rhythm_judge() );
	LOG_DEBUG( "rr.used_gesturetype() : "<< rr.used_gesturetype() );
	LOG_DEBUG( "rr.gesturetype_input_error() : "<< rr.gesturetype_input_error() );
	LOG_DEBUG( "rr.batting_hittype() : "<< rr.batting_hittype() );
	LOG_DEBUG( "rr.batting_timing_judge() : "<< rr.batting_timing_judge() );
	LOG_DEBUG( "rr.hit_type() : "<< rr.hit_type() );
	LOG_DEBUG( "rr.uid_attack() : "<< rr.uid_attack() );
	LOG_DEBUG( "rr.score() : "<< rr.score() );
	LOG_DEBUG( "rr.base_runner_state() : "<< rr.base_runner_state() );

	if (DBClientInterface::E_SUCCESS != db->execute_query(insert_query, params, &result_rows))
	{
		LOG_WARNING("get_last_error_string = " << db->get_last_error_string().c_str() );
		return make_error("ERR_DB_QUERY_FAIL");
	}

	return 0;
}



