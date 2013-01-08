

DROP TABLE IF EXISTS Tbl_Result;
CREATE TABLE Tbl_Result (
-- game������ȣ
	 db_id 	 INTEGER 	 PRIMARY KEY AUTOINCREMENT
-- is_singlemode : 0=��Ƽ�÷��� 1=�̱��÷���
,	 is_singlemode 	 BIT 	 
-- ������ȣ : ���� ������ȣ
,	 win_uid 	 INTEGER 	 
-- Ÿ�� pid : ����
,	 win_better 	 INTEGER 	 
-- ���� pid : ����
,	 win_pitcher 	 INTEGER 	 
-- ��id
,	 win_team 	 INTEGER 	 
-- ���ڽ��ھ�
,	 win_score 	 TINYINT 	 
-- ���� �������ġ : �÷��̾�1�� �������ġ( ����Ÿ�ڸ������)
,	 win_reward_exp 	 INTEGER 	 
-- ���� ������ӸӴ� : ������ӸӴ�
,	 win_reward_gamemoney 	 INT 	 
-- ������ȣ : ���� ������ȣ
,	 lose_uid 	 INTEGER 	 
-- Ÿ�� pid : ����
,	 lose_better 	 INTEGER 	 
-- ���� pid : ����
,	 lose_pitcher 	 INTEGER 	 
-- ������id
,	 lose_team 	 INTEGER 	 
-- ���ڽ��ھ�
,	 lose_score 	 TINYINT 	 
-- ���� �������ġ : �������ġ
,	 lose_reward_exp 	 INTEGER 	 
-- ���� ������ӸӴ� : ������ӸӴ�
,	 lose_reward_gamemoney 	 INT 	 
-- �÷��̽ð� : �÷��� �� �ð�(��)
,	 play_time_sec 	 INTEGER 	 
-- �Ǹ��÷�������Ʈ
,	 pp_point 	 INTEGER 	 
-- ��������ð� : �÷��� �ð� (2012-12-15 13:53:15)
,	 time_end 	 DATETIME 	 
);