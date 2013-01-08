

DROP TABLE IF EXISTS Tbl_Result;
CREATE TABLE Tbl_Result (
-- game고유번호
	 db_id 	 INTEGER 	 PRIMARY KEY AUTOINCREMENT
-- 고유번호 : 승자 고유번호
,	 win_uid 	 INTEGER 	 
-- 타자 pid : 승자
,	 win_better 	 INTEGER 	 
-- 투수 pid : 승자
,	 win_pitcher 	 INTEGER 	 
-- 승자스코어
,	 win_score 	 TINYINT 	 
-- ELO_포인트 : 경기에서 승 했을 시 사용자에게 플러스 되는 매칭용 포인트
,	 win_elo_point 	 INTEGER 	 
-- 고유번호 : 패자 고유번호
,	 lose_uid 	 INTEGER 	 
-- 타자 pid : 패자
,	 lose_better 	 INTEGER 	 
-- 투수 pid : 패자
,	 lose_pitcher 	 INTEGER 	 
-- 패자스코어
,	 lose_score 	 TINYINT 	 
-- ELO_포인트 : 경기에서 패 했을 시  사용자에게 마이너스 되는 매칭용 포인트
,	 lose_elo_point 	 INTEGER 	 
-- 플레이시간 : 플레이 한 시간(초)
,	 play_time_sec 	 INTEGER 	 
-- 게임종료시간 : 플레이 시간 (2012-12-15 13:53:15)
,	 time_end 	 DATETIME 	 
);