

DROP TABLE IF EXISTS Tbl__PlayerBase;
CREATE TABLE Tbl__PlayerBase (
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
-- PK index : 선수 database table PK
	 db_id 	 INTEGER 	 PRIMARY KEY AUTOINCREMENT
-- Sys_Player아이디 : 구매한 선수카드의 번호(Sys_Player의 sid) 값이 0 이면 가상선수
,	 sid 	 SMALLINT 	 
-- 유저번호
,	 uid 	 INTEGER 	 
-- 닉네임
,	 pname 	 VARCHAR(32) 	 
-- 출신국가 : 캐주얼야구 게임기획서 3차 (20111031).docx참조
,	 city 	 VARCHAR(256) 	 
-- 이니셜 : 생성시 세팅. 등뒤의이니셜글자. 중복가능
,	 initial_name 	 VARCHAR(32) 	 
-- 백넘버 : 생성시 세팅. 변경아이템으로 변경가능
,	 back_number 	 SMALLINT 	 
-- 나이 : 생성시 세팅.
,	 age 	 SMALLINT 	 
-- 체형
,	 body_type 	 VARCHAR(256) 	 
-- 좌우타입 : 캐릭터의 좌우 구분 1이면 좌선수 0이면 우선수
,	 is_left 	 BIT 	 
-- 경험치 : 레벨은 경험치에 해당하는 Sys_PlayerLevel의 값에 따라 결정
,	 exp 	 INTEGER 	 
-- 퀘스트완료_카운트 : 완료 퀘스트 카운트
,	 questcomplete_count 	 SMALLINT 	 
-- 마지막경기id : 마지막으로 플레이한 경기결과 식별자
,	 last_game_result 	 INTEGER 	 
-- 특수능력이름 : Sys_PlayeSkillSticker에서의   semicolon로 구분되어 여러개입력
,	 skill_sticker 	 VARCHAR(1024) 	 
-- is_deleted
,	 is_deleted 	 SMALLINT 	 
-- 등록시간 : 최초게임등록일
,	 date_insert 	 DATETIME 	 
-- 수정된시간 : 마지막수정시간
,	 date_update 	 DATETIME 	 
-- ELO_포인트 : 경기마다 캐릭터에 갱신되는 매칭용 포인트
,	 elo_point 	 INTEGER 	 
-- 소속팀id : 소속된 팀번호
,	 team 	 INTEGER 	 
);