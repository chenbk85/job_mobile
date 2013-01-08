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
        public class jGuiTextField : jGuiControl
        {
          public override bool OnGUI()
          {
						if (base.OnGUI() == false) return false;

						Begin_GUIStyle();

						if (m_isLayouted)
						{
							m_Text = GUILayout.TextField(GetText(), Get_GUILayoutOption());
						}
						else
						{
							m_Text = GUI.TextField(GetRect(), GetText());
						}
						End_GUIStyle();

						return true;

          }

        }//public class jGuiTextField : jGuiControl
    }//namespace nGui
}//namespace nNWM
