/* file : jIPipe.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-10-31 15:02:53
comp.: jgame.co.kr
title : 
desc : 



//const char* sPipeName = "\\\\.\\pipe\\jGame_Logger";

*/

#ifndef __jI23434lksdjfweiuofsPipe_header__
#define __jI23434lksdjfweiuofsPipe_header__
#pragma once

#include "header/jDefine.h"
#include "header/jInterface.h"

namespace nMech
{
	namespace nPipe
	{
		struct jIPipeWriter;
		typedef void jIPipeWriter_OnDisconnect_t(jIPipeWriter* pPipe);

		#define jINTERFACE_jIPipeWriter(x) public:	\
				virtual bool Connect(cstr szPipeName,jIPipeWriter_OnDisconnect_t*pF) ##x \
				virtual bool Write(tcstr pStr,...) ##x \

				jINTERFACE_END_BASE1(jIPipeWriter, nInterface::jIInterface);

				struct jIPipeReader;
				struct jIPipeEvent
				{
					jIPipeReader* m_pjIPipeReader;
					virtual void OnConnectingPipe(){}
					virtual void OnDisConnectingPipe(){}
					virtual void OnIncomingData(BYTE* pStr, DWORD nSize)=0;
				};

				//const char* sPipeName = "\\\\.\\pipe\\jGame_Logger";

#define jINTERFACE_jIPipeReader(X) public:	\
	virtual bool RunThread(tcstr szPipeName, jIPipeEvent* pEvent) ##X\
	virtual tcstr GetPipeName() ##X \

				jINTERFACE_END_BASE1(jIPipeReader, nInterface::jIInterface);


	}//namespace nPipe


	// »ç¿ë¹ý.
	// nPipe::jIPipeWriter* pjIPipeWriter = jCREATE_INTERFACE(nMech::nPipe::jIPipeWriter);

	// nMech::nPipe::jIPipeReader* pjIPipeReader = jCREATE_INTERFACE(nMech::nPipe::jIPipeReader);
	//pjIPipeReader->Release();

}



#endif // __jI23434lksdjfweiuofsPipe_header__
