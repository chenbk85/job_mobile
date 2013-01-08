using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using nNWM;
using user_id_t = System.Int64;


namespace nNWM
{
	namespace nDummy
	{

		public class DummyClientLogger : MSG.Logger
		{

			public override void HandleLog(string log)
			{
				Debug.Log(log);
			}
		}
	}//namespace nDummy
}//namespace nNWM




	public class CustomObj
	{
		public string i;
		public CustomObj(string ii){ i = ii;}
	}

public class NetEventManager : MonoBehaviour 
{
	public int SvcID = 100;
	public int Version = 270;
	public MSG.LogLevel m_MSG_LogLevel = MSG.LogLevel.Debug;
	public nNWM.nUtil.jDumper.EDumpType m_PacketLogType = nNWM.nUtil.jDumper.EDumpType.eONLY_NAME;
	public string m_RecvPrefix = "recv_";

	Dictionary<user_id_t, nNWM.nDummy.NetEventPlugin> m_mapMSGClient = new Dictionary<user_id_t, nNWM.nDummy.NetEventPlugin>();
	List<user_id_t> m_discon_uid_list=new List<user_id_t> ();

	//#--------------------------------------------------------------------------
	// NetEventManager's  MonoBehaviour Event.
	//#--------------------------------------------------------------------------

	void Start()
	{
	}
	void OnDestroy() 
	{
	}

	void Update() 
	{
		MSG.MSGEvent e=null;
		PlayerPrefs.SetString("m_MSG_LogLevel", m_MSG_LogLevel.ToString());

		m_discon_uid_list.Clear();
		foreach (var v in m_mapMSGClient)
		{
			nNWM.nDummy.NetEventPlugin plugin = v.Value;
			MSG.MSGClient client = plugin.m_MSGClient;
			if(client==null) continue;

			while (client.PopEvent(out e))
			{
				switch (e.EventType)
				{
					case MSG.MSGEventType.Connected:
						plugin.NetLog("[Net] On Connect : " + plugin.db_id() ,true);//nNWM.nUtil.jDumper.NamedDump(e));
						plugin.OnConnect();
						break;
					case MSG.MSGEventType.Disconnected:
						plugin.NetLog("[Net] On Disconnect",true);// + nNWM.nUtil.jDumper.NamedDump(e),true);
						plugin.OnDisconnect();
						plugin.m_MSGClient = null;
						//m_discon_uid_list.Add(plugin.db_id());
						break;
					case MSG.MSGEventType.RecvMessage:
						onRecvFromUG(plugin,e);
						break;
					default:
						plugin.NetError("[Net] Unkown MSGEventType : " + e.EventType.ToString() + " : " + nNWM.nUtil.jDumper.NamedDump(e) );
						break;
				}
			}
			if(e!=null)
				client.InsertEventToRecyclingPool(e);
		}//foreach (var v in m_mapMSGClient)
		
// 		foreach(var uid in m_discon_uid_list)
// 		{
// 			m_mapMSGClient.Remove(uid);
// 		}

	}//void FixedUpdate () 



	//#--------------------------------------------------------------------------
	// private member function
	//#--------------------------------------------------------------------------

