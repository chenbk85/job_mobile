

DROP TABLE IF EXISTS Tbl_Item;
CREATE TABLE Tbl_Item (
-- �����ĺ��� : db pk
	 db_id 	 INTEGER 	 PRIMARY KEY AUTOINCREMENT
-- ������ ���������� : Sys__ItemBase_id_t
,	 sid 	 SMALLINT 	 
-- ��з� : ��� ���� �Һ� ����
,	 category 	 VARCHAR(256) 	 
-- ������id
,	 uid 	 INTEGER 	 
-- �ͼӵȼ���ID : �ͼӵ� ����id�̸� �Ҹ��������� Ư�����ͼӵ����ʰ���.ĳ���κ� or �����κ� ȯ�ҿ��ΰ� �����ȴ�
,	 used_player_id 	 INTEGER 	 
-- ������Ÿ���������� : true=Ÿ�� false=����
,	 is_better 	 BIT 	 
-- ���׷��̵��� : baseball.xml���� ITEM_UPGRADE_LOGIC ����
,	 upgrade_level 	 VARCHAR(32) 	 
-- ���׷��̵�����Ϸ�ð� : �����ð����� �̷��� �ð��� ���õǸ� ���׷��̵�����̴�.
,	 date_end_upgrade 	 DATETIME 	 
-- ��Ÿ���� : ���ȣ ������:BACKNUM=���ȣ. ��ŷ������:MARK=NAME. INSERT_TYPE=Q:NAME | BONUS | ADMIN | SHOP
,	 etc_info 	 VARCHAR(256) 	 
-- �������� : �����������ǰ�� ������������ ����
,	 is_equiped 	 BIT 	 
-- �Ⱓ���������ǻ��ð� : �Ⱓ���������ǰ�� ��밡���� �ð�
,	 date_expire 	 DATETIME 	 
-- �����ѳ�¥ : �����ѳ�¥
,	 date_insert 	 DATETIME 	 
-- �����Ƚð� : �����������ð�
,	 date_update 	 DATETIME 	 
-- �����÷��� : �������� �����Ȱ�.�Ǵ� ���¡���� ��������
,	 is_deleted 	 SMALLINT 	 
-- �����ۻ���
,	 state 	 VARCHAR(256) 	 
-- ��밡���� ���Ƚ�� : �Һ�(����)�ǰ�� ��밡���� ������ ��� Ƚ��. ���(����)�ǰ�� ��������(��ø����) ������������ ���� 0
,	 use_count 	 SMALLINT 	 
);