

DROP TABLE IF EXISTS Tbl_User;
CREATE TABLE Tbl_User (
-- 고유번호
	 db_id 	 INTEGER 	 PRIMARY KEY
-- 피망ID : MemberInfo의 (game_id)피망에서 온 id를 그대로 사용
,	 pp_id 	 INTEGER 	 
-- HOST_TYPE : 0-pp user 1-facebook 2-카톡
,	 host_type 	 VARCHAR(32) 	 
-- 닉네임 : 베이스볼에서의 유저닉네임
,	 uname 	 VARCHAR(32) 	 
-- 총Disconnect수 : 게임중간에 나간수
,	 discon_tot 	 INTEGER 	 
-- 총전적_승 : 토탈 승 카운트
,	 win_tot 	 INTEGER 	 
-- 연승패 : 연속으로 승리한 개수. 음수면 연패
,	 win_tot_continue 	 INTEGER 	 
-- 최대연승 : 최대연승
,	 win_tot_continue_max 	 INTEGER 	 
-- 총전적_패 : 토탈 패 카운트
,	 lose_tot 	 INTEGER 	 
-- 시즌전적_승 : 시즌 승 카운트(3개월)
,	 win_season 	 INTEGER 	 
-- 시즌전적_패 : 시즌 패 카운트(3개월)
,	 lose_season 	 INTEGER 	 
-- 총_홈런수 : 타자총_홈런
,	 batter_tot_homerun 	 SMALLINT 	 
-- 탈삼진수 : 투수총_탈삼진
,	 pitcher_tot_strikeout 	 SMALLINT 	 
-- 시즌 총_홈런수 : 시즌 타자총_홈런
,	 batter_tot_homerun_season 	 SMALLINT 	 
-- 시즌 탈삼진수 : 시즌 투수총_탈삼진
,	 pitcher_tot_strikeout_season 	 SMALLINT 	 
-- ELO_포인트 : 경기마다 캐릭터에 갱신되는 매칭용 포인트
,	 elo_point 	 INTEGER 	 
-- 캐쉬템구매누적액 : 캐쉬템구매 누적액
,	 cash_item_buy_money_amount 	 INTEGER 	 
-- 마지막로긴시간 : 마지막로긴시간
,	 time_last_login 	 DATETIME 	 
-- 마지막로그아웃시간 : 마지막 로그아웃시간
,	 time_last_logout 	 DATETIME 	 
-- 연속출석일수 : 연속출석한 일수
,	 day_continue_attend 	 SMALLINT 	 
-- client_os : 클라 OS ( IOS  ANDROID )
,	 client_os 	 VARCHAR(32) 	 
-- client_networ : 클라 네트웍(3G 4G WIFI)
,	 client_networ 	 VARCHAR(32) 	 
-- 총_플레이_타임 : 총_플레이_타임(분)
,	 playtime_tot 	 INTEGER 	 
);