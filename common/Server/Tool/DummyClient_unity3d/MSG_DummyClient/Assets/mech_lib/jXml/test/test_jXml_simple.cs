using UnityEngine;
using System.Collections;

using nXML = nNWM.nXML;
using nNWM;

using jxD = nNWM.nXML.jxDocument; // xml doc;
using jxE = nNWM.nXML.jxElement; // xml element
using jxA = nNWM.nXML.jxVar; // element attribute
using jxV = nNWM.nXML.jxVar; // attribute or element data
using string_id_t = System.Int32;

public class test_jXml_simple : MonoBehaviour
{
	public TextAsset test_xml_file_simple;
	GameObject prefab;

	// Use this for initialization
	void Start()
	{
		nXML.jxDocument doc = nXML.jxDocument.Load(test_xml_file_simple.name, test_xml_file_simple.text);
		jDebug.jASSERT(doc != null && doc.m_Root != null);

		string outString = "";
		doc.m_Root.WriteToString(ref outString);
		Debug.Log("doc = " + outString);

		string aaS = "";
		jxE aa = doc.m_Root.Find("aa");
		jDebug.jASSERT(aa.GetTagName() == "aa");
		aa.WriteToString(ref aaS);
		//Debug.Log("aa = " + aaS);

		string aa1S = "";
		jxE aa1 = aa.MakeClone();
		aa1.WriteToString(ref aa1S);
		//Debug.Log("aa1 = " + aa1S);

		jDebug.jASSERT(aaS == aa1S);

		jDebug.jASSERT(aa1.GetParent() == null);
		doc.m_Root.InsertChild(aa1);
		
		outString ="";
		doc.m_Root.WriteToString(ref outString);
		Debug.Log("doc = " + outString);

	}
}