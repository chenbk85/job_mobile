

DROP TABLE IF EXISTS Tbl_PlayerBetter;
CREATE TABLE Tbl_PlayerBetter (
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
-- Ÿ�� : 0.001 - 0.999 õ������ ǥ��
,	 batting_average 	 SMALLINT 	 
-- ����Ȩ���� : ����_Ȩ����
,	 continue_homerun_count 	 SMALLINT 	 
-- ��_Ȩ���� : ��_Ȩ����
,	 homeruntotal_count 	 SMALLINT 	 
-- �̱�Ȩ��ī��Ʈ : �̱�Ȩ�� ī��Ʈ
,	 single_homerun_count 	 SMALLINT 	 
-- ����Ȩ��ī��Ʈ : ����Ȩ�� ī��Ʈ
,	 tworun_homerun_count 	 SMALLINT 	 
-- ������Ȩ��ī��Ʈ : ������Ȩ�� ī��Ʈ
,	 threerun_homerun_count 	 SMALLINT 	 
-- ����Ȩ��ī��Ʈ : ����Ȩ�� ī��Ʈ
,	 grandslam_homerun_count 	 SMALLINT 	 
-- �Ϸ�Ÿī��Ʈ : �Ϸ�Ÿ ī��Ʈ
,	 one_hit_count 	 SMALLINT 	 
-- �̷�Ÿī��Ʈ : �̷�Ÿ ī��Ʈ
,	 double_hit_count 	 SMALLINT 	 
-- ���Ÿī��Ʈ : ���Ÿ ī��Ʈ
,	 triple_hit_count 	 SMALLINT 	 
-- �Ŀ�ī��Ʈ : �Ŀ� ī��Ʈ
,	 foul_hit_count 	 SMALLINT 	 
-- �ƿ�ī��Ʈ : �ƿ� ī��Ʈ
,	 out_hit_count 	 SMALLINT 	 
-- ����ī��Ʈ : ���� ī��Ʈ
,	 score_count 	 SMALLINT 	 
-- Ÿ��Ÿ�� : Ÿ�� ������ ��ų
,	 betting_type 	 TINYINT 	 
-- Ÿ���� : Ÿ�� ��
,	 betting_form 	 TINYINT 	 
-- Ÿ�� �Ŀ�
,	 better_power 	 SMALLINT 	 
-- Ÿ�� ����
,	 better_focus 	 SMALLINT 	 
-- Ÿ�� �Ŀ� ����
,	 better_power_buff 	 SMALLINT 	 
-- Ÿ�� ���� ����
,	 better_focus_buff 	 SMALLINT 	 
);