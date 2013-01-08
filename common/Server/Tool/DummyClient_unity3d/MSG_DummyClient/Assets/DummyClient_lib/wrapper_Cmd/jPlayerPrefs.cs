using UnityEngine;
using System.Collections;

namespace nNWM
{
	namespace nDummy
	{

		public class jPlayerPrefs
		{
			CmdEventManager m_CMD;
			public jPlayerPrefs(CmdEventManager cmd)
			{
				m_CMD = cmd;
			}

			public  void Get(string name, ref int i)
			{
				name = m_CMD.m_GameGuiEventManager + name;
				i = PlayerPrefs.GetInt(name, i);;
			}
			public void Get(string name, ref string i)
			{
				name = m_CMD.m_GameGuiEventManager + name;
				i = PlayerPrefs.GetString(name, i);
			}
			public void Get(string name, ref bool i)
			{
				name = m_CMD.m_GameGuiEventManager + name;
				i = bool.Parse(PlayerPrefs.GetString(name, i.ToString()));
			}
			public void Get<T>(string name, ref T i)
			{
				name = m_CMD.m_GameGuiEventManager + name;
				i = (T)System.Enum.Parse(typeof(T), PlayerPrefs.GetString(name, i.ToString()));
			}

			public void Set(string name, int i)
			{
				name = m_CMD.m_GameGuiEventManager + name;
				PlayerPrefs.SetInt(name, i);
			}
			public void Set(string name, string i)
			{
				name = m_CMD.m_GameGuiEventManager + name;
				PlayerPrefs.SetString(name, i);
			}
			public void Set(string name, bool i)
			{
				name = m_CMD.m_GameGuiEventManager + name;
				PlayerPrefs.SetString(name, i.ToString()); ;
			}
			public void Set<T>(string name, T i)
			{
				name = m_CMD.m_GameGuiEventManager + name;
				PlayerPrefs.SetString(name, i.ToString());
			}

		}//public class jPlayerPrefs
	} ///nDummy

} // nNWM
