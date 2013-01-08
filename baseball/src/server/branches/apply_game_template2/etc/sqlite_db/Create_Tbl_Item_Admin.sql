

DROP TABLE IF EXISTS Tbl_Item_Admin;
CREATE TABLE Tbl_Item_Admin (
-- 고유식별자 : db pk
	 db_id 	 INTEGER 	 PRIMARY KEY AUTOINCREMENT
-- 게임결과식별자 : 보상아이템의경우 해당경기결과 식별자
,	 rid 	 INTEGER 	 
-- 구매캐쉬 : 구매시 사용한 리얼캐쉬
,	 bought_real_money 	 INT 	 
-- 구매포인트 : 구매시 사용한 포인트
,	 bought_point_money 	 INT 	 
-- 구매게임머니 : 구매시 사용한 게임머니
,	 bought_game_money 	 INT 	 
-- 구매상태 : 아이템획득경로 정보 ( 보상아이템  또는 상점구매  or 이벤트)
,	 item_buy_type 	 VARCHAR(256) 	 
-- 상점판매번호 : 상점으로부터 구매한경우 상점판매정보
,	 shop_id 	 SMALLINT 	 
);