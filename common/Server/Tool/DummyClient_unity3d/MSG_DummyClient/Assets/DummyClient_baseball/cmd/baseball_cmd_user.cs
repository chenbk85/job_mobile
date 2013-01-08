using UnityEngine;
using System.Collections;
using user_id_t = System.Int64;

using nNWM;

public class baseball_cmd_user : CmdEvent_base
{
	nNWM.nBaseball.NetEventPlugin_baseball cmd_NetEventPlugin2(string sUID)
	{
		return (nNWM.nBaseball.NetEventPlugin_baseball)base.cmd_NetEventPlugin(sUID);
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
			plugin = new nNWM.nBaseball.NetEventPlugin_baseball(user_id_t.Parse(arg[eUID]), m_CMD, m_MSG);
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

	static int s_iSeq_ReqDB = 0;
	public void req_db_table(nNWM.nConsole.jConsoleArg arg)
	{
		const int eUID = 0;
		if (IsFail_ArgCheck(arg, "<uid>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }

		string[] excel_tbl_list = new string[] { "tbl_user", }; //gameLogic.proto에서 GameInfo에 있는 테이블 리스트.
		foreach (var tbl in excel_tbl_list)
		{
			if (tbl == "tbl_user")
			{
				plugin.m_User.m_GameInfo.m_tbl_user.Clear();
			}

			string sREQ = "GameInfo." + tbl;
			const int startRecordIndex = 0;
			plugin.m_User.m_ServerInfoRecvState[tbl] = startRecordIndex;// 받을 테이블 레코드 인덱스 초기화.

			var db = new MSG.ReqDB
			{
				Seq = ++s_iSeq_ReqDB,
				Query = sREQ,
			};
			db.Params.Add(new MSG.DBIn
			{
				Type = MSG.DBIn.TypeEnum.Int,
				Value = startRecordIndex.ToString(),
			});
			plugin.send_to_MSG(db, "req_db_table");
		}
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

	public void x2ug_get_client_version(nNWM.nConsole.jConsoleArg arg)
	{
		const int eUID=0;
		if (IsFail_ArgCheck(arg, "<uid>")) return;

		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null)
		{
			m_CMD.LogError(arg[eUID] + " is not found");
			return;
		}
		
		var sd = plugin.Make(nProtoUG.Client_UserGateServer.Type.x2ug_get_client_version);
		sd.m_x2ug_get_client_version = new nProtoUG.s_x2ug_get_client_version
		{
			version = "client"
		};
		plugin.send_to_ug(sd);
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
		var sd = plugin.Make(nProtoUG.Client_UserGateServer.Type.x2ug_echo);
		sd.m_x2ug_echo = new nProtoUG.s_x2ug_echo
		{
			type = 0,
			msg = (arg.Get_string(eMSG) + s_iSerial++),
		};
		plugin.send_to_ug(sd);
	}

	void x2bs_echo(nNWM.nConsole.jConsoleArg arg)
	{
		const int eUID = 0, eMSG = 1;
		if (IsFail_ArgCheck(arg, "<uid> <message>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }
		//-------------------------------------------------------------------

		var sd = plugin.Make(nProtoBS.Client_BaseballServer.Type.x2bs_echo);
		sd.m_x2bs_echo = new nProtoBS.s_x2bs_echo
		{
			type = 0,
			msg = (arg.Get_string(eMSG) + s_iSerial++),
		};
		plugin.send_to_gs(sd);
	}
	/*
	 * 템플릿 코드.
	 
	void asdf(nNWM.nConsole.jConsoleArg arg)
	{
		const int eUID = 0;
		if (IsFail_ArgCheck(arg, "<uid>")) return;
		var plugin = cmd_NetEventPlugin2(arg[eUID]);
		if (plugin == null) { m_CMD.LogWarning("user not found"); return; }
		//-------------------------------------------------------------------

		var sd = plugin.Make(nProtoBS.Client_BaseballServer.Type.asdf);
		sd.m_asdf = new nProtoBS.s_asdf
		{
			uid = plugin.db_id(),
			batter = arg.Get_int32(eBATTER),
		};
		plugin.send_to_gs(sd);


	}
	 
	 * */


}//public class baseball_cmd_user : CmdEvent_base
