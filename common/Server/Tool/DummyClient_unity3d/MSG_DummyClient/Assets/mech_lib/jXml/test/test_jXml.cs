using UnityEngine;
using System.Collections;

using nXML = nNWM.nXML;
using nNWM;

using jxD = nNWM.nXML.jxDocument; // xml doc;
using jxE = nNWM.nXML.jxElement; // xml element
using jxA = nNWM.nXML.jxVar; // element attribute
using jxV = nNWM.nXML.jxVar; // attribute or element data
using string_id_t = System.Int32;

/*
 * test_xml_file = 
<stageData a="A" b="B">
	<stage f_c="234" ff_c2="1;2"  ff_c3="1;2;3">
		<map>1, 2, 3, A, B, C</map>
		<ii_mapii>255;255;0;255</ii_mapii>
		<argb_map>255;0;255;125</argb_map>
	</stage>
	<stage1 i_b="23" ii_b2="11;22" ii_b3="33;44;55">
	</stage1>
	<b_bool b_bool1="1" b_bool2="False" >false</b_map>
	<i_bigVal>12345678</i_bigVal>
	<i64_bigVal>1234567890123456789</i64_bigVal>
	<r_map2>255;0;255;125</r_map2>
	<map3>1, 1, 1, 1, 1, 1</map3>
	<map4>A, A, A, A, A, A</map4>
	<map5>3, 3, 3, 3, 3, 3</map5>
	
</stageData>
 * 
 * */
public class test_jXml : MonoBehaviour
{
    public TextAsset test_xml_file;
    GameObject prefab;

    // Use this for initialization
    void Start()
    {
        Debug.Log("test_jXml Start====================================");
        // Load a text asset XML file from the assets/resources folder
        //m_doc = Resources.Load("Assets/xml_test", typeof(TextAsset)) as TextAsset;
        //m_doc = Resources.Load("test_xml") as TextAsset;
        //m_doc = (TextAsset)Resources.LoadAssetAtPath("xml/xml_test.txt", typeof(TextAsset));

        nXML.jxDocument doc = nXML.jxDocument.Load(test_xml_file.name, test_xml_file.text);
        jDebug.jASSERT(doc != null && doc.m_Root!=null);
        
        string outString = "";
        doc.m_Root.WriteToString(ref outString);
        Debug.Log(outString);

        jDebug.jASSERT(doc.m_Root.Attr("b") == "B");

        jxE stage = doc.m_Root.Find("stage");
        jDebug.jASSERT(stage != null);
        jDebug.jASSERT(stage.GetIndex() == jIndexString.GetIndex("stage"));
        jxE mapii = stage.Find("mapii");
        jDebug.jASSERT(mapii != null);
        jDebug.jASSERT(mapii.IsEType(nXML.EDataType.e_int_array));
        jDebug.jASSERT(mapii.Get_int(0) == 255);
        jDebug.jASSERT(mapii.Get_int(2) == 0);

        jxV v = stage.AttrVar("c3");
        jDebug.jASSERT(v.IsEType(nXML.EDataType.e_float_array));
        jDebug.jASSERT( v.Get_float(2) == 3 );


        // test duplcated load;
//         doc = nXML.jxDocument.Load(test_xml_file.name, test_xml_file.text);
//         jDebug.jASSERT(doc == null, "duplicated xml loading must be fail");

        Debug.Log("test_jXml End====================================");
    }
} 