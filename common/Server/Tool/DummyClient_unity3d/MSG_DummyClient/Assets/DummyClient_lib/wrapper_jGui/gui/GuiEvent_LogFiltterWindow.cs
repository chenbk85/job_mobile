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


public class GuiEvent_LogFiltterWindow : nNWM.nDummy.GuiEvent_base
{
	void OnLoadedGUI_LogFiltterWindow(jGuiWindow win) // "LogFiltterWindow"라는 jGuiWindow 로딩이 완료되면 호출됨.
	{
		base.Set_jGuiWindow(win);// 반드시 호출.

	}
	void OnShowModal_ConfigWindow(jGuiWindow win) // "ConfigWindow"라는 모달윈도우가 보여질때.
	{

	}
	void jGuiButton_Ok(jGuiButton ctrl) // "Ok"이라는 
	{
		m_jGuiStage.HideModalWindow();	//모달 윈도우를 종료한다.
	}

	void jGuiButton_Cancel(jGuiButton ctrl) // "Cancel"이라는 
	{
		m_jGuiStage.HideModalWindow();	//모달 윈도우를 종료한다.
	}

}
