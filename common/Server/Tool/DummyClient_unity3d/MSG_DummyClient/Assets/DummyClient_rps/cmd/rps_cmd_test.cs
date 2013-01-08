using UnityEngine;
using System.Collections;
using user_id_t = System.Int64;
using nNWM;

public class rps_cmd_test : CmdEvent_base
{
	nNWM.nRPS.NetEventPlugin_rps cmd_NetEventPlugin2(string sUID)
	{
		return (nNWM.nRPS.NetEventPlugin_rps)base.cmd_NetEventPlugin(sUID);
	}

	/*
	 * ÅÛÇÃ¸´ ÄÚµå.
	 
	void rps(nNWM.nConsole.jConsoleArg arg)
	{
		const int eUID = 0;
		if (IsFail_ArgCheck(arg, "<uid>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }
		//-------------------------------------------------------------------

		var sd = plugin.Make(nProtoGSrps.Client_GameServer.Type.rps);
		sd.m_rps = new nProtoBS.s_rps
		{
			uid = plugin.db_id(),
			batter = arg.Get_int32(eBATTER),
		};
		plugin.send_to_gs(sd);

	}
	 
	 * */

}//public class rps_cmd_test : CmdEvent_base
