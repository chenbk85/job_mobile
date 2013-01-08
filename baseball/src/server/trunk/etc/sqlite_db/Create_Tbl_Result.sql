

DROP TABLE IF EXISTS Tbl_Result;
CREATE TABLE Tbl_Result (
-- game������ȣ
	 db_id 	 INTEGER 	 PRIMARY KEY AUTOINCREMENT
-- ������ȣ : ���� ������ȣ
,	 win_uid 	 INTEGER 	 
-- Ÿ�� pid : ����
,	 win_better 	 INTEGER 	 
-- ���� pid : ����
,	 win_pitcher 	 INTEGER 	 
-- ���ڽ��ھ�
,	 win_score 	 TINYINT 	 
-- ELO_����Ʈ : ��⿡�� �� ���� �� ����ڿ��� �÷��� �Ǵ� ��Ī�� ����Ʈ
,	 win_elo_point 	 INTEGER 	 
-- ������ȣ : ���� ������ȣ
,	 lose_uid 	 INTEGER 	 
-- Ÿ�� pid : ����
,	 lose_better 	 INTEGER 	 
-- ���� pid : ����
,	 lose_pitcher 	 INTEGER 	 
-- ���ڽ��ھ�
,	 lose_score 	 TINYINT 	 
-- ELO_����Ʈ : ��⿡�� �� ���� ��  ����ڿ��� ���̳ʽ� �Ǵ� ��Ī�� ����Ʈ
,	 lose_elo_point 	 INTEGER 	 
-- �÷��̽ð� : �÷��� �� �ð�(��)
,	 play_time_sec 	 INTEGER 	 
-- ��������ð� : �÷��� �ð� (2012-12-15 13:53:15)
,	 time_end 	 DATETIME 	 
);