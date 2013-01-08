/* file : jIGuiStage.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-12-27 22:46:50
title : 
desc : 

*/

#ifndef __jIGuiStage_header__
#define __jIGuiStage_header__
#pragma once

namespace nMech
{
	namespace nGUI
	{

		struct jIGuiControl;
		struct jIGuiDialog;
		struct _jGuiTextureNode;
		struct _jGuiFontNode;
		struct jGuiStageView;

#define jINTERFACE_jIGuiStage(x) public:	\
	virtual void Load(jIE*) ##x \
	virtual _jGuiTextureNode* GetTextureNode(StringID  id) ##x \
	virtual jGuiStageView* GetStageView() ##x \
	virtual _jGuiFontNode* GetFontNode(StringID id) ##x \
	virtual void ResetDevice() ##x \
	virtual void Render( float fElapsedTime ) ##x \
	virtual jIGuiControl* GetControlFocus() ##x \
	/* The control which has focus*/ \
	virtual jIGuiControl* GetControlPressed() ##x \
	/* The control currently pressed */	\
	virtual jIGuiControl* GetControlMouseOver() ##x \
	/* The control which is hovered over */ \
	virtual void RequestFocus( jIGuiControl* pControl ) ##x \
	virtual void ClearFocus() ##x \
	virtual void SetRefreshTime( float fTime ) ##x \
	virtual jID* GetDoc() ##x \
	virtual jIE* GetModalressList() ##x \
	virtual jIE* GetModalList() ##x \
	virtual jIGuiDialog* GetActiveDlg() ##x \
	virtual bool IsPopupDialog() ##x \
	virtual bool IsPopupDialog(jIGuiDialog *pDlg ) ##x \
	virtual cstr GetName() ##x \
	virtual void ClosePopupDlg(bool isPopupDlgClear =false) ##x \
	virtual jIGuiControl* FindCtrl(cstr szDlg , cstr szName) ##x \
	virtual jIGuiDialog* FindDlg(POINT po) ##x \
	virtual jIGuiDialog* FindDlg(cstr szDlg) ##x \
	/* ���� null�̸� priority dlg list�� ���� �����Ѱ��̴�. */ \
	virtual bool MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ##x \
	virtual void FrameMove(double fTime, float fElapsedTime) ##x \
	virtual void Save(int type=0) ##x \
	virtual void ShowDlg(jIGuiDialog* pDlg) ##x \
	virtual void HideDlg(jIGuiDialog* pDlg) ##x \
	virtual jIGuiDialog* ShowPopupDlg(jIGuiDialog* pDlg) ##x \
	virtual jIGuiDialog* ShowPopupDlg(cstr szDlg) ##x \
	virtual void		Refresh() ##x \
	virtual void SetXmlCursor(cstr szCursor) ##x \
	/* Ŀ�� : prototype xml���������� Ŀ�� �̸�*/	\
	virtual POINT GetMousePos() ##x \
	/* Ŀ�� ��ġ */ \
	virtual void SetMousePos(POINT po) ##x \
	virtual jIGuiDialog* GetDlgTooltip() ##x \
	/* ���� dialog*/ \
	virtual jID* GetDocSound() ##x \
	virtual jIE* PlaySound(cstr szControl) ##x \
	virtual jIE* PlaySound(cstr szControl,cstr szEvent) ##x \
	/* jGui�� gui_prototype.xml�� DEFAULT_SOUND_FILE	�� szControl = "jIGuiDialog.OnShow" */\
	/* *_* by ALo : 2006-01-02 14:59:01*/\
	virtual void RegistDlgAlwaysTop(jIGuiDialog* pC) ##x \
	virtual void UnRegistDlgAlwaysTop(jIGuiDialog*pC) ##x \
	/* *_* by ALo : 2006-02-07 */\
	virtual jIE* GetTexList() ##x \
	virtual jIE* GetFontList() ##x \
	virtual jIVar* GetButtonBlendRate() ##x \
	virtual jIE* Play_GUI_ANI_PLAY_LIST(cstr szName) ##x\
	virtual void Stop_GUI_ANI_PLAY_LIST(jIE* pePlayList) ##x\
	virtual void Reset_GUI_ANI_PLAY_LIST() ##x\

		jINTERFACE_END(jIGuiStage);

		inline jIGuiStage* GetjIGuiStage(jID* pE)
		{ 
			assert(!_tcscmp( pE->BaseI()->GetTagName() , _T("jGuiStage") ) );
			return (jIGuiStage*) pE->BaseI()->GetUserData();
		}


		//---------------------------------------------------------------
		struct jGuiStageView : public jRttiObj
			//----------------------------------------------------------------
		{
		public:
			jIGuiStage*   m_pStage;
			virtual jIGuiStage* GetStage(){ return m_pStage;	}
			virtual void SetStage(jIGuiStage* pD){ m_pStage=pD;}
			virtual void OnShowDlg(jIGuiDialog* pDlg){}
			virtual void OnHideDlg(jIGuiDialog* pDlg){}
			virtual void OnLoad(jIE* pE) {} // gui xml �ε��Ϸ��� ȣ���
			virtual void OnUnload() { 	} // stage �ε����� ����ȣ���
			virtual bool OnMsgProc(jGuiMessage* ) {return false;} // �Է¸޼���ó�� ������ ȣ���. �Է¸޼����� ���͸��Ҽ� ����.
			virtual void OnResetDevice() {}
			virtual void OnFrameMove(double fTime, float fElapsedTime) {}
			virtual void OnPreRender(float fElapsedTime ){} //Stage�������ϱ����� ȣ��
			virtual void	 OnRender( float fElapsedTime ) {} //Stage�������Ҵ� ȣ��
		};

	}
}

#endif // __jIGuiStage_header__
