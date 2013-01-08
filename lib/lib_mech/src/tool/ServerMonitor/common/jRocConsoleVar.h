/* file : jRocConsoleVar.h
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-01-27 23:06:45
comp.: rocworks.co.kr
title : 
desc : 

���� ���� : D:\Job_Maestia\MaestiaDoc\Program\�۾���Ʈ\����\2011-01\2011-01-28a-���ο���-jRocConsoleVar �߰�\jRocConsoleVar����.txt

*/

#ifndef __jRocConsoleVar_header__
#define __jRocConsoleVar_header__
#pragma once



namespace nCONSOLE_VAR
{
	using namespace nMech;

#define for_each_CONSOLE_VAR_TYPE_string(T)\
	T(wstring)\

#define for_each_CONSOLE_VAR_TYPE_simple(T)\
	T(int8) \
	T(uint8) \
	T(int16) \
	T(uint16) \
	T(int32) \
	T(uint32) \
	T(int64) \
	T(uint64) \
	T(float) \
	T(double) \

#define for_each_CONSOLE_VAR_TYPE(T) for_each_CONSOLE_VAR_TYPE_string(T) for_each_CONSOLE_VAR_TYPE_simple(T)


#define DEC_EConsoleVarType(TYPE) eCV_##TYPE,
	enum EConsoleVarType
	{ 
		for_each_CONSOLE_VAR_TYPE(DEC_EConsoleVarType)
	};

	struct jRocConsoleVar
	{
		EConsoleVarType m_eType;
		tstring m_name;
		tstring m_help;
		int m_option;
		union
		{
#define union_CV_9845(TYPE) TYPE m_##TYPE;
			for_each_CONSOLE_VAR_TYPE_simple(union_CV_9845)
		};
#define GET_SET_CV_9845(TYPE) \
	TYPE Get_##TYPE(){ return m_##TYPE;} \
	void Set_##TYPE(const TYPE var){m_##TYPE = var;}
		for_each_CONSOLE_VAR_TYPE_simple(GET_SET_CV_9845);

		wstring m_wstring;
		wcstr Get_wstring(){ return m_wstring.c_str(); }
		void Set_wstring(wcstr sz){ m_wstring = sz;}

		tcstr ToString(tname1024_t buf);
		void  FromString(tcstr buf);

		//������.
		jRocConsoleVar(wcstr val,tcstr name,tcstr help,int option) : m_wstring(val),m_eType(eCV_wstring),m_name(name),m_help(help),m_option(option){}
#define jRocConsoleVar_CV_9845(TYPE) jRocConsoleVar(const TYPE val,tcstr name,tcstr help,int option):m_##TYPE(val),m_eType(eCV_##TYPE),m_name(name),m_help(help),m_option(option){}
		for_each_CONSOLE_VAR_TYPE_simple(jRocConsoleVar_CV_9845);

	};//struct jRocConsoleVar

#define rocDECLARE_CONSOLE_VAR(TYPE, NAME , VAL , HELP , OPTION) extern nCONSOLE_VAR::jRocConsoleVar NAME;
#define rocDEFINE_CONSOLE_VAR(TYPE, NAME , VAL , HELP , OPTION) nCONSOLE_VAR::jRocConsoleVar NAME(VAL,_T(#NAME),_T(#HELP) _T(" ") _T(#OPTION),OPTION);

	extern bool SetConsoleVar(tcstr szName, tcstr szData);
	extern jRocConsoleVar* GetConsoleVar(tcstr szName);

	enum ERocConsoleVarOption
	{
		eCVO_NOTIFY_TO_CLIENTS	=jBIT_0, // ���� �� ����� ��� Ŭ�󿡰� �뺸.( SET_PARAM��ɽ� ��ü Ŭ���̾�Ʈ�� �ֺܼ����� �ٲ��. )
		eCVO_DONT_SAVE_SERVER	=jBIT_1, // ������ ���� ���Ϸ� �����ϰų� �ε����� ����.
		eCVO_DONT_SAVE_CLIENT	=jBIT_2, // Ŭ�� ���� ���Ϸ� �����ϰų� �ε����� ����.
		eCVO_NOT_USE_VAR		=jBIT_3, // �ش� CONSOLE VAR�� ���� ������� ���� �׷��� ���� ����� ���������� ����ó��.( Ȯ���� .delete)
		eCVO_ONLY_SERVER		=jBIT_4, // ���������� ����ϴ� �ܼ� ����.  ������ �ƹ� ��ɾ���. ���� ǥ�ø� ���Ѱ�.
		eCVO_ONLY_CLIENT		=jBIT_5, // SET_PARAM����� ���� ������ �ȹٲ�� �ش� Ŭ���� �ֺܼ����� �ٲ��. Ŭ���׽�Ʈ��.
	};

}//namespace nCONSOLE_VAR



