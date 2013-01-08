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
		public class jGuiTextArea : jGuiControl
		{
			int m_iMaxLength = -1;
			bool m_bReadOnly=false;
			public override void Load(jGuiStage stage, jGuiWindow win, jGuiControl parent, jxE g, jxE overrideAttribute)
			{
				base.Load(stage,  win , parent , g , overrideAttribute);

				jxV v = g.AttrVar("MaxLength");
				if (v != null)
					m_iMaxLength = v.Get_int();

				if (m_Text == null) throw new System.Exception(g.GetTagName() + "' Text is not found ");

				v = g.AttrVar("ReadOnly");
				if (v != null)
					m_bReadOnly = v.Get_bool();
			}

			public override bool OnGUI()
			{
				if (base.OnGUI() == false) return false;

				Begin_GUIStyle();

				if (m_isLayouted)
				{
					if (m_bReadOnly)
					{
						GUILayout.TextArea(GetText(), 100, Get_GUILayoutOption());
					}
					else
					{
						m_Text = GUILayout.TextArea(GetText(), 100, Get_GUILayoutOption());
					}
				}
				else
				{
					if (m_bReadOnly)
					{
						GUI.TextArea(GetRect(), GetText(), m_iMaxLength);
					}
					else
					{
						m_Text = GUI.TextArea(GetRect(), GetText(), m_iMaxLength);
					}
				}

				End_GUIStyle();

				return true;
			}

		}//public class jGuiTextArea : jGuiControl
	}//namespace nGui
}//namespace nNWM


