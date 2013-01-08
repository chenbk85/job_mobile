// AqCilent.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "windows.h"
#include "conio.h"


int _tmain(int argc, _TCHAR* argv[])
{
	void Init_net();Init_net();
//	g_Net->console_parsor(_T("@test.login 127.0.0.1:33100 test1 1234"));


	printf("\n\n[Input Command...]\nC : Connect\nS : Select\nE : Enter Town\nR : Create Avatar\nD : Delete Avatar\nM : Send Msg\nQ : Quit\n");
	int c;
	while((c=getchar()) !='Q'){
		switch(c){
			case 'C' :
				g_Net->console_parsor(_T("@test.login 127.0.0.1:33100 test1 1234"));
				break;
			case 'S' :
				void select_avatar(avatarid_t ); select_avatar(1);	
				break;
			case 'E' :
				void enter_town()	; enter_town();	
				break;
			case 'R' :
				g_Net->Send_X2T_AVATAR_CREATE(1,L"kenshin");
				break;
			case 'D':
				void delete_avatar(avatarid_t ); delete_avatar(3);	
				break;
			case 'M' :
				void send_Msg(); send_Msg();
				break;
			case '\n':
				continue;
			default :
				printf("Wrong Message..\n");
				break;

		}
	}
	
//	_getch();
	return 0;
}

