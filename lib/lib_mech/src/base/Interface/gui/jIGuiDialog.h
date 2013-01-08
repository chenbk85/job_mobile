/* file : jIGuiDialog.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-12-27 21:43:39
title : 
desc : 

*/

#ifndef __jIGuiDialog_headeasdf232sr__
#define __jIGuiDialog_headeasdf232sr__
#pragma once

#include "base/jXmlDictionary.h"

namespace nMech
{
	namespace nGUI
	{

		class jGuiGroup;
		class jGuiDialog;
		struct jIGuiControl;
		struct jGuiDialogView;

#define jINTERFACE_jIGuiGroup(x) public:	\
	virtual jIGuiControl* BaseI() ##x \
	virtual void ClearRadioButtonGroup( ) ##x \
	virtual jIGuiControl* GetActiveRadio() ##x \
	virtual void ActivateTabGroup(jIE* peTab,jIE* peGroup) ##x \
	virtual jIE* GetActiveTabButton() ##x \

		jINTERFACE_END(jIGuiGroup);

#define jINTERFACE_jIGuiDialog(x) public:	\
	virtual void* GetInterface(StringID id) ##x \
	virtual jIGuiControl* BaseI() ##x \
	virtual jIGuiGroup* BaseGroupI() ##x \
	virtual jIGuiStage* GetStage() ##x \
	virtual cstr GetDlgViewName() ##x \
	virtual jGuiDialogView* GetDlgView()	##x \
	virtual jIGuiControl* Find(cstr szID) ##x \
	virtual void SetControlEnabled( cstr   ID, bool bEnabled ) ##x \
	virtual jGuiDialog* Base() ##x \

		jINTERFACE_END(jIGuiDialog);


		//---------------------------------------------------------------
		struct jGuiDialogView : public jRttiObj
			//----------------------------------------------------------------
		{
		public:
			jIGuiDialog*   m_pDlg;
			virtual jIGuiDialog* GetDlg(){ return m_pDlg;	}
			virtual void SetDlg(jIGuiDialog* pD){ m_pDlg=pD;}

			virtual void OnShow(){} // dialog가 Show될때 호출됨
			virtual void OnHide(){} // dialog가 Hide될때 호출됨
			virtual void		OnPreRender(  float fElapsedTime ){ 	} // 이 Dialog가 Rendering될때 호출됨.
			virtual void		OnRender(  float fElapsedTime ){ 	} // 이 Dialog가 Rendering될때 호출됨.
			virtual void OnResetDevice(){}
			virtual void Refresh(){	}
			virtual bool OnMsgProc( jGuiMessage* pMsg){ return false;}

			virtual void Init(jIE* ){ 	}
			virtual void Close(){ 	}

		};
		inline jIGuiDialog* jGetDlgI(jIE* pE)
		{ 	
			assert( !_tcscmp(pE->GetTagName() , _T("jGuiDialog") ));
			return (jIGuiDialog*)jGetCtrl(pE)->GetInterface(jx(jIGuiDialog)); 
		}

	}
}


#endif // __jIGuiDialog_headeasdf232sr__
