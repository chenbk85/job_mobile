/* file : ReadMe.txt
Coder : by icandoit ( mech12@nate.com)
Date : 2008-03-04 12:42:39
comp.: www.actoz.com
title : 
desc : 

*/

//--------------------------------------------------------------------------
//	시작 옵션
//--------------------------------------------------------------------------

jConsoleShell.exe [app_nic_name:이름] [default_dll:net_module.dll] [NetConfigNode:netconfig_xml_node_name]

	default_dll:net_module.dll
		[jIConsoleDLL를_상속받은_DLL파일명] 
		
	NetConfigNode:netconfig_xml_node_name
		[netconfig_xml_file에서의_설정노드]

	netconfig_xml_file은 콘솔변수[net][NetConfigXml]에서 세팅 할수도 있다.


//--------------------------------------------------------------------------
// 모듈의 사용 메모리 
//--------------------------------------------------------------------------
jMech_init()하기전

	디버그모드  4,068kb

	릴리즈모드	3,700kb


jMech_Init()후

	디버그		18,400kb
		jPak.dll로딩안하면 2,000kb 줄어든다.

	릴리즈		 9,800kb	




//--------------------------------------------------------------------------
// Console Cmd (명령) 히스토리 기능
//--------------------------------------------------------------------------

	jt_sprintf(buf, _T("%s.cmd.txt"),g_ExeEnv.m_szAppNic);
	위와 같이 명령 히스토리 파일이 게임루트 폴더에 만들어짐.



//--------------------------------------------------------------------------
// 콘솔DLL 클래스 생성하는 예
//--------------------------------------------------------------------------

			#include "util/jConsoleDLL.h"

			class test_dll : public nCONSOLE::jConsoleDLL_Net
			{
			public:
				jINTERFACE_HEADER(jIConsoleDLL);

			};


			bool test_dll::ParseCmd(tcstr szCommand) 
			{
				if( parent_t::parseCmd(szCommand) ) return true;
				//여기에 코드를 추가하시오

				// true를 리턴 하면 콘솔프로그램에서 명령어를 히스토리에 기억시킴
				return false;
			}
			void test_dll::Start(tcstr szNetConfigFile,tcstr szNetConfig_Name) 
			{
				parent_t::Start(szNetConfigFile,szNetConfig_Name);
				// 여기에 코드를 추가하시오


			}

			void test_dll::End() 
			{
				//여기에 코드를 추가하시오

				parent_t::End();
			}
