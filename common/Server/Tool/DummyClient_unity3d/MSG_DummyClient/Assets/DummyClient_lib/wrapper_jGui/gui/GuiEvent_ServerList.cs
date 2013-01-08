using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;

using nNWM;
using nNWM.nGui;

using jxD = nNWM.nXML.jxDocument; // xml doc;
using jxE = nNWM.nXML.jxElement; // xml element
using jxA = nNWM.nXML.jxVar; // element attribute
using jxV = nNWM.nXML.jxVar; // attribute or element data
using string_id_t = System.Int32;


public class GuiEvent_ServerList : nNWM.nDummy.GuiEvent_base
{
	jGuiScrollView m_guiServerList;
	void OnLoadedGUI_ServerList(jGuiWindow win) // "ServerList"라는 jGuiWindow 로딩이 완료되면 호출됨.
	{
		base.Set_jGuiWindow(win);// 반드시 호출.

		m_guiServerList = (jGuiScrollView)m_jGuiWindow.FindCtrl("ServerList_ScrollView");
		if(m_guiServerList==null) 
			throw new System.Exception("ServerList(jGuiScrollView ) is not found");

	}
	void OnShowModal_ServerList(jGuiWindow win) // "ServerList"라는 모달
	{
		jxE eServerList = m_CMD.GetCurrServerList();
		if (eServerList == null)
		{
			m_CMD.LogWarning(m_CMD.m_DefaultServerListName + " is not found in ServerList xml");
			return;
		}

		int iSize = eServerList.size() - m_guiServerList.m_jxE.size();
		if (iSize > 0)// 다운로드 받은 서버리스트 보다 gui xml의 서버리스트 컨트롤이 적다면 컨트롤 추가.
		{
			for (int i = 0; i < iSize; ++i)
			{
				jxE eServer = m_guiServerList.m_jxE.begin().MakeClone();
				m_guiServerList.m_jxE.InsertChild(eServer);

				// jGuiContorl 리로딩.
				jGuiControl new_ctrl = m_guiServerList.GetStage().CreateRTTI(eServer);
				if (new_ctrl == null)
				{
					eServer.DebugPrint();
					throw new System.Exception("CreateRTTI : new_ctrl==null");
				}
				new_ctrl.m_isLayouted = m_guiServerList.m_isLayouted;
				new_ctrl.Load(m_guiServerList.GetStage()
					, m_guiServerList.GetWindow()
					, m_guiServerList
					, eServer
					, m_guiServerList.Get_OverrideAttribute());
			}
		}
		int idx = 0;
		foreach (jGuiControl gui in m_guiServerList)
		{
			if (idx >= eServerList.size())
			{
				gui.SetEnabled(false);
				continue;
			}
			var btn = (jGuiButton)gui.FindCtrl("ServerOk");
			jxE server =eServerList.GetChild(idx);
			string name = server.Attr("NAME");
			string text = name+ " " + server.Attr("IP") + ":" + server.AttrVar("PORT").Get_int().ToString();
			var lbl = (jGuiLabel)gui.FindCtrl("ServerStatus");
			if (name == m_CMD.m_ServerName)
			{
				lbl.SetText("Selected");
			}
			else
			{
				lbl.SetText("Unkown");
			}

			btn.SetText(text);
			++idx;
		}
		UpdateServerStatus();
	}

	bool tryConnectToServer(string ip , int port)
	{
		try
		{
			IPAddress serverIP = IPAddress.Parse(ip);
			IPEndPoint serverEndPoint = new IPEndPoint(serverIP, port);
			Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
			socket.Connect(serverEndPoint);
			return socket.Connected;
		}
		catch (System.Exception )
		{
			
		}
		return false;
	}

	IEnumerator _gettering_server_state()
	{
		jxE eServerList = m_CMD.GetCurrServerList();

		int idx = 0;
		foreach (jGuiControl gui in m_guiServerList)
		{
			var lbl = (jGuiLabel)gui.FindCtrl("ServerStatus");
			if (lbl == null) continue;

			jxE server = eServerList.GetChild(idx);
			bool isOk = tryConnectToServer(server.Attr("IP"), server.AttrVar("PORT").Get_int());

			if (isOk)
			{
				lbl.SetText("Online");
			}
			else
			{
				lbl.SetText("Offline");
			}
			if (m_CMD.m_ServerName == server.Attr("Name"))
			{
				lbl.SetText("[" + lbl.GetText() + "]");
			}
			++idx;
			
			//yield return new WaitForSeconds(1.0f);
			yield return 0;

		}
		m_jGuiWindow.SetText("Select Server : Status update Completed.");
	}
	void UpdateServerStatus()
	{
		m_jGuiWindow.SetText("Wait! Status is updating");
		foreach (jGuiControl gui in m_guiServerList)
		{
			var lbl = (jGuiLabel)gui.FindCtrl("ServerStatus");
			if (lbl == null) continue;
			lbl.SetText("???");
		}
		StartCoroutine(_gettering_server_state());
	}
	void jGuiButton_Refresh(jGuiButton ctrl)
	{
		UpdateServerStatus();
	}

	void jGuiButton_Cancel(jGuiButton ctrl)
	{
		m_jGuiStage.HideModalWindow();//모달 윈도우를 종료한다.
	}

	void jGuiButton_ServerOk(jGuiButton ctrl)
	{
		var lbl = (jGuiControl)ctrl.GetParent().FindCtrl("ServerStatus");
		if (lbl.GetText().Contains("Offline"))
		{
			return;
		}

		m_jGuiStage.HideModalWindow();
		int iOrder = ctrl.GetParent().m_jxE.GetOrder();
		jxE eServerList = m_CMD.GetCurrServerList();
		if (iOrder >= eServerList.size())
		{
			m_CMD.LogWarning("ctrl.m_jxE.GetOrder() is overflow : " + iOrder + "eServerList.size() = " + eServerList.size());
			return;
		}
		jxE server= eServerList.GetChild(iOrder);

		m_CMD.m_ServerIP = server.Attr("IP");
		m_CMD.m_ServerName = server.Attr("NAME");
		m_CMD.m_ServerPort = server.AttrVar("PORT").Get_int();
		//Debug.Log("ip : " + m_CMD.m_ServerIP + " " + m_CMD.m_ServerPort + " " + m_CMD.m_ServerName);

		var c = GetComponent<GuiEvent_CommandWindow>();
		c.Reload_PlayerCmd();


		GuiEvent_CommandWindow cmdWin = GetComponent<GuiEvent_CommandWindow>();
		cmdWin.SetWindowText(m_CMD.m_ServerName + " - " + m_CMD.m_ServerIP + ":" + m_CMD.m_ServerPort);
	}


}
