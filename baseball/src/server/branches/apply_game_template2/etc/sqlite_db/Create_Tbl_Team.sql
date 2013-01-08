

DROP TABLE IF EXISTS Tbl_Team;
CREATE TABLE Tbl_Team (
	-- ������_�� : ��Ż �� ī��Ʈ
		 win_tot 	 INTEGER 	 
	-- ������_�� : ��Ż �� ī��Ʈ
	,	 lose_tot 	 INTEGER 	 
	-- ��������_�� : ���� �� ī��Ʈ(3����)
	,	 win_season 	 INTEGER 	 
	-- ��������_�� : ���� �� ī��Ʈ(3����)
	,	 lose_season 	 INTEGER 	 
	-- ���� : �������� �¸��� ����. ������ ����
	,	 win_continue 	 SMALLINT 	 
	-- �̱�-������_�� : ��Ż �� ī��Ʈ
	,	 win_tot_single 	 INTEGER 	 
	-- �̱�-������_�� : ��Ż �� ī��Ʈ
	,	 lose_tot_single 	 INTEGER 	 
	-- �̱�-��������_�� : ���� �� ī��Ʈ(3����)
	,	 win_season_single 	 INTEGER 	 
	-- �̱�-��������_�� : ���� �� ī��Ʈ(3����)
	,	 lose_season_single 	 INTEGER 	 
	-- �̱�-������ : �������� �¸��� ����. ������ ����
	,	 win_continue_single 	 SMALLINT 	 
-- ������ȣ
	 db_id 	 INTEGER 	 PRIMARY KEY AUTOINCREMENT
-- ���̸� : ����Ʈ���� pp_name�̴�
,	 name 	 VARCHAR(32) 	 
-- ����id
,	 uid 	 INTEGER 	 
-- Ÿ��
,	 pid_better 	 INTEGER 	 
-- ����
,	 pid_pitcher 	 INTEGER 	 
-- �����÷��� : �������� �����Ȱ�.�Ǵ� ���¡���� ��������
,	 is_deleted 	 SMALLINT 	 
);