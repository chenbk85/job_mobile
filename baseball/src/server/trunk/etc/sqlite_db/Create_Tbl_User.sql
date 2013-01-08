

DROP TABLE IF EXISTS Tbl_User;
CREATE TABLE Tbl_User (
-- ������ȣ
	 db_id 	 INTEGER 	 PRIMARY KEY
-- �Ǹ�ID : MemberInfo�� (game_id)�Ǹ����� �� id�� �״�� ���
,	 pp_id 	 INTEGER 	 
-- HOST_TYPE : 0-pp user 1-facebook 2-ī��
,	 host_type 	 VARCHAR(32) 	 
-- �г��� : ���̽��������� �����г���
,	 uname 	 VARCHAR(32) 	 
-- ��Disconnect�� : �����߰��� ������
,	 discon_tot 	 INTEGER 	 
-- ������_�� : ��Ż �� ī��Ʈ
,	 win_tot 	 INTEGER 	 
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
-- ��_Ȩ���� : Ÿ����_Ȩ��
,	 batter_tot_homerun 	 SMALLINT 	 
-- Ż������ : ������_Ż����
,	 pitcher_tot_strikeout 	 SMALLINT 	 
-- ���� ��_Ȩ���� : ���� Ÿ����_Ȩ��
,	 batter_tot_homerun_season 	 SMALLINT 	 
-- ���� Ż������ : ���� ������_Ż����
,	 pitcher_tot_strikeout_season 	 SMALLINT 	 
-- ELO_����Ʈ : ��⸶�� ĳ���Ϳ� ���ŵǴ� ��Ī�� ����Ʈ
,	 elo_point 	 INTEGER 	 
-- ĳ���۱��Ŵ����� : ĳ���۱��� ������
,	 cash_item_buy_money_amount 	 INTEGER 	 
-- �������α�ð� : �������α�ð�
,	 time_last_login 	 DATETIME 	 
-- �������α׾ƿ��ð� : ������ �α׾ƿ��ð�
,	 time_last_logout 	 DATETIME 	 
-- �����⼮�ϼ� : �����⼮�� �ϼ�
,	 day_continue_attend 	 SMALLINT 	 
-- client_os : Ŭ�� OS ( IOS  ANDROID )
,	 client_os 	 VARCHAR(32) 	 
-- client_networ : Ŭ�� ��Ʈ��(3G 4G WIFI)
,	 client_networ 	 VARCHAR(32) 	 
-- ��_�÷���_Ÿ�� : ��_�÷���_Ÿ��(��)
,	 playtime_tot 	 INTEGER 	 
);