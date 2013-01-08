using UnityEngine;
using System.Collections;
using user_id_t = System.Int64;
using nNWM;

public class rps_cmd_game : CmdEvent_base
{
	nNWM.nRPS.NetEventPlugin_rps cmd_NetEventPlugin2(string sUID)
	{
		return (nNWM.nRPS.NetEventPlugin_rps)base.cmd_NetEventPlugin(sUID);
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


	/*
	 * ÅÛÇÃ¸´ ÄÚµå.
	 
	//#--------------------------------------------------------------------------
	void rps(nNWM.nConsole.jConsoleArg arg)
	//#--------------------------------------------------------------------------
	{
		const int eUID = 0;
		if (IsFail_ArgCheck(arg, "<uid>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }
	  //nNWM.nRPS.jUser user= plugin.m_User;
		//-------------------------------------------------------------------

		var sd = plugin.Make(nProtoGSrps.Client_GameServer.Type.rps);
		sd.m_rps = new nProtoBS.s_rps
		{
			//uid = plugin.db_id(),
			//batter = arg.Get_int32(eBATTER),
		};
		plugin.send_to_gs(sd);

	}
	 
	 * */

}//public class rps_cmd_game : CmdEvent_base<rps_cmd_game>

