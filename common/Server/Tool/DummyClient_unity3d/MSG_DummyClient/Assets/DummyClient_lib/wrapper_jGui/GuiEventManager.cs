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

public class GuiEventManager : nNWM.nGui.jGuiEventManager
{
	public CmdEventManager m_CMD;

	protected override void OnStart()
	{
		if (m_CMD == null)
		{
			Debug.LogError("m_CMD is null. set CmdEventManager gameobject to m_CMD");
			return;
		}
		m_CMD.Set_GuiEvent_LogWindow(GetComponent<GuiEvent_LogWindow>());
	}

	// "dummy_client"라는 jGuiStage xml파일을 로딩했을때 호출됨.
	protected void OnLoadStageXML_dummy_client(nNWM.nXML.jxDocument stageXml) 
	{
		jxE xml = stageXml.m_Root;
		jxV v =null;
		jxE ePlayerList = xml.FindByAttr("Name", "PlayerList", out v);
		int iTot = m_CMD.m_PlayerCmdFile.Length - 1;
		Debug.Log("m_CMD.m_PlayerCmdFile.Length  = " + m_CMD.m_PlayerCmdFile.Length);
		for (int i = 0; i <  iTot; ++i)
		{
			jxE eClone = ePlayerList.begin().MakeClone();
			ePlayerList.InsertChild(eClone);
		}
	
		int idx = 0;
		foreach (jxE e in ePlayerList)
		{
			e.Set_string(m_CMD.m_PlayerCmdFile[idx++].USER_ID);
		}
	}

	IEnumerator _show_ServerListWindow()
	{
		enabled = false;
		yield return new WaitForSeconds(0.1f);
		m_jGuiStage.ShowModalWindow("ServerList");//see Assets\DummyClient_lib\wrapper_jGui\guixml_dummy_client.xml
		enabled = true;
	}

	// "dummy_client"라는 jGuiStage xml파일의 jGuiControl에 대한 초기화가 완료되었을때 호출됨.
	protected void OnLoadStageGUI_dummy_client(jGuiStage stage)
	{
		StartCoroutine(_show_ServerListWindow());
	}

}//public class GuiEventManager

