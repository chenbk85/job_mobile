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


public class GuiEvent_ConfigWindow : nNWM.nDummy.GuiEvent_base
{
	jGuiScrollView m_ConfigWindow_ScrollView;

	void OnLoadedGUI_ConfigWindow(jGuiWindow win) // "ConfigWindow"라는 jGuiWindow 로딩이 완료되면 호출됨.
	{
		base.Set_jGuiWindow(win);// 반드시 호출.

		m_ConfigWindow_ScrollView = (jGuiScrollView)m_jGuiWindow.FindCtrl("ConfigWindow_ScrollView");
		if (m_ConfigWindow_ScrollView == null) 
			Debug.LogError("ConfigWindow_ScrollView is not found");
	}
	void OnShowModal_ConfigWindow(jGuiWindow win) // "ConfigWindow"라는 모달윈도우가 보여질때.
	{
		jGuiControl c;
		if(m_CMD.m_PlayerCmdFile.Length>=4)
		{
			c = m_ConfigWindow_ScrollView.FindCtrl("Player1");
			c.SetText(m_CMD.m_PlayerCmdFile[0].USER_ID);
			c = m_ConfigWindow_ScrollView.FindCtrl("Player2");
			c.SetText(m_CMD.m_PlayerCmdFile[1].USER_ID);
			c = m_ConfigWindow_ScrollView.FindCtrl("Player3");
			c.SetText(m_CMD.m_PlayerCmdFile[2].USER_ID);
			c = m_ConfigWindow_ScrollView.FindCtrl("Player4");
			c.SetText(m_CMD.m_PlayerCmdFile[3].USER_ID);
		}
		jGuiToggle tg;
		tg = (jGuiToggle)m_ConfigWindow_ScrollView.FindCtrl("AddLogCount");
		tg.SetToggleValue(m_CMD.m_isAddLogCount);
		tg = (jGuiToggle)m_ConfigWindow_ScrollView.FindCtrl("AutoPlay");
		tg.SetToggleValue(m_CMD.m_isAutoPlay);

		c = m_ConfigWindow_ScrollView.FindCtrl("MaxLogLine");
		c.SetText(m_CMD.m_MaxLogLine.ToString());

		c = m_ConfigWindow_ScrollView.FindCtrl("Version");
		c.SetText(m_CMD.m_MSG.Version.ToString());

		c = m_ConfigWindow_ScrollView.FindCtrl("ServerListURL");
		c.SetText(m_CMD.GetLoadedServerListURL());

	}
	void jGuiButton_Ok(jGuiButton ctrl) // "Ok"이라는 
	{
		jGuiControl c;
		if (m_CMD.m_PlayerCmdFile.Length >= 4)
		{
			c = m_ConfigWindow_ScrollView.FindCtrl("Player1");
			m_CMD.m_PlayerCmdFile[0].USER_ID = c.GetText();
			c = m_ConfigWindow_ScrollView.FindCtrl("Player2");
			m_CMD.m_PlayerCmdFile[1].USER_ID = c.GetText();
			c = m_ConfigWindow_ScrollView.FindCtrl("Player3");
			m_CMD.m_PlayerCmdFile[2].USER_ID = c.GetText();
			c = m_ConfigWindow_ScrollView.FindCtrl("Player4");
			m_CMD.m_PlayerCmdFile[3].USER_ID = c.GetText();
		}
		jGuiToggle tg;
		tg = (jGuiToggle)m_ConfigWindow_ScrollView.FindCtrl("AddLogCount");
		m_CMD.m_isAddLogCount = tg.GetToggleValue();
		tg = (jGuiToggle)m_ConfigWindow_ScrollView.FindCtrl("AutoPlay");
		m_CMD.m_isAutoPlay = tg.GetToggleValue();

		c = m_ConfigWindow_ScrollView.FindCtrl("MaxLogLine");
		m_CMD.m_MaxLogLine = int.Parse(c.GetText());
		c = m_ConfigWindow_ScrollView.FindCtrl("Version");
		m_CMD.m_MSG.Version = int.Parse(c.GetText()) ;


		//c = m_ConfigWindow_ScrollView.FindCtrl("ServerListURL");
		//m_CMD.GetLoadedServerListURL() = c.GetText();


		m_jGuiStage.HideModalWindow();	//모달 윈도우를 종료한다.
	}

	void jGuiButton_Cancel(jGuiButton ctrl) // "Cancel"이라는 버튼
	{
		m_jGuiStage.HideModalWindow();	//모달 윈도우를 종료한다.
	}

}
