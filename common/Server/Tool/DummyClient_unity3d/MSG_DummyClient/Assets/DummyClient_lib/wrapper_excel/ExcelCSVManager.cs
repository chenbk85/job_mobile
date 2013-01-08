using UnityEngine;
using System.Collections;

public class ExcelCSVManager : MonoBehaviour 
{
	public TextAsset[] m_CSVFile;

	// Use this for initialization
	void Start () 
	{
		if(m_CSVFile==null)
		{
			Debug.LogError("m_CSVFile is not setup");
			return;
		}
		foreach (var f in m_CSVFile)
		{
			if (f.name.Contains("Sys_Error")==true)
			{
				nEXCEL.CSV_Sys_Error.LoadCSV_FromString(f.text);
				Debug.Log("Load OK : nEXCEL.CSV_Sys_Error.Count()=" + nEXCEL.CSV_Sys_Error.Count());
			}
		}

		nEXCEL.nUtil.jCSV.PostParse();
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
