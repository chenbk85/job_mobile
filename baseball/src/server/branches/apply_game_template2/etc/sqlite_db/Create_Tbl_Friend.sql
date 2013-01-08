

DROP TABLE IF EXISTS Tbl_Friend;
CREATE TABLE Tbl_Friend (
-- id
	 db_id 	 INTEGER 	 PRIMARY KEY AUTOINCREMENT
-- ������ȣ
,	 uid 	 INTEGER 	 
-- ģ����ȣ
,	 uid_fiend 	 INTEGER 	 
-- ģ���̸�
,	 nic_fiend 	 VARCHAR(32) 	 
-- is_blocked : ������Ʈ�̳�?
,	 is_blocked 	 BIT 	 
-- is_deleted
,	 is_deleted 	 SMALLINT 	 
-- ģ��-������_�� : ��Ż �� ī��Ʈ
,	 win_tot 	 INTEGER 	 
-- ģ��-������_�� : ��Ż �� ī��Ʈ
,	 lose_tot 	 INTEGER 	 
-- ģ��-��������_�� : ���� �� ī��Ʈ(3����)
,	 win_season 	 INTEGER 	 
-- ģ��-��������_�� : ���� �� ī��Ʈ(3����)
,	 lose_season 	 INTEGER 	 
-- ģ��-���� : �������� �¸��� ����. ������ ����
,	 win_continue 	 SMALLINT 	 
);