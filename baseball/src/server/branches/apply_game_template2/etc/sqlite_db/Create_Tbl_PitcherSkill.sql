

DROP TABLE IF EXISTS Tbl_PitcherSkill;
CREATE TABLE Tbl_PitcherSkill (
-- 고유번호
	 db_id 	 INTEGER 	 PRIMARY KEY AUTOINCREMENT
-- 소유자id
,	 uid 	 INTEGER 	 
-- 소유투수id : 디펄트명은 pp_name이다
,	 pid 	 INTEGER 	 
-- 제스쳐타입 : 제스쳐종류
,	 gesture 	 VARCHAR(256) 	 
-- 삭제플레그
,	 is_deleted 	 SMALLINT 	 
-- 투수변화구 진행 시간 : 각각의 변화구에 진행된 시간을 기록
,	 exp 	 INTEGER 	 
-- 투수변화구종류 : 투수 변화구종류
,	 type 	 VARCHAR(256) 	 
);