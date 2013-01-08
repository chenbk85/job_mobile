/********************************************************************
Module name: HWInputMon.cpp
Notices: Written 1998 by Jeffrey Richter
Description: App to monitor keyboard & mouse performance info.
********************************************************************/


#include "CmnHdr.h"
#include <Windows.h>
#include <WindowsX.h>
#include <Math.h>
#include <TChar.h>
#include "HWInputPrfDataMap.h"


/////////////////////////////////////////////////////////////////////


LRESULT CALLBACK LowLevelKeyboardProc(int nCode, 
   WPARAM wParam, LPARAM lParam) {

   if (nCode == HC_ACTION) {
      switch (wParam) {
         case WM_KEYDOWN:  case WM_SYSKEYDOWN:
         case WM_KEYUP:    case WM_SYSKEYUP: 
            g_PrfData.GetCtr32(HWINPUT_KEYS)++; 
            g_PrfData.GetCtr32(HWINPUT_KEYSPERSEC)++;
            break;
      }
   }
   return(CallNextHookEx(NULL, nCode, wParam, lParam));
}


/////////////////////////////////////////////////////////////////////


typedef enum { 
   mciFirst = 0, 
   mciTotal = mciFirst, 
   mciLeft, 
   mciMiddle, 
   mciRight,
   mciLast = mciRight
} MOUSECLCKINST;

CPrfData::INSTID g_MouseClckInstToPrfInstId[mciLast + 1];


/////////////////////////////////////////////////////////////////////


LRESULT CALLBACK LowLevelMouseProc(int nCode, 
   WPARAM wParam, LPARAM lParam) {

   if (nCode == HC_ACTION) {
      if (wParam == WM_MOUSEMOVE) {
         g_PrfData.GetCtr32(HWINPUT_MOUSEMOVES)++;
         g_PrfData.GetCtr32(HWINPUT_MOUSEMOVESPERSEC)++;
      }

      BOOL fDown = ((wParam == WM_LBUTTONDOWN) || 
         (wParam == WM_MBUTTONDOWN) || (wParam == WM_RBUTTONDOWN));
      if (fDown) {

         MOUSECLCKINST mci;
         if ((wParam == WM_LBUTTONDOWN) || (wParam == WM_LBUTTONUP))
            mci = mciLeft;
         if ((wParam == WM_MBUTTONDOWN) || (wParam == WM_MBUTTONUP))
            mci = mciMiddle;
         if ((wParam == WM_RBUTTONDOWN) || (wParam == WM_RBUTTONUP))
            mci = mciRight;

         g_PrfData.GetCtr32(MOUSECLCKS_CLICKS,       
            g_MouseClckInstToPrfInstId[mciTotal])++;
         g_PrfData.GetCtr32(MOUSECLCKS_CLICKSPERSEC, 
            g_MouseClckInstToPrfInstId[mciTotal])++;
         g_PrfData.GetCtr32(MOUSECLCKS_CLICKS,       
            g_MouseClckInstToPrfInstId[mci])++;
         g_PrfData.GetCtr32(MOUSECLCKS_CLICKSPERSEC, 
            g_MouseClckInstToPrfInstId[mci])++;
      }
   }
   return(CallNextHookEx(NULL, nCode, wParam, lParam));
}


/////////////////////////////////////////////////////////////////////


int WINAPI WinMain (HINSTANCE hinstExe, 
   HINSTANCE hinstExePrev, LPSTR pszCmdLine, int nCmdShow) {

   BOOL fRunApp = TRUE;

   if (lstrcmpiA(pszCmdLine, "-Install") == 0) {
      WCHAR szPath[_MAX_PATH];
      GetModuleFileNameW(hinstExe, szPath, chDIMOF(szPath));
      wcscpy(wcsrchr(szPath, L'\\') + 1, L"HWInputMonPrfInfo.dll");
      g_PrfData.Install(szPath);
      fRunApp = FALSE;
   }

   if (lstrcmpiA(pszCmdLine, "-Uninstall") == 0) {
      g_PrfData.Uninstall();
      fRunApp = FALSE;
   }

   if (fRunApp) {
      g_PrfData.Activate();

      // Add the four Mouse Click Object Instances
      g_MouseClckInstToPrfInstId[mciTotal]  = 
         g_PrfData.AddInstance(PRFOBJ_MOUSECLCKS, L"_Total");
      g_MouseClckInstToPrfInstId[mciLeft]   = 
         g_PrfData.AddInstance(PRFOBJ_MOUSECLCKS, L"Left");
      g_MouseClckInstToPrfInstId[mciMiddle] = 
         g_PrfData.AddInstance(PRFOBJ_MOUSECLCKS, L"Middle");
      g_MouseClckInstToPrfInstId[mciRight]  = 
         g_PrfData.AddInstance(PRFOBJ_MOUSECLCKS, L"Right");

      // Install the low-level keyboard & mouse hooks      }
      HHOOK hhkLowLevelKybd  = SetWindowsHookEx(WH_KEYBOARD_LL, 
         LowLevelKeyboardProc, hinstExe, 0);
      HHOOK hhkLowLevelMouse = SetWindowsHookEx(WH_MOUSE_LL, 
         LowLevelMouseProc, hinstExe, 0);

      // Keep this app running until we're told to stop
      int x = IDRETRY;
      while (x == IDRETRY) {

         if (x == IDRETRY) {
            // Reset all of the counters to zero
            g_PrfData.LockCtrs();
            g_PrfData.GetCtr32(HWINPUT_KEYS) = 0;
            g_PrfData.GetCtr32(HWINPUT_KEYSPERSEC) = 0;
            g_PrfData.GetCtr32(HWINPUT_MOUSEMOVES) = 0;
            g_PrfData.GetCtr32(HWINPUT_MOUSEMOVESPERSEC) = 0;

            MOUSECLCKINST mci = mciFirst; 
            while (mci <= mciLast) {
               g_PrfData.GetCtr32(MOUSECLCKS_CLICKS,       
                  g_MouseClckInstToPrfInstId[mci]) = 0;
               g_PrfData.GetCtr32(MOUSECLCKS_CLICKSPERSEC, 
                  g_MouseClckInstToPrfInstId[mci]) = 0;

               mci = (MOUSECLCKINST) ((int) mci + 1);
            }
            g_PrfData.UnlockCtrs();
         }

         x = ::MessageBox(NULL, 
            __TEXT("Click \"Retry\"  to reset the counters.\n")
            __TEXT("Click \"Cancel\" to terminate the application."),
            __TEXT("Hardware Input Performance Monitor "),
            MB_RETRYCANCEL);
      }

      UnhookWindowsHookEx(hhkLowLevelKybd);
      UnhookWindowsHookEx(hhkLowLevelMouse);

      // Remove the four Mouse Click Object Instances
      g_PrfData.RemoveInstance(PRFOBJ_MOUSECLCKS, 
         g_MouseClckInstToPrfInstId[mciTotal]);
      g_PrfData.RemoveInstance(PRFOBJ_MOUSECLCKS, 
         g_MouseClckInstToPrfInstId[mciLeft]);
      g_PrfData.RemoveInstance(PRFOBJ_MOUSECLCKS, 
         g_MouseClckInstToPrfInstId[mciMiddle]);
      g_PrfData.RemoveInstance(PRFOBJ_MOUSECLCKS, 
         g_MouseClckInstToPrfInstId[mciRight]);
   }

   return(0);
}


//////////////////////////// End Of File ////////////////////////////
