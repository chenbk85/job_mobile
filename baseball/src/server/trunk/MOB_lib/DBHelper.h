/* file : DBHelper.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-04-02 15:29:29
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __DBHelper_header__
#define __DBHelper_header__
#pragma once



#define jFUNC_LOG() jLOG("<<< %s:%d(%s) >>> ",__FUNCTION__,__LINE__,__FILE__);printf("\n");
#define jFUNC_LOG2(name,id) jLOG("<<< %s:%d(%s) %s:%d>>> ",__FUNCTION__,__LINE__,__FILE__,name,id);printf("\n");


#define SERVER_OK 0 // 서버에서 클라로 응답줄때 에러코드중 성공일때.

#include <sstream>


#define for_each_QCT_GAME_VALIABLE(X)\
	X(player_count				,"투수타자모두포함한 카운트")\
	X(win_tot					,"유저의 매치모드에서의 토탈승수")\
	X(win_tot_single			,"유저의 싱글모드에서의 토탈승수")\
	X(win_tot_friend			,"유저의 친구모드에서의 토탈승수")\
	X(user_play_count			,"유저의 매치모드 플레이한 횟수")\
	X(user_play_count_single	,"유저의 싱글모드 플레이한 횟수")\
	X(user_play_count_friend	,"유저의 친구모드 플레이한 횟수")\
	X(better_tot_homerun		,"유저의 토탈 홈런카운트")\
	X(pitcher_tot_strikeout		,"유저의 토탈 스트라이크 수")\
	X(cash_item_buy_count		,"캐쉬템구매갯수")\
	X(cash_item_buy_money_amount,"캐쉬템구매누적액")\
	X(game_money				,"게임머니")\


namespace nProtoHelper
{


// excel에서 뽑은 메세지 구조체들.
// X(TABLE,EXCEL_TABLE,SELECT_FIELD)
#define for_each_nEXCEL_excel_baseball_table_db_proto(X)\
	X(s_tbl_user			,Tbl_User			,db_id )\
	X(s_tbl_result			,Tbl_Result			,db_id )\
	X(s_tbl_roundresult		,Tbl_RoundResult	,db_id )\

// gameLogic.proto의 GameInfo 메세지에 포함된 구조체 리스트.
// X(TABLE,EXCEL_TABLE,SELECT_FIELD)
#define for_each_GameInfo_Excel_Table(X)\
	X(tbl_user			,Tbl_User			,db_id)\

#define for_each_WIN_LOSE(X) X(win) X(lose)

#define for_each_SCORE_RECORD_OBJ(X) \
	X(user) \

#	define __print_field_43(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple) \
		o_stream<< #eng_name << " = " << t.eng_name() << endl;

#	define __print_field_simple_43(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple) \
		o_stream<< " ," << t.eng_name() ; 

#	define __print_data_func_43(TABLE,EXCEL_TABLE,SELECT_FIELD) \
	inline void message_print(const TABLE& t,Tbl_User_id_t uid=0,bool isSimpleLog=false) \
	{\
		std::ostringstream o_stream; \
		if(uid){	o_stream << endl << #TABLE <<"[uid=" << uid <<"]"<< endl;}\
		else{o_stream<< endl << #TABLE << endl;}\
		\
		if(isSimpleLog)\
		{\
			_jJOIN_3(for_each_nEXCEL_,EXCEL_TABLE,_STRUCT_FIELD_all_member)(__print_field_simple_43); o_stream << endl;\
		}\
		else\
		{\
			_jJOIN_3(for_each_nEXCEL_,EXCEL_TABLE,_STRUCT_FIELD_all_member)(__print_field_43); o_stream << endl;\
		}\
		jLOG(o_stream.str().c_str());\
	}


	for_each_nEXCEL_excel_baseball_table_db_proto(__print_data_func_43);



	//X(TYPE, RETURN_TYPE, RETURN_VAL)
#define for_each_default_type_init_value_google(X)\
	X(google::protobuf::int64, google::protobuf::int64, 0)\
	X(int32, int32, 0)\
	X(int16, int16, 0)\
	X(int8, int8, 0)\
	X(uint64, uint64, 0)\
	X(uint32, uint32, 0)\
	X(uint16, uint16, 0)\
	X(uint8, uint8, 0)\
	X(bool,bool , false)\
	X(string,cstr, "NULL")\
	X(char*,cstr,"NULL")\
	X(SYSTEMTIME,cstr,"NULL")\

#	define __proto_23443(TYPE, RETURN_TYPE, RETURN_VAL)	inline RETURN_TYPE proto_field_default_value(TYPE){ return RETURN_VAL;}
	for_each_default_type_init_value_google(__proto_23443)


#	define __init_field_43(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple) \
	t.set_##eng_name(proto_field_default_value(t.eng_name()));\

#	define __init_data_func_43(TABLE,EXCEL_TABLE,SELECT_FIELD)\
	inline void message_init(TABLE& t) \
	{_jJOIN_3(for_each_nEXCEL_,EXCEL_TABLE,_STRUCT_FIELD_all_member)(__init_field_43);}\

	for_each_nEXCEL_excel_baseball_table_db_proto(__init_data_func_43);

	inline void message_init(cstr szID,Tbl_User_id_t ppid, GameUserInfo& v)
	{
		GameInfo* pGameInfo = v.mutable_game_info();
		(*v.mutable_member_info()) = "";
		s_tbl_user* pTbl_User =0;
		if(pGameInfo->m_tbl_user_size())
			pTbl_User = pGameInfo->mutable_m_tbl_user(0);
		else
			pTbl_User = pGameInfo->add_m_tbl_user();

		message_init(*pTbl_User);
		pTbl_User->set_db_id(ppid);
		pTbl_User->set_uname(szID);

		//message_print(*pTbl_User);
	}

	inline void message_print(const s_game_play_info& gpi)
	{
		jLOG("s_game_play_info db_id = %lld",gpi.m_tbl_user().db_id());
		jLOG("\tm_e_user_gps=%d", gpi.m_e_user_gps() );
		jLOG("\tm_pitcher_sid=%d", gpi.m_pitcher_sid() );
		jLOG("\tm_batter_sid=%d", gpi.m_batter_sid() );
		//message_print(gpi.m_tbl_user());
	}


	inline void message_print(const GameRoomInfo& gri)
	{
		jLOG("GameRoomInfo id=%d",gri.room_id());
		jLOG("s_game_play_info size=%d", gri.m_game_play_info_size());
		for(int i=0; i< gri.m_game_play_info_size() ; ++i)
		{
			message_print(gri.m_game_play_info(i));
		}
		
		jLOG("m_attack_user=%d",gri.m_attack_user());
		jLOG("m_round_count=%d" , gri.m_round_count());
		jLOG("m_result_round_size=%d" , gri.m_result_round_size());
		jLOG("m_baseball_park=%d" , gri.m_baseball_park());

	}

	inline bool is_equal(const s_tbl_roundresult& r1, const s_tbl_roundresult& r2)
	{
		return r1.round_number()==r2.round_number() 
			//&& r1.uid_attack()==r2.uid_attack() 
			&& r1.score()==r2.score()
			&& r1.base_runner_state() ==r2.base_runner_state()
			&& r1.hit_type() == r2.hit_type()
			;
	}


}//namespace nProtoHelper





#define MAKE_SAVE_DB_FILE ja_sprintf(szFile,"../etc/file_db/user[%lld].proto.db",id);


namespace nProtoHelper
{
	template<typename T>
	bool message_file_load(tcstr szID,Tbl_User_id_t id, OUT T& v)
	{
		afname_t szFile;
		MAKE_SAVE_DB_FILE;
		if(!nOS::is_exist_file(szFile)) return false;

		FILE* fp = fopen(szFile, "rb");
		jRETURN_ret(false, fp);
		int32 iVer=0;
		fread(&iVer,sizeof(iVer), 1, fp);
		if(iVer!=DEF_i_DB_VERSION) return false;
		int32 iSize=0;
		fread(&iSize, sizeof(iSize),1,fp);
		char* buf = new char[iSize];
		fread(buf, iSize,1,fp);
		fclose(fp);

		google::protobuf::io::ArrayInputStream ais(buf, iSize);
		v.ParseFromZeroCopyStream(&ais);
		delete [] buf;

		return true;
	}

	template<typename T>
	bool message_file_save(tcstr szID,Tbl_User_id_t id, OUT T& v)
	{
		jFUNC_LOG();
		static bool isInit=false;
		if(isInit==false)
		{
			nOS::create_dir_force("../etc/file_db");
			isInit=true;
		}

		char *buf =new char[v.ByteSize()];
		google::protobuf::io::ArrayOutputStream aos(buf, v.ByteSize());
		v.SerializeToZeroCopyStream(&aos);

		afname_t szFile;
		MAKE_SAVE_DB_FILE;

		FILE* fp = fopen(szFile, "wb");
		jvRETURN_ret(false , fp!=NULL,_T("[ERROR] fopen failed :%s  curr dir = %s") , szFile ,nOS::get_current_dir().c_str());

		int32 iVer=DEF_i_DB_VERSION;
		fwrite(&iVer,sizeof(iVer), 1, fp);
		int32 iSize=v.ByteSize();
		fwrite(&iSize, sizeof(iSize),1,fp);
		fwrite(buf, iSize,1,fp);
		fclose(fp);
		delete [] buf;
		std::cout << __FUNCTION__ << " OK " << szFile << endl;
		return true;
	}



	//#--------------------------------------------------------------------------
	// gameLogic.proto에 정의된 메세지에서 유저의 db_id값을 가져올때사용하는 핼퍼.
	//#--------------------------------------------------------------------------
	inline int64 get_db_id(s_game_play_info *p){ return p->m_tbl_user().db_id();}

}//namespace nProtoHelper
namespace nPH = nProtoHelper;

namespace nError
{
	inline Sys_Error_id_t FromString(acstr szError)
	{
		Sys_Error* p= jCSV(Sys_Error).find(szError);
		if(!p) p = jCSV(Sys_Error).at(0);
		return p->Get_id();
	}
	inline acstr ToString(Sys_Error_id_t err)
	{
		Sys_Error* p = jCSV(Sys_Error).at(err);
		if(!p) return "UNKOWN_ERROR_NO";
		return p->Get_name();
	}
}


#define jMAKE_ERR(X)  nError::FromString(#X)
inline Sys_Error_id_t make_error(cstr szError){ return nError::FromString(szError);}


#define BASE_BALL_GATEWAY_VERSION 3


#include "jUser_base.h"


#endif // __DBHelper_header__
