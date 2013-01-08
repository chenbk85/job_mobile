/* file : jIGuiDefine.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-12-27 20:30:57
title : 
desc : 

*/

#ifndef __jIGuiDefine_header__
#define __jIGuiDefine_header__
#pragma once

namespace nMech
{
	namespace nEVENT
	{
		struct jEventMessage;
	}
	namespace nGUI
	{

		//--------------------------------------------------------------------------------------
		// Defines and macros 
		//--------------------------------------------------------------------------------------

#ifndef WM_XBUTTONDOWN
#define WM_XBUTTONDOWN 0x020B // (not always defined)
#endif
#ifndef WM_XBUTTONUP
#define WM_XBUTTONUP 0x020C // (not always defined)
#endif
#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x020A // (not always defined)
#endif
#ifndef WHEEL_DELTA
#define WHEEL_DELTA 120 // (not always defined)
#endif

#define jRET_OK 1
#define jRET_NO -1
#define jRET_NOTTING 0

		//---------------------------------------------------------------
		// jIGuiControl을 상속받은 사용자컨트롤 클래스정의용.
		//----------------------------------------------------------------
#ifndef jGUI_RTTI_DECLEAR
#define jGUI_RTTI_DECLEAR(className , parentName) \
	public:\
	virtual void Init(jIE*);\
	virtual void Create();\
	virtual void Destroy();\
	typedef parentName parent_t;\
	typedef parentName parentCtrl_t;\
	jDECLARE_RTTIOBJ(className );
#endif
#ifndef jGUI_RTTI_DEFINE
#define jGUI_RTTI_DEFINE(className,obj,slot) jDEFINE_RTTIOBJ(className,jGui,obj,slot);
#endif

		typedef nEVENT::jEventMessage jGuiMessage;

		typedef int jIGui_EventHandler(jGuiMessage*);
		struct jGuiHandlerInfo
		{
			cstr m_szClass; // dialog name
			cstr m_szEventName;
			jIGui_EventHandler* m_pFunc;
			jGuiHandlerInfo(cstr c,cstr name, jIGui_EventHandler* pF): m_szClass(c),m_szEventName(name),m_pFunc(pF){ 	}
			jGuiHandlerInfo():m_szClass(0),m_szEventName(0),m_pFunc(0){ 	}
		};
		class jCOMMON_API jGuiHandlerInfoList
		{
		public:
			void push_back(cstr szStage, jGuiHandlerInfo a);
			void GotoBegin();
			jGuiHandlerInfo* Get();
			bool IsEnd();
			bool Find(cstr);
			static jGuiHandlerInfoList& This();
		};

		enum EGuiRunMode
		{
			eRUN_MODE,
			eEDIT_MODE,
			eGROUP_MODE,
		};

		struct jIGuiTool
		{
			enum EResizeType
			{
				EResizeType_BEGIN,
				eWIDTH,
				eHEIGHT,
				eWH,
				EResizeType_MAX
			};

		};
#ifndef RENDER_DEVICE_t
#define RENDER_DEVICE_t void*
#endif


		/// edit box, static ...

		//---------------------------------------------------------------
		// jGuiStage를 상속받은 클래스에서의 핸들러 함수 초기화
		// 초기화되는 지역변수는 pStageView ,pStage , pDlg , pCtrl , pMsg
		//----------------------------------------------------------------
#define jHANDLER_INIT_CONTROL(stageview)  \
	if(!pMsg->peReceiver) return 0; \
	jIGuiControl* pCtrl = jGetCtrl(pMsg->peReceiver);\
	jIGuiDialog *pDlg = jGetDlgI(pMsg->peReceiver->GetRoot());\
	jIGuiStage* pStage = pDlg->GetStage();\
	stageview* pStageView= (stageview*)(pStage->GetStageView()); \
	/*
		if(g_IsGuiDebug){  \
		if(pMsg->uMsg!=WM_MOUSEMOVE)jTRACE(_T("(STAGE)%s::Hdr_%s_%s(msg=%d,wParam=%d);" \
		, pStage->GetName()  , pDlg->BaseI()->GetName() , pCtrl->GetName() ,pMsg->uMsg ,pMsg->wParam); \
		} 
		/*
		if(_tcscmp(pCtrl->GetjIE()->GetTagName() , #type) )\
		jLOG(_T("\005ERROR:don't match control type : %s jHANDLER_INIT_DLGVIEW(%s) != %s ")\
		, #stage ,pCtrl->GetjIE()->GetTagName() , #type);
		*/

