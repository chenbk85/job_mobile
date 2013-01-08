/* file : jIOrb.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-10-29 16:20:25
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jIOrb_header__
#define __jIOrb_header__
#pragma once
#include "header/jInterface.h"
#include <boost/any.hpp>
#include "interface/xml/jIXml.h"


namespace nMech
{
	namespace nORB
	{
#if 0
#define for_each_SYSTEM_ORB_PACKET(X)\
	X(H_HELLO,"원격지 첫접속")\
	X(H_HELLO_OK,"원격지가 나의 접속에 응답")\
	X(H_DISCONNECT,"원격지가 접속해제되었을때 콜.")\
	X(H_NOTIFY_HWND,"원격지의 윈도핸들을 알려줄때")\
	X(H_SEND_LOG,"LOG 메세지전송")\

#endif
		enum EOrbSystemCallbackType
		{
			eUNKOWN_PACKET,//protocal xml에 등록이 안된 패킷
			eUNHANDLED_PACKET,// HANDLER가 등록이 안되어 있슴
		};

		struct jIOrbNode;
		typedef boost::function<void (jIOrbNode* , const boost::any lParam,const boost::any wParam)> Notify_callback_t;
		typedef const Notify_callback_t& Notify_callback_cr_t;
		typedef void jIOrb_system_callback_t(nMech::nORB::EOrbSystemCallbackType,nMech::nORB::jIOrbNode*,tcstr protocal);
		typedef void OrbNode_for_each_ft(jIOrbNode* pOrb,void*);


#define jINTERFACE_jIOrbNode(X) public:	\
	virtual bool IsRemoteServerMode() ##X\
	/* ORB_APP_LIST에서의 항목노드 */\
	virtual jIE* GetService() ##X \
	virtual tcstr GetRemoteAppName() ##X\
	virtual jID* GetProtocalDoc()##X\
	\
	/*원격이 실행중인지*/ \
	virtual bool IsRemoteOk()##X \
	virtual jIE* FindProtocal(cstr szName) ##X \
	/* orb관련 툴이 있으면 show/hide토글*/\
	virtual bool ShowTool()##X\
	\
	/* 원격에서 호출되는것을 시뮬레이션함.*/\
	virtual void LocalCall(jIE* pE) ##X\
	virtual void Send(jIE* peProtocal)##X \
	\
	/* 원격지에 있는 해당문서를 저장시킬때. */\
	virtual void SendSaveDoc(jID* pD)##X\
	virtual void Send_H_COPY_XML_ELEMENT(jIE* pE,cstr szProtocal=0,bool isInsertMode=false)##X\
	virtual void Send_XMLDel(jIE* pE,jIA* pA=0, cstr szPROTOCAL=0)##X\
	\
	/* 원격지에서는 H_SEND_LOG로 통보됨. type은 로그 메세지에서 0이면 Log() , 1이면 LogAdd()를 의미*/\
	virtual void Send_H_SEND_LOG(tcstr szMsg,uint8 type)##X\
	/* 해당 xml node의 변경사항을 원격지에 전달*/\
	virtual void Notify_H_CHANGE_XML_NODE(jIE* pE, jIA* pA =0 )##X\
	/* 해당 xml node의 새로운 값을 원격지로 부터 요청 */\
	virtual void Notify_H_GET_UPDATE_XML_NODE(jIE* pE, jIA* pA =0 )##X\
	/* szXml문서를 원격지로 부터 다운로드받은후 완료됬을때 event를 호출함 lParam = jID* , wParam = szXml이 활당됨*/\
	virtual void Notify_DownloadXml(cstr szXml ,  Notify_callback_cr_t  event)##X\
	virtual HWND GetRemoteWnd()##X\
	virtual HWND GetLocalWnd()##X\
	virtual void SetNotifyEvent(cstr id,Notify_callback_cr_t event )##X\

	jINTERFACE_END(jIOrbNode);


#define jINTERFACE_jIOrb(X) public:	\
		/* xml/orb/Orb_NetConfig.xml 를 리턴*/\
		virtual jID* GetDoc() ##X\
		virtual void Start(jIOrb_system_callback_t* func\
					,tcstr szConnectServerList /*서비스를 이용할 ORB_APP_LIST에서의 ORB이름을 "ORB_a;ORB_b"식으로 입력한다.*/\
					,tcstr szMyServiceName /* 내가 서비스를 할 ORB이름을 지정한다.순수 클라이언트이면 0을 입력*/\
					,tcstr netConfigXml=_T("xml\\orb\\Orb_NetConfig.xml")) ##X \
		virtual jIOrbNode* FindByServiceName(tcstr szName) ##X \
		virtual jIOrbNode* FindByRemoteName(tcstr szName) ##X \
		virtual void OrbNode_for_each(OrbNode_for_each_ft*,void*) ##X\
		\
		virtual void SetLocalWnd(HWND hWnd)##X\
		/*종료될때 원격지에 알린다. */\
		virtual void DisconnectAll() ##X \
		virtual bool RunTool(cstr szOrbName)##X\

	jINTERFACE_END(jIOrb);

	}//namespace nORB

	namespace nInterface{ extern JBASE_API nORB::jIOrb* g_pjIOrb;	}

	namespace nORB
	{	
		inline jIOrbNode* GetOrb_service(tcstr name)
		{
			return nInterface::g_pjIOrb ? nInterface::g_pjIOrb->FindByServiceName(name) : 0 ;
		}
		inline jIOrbNode* GetOrb_remote(tcstr name)
		{
			return nInterface::g_pjIOrb ? nInterface::g_pjIOrb->FindByRemoteName(name) : 0 ;
		}
	}

