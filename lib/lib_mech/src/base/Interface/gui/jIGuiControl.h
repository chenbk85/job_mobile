/* 
	filename:	jIGui.h
	coder	:	Cho Hyun Min (icandoit@wemade.com) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	2005-01-14 오전 10:23:36
	title	:	
*/


#ifndef __jIGuiControl_h__
#define __jIGuiControl_h__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000

namespace nMech
{
	namespace nGUI
	{
		enum EGuiClassType 
		{ 
			EGuiClasslType_BEGIN,
			jGUI_CTRL_EDITBOX_CLASS,
			jGUI_CTRL_CLASS,
			jGUI_GROUP_CLASS,
			EGuiCtrlType_END
		};

		typedef nEVENT::jEventMessage jGuiMessage;

		class jGuiControl;
		struct jIGuiControl;
		struct _jGuiElement;
		struct _jGuiTextureNode;
		struct _jGuiFontNode;
		struct jGuiRenderStateObj;

#ifndef jSET_FLAG_INTERFACE_VIRTUAL
#define jSET_FLAG_INTERFACE_VIRTUAL(x, var , bit)\
	virtual bool GetFlag##var()=0; \
	virtual void SetFlag##var(bool is)=0;
#endif
		typedef bool IsWantThingFunc_t(jIGuiControl* pC, void* v);

		struct jIGuiControl
		{
			virtual void* GetInterface(StringID id)=0;
			virtual int ProcessMessage(jIE* peMsg,void**)=0; // jGuiMessage.xml에 메세지 스펙이 있음.
			virtual void SetLocation( int x, int y ,bool isCallCB=true) =0;
			virtual void SetSize( int width, int height ,bool isCallCB=true) =0;
			virtual void Refresh() =0;
			virtual jGuiControl* Base() =0;
			virtual jIE* PlaySound(cstr szEvent) =0;
			virtual jIVar* GetCustomProperty(cstr sz) =0;
			virtual jIVar* SetCustomProperty(cstr sz, jIVar* v) =0;
			virtual jIVar* GetCustomProperty(StringID sz) =0;
			virtual jIVar* SetCustomProperty(StringID sz, jIVar* v) =0;
			virtual cstr   GetTypeName() =0;
			virtual cstr   GetName() =0;
			virtual cstr   GetText() =0;
			virtual void		SetText(cstr) = 0;
			virtual void SetMouseInput(bool is)	=0;
			virtual bool IsMouseInput() =0;
			virtual void SetEnabled( bool bEnabled) =0;
			virtual bool GetEnable() =0;
			virtual void SetVisible( bool bVisible ) 	=0;
			virtual bool GetVisible() =0;
			virtual int GetOrder() =0;
			virtual jIGuiDialog* GetDlg() =0;
			virtual int size() =0;
			virtual void SetFontNode(StringID id) =0;
			virtual jIE* GetjIE()=0;
			virtual int GetX() =0;
			virtual int GetY() =0;
			virtual int GetW() =0;
			virtual int GetH() =0;
			virtual int GetX2() =0;
			virtual int GetY2() =0;
			virtual jIGuiControl* GetParent()	 =0;
			virtual _jGuiFontNode* GetFontNode() =0;
			virtual jIGuiControl* GetCtrlAtPt( POINT &pt ) =0;
			virtual jIGuiControl* GetCtrl( cstr   szName, StringID guiType=0) =0;
			virtual EGuiClassType GetClassType() =0;
			virtual jIGuiControl* Find(cstr   szName) =0;
			virtual _jGuiElement* GetGuiElement(StringID id) =0;
			virtual _jGuiTextureNode* GetTextureNode() =0;
			virtual void SetTextureNode(_jGuiTextureNode* pTex) =0;
			virtual jGuiRenderStateObj* GetRenderState()=0;
			virtual BOOL ContainsPoint( POINT& pt ) =0;
			virtual RECT &GetRect() =0;
			virtual void SetRenderState(jGuiRenderStateObj*) =0;
			virtual int CallHandler(jGuiMessage *pMsg, bool bTriggeredByUser=true) =0;
			virtual int CallScriptHandler(jGuiMessage* pMsg) =0;
			virtual void UpdateRects(POINT po,bool isCallCB) =0;
			virtual UINT GetHotkey() 	=0;
			virtual bool CanHaveFocus() =0;
			virtual void SetTextColor( jGUICOLOR col )=0;
			virtual bool Render(  float fElapsedTime ) =0;
			virtual jIE* CustomPropertyNode() =0;
			virtual void OnHotkey(jGuiMessage* pMsg) =0;
			virtual jIGuiControl* GetCtrlAtPt_if( POINT &pt, IsWantThingFunc_t* pFunc,void* ) =0;
			virtual void ClearText() =0;
			virtual void CalcTextRect(RECT* rect) =0;
			virtual void SetCustomImage(cstr szImageFileName) =0;
			jSET_FLAG_INTERFACE_VIRTUAL(x, MouseOver, jBIT_0) \
				jSET_FLAG_INTERFACE_VIRTUAL(x, HasFocus, jBIT_1) \
				jSET_FLAG_INTERFACE_VIRTUAL(x, LButtonPress, jBIT_2) \
				jSET_FLAG_INTERFACE_VIRTUAL(x, RButtonPress, jBIT_3) \
				jSET_FLAG_INTERFACE_VIRTUAL(x, Tooltip, jBIT_4) \
				virtual float SetKeyAni_WithChilds(cstr szAnimationName) =0;
			virtual jIE* SetKeyAni(cstr szAnimationName) =0;
			virtual void StopKeyAni_WithChilds()=0;
			virtual jIE* PlayKeyAni_WithChilds()=0;
			virtual jIE* RPlayKeyAni_WithChilds()=0;
		};

		inline jIGuiControl* jGetCtrl(jIE* pE){ 	return (jIGuiControl*) pE->GetUserData();	}

	}
}



#endif //__jIGuiControl_h__
