using UnityEngine;
using System.Collections.Generic;


using jxD = nNWM.nXML.jxDocument; // xml doc;
using jxE = nNWM.nXML.jxElement; // xml element
using jxA = nNWM.nXML.jxVar; // element attribute
using jxV = nNWM.nXML.jxVar; // attribute or element data
using string_id_t = System.Int32;


namespace nNWM
{
	namespace nGui
	{
		public class jGuiComboBox : jGuiControl
		{
			public override void Load(jGuiStage stage, jGuiWindow win, jGuiControl parent, jxE g, jxE overrideAttribute)
			{
				m_isLayouted = parent.IsLayouted();
				base.Load(stage, win, parent, g, overrideAttribute);
			}

			public override bool OnGUI()
			{
				if (base.OnGUI() == false) return false;

				Begin_GUIStyle();


				bool isEvent = false;
				if (m_isLayouted)
				{
					if (m_GUIStyle == null)
						isEvent = GUILayout.Button(GetText(), Get_GUILayoutOption());
					else
						isEvent = GUILayout.Button(GetText(), m_GUIStyle, Get_GUILayoutOption());
				}
				else
				{
					isEvent = GUI.Button(GetRect(), GetText());

					// 					GUI.Button(new Rect(10, 10, 100, 20), new GUIContent("Click me", "1234This is the tooltip"));
					// 					GUI.Label(new Rect(10, 80, 100, 20), GUI.tooltip);

				}

				End_GUIStyle();

				if (isEvent && HasName())
				{
					m_jGuiStage.CallEventHandler(this);
				}

				return true;

			}

		}//public class jGuiComboBox : jGuiControl
	}//namespace nGui
}//namespace nNWM
