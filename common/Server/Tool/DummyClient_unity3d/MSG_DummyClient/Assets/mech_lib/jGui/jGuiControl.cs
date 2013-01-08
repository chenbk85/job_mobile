using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using jxD = nNWM.nXML.jxDocument; // xml doc;
using jxE = nNWM.nXML.jxElement; // xml element
using jxA = nNWM.nXML.jxVar; // element attribute
using jxV = nNWM.nXML.jxVar; // attribute or element data
using string_id_t = System.Int32;


namespace nNWM
{
	namespace nGui
	{
		public class jGuiControl
		{
			protected string m_Name;
			protected string m_Text;

			protected jxV m_Enable;
			protected jGuiStage m_jGuiStage;
			protected jGuiControl m_jGuiParent; // 자신의 바로 상위객체.
			protected jGuiWindow m_jGuiWindow;//자신의 부모 윈도우객체

			protected Rect m_Rect;
			protected jxE m_OverrideAttribute;

			public jxE m_jxE;

			public bool m_isLayouted = false;
			public jGUILayoutOption m_jLayoutParam;

			protected class Auto_GUIStlyer
			{
				jGuiControl m_ctrl;
				public Auto_GUIStlyer(jGuiControl ctrl) { m_ctrl = ctrl; ctrl.Begin_GUIStyle(); }
				~Auto_GUIStlyer() { m_ctrl.End_GUIStyle(); }
			}


			//#--------------------------------------------------------------------------
			// member function
			//#--------------------------------------------------------------------------
			public jxV AttrVarOverride(string attribute_name)
			{
				jxA v = m_jxE.AttrVar(attribute_name);
				if (v != null || m_OverrideAttribute==null) return v;

				jxE e = m_OverrideAttribute.Find(m_jxE.GetTagID(), 1);
				if (e == null) return null;
				//Debug.Log(e.GetTagName() + " : OverrideAttribute : " + attribute_name);
				return e.AttrVar(attribute_name);
			}
			public string AttrOverride(string attribute_name)
			{
				jxA v = AttrVarOverride(attribute_name);
				if (v == null) return null;
				if (!v.IsEType(nXML.EDataType.e_string))
				{
					string sError = m_jxE.GetTagName() + "'s attribute<" + attribute_name + "> is not e_string : " + v.GetEType().ToString();
					throw new System.Exception(sError);
				}
				return v.Get_string();
			}

			//#--------------------------------------------------------------------------
			// public member function
			//#--------------------------------------------------------------------------
			public jGuiWindow GetWindow() { return m_jGuiWindow; }
			public jGuiStage GetStage() { return m_jGuiStage; }
			public jxE Get_OverrideAttribute() { return m_OverrideAttribute; }
			public void SetDefaultStyleName(string s) { m_GUIStyle_DefaultName = s; }
			public GUILayoutOption[] Get_GUILayoutOption()
			{
				if (m_jLayoutParam == null) return null;
				return m_jLayoutParam.GetOptions();
			}
			public Rect GetRect() { return m_Rect; }
			public void SetRect(Rect r) { m_Rect = r; }
			public Rect GetXmlRect() { return m_jGuiStage.GetGuiRect(m_jxE);}
			public bool IsEnabled() { return (m_Enable == null) || m_Enable.Get_bool(); }
			public void SetEnabled(bool isEnable) { if (m_Enable!=null) m_Enable.Set_bool(isEnable); }
			public string GetName() { return m_Name; }
			public bool HasName() { return m_Name != null && m_Name.Length != 0; }
			public string GetText() { if (m_Text == null) return ""; return m_Text; }
			public void SetText(string txt) { m_Text = txt; }
			public bool IsLayouted() { return m_isLayouted; }
			public override string ToString() { return m_jxE.GetTagName() + ":" + GetName(); }
			public jGuiControl GetParent() 
			{
				jxE e = m_jxE.GetParent();
				if (e == null) return null;
				return (jGuiControl)e.m_UserData;
			}
			public jGuiControl GetNext()
			{
				jxE e = m_jxE.GetNext();
				if (e == null) return null;
				return (jGuiControl)e.m_UserData;
			}
			public jGuiControl GetPrev()
			{
				jxE e = m_jxE.GetPrev();
				if (e == null) return null;
				return (jGuiControl)e.m_UserData;
			}


