using UnityEngine;
using System.Collections;
using System.Collections.Generic;


namespace nNWM
{
	using error_string = System.String;
	namespace nConsole
	{
		public class jConsoleArg
		{
			protected string[] m_ArgList;
			string[] m_ArgDefault;
			string m_sFormat;
			public error_string CheckArg(string sFormat) // 성공이면 return ""한다.
			{
				m_sFormat = sFormat;
				string[] argToken = sFormat.Split(' ');
				m_ArgDefault = new string[argToken.Length];
				int iSkipCount = 0;
				int idx=0;
				foreach (var s in argToken)
				{
					if (s[0] == '[')
					{
						++iSkipCount;
						string[] argDefault = s.Split('=');
						if (argDefault.Length != 2)
						{
							return "default arg Format is [variable=value] : " + s ;
						}
						m_ArgDefault[idx] = argDefault[1];
					}
					++idx;
				}

				if (m_ArgList.Length < (argToken.Length - iSkipCount)
					|| m_ArgList.Length > (argToken.Length))
				{
					return "Arg count error: " + sFormat + " Input="+nNWM.nUtil.jDumper.NamedDump(m_ArgList);
				}
				return "";
			}

			public System.Int64 Get_int64(System.IConvertible _arg_index) 
			{
				int arg_index = _arg_index.ToInt32(null);
				if (arg_index<m_ArgList.Length)
					return System.Int64.Parse(m_ArgList[arg_index]); 
				if( arg_index < m_ArgDefault.Length)
					return System.Int64.Parse(m_ArgDefault[arg_index]);
				throw new System.Exception("arg_index overflow : " + arg_index + " : " + m_sFormat);
			}
			public int Get_int32(System.IConvertible _arg_index) 
			{
				int arg_index = _arg_index.ToInt32(null);
				if (arg_index < m_ArgList.Length)
					return int.Parse(m_ArgList[arg_index]);
				if (arg_index < m_ArgDefault.Length)
					return int.Parse(m_ArgDefault[arg_index]);
				throw new System.Exception("arg_index overflow : " + arg_index + " : " + m_sFormat);
			}
			public bool Get_bool(System.IConvertible _arg_index) 
			{
				int arg_index = _arg_index.ToInt32(null);
				if (arg_index < m_ArgList.Length)
					return bool.Parse(m_ArgList[arg_index]);
				if (arg_index < m_ArgDefault.Length)
					return bool.Parse(m_ArgDefault[arg_index]);
				throw new System.Exception("arg_index overflow : " + arg_index + " : " + m_sFormat);
			}
			public string Get_string(System.IConvertible _arg_index) 
			{
				int arg_index = _arg_index.ToInt32(null);
				if (arg_index < m_ArgList.Length)
					return m_ArgList[arg_index];
				if (arg_index < m_ArgDefault.Length)
					return m_ArgDefault[arg_index];
				throw new System.Exception("arg_index overflow : " + arg_index + " : " + m_sFormat);
			}
			public string this[System.IConvertible _arg_index] { get { return Get_string(_arg_index); } }
		}
		//#--------------------------------------------------------------------------
		class jConsoleCmd : jConsoleArg
		//#--------------------------------------------------------------------------
		{
			public string m_Cmd = "";
			public string m_Category = "";


			bool is_White(char c) { return c == ' ' || c == '\t'; }
			bool is_Colune(char c) { return c == '\"'; }
			int find_StartPos(string arg, int iIn, ref int iOut, ref bool isInColon)
			{
				int i = iIn;
				iOut = i;
				isInColon = false;
				++i;
				char c;
				for (; i < arg.Length; ++i)
				{
					c = arg[i];
					if (c == ' ')
						continue;
					else if (c == '\"')
					{
						isInColon = true;
						continue;
					}
					else
						break;
				}
				iOut = i;
				return iOut;
			}
			string[] parse_Arg(string arg)
			{

				string str;
				int iStart = 0;
				List<string> m_ArgList = new List<string>();
				bool isColonIn = false; // 인용문자("")안에 있는거라면 true

				arg = arg.Trim();

				for (int iCurr = 0; iCurr < arg.Length; ++iCurr)
				{
					char c = arg[iCurr];

					if (is_White(c))
					{
						if (arg.Length > (iCurr + 1))
						{
							char c_next = arg[iCurr + 1];
							if (is_White(c_next))
							{
								continue;
							}
						}
						if (isColonIn == false)
						{
							str = arg.Substring(iStart, iCurr - iStart).Trim();
							//Debug.Log("arg1 = " + str);
							m_ArgList.Add(str);

							iStart = find_StartPos(arg, iCurr, ref iCurr, ref isColonIn);
							continue;
						}
					}

					if (c == '\"')
					{
						if (!isColonIn)
						{
							isColonIn = true;
							iStart = (++iCurr);
							continue;
						}
						else
						{
							str = arg.Substring(iStart, (iCurr - iStart)).Trim();
							m_ArgList.Add(str);
							//Debug.Log("arg 2 = " + str);
							isColonIn = false;
							iStart = find_StartPos(arg, iCurr, ref iCurr, ref isColonIn);
							continue;
						}
					}
				}
				str = arg.Substring(iStart).Trim();
				//Debug.Log("arg 3 = " + str);
				if( str.Length > 0)
					m_ArgList.Add(str);

				if (m_ArgList.Count == 0) return null;

				string[] al = new string[m_ArgList.Count];
				int i = 0;
				foreach (var s in m_ArgList)
				{
					al[i++] = s;
				}
				return al;
			}
			public bool Parse_CodeCommand(string sInputCmd)
			{
				m_Cmd = sInputCmd.Substring(1);
				int iCategoryEnd = m_Cmd.IndexOf('.');
				if (iCategoryEnd < 0) return false;
				m_Category = m_Cmd.Substring(0, iCategoryEnd);
				if (m_Category.Length < 0) return false;
				m_Cmd = m_Cmd.Substring(iCategoryEnd + 1);
				int iCut = m_Cmd.IndexOf(' ');
				if (iCut < 0) return false;
				string arg = m_Cmd.Substring(iCut + 1);
				arg.Trim();
				m_Cmd = m_Cmd.Substring(0, iCut);
				if (m_Cmd.Length < 0) return false;

				m_ArgList = parse_Arg(arg);

				//Debug.Log("m_Category= [" + m_Category + "] m_Cmd = [" + m_Cmd + "] arg = [" + arg + "]");
				//Debug.Log("m_ArgList = " + nNWM.nUtil.jDumper.NamedDump(m_ArgList));
				return true;
			}
		}

