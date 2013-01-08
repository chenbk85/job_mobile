

DROP TABLE IF EXISTS Tbl_User;
CREATE TABLE Tbl_User (
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
-- ������ȣ : db pk �Ǹ����� �� id�� �״�� ���
	 db_id 	 INTEGER 	 PRIMARY KEY
-- �г��� : ���̽��������� �����г���
,	 uname 	 VARCHAR(32) 	 
-- ��Disconnect�� : �����߰��� ������
,	 discon_tot 	 INTEGER 	 
-- Ż������ : ������_Ż����
,	 pitcher_tot_strikeout 	 SMALLINT 	 
-- ���������_���� : ���������_���� �ַ� ����� �����ΰ�
,	 pitcher_tot_average_level 	 SMALLINT 	 
-- ��_Ȩ���� : Ÿ����_Ȩ��
,	 better_tot_homerun 	 SMALLINT 	 
-- Ÿ�������_���� : Ÿ�������_����
,	 better_tot__average_level 	 SMALLINT 	 
-- ĳ���۱��Ű��� : ĳ���۱��Ű���
,	 cash_item_buy_count 	 SMALLINT 	 
-- �������α�ð� : �������α�ð�
,	 time_last_login 	 DATETIME 	 
-- �������α׾ƿ��ð� : ������ �α׾ƿ��ð�
,	 time_last_logout 	 DATETIME 	 
-- �����⼮�ϼ� : �����⼮�� �ϼ�
,	 day_continue_attend 	 SMALLINT 	 
-- ��Ͻð� : ���ʰ��ӵ����
,	 date_insert 	 DATETIME 	 
-- �����Ƚð� : �����������ð�
,	 date_update 	 DATETIME 	 
-- �⺻����ȣ : �⺻�� index
,	 default_tid 	 INTEGER 	 
-- �ɼ� : �ɼ�(Ŭ�󿡼����Ƿ������ҳ���)
,	 option 	 VARCHAR(1024) 	 
-- �̱��÷��̺���ī��Ʈ : �Ϸ翡 �߱޵� �̱��÷��� �������ġ Ƚ��
,	 singleplay_gift_count 	 SMALLINT 	 
-- �����÷��� : �������� �����Ȱ�.�Ǵ� ���¡���� ��������
,	 is_deleted 	 SMALLINT 	 
-- ���ӸӴ�
,	 game_money 	 INTEGER 	 
-- client_os : Ŭ�� OS ( IOS / ANDROID )
,	 client_os 	 VARCHAR(32) 	 
-- client_networ : Ŭ�� ��Ʈ��(3G, 4G, WIFI)
,	 client_networ 	 VARCHAR(32) 	 
-- ��_�÷���_Ÿ�� : ��_�÷���_Ÿ��(��)
,	 playtime_tot 	 INTEGER 	 
);