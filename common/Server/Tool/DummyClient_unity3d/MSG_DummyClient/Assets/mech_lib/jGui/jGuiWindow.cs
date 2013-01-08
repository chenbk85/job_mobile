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
		public class jGuiWindow : jGuiControlGroup
		{
			jxV m_vDragWindow;

			//#--------------------------------------------------------------------------
			// window scale info
			//#--------------------------------------------------------------------------
			enum EScaleState
			{
				eNOT // scale못하는 상태
				,eREADY // scale 대기 상태
				,eOK // scale 중인상태
			}
			EScaleState m_EScaleState = EScaleState.eNOT;
			Rect m_rectScaleBox;
			bool m_bScaleToggle=false;
			const float fTOGGLEBOX_OFFSET = 60;
			const float fSCALE_BOX_WIDTH = 100;
			const float fSCALE_BOX_HEIGT = 30;
			Vector2 m_v2_MouseDown;

			//#--------------------------------------------------------------------------
			public override void Load(jGuiStage stage, jGuiWindow win, jGuiControl parent, jxE g, jxE overrideAttribute)
			//#--------------------------------------------------------------------------
			{
				base.Load(stage,  this , parent , g , overrideAttribute);

				m_vDragWindow = g.AttrVar("DragWindow");
				jxV v = g.AttrVar("IsScalable");
				if (v != null && v.Get_bool())
				{
					m_EScaleState = EScaleState.eREADY;
					m_rectScaleBox.x = m_Rect.x + m_Rect.width - fTOGGLEBOX_OFFSET;
					m_rectScaleBox.y = m_Rect.y + m_Rect.height ;
					m_rectScaleBox.width = fSCALE_BOX_WIDTH;
					m_rectScaleBox.height = fSCALE_BOX_HEIGT;
				}

				m_jGuiStage.CallEventHandler_jGuiWindow("OnLoadedGUI_"+GetName() , this);
			}
			void checkScaleWindow()
			{
				m_rectScaleBox.x = m_Rect.x + m_Rect.width - fTOGGLEBOX_OFFSET ;
				m_rectScaleBox.y = m_Rect.y + m_Rect.height;
				GUILayout.BeginArea(m_rectScaleBox);

				string scaleText ;
				if (m_bScaleToggle)
				{
					scaleText = string.Format("{0};{1};{2};{3}", m_Rect.x, m_Rect.y, m_Rect.width, m_Rect.height);
				}
				else
				{
					scaleText = "Scale";
				}
				m_bScaleToggle = GUILayout.Toggle(m_bScaleToggle, scaleText
								, GUILayout.Width(fSCALE_BOX_WIDTH)
								, GUILayout.Height(fSCALE_BOX_HEIGT));

				GUILayout.EndArea();

				if (Event.current.type == EventType.MouseUp)
				{
					m_EScaleState = EScaleState.eREADY;
					return;
				}
				if (Event.current.type == EventType.MouseDown 
						&& m_bScaleToggle
						 //GUILayoutUtility.GetLastRect().Contains(Event.current.mousePosition)
					)
				{
					m_EScaleState = EScaleState.eOK;
					m_v2_MouseDown = Event.current.mousePosition;
				}

				if (m_EScaleState == EScaleState.eOK)
				{
					const float fWINDOW_MIN_SIZE = 50;
					Vector2 offset = Event.current.mousePosition - m_v2_MouseDown;
					if (m_Rect.width + offset.x < fWINDOW_MIN_SIZE) offset.x = 0;
					if (m_Rect.height + offset.y < fWINDOW_MIN_SIZE) offset.y = 0;
					m_v2_MouseDown = Event.current.mousePosition;
					m_Rect = new Rect(m_Rect.x, m_Rect.y
									, m_Rect.width + offset.x
									, m_Rect.height + offset.y);
					//Debug.Log("Rect=" + m_Rect.ToString());
				}
			}

			//#--------------------------------------------------------------------------
			public override bool OnGUI()
			//#--------------------------------------------------------------------------
			{
				if (IsEnabled() == false) return false;

				new Auto_GUIStlyer(this);
				if (m_GUIStyle == null)
				{
					Debug.LogError("m_GUIStyle == null : " + m_jxE.GetTagName());
					return false;
				}

				m_Rect = GUI.Window(m_jxE.GetOrder(), GetRect(), OnGUI_jGuiWindow, GetText(), m_GUIStyle);

				if (m_EScaleState != EScaleState.eNOT)
					checkScaleWindow();

				return true;

			}

			void OnGUI_jGuiWindow(int windowID)
			{
				base.OnGUI();

				if (m_vDragWindow != null && m_vDragWindow.Get_bool() == true)
					GUI.DragWindow();
			}
		}

	}//namespace nGui
}
