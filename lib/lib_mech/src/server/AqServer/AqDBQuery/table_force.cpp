/* file : db_insert_code.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-03-17 12:36:20
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"



void make_Insert_table(WCHAR* szSQL, nAQ::Use_Force* p )
{

jw_sprintf(szSQL, L"INSERT INTO Use_Force ( \
,uid\
,huid1\
,huid2\
,huid3\
,fsid\
,state_xml_id\
,morale\
,morale_decrease\
,energy\
,energy_fill\
,unit_soldier\
,unit_wound\
,unit_injury\
,att\
,def\
,mspeed\
,aspeed\
,arange\
,srange\
,killing\
,survival\
,food\
,gold\
,tree\
,stone\
,iron\
,silk\
,PosType\
,PosID\
,x\
,y\
) VALUES ( \
%I64d,\
%I64d,\
%I64d,\
%I64d,\
%d,\
'%s',\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d)"
,p->Get_uid().m_db_id
,p->Get_huid1().m_db_id
,p->Get_huid2().m_db_id
,p->Get_huid3().m_db_id
,p->Get_fsid() 
,jT(p->Get_state_xml_id())
,p->Get_morale() 
,p->Get_morale_decrease() 
,p->Get_energy() 
,p->Get_energy_fill() 
,p->Get_unit_soldier() 
,p->Get_unit_wound() 
,p->Get_unit_injury() 
,p->Get_att() 
,p->Get_def() 
,p->Get_mspeed() 
,p->Get_aspeed() 
,p->Get_arange() 
,p->Get_srange() 
,p->Get_killing() 
,p->Get_survival() 
,p->Get_food() 
,p->Get_gold() 
,p->Get_tree() 
,p->Get_stone() 
,p->Get_iron() 
,p->Get_silk() 
,p->Get_PosType() 
,p->Get_PosID() 
,p->Get_x() 
,p->Get_y() 
);

}



void make_update_table(WCHAR*szSQL , nAQ::Use_Force* p)
{
jw_sprintf(szSQL, L"UPDATE Use_Force SET \
[huid1]=%I64d\
,[huid2]=%I64d\
,[huid3]=%I64d\
,[fsid]=%d\
,[state_xml_id]='%s'\
,[morale]=%d\
,[morale_decrease]=%d\
,[energy]=%d\
,[energy_fill]=%d\
,[unit_soldier]=%d\
,[unit_wound]=%d\
,[unit_injury]=%d\
,[att]=%d\
,[def]=%d\
,[mspeed]=%d\
,[aspeed]=%d\
,[arange]=%d\
,[srange]=%d\
,[killing]=%d\
,[survival]=%d\
,[food]=%d\
,[gold]=%d\
,[tree]=%d\
,[stone]=%d\
,[iron]=%d\
,[silk]=%d\
,[PosType]=%d\
,[PosID]=%d\
,[x]=%d\
,[y]=%d\
 WHERE [fuid]=%I64d "
,p->Get_huid1()
,p->Get_huid2()
,p->Get_huid3()
,p->Get_fsid()
,jT(p->Get_state_xml_id())
,p->Get_morale()
,p->Get_morale_decrease()
,p->Get_energy()
,p->Get_energy_fill()
,p->Get_unit_soldier()
,p->Get_unit_wound()
,p->Get_unit_injury()
,p->Get_att()
,p->Get_def()
,p->Get_mspeed()
,p->Get_aspeed()
,p->Get_arange()
,p->Get_srange()
,p->Get_killing()
,p->Get_survival()
,p->Get_food()
,p->Get_gold()
,p->Get_tree()
,p->Get_stone()
,p->Get_iron()
,p->Get_silk()
,p->Get_PosType()
,p->Get_PosID()
,p->Get_x()
,p->Get_y()
,p->Get_fuid().m_db_id
);}
