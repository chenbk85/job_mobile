/* file : jIPacketDispatch.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2009-12-08 12:50:26
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jIPacketDispatch_header__
#define __jIPacketDispatch_header__
#pragma once


namespace nMech
{
	namespace nNET
	{

		struct jNamedEventNode
		{
			nMech::int32	m_id;
			nMech::StringID m_jStringID;
			nMech::tcstr	m_szName;
			tcstr			thread_name;
		};
		struct jNamedEventTable
		{
			typedef void for_each_func_t(jNamedEventNode*,jIE* pE,struct jIPacketDispatchTable* pTable);
			virtual jNamedEventNode* GetByNum(nMech::int32 i)=0;
			virtual jNamedEventNode* GetByID(nMech::StringID& id)=0;
			virtual jNamedEventNode* GetByName(nMech::tcstr sz)=0;
			virtual jNamedEventNode* Insert(nMech::int32 idx,nMech::tcstr name,tcstr thread_name)=0;
			virtual void for_each(for_each_func_t*,jIE* pE,struct jIPacketDispatchTable* pTable)=0;
		};
		//typedef jNamedEventTable jPlugInHelpTableList;// old version 때문에. 향후 삭제

		struct _jNamed_Event_Handler;// 사용하는쪽에서 정의한다.
		struct jIPacketDispatchTable
		{
			jIE* m_pE;
			struct jNamedEventTable* m_pHT;
			virtual const _jNamed_Event_Handler* find(nMech::int32 id) const =0;
			virtual void insert(nMech::int32 id, _jNamed_Event_Handler* pNEH)=0;
		};

		#define jINTERFACE_jIPacketDispatch(X) public:	\
			virtual jIPacketDispatchTable* Regist_NamedEvent(jIE* pePlugInNode) ##X \
			virtual jIPacketDispatchTable* Regist_NamedEvent_ByTag(jIE*peSocketNode) ##X \
			virtual jIPacketDispatchTable* Regist_NamedEvent_Direct(tcstr szPlugInName,tcstr szHEADER) ##X \
			virtual jIPacketDispatchTable* Regist_NamedEvent_ByTag_Direct(tcstr szPlugInName,tcstr szHEADER) ##X \
			virtual jIPacketDispatchTable* Find(tcstr szPlugInName,tcstr szHEADER=0) ##X\
			virtual jNamedEventTable*		GetNamedEventTable(nMech::tcstr szPlugIn_HEADER) ##X \

		jINTERFACE_END_BASE1(jIPacketDispatch, nInterface::jIInterface);

		// 사용법.
		//	jIPacketDispatch* pjIPacketDispatch= jCREATE_INTERFACE(nMech::nNET::jIPacketDispatch);
		//	SAFE_RELEASE(pjIPacketDispatch);

		// 또는 
		// jCREATE_INTERFACE_AUTO(pjIPacketDispatch, nMech::nNET::jIPacketDispatch);

	}//namespace nNET

}//namespace nMech


#define jNAMED_EVENT_BEGIN(PLUGIN)namespace ns_##PLUGIN{ static nMech::tcstr _jPLUGIN_NAME_ = jS(PLUGIN); namespace Impl
#define jNAMED_EVENT_END(PLUGIN)	}


#define jNAMED_EVENT_RECEIVER(PROTOCAL) \
struct _jJOIN_2(jNamedEvent_,PROTOCAL) : public nMech::nNET::_jNamed_Event_Handler {_jJOIN_2(jNamedEvent_,PROTOCAL)(){\
	nMech::tfname_t szName; jt_sprintf(szName,_T("jNamedEvent_%s"), _jPLUGIN_NAME_ ); \
	nMech::jBase::RegistNamedPointer(szName , _T(#PROTOCAL),this);} void Call(_ARG_jNamedEventHandler) const;}; \
	static _jJOIN_2(jNamedEvent_,PROTOCAL) _jJOIN_2(g_jNetEvent_,PROTOCAL);\
	void _jJOIN_2(jNamedEvent_,PROTOCAL)::Call(_ARG_jNamedEventHandler) const


#define jNAMED_EVENT_RECEIVER2(PROTOCAL,HEADER) \
struct _jJOIN_3(jNamedEvent_,HEADER,PROTOCAL) : public nMech::nNET::_jNamed_Event_Handler\
{_jJOIN_3(jNamedEvent_,HEADER,PROTOCAL)(){\
	nMech::tfname_t szName; jt_sprintf(szName,_T("jNamedEvent_%s_%s"),_jPLUGIN_NAME_,_T(#HEADER)); \
	nMech::jBase::RegistNamedPointer(szName,_T(#PROTOCAL),this);}	void Call(_ARG_jNamedEventHandler) const ; }; \
	static _jJOIN_3(jNamedEvent_,HEADER,PROTOCAL) _jJOIN_3(g_jNetEvent_P2P_Tcp_,PROTOCAL,HEADER);\
	void _jJOIN_3(jNamedEvent_,HEADER,PROTOCAL)::Call(_ARG_jNamedEventHandler) const



#define READ_PACKET(PROTOCOL) 				S_##PROTOCOL Data; 				bool _isOK=##READ_##PROTOCOL(pS,dwLen,pReadBuff, Data);
#define READ_PACKET_N(NAMESPACE,PROTOCOL) 	NAMESPACE::S_##PROTOCOL Data;	bool _isOK=NAMESPACE::READ_##PROTOCOL(dwLen,pReadBuff, Data);


#define READ_PACKET_Data(PROTOCOL,Data) 				bool _isOK=##READ_##PROTOCOL(pS,dwLen,pReadBuff, Data);
#define READ_PACKET_N_Data(NAMESPACE,PROTOCOL,Data) 	bool _isOK=NAMESPACE::READ_##PROTOCOL(dwLen,pReadBuff, Data);


// 주의 xml은 CreateElement()된 것이므로 필요없을땐 DeleteElement()해야한다.
#define READ_PACKET_XML(PROTOCOL,xml)			S_##PROTOCOL Data;Data.xml = GetjIXml()->CreateElement(); READ_PACKET_Data(PROTOCOL,Data);
#define READ_PACKET_XML_Data(PROTOCOL,xml,Data) S_##PROTOCOL Data;Data.xml = GetjIXml()->CreateElement(); READ_PACKET_Data(PROTOCOL,Data);


#define READ_PACKET_SEND_FILENAME(szFileName,iTransferTime,iFileSize)\
	uint16 fileLen431;tname1024_t szFileName; int iOffset=0;\
	memcpy(&fileLen431,pReadBuff+iOffset,sizeof(fileLen431));\
	jRETURN(fileLen431<1023);\
	iOffset+=sizeof(fileLen431);\
	\
	memcpy(szFileName,pReadBuff+iOffset,sizeof(TCHAR)*fileLen431);\
	szFileName[fileLen431]=0;\
	iOffset+=(sizeof(TCHAR)*fileLen431);\
	\
	DWORD iTransferTime;\
	memcpy(&iTransferTime,pReadBuff+iOffset,sizeof(iTransferTime));\
	iOffset+=(sizeof(iTransferTime));\
	\
	int iFileSize;\
	memcpy(&iFileSize,pReadBuff+iOffset,sizeof(iFileSize));\
	iOffset+=(sizeof(iFileSize));\
	\
	dwLen-=iOffset; pReadBuff+=iOffset;\

#endif // __jIPacketDispatch_header__