#define GetjIOrb()		if(nInterface::g_pjIOrb)nInterface::g_pjIOrb
#define jORB2(pOrb,X)		nORB::jIOrbNode* pOrb = nORB::GetOrb_service(X);
#define jORB2_void(pOrb,X)		nORB::jIOrbNode* pOrb = nORB::GetOrb_service(X);if(!pOrb) return;
#define jORB2_ret(pOrb,X,ret)		nORB::jIOrbNode* pOrb = nORB::GetOrb_service(X);if(!pOrb) return ret;

#define jORB(X)			nORB::jIOrbNode* p##X = nORB::GetOrb_service(_T(#X));
#define jORB_void(X)	jORB(X);if(!p##X) return;
#define jORB_ret(X,ret) jORB(X);if(!p##X) return ret;

#define jORB2_R(pOrb,X)		nORB::jIOrbNode* pOrb = nORB::GetOrb_remote(X);
#define jORB2_R_void(pOrb,X)		nORB::jIOrbNode* pOrb = nORB::GetOrb_remote(X);if(!pOrb) return;
#define jORB2_R_ret(pOrb,X,ret)		nORB::jIOrbNode* pOrb = nORB::GetOrb_remote(X);if(!pOrb) return ret;

#define jORB_R(X)			nORB::jIOrbNode* p##X = nORB::GetOrb_remote(_T(#X));
#define jORB_R_void(X)	jORB(X);if(!p##X) return;
#define jORB_R_ret(X,ret) jORB(X);if(!p##X) return ret;


	inline void jIOrb_system_callback(nORB::EOrbSystemCallbackType type,nMech::nORB::jIOrbNode* pOrb,tcstr protocal)
	{
		switch(type)
		{
		case nORB::eUNKOWN_PACKET:
			{
				jWARN(_T(" eUNKOWN_PACKET : %s=%s"),pOrb->GetService()->GetTagName(),protocal);

			}
			break;
		case nORB::eUNHANDLED_PACKET:
			{
				//jLOG_T(__T("pON->IsAlive() : %d") ,pOrb->IsRemoteOk());
				jWARN(_T(" eUNHANDLED_PACKET : %s=%s"),pOrb->GetService()->GetTagName(),protocal);
			}
			break;
		default:
			{
				jWARN(_T(" unkown  %s=%s"),pOrb->GetService()->GetTagName(),protocal);
			}
			break;
		}

	}


}//namespace nMech

#define ORB_protocal_handler_ARG nMech::nORB::jIOrbNode* m_pOrb,nMech::jIE* m_peArg
typedef void jIORB_protocal_handler_t(ORB_protocal_handler_ARG);

#define jORB_HANDLER(argORB_NAME,argPROTOCAL)\
struct _jJOIN_4(ORB_HANDLER_,argORB_NAME,_,argPROTOCAL)\
{\
	static void call(ORB_protocal_handler_ARG);\
	_jJOIN_4(ORB_HANDLER_,argORB_NAME,_,argPROTOCAL)(){\
	tname256_t buf;jt_sprintf(buf,_T("ORB_HANDLER_%s"),jS(argORB_NAME));\
	jBase::RegistNamedPointer(buf,jS(argPROTOCAL),call);}\
};static _jJOIN_4(ORB_HANDLER_,argORB_NAME,_,argPROTOCAL) _jJOIN_4(s_ORB_HANDLER_,argORB_NAME,_,argPROTOCAL);\
void _jJOIN_4(ORB_HANDLER_,argORB_NAME,_,argPROTOCAL)::call(ORB_protocal_handler_ARG)\



#define jIOrb_XPATH_INIT() \
	jIE* m_peXPATH = m_peArg->Find(jS(XPATH) );\
	jIE* m_peFind=0; jIA* m_paFind=0; 	jID* m_pD =0; \
	if(m_peXPATH)	m_pD = m_peXPATH->XPathFromThis(&m_peFind, &m_paFind);\
	if(!m_peFind) return;





#endif // __jIOrb_header__
