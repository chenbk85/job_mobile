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
		public class jGuiVertical : jGuiControlGroup
		{
			public override void Load(jGuiStage stage, jGuiWindow win, jGuiControl parent, jxE g, jxE overrideAttribute)
			{
				m_isLayouted = true;// only GUILayout mode !
				base.Load(stage,  win , parent , g , overrideAttribute);
			}

			public override bool OnGUI()
			{
				if (base.IsEnabled() == false) return false;

				base.Begin_GUIStyle();

				if (m_GUIStyle == null)
					GUILayout.BeginVertical(Get_GUILayoutOption());
				else
					GUILayout.BeginVertical(m_GUIStyle, Get_GUILayoutOption());

				base.OnGUI();
				GUILayout.EndVertical();
				return true;


			}

		}//public class jGuiVertical : jGuiControl
	}//namespace nGui
}//namespace nNWM
