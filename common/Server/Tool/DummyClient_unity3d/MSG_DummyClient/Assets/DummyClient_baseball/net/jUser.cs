using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using nNWM;
using user_id_t = System.Int64;

namespace nNWM
{
	namespace nBaseball
	{
		public enum EUserGPS
		{
			eUGPS_LOGOUT					, //- 네트웍접속해제")
			eUGPS_LOGIN					, // -UserGate서버에접속-)")
			eUGPS_DB_LOAD					, // -UserGate서버에접속-)")

 			eUGPS_x2ug_goto_main	, //메인화면")
// 
// 			eUGPS_x2ug_goto_charactor_create, //캐릭생성창")
// 			eUGPS_x2ug_goto_inventory, //인벤토리창")

			eUGPS_x2ug_goto_single, //싱글플레이상태")
// 			eUGPS_SINGLEPLAY				, //-싱글프레이중-")

// 			eUGPS_x2ug_goto_upgrade_pitcher, //강화-투수코치창")
// 			eUGPS_x2ug_goto_upgrade_tranner, //강화-트레이너창")
// 			eUGPS_x2ug_goto_upgrade_maestro, //강화-장인창")
// 			eUGPS_x2ug_goto_etc_ativate, //강화-장외활동창")
// 
// 			eUGPS_x2ug_goto_shop, //상점창")
// 			eUGPS_x2ug_goto_team, //팀관리창")
// 			eUGPS_x2ug_goto_rank, //랭킹창")
// 			eUGPS_x2ug_goto_quest, //퀘스트창")
// 			eUGPS_x2ug_goto_option, //옵션창")
// 			eUGPS_x2ug_goto_tutorial, //튜토리얼모드")

			eUGPS_UserGateServer			, //여기까지가 유저게이트서버에서의 상태")
			eUGPS_x2ug_goto_match, //매치창(멀티플레이창)")
			eUGPS_GAMEROOM				, //BaseballServer에접속 대기방상태")
			eUGPS_LABEL_GAME_NOT_QUIT		, // ")
			eUGPS_GAME_READY2				, //x2bs_auto_match_ready2 레디 한 상태")
			eUGPS_GAME_READY				, //게임 레디 한 상태")
			eUGPS_GAME_START				, //게임시작")
			eUGPS_GAME_ROUND_START		, //")
			eUGPS_GAME_BATTER_READY		, //라운드시작후 타자가 칠준비가되었는지")
			eUGPS_PITCHER_THROW			, //투수가 공을 던졌다")
			eUGPS_BETTER_HIT				, //타자가 공을 쳤다")
			eUGPS_BETTER_HIT_RESULT		, //타자는 req_result_better_hit를 보냈고 투수는 ans_result_better_hit를 받았다.")
			eUGPS_ATTACK_USER_CHANGED		, //팀이 막 바꼈다.")
			eUGPS_GAME_END				, //게임을 모두 끝내고 게임종료패킷 ans_game_end 을 보냈다")
			eUGPS_GAME_REMATCH			, //게임을 모두 끝내고 req_rematch보낸상태 또는 rematch허락상태")
			eUGPS_GAMEROOM_PRE_LEAVE		, //로비로 갈려고 대기중인 상태-")
			eUGPS_BS_USER_IS_ILLEGAL		, //게임서버에 접속된 상태이지만 유저의 정보가 정상이 아님 강제종료대상")
			eUGPS_BS_ABNORMAL_DISCONNECT	, //해당 유저는 클라이언트가 비정상적인 TCP DISCONNECT상태이다.")

			eUGPS_x2ug_goto_friend_match, //프랜들리매치상태")
			eUGPS_BaseballServer			, //여기까지가 게임서버접속상태")

		}

		public class jUser 
		{
			public EUserGPS m_eEUserGPS = EUserGPS.eUGPS_LOGOUT;
			public NetEventPlugin_baseball m_Plugin;

			public nProtoGL.GameRoomInfo m_GameRoomInfo; // gameLogic.proto첨고 할것.
			public nProtoGL.GameInfo m_GameInfo = new nProtoGL.GameInfo();
			public Dictionary<string, int> m_ServerInfoRecvState = new Dictionary<string, int>();
			public int m_sid_Sys_Runner_State;
			public nProtoBS.s_ans_pitcher_throw m_ans_pitcher_throw;
			public nProtoBS.s_ans_better_hit m_ans_better_hit;

