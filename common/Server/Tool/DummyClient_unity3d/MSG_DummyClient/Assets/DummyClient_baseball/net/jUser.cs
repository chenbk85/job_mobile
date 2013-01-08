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
			eUGPS_LOGOUT					, //- ��Ʈ����������")
			eUGPS_LOGIN					, // -UserGate����������-)")
			eUGPS_DB_LOAD					, // -UserGate����������-)")

 			eUGPS_x2ug_goto_main	, //����ȭ��")
// 
// 			eUGPS_x2ug_goto_charactor_create, //ĳ������â")
// 			eUGPS_x2ug_goto_inventory, //�κ��丮â")

			eUGPS_x2ug_goto_single, //�̱��÷��̻���")
// 			eUGPS_SINGLEPLAY				, //-�̱���������-")

// 			eUGPS_x2ug_goto_upgrade_pitcher, //��ȭ-������ġâ")
// 			eUGPS_x2ug_goto_upgrade_tranner, //��ȭ-Ʈ���̳�â")
// 			eUGPS_x2ug_goto_upgrade_maestro, //��ȭ-����â")
// 			eUGPS_x2ug_goto_etc_ativate, //��ȭ-���Ȱ��â")
// 
// 			eUGPS_x2ug_goto_shop, //����â")
// 			eUGPS_x2ug_goto_team, //������â")
// 			eUGPS_x2ug_goto_rank, //��ŷâ")
// 			eUGPS_x2ug_goto_quest, //����Ʈâ")
// 			eUGPS_x2ug_goto_option, //�ɼ�â")
// 			eUGPS_x2ug_goto_tutorial, //Ʃ�丮����")

			eUGPS_UserGateServer			, //��������� ��������Ʈ���������� ����")
			eUGPS_x2ug_goto_match, //��ġâ(��Ƽ�÷���â)")
			eUGPS_GAMEROOM				, //BaseballServer������ �������")
			eUGPS_LABEL_GAME_NOT_QUIT		, // ")
			eUGPS_GAME_READY2				, //x2bs_auto_match_ready2 ���� �� ����")
			eUGPS_GAME_READY				, //���� ���� �� ����")
			eUGPS_GAME_START				, //���ӽ���")
			eUGPS_GAME_ROUND_START		, //")
			eUGPS_GAME_BATTER_READY		, //��������� Ÿ�ڰ� ĥ�غ񰡵Ǿ�����")
			eUGPS_PITCHER_THROW			, //������ ���� ������")
			eUGPS_BETTER_HIT				, //Ÿ�ڰ� ���� �ƴ�")
			eUGPS_BETTER_HIT_RESULT		, //Ÿ�ڴ� req_result_better_hit�� ���°� ������ ans_result_better_hit�� �޾Ҵ�.")
			eUGPS_ATTACK_USER_CHANGED		, //���� �� �ٲ���.")
			eUGPS_GAME_END				, //������ ��� ������ ����������Ŷ ans_game_end �� ���´�")
			eUGPS_GAME_REMATCH			, //������ ��� ������ req_rematch�������� �Ǵ� rematch�������")
			eUGPS_GAMEROOM_PRE_LEAVE		, //�κ�� ������ ������� ����-")
			eUGPS_BS_USER_IS_ILLEGAL		, //���Ӽ����� ���ӵ� ���������� ������ ������ ������ �ƴ� ����������")
			eUGPS_BS_ABNORMAL_DISCONNECT	, //�ش� ������ Ŭ���̾�Ʈ�� ���������� TCP DISCONNECT�����̴�.")

			eUGPS_x2ug_goto_friend_match, //�����鸮��ġ����")
			eUGPS_BaseballServer			, //��������� ���Ӽ������ӻ���")

		}

		public class jUser 
		{
			public EUserGPS m_eEUserGPS = EUserGPS.eUGPS_LOGOUT;
			public NetEventPlugin_baseball m_Plugin;

			public nProtoGL.GameRoomInfo m_GameRoomInfo; // gameLogic.proto÷�� �Ұ�.
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

