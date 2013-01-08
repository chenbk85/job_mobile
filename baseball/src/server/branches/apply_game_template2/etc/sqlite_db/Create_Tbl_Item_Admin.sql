

DROP TABLE IF EXISTS Tbl_Item_Admin;
CREATE TABLE Tbl_Item_Admin (
-- �����ĺ��� : db pk
	 db_id 	 INTEGER 	 PRIMARY KEY AUTOINCREMENT
-- ���Ӱ���ĺ��� : ����������ǰ�� �ش����� �ĺ���
,	 rid 	 INTEGER 	 
-- ����ĳ�� : ���Ž� ����� ����ĳ��
,	 bought_real_money 	 INT 	 
-- ��������Ʈ : ���Ž� ����� ����Ʈ
,	 bought_point_money 	 INT 	 
-- ���Ű��ӸӴ� : ���Ž� ����� ���ӸӴ�
,	 bought_game_money 	 INT 	 
-- ���Ż��� : ������ȹ���� ���� ( ���������  �Ǵ� ��������  or �̺�Ʈ)
,	 item_buy_type 	 VARCHAR(256) 	 
-- �����ǸŹ�ȣ : �������κ��� �����Ѱ�� �����Ǹ�����
,	 shop_id 	 SMALLINT 	 
);