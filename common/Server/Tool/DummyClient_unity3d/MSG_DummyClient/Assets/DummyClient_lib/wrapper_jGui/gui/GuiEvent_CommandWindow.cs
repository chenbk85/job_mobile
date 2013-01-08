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


public class GuiEvent_CommandWindow : nNWM.nDummy.GuiEvent_base
{
	jGuiTextField m_txt_CommandLine;
	jGuiScrollView m_scroll_CmdList;

	//#--------------------------------------------------------------------------
	// MonoBehaviour Event
	//#--------------------------------------------------------------------------
	void OnDestroy()
	{
		jGuiToolbar tb = (jGuiToolbar)m_jGuiWindow.FindCtrl("PlayerList");
		m_CMD.Get_jPlayerPrefs().Set("PlayerList_TookBarIndex", tb.GetToolBarIndex());
	}

	//#--------------------------------------------------------------------------
	// public member function
	//#--------------------------------------------------------------------------
	public void Reload_PlayerCmd()
	{
		jGuiToolbar tb = (jGuiToolbar)m_jGuiWindow.FindCtrl("PlayerList");
		jxE eChild = tb.m_jxE.GetChild(tb.GetToolBarIndex());
		string[] cmdList = (string[])eChild.GetUserData("PlayerCmd");
		SetPlayerCmdList(cmdList,tb.GetToolBarIndex());
	}

	//#--------------------------------------------------------------------------
	// private member function
	//#--------------------------------------------------------------------------

	void AddPlayerCmd(string cmd, int idx)
	{
		// 맨처음 노드는 cmd용 original 탬플릿이다.
		jxE eCmdGroup;
		bool isReloadGui = false;
		if (idx >= m_scroll_CmdList.m_jxE.size())
		{
			eCmdGroup = m_scroll_CmdList.m_jxE.begin().MakeClone();
			m_scroll_CmdList.m_jxE.InsertChild(eCmdGroup);
			isReloadGui = true;
		}
		else
		{
			eCmdGroup = m_scroll_CmdList.m_jxE.GetChild(idx);
		}

		eCmdGroup.AttrVar("Enable").Set_bool(true);
		jxA a;
		jxE eCmdText = eCmdGroup.FindByAttr("Name", "CmdRun", out a);
		a = eCmdText.AttrVar("Text");
		a.Set_string(cmd);

		if (isReloadGui)
		{
			// jGuiContorl 리로딩.
			jGuiControl ctrl = m_scroll_CmdList.GetStage().CreateRTTI(eCmdGroup);
			jDebug.jASSERT(ctrl != null);
			ctrl.m_isLayouted = m_scroll_CmdList.m_isLayouted;
			ctrl.Load(m_scroll_CmdList.GetStage()
				, m_scroll_CmdList.GetWindow()
				, m_scroll_CmdList
				, eCmdGroup
				, m_scroll_CmdList.Get_OverrideAttribute());
		}
		else
		{
			jGuiButton btn = (jGuiButton)eCmdText.m_UserData;
			btn.SetText(cmd);
		}
	}

	void SetPlayerCmdList(string[] cmdList,int player_index)
	{
		string uid = m_CMD.m_PlayerCmdFile[player_index].USER_ID;
		foreach (jxE e in m_scroll_CmdList.m_jxE)
		{
			e.AttrVar("Enable").Set_bool(false);
		}

		int idx = 0;
		foreach (var s in cmdList)
		{
			string cmd = s.Trim();
			if (cmd.Length <= 0) continue;
			if (cmd.Substring(0, 2) == "//")
				continue;

			cmd = cmd.Replace("{SERVER_IP}", m_CMD.m_ServerIP);
			cmd = cmd.Replace("{SERVER_PORT}", m_CMD.m_ServerPort.ToString());
			cmd = cmd.Replace("{USER_ID}", uid);
			
			AddPlayerCmd(cmd, idx++);
		}
	}


