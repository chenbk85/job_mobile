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


namespace nNWM
{
	namespace nDummy
	{

		public abstract class GuiEvent_base : MonoBehaviour
		{
			protected CmdEventManager m_CMD;
			protected GuiEventManager m_GUI;
			protected jGuiStage m_jGuiStage;
			protected jGuiWindow m_jGuiWindow;

			//#--------------------------------------------------------------------------
			// public function
			//#--------------------------------------------------------------------------
			public void SetWindowText(string txt)
			{
				if (m_jGuiWindow == null) return;
				m_jGuiWindow.SetText(txt);
			}


			//#--------------------------------------------------------------------------
			// prototected
			//#--------------------------------------------------------------------------
			protected void Set_jGuiWindow(jGuiWindow win)
			{
				m_jGuiStage = win.GetStage();
				m_jGuiWindow = win;

				if (m_jGuiStage == null || m_jGuiWindow == null)
					throw new System.Exception("m_jGuiStage==null || m_jGuiWindow == null");

				m_GUI = gameObject.GetComponent<GuiEventManager>();
				m_CMD = m_GUI.m_CMD;
				if (m_CMD == null) throw new System.Exception("m_CMD==null");

			}

			void Start()
			{
			}

			// Update is called once per frame
			void Update()
			{

			}
		}//public abstract class GuiEvent_base : MonoBehaviour

	}//namespace nDummy

}//namespace nNWM
