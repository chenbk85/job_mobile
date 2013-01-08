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
      // group type gui control
			public class jGuiControlGroup : jGuiControl
			{
				override public jGuiControl FindCtrl(string name)
				{
					jxA findA;
					jxE e = m_jxE.FindByAttr("Name", name, out findA);
					if (e == null)
					{
						Debug.Log("jGuiControl FindCtrl : " + name + " is not found");
						return null;
					}
					jGuiControl ctrl = (jGuiControl)e.m_UserData;
					return ctrl;
				}

				protected void loadChild(jGuiStage stage, jGuiControl parent, jxE g)
				{
					jGuiControl ctrl;
					foreach (jxE e in m_jxE)
					{
						ctrl = m_jGuiStage.CreateRTTI(e);
						if (ctrl == null) continue;
						ctrl.m_isLayouted = this.m_isLayouted;

						ctrl.Load(stage, this.m_jGuiWindow, this, e, this.m_OverrideAttribute);
					}
				}

				protected void onGui_Child()
				{
					jGuiControl ctrl;
					foreach (jxE e in this.m_jxE)
					{
						ctrl = (jGuiControl)e.m_UserData;
						if (ctrl == null) continue;
						ctrl.OnGUI(); ;
					}
				}

				public override void Load(jGuiStage stage, jGuiWindow win, jGuiControl parent, jxE g, jxE overrideAttribute)
				{
					///Debug.Log("load : jGuiControlGroup : " + g.GetTagName());
					base.Load(stage,  win , parent , g , overrideAttribute);
					loadChild(stage, parent, g );

				}

				public override bool OnGUI()
				{
					//if (base.OnGUI() == false) return false;

					onGui_Child();

					return true;
				}

			}//public class jGuiControlGroup : jGuiControl
		}//namespace nGui
	}//namespace nNWM
