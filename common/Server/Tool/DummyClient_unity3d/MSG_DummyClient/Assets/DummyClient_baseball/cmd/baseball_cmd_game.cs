using UnityEngine;
using System.Collections;
using user_id_t = System.Int64;
using nNWM;

public class baseball_cmd_game : CmdEvent_base
{
	nNWM.nBaseball.NetEventPlugin_baseball cmd_NetEventPlugin2(string sUID)
	{
		return (nNWM.nBaseball.NetEventPlugin_baseball)base.cmd_NetEventPlugin(sUID);
	}

	//#--------------------------------------------------------------------------
	void match_auto_join_team(nNWM.nConsole.jConsoleArg arg)
	//#--------------------------------------------------------------------------
	{
		const int eUID = 0;
		if (IsFail_ArgCheck(arg, "<uid>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }

		var sd = new MSG.ReqAutoJoin
		{
			CategoryID = 0,
			ChannelID = 0
		};
		plugin.send_to_MSG(sd);
	}
	
	//#--------------------------------------------------------------------------
	void UReqLeaveGame(nNWM.nConsole.jConsoleArg arg)
	//#--------------------------------------------------------------------------
	{
		const int eUID = 0;
		if (IsFail_ArgCheck(arg, "<uid>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }
		//-------------------------------------------------------------------

		byte[] info = Serialize<string>(plugin.db_id().ToString());
		//info[0] = 111;
		var sd = new MSG.ReqLeaveGame
		{
			GameID = plugin.db_id(),
			LeaveInfo = info,
		};
		plugin.send_to_MSG(sd);
	}

	//#--------------------------------------------------------------------------
	void x2bs_auto_match_ready2(nNWM.nConsole.jConsoleArg arg)
	//#--------------------------------------------------------------------------
	{
		const int eUID=0 ,eBATTER=1 ,ePITCHER=2;
		if (IsFail_ArgCheck(arg, "<uid> [batter=1] [pitcher=1]")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }
		//-------------------------------------------------------------------

		var sd = plugin.Make(nProtoBS.Client_BaseballServer.Type.x2bs_auto_match_ready2);
		sd.m_x2bs_auto_match_ready2 = new nProtoBS.s_x2bs_auto_match_ready2
		{
			uid = plugin.db_id(),
			batter = arg.Get_int32(eBATTER),
			pitcher = arg.Get_int32(ePITCHER),
		};
		plugin.send_to_gs(sd);
	}

	//#--------------------------------------------------------------------------
	void x2bs_match_ready(nNWM.nConsole.jConsoleArg arg)
	//#--------------------------------------------------------------------------
	{
		const int eUID = 0;
		if (IsFail_ArgCheck(arg, "<uid>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }
		//-------------------------------------------------------------------

		var sd = plugin.Make(nProtoBS.Client_BaseballServer.Type.x2bs_match_ready);
		sd.m_x2bs_match_ready = new nProtoBS.s_x2bs_match_ready
		{
			uid = plugin.db_id(),
		};
		plugin.send_to_gs(sd);

	}

	//#--------------------------------------------------------------------------
	void x2bs_batter_ready(nNWM.nConsole.jConsoleArg arg)
	//#--------------------------------------------------------------------------
	{
		const int eUID = 0;
		if (IsFail_ArgCheck(arg, "<uid>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }
		//-------------------------------------------------------------------

		var sd = plugin.Make(nProtoBS.Client_BaseballServer.Type.x2bs_batter_ready);
		sd.m_x2bs_batter_ready = new nProtoBS.s_x2bs_batter_ready();
		plugin.send_to_gs(sd);
	}

	//#--------------------------------------------------------------------------
	void req_pitcher_throw(nNWM.nConsole.jConsoleArg arg)
	//#--------------------------------------------------------------------------
	{
		const int eUID = 0;
		if (IsFail_ArgCheck(arg, "<uid>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }
		nNWM.nBaseball.jUser user = plugin.m_User;
		//-------------------------------------------------------------------

		var pti = new nProtoGL.s_pitcher_throw_info
		{
			screen_to_world = new nProtoGL.s_vector3() , 
			ball_type = 0,
			scale_rate = 0,	
			ball_breaking	= 0,	
			angle = 0,
			uid = plugin.db_id(),	
			round = user.GetCurr_round_count(),
			rhythm_judge_verifi = 0,
		};
		int gesture = (int)nEXCEL.EGestureType.EGTT_STRAGHT;
		int gesture_error = 0;

		var sd = plugin.Make(nProtoBS.Client_BaseballServer.Type.req_pitcher_throw);
		sd.m_req_pitcher_throw = new nProtoBS.s_req_pitcher_throw
		{
			info = pti,
			used_gesturetype = gesture,
			gesturetype_input_error = gesture_error,
		};
		plugin.send_to_gs(sd);

	}
	
	//#--------------------------------------------------------------------------
	void req_better_hit(nNWM.nConsole.jConsoleArg arg)
	//#--------------------------------------------------------------------------
	{
		const int eUID = 0;
		if (IsFail_ArgCheck(arg, "<uid>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }
		//nNWM.nBaseball.jUser user = plugin.m_User;

		//-------------------------------------------------------------------
		var bhi = new nProtoGL.s_better_hit_info();
// 		{
// 			//screen_to_world	
// 			//force_xy		
// 			force			=0,
// 			torque			=0,
// 			velocity_x =0,
// 			uid				=plugin.db_id(),
// 			round			=user.GetCurr_round_count(),
// 			hit_info = i_EBatterHitType,
// 		};

		var sd = plugin.Make(nProtoBS.Client_BaseballServer.Type.req_better_hit);
		sd.m_req_better_hit = new nProtoBS.s_req_better_hit
		{
			info = bhi,
		};
		plugin.send_to_gs(sd);
	}

	//#--------------------------------------------------------------------------
	void req_rematch(nNWM.nConsole.jConsoleArg arg)
	//#--------------------------------------------------------------------------
	{
		const int eUID = 0;
		if (IsFail_ArgCheck(arg, "<uid>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }
	  //nNWM.nBaseball.jUser = plugin.m_User;
		//-------------------------------------------------------------------

		var sd = plugin.Make(nProtoBS.Client_BaseballServer.Type.req_rematch);
		sd.m_req_rematch = new nProtoBS.s_req_rematch
		{
			uid = plugin.db_id(),
		};
		plugin.send_to_gs(sd);

	}

	//#--------------------------------------------------------------------------
	void req_answer_restart_game(nNWM.nConsole.jConsoleArg arg)
	//#--------------------------------------------------------------------------
	{
		const int eUID = 0, eIS_REMATCH=1;
		if (IsFail_ArgCheck(arg, "<uid> <isRematch>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }
	  //nNWM.nBaseball.jUser user= plugin.m_User;
		//-------------------------------------------------------------------

		var sd = plugin.Make(nProtoBS.Client_BaseballServer.Type.req_answer_restart_game);
		sd.m_req_answer_restart_game = new nProtoBS.s_req_answer_restart_game
		{
			uid = plugin.db_id(),
			ok = arg.Get_bool(eIS_REMATCH),
		};
		plugin.send_to_gs(sd);

	}


	/*
	 * ÅÛÇÃ¸´ ÄÚµå.
	 
	//#--------------------------------------------------------------------------
	void asdf(nNWM.nConsole.jConsoleArg arg)
	//#--------------------------------------------------------------------------
	{
		const int eUID = 0;
		if (IsFail_ArgCheck(arg, "<uid>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }
	  //nNWM.nBaseball.jUser user= plugin.m_User;
		//-------------------------------------------------------------------

		var sd = plugin.Make(nProtoBS.Client_BaseballServer.Type.asdf);
		sd.m_asdf = new nProtoBS.s_asdf
		{
			//uid = plugin.db_id(),
			//batter = arg.Get_int32(eBATTER),
		};
		plugin.send_to_gs(sd);

	}
	 
	 * */

}//public class baseball_cmd_game : CmdEvent_base

