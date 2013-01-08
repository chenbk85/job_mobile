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


public class GuiEvent_baseball_MainWindow : nNWM.nDummy.GuiEvent_base
{
	void OnLoadedGUI_MainWindow(jGuiWindow win) // "ConfigWindow2"라는 jGuiWindow 로딩이 완료되면 호출됨.
	{
	}
	void OnShowModal_MainWindow(jGuiWindow win) // "ConfigWindow2"라는 모달윈도우가 보여질때.
	{

	}
	void jGuiButton_Start(jGuiButton ctrl) // "Ok"이라는 
	{
		//m_jGuiStage.HideModalWindow();	//모달 윈도우를 종료한다.
		var gui1 = (nNWM.nGui.jGuiEventManager)GetComponent("GuiEventManager");
		gui1.enabled = true;

		var gui2 = (nNWM.nGui.jGuiEventManager)GetComponent("GuiEventManager_baseball");
		gui2.enabled = false;

	}

	void jGuiButton_Exit(jGuiButton ctrl) // "Cancel"이라는 
	{
		Application.Quit();
	}

}


