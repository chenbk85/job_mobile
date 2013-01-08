/* file : jINet_asio.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-03-21 17:36:28
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __jINet_asio_header__
#define __jINet_asio_header__
#pragma once

#define SQPLUS_CONST_OPT
#include "interface/Squirrel/jISquirrel.h"
#include "base/jSQ_bind.h"

namespace nMech
{
	namespace nNET
	{
		enum { MAX_BODY_LENGTH = 2048 };

		struct MOB_ITimer{};
		typedef boost::function<bool()> MOB_Timer_handler_t;

		typedef int32 asio_header_type_t;

		struct jIClientSession;
		struct jIClientSessionManager;
		//#--------------------------------------------------------------------------
		struct jIPlugin_jIClientSession_Asio :  public nMech::jRttiObj 
		//#--------------------------------------------------------------------------
		{
			jIE* m_pE;
			jIClientSessionManager* m_pCSM;
			virtual bool Load_SQ(){ return false;}
			virtual nSQ::SquirrelObject* GetSQTable(){return 0;}

#define		INTERFACE_jIPlugin_jIClientSession_Asio(X)\
			virtual void OnStartup() X;\
			virtual void OnStop() X;\
			virtual bool OnConnect(jIE*) X;\
			virtual void OnDisconnect(jIE*) X;\
			virtual bool OnRead(jIE*,char*,int iReadLen) X;\
			virtual bool ParseCmd(tcstr szCommand) X;\

			INTERFACE_jIPlugin_jIClientSession_Asio(=0);
		};

#define jINTERFACE_jIClientSessionManager(X) public:	\
	virtual jIE* Create(cstr szIOServiceName,jIPlugin_jIClientSession_Asio* pPlugIn,jIE* peSession) X\
	virtual jIE* Find(cstr szSessionName) X\
	virtual void Send(jIE* peSession,char* sendData,asio_header_type_t iLen) X\
	virtual void Close(jIE* peSession)/*접속종료하고자할때*/ X\
	virtual bool IsConnected(jIE* peSession) X\
	virtual void ReleaseAll() X\
	virtual MOB_ITimer* Timer_Create(cstr szIOServiceName,int iTime,MOB_Timer_handler_t& func) X\
	virtual void Timer_Delete(MOB_ITimer*p) X\


		jINTERFACE_END(jIClientSessionManager);


		jIPlugin_jIClientSession_Asio* Create_Plugin_jClientSession_Asio(cstr szPlugIn,jIE* pePlugIn);
		void Stop_jClientSession_Asio(jIE* pePlugIn);
		void Run_jClientSession_Asio(jIE* pePlugIn);


	}//namespace nNET

}//namespace nMech



#endif // __jINet_asio_header__
