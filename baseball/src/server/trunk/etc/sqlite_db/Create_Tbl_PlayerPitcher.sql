

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
-- �Ǿ�Ÿ�� : �Ǿ�Ÿ��
,	 hit_count 	 SMALLINT 	 
-- Ż������ : Ż������
,	 strikeout 	 SMALLINT 	 
-- ���ӻ����� : ���ӻ�����
,	 strikeout_continue 	 SMALLINT 	 
-- ���ӻ���_�ִ�� : ���ӻ���_�ִ��
,	 strikeout_continue_max 	 SMALLINT 	 
-- ��Ȩ���� : ��Ȩ����
,	 homerun_pitching 	 SMALLINT 	 
-- ������Ȩ���� : ������Ȩ����
,	 homerun_pitching_continue 	 SMALLINT 	 
-- ������Ȩ��_�ִ�� : ������Ȩ��_�ִ��
,	 homerun_pitching_continue_max 	 SMALLINT 	 
-- ����Ÿ�� : ���� ��Ÿ�� ��ų. ���������� �⺻���� �� �������� ���� �� �߰��ô� Tbl_PlayerSkillSticker�� ����
,	 pitcher_type 	 VARCHAR(256) 	 
-- ������ : ���� ��
,	 pitcher_form 	 VARCHAR(256) 	 
-- ���� �������� : ��������
,	 pitcher_control 	 SMALLINT 	 
-- ���� ���ӽ��� : ��������
,	 pitcher_ballspeed 	 SMALLINT 	 
-- ������ȭ���������� : �����Ҽ� �ִ� ��ȭ����
,	 pitcher_breakingball 	 SMALLINT 	 
-- ���� ���� ����
,	 pitcher_control_buff 	 SMALLINT 	 
-- ���� ���� ����
,	 pitcher_ballspeed_buff 	 SMALLINT 	 
-- ���� ��ȭ�� ��ġ ����
,	 pitcher_breakingball_value_buff 	 SMALLINT 	 
);