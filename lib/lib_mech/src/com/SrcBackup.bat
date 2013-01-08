@echo off

rem 첫번째 인자 : 프로젝트 이름
rem 두번째 인자 : 백업 대상 디렉토리
rem 세번째 인자 : 백업 파일 저장 위치
mkdir y:\backup\jUtil
runbackup.bat "jUtil" "." "y:\Backup\jUtil"