			protected void loadDefaultParam(jGuiStage stage, jGuiWindow win,jGuiControl parent, jxE g, jxE overrideAttribute)
			{
				m_OverrideAttribute = g.Find("OverrideAttribute", 1);
				if (m_OverrideAttribute == null)
					m_OverrideAttribute = overrideAttribute;

				m_TextAnchor.t1= false;
				m_jxE = g;
				m_jGuiStage = stage;
				m_jGuiParent = parent;
				m_Enable = m_jxE.AttrVar("Enable");
				m_Text = AttrOverride("Text");
				m_Name = m_jxE.Attr("Name");
				if (m_Text == null)
				{
					m_Text = m_Name;
				}

				load_GUIStyle();
			}

			virtual public jGuiControl FindCtrl(string name)
			{
				return null;// default gui control has not child;
			}

			virtual public void Load(jGuiStage stage, jGuiWindow win,jGuiControl parent, jxE g, jxE overrideAttribute)
			{
				//////Debug.Log("load : jGuiControl : " + g.GetTagName());
				loadDefaultParam(stage, win, parent,  g , overrideAttribute);

				if (m_isLayouted == false)
				{
					m_Rect = stage.GetGuiRect(m_jxE);
				}
				else
				{
					m_jLayoutParam = new jGUILayoutOption(m_jxE,this);
				}
			}
			virtual public bool OnGUI()
			{
				if (IsEnabled() == false) return false;
				return true;
			}


			//#--------------------------------------------------------------------------
			// GUIStyle
			//#--------------------------------------------------------------------------
			protected GUIStyle m_GUIStyle;
			protected string m_GUIStyle_Name;
			protected string m_GUIStyle_DefaultName;
			protected tuple<bool, TextAnchor, TextAnchor> m_TextAnchor; // <isEnable , new value , saved value >
			protected tuple<bool, int, int> m_FontSize; // <isEnable , new value , saved value >
			protected tuple<bool, FontStyle, FontStyle> m_FontStyle; // <isEnable , new value , saved value >


			void load_GUIStyle()
			{
				m_GUIStyle_Name = AttrOverride("GUIStyle");

				bool isSetName = false;

				string s = AttrOverride("TextAnchor");
				if (s != null)
				{
					isSetName = true;
					m_TextAnchor.t1 = true;
					m_TextAnchor.t2 = (TextAnchor)System.Enum.Parse(typeof(TextAnchor), s);
				}
				s = AttrOverride("FontStyle");
				if (s != null)
				{
					isSetName = true;
					m_FontStyle.t1 = true;
					m_FontStyle.t2 = (FontStyle)System.Enum.Parse(typeof(FontStyle), s);
				}


				jxV v;

				v = AttrVarOverride("FontSize");
				if (v != null)
				{
					isSetName = true;
					m_FontSize.t1 = true;
					m_FontSize.t2 = v.Get_int();
				}


				if (isSetName && m_GUIStyle_Name == null)
				{
					m_GUIStyle_Name = m_GUIStyle_DefaultName;
					if (m_GUIStyle_Name.Length == 0)
					{
						throw new System.Exception(m_jxE.GetTagName() + " : m_GUIStyle_DefaultName.Length == 0");
					}
				}
			}

			protected void Begin_GUIStyle()
			{
				if (m_GUIStyle_Name!=null && m_GUIStyle == null)
					m_GUIStyle = GUI.skin.GetStyle(m_GUIStyle_Name);

				if (m_TextAnchor.t1==true)
				{
					m_TextAnchor.t3 = m_GUIStyle.alignment;
					m_GUIStyle.alignment = m_TextAnchor.t2;
				}
				if (m_FontSize.t1==true)
				{
					m_FontSize.t3 = m_GUIStyle.fontSize;
					m_GUIStyle.fontSize = m_FontSize.t2;
				}
				if (m_FontStyle.t1 == true)
				{
					m_FontStyle.t3 = m_GUIStyle.fontStyle;
					m_GUIStyle.fontStyle = m_FontStyle.t2;
				}



			}

			protected void End_GUIStyle()
			{
				if (m_TextAnchor.t1) m_GUIStyle.alignment = m_TextAnchor.t3;
				if (m_FontSize.t1) m_GUIStyle.fontSize = m_FontSize.t3;
				if (m_FontStyle.t1) m_GUIStyle.fontStyle = m_FontStyle.t3;
			}


			public IEnumerator GetEnumerator()
			{
				for (jxE e = m_jxE.GetChild(); e != null; e = e.GetNext())
				{
					
					if(e.m_UserData==null) 
						continue;
					yield return (jGuiControl)e.m_UserData;
				}
			}
		}//public class jGuiControl


	}//namespace nGui
}// namespace nNWM
