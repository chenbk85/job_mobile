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
        public class jGuiRepeatButton : jGuiControl
        {
            public override void Load(jGuiStage stage, jGuiWindow win, jGuiControl parent, jxE g, jxE overrideAttribute)
            {
                base.Load(stage,  win , parent , g , overrideAttribute);
            }

            public override bool OnGUI()
            {
							if (base.OnGUI() == false) return false;

							Begin_GUIStyle();

							if (m_isLayouted)
							{
								if (GUILayout.RepeatButton(GetText(), Get_GUILayoutOption()))
								{

								}
							}
							else
							{
								if (GUI.RepeatButton(GetRect(), GetText()))
								{
									//jTODO event call

								}
							}
							
							End_GUIStyle();

							return true;

            }

        }//public class jGuiRepeatButton : jGuiControl
    }//namespace nGui
}//namespace nNWM
