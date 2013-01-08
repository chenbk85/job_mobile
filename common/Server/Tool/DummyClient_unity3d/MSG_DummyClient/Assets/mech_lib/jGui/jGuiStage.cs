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
		public class jGuiStage
		{
			public GUISkin m_GUISkin;
			public nNWM.nXML.jxDocument m_Doc;
			
			string m_GuiEventPrifix = "GuiEvent_";
			GameObject m_EventHandler;
			private jxE m_eGuiHeader;
			private jxE m_eNamedRect;
			private jxE m_ejGuiList;
			

			//#--------------------------------------------------------------------------
			// modal window
			//#--------------------------------------------------------------------------
			private jxE m_eModal_Window;
			private List<jGuiControl> m_ModalWindowList = new List<jGuiControl>();
			private List<jGuiControl> m_BackupEnableWindowStatus = new List<jGuiControl> ();



			static jGuiControl get_rtti_control(string default_style_name, jGuiControl ctrl,jxE e)
			{
				ctrl.SetDefaultStyleName(default_style_name);
				e.m_UserData = ctrl;
				return ctrl;
			}

			public jGuiControl CreateRTTI(jxE e)
			{
				string rtti = e.GetTagName();
				if (!rtti.Contains("jGui"))
					return null;
				if (rtti == "jGuiWindow") return get_rtti_control("window", new jGuiWindow(),e);
				if (rtti == "jGuiGroup") return get_rtti_control(null, new jGuiGroup(),e);
				if (rtti == "jGuiBox") return get_rtti_control("box", new jGuiBox(),e);
				if (rtti == "jGuiVertical") return get_rtti_control(null, new jGuiVertical(),e);
				if (rtti == "jGuiHorizontal") return get_rtti_control(null, new jGuiHorizontal(),e);
				if (rtti == "jGuiScrollView") return get_rtti_control("scrollview", new jGuiScrollView(),e);

				if (rtti == "jGuiButton") return get_rtti_control("button", new jGuiButton(),e);
				if (rtti == "jGuiRepeatButton") return get_rtti_control("button", new jGuiRepeatButton(),e);

				if (rtti == "jGuiToolbar") return get_rtti_control("button", new jGuiToolbar(),e);
				if (rtti == "jGuiGrid") return get_rtti_control("button", new jGuiGrid(),e); //SelectionGrid  다수의 행의Toolbar 
				if (rtti == "jGuiToggle") return get_rtti_control("toggle", new jGuiToggle(),e);

				//Slider과 비슷하나 브라우저나 워드를 위한 스크롤링. ScrollView 컨트롤을 조종
				if (rtti == "jGuiScrollbarH") return get_rtti_control("horizontalscrollbar", new jGuiScrollbarH(),e);
				if (rtti == "jGuiScrollbarV") return get_rtti_control("verticalscrollbar", new jGuiScrollbarV(),e);

				//HorizontalSlider  미리 결정된 최소와 최대 값 사이의 값을 변화
				if (rtti == "jGuiSliderH") return get_rtti_control("horizontalscrollbar", new jGuiSliderH(),e);
				if (rtti == "jGuiSliderV") return get_rtti_control("verticalscrollbar", new jGuiSliderV(),e);

				if (rtti == "jGuiLabel") return get_rtti_control("label", new jGuiLabel(),e);
				if (rtti == "jGuiPassword") return get_rtti_control("textfield", new jGuiPassword(),e);
				if (rtti == "jGuiTextField") return get_rtti_control("textfield", new jGuiTextField(),e);
				if (rtti == "jGuiTextArea") return get_rtti_control("textarea", new jGuiTextArea(),e);
				if (rtti == "jGuiLayout") return get_rtti_control(null, new jGuiLayout(),e);
				if (rtti == "jGuiArea") return get_rtti_control("textarea", new jGuiArea(),e);

				throw new System.Exception("Gui==null : " + e.GetTagName() + " : Not found in jGuiStage.CreateRTTI()");
			}

			public void Load(string name, string xml, GUISkin skin,GameObject eventHandler,string GuiEventPrifix="GuiEvent_")
			{
				m_GuiEventPrifix = GuiEventPrifix;
				if (eventHandler == null)
				{
					throw new System.Exception(xml + " : eventHandler == null. set EventHandler GameObject!");
				}
				m_EventHandler = eventHandler;
				string xml_url = " name = " + name + "xml=" + xml;
				m_GUISkin = skin;
				m_Doc = nXML.jxDocument.Load(name, xml);
				if (m_Doc == null)
					throw new System.Exception(xml_url);

// 				string outString = "";
// 				m_Doc.m_Root.WriteToString(ref outString);
// 				Debug.Log(outString);

				m_eGuiHeader = m_Doc.m_Root.Find("GuiHeader");
				if (m_eGuiHeader != null)
					m_eNamedRect = m_eGuiHeader.Find("NamedRect");

				m_ejGuiList = m_Doc.m_Root.Find("jGui_List");
				if (m_ejGuiList == null)
					throw new System.Exception("xml : jGui_List is not found : " + xml_url);

				m_eModal_Window = m_Doc.m_Root.Find("Modal_Window",1);

				string stageName = m_Doc.m_Root.Attr("Name");
				m_EventHandler.SendMessage("OnLoadStageXML_" + stageName, m_Doc);

				jGuiControl ctrl;

				jxE overrideAttr = m_ejGuiList.Find("OverrideAttribute", 1);
				foreach (jxE e in m_ejGuiList)
				{
					//Debug.Log (" load ; " + e.GetTagName());
					ctrl = CreateRTTI(e);
					if (ctrl == null) continue;
					ctrl.Load(this, null, null, e, overrideAttr);
				}

				if(m_eModal_Window!=null)
				{
					overrideAttr = m_eModal_Window.Find("OverrideAttribute", 1);
					foreach (jxE e in m_eModal_Window)
					{
						ctrl = CreateRTTI(e);
						if (ctrl == null) continue;
						ctrl.Load(this, null, null, e, overrideAttr);
					}
				}

				m_EventHandler.SendMessage("OnLoadStageGUI_" + stageName , this);

			}

			public Rect GetGuiRect(jxE g)
			{
				jxV vRect = g.AttrVar("Rect");
				if (vRect == null)
				{
					vRect = g.AttrVar("Name");
				}
				if (vRect == null)
				{

					//jDebug.jWARN(" attribute not found Rect : " + g.GetTagName());
					return new Rect(0, 0, 0, 0);
				}

				if (vRect.GetEType() == nXML.EDataType.e_Rect)
					return vRect.GetRect();

				if (vRect.GetEType() != nXML.EDataType.e_string)
				{
					throw new System.Exception("xml : vRect.GetEType() != nXML.EDataType.e_string : " + m_Doc.m_name);

				}

				jxE eRect = m_eNamedRect.Find(vRect.Get_string());
				if (eRect == null)
				{
					throw new System.Exception(m_Doc.m_name + "  eRect==null");
				}

				return eRect.GetRect();
			}

			public void OnGUI()
			{
				GUI.skin = m_GUISkin;

				if( m_ModalWindowList.Count>0)
				{
					var mw = m_ModalWindowList[m_ModalWindowList.Count-1];
					mw.OnGUI();
					return;
				}

				foreach (jxE e in m_ejGuiList)
				{
					jGuiControl w = (jGuiControl)e.m_UserData;
					if (w == null) continue;
					if (w.IsEnabled())
						w.OnGUI();
				}

			}

			public void CallEventHandler_jGuiWindow(string sEventType, jGuiWindow win)
			{
				string eventHandler = m_GuiEventPrifix + win.GetName();

				Component c = m_EventHandler.GetComponent(eventHandler);
				if(c==null) 
				{
					Debug.LogWarning("Component:" + eventHandler + " is not found");
					return;
				}
				//Debug.Log("CallEventHandler_jGuiWindow : " + eventHandler + "." + sEventType + " is called");
				//Debug.Log("Component name = " + c.ToString());

				c.SendMessage(sEventType,win,SendMessageOptions.RequireReceiver);

			}
			public void CallEventHandler(jGuiControl ctrl, string sEventType="")
			{
				if (ctrl == null || !ctrl.HasName())
				{
					return;
				}
				if(sEventType.Length==0)
				{
					sEventType = ctrl.m_jxE.GetTagName();
				}
				else
				{
					sEventType = ctrl.m_jxE.GetTagName() + "_" + sEventType;
				}

				string sEventName = sEventType + "_" + ctrl.GetName();
				m_EventHandler.SendMessage(sEventName, ctrl, SendMessageOptions.DontRequireReceiver);
			}

			public jGuiControl FindCtrl(string name)
			{
				jxA findA;
				jxE e = m_ejGuiList.FindByAttr("Name", name, out findA);
				if (e == null) return null;
				jGuiControl ctrl = (jGuiControl)e.m_UserData;
				return ctrl;
			}

			public void HideModalWindow()// 현제 활성화된 모달 대화상자를 닫는다.
			{
				if(m_ModalWindowList.Count<=0) return;
				m_ModalWindowList.RemoveAt(m_ModalWindowList.Count-1);
				if(m_ModalWindowList.Count>0) return;

				foreach(var v in m_BackupEnableWindowStatus)
				{
					v.SetEnabled(true);
				}
			}
			public void ShowModalWindow(string windowName) //gui xml에서 <Modal_Window>의 자식항목중에 해당 이름의 윈도우를 뛰운다.
			{
				if(m_eModal_Window==null)
				{
					Debug.LogWarning("gui xml file has not Modal_Window node");
					return;
				}

				jxA findA;
				jxE e = m_eModal_Window.FindByAttr("Name", windowName, out findA);
				if (e == null) 
				{
					Debug.LogWarning("Modal_Window is not found : " + windowName);
					return;
				}
				var modal = (jGuiWindow)e.m_UserData;
				if(modal==null)
				{
					Debug.LogWarning("Modal_Window jGuiControl==null : " + windowName);
					return;
				}

				foreach (jxE eCtrl in m_ejGuiList)
				{
					jGuiControl w = (jGuiControl)eCtrl.m_UserData;
					if (w == null) continue;
					if (w.IsEnabled())
					{
						m_BackupEnableWindowStatus.Add(w);
						w.SetEnabled(false);
					}
				}

				Rect rect = modal.GetXmlRect();
				rect.x = (Screen.width - rect.width)/2;
				rect.y = (Screen.height - rect.height)/2;
				modal.SetRect(rect);

				CallEventHandler_jGuiWindow("OnShowModal_" + modal.GetName() , modal );

				m_ModalWindowList.Add(modal);
			}

		}// public class jGuiStage

	}//namespace nGui
}

