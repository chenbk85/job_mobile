

DROP TABLE IF EXISTS Tbl_RoundResult;
CREATE TABLE Tbl_RoundResult (
-- ������ȣ : �Ϻ� ��Ƽ�� Ű
	 db_id 	 INTEGER 	 PRIMARY KEY AUTOINCREMENT
-- Tbl_Result_M�� ������ȣ
,	 grid 	 INTEGER 	 
-- �����ȣ : 1���ͽ���. 1~10�� ���� �Ѱ����� ��Ż����� Tbl_Result�� ����
,	 round_number 	 TINYINT 	 
-- ������ �������� ���� : ĳ������ �¿� ���� 1�̸� �¼��� 0�̸� �켱��
,	 is_left 	 BIT 	 
-- ������ ��� ���� : ����� ������ ����
,	 used_breakingball 	 VARCHAR(256) 	 
-- ������ ��� ������ ���� : ����� ������ �ӵ�
,	 used_breakingball_speed 	 SMALLINT 	 
-- ����ϰ� �ִ� ������ ��ų(��ȭ�� ����) : ���ݿ� ������ �� ������ Ư���ɷ�
,	 used_pitcherability 	 VARCHAR(256) 	 
-- ���� �� ���� Ÿ�̹� : ���� �� ���� Ÿ�̹��� ����
,	 pitching_rhythm_judge 	 TINYINT 	 
-- ������ ����ϰ� �ִ� ������ : ���ݿ� ������ �� ������ ������
,	 used_pitcher_itemcategoryequipment 	 VARCHAR(256) 	 
-- ������ ī���� ��� : 0=������� �ʾ��� 1=��� �Ͽ���
,	 used_pitcher_counter 	 BIT 	 
-- ����ϰ� �ִ� Ÿ���� ��ų : ���ݿ� ������ �� Ÿ���� Ư���ɷ�
,	 used_batterability 	 TINYINT 	 
-- Ÿ�� ��Ʈ �� Ǯ�Ŀ� ��� : Ÿ�� ��Ʈ�� ����(�Ϲ���Ʈ_��Ʈ����Ʈ_�꽺��_������)
,	 used_batting_fullpower 	 TINYINT 	 
-- Ÿ�� �� Ÿ�� Ÿ�̹� : Ÿ�� �� Ÿ�̹� ����(veryfast_fast_goodfast_perfect_goodslow_slow_veryslow)
,	 batting_timing_judge 	 TINYINT 	 
-- Ÿ���� ����ϰ� �ִ� ������ : ���ݿ� ������ �� Ÿ���� ������
,	 used_batter_itemcategoryequipment 	 VARCHAR(256) 	 
-- Ÿ���� ī���� ��� : 0=������� �ʾ��� 1=��� �Ͽ���
,	 used_batter_counter 	 BIT 	 
-- uid_attack : ������
,	 uid_attack 	 INTEGER 	 
-- better������
,	 score 	 TINYINT 	 
-- ��������ڼ� : bit flag�� ����� ���ڻ��¸� ǥ���Ѵ�. 1��� 2^0 �ִ�� xml����  i_max_runner_per_game=19�̴�
,	 base_runner_state 	 TINYINT 	 
-- ��Ÿ���� : 0=�ƿ� 1�Ϸ�Ÿ 2�̷�Ÿ 3���Ÿ 4�̱�Ȩ�� 5����Ȩ�� 6
,	 hit_type 	 TINYINT 	 
);