/* file : logic_build.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-03-17 18:58:17
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "base/jTimeHelper.h"


std::pair<time_t,int32>  calc_BuildUpgradeSecond(Use_User&u,Use_Town* pT,nXML::jE eSlot,Use_Hero* pH,time_t upgradeSec)
{
	jTimeHelper th;
	th.Get_curr_time();
	fname_t buf;
	jIVar *pV = eSlot->PersistAttr(jS(UPGRADE_END_DAY),ToString((int64)(th.m_t+upgradeSec),buf));//종료되는 날짜
	pV->Set_cstr(buf);
	return make_pair(th.m_t,upgradeSec);
}


#define for_each_build_upgrade_check_item(X) X(tree_num) X(stone_num) X(iron_num) X(silk_num) X(population_num)

#define upgrade_check_item5654(item)\
	if(pT->Get_##item() < pN->Get_##item())\
		throw jError(SR_t(CheckUpgrade_98742345),CR_t(item));\
	pT->Set_##item(pT->Get_##item()-pN->Get_##item());\


#define CheckUpgrade_98742345(table)\
std::pair<time_t,int32> CheckUpgrade_##table(Use_User&u,Use_Town* pT,nXML::jE eSlot,Use_Hero* pH)\
{\
	jIVar* pV = eSlot->PersistAttr(jS(LEVEL),0);\
	if(pV->Get_int()<0) throw jError(SR_t(CheckUpgrade_98742345),CR_t(CURR_LEVEL_ERROR));\
	if(pV->Get_int()>=jCSV(table).size())	throw jError(SR_t(CheckUpgrade_98742345),CR_t(DONT_BUILD_UPGRADE));\
	table* pN = jCSV(table).at(pV->Get_int()+1);\
	for_each_build_upgrade_check_item(upgrade_check_item5654);\
	return calc_BuildUpgradeSecond(u,pT,eSlot,pH,pN->Get_upgradetime());\
}\

for_each_EBuildType_Impl(CheckUpgrade_98742345);


