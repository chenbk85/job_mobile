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


public class GuiEvent_LogWindow : nNWM.nDummy.GuiEvent_base
{
	jGuiLabel m_lbl_LogLabel;
	jGuiButton m_btn_ClearLog;



	//#--------------------------------------------------------------------------
	// public member function
	//#--------------------------------------------------------------------------
	public void OnLoadedGUI_LogWindow(jGuiWindow win)// "LogWindow"라는 jGuiWindow 로딩이 완료되면 호출됨.
	{
		base.Set_jGuiWindow(win);

		m_lbl_LogLabel = (jGuiLabel)m_jGuiWindow.FindCtrl("LogLabel");
		if (m_lbl_LogLabel == null) throw new System.Exception("LogLabel not found");
		m_btn_ClearLog = (jGuiButton)m_jGuiWindow.FindCtrl("ClearLog");
		if (m_btn_ClearLog == null) throw new System.Exception("ClearLog not found");


		jGuiToolbar gui_LogFilter = (jGuiToolbar)m_jGuiWindow.FindCtrl("LogFilter");
		if (gui_LogFilter == null) throw new System.Exception("LogFilter not found");


		nNWM.nDummy.jFilteredLog.m_MaxLogLine = m_CMD.m_MaxLogLine;
		m_jFilteredLog.Init(gui_LogFilter.m_jxE);
		changeLogFilter(gui_LogFilter);

	}
	public void Log(string strLog)
	{
		List<string> logList = m_jFilteredLog.AddLog(strLog);
		if (logList == null) return;

		refreshLog(logList);
	}

	//#--------------------------------------------------------------------------
	// private member function
	//#--------------------------------------------------------------------------
	nNWM.nDummy.jFilteredLog m_jFilteredLog = new nNWM.nDummy.jFilteredLog();

	void refreshLog(List<string> logList)
	{
		string logs = "";
		foreach (var log in logList)
		{
			logs += log;
			logs += "\n";
		}
		m_lbl_LogLabel.SetText(logs);
		jGuiScrollView sv = (jGuiScrollView)m_lbl_LogLabel.GetParent();
		sv.SetEndScroll(true);
	}
	void changeLogFilter(jGuiToolbar ctrl)
	{
		List<string> logList = m_jFilteredLog.ChangeLogFilter(ctrl.GetToolBarIndex());
		if (logList == null) return;
		refreshLog(logList);

		jxE eChild = ctrl.m_jxE.GetChild(ctrl.GetToolBarIndex());
		m_btn_ClearLog.SetText("Clear (" + eChild.Get_string() + ")");
	}


	//#--------------------------------------------------------------------------
	// jGui Event Handler
	//#--------------------------------------------------------------------------
	void jGuiButton_ClearLog(jGuiButton ctrl)
	{
		m_jFilteredLog.ClearLog();
		m_lbl_LogLabel.SetText("");
	}
	void jGuiToolbar_LogFilter(jGuiToolbar ctrl)
	{
		changeLogFilter(ctrl);
	}

}