		//--------------------------------------------------------------- 
		// jGuiDialogView를 상속받은 클래스에서의 핸들러 함수 초기화
		// pStage , pDlg , pCtrl , pMsg ,pDlgView 를 정의 하고 초기화 해줌.
		//----------------------------------------------------------------
#define jHANDLER_INIT_DLGVIEW(dlgClass)  \
	if(!pMsg->peReceiver) return 0; \
	jIGuiControl* pCtrl = (jIGuiControl*)jGetCtrl(pMsg->peReceiver);\
	jIGuiDialog *pDlg = jGetDlgI(pMsg->peReceiver->GetRoot());\
	dlgClass* pDlgView = (dlgClass*)pDlg->GetDlgView(); 
		/*
		if(_tcscmp(pCtrl->GetjIE()->GetTagName() , #type) )\
		jLOG(_T("\005ERROR:don't match control type : %s jHANDLER_INIT_DLGVIEW(%s) != %s ")\
		, #dlgClass ,pCtrl->GetjIE()->GetTagName() , #type);
		*/

		//---------------------------------------------------------------
		//   jGuiStage , jGuiDialogView를 상속받은 class의 cpp 에서 핸들러 등록용.
		//----------------------------------------------------------------
#define jGUI_HANDLER_DEFINE(c,dlg,x) 			extern int _jJOIN_4(jGuiEvent_,c,dlg,x)(jGuiMessage* pMsg);\
		struct _jJOIN_4(jGuiEvent_binder,c,dlg,x){_jJOIN_4(jGuiEvent_binder,c,dlg,x)(){\
		jGuiHandlerInfoList::This().push_back( 	_T(#c),jGuiHandlerInfo(_T(#dlg),_T(#x),_jJOIN_4(jGuiEvent_,c,dlg,x) ) );\
		}};static _jJOIN_4(jGuiEvent_binder,c,dlg,x) _jJOIN_4(jGuiEvent_binder_impl_,c,dlg,x);\
		int _jJOIN_4(jGuiEvent_,c,dlg,x)(jGuiMessage* pMsg)


#define jGUI_HANDLER_DEFINE_LINK(stage,dlg,ctr, exist_ctrl) \
	extern int _jJOIN_4(jGuiEvent_,stage,dlg,exist_ctrl)(jGuiMessage* pMsg);\
		struct _jJOIN_5(jGuiEvent_binder,stage,dlg,exist_ctrl){ _jJOIN_5(jGuiEvent_binder,stage,dlg,exist_ctrl)(){ \
		jGuiHandlerInfoList::This().push_back( 	_T(#stage), jGuiHandlerInfo(_T(#dlg),_T(#ctr),_jJOIN_4(jGuiEvent_,stage,dlg,exist_ctrl) ) );\
		};static _jJOIN_5(jGuiEvent_binder,stage,dlg,exist_ctrl) _jJOIN_5(jGuiEvent_binder_impl,stage,dlg,exist_ctrl);


		//---------------------------------------------------------------
		// jGuiDialogView를 상속받은 사용자 클래스정의용.
		//----------------------------------------------------------------
#define jGUI_DLGVIEW_RTTI_DECLEAR(className , parentName) \
		public:\
		virtual void Init(jIE*);\
		virtual void Create();\
		virtual void Destroy();\
		typedef parentName parent_t;\
		jDECLARE_RTTIOBJ(className );

	}
}

#endif // __jIGuiDefine_header__
