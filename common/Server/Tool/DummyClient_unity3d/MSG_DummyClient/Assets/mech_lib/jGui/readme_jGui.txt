xml�� ��� gui�� �����ϴ����� ���� ������ ������ �����ϼ���.

	MSG_DummyClient/Assets/mech_lib/jGui/test/guixml_dummy_client.xml



/* 

//#--------------------------------------------------------------------------
jGuiContorl�� ���� ���� �Ӽ�.
//#--------------------------------------------------------------------------
	�Ӽ� Rect�� �ǹ�
		r_Rect="1;2;3;4" 
			x,y,width,height
		
		Rect="string"
			�ش�string�� xml�� <NamedRect>���� ã�´�.
		
	�Ӽ� Text (�ɼ�.)
		jGuiControl�� ȭ�鿡 �������� text������ �´�.
		���� Text�Ӽ��� ������ Name�Ӽ��� text�� ����Ѵ�.
		Name�Ӽ��� ������ ���� ""���� ��޵ȴ�.
		
	�Ӽ� Name (�ɼ�)
		Name�� �����ϴ� ������ �ϳ��̴�.
		��, jGuiControl�� �̺�Ʈ�� �߻��Ҷ� Name�� �ش��ϴ� �Լ�EventHandler�� �����ϸ� ȣ��ȴ�.

	�Ӽ� TextAnchor="enum�̸�" (�ɼ�)
		���� ����.
			public enum TextAnchor
			{
				UpperLeft = 0,
				UpperCenter = 1,
				UpperRight = 2,
				MiddleLeft = 3,
				MiddleCenter = 4,
				MiddleRight = 5,
				LowerLeft = 6,
				LowerCenter = 7,
				LowerRight = 8,
			}
	
	i_FontSize="int"
	
	FontStyle="enum�̸�" (�ɼ�)
	
		public enum FontStyle
		{
			Normal = 0,
			Bold = 1,
			Italic = 2,
			BoldAndItalic = 3,
		}



//#--------------------------------------------------------------------------
jGuiTextArea�� �Ӽ�
//#--------------------------------------------------------------------------

	MaxLength="int" (�ɼ�) ���ڸ�ŭ�� text�� �Է¹���.
	
		��= 0�̸� Text������.
		��= ���� �̸� text���� ���Ѿ���.
	

//-------------------------------------------------------------------------------
//����  �׷���Ʈ�ѵ��� ���� Ư¡�� ����.
//-------------------------------------------------------------------------------
	<jGuiLayout>
	<jGuiVertical>
	<jGuiHorizontal>
	
	Ư¡.
	
		�ڽŰ� �ڽĸ�� m_isLayouted�� �׻� true�̴�.
		�ڽŰ� �ڽĸ�� LayoutOption�� �Ӽ��� ������ �ִ�.
	
	LayoutOption �Ӽ��� ����.
	
		�ش� �Ӽ��� ���ų� ���� 0�̸� �ش� �Ӽ�����.
		
		����.
			f_Width="-1"	
				���� -1 �̸� b_ExpandWidth="true"�� ���õȴ�.
			
			f_Height="130" 
				���� -1 �̸� b_ExpandHeight="true"�� ���õȴ�.
				
			f_MaxWidth="500" 
			f_MaxHeight="-1" 
			
			f_MinWidth="-1" 
			f_MinHeight="-1"
			
			ff_WH="0;0" 
				f_Width�� f_Height�� ��ģ��.
			
			ff_MinMaxWidth="0;0"
				f_MinWidth �� f_MaxWidth�� ��ģ��.

			ff_MinMaxHeight="0;0"
				f_MinHeight �� f_MaxHeight�� ��ģ��.


	<OverrideAttribute> ��?
		�ش� jGuiControl�� �ڽ��� xml������ �ε��Ҷ�  �ʿ�� �ϴ� �Ӽ��� ��ã����� 
		�ڽ��� �����߿� <OverrideAttribute>�� �ְ� �� �߿� �ڽŰ� ������ 
		��Ʈ���̸��� ������ �� xml element���� �Ӽ��� �ѹ� �� ã�´�.
		
		���� �Լ�
			string	jGuiControl.AttrOverride(string);
			jxV		jGuiControl.AttrVarOverride(string);
			
	
	

	xml���� jGui�� �����ϴ� ������ jGuiControl ��ü�� �����ϸ�ȴ�.
		�ݴ�� jGui�� �������� �ʴ� element�� �Ϲ� �����̴�.
		
		jGuiControl CreateRTTI(jxE e)

*/


