#include "stdafx.h"
#include "../AqCommon/AqCommon.h"


jCONSOLE_CMD_AUTO(jSERVER_NAME,file_db_print,0,"file db","")
{
	check_Dummy();
	if(g_pCurrUser->m_eCurrTown.empty())
	{
		GetjILog()->Warning(_T("@town.select <townid>를 먼저 실행하세요"));
		return false;
	}
	g_pCurrUser->m_eUser_file_db->DebugPrint(true);
	return true;
}
bool check_Build_create_condition( jDummyPlayer *pUser,nAQ::EBuildType eType)
{// jTODO : 일단 서버에서 체크하지만 나중에 클라에서 체크하는 코드 추가예정
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,build_create,0,"slot = B1~B23","<szBuild_slot> <EBuildType> <exec_hero_id>")
{
	check_Dummy();

	#define jCONSOLE_PARAM_build_create(X,Y) 	X(szBuild_slot,wcstr) X(buildType,wcstr) X(exec_hero_id,int)
	jCONSOLE_PARAM_END(build_create);

	if(g_pCurrUser->m_eCurrTown.empty())
	{
		GetjILog()->Warning(_T("@town.select <townid>를 먼저 실행하세요"));
		return false;
	}
	
	nXML::jE eB = g_pCurrUser->m_eCurrTown[jS(BUILD_SLOT_LIST)];
	if(eB(szBuild_slot).full())
	{
		GetjILog()->Log(_T("szBuild_slot error 기존의 건물 존제"));
		return false;
	}

	nAQ::EBuildType eType;
	eType =StringToVal(wstring(buildType),eBEGIN_EBuildType);
	if(!check_Build_create_condition(g_pCurrUser,eType))
	{
		GetjILog()->Log(_T("건물 생성 조건 안됨기존의 건물 존제"));
		return false;
	}

	Use_Hero* pHero = g_pCurrUser->Hero_at(exec_hero_id);
	if(!pHero)
	{
		GetjILog()->Log(_T("실행장수를 세팅하세요"));
		return false;
	}
	if(pHero->Get_work_state()!=nAQ::eHWS_REST)
	{
		GetjILog()->Log(_T("쉬고 있는 장수가 아닙니다."));
		return false;
	}

	
	g_pCurrUser->Write_Packet_Town(WRITE_X2T_NEW_BUILD(buf,szBuild_slot,eType,exec_hero_id));
	return true;
}
