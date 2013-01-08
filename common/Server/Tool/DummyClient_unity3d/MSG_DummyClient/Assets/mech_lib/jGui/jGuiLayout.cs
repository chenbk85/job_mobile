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
		public class jGuiLayout : jGuiControlGroup
		{
			public override void Load(jGuiStage stage, jGuiWindow win, jGuiControl parent, jxE g, jxE overrideAttribute)
			{
				m_isLayouted = true;
				base.loadDefaultParam(stage, win, parent, g , overrideAttribute);

				base.loadChild(stage, parent, g );
			}

			public override bool OnGUI()
			{
				if (IsEnabled() == false) return false;
				return base.OnGUI();
			}

		}//public class jGuiLayout : jGuiControl
	}//namespace nGui
}//namespace nNWM
