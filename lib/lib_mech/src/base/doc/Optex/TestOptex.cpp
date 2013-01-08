/******************************************************************************
Module name: TestOptex.cpp
Written by:  Jeffrey Richter
Purpose:     A simple app that test the COptec class 
NOTE:        Run multiple instances of this app to fully test the COptex
******************************************************************************/


#include <windows.h>
#include "Optex.h"


///////////////////////////////////////////////////////////////////////////////


#pragma data_seg("Shared")
int g_n= 0;
DWORD g_dw[1024] = { 0 };
#pragma data_seg()

#pragma comment(linker, "/section:Shared,rws")


///////////////////////////////////////////////////////////////////////////////


void main() {
   COptex optex("TestOptex");
   while (TRUE) {
      optex.Enter();
      if (g_n == 1024) { optex.Leave(); break; }
      g_dw[g_n++] = GetCurrentProcessId();
      optex.Leave();
   }
   GetLastError();
}


///////////////////////////////// End of File /////////////////////////////////
