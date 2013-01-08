/* file : jOrb.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-10-29 16:36:59
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jOrb_header__
#define __jOrb_header__
#pragma once

// ���� ifdef ����� DLL���� ���������ϴ� �۾��� ���� �� �ִ� ��ũ�θ� ����� 
// ǥ�� ����Դϴ�. �� DLL�� ��� �ִ� ������ ��� ����ٿ� ���ǵ� _EXPORTS ��ȣ��
// �����ϵǸ�, ������ DLL�� ����ϴ� �ٸ� ������Ʈ������ �� ��ȣ�� ������ �� �����ϴ�.
// �̷��� �ϸ� �ҽ� ���Ͽ� �� ������ ��� �ִ� �ٸ� ��� ������Ʈ������ 
// JORB_API �Լ��� DLL���� �������� ������ ����, �� DLL��
// �� DLL�� �ش� ��ũ�η� ���ǵ� ��ȣ�� ���������� ������ ���ϴ�.
#if 0
#ifdef JORB_EXPORTS
#define JORB_API __declspec(dllexport)
#else
#define JORB_API __declspec(dllimport)
#endif
#endif


#include "interface/jIOrb.h"
#include "jOrbNode.h"
#include "protocal/PT_OrbHost_Enum.h"
using namespace nMech::nNET::nOrbHost;
namespace nMech
{
	namespace nORB
	{
		class jOrb : public jIOrb
		{
		public:
			jINTERFACE_HEADER(jIOrb);
			
			nEVENT::jIMsgManager* m_pMM;
			jIOrb_system_callback_t* m_jIOrb_system_callback;
			void Call_jIOrb_system_callback(nORB::EOrbSystemCallbackType type,jIOrbNode* pON,tcstr name);

			void _Create(jIE* pE);
			void _Delete();
			nXML::jE m_docOrbConfig;
			nXML::jE m_eNetConfig;// xml/orb/Orb_NetConfig.xml
			HWND m_hWnd;
			std::vector<tstring> m_UsingService;

			nUtil::jCriticalSection m_jOrbNode_CS;
			//jLIST_TYPEDEF_map(jIP_Address,jOrbNode,m_jOrbNode);
			jLIST_TYPEDEF_YVECTOR(jOrbNode , m_jOrbNode);

			jOrbNode* OrbNode_push_back(jIPacketSocket_IOCP* pS, jIP_Address& ip 
				, tcstr orbServiceName,tcstr myName,bool isServerMode
				);
			jOrbNode* findByIP(jIP_Address& ip);

			#define jAUTO_LOCK_CS_m_jOr32bNode_CS_
			template <class _Predicate>
			void OrbNode_for_each(_Predicate __pred ) 
			{
				jAUTO_LOCK_CS_m_jOr32bNode_CS_;
				for( m_jOrbNode_it it = m_jOrbNode.begin() ; it ; ++it)	
					__pred(it);
			}
		};

	}//namespace nORB

}//namespace nMech
using namespace nMech::nORB;

extern jOrb g_jOrb;


JUTIL_API tcstr Get_Uniq_AppNicName();
#endif // __jOrb_header__

