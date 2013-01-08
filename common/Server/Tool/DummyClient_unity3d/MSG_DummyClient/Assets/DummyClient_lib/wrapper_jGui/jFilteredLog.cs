using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using nNWM;
using nNWM.nGui;

using jxD = nNWM.nXML.jxDocument; // xml doc;
using jxE = nNWM.nXML.jxElement; // xml element
using jxA = nNWM.nXML.jxVar; // element attribute
using jxV = nNWM.nXML.jxVar; // attribute or element data
using string_id_t = System.Int32;


namespace nNWM
{
	namespace nDummy
	{
		public class jFilteredLog
		{
			static public int m_MaxLogLine = 300;
			class jFilteredLogNode
			{
				public string[] m_FilterList;
				public List<string> m_LogList;


				public jFilteredLogNode(string[] f)
				{
					m_FilterList = f;
					m_LogList = new List<string>();
				}
				public List<string> add_log(string strLog)
				{
					if (m_LogList.Count >= jFilteredLog.m_MaxLogLine)
					{
						m_LogList.RemoveAt(0);
					}
					m_LogList.Add(strLog);
					return m_LogList;
				}
			}

			jFilteredLogNode[] m_FilteredLogList;
			jFilteredLogNode m_CurrFilteredLog;

			public void Init(jxE eLogFilter)
			{
				m_FilteredLogList = new jFilteredLogNode[eLogFilter.size()];
				foreach (jxE e in eLogFilter)
				{
					string sFilter = e.Attr("FILTER");
					if (sFilter == null) 
						throw new System.Exception(e.ToString() + " : FILTER attribute not found.");

					string[] strList = nNWM.jString.jSplit(sFilter, "| ");

					if (strList == null)
					{
						throw new System.Exception( e.ToString() + " : split filter is null : " + sFilter );
					}

					m_FilteredLogList[e.GetOrder()] = new jFilteredLogNode(strList);
				}
				m_CurrFilteredLog = m_FilteredLogList[0];

			}
			public List<string> ChangeLogFilter(int idx)
			{
				m_CurrFilteredLog = m_FilteredLogList[idx];
				if (m_CurrFilteredLog == null)
					throw new System.Exception("m_CurrFilteredLog == null");
				return m_CurrFilteredLog.m_LogList;
			}

			public List<string> AddLog(string strLog)
			{
				bool isCurrAddLog = false;
				foreach (jFilteredLogNode fl in m_FilteredLogList)
				{
					bool isAdd = true;
					if (fl.m_FilterList != null)
					{
						isAdd = false;
						foreach (string sFilter in fl.m_FilterList)
						{
							isAdd = strLog.Contains(sFilter);
							if (isAdd) break;
						}
					}
					if (isAdd)
					{
						fl.add_log(strLog);
						if (fl == m_CurrFilteredLog)
							isCurrAddLog = true;
					}
				}
				return isCurrAddLog ? m_CurrFilteredLog.m_LogList : null;
			}

			public void ClearLog()
			{
				m_CurrFilteredLog.m_LogList.Clear();
			}

		}//public class jFilteredLog

	}//public namespace nDummy
}//using namespace nNWM
