/* file : test_jIConsoleCmd.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-03-07 17:39:50
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"

#include "base/jTestUnit.h"
#include "interface/jIConsoleCmd.h"


using namespace nMech;
using namespace nMech::nCONSOLE;

namespace 
{
	int asdf = 0;
	jCONSOLE_CMD(test_command)
	{
		jAssert0(arg.size()==0);
		asdf = 999;
		return true;
	}

	tstring save_arg;
	jCONSOLE_CMD(test_command_arg)
	{
		jAssert0(arg.size()==1);
		save_arg = arg[0];
		return true;
	}

	jTEST(jIConsoleCmd_)
	{
		std::vector<std::tstring> listBuffer;

		size_t totCmd = Get_jIConsoleCmd()->GetSize();
		Get_jIConsoleCmd()->GetCmdList(_T("test_command"), listBuffer);
		size_t prev_cmd_list_cnt=listBuffer.size(); //test_command�� �����ϴ� ��ɸ���Ʈ�� �ϴ� ����.


		jCC(test,test_command,0,"test command","noarg");
		jEQUAL(asdf,0);

		bool is = Get_jIConsoleCmd()->Run(_T("test"),_T("test_command"),0);
		jCHECK(is);
		jEQUAL(asdf,999);

		Get_jIConsoleCmd()->GetCmdList(_T("test_command"), listBuffer);
		jEQUAL(listBuffer.size() , prev_cmd_list_cnt+1);

		Get_jIConsoleCmd()->GetCmdList(_T("test"), listBuffer);
		// "test." �� "test.test_command" �� ����
		jEQUAL(listBuffer.size() , prev_cmd_list_cnt+2);

		asdf = 0;
		is =Get_jIConsoleCmd()->Run(0,_T("test_command"),0);
		jCHECK(is);
		jEQUAL(asdf,999);

		// ī�װ� ��������
		is = Get_jIConsoleCmd()->UnRegist(_T("test"),_T("test_command"));
		// ���� ��� ��������̱� ������ �����ؾ���.
		jCHECK(is);

		// ����� ���⶧���� �����ؾ���.
		is =Get_jIConsoleCmd()->Run(_T("test"),_T("test_command"),0);
		jCHECK(!is);

		size_t totCmd2 = Get_jIConsoleCmd()->GetSize();
		jEQUAL(totCmd,totCmd2);
		jCC(test,test_command_arg,0,"test command arg","<string>");
		save_arg.clear();
		//ParseCmd�� ��ɽ�Ʈ���� ù���ڰ� @�� �����ؾ��Ѵ�.
		is = Get_jIConsoleCmd()->ParseCmd(_T("@ \t\n test_command_arg	arg_string") );
		jCHECK(is);
		jCHECK(save_arg ==_T("arg_string") );

		save_arg.clear();
		is = Get_jIConsoleCmd()->ParseCmd(_T("@ \t\n test.test_command_arg	arg_string") );
		jCHECK(is);
		jCHECK(save_arg ==_T("arg_string") );

		Get_jIConsoleCmd()->UnRegist(_T("test"), _T("test_command_arg"));

		is = Get_jIConsoleCmd()->ParseCmd(_T("@ test.test_command_arg	arg_string") );
		jCHECK(!is);

	}

}


