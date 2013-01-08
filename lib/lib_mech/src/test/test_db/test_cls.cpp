#include "stdafx.h"
#include <stdio.h>
#include <conio.h> // ���� ���� getch() �Լ��� ����
#include <Windows.h>

void cls(HANDLE hConsole);


int test_cls(void) {
	puts("�̷����� ���ڿ���...");
	puts("�̷����� ���ڿ���...");
	puts("�̷����� ���ڿ���...");
	puts("");
	puts("���� ȭ���� ����ڽ��ϴ�. �ƹ� Ű�� ��������.");
	_getch(); // ȭ�� ����


	// ���� ����â�� ���� �ڵ� ���
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	cls(hConsole);

	return 0;
}




// ���� �ҽ�: http://support.microsoft.com/kb/q99261/
// ���⼭����, ȭ�� ����� �Լ��� ���۵�


/* Standard error macro for reporting API errors */
#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s     on line %d\n", __FILE__, GetLastError(), api, __LINE__);}

void cls( HANDLE hConsole =0)
{
	if(hConsole ==0)
	{
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	COORD coordScreen = { 0, 0 };    /* here's where we'll home the
									 cursor */
	BOOL bSuccess;
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
	DWORD dwConSize;                 /* number of character cells in
									 the current buffer */

	/* get the number of character cells in the current buffer */

	bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
	PERR( bSuccess, "GetConsoleScreenBufferInfo" );
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	/* fill the entire screen with blanks */

	bSuccess = FillConsoleOutputCharacter( hConsole, (TCHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten );
	PERR( bSuccess, "FillConsoleOutputCharacter" );

	/* get the current text attribute */

	bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
	PERR( bSuccess, "ConsoleScreenBufferInfo" );

	/* now set the buffer's attributes accordingly */

	bSuccess = FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten );
	PERR( bSuccess, "FillConsoleOutputAttribute" );

	/* put the cursor at (0, 0) */

	bSuccess = SetConsoleCursorPosition( hConsole, coordScreen );
	PERR( bSuccess, "SetConsoleCursorPosition" );
	return;
}