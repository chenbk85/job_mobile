#include "stdafx.h"
#include "TPlayer.h"


jCONSOLE_CMD_AUTO(jSERVER_NAME,file_db_print,0,"file db","")
{
	jCHECK_CurrUser();
// 	if(g_pCurrUser->m_eCurrChannel.empty())
// 	{
// 		jWARN1(_T("@channel.select <channelid>�� ���� �����ϼ���"));
// 		return false;
// 	}
// 	g_pCurrUser->m_eUser_file_db->DebugPrint(true);
	return true;
}
bool check_Build_create_condition( jPlayerObj *pPlayer,nAQ::EBuildType eType)
{// jTODO : �ϴ� �������� üũ������ ���߿� Ŭ�󿡼� üũ�ϴ� �ڵ� �߰�����
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,build_create,0,"slot = B1~B23","<szBuild_slot> <EBuildType> <exec_hero_id>")
{
	jCHECK_CurrUser();

// 	#define jCONSOLE_PARAM_build_create(X,Y) 	X(szBuild_slot,wcstr) X(buildType,wcstr) X(exec_hero_id,int)
// 	jCONSOLE_PARAM_END(build_create);
// 
// 	if(g_pCurrUser->m_eCurrChannel.empty())
// 	{
// 		jWARN1(_T("@channel.select <channelid>�� ���� �����ϼ���"));
// 		return false;
// 	}
// 	
// 	nXML::jE eB = g_pCurrUser->m_eCurrChannel[jS(BUILD_SLOT_LIST)];
// 	if(eB(szBuild_slot).full())
// 	{
// 		jLOG1(_T("szBuild_slot error ������ �ǹ� ����"));
// 		return false;
// 	}
// 
// 	nAQ::EBuildType eType;
// 	eType =StringToVal(wstring(buildType),eBEGIN_EBuildType);
// 	if(!check_Build_create_condition(g_pCurrUser,eType))
// 	{
// 		jLOG1(_T("�ǹ� ���� ���� �ȵʱ����� �ǹ� ����"));
// 		return false;
// 	}
// 
// 	Use_Hero* pHero = g_pCurrUser->Hero_at(exec_hero_id);
// 	if(!pHero)
// 	{
// 		jLOG1(_T("��������� �����ϼ���"));
// 		return false;
// 	}
// 	if(pHero->Get_work_state()!=nAQ::eHWS_REST)
// 	{
// 		jLOG1(_T("���� �ִ� ����� �ƴմϴ�."));
// 		return false;
// 	}
// 
// 	
// 	g_pCurrUser->Write_Packet_Channel(WRITE_X2T_NEW_BUILD(buf,szBuild_slot,eType,exec_hero_id));
	return true;
}
