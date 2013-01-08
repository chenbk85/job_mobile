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
		public class jGuiGrid : jGuiControl
		{
			//#--------------------------------------------------------------------------
			// public member 
			//#--------------------------------------------------------------------------

			//#--------------------------------------------------------------------------
			// protected member 
			//#--------------------------------------------------------------------------

			//#--------------------------------------------------------------------------
			// private member 
			//#--------------------------------------------------------------------------
			int m_iCurrGrid = 0;
			string[] m_listGridString;
			jxV m_vColumn;

			//#--------------------------------------------------------------------------
			// public member function
			//#--------------------------------------------------------------------------
			void ReloadGridString()
			{
				m_listGridString = new string[m_jxE.size()];
				foreach (jxE e in m_jxE)
				{
					m_listGridString[e.GetOrder()] = e.Get_string();
				}
			}

			//#--------------------------------------------------------------------------
			// protectec member function
			//#--------------------------------------------------------------------------

			//#--------------------------------------------------------------------------
			// private member function
			//#--------------------------------------------------------------------------


			//#--------------------------------------------------------------------------
			// jGuiControl Event function
			//#--------------------------------------------------------------------------
			public override void Load(jGuiStage stage, jGuiWindow win, jGuiControl parent, jxE g, jxE overrideAttribute)
			{
				base.Load(stage, win, parent, g, overrideAttribute);

				m_vColumn = g.AttrVar("Column");
				if (m_vColumn == null) throw new System.Exception(ToString() + " has not i_Column attribute");
				ReloadGridString();
			}

			public override bool OnGUI()
			{
				if (base.OnGUI() == false) return false;

				Begin_GUIStyle();
				int saveIndex = m_iCurrGrid;
				if (m_isLayouted)
				{
					m_iCurrGrid = GUILayout.SelectionGrid(m_iCurrGrid, m_listGridString, m_vColumn.Get_int(), Get_GUILayoutOption());
				}
				else
				{
					m_iCurrGrid = GUI.SelectionGrid(GetRect(), m_iCurrGrid, m_listGridString, m_vColumn.Get_int());
				}
				End_GUIStyle();

				if (saveIndex != m_iCurrGrid && HasName())
				{
					m_jGuiStage.CallEventHandler(this);
				}

				return true;
			}

		}//public class jGuiGrid : jGuiControl
	}//namespace nGui
}//namespace nNWM
