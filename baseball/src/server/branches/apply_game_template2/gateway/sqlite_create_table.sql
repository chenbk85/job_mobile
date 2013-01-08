CREATE TABLE Tbl_User (
-- 고유번호 : db pk 피망에서 온 id를 그대로 사용
	 db_id 	 INT 	 
-- 닉네임 : 베이스볼에서의 유저닉네임
,	 uname 	 VARCHAR(32) 	 
-- 총전적_승 : 투수총전적_승
,	 tot_win 	 SMALLINT 	 
-- 총전적_패 : 투수총전적_패
,	 tot_lose 	 SMALLINT 	 
-- 탈삼진수 : 투수총_탈삼진
,	 pitcher_tot_strikeout 	 SMALLINT 	 
-- 투수총평균_레벨 : 투수총평균_레벨 멀로 평균을 낼것인가
,	 pitcher_tot_average_level 	 SMALLINT 	 
-- 총_홈런수 : 타자총_홈런
,	 better_tot_homerun 	 SMALLINT 	 
-- 타자총평균_레벨 : 타자총평균_레벨
,	 better_tot__average_level 	 SMALLINT 	 
-- 캐쉬템구매갯수 : 캐쉬템구매갯수
,	 cash_item_buy_count 	 SMALLINT 	 
-- 마지막로긴시간 : 마지막로긴시간
,	 time_last_login 	 DATETIME 	 
-- 마지막로그아웃시간 : 마지막 로그아웃시간
,	 time_last_logout 	 DATETIME 	 
-- 연속출석일수 : 연속출석한 일수
,	 day_continue_attend 	 SMALLINT 	 
-- 게임등록시간 : 최초게임등록일
,	 regist_date 	 DATETIME 	 
-- 기본팀번호 : 기본팀 index
,	 default_tid 	 BIGINT 	 
-- 옵션 : 옵션(클라에서임의로저장할내용)
,	 option 	 VARCHAR(256) 	 
-- 삭제플레그 : 아이템이 삭제된것.또는 어뷰징으로 제제상태
,	 is_deleted 	 SMALLINT 	 
-- 총_플레이_타임 : 총_플레이_타임(분)
,	 playtime_tot 	 BIGINT 	 
);
