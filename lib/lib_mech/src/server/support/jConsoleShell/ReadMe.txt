/* file : ReadMe.txt
Coder : by icandoit ( mech12@nate.com)
Date : 2008-03-04 12:42:39
comp.: www.actoz.com
title : 
desc : 

*/

//--------------------------------------------------------------------------
//	���� �ɼ�
//--------------------------------------------------------------------------

jConsoleShell.exe [app_nic_name:�̸�] [default_dll:net_module.dll] [NetConfigNode:netconfig_xml_node_name]

	default_dll:net_module.dll
		[jIConsoleDLL��_��ӹ���_DLL���ϸ�] 
		
	NetConfigNode:netconfig_xml_node_name
		[netconfig_xml_file������_�������]

	netconfig_xml_file�� �ֺܼ���[net][NetConfigXml]���� ���� �Ҽ��� �ִ�.


//--------------------------------------------------------------------------
// ����� ��� �޸� 
//--------------------------------------------------------------------------
jMech_init()�ϱ���

	����׸��  4,068kb

	��������	3,700kb


jMech_Init()��

	�����		18,400kb
		jPak.dll�ε����ϸ� 2,000kb �پ���.

	������		 9,800kb	




//--------------------------------------------------------------------------
// Console Cmd (���) �����丮 ���
//--------------------------------------------------------------------------

	jt_sprintf(buf, _T("%s.cmd.txt"),g_ExeEnv.m_szAppNic);
	���� ���� ��� �����丮 ������ ���ӷ�Ʈ ������ �������.



//--------------------------------------------------------------------------
// �ܼ�DLL Ŭ���� �����ϴ� ��
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
				//���⿡ �ڵ带 �߰��Ͻÿ�

				// true�� ���� �ϸ� �ܼ����α׷����� ��ɾ �����丮�� ����Ŵ
				return false;
			}
			void test_dll::Start(tcstr szNetConfigFile,tcstr szNetConfig_Name) 
			{
				parent_t::Start(szNetConfigFile,szNetConfig_Name);
				// ���⿡ �ڵ带 �߰��Ͻÿ�


			}

			void test_dll::End() 
			{
				//���⿡ �ڵ带 �߰��Ͻÿ�

				parent_t::End();
			}
