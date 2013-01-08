	/* 
	filename:	jIGui.h
	coder	:	Cho Hyun Min (icandoit@wemade.com) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	2005-01-14 오전 10:23:36
	title	:	
*/


#ifndef __jIGui_h__
#define __jIGui_h__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000
#include "base/jMsgManager.h"
#include "base/jRtti.h"

//#include "gui\\jIGuiControl.h"
#include "interface/gui/jIGuiDefine.h"

namespace nMech
{

	namespace nGUI
	{

		struct jIGuiDialog;

		struct jIGuiControl;

		struct jIGuiStage;
		struct jIGuiRender;

#define jINTERFACE_jIGui(tag32) public:	\
	virtual void SetLocalWnd( HWND hWnd) ##tag32 \
	virtual void OnCreateDevice( void* pd3dDevice) ##tag32 \
	virtual void OnRender()##tag32 \
	virtual void OnFrameMove() ##tag32 \
	virtual void Close() ##tag32 \
	/* 프로그램 종료직전 콜 */ \
	virtual void OnLostDevice() ##tag32 \
	/* windowed/full screen toggles. Resources created in the OnCreateDevice callback  */\
	/* should be released here, which generally includes all D3DPOOL_MANAGED resources. */\
	virtual void OnResetDevice() ##tag32 \
	virtual void OnDestroyDevice() ##tag32 \
	virtual bool OnMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ##tag32 \
	virtual jID* GetMsgDoc() ##tag32 \
	virtual void ChangeStage(tcstr szStageXml) ##tag32 \
	virtual void* GetInfo(int infoType, void*) ##tag32 \
	virtual void SetScriptEvent(jIGui_EventHandler pFunc,void*) ##tag32 \
	virtual void SetCursorShow(bool is) ##tag32 \
	virtual bool IsEnable() ##tag32 \
	virtual POINT GetMousePos() ##tag32 \
	virtual void DrawText(int argX,int argY,cstr szText,int iSize, DWORD color) ##tag32 \
	virtual int &IsActivate() ##tag32 \
	virtual jIGuiStage* GetCurrStage() ##tag32 \
	virtual bool OpenStageFile(fname_t buf) ##tag32 \
	virtual jIGuiRender* GetRender() ##tag32 \
	virtual bool GetFlagBlockOtherEvent() ##tag32 \
	virtual void SetFlagBlockOtherEvent(bool iSet) ##tag32 \
	\
	/*아래는  jGuiTool 관련 */\
	virtual jIGuiTool* GetTool() ##tag32 \
	virtual int &ToolGetMode() ##tag32 \
	virtual void ToolToggleEditMode() ##tag32 \
	virtual bool ToolStageFileOpenDlg(tname256_t fname) ##tag32 \
	virtual void ToolRun() ##tag32 \
	virtual void ToolShowToggle() ##tag32 \
	virtual void ToolClose() ##tag32 \
	virtual RENDER_DEVICE_t GetRenderDevice() ##tag32 \
	virtual HWND GetHWnd() ##tag32 \
	virtual jIGuiControl* GetFocusControl() ##tag32 \
	virtual jIGuiControl* GetPressedControl() ##tag32 \
	virtual jIGuiControl* GetMouseOverControl() ##tag32 \
	virtual bool CallMsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ##tag32 \
	\
	virtual POINT &GetRealScreenWH() ##tag32 \
	virtual POINT &GetVirtualScreenWH() ##tag32 \
	virtual RECT GetRToVRect(const RECT& r) ##tag32 \
	/* real to virtual pos*/\
	virtual POINT GetRToVPos(const POINT& r) ##tag32 \
	/*  virtual to real pos*/\
	virtual POINT GetVToRPos(const POINT& r) ##tag32 \

	jINTERFACE_END(jIGui);

	}
	namespace nInterface
	{
		extern JBASE_API nGUI::jIGui* g_pjIGui;
	}
	#define Get_jIGui() if(nMech::nInterface::g_pjIGui)nMech::nInterface::g_pjIGui
	namespace nGLOBAL
	{
		extern JBASE_API jID* g_pDocGui; ///xml\jGui.xml
	}
}

#include "jIGuiRender.h"

#include "jIGuiCheckBox.h"
#include "jIGuiRadioButton.h"
#include "jIGuiComboBox.h"
#include "jIGuiControl.h"
#include "jIGuiDialog.h"
#include "jIGuiListBox.h"
#include "jIGuiScrollBar.h"
#include "jIGuiSlider.h"
#include "jIGuiStage.h"
#include "jIGuiStaticVar.h"


#endif //__jIGui_h__
