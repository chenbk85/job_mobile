

DROP TABLE IF EXISTS Tbl_PlayerPitcher;
CREATE TABLE Tbl_PlayerPitcher (
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
-- 방어율 : 0.001 - 0.999 천분율로 표시
,	 pitching_average 	 SMALLINT 	 
-- 피안타율 : 피안타율
,	 hit_count 	 SMALLINT 	 
-- 탈삼진수 : 탈삼진수
,	 strikeout_count 	 SMALLINT 	 
-- 피홈런수 : 피홈런수
,	 homerun_pitching_count 	 SMALLINT 	 
-- 연속삼진수 : 연속삼진수
,	 continue_strikeout_count 	 SMALLINT 	 
-- 연속피홈런수 : 연속피홈런수
,	 continue_homerun_pitching_count 	 SMALLINT 	 
-- 투수타입 : 투수 대타자 스킬
,	 pitcher_type 	 VARCHAR(256) 	 
-- 투구폼 : 투수 폼
,	 pitcher_form 	 VARCHAR(256) 	 
-- 투수 제구
,	 pitcher_control 	 SMALLINT 	 
-- 투수 구속
,	 pitcher_ballspeed 	 SMALLINT 	 
-- 투수 제구 버프
,	 pitcher_control_buff 	 SMALLINT 	 
-- 투수 구속 버프
,	 pitcher_ballspeed_buff 	 SMALLINT 	 
-- 투수 변화구 수치 버프
,	 pitcher_breakingball_value_buff 	 SMALLINT 	 
);