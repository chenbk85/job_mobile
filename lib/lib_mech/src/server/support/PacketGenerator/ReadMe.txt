/* file : ReadMe.txt
Coder : by icandoit ( mech12@nate.com)
Date : 2007-08-23 13:41:57
comp.: jgame.co.kr
title : 
desc : 

*/

*.usd���Ͽ��� ���� ���� �̸��� Skip���� �����ϸ� �ش� usd������ �Ľ���������.


//--------------------------------------------------------------------------
usd���Ͽ��� enum�� ���� ����
//--------------------------------------------------------------------------

	<enum �������ݵ����θ�::enum����ǥ�̸�>
	enum����[=�����] , ����

	����)

		<enum GMServer::EAddAccount>
		AA_SUCCESS=0,���� 
		AA_AccountDuple,�����ߺ�
		AA_Auth, ���Ѿ���
		AA_Unkown,�˼����½���




#define jNOT_USE_DebugPrint_[Server��] 
	����� ��¿� define��


PT_[�ܼ�"Server_TAG"]_LIB_API 
	DLL ����Ʈ �ͽ���Ʈ define��




packetgenerator.exe net �ش�����.xml ����Tag [TEXTEDITOR]


		<PT_REG_USER>			=---------------------- �������� ����
			<USER_ID TYPE="int32" /> ---------------  �ڷ� ����
			<USER_NAME TYPE="CHAR" i_Length="32" />
			<AGE TYPE="DWORD" />
			<SEX TYPE="BYTE" />
			<ADDRESS TYPE="CHAR" i_Length="32" />
		</PT_REG_USER>



//--------------------------------------------------------------------------
�������ݹ��� �Ӽ� ( �������� xml��������)
			b_jxDEFINE �� �ְ� ���� 0�̸� jxDEFINE���� ��¾���.
			
			i_DebugPrint�Ӽ��� ������ �� ���� �� ���������� i_DebugPrint ����Ʈ���̵�

				i_DebugPrint= 0�̸� DebugPrint���� ��¾��ϴ°��� ����Ʈ.
				i_DebugPrint =1�̸� ���������̸��� ����ϴ°��� ����Ʈ.
				i_DebugPrint =2�̰ų� b_DebugPrint�Ӽ��� ������ ��ü ����� ����Ʈ.
				i_DebugPrint =3�̸� ��Ŷ read�Ҷ� ������ ���
			

//--------------------------------------------------------------------------
���������� �Ӽ�	:  USD���Ͽ���  �������������Ҷ� {OPTION} ������ ��ġ
//--------------------------------------------------------------------------
			b_jxDEFINE �� �ְ� ���� 0�̸� jxDEFINE���� ��¾���.
			�� �������� ���ӽ����̽��� ���� jxDEFINE����� DOC ROOT�� �����ϸ� �ȴ�.
			
			i_DebugPrint= 0�̸� DebugPrint���� ��¾���.
			i_DebugPrint =1�̸� ���������̸��� ���.
			i_DebugPrint =2�̰ų� b_DebugPrint�Ӽ��� ������ ��ü ���
			
				��)

				[TA_SET_TEST_ENV]

				�׽�Ʈ ȯ�漼��

				{PARAM}

				i_DummySessionCount-int16-����Ŭ���̾�Ʈ�� ���ǰ���
				sLoginIP-net_string32
				iLoginPort-uint32

				{OPTION}
				i_DebugPrint=2
			
			
			u_CustomNumber=1234 �� ���� �Ǿ� ������ �������ݹ�ȣ�� 1234�� ���� �����Ѵ�.
			
			thread_name = �۾�������� 
				�ش� ���������� "�۾��������"�� �����忡�� ���� ó���ȴ�.

			
			
�ڷ��� �Ӽ�
			
			i_Length�� ����ϸ� �迭�� �ǹ��Ѵ�.
//--------------------------------------------------------------------------



//--------------------------------------------------------------------------
TYPE�� �ü� �ִ� �ڷ���
//--------------------------------------------------------------------------


			bool 

			CHAR : tstring�ϰ�� ��� 
			WCHAR : wstring�� ��� ���
			tstring
			wstring
			astring

			int8 : 
			uint8 : 

			int16 : 
			uint16 :

			int32 : 
			uint32 :
			
			float


//--------------------------------------------------------------------------
// ProtocalPrototype.xml�� �׻� Ÿ�� Seucence���� ���� �ȿ� �־�� �Ѵ�.
// �⺻ ������ ������ ����.
//--------------------------------------------------------------------------
<?xml version='1.0' encoding='euc-kr'?>
<PROTOCAL HEADER='NULL' VERSION='1' i_DebugPrint='2' b_jxDEFINE='1' >
	<!-- CODE���� ���๮�� �����ȵ�. anpersent # x 0 A ; �� ����Ұ�-->
	<CODE TYPE='ENUM_FILE'></CODE>
	<STRUCT_LIST>
	</STRUCT_LIST>
	<PROTOCAL_LIST>
	</PROTOCAL_LIST>
	<CODE TYPE='ENUM_FILE'>
	</CODE>
</PROTOCAL>
