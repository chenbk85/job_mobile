use DG_Game;
-- source D:\svn\dualgo\Tool\excel\code\sql\Create_Tbl_LogTable.sql


DROP TABLE IF EXISTS Tbl_DG_LogTable;
CREATE TABLE Tbl_DG_LogTable (
-- pk�ε��� : pk�ε���
	 index_Log 	 BIGINT
-- user_id : user_id
,	 id_user 	 BIGINT 	 NOT NULL
-- room_id : room_id
,	 id_room 	 INT 	 NOT NULL
-- �α� Ÿ�� : �α� Ÿ��
,	 e_type 	 TINYINT 	 NOT NULL
-- ���� : ����
,	 nv_text 	 NVARCHAR(256)
-- �α� ��¥ : �α� ��¥
,	 t_date 	 TIMESTAMP
);

DROP TABLE IF EXISTS Tbl_DG_Notice;
CREATE TABLE Tbl_DG_Notice (
-- pk index : pk index
	 index_notice 	 INT
-- ���� �� : ���� ��
,	 t_begin 	 DATETIME
-- ������ : ������
,	 t_end 	 DATETIME
-- �������� ���� : �������� ����
,	 nv_title 	 NVARCHAR(32)
-- ���� ���� : ���� ����
,	 nv_message 	 NVARCHAR(1024)
-- ���� �� : ���� ��
,	 i_status 	 INT
-- ���� : ������=1/�ӽ�����=2/��������=3
,	 e_Type 	 TINYINT 	 DEFAULT 1
);