/*

VAR(TYPE, NAME , VAL , HELP , OPTION)

	TYPE		: for_each_CONSOLE_VAR_TYPE()�� ������ �ڷ����� ����.
	VAL			: �ʱⰪ ( �� �ش� ���������� ������ �װ��� ���.)
	NAME		: �׻� pv_�� ��������.
	HELP		: ���Ϸ� ����� ����.
	OPTION		: enum ERocConsoleVarOption

*/

#if defined(DF_SERVER_TEAM) && defined(DF_VER_YD)
#define for_each_CONSOLE_VAR_YD(VAR)\
	VAR(wstring	,pv_YD_ZeroMonitor_ServerIP,L"maestia.zeromonitor.zeus.kr","YD ZeroMonitor server ip , 121.253.15.51",eCVO_ONLY_SERVER|eCVO_DONT_SAVE_CLIENT)\
	VAR(wstring	,pv_YD_ZeroMonitor_ServerPORT,L"20100","YD ZeroMonitor Server port",eCVO_ONLY_SERVER|eCVO_DONT_SAVE_CLIENT)\
	VAR(uint32	,pv_YD_ZeroMonitor_PingTime,60,"YD ZeroMonitor live ping packet send delay time (second)",eCVO_ONLY_SERVER|eCVO_DONT_SAVE_CLIENT)\
	\
	VAR(wstring	,pv_YD_ZeroPC_ServerIP	,L"maestia.zeropc.zeus.kr","YD ZeroPC server ip , 121.253.15.27",eCVO_ONLY_SERVER|eCVO_DONT_SAVE_CLIENT)\
	VAR(uint32	,pv_YD_ZeroPC_ServerPORT,20115,"YD ZeroPC Server port",eCVO_ONLY_SERVER|eCVO_DONT_SAVE_CLIENT)\
	VAR(uint32	,pv_YD_ZeroPC_SessionTimeout_SEC,60,"YD ZeroPC Server echoing loop delay time ( second)",eCVO_ONLY_SERVER|eCVO_DONT_SAVE_CLIENT)\
	VAR(uint32	,pv_YD_ZeroPC_AutoReconnect,1,"YD ZeroPC Server socket is disconnected then auto reconnect",eCVO_ONLY_SERVER|eCVO_DONT_SAVE_CLIENT)\
	VAR(wstring	,pv_YD_ZeroPC_normal_testID,L"test","YD ZeroPC Test ID: normal pc user",eCVO_ONLY_SERVER|eCVO_DONT_SAVE_CLIENT | eCVO_NOT_USE_VAR)\
	VAR(wstring	,pv_YD_ZeroPC_special_testID,L"testpc","YD ZeroPC Test ID: special pc user",eCVO_ONLY_SERVER|eCVO_DONT_SAVE_CLIENT)\
	VAR(uint32	,pv_YD_ZeroPC_log		,0,"YD ZeroPC log on(=1) off(=0)",eCVO_ONLY_SERVER|eCVO_DONT_SAVE_CLIENT)\
	VAR(wstring	,pv_YD_ZeroPC_buff_list	,L"50007;52007","YD ZeroPC buff list. Seperated by  \";\"",eCVO_ONLY_SERVER|eCVO_DONT_SAVE_CLIENT)\
	VAR(uint32	,pv_YD_ZeroPC_notify_time,180,"YD ZeroPC notify user state ( second )",eCVO_ONLY_SERVER|eCVO_DONT_SAVE_CLIENT)\
	VAR(wstring	,pv_YD_ZeroPC_item_reset_time,L"00;01","YD ZeroPC item set time.  (HH:MM)",eCVO_ONLY_SERVER|eCVO_DONT_SAVE_CLIENT)\
	VAR(uint32	,pv_YDPC,0,"force yd pcbang enable",eCVO_ONLY_SERVER|eCVO_DONT_SAVE_CLIENT)\
	VAR(uint32	,pv_YD_FAILED_ORDER_CODE_BATCH_TIME_MIN,20,"yd_order_code notify fail batch job time (minute)",eCVO_ONLY_SERVER|eCVO_DONT_SAVE_CLIENT)\


 
#else
#define for_each_CONSOLE_VAR_YD(VAR)
#endif //#if defined(DF_SERVER_TEAM) && defined(DF_VER_YD)


#define for_each_CONSOLE_VAR(VAR)\
	for_each_CONSOLE_VAR_YD(VAR)\
	VAR(uint32,pv_LastRecvPacket_WaitTime,10000,"(MSEC)wait time for client move_rock"\
										,eCVO_NOTIFY_TO_CLIENTS|eCVO_DONT_SAVE_CLIENT)\
	VAR(uint32,pv_AVM_LOGIN_CHECK_LONGTIME,5,"(MIN)server disconnect TIME when user connect long time in login server"\
										,eCVO_ONLY_SERVER|eCVO_DONT_SAVE_CLIENT)\

for_each_CONSOLE_VAR(rocDECLARE_CONSOLE_VAR);


#endif // __jRocConsoleVar_header__
