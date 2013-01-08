
/* 
filename:	jeORB.h
coder	:	Cho Wook Rea (mech12@dreamwiz.com)(icq:74456993) 
comp.	:	EmailPet 
compiler:	vc++ 6.0
date	:	2002-02-01���� 10:33:21
title	:	
*/


#ifndef __IEORB_CopyData_hasdf12333333__
#define __IEORB_CopyData_hasdf12333333__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000


#include "base/jRtti.h"
#include "base/jXmlDictionary.h"

namespace nMech
{
	namespace nUtil
	{
		struct jMemoryChunk;
	}

	namespace nXML_ORB
	{
		struct jIORB;
		struct _jeORB_packet : public jRttiObj{	virtual void Call(jIORB*,jIE*)=0;};

#define jORB_PACKET_RECEIVER(LOCAL_NAME,PACKET) \
		struct _jJOIN_(LOCAL_NAME,PACKET) : public nMech::nXML_ORB::_jeORB_packet \
		{	jDECLARE_RTTIOBJ(_jJOIN_(LOCAL_NAME,PACKET));\
		void Call(nMech::nXML_ORB::jIORB*,nMech::jIE*);}; jDEFINE_RTTIOBJ_BY_SCOPE_NICK( _jJOIN_(LOCAL_NAME,PACKET) , LOCAL_NAME,PACKET,1,1 ); \
		void _jJOIN_(LOCAL_NAME,PACKET)::Call(nMech::nXML_ORB::jIORB* m_pOrb,nMech::jIE* m_peArg)

#define jORB_XPATH_INIT() \
	jIE* m_peXPATH = m_peArg->Find(jS(XPATH));\
	jIE* m_peFind=0; jIA* m_paFind=0; 	jID* m_pD =0; \
	if(m_peXPATH)	m_pD = m_peXPATH->XPathFromThis(&m_peFind, &m_paFind);\
	if(!m_peFind) return;

		/* *_* by icandoit : 2005-08-25 18:30:48

		struct _jORB_NotifyInfo
		{
		jIORB* m_pOrb;
		jIE* m_peArg;
		jID* m_pD;
		jIE*	m_pE;
		jIA* m_pA;
		};
		enum EjORB_NotifyAction
		{
		eONA_change,
		eONA_delete,
		eONA_move,
		eONA_insert,//not use
		};

		struct _jeORB_Notify : public jRttiObj{	virtual void Call(_jORB_NotifyInfo* pInfo,int notifyAction)=0;};

		#define jORB_XML_CHANGE_RECEIVER(LOCAL_NAME,PACKET) \
		struct _jJOIN_(LOCAL_NAME,PACKET) : public _jeORB_Notify \
		{	jDECLARE_RTTIOBJ(_jJOIN_(LOCAL_NAME,PACKET));\
		void Call(jIORB*,jIE*);}; jDEFINE_RTTIOBJ_BY_SCOPE_NICK( _jJOIN_(LOCAL_NAME,PACKET) , LOCAL_NAME,PACKET,1,1 ); \
		void _jJOIN_(LOCAL_NAME,PACKET)::Call(jIORB* m_pOrb,jIE* m_peArg)
		*/ //*_* by icandoit : 2005-08-25 18:30:51
		//----------------------------------------------------------------
		struct   jIORB
			//----------------------------------------------------------------
		{
		public:
			virtual jID* GetDoc()=0;
			virtual jIE* GetRemote()=0;
			virtual jIE* GetLocal()=0;

			virtual void SetLocalWnd(HWND hWnd)=0;
			virtual HWND GetRemoteWnd()=0;
			virtual HWND GetLocalWnd()=0;

		public:
			virtual tcstr GetRemoteAppName()=0; // ����Ʈ��ü�� �ĺ����̴�. �� �̸����� HWND�� �˾Ƴ���.
			virtual tcstr GetLocalAppName()=0; // ����Ʈ�� ��ϵǾ� �ִ� �ڽ��� �ĺ����̴�.
			// �� �̸����� ����Ʈ������ �ڽ��� HWND�� �˾Ƴ���.
			virtual tcstr GetRemoteName()=0; // ����Ʈ��ü�� ORB.XML������ �����������̺��̸�.
			virtual tcstr GetLocalName()=0;

			virtual jIE* FindProtocal(tcstr szName)=0;

			virtual void Send_XMLDel(jIE* pE,jIA* pA=0, cstr szPROTOCAL=0)=0;
			virtual void Send(jIE* peProtocal)=0;

			// ���ݿ��� ȣ��Ǵ°��� �ùķ��̼���.
			virtual int LocalCall(jIE* pE)=0;
			//������ ����������
			virtual bool IsRemoteOk()=0;
			// �������� �ִ� �ش繮���� �����ų��.
			virtual void SendSaveDoc(jID* pD)=0;
			virtual bool RunTool()=0;
			// orb���� ���� ������ show/hide���
			virtual bool ShowTool()=0;

			typedef boost::function<void (jIORB* , const boost::any lParam,const boost::any wParam)> Notify_callback_t;
			typedef const Notify_callback_t& Notify_callback_cr_t;

			virtual void Notify_XmlDocList(const Notify_callback_t& event) =0;
			// �������� �ε��� xml��������Ʈ�� �޴´� xml�����̸��� �ϳ����������� event�� ȣ���
			// lParam = cstr , �����̸�

			virtual void Notify_DownloadXml(cstr szXml , Notify_callback_cr_t event)=0;
			// szXml������ �������� ���� �ٿ�ε������ �Ϸ������ event�� ȣ����
			// lParam = jID* , wParam = szXml�� Ȱ���

			virtual nUtil::jMemoryChunk* GetNotifyBuffer(char* buf, int bufSize)=0;
			virtual void ReleaseNotifyBuffer(nUtil::jMemoryChunk* )=0;

			virtual void Notify(StringID ,nUtil::jMemoryChunk* mc,Notify_callback_cr_t event )=0;
			// �������� StringID��ȣ�� �ش��ϴ� �̺�Ʈ�� ȣ���Ѵ�
			// mc���� �ش� �������ݹ�ȣ�� �ش��ϴ� ������ ����
			// �ش� ������ event�� �޴´�

			virtual void Send(nUtil::jMemoryChunk& mc)=0;
			virtual void SetNotifyEvent(StringID ,Notify_callback_cr_t event )=0;


		};

