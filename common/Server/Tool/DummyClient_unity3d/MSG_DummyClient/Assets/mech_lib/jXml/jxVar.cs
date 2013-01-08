using UnityEngine;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

using string_id_t = System.Int32;

namespace nNWM
{
	namespace nXML
	{
		public enum EDataType
		{
			e_Int64,// i64_
			e_int, // i_

			e_double, // f64_
			e_float, // f_

			e_bool, // b_

			e_int_array, // ia_
			e_float_array, // fa_
			e_Rect,// r_
			e_Point,//p_

			e_string,

			e_element,
			e_unkown,
			e_error,
			e_null,
		}
		public enum EWidthHeight
		{
			eW,
			eH,
		}


		[StructLayout(LayoutKind.Explicit)]
		//#--------------------------------------------------------------------------
		public struct jxData
		//#--------------------------------------------------------------------------
		{
			// int

			[FieldOffset(0)]
			public Int64 m_Int64;
			[FieldOffset(0)]
			public int m_int;

			//float

			[FieldOffset(0)]
			public double m_double;
			[FieldOffset(0)]
			public float m_float;

			[FieldOffset(0)]
			public bool m_bool;

			// array
			[FieldOffset(0)]
			public float[] m_float_array;

			[FieldOffset(0)]
			public int[] m_int_array;
		}

