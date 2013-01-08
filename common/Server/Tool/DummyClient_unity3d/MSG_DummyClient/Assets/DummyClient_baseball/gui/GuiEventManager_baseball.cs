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


public class GuiEventManager_baseball : nNWM.nGui.jGuiEventManager
{
	public CmdEventManager m_CMD;

	protected override void OnStart()
	{
		if (m_CMD == null)
		{
			Debug.LogError("m_CMD is null. set CmdEventManager gameobject to m_CMD");
			return;
		}
	}

	protected void OnLoadStageXML_baseball(nNWM.nXML.jxDocument stageXml)
	{

	}
	protected void OnLoadStageGUI_baseball(jGuiStage stage)
	{

	}

}//public class GuiEventManager_baseball

