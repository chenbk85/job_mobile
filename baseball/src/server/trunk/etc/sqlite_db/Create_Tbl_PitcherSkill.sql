

DROP TABLE IF EXISTS Tbl_PitcherSkill;
CREATE TABLE Tbl_PitcherSkill (
-- ������ȣ
	 db_id 	 INTEGER 	 PRIMARY KEY AUTOINCREMENT
-- ������id
,	 uid 	 INTEGER 	 
-- ��������id : ����Ʈ���� pp_name�̴�
,	 pid 	 INTEGER 	 
-- ������Ÿ�� : ����������
,	 gesture 	 VARCHAR(256) 	 
-- �����÷���
,	 is_deleted 	 SMALLINT 	 
-- ������ȭ�� ���� �ð� : ������ ��ȭ���� ����� �ð��� ���
,	 exp 	 INTEGER 	 
-- ������ȭ������ : ���� ��ȭ������
,	 type 	 VARCHAR(256) 	 
);