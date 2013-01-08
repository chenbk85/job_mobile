using UnityEngine;
using System.Collections;
using user_id_t = System.Int64;
using nNWM;

public class asdf_cmd_test : CmdEvent_base
{
	nNWM.nASDF.NetEventPlugin_asdf cmd_NetEventPlugin2(string sUID)
	{
		return (nNWM.nASDF.NetEventPlugin_asdf)base.cmd_NetEventPlugin(sUID);
	}

	/*
	 * ÅÛÇÃ¸´ ÄÚµå.
	 
	void asdf(nNWM.nConsole.jConsoleArg arg)
	{
		const int eUID = 0;
		if (IsFail_ArgCheck(arg, "<uid>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }
		//-------------------------------------------------------------------

		var sd = plugin.Make(nProtoGSasdf.Client_GameServer.Type.asdf);
		sd.m_asdf = new nProtoBS.s_asdf
		{
			uid = plugin.db_id(),
			batter = arg.Get_int32(eBATTER),
		};
		plugin.send_to_gs(sd);

	}
	 
	 * */

}//public class asdf_cmd_test : CmdEvent_base
