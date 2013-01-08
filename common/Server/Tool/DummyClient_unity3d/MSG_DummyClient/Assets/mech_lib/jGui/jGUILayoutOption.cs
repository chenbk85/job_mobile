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
		using dictionary_option_t = List<GUILayoutOption>;
		public class jGUILayoutOption
		{
			GUILayoutOption[] m_GUILayoutOption;

			void set_Width(float f , dictionary_option_t dic_o)
			{
				if (f == 0) return;
				if (f == -1)
					dic_o.Add(GUILayout.ExpandWidth(true));
				else
					dic_o.Add(GUILayout.Width(f));
			}
			void set_Height(float f, dictionary_option_t dic_o)
			{
				if (f == 0) return;
				if (f == -1)
					dic_o.Add(GUILayout.ExpandHeight(true));
				else
					dic_o.Add(GUILayout.Height(f));
			}
			void set_MinMaxW(float fMin, float fMax, dictionary_option_t dic_o)
			{
				if (fMax > 0)
					dic_o.Add(GUILayout.MaxWidth(fMax));

				if (fMin > 0)
					dic_o.Add(GUILayout.MinWidth(fMin));
			}
			void set_MinMaxH(float fMin, float fMax, dictionary_option_t dic_o)
			{
				if (fMax > 0)
					dic_o.Add(GUILayout.MaxHeight(fMax));

				if (fMin > 0)
					dic_o.Add(GUILayout.MinHeight(fMin));
			}

			public jGUILayoutOption(jxE g,jGuiControl c)
			{
				dictionary_option_t dic_o = new dictionary_option_t();

				jxA a;

				a = c.AttrVarOverride("WH");
				if (a != null)
				{
					jDebug.jASSERT(a.IsEType(nXML.EDataType.e_float_array), g.GetTagName() + " WH type is not e_float_array");

					set_Width(a.Get_float(0), dic_o);
					set_Height(a.Get_float(1), dic_o);
				}
				else
				{
					a = c.AttrVarOverride("Width");
					if (a != null)
					{
						jDebug.jASSERT(a.IsEType(nXML.EDataType.e_float), g.GetTagName() + " Width type is not e_float");
						set_Width(a.Get_float(), dic_o);
					}

					a = c.AttrVarOverride("Height");
					if (a != null)
					{
						jDebug.jASSERT(a.IsEType(nXML.EDataType.e_float), g.GetTagName() + " Height type is not e_float");
						set_Height(a.Get_float(), dic_o);
					}
				}
				a = c.AttrVarOverride("MinMaxW");
				if (a != null)
				{
					if (!a.IsEType(nXML.EDataType.e_float_array))
						throw new System.Exception(g.GetTagName() + " MinMaxW type is not e_float_array");

					set_MinMaxW(a.Get_float(0), a.Get_float(1), dic_o);
				}
				else
				{
					float fMax = 0;
					float fMin = 0;

					a = c.AttrVarOverride("MaxWidth");
					if (a != null && a.Get_float() > 0) fMax = a.Get_float();

					a = c.AttrVarOverride("MinWidth");
					if (a != null && a.Get_float() > 0) fMin = a.Get_float();

					set_MinMaxW(fMin, fMax, dic_o);
				}

				a = c.AttrVarOverride("MinMaxH");
				if (a != null)
				{
					if (!a.IsEType(nXML.EDataType.e_float_array))
						throw new System.Exception(g.GetTagName() + " MinMaxH type is not e_float_array");

					set_MinMaxH(a.Get_float(0), a.Get_float(1), dic_o);
				}
				else
				{
					float fMax = 0;
					float fMin = 0;

					a = c.AttrVarOverride("MaxHeight");
					if (a != null && a.Get_float() > 0) fMax = a.Get_float();

					a = c.AttrVarOverride("MinHeight");
					if (a != null && a.Get_float() > 0) fMin = a.Get_float();

					set_MinMaxH(fMin, fMax, dic_o);
				}

				/*
				a = c.AttrVarOverride("ExpandWidth");
				if (a != null && a.Get_bool() != false)
				{
					dic_o.Add(GUILayout.ExpandWidth(a.Get_bool()));
				}

				a = c.AttrVarOverride("ExpandHeight");
				if (a != null && a.Get_bool() != false)
				{
					dic_o.Add(GUILayout.ExpandHeight(a.Get_bool()));
				}
				 */

				m_GUILayoutOption = new GUILayoutOption[dic_o.Count];

				int i = 0;
				foreach (var v in dic_o)
				{
					m_GUILayoutOption[i++] = v;
				}

			}//public jGUILayoutOption(jxE g)

			public GUILayoutOption[] GetOptions()
			{
				return m_GUILayoutOption;
			}
		}//public class jGUILayoutOption


	}//namespace nGui
}// namespace nNWM
