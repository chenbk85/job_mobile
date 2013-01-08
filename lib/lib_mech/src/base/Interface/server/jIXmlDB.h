#ifndef MaGINEefsT_2332G2AM2E36_6LOGIC_H
#define MaGINEefsT_2332G2AM2E36_6LOGIC_H

#include "jMessageObject.h"


//------------------------------------------------------------------------------------
// intefrace: NetGameLogic
//------------------------------------------------------------------------------------
#define jINTERFACE_jIXmlDB(x) public:	\
	virtual void ConnectToServer() ##x \
	/* szNetConfigName ������ DB������ <NetConfig>������ �̸� */
	virtual void LogOut				()  ##x \
	virtual jINetPort* GetNetPort() ##x \
	virtual void FrameMove() ##x \
	virtual void ParseCmd(cstr cmd) ##x \

jINTERFACE_BASE1_DEFINE(jIXmlDB,jIMessageObject);

//------------------------------------------------------------------------------------
#endif //MGINETWORK_H
