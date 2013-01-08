#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>

#if 0
HANDLE hStdout; 

int ScrollByAbsoluteCoord(int iRows)
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 
	SMALL_RECT srctWindow; 

	// Get the current screen buffer size and window position. 

	if (! GetConsoleScreenBufferInfo(hStdout, &csbiInfo)) 
	{
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError()); 
		return 0;
	}

	// Set srctWindow to the current window size and location. 

	srctWindow = csbiInfo.srWindow; 

	// Check whether the window is too close to the screen buffer top

	if ( srctWindow.Top >= iRows ) 
	{ 
		srctWindow.Top -= iRows;     // move top up
		srctWindow.Bottom -= iRows;  // move bottom up

		if (! SetConsoleWindowInfo( 
			hStdout,          // screen buffer handle 
			TRUE,             // absolute coordinates 
			&srctWindow))     // specifies new location 
		{
			printf("SetConsoleWindowInfo (%d)\n", GetLastError()); 
			return 0;
		}
		return iRows;
	}
	else
	{
		printf("\nCannot scroll; the window is too close to the top.\n");
		return 0;
	}
}

int ScrollByRelativeCoord(int iRows)
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 
	SMALL_RECT srctWindow; 

	// Get the current screen buffer window position. 

	if (! GetConsoleScreenBufferInfo(hStdout, &csbiInfo)) 
	{
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError()); 
		return 0;
	}

	// Check whether the window is too close to the screen buffer top

	if (csbiInfo.srWindow.Top >= iRows) 
	{ 
		srctWindow.Top = -iRows;     // move top up
		srctWindow.Bottom = -iRows;  // move bottom up 
		srctWindow.Left = 0;         // no change 
		srctWindow.Right = 0;        // no change 

		if (! SetConsoleWindowInfo( 
			hStdout,          // screen buffer handle 
			FALSE,            // relative coordinates
			&srctWindow))     // specifies new location 
		{
			printf("SetConsoleWindowInfo (%d)\n", GetLastError()); 
			return 0;
		}
		return iRows;
	}
	else
	{
		printf("\nCannot scroll; the window is too close to the top.\n");
		return 0;
	}
}

void main()
{
	int i;

	printf("\nPrinting twenty lines, then scrolling up five lines.\n");
	printf("Press any key to scroll up ten lines; ");
	printf("then press another key to stop the demo.\n");
	for(i=0; i<=20; i++)
		printf("%d\n", i);

	_getch();
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 

	if(ScrollByAbsoluteCoord(5))
		_getch();
	else return;

	if(ScrollByRelativeCoord(10))
		_getch();
	else return;
}

#endif