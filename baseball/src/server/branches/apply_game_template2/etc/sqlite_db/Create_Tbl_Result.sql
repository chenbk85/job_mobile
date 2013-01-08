

DROP TABLE IF EXISTS Tbl_Result;
CREATE TABLE Tbl_Result (
-- game고유번호
	 db_id 	 INTEGER 	 PRIMARY KEY AUTOINCREMENT
-- is_singlemode : 0=멀티플레이 1=싱글플레이
,	 is_singlemode 	 BIT 	 
-- 고유번호 : 승자 고유번호
,	 win_uid 	 INTEGER 	 
-- 타자 pid : 승자
,	 win_better 	 INTEGER 	 
-- 투수 pid : 승자
,	 win_pitcher 	 INTEGER 	 
-- 팀id
,	 win_team 	 INTEGER 	 
-- 승자스코어
,	 win_score 	 TINYINT 	 
-- 승자 보상경험치 : 플레이어1의 보상경험치( 투수타자모두지급)
,	 win_reward_exp 	 INTEGER 	 
-- 승자 보상게임머니 : 보상게임머니
,	 win_reward_gamemoney 	 INT 	 
-- 고유번호 : 패자 고유번호
,	 lose_uid 	 INTEGER 	 
-- 타자 pid : 패자
,	 lose_better 	 INTEGER 	 
-- 투수 pid : 패자
,	 lose_pitcher 	 INTEGER 	 
-- 패자팀id
,	 lose_team 	 INTEGER 	 
-- 패자스코어
,	 lose_score 	 TINYINT 	 
-- 패자 보상경험치 : 보상경험치
,	 lose_reward_exp 	 INTEGER 	 
-- 패자 보상게임머니 : 보상게임머니
,	 lose_reward_gamemoney 	 INT 	 
-- 플레이시간 : 플레이 한 시간(초)
,	 play_time_sec 	 INTEGER 	 
-- 피망플러스포인트
,	 pp_point 	 INTEGER 	 
-- 게임종료시간 : 플레이 시간 (2012-12-15 13:53:15)
,	 time_end 	 DATETIME 	 
);