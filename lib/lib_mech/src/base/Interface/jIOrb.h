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
	X(H_HELLO,"������ ù����")\
	X(H_HELLO_OK,"�������� ���� ���ӿ� ����")\
	X(H_DISCONNECT,"�������� ���������Ǿ����� ��.")\
	X(H_NOTIFY_HWND,"�������� �����ڵ��� �˷��ٶ�")\
	X(H_SEND_LOG,"LOG �޼�������")\

#endif
		enum EOrbSystemCallbackType
		{
			eUNKOWN_PACKET,//protocal xml�� ����� �ȵ� ��Ŷ
			eUNHANDLED_PACKET,// HANDLER�� ����� �ȵǾ� �ֽ�
		};

		struct jIOrbNode;
		typedef boost::function<void (jIOrbNode* , const boost::any lParam,const boost::any wParam)> Notify_callback_t;
		typedef const Notify_callback_t& Notify_callback_cr_t;
		typedef void jIOrb_system_callback_t(nMech::nORB::EOrbSystemCallbackType,nMech::nORB::jIOrbNode*,tcstr protocal);
		typedef void OrbNode_for_each_ft(jIOrbNode* pOrb,void*);


#define jINTERFACE_jIOrbNode(X) public:	\
	virtual bool IsRemoteServerMode() ##X\
	/* ORB_APP_LIST������ �׸��� */\
	virtual jIE* GetService() ##X \
	virtual tcstr GetRemoteAppName() ##X\
	virtual jID* GetProtocalDoc()##X\
	\
	/*������ ����������*/ \
	virtual bool IsRemoteOk()##X \
	virtual jIE* FindProtocal(cstr szName) ##X \
	/* orb���� ���� ������ show/hide���*/\
	virtual bool ShowTool()##X\
	\
	/* ���ݿ��� ȣ��Ǵ°��� �ùķ��̼���.*/\
	virtual void LocalCall(jIE* pE) ##X\
	virtual void Send(jIE* peProtocal)##X \
	\
	/* �������� �ִ� �ش繮���� �����ų��. */\
	virtual void SendSaveDoc(jID* pD)##X\
	virtual void Send_H_COPY_XML_ELEMENT(jIE* pE,cstr szProtocal=0,bool isInsertMode=false)##X\
	virtual void Send_XMLDel(jIE* pE,jIA* pA=0, cstr szPROTOCAL=0)##X\
	\
	/* ������������ H_SEND_LOG�� �뺸��. type�� �α� �޼������� 0�̸� Log() , 1�̸� LogAdd()�� �ǹ�*/\
	virtual void Send_H_SEND_LOG(tcstr szMsg,uint8 type)##X\
	/* �ش� xml node�� ��������� �������� ����*/\
	virtual void Notify_H_CHANGE_XML_NODE(jIE* pE, jIA* pA =0 )##X\
	/* �ش� xml node�� ���ο� ���� �������� ���� ��û */\
	virtual void Notify_H_GET_UPDATE_XML_NODE(jIE* pE, jIA* pA =0 )##X\
	/* szXml������ �������� ���� �ٿ�ε������ �Ϸ������ event�� ȣ���� lParam = jID* , wParam = szXml�� Ȱ���*/\
	virtual void Notify_DownloadXml(cstr szXml ,  Notify_callback_cr_t  event)##X\
	virtual HWND GetRemoteWnd()##X\
	virtual HWND GetLocalWnd()##X\
	virtual void SetNotifyEvent(cstr id,Notify_callback_cr_t event )##X\

	jINTERFACE_END(jIOrbNode);


#define jINTERFACE_jIOrb(X) public:	\
		/* xml/orb/Orb_NetConfig.xml �� ����*/\
		virtual jID* GetDoc() ##X\
		virtual void Start(jIOrb_system_callback_t* func\
					,tcstr szConnectServerList /*���񽺸� �̿��� ORB_APP_LIST������ ORB�̸��� "ORB_a;ORB_b"������ �Է��Ѵ�.*/\
					,tcstr szMyServiceName /* ���� ���񽺸� �� ORB�̸��� �����Ѵ�.���� Ŭ���̾�Ʈ�̸� 0�� �Է�*/\
					,tcstr netConfigXml=_T("xml\\orb\\Orb_NetConfig.xml")) ##X \
		virtual jIOrbNode* FindByServiceName(tcstr szName) ##X \
		virtual jIOrbNode* FindByRemoteName(tcstr szName) ##X \
		virtual void OrbNode_for_each(OrbNode_for_each_ft*,void*) ##X\
		\
		virtual void SetLocalWnd(HWND hWnd)##X\
		/*����ɶ� �������� �˸���. */\
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