		//[System.Serializable]
		//#--------------------------------------------------------------------------
		public class jxVar 
		//#--------------------------------------------------------------------------
		{
			private EDataType m_EDataType;
			private string _name;

			protected string_id_t m_string_id;

			public string GetTagName(){ return _name;}
			public bool IsTagName(string name) { return _name==name;}
			public void SetTagName(string name)
			{
				if (name == null)
				{
					throw new System.Exception("name is null");
				}
				name.Trim();
				if (name.Length == 0)
					throw new System.Exception("name = [" + name + "] is Length==0");
				if (name.Contains("/"))
					throw new System.Exception("name = [" + name + "] is Contain slash !");
				
				EDataType eType = jxUtil.GetTypeByTagName(name, ref _name);
				if (! (eType == EDataType.e_element && m_EDataType == EDataType.e_string) )
					m_EDataType = eType;
				m_string_id = jIndexString.GetIndex(_name);
			}
			private string m_string;
			private jxData m_data;


			//#--------------------------------------------------------------------------
			// ctor & dtor
			//#--------------------------------------------------------------------------
			//public jxVar() { m_EDataType = EDataType.e_unkown; }
			public jxVar(EDataType eType) { m_EDataType = eType; }
			//~jxVar() { clear();}

			private void clear() 
			{  
				if(m_EDataType==EDataType.e_null) return;
				_name=null;
				m_string_id=0;
				switch(m_EDataType)
				{
					case EDataType.e_string:
						{
							m_string =null;
							break;
						}
					case EDataType.e_float_array:
					{
						m_data.m_float_array =null;
						break;
					}
					case EDataType.e_int_array:
					{
						m_data.m_int_array =null;
						break;
					}
				}
				m_EDataType = EDataType.e_null;
			}
			//#--------------------------------------------------------------------------
			// member function
			//#--------------------------------------------------------------------------
			public string Get_string() { return m_string; }
			public bool Get_bool() { return m_data.m_bool; }
			public string_id_t GetIndex() { return m_string_id; }
			public EDataType GetEType() { return m_EDataType; }
			public bool IsEType(EDataType eType) { return m_EDataType == eType; }
			public jxVar Base() { return this; }
			public string ToDebugString()
			{
				string name = GetTagName();
				if(name == null ) 
					name = "NULL";
				return name + "(" + m_EDataType.ToString() + ") = " + ConvertToString();
			}

			public void Set_int(int i)			{ m_data.m_int = i; if (m_EDataType != EDataType.e_int)throw new System.Exception("type is not e_int"); }
			public void Set_float(float i)	{ m_data.m_float = i; if (m_EDataType != EDataType.e_float)throw new System.Exception("type is not e_float"); }
			public void Set_bool(bool i)		{ m_data.m_bool = i; if (m_EDataType != EDataType.e_bool)throw new System.Exception("type is not e_bool"); }
			public void Set_string(string i){ m_string = i; if (m_EDataType != EDataType.e_string)throw new System.Exception("type is not e_string"); }

			public int Get_int() { return m_data.m_int; }
			public int Get_int(int idx)
			{
				if (m_EDataType != EDataType.e_int_array)
					throw new System.Exception(ToDebugString());

				if (idx < 0 && idx >= m_data.m_int_array.Length)
					throw new System.Exception(ToDebugString());

				return m_data.m_int_array[idx];
			}
			public float Get_float() { return m_data.m_float; }
			public float Get_float(int idx)
			{
				if (m_EDataType != EDataType.e_float_array)
					throw new System.Exception(ToDebugString());

				if (idx < 0 && idx >= m_data.m_float_array.Length)
					throw new System.Exception(ToDebugString());

				return m_data.m_float_array[idx];
			}
			public float GetWH(nXML.EWidthHeight e)
			{
				if (m_EDataType != EDataType.e_float_array || m_data.m_float_array.Length != 2)
					throw new System.Exception(ToDebugString());

				return m_data.m_float_array[(int)e];
			}

			public Rect GetRect()
			{
				if (m_EDataType != EDataType.e_Rect) throw new System.Exception("m_EDataType != EDataType.e_Rect");
				Rect r = new Rect();
				r.Set(m_data.m_float_array[0], m_data.m_float_array[1], m_data.m_float_array[2], m_data.m_float_array[3]);
				return r;
			}
			public void SetDataByEDataType(string name, string val)
			{
				SetTagName(name);
				if (val != null)
				{
					ConvertFromString(val);
				}
			}

			//  ( "tagname", e_int)  -> "i_tagName"
			public String GetTagNameFull() { return jxUtil.GetTagNameByType(_name, m_EDataType); }


			// --------------------------------------
			public static void CopyArray_int(out int[] array, string[] words)
			{
				array = new int[words.Length];
				int i = 0;
				foreach (var s in words)
				{
					array[i++] = int.Parse(s);
				}
			}
			public static void CopyArray_float(out float[] array, string[] words)
			{
				array = new float[words.Length];
				int i = 0;
				foreach (var s in words)
				{
					array[i++] = float.Parse(s);
				}
			}
			// --------------------------------------



			public void ConvertFromString(string val)
			{
				if (val == null) return;

				try
				{
					switch (m_EDataType)
					{
						case EDataType.e_Int64:// i64_
							{
								m_EDataType = EDataType.e_Int64;
								m_data.m_Int64 = Int64.Parse(val);
								return;
							}
						case EDataType.e_int: // i_
							{
								m_data.m_int = int.Parse(val);
								return;
							}

						case EDataType.e_double: // f64_
							{
								m_EDataType = EDataType.e_double;
								m_data.m_double = Int64.Parse(val);
								return;
							}
						case EDataType.e_float: // f_
							{
								m_data.m_float = float.Parse(val);
								return;
							}

						case EDataType.e_bool: // b_
							{
								if (bool.TryParse(val, out m_data.m_bool) == false)
								{
									m_data.m_bool = (val == "0");
								}
								return;
							}

						case EDataType.e_int_array: // ia_
							{
								string[] words = jString.jSplit(val, " ;\t");
								CopyArray_int(out m_data.m_int_array, words);
								return;
							}
						case EDataType.e_Rect: // r_
							{
								string[] words = jString.jSplit(val, " ;\t");
								jDebug.jASSERT(words.Length == 4, "val = " + val);
								CopyArray_float(out m_data.m_float_array, words);
								return;

							}
						case EDataType.e_Point: //p_
							{
								string[] words = jString.jSplit(val, " ;\t");
								jDebug.jASSERT(words.Length == 2, "val = " + val);
								CopyArray_float(out m_data.m_float_array, words);
								return;
							}

						case EDataType.e_float_array: // fa_
							{
								string[] words = jString.jSplit(val, " ;\t");
								CopyArray_float(out m_data.m_float_array, words);
								return;
							}
						case EDataType.e_string:
							{
								m_string = val;
								return;
							}
						case EDataType.e_element:
							{
								string new_val = val;
								new_val.Trim();
								if (new_val.Length != 0)
								{
									m_string = val;
									m_EDataType = EDataType.e_string;
								}
								else
								{
									Debug.LogWarning("skip " + GetTagName() + " = " + val);
								}
							}
							return;
						case EDataType.e_unkown:// jxElement置段 持失葵.
							{
								string new_val = val;
								new_val.Trim();
								if (new_val.Length != 0)
								{
									m_string = val;
									m_EDataType = EDataType.e_string;
								}
								else
								{
									Debug.LogWarning("skip " + GetTagName() + " = " + val);
								}
								return;
							}
					}//switch (m_EDataType)
				}
				catch (System.Exception ex)
				{
					Debug.LogError(this._name + " error :" + ex.ToString());

				}//catch (System.Exception ex)

			}//public void FromString(string val)

			public string ConvertToString()
			{
				switch (m_EDataType)
				{
					case EDataType.e_Int64:// i64_
						{
							return m_data.m_Int64.ToString();
						}
					case EDataType.e_int: // i_
						{
							return m_data.m_int.ToString();
						}

					case EDataType.e_double: // f64_
						{
							return m_data.m_double.ToString();
						}
					case EDataType.e_float: // f_
						{
							return m_data.m_float.ToString();
						}

					case EDataType.e_bool: // b_
						{
							return m_data.m_bool.ToString();
						}

					case EDataType.e_int_array: // ia_
						{
							string sData = "";
							int iSize = m_data.m_int_array.Length;
							foreach (var i in m_data.m_int_array)
							{
								sData += i.ToString();
								--iSize;
								if (iSize >= 1)
									sData += ";";
							}
							return sData;
						}

					case EDataType.e_Rect: // r_
					case EDataType.e_Point: // p_
					case EDataType.e_float_array: // fa_
						{
							string sData = "";
							int iSize = m_data.m_float_array.Length;
							foreach (var i in m_data.m_float_array)
							{
								sData += i.ToString();
								--iSize;
								if (iSize >= 1)
									sData += ";";
							}
							return sData;
						}
					case EDataType.e_string:
						{
							return m_string;
						}
					case EDataType.e_element:
						return "";

				}
				return m_string;
			}
		}//public class jxVar

	}//namespace nXML
}
