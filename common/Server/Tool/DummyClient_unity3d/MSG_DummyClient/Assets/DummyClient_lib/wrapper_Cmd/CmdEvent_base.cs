using UnityEngine;
using System.Collections;

using user_id_t = System.Int64;
using nNWM;

public class CmdEvent_base : MonoBehaviour
{
	protected CmdEventManager m_CMD;
	protected NetEventManager m_MSG;

	public void Start()
	{
		m_CMD = gameObject.GetComponent<CmdEventManager>();
		if (m_CMD == null) throw new System.Exception("m_CMD==null");
		m_MSG = m_CMD.m_MSG;
		if (m_MSG == null) throw new System.Exception("m_MSG==null");
	}

	protected bool IsFail_ArgCheck(nNWM.nConsole.jConsoleArg arg, string sFormat)// 인자 유효성검사가 실패이면 true 리턴.
	{
		string error = arg.CheckArg(sFormat);
		if (error.Length == 0) return false;
		m_CMD.LogWarning(error);
		return true;
	}
	protected nNWM.nDummy.NetEventPlugin cmd_NetEventPlugin(string sUid) { return cmd_NetEventPlugin(user_id_t.Parse(sUid)); }
	protected nNWM.nDummy.NetEventPlugin cmd_NetEventPlugin(user_id_t uid)
	{
		nNWM.nDummy.NetEventPlugin plugin = m_MSG.Find(uid);
		if (plugin == null)
		{
			m_CMD.LogWarning("uid (" + uid + ") is not found");
			return null;
		}
		return plugin;
	}
	protected static T Deserialize<T>(byte[] buffer){return nNWM.nDummy.NetEventPlugin.Deserialize<T>(buffer);}
	protected static byte[] Serialize<T>(T sd){ return nNWM.nDummy.NetEventPlugin.Serialize<T>(sd);}

}

