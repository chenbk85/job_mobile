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
	void OnLoadedGUI_LogFiltterWindow(jGuiWindow win) // "LogFiltterWindow"��� jGuiWindow �ε��� �Ϸ�Ǹ� ȣ���.
	{
		base.Set_jGuiWindow(win);// �ݵ�� ȣ��.

	}
	void OnShowModal_ConfigWindow(jGuiWindow win) // "ConfigWindow"��� ��������찡 ��������.
	{

	}
	void jGuiButton_Ok(jGuiButton ctrl) // "Ok"�̶�� 
	{
		m_jGuiStage.HideModalWindow();	//��� �����츦 �����Ѵ�.
	}

	void jGuiButton_Cancel(jGuiButton ctrl) // "Cancel"�̶�� 
	{
		m_jGuiStage.HideModalWindow();	//��� �����츦 �����Ѵ�.
	}

}
