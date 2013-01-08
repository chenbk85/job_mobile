using UnityEngine;
using System.Collections;
using user_id_t = System.Int64;
using nNWM;

public class asdf_cmd_game : CmdEvent_base
{
	nNWM.nASDF.NetEventPlugin_asdf cmd_NetEventPlugin2(string sUID)
	{
		return (nNWM.nASDF.NetEventPlugin_asdf)base.cmd_NetEventPlugin(sUID);
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
	void asdf(nNWM.nConsole.jConsoleArg arg)
	//#--------------------------------------------------------------------------
	{
		const int eUID = 0;
		if (IsFail_ArgCheck(arg, "<uid>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }
	  //nNWM.nASDF.jUser user= plugin.m_User;
		//-------------------------------------------------------------------

		var sd = plugin.Make(nProtoGSasdf.Client_GameServer.Type.asdf);
		sd.m_asdf = new nProtoBS.s_asdf
		{
			//uid = plugin.db_id(),
			//batter = arg.Get_int32(eBATTER),
		};
		plugin.send_to_gs(sd);

	}
	 
	 * */

}//public class asdf_cmd_game : CmdEvent_base<asdf_cmd_game>

