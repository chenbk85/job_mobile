

DROP TABLE IF EXISTS Tbl_PlayerPitcher;
CREATE TABLE Tbl_PlayerPitcher (
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
-- ����� : 0.001 - 0.999 õ������ ǥ��
,	 pitching_average 	 SMALLINT 	 
-- �Ǿ�Ÿ�� : �Ǿ�Ÿ��
,	 hit_count 	 SMALLINT 	 
-- Ż������ : Ż������
,	 strikeout_count 	 SMALLINT 	 
-- ��Ȩ���� : ��Ȩ����
,	 homerun_pitching_count 	 SMALLINT 	 
-- ���ӻ����� : ���ӻ�����
,	 continue_strikeout_count 	 SMALLINT 	 
-- ������Ȩ���� : ������Ȩ����
,	 continue_homerun_pitching_count 	 SMALLINT 	 
-- ����Ÿ�� : ���� ��Ÿ�� ��ų
,	 pitcher_type 	 VARCHAR(256) 	 
-- ������ : ���� ��
,	 pitcher_form 	 VARCHAR(256) 	 
-- ���� ����
,	 pitcher_control 	 SMALLINT 	 
-- ���� ����
,	 pitcher_ballspeed 	 SMALLINT 	 
-- ���� ���� ����
,	 pitcher_control_buff 	 SMALLINT 	 
-- ���� ���� ����
,	 pitcher_ballspeed_buff 	 SMALLINT 	 
-- ���� ��ȭ�� ��ġ ����
,	 pitcher_breakingball_value_buff 	 SMALLINT 	 
);