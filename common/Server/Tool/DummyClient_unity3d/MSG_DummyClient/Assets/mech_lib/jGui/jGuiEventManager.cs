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
	namespace nGui
	{
		public class jGuiEventManager : MonoBehaviour
		{
			public GUISkin m_GUISkin;
			public TextAsset m_XmlFile;
			protected jGuiStage m_jGuiStage;
			public string m_GuiEventPrifix = "GuiEvent_";

			void _load(string name, string xml, GUISkin skin, GameObject eventHandler, string GuiEventPrifix="GuiEvent_")
			{
				m_jGuiStage = new jGuiStage();
				m_jGuiStage.Load(name, xml, skin, eventHandler, GuiEventPrifix);
			}

			void Start()
			{
				//Debug.Log("Start jGuiEventManager = " + name);
				//LevelXMLFile = (TextAsset)Resources.LoadAssetAtPath("xml/xml_test.xml", typeof(TextAsset));
				_load(m_XmlFile.name, m_XmlFile.text, m_GUISkin, gameObject, m_GuiEventPrifix);
				if (m_jGuiStage == null)
				{
					throw new System.Exception(m_XmlFile.name + " : " + m_XmlFile.text + " load fail");
				}

				OnStart();

			}

			void OnGUI()
			{
				if (m_jGuiStage != null)
					m_jGuiStage.OnGUI();

				OnGui();
			}

			protected virtual void OnStart()
			{

			}
			protected virtual void OnGui()
			{

			}
// 			protected virtual void OnLoadStageXML_[Stage_name](nNWM.nXML.jxDocument stageXml)
// 			{
// 
// 			}
// 			protected virtual void OnLoadStageGUI_[Stage_name](jGuiStage stage)
// 			{
// 
// 			}
		}//public class jGui
	}//namespace nGui
}//namespace nNWM
