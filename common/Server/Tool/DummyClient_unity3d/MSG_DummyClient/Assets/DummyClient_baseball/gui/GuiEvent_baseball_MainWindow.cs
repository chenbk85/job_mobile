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
	void OnLoadedGUI_MainWindow(jGuiWindow win) // "ConfigWindow2"��� jGuiWindow �ε��� �Ϸ�Ǹ� ȣ���.
	{
	}
	void OnShowModal_MainWindow(jGuiWindow win) // "ConfigWindow2"��� ��������찡 ��������.
	{

	}
	void jGuiButton_Start(jGuiButton ctrl) // "Ok"�̶�� 
	{
		//m_jGuiStage.HideModalWindow();	//��� �����츦 �����Ѵ�.
		var gui1 = (nNWM.nGui.jGuiEventManager)GetComponent("GuiEventManager");
		gui1.enabled = true;

		var gui2 = (nNWM.nGui.jGuiEventManager)GetComponent("GuiEventManager_baseball");
		gui2.enabled = false;

	}

	void jGuiButton_Exit(jGuiButton ctrl) // "Cancel"�̶�� 
	{
		Application.Quit();
	}

}


