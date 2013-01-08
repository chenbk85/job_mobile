using UnityEngine;
using System.Collections;
using nNWM;

public class recv_BaseballServer_Client : MonoBehaviour 
{
	//#--------------------------------------------------------------------------
	// Util function 
	//#--------------------------------------------------------------------------
	nProtoBS.BaseballServer_Client ToRecvData(nNWM.nDummy.NetEventArg arg)
	{
		return (nProtoBS.BaseballServer_Client)arg.recvData;
	}
	nNWM.nBaseball.NetEventPlugin_baseball ToPlugin(nNWM.nDummy.NetEventArg arg)
	{
		return (nNWM.nBaseball.NetEventPlugin_baseball)arg.plugin;
	}
	
	//#--------------------------------------------------------------------------
	// Baseball Server -> Client Net Receiver.
	//#--------------------------------------------------------------------------
	public void ans_bs_error(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_ans_bs_error;
		var plugin = ToPlugin(arg);
		plugin.NetWarning(nNWM.nUtil.jDumper.NamedDump(rd) + nEXCEL.CSV_Sys_Error.Find(rd.sys_error_id).m_name);
	}

	public void ans_join_room(nNWM.nDummy.NetEventArg arg) // 다른 사람이 게임룸 입장.
	{
		var rd = ToRecvData(arg).m_ans_join_room;
		var plugin = ToPlugin(arg);
		
		plugin.m_User.Set_GameRoomInfo(rd.gri);
		nProtoGL.s_game_play_info other_gri = plugin.m_User.get_s_game_play_info_Other();
		if (other_gri == null)
		{
			plugin.NetWarning("get_s_game_play_info_Other()==null , uid=" + plugin.db_id());
			return;
		}
		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(other_gri.m_tbl_user));

	}

	public void bs2x_auto_match_ready2(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_bs2x_auto_match_ready2;
		var plugin = ToPlugin(arg);

		var gpi = plugin.m_User.get_s_game_play_info();
		gpi.m_pitcher_sid = rd.pitcher;
		gpi.m_batter_sid = rd.batter;

		gpi = plugin.m_User.get_s_game_play_info_Other();
		if (gpi != null)
		{
			gpi.m_pitcher_sid = rd.other_pitcher;
			gpi.m_batter_sid = rd.other_batter;
		}
		plugin.m_User.m_eEUserGPS = nNWM.nBaseball.EUserGPS.eUGPS_GAME_READY2;

		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
	}

	public void bs2x_match_ready(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_bs2x_match_ready;
		var plugin = ToPlugin(arg);

		var gpi = plugin.m_User.get_s_game_play_info(rd.uid);
		gpi.m_e_user_gps = (int)nNWM.nBaseball.EUserGPS.eUGPS_GAME_READY;

		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
	}

	public void ans_game_start(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_ans_game_start;
		var plugin = ToPlugin(arg);
		nProtoGL.GameRoomInfo gri = plugin.m_User.m_GameRoomInfo;
		gri.m_baseball_park = rd.baseball_park;
		plugin.m_User.SetAttackUser(rd.attack_user);
		plugin.m_User.m_sid_Sys_Runner_State = rd.sid_Sys_Runner_State;

		plugin.m_User.m_eEUserGPS = nNWM.nBaseball.EUserGPS.eUGPS_GAME_START;
		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
	}

	public void ans_game_round_start(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_ans_game_round_start;
		var plugin = ToPlugin(arg);
		nNWM.nBaseball.jUser user = plugin.m_User;
		var gri = user.m_GameRoomInfo;
		gri.m_round_count = rd.round;
		user.m_eEUserGPS = nNWM.nBaseball.EUserGPS.eUGPS_GAME_ROUND_START;

		if (user.IsAttackUser())
		{
			plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd) + " I'm batter. NEED! sending x2bs_batter_ready.");

			if (plugin.m_CMD.m_isAutoPlay)
			{
				plugin.m_CMD.ParseCmd("@game.x2bs_batter_ready " + plugin.db_id());
			}

		}
		else
		{
		}

		user.m_eEUserGPS = nNWM.nBaseball.EUserGPS.eUGPS_GAME_ROUND_START;
	}

	public void bs2x_batter_ready(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_bs2x_batter_ready;
		var plugin = ToPlugin(arg);
		nNWM.nBaseball.jUser user = plugin.m_User;
		if (user.IsAttackUser() == true)
		{
			plugin.NetWarning(plugin.db_id() + " is not pitcher");//타자에게는 bs2x_batter_ready가 날라오지 않는다.
		}
		else
		{
			plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
			plugin.Log(" I'm pitcher. send req_pitcher_throw");

			if (plugin.m_CMD.m_isAutoPlay)
			{
				plugin.m_CMD.ParseCmd("@game.req_pitcher_throw  " + plugin.db_id());
			}
		}
		user.m_eEUserGPS = nNWM.nBaseball.EUserGPS.eUGPS_GAME_BATTER_READY;
	}
	
	public void ans_pitcher_throw(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_ans_pitcher_throw;
		var plugin = ToPlugin(arg);
		nNWM.nBaseball.jUser user = plugin.m_User;
		user.m_ans_pitcher_throw = rd;
		if (user.IsAttackUser())
		{
			plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));

			if (plugin.m_CMD.m_isAutoPlay)
			{
				plugin.m_CMD.ParseCmd("@game.req_better_hit " + plugin.db_id());
			}
		}
		else
		{

		}
	}
	
	public void ans_better_hit(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_ans_better_hit;
		var plugin = ToPlugin(arg);
		nNWM.nBaseball.jUser user = plugin.m_User;
		user.m_ans_better_hit = rd;
		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));

		if (user.IsAttackUser())//타자
		{
			user.send_req_result_better_hit(rd);
		}
		else //투수
		{
			plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
		}
		
	}
	public void ans_result_better_hit(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_ans_result_better_hit;
		var plugin = ToPlugin(arg);
		nNWM.nBaseball.jUser user = plugin.m_User;
		//plugin.Log("user.GetCurr_round_count() = " + user.GetCurr_round_count() + "recv_round=" + rd.info.m_tbl_roundresult.round_number) ;


		user.m_GameRoomInfo.m_result_round.Add(rd.info);
		jDebug.jCHECK(user.m_GameRoomInfo.m_result_round.Count == user.GetCurr_round_count()+1);
		if (user.IsAttackUser())
		{
		}
		else
		{
			plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
		}
	}

	public void ans_change_attack_team(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_ans_change_attack_team;
		var plugin = ToPlugin(arg);
		nNWM.nBaseball.jUser user = plugin.m_User;

		user.SetAttackUser(rd.attack_user);
		user.m_GameRoomInfo.m_round_count = rd.round;
		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
		if (user.IsAttackUser())
		{
			plugin.NetLog(" I'm batter. NEED! sending x2bs_batter_ready.");
		}
		else
		{
			
		}

	}

	public void ans_game_end(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_ans_game_end;
		var plugin = ToPlugin(arg);
		//nNWM.nBaseball.jUser user = plugin.m_User;

		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
	}
	public void bs2x_game_end_other_user_info(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_bs2x_game_end_other_user_info;
		var plugin = ToPlugin(arg);
		//nNWM.nBaseball.jUser user = plugin.m_User;

		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
	}
	public void ans_rematch(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_ans_rematch;
		var plugin = ToPlugin(arg);
		//nNWM.nBaseball.jUser user = plugin.m_User;

		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
	}

	//
	bool get_ok(nNWM.nBaseball.NetEventPlugin_baseball plugin, nProtoBS.s_ans_answer_restart_game rd)
	{
		/*
		int idx = 0;
		foreach (var db_id in rd.uid)
		{
			if (db_id == plugin.db_id())
			{
				break;
			}
			++idx;
		}
		if (idx == 0)
		{
			plugin.LogWarning("s_ans_answer_restart_game db_id==0");
			return false;
		}

		int idx2 = 0;
		foreach (var ok in rd.ok)
		{
			if (idx2 == idx)
			{
				return ok;
				break;
			}
			++idx2;
		}
		plugin.LogWarning("s_ans_answer_restart_game idx2 error");
		return false;
		 * */
		return rd.ok[0] == true && rd.ok[1] == true;
	}
	public void ans_answer_restart_game(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_ans_answer_restart_game;
		var plugin = ToPlugin(arg);
		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd,nNWM.nUtil.jDumper.EDumpType.eALL));
		if (plugin.m_CMD.m_isAutoPlay == true)
		{
			if (get_ok(plugin, rd) == true)
				plugin.m_CMD.ParseCmd("@game.x2bs_match_ready " + plugin.db_id());
		}

	}
	public void bs2x_echo(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_bs2x_echo;
		var plugin = ToPlugin(arg);
		//nNWM.nBaseball.jUser user = plugin.m_User;

		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
	}
		
	/*
	 * 아래 탬플릿 코드를 복사하여 사용. asdf를 원하는 프로토콜이름으로 바꾸시오.
	 
	public void asdf(nNWM.nDummy.NetEventArg arg)
	{
		var rd = ToRecvData(arg).m_asdf;
		var plugin = ToPlugin(arg);
		//nNWM.nBaseball.jUser user = plugin.m_User;

		plugin.NetLog(nNWM.nUtil.jDumper.NamedDump(rd));
	}
	  
	 *
	 * */
}
