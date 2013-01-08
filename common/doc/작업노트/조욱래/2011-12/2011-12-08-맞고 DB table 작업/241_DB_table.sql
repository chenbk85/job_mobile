use DG_Game;
-- source D:\svn\dualgo\Tool\excel\code\sql\Create_Tbl_LogTable.sql


DROP TABLE IF EXISTS Tbl_DG_LogTable;
CREATE TABLE Tbl_DG_LogTable (
-- pk인덱스 : pk인덱스
	 index_Log 	 BIGINT
-- user_id : user_id
,	 id_user 	 BIGINT 	 NOT NULL
-- room_id : room_id
,	 id_room 	 INT 	 NOT NULL
-- 로그 타입 : 로그 타입
,	 e_type 	 TINYINT 	 NOT NULL
-- 내용 : 내용
,	 nv_text 	 NVARCHAR(256)
-- 로그 날짜 : 로그 날짜
,	 t_date 	 TIMESTAMP
);

DROP TABLE IF EXISTS Tbl_DG_Notice;
CREATE TABLE Tbl_DG_Notice (
-- pk index : pk index
	 index_notice 	 INT
-- 시작 일 : 시작 일
,	 t_begin 	 DATETIME
-- 종료일 : 종료일
,	 t_end 	 DATETIME
-- 공지사항 제목 : 공지사항 제목
,	 nv_title 	 NVARCHAR(32)
-- 공지 내용 : 공지 내용
,	 nv_message 	 NVARCHAR(1024)
-- 상태 값 : 상태 값
,	 i_status 	 INT
-- 종류 : 전광판=1/임시점검=2/공지사항=3
,	 e_Type 	 TINYINT 	 DEFAULT 1
);