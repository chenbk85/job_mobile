using UnityEngine;
using System.Collections;
using System.Collections.Generic;

using nSDD = System.Diagnostics.Debug;
using jxD = nNWM.nXML.jxDocument; // xml doc;
using jxE = nNWM.nXML.jxElement; // xml element
using jxA = nNWM.nXML.jxVar; // element attribute
using jxV = nNWM.nXML.jxVar; // attribute or element data
using string_id_t = System.Int32;


namespace nNWM
{
    namespace nXML
    {

        public class jxDocument
        {
            public string m_name;
            public jxElement m_Root;

            private static Dictionary<string, jxDocument>   m_DocList = new Dictionary<string, jxDocument>();
            
            public jxDocument Find(string name)
            {
                if (m_DocList.ContainsKey(name) == false)
                {
                    return null;
                }
                return m_DocList[name];
            }

            public static jxDocument Load(string name, string strXml)
            {
                if (m_DocList.ContainsKey(name) == true)
                {
                    throw new System.Exception(" m_DocList.ContainsKey(name) : " + name + ">>");
                }
								jxDocument doc = new jxDocument();

								try
								{
									nXML.jxParser p = new nXML.jxParser(strXml);
									doc.m_Root = p.Parse();
								}
								catch (System.Exception ex)
								{
									throw new System.Exception(" nXML.jxParser p = new nXML.jxParser("+ strXml + ") : " + name + ">> " + ex.ToString());
								}

								m_DocList.Add(name, doc);
                doc.m_name = name;

                Debug.Log("jxDocument.Load =  " + name);
                return doc;
            }
						public void DebugPrint()
						{
							string outString = "";
							m_Root.WriteToString(ref outString);
							Debug.Log(outString);
						}
        }
    }
}//namespace nNWM