//-------------------------------------------------------------------------------
// Ȯ�� jGuiControl�� ���� �⺻ ���ø� �ڵ�
//-------------------------------------------------------------------------------

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
		//#--------------------------------------------------------------------------
		public class jGui_asdf : jGuiControl
		//#--------------------------------------------------------------------------
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

			//#--------------------------------------------------------------------------
			// public member function
			//#--------------------------------------------------------------------------

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
			//#--------------------------------------------------------------------------
            {
                base.Load(stage,  win , parent , g , overrideAttribute);
            }//public override void Load
            
            public override bool OnGUI()
			//#--------------------------------------------------------------------------
            {
				if (base.OnGUI() == false) return false;

				Begin_GUIStyle();
                if (m_isLayouted)
                {
                }
                else
                {
                    throw new System.Exception("TODO");
                }
				End_GUIStyle();
                
                return true;
            }//public override bool OnGUI()

        }//public class jGui_asdf : jGuiControl
    }//namespace nGui
}//namespace nNWM




//#--------------------------------------------------------------------------
// jGuiEvent ��ũ��Ʈ�� �ڵ鷯 ���� ���.
//#--------------------------------------------------------------------------


public class jGuiEvent_MSG_DummyClient : MonoBehaviour 
{
	// 1�ܰ�.
	void jGuiStage_LoadFinished(nNWM.nGui.jGuiStage stage) // xml file�� ���� ��� jGuiControl�� �����ϴ� stage�ε��� �Ϸ�Ǿ���.
	{
		print("jGuiStage_Load");
	}
	

}



public class GuiEventManager : MonoBehaviour
{
	public GUISkin m_GUISkin;
	public TextAsset m_XmlFile;

	jGuiStage m_jGuiStage;

	void Start()
	{
		//LevelXMLFile = (TextAsset)Resources.LoadAssetAtPath("xml/xml_test.xml", typeof(TextAsset));
		m_jGuiStage = nNWM.nGui.jGui.Load(m_XmlFile.name, m_XmlFile.text, m_GUISkin, gameObject, m_GuiEventPrifix);
		if (m_jGuiStage == null)
		{
			throw new System.Exception(m_XmlFile.name + " : " + m_XmlFile.text + " load fail");
		}
	}
	
	void OnGUI()
	{
		if (m_jGuiStage != null)
			m_jGuiStage.OnGUI();
	}

	void OnLoadStageXML_baseball(jGuiStage stage)
	{

	}
	void OnLoadStageGUI_baseball(jGuiStage stage)
	{

	}

}//public class GuiEventManager


//#--------------------------------------------------------------------------
// Modal Dialog
//#--------------------------------------------------------------------------


/* Modal�� ���ø� �ڵ�

public class GuiEvent_asdf : nNWM.nDummy.GuiEvent_base
{
	void OnLoadedGUI_asdf(jGuiWindow win) // "asdf"��� jGuiWindow �ε��� �Ϸ�Ǹ� ȣ���.
	{
		base.Set_jGuiWindow(win);// �ݵ�� ȣ��.
	
	}
	void OnShowModal_asdf(jGuiWindow win) // "asdf"��� ���
	{
	}
	
	void jGuiButton_Cancel(jGuiButton ctrl) // "Cancel"�̶�� 
	{
		m_jGuiStage.HideModalWindow();	//��� �����츦 �����Ѵ�.
	}
	
}

*/


