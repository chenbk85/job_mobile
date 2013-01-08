

DROP TABLE IF EXISTS Tbl_RoundResult;
CREATE TABLE Tbl_RoundResult (
-- 고유번호 : 일별 파티션 키
	 db_id 	 INTEGER 	 PRIMARY KEY AUTOINCREMENT
-- Tbl_Result_M의 고유번호
,	 grid 	 INTEGER 	 
-- 라운드번호 : 1부터시작. 1~10은 라운드 한게임의 토탈집계는 Tbl_Result에 저장
,	 round_number 	 TINYINT 	 
-- 투수의 좌투우투 구분 : 캐릭터의 좌우 구분 1이면 좌선수 0이면 우선수
,	 is_left 	 BIT 	 
-- 투수의 사용 구종 : 사용한 구종의 종류
,	 used_breakingball 	 VARCHAR(256) 	 
-- 투수의 사용 구종의 구속 : 사용한 구종의 속도
,	 used_breakingball_speed 	 SMALLINT 	 
-- 사용하고 있는 투수의 스킬(변화구 제외) : 스텟에 영향을 준 투수의 특수능력
,	 used_pitcherability 	 VARCHAR(256) 	 
-- 투구 시 제구 타이밍 : 투구 시 제구 타이밍의 종류
,	 pitching_rhythm_judge 	 TINYINT 	 
-- 투수의 사용하고 있는 아이템 : 스텟에 영향을 준 투수의 아이템
,	 used_pitcher_itemcategoryequipment 	 VARCHAR(256) 	 
-- 투수의 카운터 사용 : 0=사용하지 않앗음 1=사용 하였음
,	 used_pitcher_counter 	 BIT 	 
-- 사용하고 있는 타자의 스킬 : 스텟에 영향을 준 타자의 특수능력
,	 used_batterability 	 TINYINT 	 
-- 타자 히트 시 풀파워 사용 : 타자 히트의 종류(일반히트_스트롱히트_헛스윙_대기상태)
,	 used_batting_fullpower 	 TINYINT 	 
-- 타격 시 타격 타이밍 : 타격 시 타이밍 종류(veryfast_fast_goodfast_perfect_goodslow_slow_veryslow)
,	 batting_timing_judge 	 TINYINT 	 
-- 타자의 사용하고 있는 아이템 : 스텟에 영향을 준 타자의 아이템
,	 used_batter_itemcategoryequipment 	 VARCHAR(256) 	 
-- 타자의 카운터 사용 : 0=사용하지 않앗음 1=사용 하였음
,	 used_batter_counter 	 BIT 	 
-- uid_attack : 공격자
,	 uid_attack 	 INTEGER 	 
-- better의점수
,	 score 	 TINYINT 	 
-- 출루한주자수 : bit flag로 출루한 주자상태를 표시한다. 1루는 2^0 최대는 xml에서  i_max_runner_per_game=19이다
,	 base_runner_state 	 TINYINT 	 
-- 안타종류 : 0=아웃 1일루타 2이루타 3삼루타 4싱글홈런 5더블홈런 6
,	 hit_type 	 TINYINT 	 
);