using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using nNWM;
using nNWM.nGui;

using jxD = nNWM.nXML.jxDocument; // xml doc;
using jxE = nNWM.nXML.jxElement; // xml element
using jxA = nNWM.nXML.jxVar; // element attribute
using jxV = nNWM.nXML.jxVar; // attribute or element data
using string_id_t = System.Int32;


//#--------------------------------------------------------------------------
public class CmdEventManager : MonoBehaviour
//#--------------------------------------------------------------------------
{
	[System.Serializable]
	public class PlayerCmdFile
	{
		public string USER_ID;
		public TextAsset text_file;
	}
	public PlayerCmdFile[] m_PlayerCmdFile;

	public NetEventManager m_MSG;
	public string m_CmdPrefix = "cmd_"; // 콘솔명령의 이벤트를 받을 c#파일명앞에 붙을 접두어.
	public string m_ServerName = "QA";
	public string m_ServerIP = "182.162.130.34";
	public int m_ServerPort = 15200;
	public string m_DefaultServerListName = "BaseballServerList"; // m_docServerList에서의 그룹명.
	public TextAsset m_DefaultServerListXml;
	public bool m_isAddLogCount = false;
	public int m_MaxLogLine = 300;
	public bool m_isAutoPlay = true;
	public string m_GameGuiEventManager = "GuiEventManager_baseball"; // game 별 main gui


	jxD m_docServerList; // Assets\DummyClient_lib\wrapper_Cmd\download_server_list.js에서 설정된 URL에서 다운받은 서버리스트 xml.
	nNWM.nConsole.jConsoleCmdManager m_jConsoleCmdManager;
	GuiEvent_LogWindow m_GuiEvent_LogWindow;
	string m_LoadedServerListURL = "";
	public string GetLoadedServerListURL() { return m_LoadedServerListURL; }
	nNWM.nDummy.jPlayerPrefs m_jPlayerPrefs;
	public nNWM.nDummy.jPlayerPrefs Get_jPlayerPrefs() { return m_jPlayerPrefs; }

	//#--------------------------------------------------------------------------
	// unity3d event call
	//#--------------------------------------------------------------------------
	void Start()
	{
		m_jPlayerPrefs = new nNWM.nDummy.jPlayerPrefs(this);
		//print("asdf = " + m_ServerName.GetType().FullName);

		m_jPlayerPrefs.Get("USER_ID1", ref m_PlayerCmdFile[0].USER_ID);
		m_jPlayerPrefs.Get("USER_ID2", ref m_PlayerCmdFile[1].USER_ID);
		m_jPlayerPrefs.Get("USER_ID3", ref m_PlayerCmdFile[2].USER_ID);
		m_jPlayerPrefs.Get("USER_ID4", ref m_PlayerCmdFile[3].USER_ID);

		m_jPlayerPrefs.Get("m_MaxLogLine"	, ref m_MaxLogLine);
		m_jPlayerPrefs.Get("m_ServerName"	, ref m_ServerName);
		m_jPlayerPrefs.Get("m_ServerIP"		, ref m_ServerIP);
		m_jPlayerPrefs.Get("m_ServerPort"	, ref m_ServerPort);
		m_jPlayerPrefs.Get("m_isAutoPlay"	, ref m_isAutoPlay);
		m_jPlayerPrefs.Get("m_isAddLogCount", ref m_isAddLogCount);

		m_jPlayerPrefs.Get("Version", ref m_MSG.Version);

		
		//m_GuiEvent_LogWindow = GetComponent<GuiEvent_LogWindow>();
		m_jConsoleCmdManager = new nNWM.nConsole.jConsoleCmdManager(gameObject, m_CmdPrefix);

		// 		m_wwwServerList = new WWW(m_ServerListURL); 
		//     StartCoroutine(WaitForAudioClip());
	}
	void OnDestroy() 
	{
		m_jPlayerPrefs.Set("USER_ID1", m_PlayerCmdFile[0].USER_ID);
		m_jPlayerPrefs.Set("USER_ID2", m_PlayerCmdFile[1].USER_ID);
		m_jPlayerPrefs.Set("USER_ID3", m_PlayerCmdFile[2].USER_ID);
		m_jPlayerPrefs.Set("USER_ID4", m_PlayerCmdFile[3].USER_ID);

		m_jPlayerPrefs.Set("m_MaxLogLine", m_MaxLogLine);
		m_jPlayerPrefs.Set("m_ServerName", m_ServerName);
		m_jPlayerPrefs.Set("m_ServerIP"	, m_ServerIP);
		m_jPlayerPrefs.Set("m_ServerPort", m_ServerPort);
		m_jPlayerPrefs.Set("m_isAutoPlay", m_isAutoPlay);
		m_jPlayerPrefs.Set("m_isAddLogCount", m_isAddLogCount);

		m_jPlayerPrefs.Set("Version", m_MSG.Version);

	}
	//#--------------------------------------------------------------------------
	// public member function
	//#--------------------------------------------------------------------------
	public jxE GetCurrServerList()
	{
		return m_docServerList.m_Root.Find(m_DefaultServerListName);
	}

	int m_LogCount = 0;
	public void Log(string log)
	{
		++m_LogCount;
		if (m_isAddLogCount)
		{
			log = m_LogCount + ":" + log;
		}
		m_GuiEvent_LogWindow.Log(log);
		Debug.Log(log);
	}
	public void LogWarning(string log)
	{
		++m_LogCount;
		log = "[WARN]" + log;
		if (m_isAddLogCount)
		{
			log += (m_LogCount + ":");
		}
		m_GuiEvent_LogWindow.Log(log);
		Debug.LogWarning(log);
	}
	public void LogError(string log)
	{
		++m_LogCount;
		log = "[ERROR]" + log;
		if (m_isAddLogCount)
		{
			log += (m_LogCount + ":");
		}
		m_GuiEvent_LogWindow.Log(log);
		//Debug.LogError(log);
		Debug.LogWarning(log);
	}

	public void SetServerListURL(string url)
	{
		m_LoadedServerListURL = url;
	}
	public void LoadServerList(string xml)
	{
		string url = m_LoadedServerListURL;
		if (xml == null)
		{
			LogWarning("DON'T download server_list xml : url=" + url);
			xml = m_DefaultServerListXml.text;
		}
		else
		{
			Log("OK : downloaded server_list xml : url=" + url);
		}

		if (xml.Contains(m_DefaultServerListName) == false)
		{
			LogWarning("CAN't find [" + m_DefaultServerListName + "] server_list xml : url=" + url);
			xml = m_DefaultServerListXml.text;
			Log("USE : Default Server List File");
			if (xml.Contains(m_DefaultServerListName) == false)
			{
				throw new System.Exception("CAN't find [" + m_DefaultServerListName + "] Default server_list xml");
			}
		}
		m_docServerList = nNWM.nXML.jxDocument.Load("server_list", xml);
		if (m_docServerList == null)
			throw new System.Exception(xml);

	}

	public void Set_GuiEvent_LogWindow(GuiEvent_LogWindow lw)
	{
		if (lw == null)
			throw new System.Exception("GuiEvent_LogWindow  is null");
		m_GuiEvent_LogWindow = lw;
	}

	public bool ParseCmd(string sInputCmd)
	{
		Log(sInputCmd);
		bool isOk = m_jConsoleCmdManager.ParseCmd(sInputCmd);
		if (!isOk)
		{
			LogWarning(" FAIL : " + sInputCmd);
		}
		return isOk;
	}


}//public class CmdEventManager : MonoBehaviour

