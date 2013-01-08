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
        public class jGuiScrollView : jGuiControlGroup
        {
					private Vector2 m_v2ScrollPostion = Vector2.zero;
					Rect m_ViewRect;
					bool m_isAutoScroll=false;


					public void SetEndScroll(bool val){ m_isAutoScroll=val;}

					public override void Load(jGuiStage stage, jGuiWindow win, jGuiControl parent, jxE g, jxE overrideAttribute)
					{
						///Debug.Log("load : jGuiScrollView : " + g.GetTagName());
						base.Load(stage,  win , parent , g , overrideAttribute);
						jxA  a;
						if (!m_isLayouted)
						{
							a = g.AttrVar("ViewRect");
							if (a == null) throw new System.Exception(this.ToString() + " must has ViewRect attribute");
							if (a.IsEType(nXML.EDataType.e_Rect)==false) 
								throw new System.Exception(this.ToString() + " is not e_Rect type");
							m_ViewRect = a.GetRect();
						}
					
						a = g.AttrVar("AutoScroll");
						if (a != null)
							m_isAutoScroll = a.Get_bool();
					}

					public override bool OnGUI()
					{
						if (IsEnabled() == false) return false;

						Begin_GUIStyle();
						if (m_isAutoScroll)
						{
							m_v2ScrollPostion.y = System.Int32.MaxValue;
							m_isAutoScroll = false;
						}

						if (m_isLayouted)
						{
							m_v2ScrollPostion = GUILayout.BeginScrollView(m_v2ScrollPostion, base.Get_GUILayoutOption());
							base.OnGUI();
							GUILayout.EndScrollView();
						}
						else
						{
							m_v2ScrollPostion = GUI.BeginScrollView(GetRect(), m_v2ScrollPostion, m_ViewRect);
							base.OnGUI();
							GUI.EndScrollView();
						}
						End_GUIStyle();
						return true;
					}
        }//public class jGuiScrollView : jGuiControl
    }//namespace nGui
}//namespace nNWM