	//#--------------------------------------------------------------------------
	// jGui Event Handler
	//#--------------------------------------------------------------------------
	void OnLoadedGUI_CommandWindow(jGuiWindow win)// "CommandWindow"라는 jGuiWindow 로딩이 완료되면 호출됨.
	{
		base.Set_jGuiWindow(win);

		m_scroll_CmdList = (jGuiScrollView)m_jGuiWindow.FindCtrl("CmdList");
		if (m_scroll_CmdList == null) throw new System.Exception("CmdList(jGuiScrollView) not found");

		m_txt_CommandLine = (jGuiTextField)m_jGuiWindow.FindCtrl("CommandLine");
		if (m_txt_CommandLine == null) throw new System.Exception("CommandLine(jGuiTextField) not found");

		//load_PlayerCmdFile();
		{
			string[] cmdList;
			jGuiToolbar tb = (jGuiToolbar)m_jGuiWindow.FindCtrl("PlayerList");
			if (tb == null)
			{
				throw new System.Exception("PlayerList == null");
			}
			if (m_CMD == null)
			{
				throw new System.Exception("m_CMD == null");
			}

			foreach (jxE e in tb.m_jxE)
			{
				string fileText = m_CMD.m_PlayerCmdFile[e.GetOrder()].text_file.text;
				cmdList = fileText.Split('\n');
				e.SetUserData("PlayerCmd", cmdList);
			}

			int toolbarIndex = tb.GetToolBarIndex();
			m_CMD.Get_jPlayerPrefs().Get("PlayerList_TookBarIndex", ref toolbarIndex);
			tb.SetToolBarIndex(toolbarIndex);

			jxE eChild = tb.m_jxE.GetChild(tb.GetToolBarIndex());
			cmdList = (string[])eChild.GetUserData("PlayerCmd");
			SetPlayerCmdList(cmdList, tb.GetToolBarIndex());

		}

		this.SetWindowText(m_CMD.m_ServerName + " - " + m_CMD.m_ServerIP + ":" + m_CMD.m_ServerPort);


	}

	void jGuiButton_Run(jGuiButton ctrl) // jGuiButton 컨트롤중에 "Run" 이라는 Name속성을 가지는 버튼이 눌러졌다.
	{
		string strCmdLine = m_txt_CommandLine.GetText();
		if (strCmdLine.Length == 0) return;
		bool isOk = m_CMD.ParseCmd(strCmdLine);
		if (isOk)
			m_txt_CommandLine.SetText("");
	}

	

	void jGuiButton_CmdRun(jGuiButton ctrl)
	{
		m_CMD.ParseCmd(ctrl.GetText());
	}
	void jGuiButton_CmdEdit(jGuiButton ctrl)
	{
		string str = ctrl.GetParent().FindCtrl("CmdRun").GetText();
		m_txt_CommandLine.SetText(str);
	}
	void jGuiButton_GameManu(jGuiButton ctrl)
	{
		m_jGuiStage.HideModalWindow();	//모달 윈도우를 종료한다.
		m_GUI.enabled = false;

		var gui2 = (nNWM.nGui.jGuiEventManager)GetComponent(m_CMD.m_GameGuiEventManager);
		gui2.enabled = true;
	}

	void jGuiToolbar_PlayerList(jGuiToolbar tb)
	{
		jxE eChild = tb.m_jxE.GetChild(tb.GetToolBarIndex());
		string[] cmdList = (string[])eChild.GetUserData("PlayerCmd");
		SetPlayerCmdList(cmdList, tb.GetToolBarIndex());
	}

	void jGuiButton_ChangeServer(jGuiButton ctrl)
	{
		m_jGuiStage.ShowModalWindow("ServerList");
	}


	void jGuiButton_Config(jGuiButton ctrl)
	{
		m_jGuiStage.ShowModalWindow("ConfigWindow");
		
	}

}
