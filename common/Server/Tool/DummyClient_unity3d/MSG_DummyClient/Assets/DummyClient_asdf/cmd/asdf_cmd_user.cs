using UnityEngine;
using System.Collections;
using user_id_t = System.Int64;

using nNWM;

public class asdf_cmd_user : CmdEvent_base
{
	nNWM.nASDF.NetEventPlugin_asdf cmd_NetEventPlugin2(string sUID)
	{
		return (nNWM.nASDF.NetEventPlugin_asdf)base.cmd_NetEventPlugin(sUID);
	}

	public void login(nNWM.nConsole.jConsoleArg arg)
	{
		const int eIP_PORT = 0, eUID = 1;
		if (IsFail_ArgCheck(arg, "<ip:port> <uid>")) return;

		string[] ip_port = arg[eIP_PORT].Split(':');
		if (ip_port.Length != 2)
		{
			m_CMD.LogWarning(arg[eIP_PORT] + " is invaild format");
			return;
		}
		user_id_t uid = user_id_t.Parse(arg[eUID]);
		var plugin = m_MSG.Find(uid);
		if (plugin == null)
		{
			plugin = new nNWM.nASDF.NetEventPlugin_asdf(user_id_t.Parse(arg[eUID]), m_CMD, m_MSG);
			m_MSG.Login(ip_port[0], System.Int32.Parse(ip_port[1]), plugin);
			return;
		}
		else
		{
			if (plugin.m_MSGClient != null)
			{
				m_CMD.LogWarning(" client socket(MSGClient) is exist. ");
				plugin.m_MSGClient.Connect(ip_port[0], System.Int32.Parse(ip_port[1]));
				return;
			}
			plugin.NetLog("[INFO]exist user plugin connect");
			m_MSG.Login(ip_port[0], System.Int32.Parse(ip_port[1]), plugin);
		}
	}
	public void ReqConnect(nNWM.nConsole.jConsoleArg arg)
	{
		const int eUID = 0;
		if (IsFail_ArgCheck(arg, "<uid>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }

		var connect = new MSG.ReqConnect
		{
			SvcID = m_MSG.SvcID,
			GameID = plugin.db_id(),
			Version = m_MSG.Version,
			MemberInfo = new MSG.MemberInfo
			{
				GameID = plugin.db_id(),
				AvatarUrl = "avartarUrl" + plugin.db_id(),
				NickName = "nic" + plugin.db_id(),
				GenderOption = true,
			},
		};
		plugin.send_to_MSG(connect);

	}

	public void logout(nNWM.nConsole.jConsoleArg arg)
	{
		const int eUID = 0;
		if (IsFail_ArgCheck(arg, "<uid>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null){m_CMD.LogWarning("user not found"); return;}

		var sd = new MSG.ReqClose { };
		plugin.send_to_MSG(sd);
	}
	public void destroy(nNWM.nConsole.jConsoleArg arg)
	{
		const int eUID = 0;
		if (IsFail_ArgCheck(arg, "<uid>")) return;

		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }

		m_MSG.DeletePlugin(plugin);
	}

	void ReqChannel(nNWM.nConsole.jConsoleArg arg)
	{
		const int eUID = 0;
		if (IsFail_ArgCheck(arg, "<uid>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }
		//-------------------------------------------------------------------

		var sd = new MSG.ReqChannel{ };
		plugin.send_to_MSG(sd);

	}


	static int s_iSerial = 0;
	void x2ug_echo(nNWM.nConsole.jConsoleArg arg)
	{
		const int eUID = 0, eMSG=1;
		if (IsFail_ArgCheck(arg, "<uid> <message>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }
		//-------------------------------------------------------------------
		var sd = plugin.Make(nProtoUGasdf.Client_UserGateServer.Type.x2ug_echo);
		sd.m_x2ug_echo = new nProtoUGasdf.s_x2ug_echo
		{
			type = 0,
			msg = (arg.Get_string(eMSG) + s_iSerial++),
		};
		plugin.send_to_ug(sd);
	}

	void x2gs_echo(nNWM.nConsole.jConsoleArg arg)
	{
		const int eUID = 0, eMSG = 1;
		if (IsFail_ArgCheck(arg, "<uid> <message>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }
		//-------------------------------------------------------------------

		var sd = plugin.Make(nProtoGSasdf.Client_GameServer.Type.x2gs_echo);
		sd.m_x2gs_echo = new nProtoGSasdf.s_x2gs_echo
		{
			type = 0,
			msg = (arg.Get_string(eMSG) + s_iSerial++),
		};
		plugin.send_to_gs(sd);
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
		sd.m_asdf = new nProtoGSasdf.s_asdf
		{
			uid = plugin.db_id(),
			batter = arg.Get_int32(eBATTER),
		};
		plugin.send_to_gs(sd);


	}
	 
	 * */


}//public class asdf_cmd_user : CmdEvent_base
