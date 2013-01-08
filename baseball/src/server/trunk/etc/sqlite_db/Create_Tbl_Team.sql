

DROP TABLE IF EXISTS Tbl_Team;
CREATE TABLE Tbl_Team (
	-- ������_�� : ��Ż �� ī��Ʈ
		 win_tot 	 INTEGER 	 
	-- ������ : �������� �¸��� ����. ������ ����
	,	 win_tot_continue 	 INTEGER 	 
	-- �ִ뿬�� : �ִ뿬��
	,	 win_tot_continue_max 	 INTEGER 	 
	-- ������_�� : ��Ż �� ī��Ʈ
	,	 lose_tot 	 INTEGER 	 
	-- ��������_�� : ���� �� ī��Ʈ(3����)
	,	 win_season 	 INTEGER 	 
	-- ��������_�� : ���� �� ī��Ʈ(3����)
	,	 lose_season 	 INTEGER 	 
	-- �̱�-������_�� : ��Ż �� ī��Ʈ
	,	 win_tot_single 	 INTEGER 	 
	-- �̱�-������ : �������� �¸��� ����. ������ ����
	,	 win_tot_single_continue 	 INTEGER 	 
	-- �̱�-�ִ뿬�� : �̱�-�ִ뿬��
	,	 win_tot_single_continue_max 	 INTEGER 	 
	-- �̱�-������_�� : ��Ż �� ī��Ʈ
	,	 lose_tot_single 	 INTEGER 	 
	-- �̱�-��������_�� : ���� �� ī��Ʈ(3����)
	,	 win_season_single 	 INTEGER 	 
	-- �̱�-��������_�� : ���� �� ī��Ʈ(3����)
	,	 lose_season_single 	 INTEGER 	 
	-- ģ�����-������_�� : ��Ż �� ī��Ʈ
	,	 win_tot_friend 	 INTEGER 	 
	-- ģ�����-������ : �������� �¸��� ����. ������ ����
	,	 win_tot_friend_continue 	 INTEGER 	 
	-- ģ�����-�ִ뿬 : ģ��-�ִ뿬
	,	 win_tot_friend_continue_max 	 INTEGER 	 
	-- ģ�����-������_�� : ��Ż �� ī��Ʈ
	,	 lose_tot_friend 	 INTEGER 	 
	-- ģ�����-��������_�� : ���� �� ī��Ʈ(3����)
	,	 win_season_friend 	 INTEGER 	 
	-- ģ�����-��������_�� : ���� �� ī��Ʈ(3����)
	,	 lose_season_friend 	 INTEGER 	 
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