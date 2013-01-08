xml로 어떻게 gui를 설계하는지에 대한 샘플은 다음을 참고하세요.

	MSG_DummyClient/Assets/mech_lib/jGui/test/guixml_dummy_client.xml



/* 

//#--------------------------------------------------------------------------
jGuiContorl에 대한 전역 속성.
//#--------------------------------------------------------------------------
	속성 Rect의 의미
		r_Rect="1;2;3;4" 
			x,y,width,height
		
		Rect="string"
			해당string을 xml의 <NamedRect>에서 찾는다.
		
	속성 Text (옵션.)
		jGuiControl의 화면에 보여지는 text내용이 온다.
		만약 Text속성이 없으면 Name속성의 text를 사용한다.
		Name속성도 없으면 값은 ""으로 취급된다.
		
	속성 Name (옵션)
		Name을 지정하는 이유는 하나이다.
		즉, jGuiControl에 이벤트가 발생할때 Name에 해당하는 함수EventHandler가 존재하면 호출된다.

	속성 TextAnchor="enum이름" (옵션)
		값의 종류.
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
	
	FontStyle="enum이름" (옵션)
	
		public enum FontStyle
		{
			Normal = 0,
			Bold = 1,
			Italic = 2,
			BoldAndItalic = 3,
		}



//#--------------------------------------------------------------------------
jGuiTextArea의 속성
//#--------------------------------------------------------------------------

	MaxLength="int" (옵션) 숫자만큼의 text만 입력받음.
	
		값= 0이면 Text안찍힘.
		값= 음수 이면 text길이 제한없음.
	

//-------------------------------------------------------------------------------
//다음  그룹컨트롤들은 다음 특징을 가짐.
//-------------------------------------------------------------------------------
	<jGuiLayout>
	<jGuiVertical>
	<jGuiHorizontal>
	
	특징.
	
		자신과 자식모두 m_isLayouted가 항상 true이다.
		자신과 자식모두 LayoutOption의 속성를 가질수 있다.
	
	LayoutOption 속성에 대해.
	
		해당 속성이 없거나 값이 0이면 해당 속성무시.
		
		종류.
			f_Width="-1"	
				값이 -1 이면 b_ExpandWidth="true"가 세팅된다.
			
			f_Height="130" 
				값이 -1 이면 b_ExpandHeight="true"가 세팅된다.
				
			f_MaxWidth="500" 
			f_MaxHeight="-1" 
			
			f_MinWidth="-1" 
			f_MinHeight="-1"
			
			ff_WH="0;0" 
				f_Width와 f_Height를 합친것.
			
			ff_MinMaxWidth="0;0"
				f_MinWidth 와 f_MaxWidth를 합친것.

			ff_MinMaxHeight="0;0"
				f_MinHeight 와 f_MaxHeight를 합친것.


	<OverrideAttribute> 란?
		해당 jGuiControl이 자신의 xml정보를 로딩할때  필요로 하는 속성을 못찾을경우 
		자신의 조상중에 <OverrideAttribute>가 있고 그 중에 자신과 동일한 
		컨트롤이름이 있을때 그 xml element에서 속성을 한번 더 찾는다.
		
		관련 함수
			string	jGuiControl.AttrOverride(string);
			jxV		jGuiControl.AttrVarOverride(string);
			
	
	

	xml에서 jGui로 시작하는 노드들은 jGuiControl 객체로 간주하면된다.
		반대로 jGui로 시작하지 않는 element는 일반 정보이다.
		
		jGuiControl CreateRTTI(jxE e)

*/


//-------------------------------------------------------------------------------
// 확장 jGuiControl을 위한 기본 템플릿 코드
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
// jGuiEvent 스크립트의 핸들러 정의 방법.
//#--------------------------------------------------------------------------


public class jGuiEvent_MSG_DummyClient : MonoBehaviour 
{
	// 1단계.
	void jGuiStage_LoadFinished(nNWM.nGui.jGuiStage stage) // xml file에 대한 모든 jGuiControl을 포함하는 stage로딩이 완료되었다.
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


/* Modal용 템플릿 코드

public class GuiEvent_asdf : nNWM.nDummy.GuiEvent_base
{
	void OnLoadedGUI_asdf(jGuiWindow win) // "asdf"라는 jGuiWindow 로딩이 완료되면 호출됨.
	{
		base.Set_jGuiWindow(win);// 반드시 호출.
	
	}
	void OnShowModal_asdf(jGuiWindow win) // "asdf"라는 모달
	{
	}
	
	void jGuiButton_Cancel(jGuiButton ctrl) // "Cancel"이라는 
	{
		m_jGuiStage.HideModalWindow();	//모달 윈도우를 종료한다.
	}
	
}

*/


