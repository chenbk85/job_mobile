/* file : ReadMe.txt
Coder : by icandoit ( mech12@nate.com)
Date : 2008-03-24 18:09:07
comp.: www.actoz.com
title : 
desc : 

*/



enum 테이블(필드 4개)
	규칙명	규칙값	name_eng	설명

Sys , Tbl , App 테이블 ( 필드 7개)
	Name_eng	,자료형	,min	,max	,DB TYPE	,Type Note,	설명




const int jCURR_VERSION 로그;

1005 - #define jTYPE_INFO_DEF처리 추가

실행시 <Excel_Converter>의 항목은  version바낄때마다 삭제되고 새로 작성됨
<TYPE_INFO>의 디펄드 자료형들은 실행시마다 디펄트값으로 변경된다.



최종적으로 다음명령이 수행된다.
__merge_create_sql.bat