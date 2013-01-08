/* file : jUser.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-05-22 13:23:54
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jUser.h"


void init_UserGateServer()
{
	void _jConsolePrinterFunc( tcstr szString,bool bAdd );
	GetjILog()->SetPrinter(_jConsolePrinterFunc);

	void Load_Common_CSV();Load_Common_CSV();

	jRETURN(nG::g_DocApp.LoadFile("../etc/xml/baseball.xml" ) != false );
	nG::g_ECV.load_xml();
	nG::g_ECV.print_all();

}

void jUser::calc_game_round_result(OUT s_tbl_user* user
									 ,IN const s_result_round_list_t &rr_list)
{
	//���� ��_Ȩ���� ,���� Ż������ , ��_Ȩ����	 ,Ż������	
	for(int i=0; i< rr_list.size() ; ++i)
	{
		const s_tbl_roundresult& rr = rr_list.Get(i).m_tbl_roundresult();

		if(db_id()==rr.uid_attack()) // �ش������ �����ڶ��.
		{

			bool is_homerun=false;
			if(rr.hit_type() == eEBHT_HOMERUN )
			{
				is_homerun=true;
				user->set_batter_tot_homerun(user->batter_tot_homerun()+1);					// ��_Ȩ����	
				user->set_batter_tot_homerun_season(user->batter_tot_homerun_season()+1);	// ���� ��_Ȩ����
			}
		}
		else // �ش���尡 ���� ��������.
		{
			if(rr.hit_type() >eEBHT_NO_HIT)
			{
			}
			bool is_strikeout =false;
			bool is_homerun_pitching=false;
			switch(rr.hit_type())
			{
			case eEBHT_STANDOUT :
			case eEBHT_SWINGOUT :
				{//Ż������
					user->set_pitcher_tot_strikeout(user->pitcher_tot_strikeout() + 1);				// Ż������	
					user->set_pitcher_tot_strikeout_season(user->pitcher_tot_strikeout_season()+1);	// ���� Ż������
					is_strikeout=true;
					break;
				}

				/*
			case eEBHT_FOULOUT = 3:
			case eEBIT_INFIELDOUT = 4, // ���߾ƿ�
			case eEBIT_LEFTFIELDOUT = 5, // ���ͼ��ƿ�
			case eEBIT_CENTERFIELDOUT = 6, // �߰߼��ƿ�
			case eEBIT_RIGHTFIELDOUT = 7, // ���ͼ��ƿ�
			case eEBHT_NO_HIT = 8, // ġ�����ѻ���
			case eEBHT_ONEHIT = 9, // �Ϸ�Ÿ
			case eEBHT_DOUBLEHIT = 10, // �̷�Ÿ
			case eEBHT_TRIPLEHIT = 11, // ���Ÿ
			{

			}
			*/
			case eEBHT_HOMERUN:
				{
					is_homerun_pitching=true;
					break;
				}
			}
		}
	}

	//jTODO DBUpdate , ������� user , better , pitcher 
}

// DB ���� �ϱ� �� ���� ���뿡 ���� strike, homerun �����͸� ���� ������� �����ϴ� �Լ�
void jUser::db_game_record( const s_result_round_list_t &rr_list, int64 db_id, db_record& record )
{
	for(int i=0; i< rr_list.size() ; ++i)
	{
		const s_tbl_roundresult& rr = rr_list.Get(i).m_tbl_roundresult();

		if (db_id == rr.uid_attack()) // �ش� ������ �����ڶ��.
		{
			bool is_homerun	= false;
			if(rr.hit_type() == eEBHT_HOMERUN )
			{
				is_homerun	= true;	
				record.homerun++;
			}
		}
		else // �ش���尡 ���� ��������.
		{
			if(rr.hit_type() >eEBHT_NO_HIT)
			{
			}
			bool is_strikeout			= false;
			bool is_homerun_pitching	= false;

			switch(rr.hit_type())
			{
			case eEBHT_STANDOUT :
			case eEBHT_SWINGOUT :
				{	
					record.strike++;
					is_strikeout		= true;
					break;
				}
			case eEBHT_HOMERUN:
				{
					is_homerun_pitching	= true;
					break;
				}
			}
		}
	}
}