		//--------------------------------------------------------------------------
		struct jIXmlORB
			//--------------------------------------------------------------------------
		{
			typedef boost::function<void (jIORB* , HWND) > for_each_func_t;

			virtual void Recv(	HWND hWndRecv, HWND hWndSender , COPYDATASTRUCT* pCD)=0;
			// Create() : ORB������ ORB��ü�� ������ SHAREŸ���϶��� Ÿ�� Ŭ���̾�Ʈ�� �г����� �Է��ؾ���.

			// ���� ���ӵǾ� �ִ� orb�� ���� ȣ��
			virtual void for_each_LiveOrb(for_each_func_t& pFunc)=0;
			virtual jIORB* find(cstr szRemoteAppName)=0;

			virtual void SetLocalWnd(HWND)=0;


			//---------------------------------------------------------------
			void SetXPath(jIE* pePacket , jIE* pE, jIA* pA)
			{
				jIE* pePa = pePacket->Find(_T("XPATH"));
				pePa->SetXPathContents(pE, pA);
			}

			//---------------------------------------------------------------
			jID* GetXPath(jIE* pePacket, jIE**pE, jIA**pA)
			{
				jIE* pePA = pePacket->Find(jS(XPATH) );
				return pePA->XPathFromThis(pE, pA);
			}

			//---------------------------------------------------------------
			jIE* FindProtocal(jID* pD , cstr szName)
			{
				jIORB* pORB = GetORB(pD);
				if(!pORB) return 0 ;
				return pORB->FindProtocal(szName);
			}

			//---------------------------------------------------------------
			void Send(jID* pD , jIE* pE)
			{
				jIORB* pORB = GetORB(pD);
				if(!pORB) return;
				pORB->Send(pE);
			}
			jIORB* GetORB(jID* pD)	{ 		return (jIORB*)pD->BaseI()->GetUserData();	}

		};

	}//nXML_ORB
	namespace nInterface
	{
		extern JBASE_API nXML_ORB::jIXmlORB* g_pjIXmlORB;
	}

}

#endif //__IEORB_CopyData_hasdf12333333__

