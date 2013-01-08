

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
-- ��_Ȩ���� : ��_Ȩ����
,	 homerun 	 SMALLINT 	 
-- ����Ȩ���� : ����_Ȩ����
,	 homerun_continue 	 SMALLINT 	 
-- �ִ� ����Ȩ���� : �ִ�� ����Ȩ���Ѽ�
,	 homerun_continue_max 	 SMALLINT 	 
-- �̱�Ȩ��ī��Ʈ : �̱�Ȩ�� ī��Ʈ
,	 homerun1 	 SMALLINT 	 
-- ����Ȩ��ī��Ʈ : ����Ȩ�� ī��Ʈ
,	 homerun2 	 SMALLINT 	 
-- ������Ȩ��ī��Ʈ : ������Ȩ�� ī��Ʈ
,	 homerun3 	 SMALLINT 	 
-- ����Ȩ��ī��Ʈ : ����Ȩ�� ī��Ʈ
,	 homerun4 	 SMALLINT 	 
-- �Ϸ�Ÿī��Ʈ : �Ϸ�Ÿ ī��Ʈ
,	 hit1 	 SMALLINT 	 
-- �̷�Ÿī��Ʈ : �̷�Ÿ ī��Ʈ
,	 hit2 	 SMALLINT 	 
-- ���Ÿī��Ʈ : ���Ÿ ī��Ʈ
,	 hit3 	 SMALLINT 	 
-- �Ŀ�ī��Ʈ : �Ŀ� ī��Ʈ
,	 foul 	 SMALLINT 	 
-- �ƿ�ī��Ʈ : �ƿ� ī��Ʈ
,	 out 	 SMALLINT 	 
-- ����ī��Ʈ : ���� ī��Ʈ
,	 score 	 SMALLINT 	 
-- Ÿ��Ÿ�� : Ÿ�� ������ ��ų.���������� �⺻���� �� �������� ���� �� �߰��ô� Tbl_PlayerSkillSticker�� ��
,	 betting_type 	 TINYINT 	 
-- Ÿ���� : Ÿ�� ��
,	 betting_form 	 TINYINT 	 
-- Ÿ�� �Ŀ����� : ��������
,	 better_power 	 SMALLINT 	 
-- Ÿ�� ���߽��� : ��������
,	 better_focus 	 SMALLINT 	 
-- Ÿ�� �Ŀ� ����
,	 better_power_buff 	 SMALLINT 	 
-- Ÿ�� ���� ����
,	 better_focus_buff 	 SMALLINT 	 
);