		//#--------------------------------------------------------------------------
		public class jConsoleCmdManager
		//#--------------------------------------------------------------------------
		{
			GameObject m_goCmdList;
			string m_CmdPrefix;

			string GetCategory(string category) { return m_CmdPrefix + category; }

			public jConsoleCmdManager(GameObject go,string cmdTag)
			{
				m_goCmdList = go;
				if (m_goCmdList == null) throw new System.Exception("m_goCmdList==null");
				m_CmdPrefix = cmdTag;
			}

			public bool ParseCmd(string sInputCmd)
			{
				jConsoleCmd c = new jConsoleCmd();
				if (sInputCmd[0] == '@')
				{
					if (!c.Parse_CodeCommand(sInputCmd)) return false;

					string sCategory = GetCategory(c.m_Category);

					Component cp = m_goCmdList.GetComponent(sCategory);
					if (cp == null)
					{
						m_goCmdList.SendMessage("LogError", "m_goCmdList.GetComponent(" + sCategory + ")==null");
						return false;
					}

					//Application.RegisterLogCallback(HandleLog);
					cp.SendMessage(c.m_Cmd, (jConsoleArg)c, SendMessageOptions.DontRequireReceiver);
					//Application.RegisterLogCallback(null);
					return true;
				}
				else if (sInputCmd[0] == '#')
				{
					c.m_Cmd = sInputCmd.Substring(1);
				}

				//gameObject.GetComponent<>
				return true;
			}

		}//class jConsoleCmdManager

	}//namespace nConsole
}//namespace nNWM