			public jUser(NetEventPlugin_baseball plugin) { m_Plugin = plugin; }

			public user_id_t db_id(){ return m_Plugin.db_id();}
			public bool IsAttackUser(){ return m_GameRoomInfo.m_attack_user == m_Plugin.db_id();}
			public user_id_t GetAttackUser() { return m_GameRoomInfo.m_attack_user ;}
			public void SetAttackUser(user_id_t uid ){ m_GameRoomInfo.m_attack_user  = uid;}
			public int GetCurr_round_count(){ return m_GameRoomInfo.m_round_count;}
			public nProtoGL.s_result_round GetCurr_round_result()
			{
				int iTot = m_GameRoomInfo.m_result_round.Count;
				int iCurr = GetCurr_round_count();
				if( iTot <= iCurr)
				{
					m_Plugin.NetWarning("m_GameRoomInfo.m_result_round.Count = " + iTot + " curr round=" + iCurr);
					return null;
				}
				return m_GameRoomInfo.m_result_round[iCurr];
			}
			public void Inc_tbl_record(string tbl , int next_index)
			{
				if (m_ServerInfoRecvState.ContainsKey(tbl) == false)
				{
					m_ServerInfoRecvState.Add(tbl, next_index);
				}
				else
				{
					m_ServerInfoRecvState[tbl] = next_index;
				}
			}
			public void add_tbl_user(nProtoExcel.s_tbl_user tbl){m_GameInfo.m_tbl_user.Add(tbl);}
			public void Set_GameRoomInfo(nProtoGL.GameRoomInfo gri)
			{
				m_eEUserGPS = EUserGPS.eUGPS_GAMEROOM;
				m_GameRoomInfo = gri;
			}
			public nProtoGL.s_game_play_info get_s_game_play_info_Other()
			{
				foreach (var v in m_GameRoomInfo.m_game_play_info)
				{
					if (v.m_tbl_user.db_id != m_Plugin.db_id())
					{
						return v;
					}
				}
				//m_Plugin.NetWarning("get_s_game_play_info_Other not found  ");
				return null;
			}
			public nProtoGL.s_game_play_info get_s_game_play_info(user_id_t uid=0)
			{
				if(uid==0) uid = m_Plugin.db_id();
				foreach (var v in m_GameRoomInfo.m_game_play_info)
				{
					if (v.m_tbl_user.db_id == uid)
					{
						return v;
					}
				}
				m_Plugin.NetWarning("get_s_game_play_info not found : uid = " + uid);
				return null;
			}

			public void send_req_result_better_hit(nProtoBS.s_ans_better_hit rd)
			{
			//	var rr = this.GetCurr_round_result();
			//			rr.m_tbl_roundresult.batting_hittype = rd.info.hit_info;
			//			nEXCEL.EBatterHitType eType = (nEXCEL.EBatterHitType)rd.info.hit_info;
				const int iMin = ((int)nEXCEL.EBatterHitType.eBEGIN_EBatterHitType + (int)nEXCEL.EBatterHitType.EBIT_LEFTFIELDOUT);
				const int iMax = (int)(nEXCEL.EBatterHitType.eEND_EBatterHitType - 1);
				int i_EBatterHitType = (int)Random.Range(iMin, iMax);
				if (i_EBatterHitType == (int)(nEXCEL.EBatterHitType.EBHT_NO_HIT))
				{
					i_EBatterHitType = (int)(nEXCEL.EBatterHitType.EBHT_HOMERUN);
				}
				nProtoGL.s_result_round srr = new nProtoGL.s_result_round
				{
					m_tbl_roundresult = new nProtoExcel.s_tbl_roundresult
					{
						hit_type = i_EBatterHitType,
						//score = 0,
						//base_runner_state = eRSR_current,
						round_number = this.GetCurr_round_count(),
						uid_attack = this.GetAttackUser(),
					},
				};

				var sd = m_Plugin.Make(nProtoBS.Client_BaseballServer.Type.req_result_better_hit);
				sd.m_req_result_better_hit = new nProtoBS.s_req_result_better_hit
				{
					info = srr,
					test = 0,
				};
				nEXCEL.EBatterHitType eType = (nEXCEL.EBatterHitType)i_EBatterHitType; 
				m_Plugin.NetLog("[Send] batting_hittype = "+ eType.ToString());
				m_Plugin.send_to_gs(sd);
			}

		}//namespace nBaseball

	}//namespace nBaseball
}//namespace nNWM

