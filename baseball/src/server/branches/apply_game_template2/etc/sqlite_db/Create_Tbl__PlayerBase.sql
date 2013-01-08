

DROP TABLE IF EXISTS Tbl__PlayerBase;
CREATE TABLE Tbl__PlayerBase (
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
-- PK index : ���� database table PK
	 db_id 	 INTEGER 	 PRIMARY KEY AUTOINCREMENT
-- Sys_Player���̵� : ������ ����ī���� ��ȣ(Sys_Player�� sid) ���� 0 �̸� ���󼱼�
,	 sid 	 SMALLINT 	 
-- ������ȣ
,	 uid 	 INTEGER 	 
-- �г���
,	 pname 	 VARCHAR(32) 	 
-- ��ű��� : ĳ�־�߱� ���ӱ�ȹ�� 3�� (20111031).docx����
,	 city 	 VARCHAR(256) 	 
-- �̴ϼ� : ������ ����. ������̴ϼȱ���. �ߺ�����
,	 initial_name 	 VARCHAR(32) 	 
-- ��ѹ� : ������ ����. ������������� ���氡��
,	 back_number 	 SMALLINT 	 
-- ���� : ������ ����.
,	 age 	 SMALLINT 	 
-- ü��
,	 body_type 	 VARCHAR(256) 	 
-- �¿�Ÿ�� : ĳ������ �¿� ���� 1�̸� �¼��� 0�̸� �켱��
,	 is_left 	 BIT 	 
-- ����ġ : ������ ����ġ�� �ش��ϴ� Sys_PlayerLevel�� ���� ���� ����
,	 exp 	 INTEGER 	 
-- ����Ʈ�Ϸ�_ī��Ʈ : �Ϸ� ����Ʈ ī��Ʈ
,	 questcomplete_count 	 SMALLINT 	 
-- ���������id : ���������� �÷����� ����� �ĺ���
,	 last_game_result 	 INTEGER 	 
-- Ư���ɷ��̸� : Sys_PlayeSkillSticker������   semicolon�� ���еǾ� �������Է�
,	 skill_sticker 	 VARCHAR(1024) 	 
-- is_deleted
,	 is_deleted 	 SMALLINT 	 
-- ��Ͻð� : ���ʰ��ӵ����
,	 date_insert 	 DATETIME 	 
-- �����Ƚð� : �����������ð�
,	 date_update 	 DATETIME 	 
-- ELO_����Ʈ : ��⸶�� ĳ���Ϳ� ���ŵǴ� ��Ī�� ����Ʈ
,	 elo_point 	 INTEGER 	 
-- �Ҽ���id : �Ҽӵ� ����ȣ
,	 team 	 INTEGER 	 
);