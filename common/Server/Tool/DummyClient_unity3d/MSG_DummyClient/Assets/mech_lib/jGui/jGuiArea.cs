
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
		public class jGuiArea : jGuiControlGroup
		{
			public override void Load(jGuiStage stage, jGuiWindow win, jGuiControl parent, jxE g, jxE overrideAttribute)
			{
				m_isLayouted = true;// only GUILayout mode !
				base.Load(stage,  win , parent , g , overrideAttribute);

				if(g.AttrVar("Rect")==null) 
					throw new System.Exception(g.GetTagName() + " : need r_Rect=...");


			}
			public override bool OnGUI()
			{
				if (base.IsEnabled() == false) return false;

				Begin_GUIStyle();

				if(m_GUIStyle==null)
					GUILayout.BeginArea(GetRect());
				else
					GUILayout.BeginArea(GetRect(), m_GUIStyle);

				onGui_Child();
				GUILayout.EndArea();
				return true;
			}

		}//public class jGuiArea : jGuiControl
	}//namespace nGui
}//namespace nNWM
