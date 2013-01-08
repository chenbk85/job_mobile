

DROP TABLE IF EXISTS Tbl_RoundResult;
CREATE TABLE Tbl_RoundResult (
-- ������ȣ : �Ϻ� ��Ƽ�� Ű
	 db_id 	 INTEGER 	 PRIMARY KEY AUTOINCREMENT
-- Tbl_Result���̺��� ������ȣ
,	 grid 	 INTEGER 	 
-- ���� �� Ÿ�� id : ���� �� Ÿ�� id (8��)
,	 used_batter_id 	 SMALLINT 	 
-- ���� �� ���� id : ���� �� ���� id (8��)
,	 used_pitcher_id 	 SMALLINT 	 
-- �����ȣ : 1���ͽ���. 1~10�� ���� �Ѱ����� ��Ż����� Tbl_Result�� ����
,	 round_number 	 TINYINT 	 
-- ������ ��� ���� : ����� ������ ����
,	 used_breakingball 	 VARCHAR(256) 	 
-- ������ ��� ������ ���� : ����� ������ �ӵ�
,	 used_breakingball_speed 	 SMALLINT 	 
-- ����ϰ� �ִ� ������ ��ų(��ȭ�� ����) : ���ݿ� ������ �� ������ Ư���ɷ�
,	 used_pitcherability 	 VARCHAR(256) 	 
-- ���� �� ���� Ÿ�̹� : ���� �� ���� Ÿ�̹��� ����
,	 pitching_rhythm_judge 	 TINYINT 	 
-- ����� ����ó ���� : ����� ����ó ����
,	 used_gesturetype 	 VARCHAR(256) 	 
-- ����ó �Է� ���� Ƚ�� : ����ó �Է� ���� Ƚ��
,	 gesturetype_input_error 	 SMALLINT 	 
-- Ÿ�� ��Ʈ �� ���� �� Ǯ�Ŀ� ��� : Ÿ�� ��Ʈ�� ����(�Ϲ���Ʈ_��Ʈ����Ʈ_�꽺��_������)
,	 used_batting_fullpower 	 TINYINT 	 
-- Ÿ�� �� ���� �� Ÿ�� Ÿ�̹� : Ÿ�� �� Ÿ�̹� ����(veryfast_fast_goodfast_perfect_goodslow_slow_veryslow)
,	 batting_timing_judge 	 TINYINT 	 
-- Ÿ�� �� ���� �� ��Ʈ Ÿ�� : Ÿ�� �� ��Ʈ Ÿ��
,	 batting_hittype 	 TINYINT 	 
-- uid_attack : ������
,	 uid_attack 	 INTEGER 	 
-- better������
,	 score 	 TINYINT 	 
-- ��������ڼ� : bit flag�� ����� ���ڻ��¸� ǥ���Ѵ�. 1��� 2^0 �ִ�� xml����  i_max_runner_per_game=19�̴�
,	 base_runner_state 	 TINYINT 	 
-- ��Ÿ����
,	 hit_type 	 TINYINT 	 
);