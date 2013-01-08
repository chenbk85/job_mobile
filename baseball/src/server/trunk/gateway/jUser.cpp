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
	//시즌 총_홈런수 ,시즌 탈삼진수 , 총_홈런수	 ,탈삼진수	
	for(int i=0; i< rr_list.size() ; ++i)
	{
		const s_tbl_roundresult& rr = rr_list.Get(i).m_tbl_roundresult();

		if(db_id()==rr.uid_attack()) // 해당라운드의 공격자라면.
		{

			bool is_homerun=false;
			if(rr.hit_type() == eEBHT_HOMERUN )
			{
				is_homerun=true;
				user->set_batter_tot_homerun(user->batter_tot_homerun()+1);					// 총_홈런수	
				user->set_batter_tot_homerun_season(user->batter_tot_homerun_season()+1);	// 시즌 총_홈런수
			}
		}
		else // 해당라운드가 내가 투수였슴.
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
				{//탈삼진수
					user->set_pitcher_tot_strikeout(user->pitcher_tot_strikeout() + 1);				// 탈삼진수	
					user->set_pitcher_tot_strikeout_season(user->pitcher_tot_strikeout_season()+1);	// 시즌 탈삼진수
					is_strikeout=true;
					break;
				}

				/*
			case eEBHT_FOULOUT = 3:
			case eEBIT_INFIELDOUT = 4, // 내야아웃
			case eEBIT_LEFTFIELDOUT = 5, // 좌익수아웃
			case eEBIT_CENTERFIELDOUT = 6, // 중견수아웃
			case eEBIT_RIGHTFIELDOUT = 7, // 우익수아웃
			case eEBHT_NO_HIT = 8, // 치지못한상태
			case eEBHT_ONEHIT = 9, // 일루타
			case eEBHT_DOUBLEHIT = 10, // 이루타
			case eEBHT_TRIPLEHIT = 11, // 삼루타
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

	//jTODO DBUpdate , 변경사항 user , better , pitcher 
}

// DB 저장 하기 전 게임 내용에 따른 strike, homerun 데이터를 라운드 결과에서 추출하는 함수
void jUser::db_game_record( const s_result_round_list_t &rr_list, int64 db_id, db_record& record )
{
	for(int i=0; i< rr_list.size() ; ++i)
	{
		const s_tbl_roundresult& rr = rr_list.Get(i).m_tbl_roundresult();

		if (db_id == rr.uid_attack()) // 해당 라운드의 공격자라면.
		{
			bool is_homerun	= false;
			if(rr.hit_type() == eEBHT_HOMERUN )
			{
				is_homerun	= true;	
				record.homerun++;
			}
		}
		else // 해당라운드가 내가 투수였슴.
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