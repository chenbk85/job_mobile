using UnityEngine;
using System.Collections;

public class SkinTest : MonoBehaviour
{
    public GUISkin thisMetalGUISkin;
    public GUISkin thisOrangeGUISkin;
    public GUISkin thisAmigaGUISkin;
    private Rect rect_Win_OrangeUnity;
    private Rect rect_Win_MetalVista;
    private Rect rect_Win_ToggleListbox;
    private Rect rectWin_OrangeUnity;
    //private Rect rect_Win_DoMyWindow5;
    private bool blnToggleState = false;
    private float fltSliderValue = 0.5f;
    private float fltScrollerValue = 0.5f;
    private Vector2 m_scrollPosition = Vector2.zero;


    public TextAsset LevelXMLFile;



    public struct snNodeArray
    {
        public string itemType, itemName;
        public snNodeArray(string itemType, string itemName)
        {
            this.itemType = itemType;
            this.itemName = itemName;
        }
    }
    private snNodeArray[] testArray = new snNodeArray[20];

    void Start()
    {
        //LevelXMLFile = (TextAsset)Resources.LoadAssetAtPath("xml/xml_test.xml", typeof(TextAsset));

        rect_Win_OrangeUnity = new Rect(20, 20, 320, 400);
        rect_Win_MetalVista = new Rect(260, 30, 320, 420);
        rect_Win_ToggleListbox = new Rect(260, 30, 420, 250);
        rectWin_OrangeUnity = new Rect(360, 20, 320, 400);
        //rect_Win_DoMyWindow5 = new Rect(360, 20, 320, 400);
        for (int i = 0; i < 19; i++)
        {
            testArray[i].itemType = "node";
            testArray[i].itemName = "Hello" + i;
        }
    }
    void OnGUI()
    {
        int iWinOrder = 0;
        GUI.skin = thisMetalGUISkin;
        rect_Win_ToggleListbox = GUI.Window(iWinOrder++, rect_Win_ToggleListbox, Win_ToggleListbox, "Compound Control - Toggle Listbox", GUI.skin.GetStyle("window"));
        //rect_Win_DoMyWindow5 = GUI.Window(iWinOrder++, rect_Win_DoMyWindow5, Win_DoMyWindow5, "Amiga500", GUI.skin.GetStyle("window"));

        GUI.skin = thisAmigaGUISkin;
        rectWin_OrangeUnity = GUI.Window(iWinOrder++, rectWin_OrangeUnity, Win_OrangeUnity, "Amiga500", GUI.skin.GetStyle("window"));
        GUI.skin = thisOrangeGUISkin;
        rect_Win_OrangeUnity = GUI.Window(iWinOrder++, rect_Win_OrangeUnity, Win_OrangeUnity, "Orange Unity", GUI.skin.GetStyle("window"));
        GUI.skin = thisMetalGUISkin;
        rect_Win_MetalVista = GUI.Window(iWinOrder++, rect_Win_MetalVista, Win_MetalVista, "Metal Vista", GUI.skin.GetStyle("window"));
    }

    void gcListItem(string strItemName)
    {
        GUILayout.BeginHorizontal();
        GUILayout.Button(strItemName);
        //GUILayout.Label(strItemName);
        blnToggleState = GUILayout.Toggle(blnToggleState, "");
        GUILayout.EndHorizontal();
    }

    void gcListBox()
    {
        GUILayout.BeginVertical(GUI.skin.GetStyle("box"));
        m_scrollPosition = GUILayout.BeginScrollView(m_scrollPosition, GUILayout.Width(260), GUILayout.Height(130));
        for (int i = 0; i < 20; i++)
        {
            gcListItem("I'm listItem number " + i);
        }
        GUILayout.EndScrollView();
        GUILayout.EndVertical();
        GUILayout.TextField("Im a textfield");
    }

    void Win_ToggleListbox(int windowID)
    {
        gcListBox();
        GUI.DragWindow();
    }

