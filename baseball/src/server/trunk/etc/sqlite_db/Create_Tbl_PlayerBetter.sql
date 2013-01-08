

DROP TABLE IF EXISTS Tbl_PlayerBetter;
CREATE TABLE Tbl_PlayerBetter (
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
-- 총_홈런수 : 총_홈런수
,	 homerun 	 SMALLINT 	 
-- 연속홈런수 : 연속_홈런수
,	 homerun_continue 	 SMALLINT 	 
-- 최대 연속홈런수 : 최대로 연속홈런한수
,	 homerun_continue_max 	 SMALLINT 	 
-- 싱글홈런카운트 : 싱글홈런 카운트
,	 homerun1 	 SMALLINT 	 
-- 더블홈런카운트 : 더블홈런 카운트
,	 homerun2 	 SMALLINT 	 
-- 쓰리런홈런카운트 : 쓰리런홈런 카운트
,	 homerun3 	 SMALLINT 	 
-- 만루홈런카운트 : 만루홈런 카운트
,	 homerun4 	 SMALLINT 	 
-- 일루타카운트 : 일루타 카운트
,	 hit1 	 SMALLINT 	 
-- 이루타카운트 : 이루타 카운트
,	 hit2 	 SMALLINT 	 
-- 삼루타카운트 : 삼루타 카운트
,	 hit3 	 SMALLINT 	 
-- 파울카운트 : 파울 카운트
,	 foul 	 SMALLINT 	 
-- 아웃카운트 : 아웃 카운트
,	 out 	 SMALLINT 	 
-- 점수카운트 : 점수 카운트
,	 score 	 SMALLINT 	 
-- 타자타입 : 타자 대투수 스킬.선수생성시 기본으로 한 개가지며 여러 개 추가시는 Tbl_PlayerSkillSticker에 저
,	 betting_type 	 TINYINT 	 
-- 타격폼 : 타자 폼
,	 betting_form 	 TINYINT 	 
-- 타자 파워스탯 : 선수스탯
,	 better_power 	 SMALLINT 	 
-- 타자 집중스탯 : 선수스탯
,	 better_focus 	 SMALLINT 	 
-- 타자 파워 버프
,	 better_power_buff 	 SMALLINT 	 
-- 타자 집중 버프
,	 better_focus_buff 	 SMALLINT 	 
);