/* file : jIConsoleDLL.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-03-04 12:51:37
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __jIConsoleApp_header__
#define __jIConsoleApp_header__
#pragma once

#include "util/jUtil.h"

namespace nMech
{
	namespace nCONSOLE
	{
		#define jINTERFACE_jIConsoleDLL(X) public:	\
		\
		/*ParseCmd���ο��� �Էµ� ����� ��ȿ�ϸ� true����. ��������丮�� �����ϸ�ȴ�.*/\
		virtual bool ParseCmd(tcstr szCommand) ##X \
		/* szNetConfigFile = "xml/net/test_netconfig.xml" , szNetConfig_Name= test_net_server_DLL */\
		virtual bool Start(tcstr szNetConfigFile,tcstr szNetConfig_Name) ##X \
		virtual void End() ##X \

		jINTERFACE_END(jIConsoleDLL);

	}
}



#endif // __jIConsoleApp_header__