    void Win_DoMyWindow5(int windowID)
    {
        m_scrollPosition = GUI.BeginScrollView(new Rect(10, 100, 200, 200), m_scrollPosition, new Rect(0, 0, 220, 200));
        GUI.Button(new Rect(0, 0, 100, 20), "Top-left");
        GUI.Button(new Rect(120, 0, 100, 20), "Top-right");
        GUI.Button(new Rect(0, 180, 100, 20), "Bottom-left");
        GUI.Button(new Rect(120, 180, 100, 20), "Bottom-right");
        GUI.EndScrollView();
        GUI.DragWindow();
    }

    void Win_OrangeUnity(int windowID)
    {
        GUILayout.BeginVertical();
        GUILayout.Label("Im a Label");
        GUILayout.Space(8);
        GUILayout.Button("Im a Button");
        GUILayout.TextField("Im a textfield");
        GUILayout.TextArea("Im a textfield\nIm the second line\nIm the third line\nIm the fourth line");
        blnToggleState = GUILayout.Toggle(blnToggleState, "Im a Toggle button");
        GUILayout.EndVertical();
        GUILayout.BeginVertical();
        //Sliders
        GUILayout.BeginHorizontal();
        fltSliderValue = GUILayout.HorizontalSlider(fltSliderValue, 0.0f, 1.1f, GUILayout.Width(128));
        fltSliderValue = GUILayout.VerticalSlider(fltSliderValue, 0.0f, 1.1f, GUILayout.Height(50));
        GUILayout.EndHorizontal();
        //Scrollbars
        GUILayout.BeginHorizontal();
        fltScrollerValue = GUILayout.HorizontalScrollbar(fltScrollerValue, 0.1f, 0.0f, 1.1f, GUILayout.Width(128));
        fltScrollerValue = GUILayout.VerticalScrollbar(fltScrollerValue, 0.1f, 0.0f, 1.1f, GUILayout.Height(90));
        GUILayout.Box("Im\na\ntest\nBox");
        GUILayout.EndHorizontal();
        GUILayout.EndVertical();
        GUI.DragWindow();
    }

    void Win_MetalVista(int windowID)
    {
        GUILayout.Label("3D Graphics Settings");
        GUILayout.BeginVertical();
        GUILayout.BeginHorizontal();
        blnToggleState = GUILayout.Toggle(blnToggleState, "Soft Shadows");
        blnToggleState = GUILayout.Toggle(blnToggleState, "Particle Effects");
        GUILayout.EndHorizontal();
        GUILayout.BeginHorizontal();
        blnToggleState = GUILayout.Toggle(blnToggleState, "Enemy Shadows");
        blnToggleState = GUILayout.Toggle(blnToggleState, "Object Glow");
        GUILayout.EndHorizontal();
        GUILayout.EndVertical();
        GUILayout.BeginVertical();
        GUILayout.Button("Im a Button");
        GUILayout.TextField("Im a textfield");
        GUILayout.TextArea("Im a textfield\nIm the second line\nIm the third line\nIm the fourth line");
        blnToggleState = GUILayout.Toggle(blnToggleState, "Im a Toggle button");
        GUILayout.EndVertical();
        GUILayout.BeginVertical();
        //Sliders
        GUILayout.BeginHorizontal();
        fltSliderValue = GUILayout.HorizontalSlider(fltSliderValue, 0.0f, 1.1f, GUILayout.Width(128));
        fltSliderValue = GUILayout.VerticalSlider(fltSliderValue, 0.0f, 1.1f, GUILayout.Height(50));
        GUILayout.EndHorizontal();
        //Scrollbars
        GUILayout.BeginHorizontal();
        fltScrollerValue = GUILayout.HorizontalScrollbar(fltScrollerValue, 0.1f, 0.0f, 1.1f, GUILayout.Width(128));
        fltScrollerValue = GUILayout.VerticalScrollbar(fltScrollerValue, 0.1f, 0.0f, 1.1f, GUILayout.Height(90));
        GUILayout.Box("Im\na\ntest\nBox");
        GUILayout.EndHorizontal();
        GUILayout.EndVertical();
        GUI.DragWindow();
    }
}
