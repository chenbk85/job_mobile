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
		public class jGuiHorizontal : jGuiVertical
		{
			public override bool OnGUI()
			{
				if (base.IsEnabled() == false) return false;

				Begin_GUIStyle();

				if (m_GUIStyle==null)
					GUILayout.BeginHorizontal(Get_GUILayoutOption());
				else
					GUILayout.BeginHorizontal(m_GUIStyle, Get_GUILayoutOption());

				onGui_Child();
				GUILayout.EndHorizontal();
				return true;


			}

		}//public class jGuiHorizontal : jGuiControl
	}//namespace nGui
}//namespace nNWM