	void onRecvFromUG(nNWM.nDummy.NetEventPlugin plugin, MSG.MSGEvent e)
	{
		MSG.AnswerMessage ans = e.RecvMessage;

		switch (ans.Type)
		{
			case MSG.AnswerMessage.AnsType.Connect:
				//status = Status.Login;
				plugin.NetLog("[Recv:MSG] AnsConnect (Login Succeed)=>" + nNWM.nUtil.jDumper.NamedDump(ans.Connect,m_PacketLogType), true);
				plugin.OnRecv_FromMSG(ans.Connect);
				break;
			case MSG.AnswerMessage.AnsType.Info:
				plugin.NetLog("[Recv:MSG] AnsGameInfo  ",true);// + System.BitConverter.ToString(ans.Info.GameInfo), true);
				plugin.OnRecv_FromMSG(ans.Info);
				break;
			case MSG.AnswerMessage.AnsType.Channel:
				plugin.NetLog("[Recv:MSG] AnsChannel", true);
				plugin.OnRecv_FromMSG(ans.Channel);
				break;
			case MSG.AnswerMessage.AnsType.AutoJoin:
				plugin.NetLog("[Recv:MSG] AnsAutoJoin ", true);
				plugin.OnRecv_FromMSG(ans.AutoJoin);
				break;
			case MSG.AnswerMessage.AnsType.LeaveGame:
				plugin.NetLog("[Recv:MSG] AnsLeaveGame", true);
				//plugin.m_CMD.Log(nNWM.nUtil.jDumper.NamedDump(ans.LeaveGame));
				plugin.OnRecv_FromMSG(ans.LeaveGame);
				break;
			case MSG.AnswerMessage.AnsType.Close:
				plugin.NetLog("[Recv:MSG] AnsClose ", true);
				plugin.m_CMD.Log(nNWM.nUtil.jDumper.NamedDump(ans.Close));
				plugin.OnRecv_FromMSG(ans.Close);
				break;
			case MSG.AnswerMessage.AnsType.Notice:
				plugin.NetLog("[Recv:MSG] AnsNotice =>" + nNWM.nUtil.jDumper.NamedDump(ans.Notice.Notices,m_PacketLogType), true);
				plugin.OnRecv_FromMSG(ans.Notice);
				break;
			case MSG.AnswerMessage.AnsType.DB:
				plugin.OnRecv_FromMSG(ans.DB);
				break;
			case MSG.AnswerMessage.AnsType.GameProtocol:
				//status = Status.InGame;
				//plugin.NetLog("[Recv:MSG] GameProtocol", true);
				//plugin.Log("Message => " + BitConverter.ToString(ans.GameProtocol.Buffer));
				plugin.OnRecv_FromGameServer(ans.GameProtocol.Buffer);
				break;
			case MSG.AnswerMessage.AnsType.Error:
				plugin.NetError("[Recv:MSG] AnsError =>" + nNWM.nUtil.jDumper.NamedDump(ans.Error,nNWM.nUtil.jDumper.EDumpType.eALL));
				plugin.OnRecv_FromMSG(ans.Error);
				break;

			default:
				plugin.NetError("[Recv:MSG] Unkown AnswerMessage =>" + nNWM.nUtil.jDumper.NamedDump(ans));
				plugin.OnRecv_Unkown(ans);
				break;
		}
	}//void onRecvFromUG(MSGEvent e)


	//#--------------------------------------------------------------------------
	// Public member function
	//#--------------------------------------------------------------------------
	public nNWM.nDummy.NetEventPlugin Find(user_id_t pp_id)
	{
		nNWM.nDummy.NetEventPlugin plugin;

		if (m_mapMSGClient.TryGetValue(pp_id, out plugin))
			return plugin;
		return null;
	}
	public void Login(string ip, int port, nNWM.nDummy.NetEventPlugin plugin, MSG.Logger logger = null)
	{
		user_id_t uid = plugin.db_id();
		bool isExist=false;
		if (m_mapMSGClient.ContainsKey(uid) == true)
		{
			if(plugin.m_MSGClient!=null)
			{
				plugin.NetError(" already logined. Do \"@user.logout " +uid +"\"");
				return;
			}
			isExist=true;
		}
		if(logger==null)
		{
			logger = new nNWM.nDummy.DummyClientLogger() ;
		}
		MSG.MSGClient client = new MSG.MSGClient(uid.ToString(), logger);
		client.LogLevel = m_MSG_LogLevel;

		plugin.m_MSGClient = client;
		try
		{
			bool isOk = plugin.m_MSGClient.Connect(ip, port);
			if(!isOk)
			{
				plugin.NetError(" Login Fail");
				return;
			}
		}
		catch(System.Exception ex)
		{
			plugin.NetError("Login : " + ex.ToString() );
			return;
		}
		if(isExist==false)
		{
			m_mapMSGClient.Add(uid, plugin);
		}
	}
	public void Logout(nNWM.nDummy.NetEventPlugin plugin)
	{
		if(plugin==null)
		{
			Debug.LogWarning("Logout : plugin ==null");
			return;
		}
		MSG.MSGClient client = plugin.m_MSGClient;
		if (client == null)
		{
			Debug.LogWarning("client ==null");
			return;
		}
		if(client.IsConnected)
		{
			client.Close(true);
		}
	}

	public void CallNetEvent(string sCategory, string eventName , nNWM.nDummy.NetEventArg arg)
	{
		string sScript = m_RecvPrefix + sCategory;
		Component cp = gameObject.GetComponent(sScript);
		if (cp == null)
		{
			arg.plugin.NetError("c# script file not found : " + sScript + " : " + eventName);
			return;
		}
		//arg.plugin.NetLog("[Recv:" + sCategory + "]" + eventName);
		cp.SendMessage(eventName, arg, SendMessageOptions.DontRequireReceiver);
	}

	public void DeletePlugin(nNWM.nDummy.NetEventPlugin plugin)
	{
		m_mapMSGClient.Remove(plugin.db_id());
	}

}//public class NetEventManager : MonoBehaviour 
