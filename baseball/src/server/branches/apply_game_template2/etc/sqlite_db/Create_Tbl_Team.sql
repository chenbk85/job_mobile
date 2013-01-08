

DROP TABLE IF EXISTS Tbl_Team;
CREATE TABLE Tbl_Team (
	-- 총전적_승 : 토탈 승 카운트
		 win_tot 	 INTEGER 	 
	-- 총전적_패 : 토탈 패 카운트
	,	 lose_tot 	 INTEGER 	 
	-- 시즌전적_승 : 시즌 승 카운트(3개월)
	,	 win_season 	 INTEGER 	 
	-- 시즌전적_패 : 시즌 패 카운트(3개월)
	,	 lose_season 	 INTEGER 	 
	-- 연승 : 연속으로 승리한 개수. 음수면 연패
	,	 win_continue 	 SMALLINT 	 
	-- 싱글-총전적_승 : 토탈 승 카운트
	,	 win_tot_single 	 INTEGER 	 
	-- 싱글-총전적_패 : 토탈 패 카운트
	,	 lose_tot_single 	 INTEGER 	 
	-- 싱글-시즌전적_승 : 시즌 승 카운트(3개월)
	,	 win_season_single 	 INTEGER 	 
	-- 싱글-시즌전적_패 : 시즌 패 카운트(3개월)
	,	 lose_season_single 	 INTEGER 	 
	-- 싱글-연승패 : 연속으로 승리한 개수. 음수면 연패
	,	 win_continue_single 	 SMALLINT 	 
-- 고유번호
	 db_id 	 INTEGER 	 PRIMARY KEY AUTOINCREMENT
-- 팀이름 : 디펄트명은 pp_name이다
,	 name 	 VARCHAR(32) 	 
-- 유저id
,	 uid 	 INTEGER 	 
-- 타자
,	 pid_better 	 INTEGER 	 
-- 투수
,	 pid_pitcher 	 INTEGER 	 
-- 삭제플레그 : 아이템이 삭제된것.또는 어뷰징으로 제제상태
,	 is_deleted 	 SMALLINT 	 
);