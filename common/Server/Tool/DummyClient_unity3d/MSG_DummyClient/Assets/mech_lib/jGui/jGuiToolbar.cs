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
		public class jGuiToolbar : jGuiControl
		{
			int m_indexToolbar = 0;
			string[] m_listText;

			public int GetToolBarIndex() { return m_indexToolbar; }
			public void SetToolBarIndex(int idx) { m_indexToolbar = idx; }

			public override void Load(jGuiStage stage, jGuiWindow win, jGuiControl parent, jxE g, jxE overrideAttribute)
			{
				base.Load(stage,  win , parent , g , overrideAttribute);
				m_listText = new string[g.size()];
				int i = 0;
				foreach (jxE e in g)
				{
					m_listText[i++] = e.Get_string();
				}
			}

			public override bool OnGUI()
			{
				if (base.OnGUI() == false) return false;
				Begin_GUIStyle();

				int indexToolbar = m_indexToolbar;
				if (m_isLayouted)
				{
					m_indexToolbar = GUILayout.Toolbar(m_indexToolbar, m_listText ,Get_GUILayoutOption());
				}
				else
				{
					m_indexToolbar = GUI.Toolbar(GetRect(), m_indexToolbar, m_listText);
				}
				End_GUIStyle();
				if (indexToolbar != m_indexToolbar && HasName())
				{
					m_jGuiStage.CallEventHandler(this);
				}
				return true;

			}
			public void UpdateList()
			{
				m_listText = new string[m_jxE.size()];
				int i = 0;
				foreach (jxE e in m_jxE)
				{
					jxV v = e.AttrVar("Enable");
					if(v!=null && v.Get_bool()==false)
						continue;
					m_listText[i++] = e.Get_string();
				}
			}

		}//public class jGuiToolbar : jGuiControl
	}//namespace nGui
}//namespace nNWM
