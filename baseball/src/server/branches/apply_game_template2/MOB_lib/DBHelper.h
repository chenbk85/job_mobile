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



#define jFUNC_LOG() jLOG("<<< %s:%d(%s) >>> ",__FUNCTION__,__LINE__,__FILE__);
#define jFUNC_LOG2(name,id) jLOG("<<< %s:%d(%s) %s:%d>>> ",__FUNCTION__,__LINE__,__FILE__,name,id);


#define SERVER_OK 0 // 서버에서 클라로 응답줄때 에러코드중 성공일때.

namespace nProtoHelper
{


// excel에서 뽑은 메세지 구조체들.
// X(TABLE,EXCEL_TABLE,SELECT_FIELD)
#define for_each_nEXCEL_excel_baseball_table_db_proto(X)\
	X(s_tbl_user			,Tbl_User			,db_id )\
	X(s_tbl_friend			,Tbl_Friend			,db_id )\
	X(s_tbl__playerbase		,Tbl__PlayerBase	,db_id )\
	X(s_tbl_playerbetter	,Tbl_PlayerBetter	,db_id )\
	X(s_tbl_playerpitcher	,Tbl_PlayerPitcher	,db_id )\
	X(s_tbl_item			,Tbl_Item			,db_id )\
	X(s_tbl_pitcherskill	,Tbl_PitcherSkill	,db_id )\
	X(s_tbl_result			,Tbl_Result			,db_id )\
	X(s_tbl_roundresult		,Tbl_RoundResult	,db_id )\
	X(s_tbl_team			,Tbl_Team			,db_id )\
	X(s_tbl_package			,Tbl_Package		,db_id)\
	X(s_tbl_quest			,Tbl_Quest			,db_id)\
	X(s_tbl_title			,Tbl_Title			,db_id)\



// gameLogic.proto의 GameInfo 메세지에 포함된 구조체 리스트.
// X(TABLE,EXCEL_TABLE,SELECT_FIELD)
#define for_each_GameInfo_Excel_Table(X)\
	X(tbl_user			,Tbl_User			,db_id)\
	X(tbl_friend		,Tbl_Friend			,uid)\
	X(tbl_playerbetter	,Tbl_PlayerBetter	,uid)\
	X(tbl_playerpitcher	,Tbl_PlayerPitcher	,uid)\
	X(tbl_item			,Tbl_Item			,uid)\
	X(tbl_pitcherskill	,Tbl_PitcherSkill	,uid)\
	X(tbl_team			,Tbl_Team			,uid)\
	X(tbl_package		,Tbl_Package		,uid)\
	X(tbl_quest			,Tbl_Quest			,uid)\
	X(tbl_title			,Tbl_Title			,uid)\


#define for_each_WIN_LOSE(X) X(win) X(lose)

#define for_each_SCORE_RECORD_OBJ(X) \
	X(user) \
	X(better) \
	X(pitcher) \
	X(team)\

// ENUM_FIELD(ITEM_ENUM,ItemType)
#define for_each_nEXCEL_EItemCategory123(ENUM_FIELD)\
	ENUM_FIELD(EQUIP	,Equip)\
	ENUM_FIELD(CONSUME	,Stuff)\
	ENUM_FIELD(STUFF	,Consume)\


#	define __print_field_43(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple) \
		cout<< #eng_name << " = " << t.eng_name() << endl; 

#	define __print_data_func_43(TABLE,EXCEL_TABLE,SELECT_FIELD) \
	inline void message_print(const TABLE& t,Tbl_User_id_t uid=0) \
	{\
		if(uid){	cout<< endl << #TABLE <<"[uid=" << uid <<"]"<< endl;}\
		else{cout<< endl << #TABLE << endl;}\
		_jJOIN_3(for_each_nEXCEL_,EXCEL_TABLE,_STRUCT_FIELD_all_member)(__print_field_43); cout << endl;\
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

		message_print(*pTbl_User);
	}

	inline void message_print(const GameRoomInfo& gri)
	{
		jLOG("GameRoomInfo id=%d",gri.room_id());
		jLOG("s_game_play_info size=%d", gri.m_game_play_info_size());
		jLOG("m_attack_user=%d",gri.m_attack_user());
		jLOG("m_round_count=%d" , gri.m_round_count());
		jLOG("m_result_round_size=%d" , gri.m_result_round_size());
		//jLOG("m_result_game" , gri.m_result_game());
	}
	inline void message_print(const s_game_play_info& gpi)
	{
		jLOG("s_game_play_info > m_e_user_gps=%d", gpi.m_e_user_gps() );
		message_print(gpi.m_tbl_user());
		message_print(gpi.m_tbl_team());
		//message_print(gpi.m_tbl_playerbetter());
		//message_print(gpi.m_tbl_playerpitcher());
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





#define MAKE_SAVE_DB_FILE ja_sprintf(szFile,"../etc/file_db/user[%s].proto.db",szID);


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


#define BASE_BALL_GATEWAY_VERSION 1234


#include "jUser_base.h"


#endif // __DBHelper_header__
