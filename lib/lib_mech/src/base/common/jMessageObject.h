/* file : jIMessageObject.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-12-02 12:32:35
title : 
desc : 

*/

#ifndef __jIMessageObject_header__
#define __jIMessageObject_header__
#pragma once

#include "base\\jMsgManager.h"
#include "base/jRTTI.h"

namespace nMech
{
	namespace nEVENT
	{
		struct jIMessage ;
		struct jCOMMON_API jIMessageObject  ;
		struct _jIMessage : public jRttiObj{	virtual int Call(jIMessageObject*,jIE*,jIMessage*)=0;};

#define jORB_MESSAGE_RECEIVER(LOCAL_NAME,PACKET) \
		struct _jJOIN_(LOCAL_NAME,PACKET) : public _jIMessage \
		{	jDECLARE_RTTIOBJ(_jJOIN_(LOCAL_NAME,PACKET));\
		int  Call(jIMessageObject*,jIE*,jIMessage*);}; jDEFINE_RTTIOBJ_BY_SCOPE_NICK( _jJOIN_(LOCAL_NAME,PACKET) , LOCAL_NAME,PACKET,1,1 ); \
		int _jJOIN_(LOCAL_NAME,PACKET)::Call(jIMessageObject* m_pMsgObj , jIE* m_peMsgSpec ,jIMessage* m_pMsg)

		/*
		jORB_MESSAGE_RECEIVER�� ��뿹

		jORB_MESSAGE_RECEIVER(jIClientEntity, Attack)
		{
		m_pMsgObj --> jIClientEntity��ü
		m_peMsg -> xml\game\jMessageObject.xml���� jIClientEntity�� �׸��� �ϳ�.
		}

		*/

		struct _jxORBMsgRegister
		{
			cstr szScope;
			int iDepth;
			_jxORBMsgRegister(cstr szScope1 ,int iStartDepth ):szScope(szScope1), iDepth(iStartDepth){ }
			void operator()(jIE* pE)
			{
				//depth > 2�̰� element type�϶���.
				if(pE->GetDepth() != iDepth) return;
				if(pE->GetType() !=jIVar::ETelement) return;
				_jIMessage* pPacket = (_jIMessage*)jRTTI::New(pE->GetTagName() , szScope);
				if(pPacket)
					pE->SetUserData(pPacket);
			}
		};

		struct jCOMMON_API jIMessageObject  
		{
			static void Create(cstr szName); //JBASE_API void jMech_Init(cstr szApp)������ ȣ���.
			static jIMsgManager* GetMsgManager();
			typedef jIMessageObject parent_t;
			static void Init(jIE* peMsgList);

			// �Ʒ��� 3������ �׻� �����ǵǾ���.
			virtual jIE* GetMsgNode(){ return 0;}
			virtual int ProcessMessage(jIE* pE, void* vData );
			virtual bool jQueryInterface(StringID id,void** ppInterface){ return false;}

		};
	}
}



#endif // __jIMessageObject_header__
