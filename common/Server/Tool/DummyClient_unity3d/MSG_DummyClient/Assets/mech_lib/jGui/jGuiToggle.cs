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
        public class jGuiToggle : jGuiControl
				{
					jxV m_ToggleValue;
					public void SetToggleValue(bool isVal) { m_ToggleValue.Set_bool(isVal); }
					public bool GetToggleValue() { return m_ToggleValue.Get_bool(); }

					public override void Load(jGuiStage stage, jGuiWindow win, jGuiControl parent, jxE g, jxE overrideAttribute)
					{
						base.Load(stage,  win , parent , g , overrideAttribute);

						m_ToggleValue = g.AttrVar("ToggleValue");
						if (m_ToggleValue == null)
						{
							throw new System.Exception("jGuiToggle : attribute b_ToggleValue is null");
						}
					}

					public override bool OnGUI()
					{
						if (base.OnGUI() == false) return false;

						Begin_GUIStyle();

						if (m_isLayouted)
						{
							bool toggle= GUILayout.Toggle(m_ToggleValue.Get_bool(), GetText(), Get_GUILayoutOption());
							m_ToggleValue.Set_bool(toggle);
						}
						else
						{
							throw new System.Exception("TODO");
						}

						End_GUIStyle();

						return true;
					}

				}//public class jGuiToggle : jGuiControl
			}//namespace nGui
	}//namespace nNWM
