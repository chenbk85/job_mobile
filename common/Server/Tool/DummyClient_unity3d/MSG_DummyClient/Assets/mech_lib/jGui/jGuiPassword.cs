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
		public class jGuiPassword : jGuiControl
		{
			jxV m_vMaxLength;
			jxV m_vMask;

			public override void Load(jGuiStage stage, jGuiWindow win, jGuiControl parent, jxE g, jxE overrideAttribute)
			{
				base.Load(stage, win, parent, g, overrideAttribute);
				m_vMask = g.AttrVar("Mask");
				if (m_vMask == null) throw new System.Exception(ToString() + " has not Mask attribute");

				m_vMaxLength = g.AttrVar("MaxLength");
				if (m_vMaxLength == null) throw new System.Exception(ToString() + " has not i_MaxLength attribute");

			}

			public override bool OnGUI()
			{
				if (base.OnGUI() == false) return false;

				Begin_GUIStyle();
				if (m_isLayouted)
				{
					m_Text = GUILayout.PasswordField(GetText(), m_vMask.Get_string()[0], m_vMaxLength.Get_int() , Get_GUILayoutOption());
				}
				else
				{
					m_Text = GUI.PasswordField(GetRect(), GetText(), m_vMask.Get_string()[0], m_vMaxLength.Get_int());
				}
				End_GUIStyle();
				return true;

			}

		}//public class jGuiPassword : jGuiControl
	}//namespace nGui
}//namespace nNWM
