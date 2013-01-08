

DROP TABLE IF EXISTS Tbl_Friend;
CREATE TABLE Tbl_Friend (
-- id
	 db_id 	 INTEGER 	 PRIMARY KEY AUTOINCREMENT
-- 유저번호
,	 uid 	 INTEGER 	 
-- 친구번호
,	 uid_fiend 	 INTEGER 	 
-- 친구이름
,	 nic_fiend 	 VARCHAR(32) 	 
-- is_blocked : 블랙리스트이냐?
,	 is_blocked 	 BIT 	 
-- is_deleted
,	 is_deleted 	 SMALLINT 	 
-- 친구-총전적_승 : 토탈 승 카운트
,	 win_tot 	 INTEGER 	 
-- 친구-총전적_패 : 토탈 패 카운트
,	 lose_tot 	 INTEGER 	 
-- 친구-시즌전적_승 : 시즌 승 카운트(3개월)
,	 win_season 	 INTEGER 	 
-- 친구-시즌전적_패 : 시즌 패 카운트(3개월)
,	 lose_season 	 INTEGER 	 
-- 친구-연승 : 연속으로 승리한 개수. 음수면 연패
,	 win_continue 	 SMALLINT 	 
);