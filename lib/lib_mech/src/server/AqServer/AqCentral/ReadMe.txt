콘솔 커맨드에서

@ 로 시작하면 nCONSOLE::Get_jIConsoleCmd()->ParseCmd(szCmd);로 처리
# 으로 시작하면 SQ스크립트로 처리
$ 로 시작하면 $<서버태그> <명령리스트>로 파싱되어 원격서버의 nCONSOLE::Get_jIConsoleCmd()->ParseCmd(szCmd);로 처리


<서버태그>의 종류
L , T ,D , DC ,W , U