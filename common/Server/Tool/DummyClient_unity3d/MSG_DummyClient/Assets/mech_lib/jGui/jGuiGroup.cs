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
        public class jGuiGroup : jGuiControlGroup
        {
            public override void Load(jGuiStage stage, jGuiWindow win, jGuiControl parent, jxE g, jxE overrideAttribute)
            {
                ///Debug.Log("load : jGuiGroup : " + g.GetTagName());

                base.Load(stage,  win , parent , g , overrideAttribute);
            }

            public override bool OnGUI()
            {
                if (IsEnabled() == false) return false;
								// GUILayoutÀÌ ¾ø´Ù.
                GUI.BeginGroup(GetRect());

                base.OnGUI();

                GUI.EndGroup();
                return true;

            }

        }//public class jGuiGroup : jGuiControl
    }//namespace nGui
}//namespace nNWM
