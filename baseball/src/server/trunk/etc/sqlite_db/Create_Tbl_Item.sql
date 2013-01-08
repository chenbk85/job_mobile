

DROP TABLE IF EXISTS Tbl_Item;
CREATE TABLE Tbl_Item (
-- 고유식별자 : db pk
	 db_id 	 INTEGER 	 PRIMARY KEY AUTOINCREMENT
-- 구매한 아이템종류 : Sys__ItemBase_id_t
,	 sid 	 SMALLINT 	 
-- 대분류 : 장비 스텁 소비 구분
,	 category 	 VARCHAR(256) 	 
-- 소유자id
,	 uid 	 INTEGER 	 
-- 귀속된선수ID : 귀속된 선수id이며 소모용아이템은 특별히귀속되지않고쓴다.캐쉬인벤 or 게임인벤 환불여부가 결정된다
,	 used_player_id 	 INTEGER 	 
-- 소유한타자투수구분 : true=타자 false=투수
,	 is_better 	 BIT 	 
-- 업그레이드등급 : baseball.xml에서 ITEM_UPGRADE_LOGIC 참조
,	 upgrade_level 	 VARCHAR(32) 	 
-- 업그레이드진행완료시간 : 현제시간보다 미래의 시간이 세팅되면 업그레이드상태이다.
,	 date_end_upgrade 	 DATETIME 	 
-- 기타정보 : 등번호 아이템:BACKNUM=등번호. 마킹아이템:MARK=NAME. INSERT_TYPE=Q:NAME | BONUS | ADMIN | SHOP
,	 etc_info 	 VARCHAR(256) 	 
-- 장착상태 : 장착아이템의경우 장착상태인지 여부
,	 is_equiped 	 BIT 	 
-- 기간제아이템의사용시간 : 기간제아이템의경우 사용가능한 시간
,	 date_expire 	 DATETIME 	 
-- 구매한날짜 : 구매한날짜
,	 date_insert 	 DATETIME 	 
-- 수정된시간 : 마지막수정시간
,	 date_update 	 DATETIME 	 
-- 삭제플레그 : 아이템이 삭제된것.또는 어뷰징으로 제제상태
,	 is_deleted 	 SMALLINT 	 
-- 아이템상태
,	 state 	 VARCHAR(256) 	 
-- 사용가능한 경기횟수 : 소비(컨슘)의경우 사용가능한 게임의 경기 횟수. 재료(스텁)의경우 보유갯수(중첩갯수) 장착아이템은 값이 0
,	 use_count 	 SMALLINT 	 
);