/******************************************************************************
Module name: HWInputPrfDataMap.cpp
Notices: Written 1998 by Jeffrey Richter
Description: Performance object and counter map
******************************************************************************/


#include "CmnHdr.h"
#include <Windows.h>
#include "PrfData.h"
#include "HWInputPrfDataMap.h"


///////////////////////////////////////////////////////////////////////////////


PRFDATA_MAP_BEGIN()
   PRFDATA_MAP_OBJ(PRFOBJ_HWINPUT, L"Hardware Input", 
      L"The Hardware Input object type includes those counters "
      L"that apply to keystrokes and mouse moves.", 
      PERF_DETAIL_NOVICE, HWINPUT_KEYS, PERF_NO_INSTANCES, 0)

   PRFDATA_MAP_CTR(HWINPUT_KEYS,  L"Keystrokes",  
      L"The number of down and up keystrokes",  
      PERF_DETAIL_NOVICE, 0, PERF_COUNTER_RAWCOUNT)
   PRFDATA_MAP_CTR(HWINPUT_KEYSPERSEC,  L"Keystrokes/sec",  
      L"The number of down and up keystrokes per second",  
      PERF_DETAIL_NOVICE, 0, PERF_COUNTER_COUNTER)
   PRFDATA_MAP_CTR(HWINPUT_MOUSEMOVES,  L"Mouse moves",  
      L"The number of mouse moves",  
      PERF_DETAIL_NOVICE, 0, PERF_COUNTER_RAWCOUNT)
   PRFDATA_MAP_CTR(HWINPUT_MOUSEMOVESPERSEC,  L"Mouse moves/sec",  
      L"The number of mouse moves per second",  
      PERF_DETAIL_NOVICE, 0, PERF_COUNTER_COUNTER)



   PRFDATA_MAP_OBJ(PRFOBJ_MOUSECLCKS, L"Mouse Clicks", 
      L"The Mouse Clicks object type includes those counters "
      L"that apply to mouse button clicks.", 
      PERF_DETAIL_NOVICE, MOUSECLCKS_CLICKS, 4, 10)

   PRFDATA_MAP_CTR(MOUSECLCKS_CLICKS,  L"Clicks",  
      L"The number of down clicks",  
      PERF_DETAIL_NOVICE, 0, PERF_COUNTER_RAWCOUNT)
   PRFDATA_MAP_CTR(MOUSECLCKS_CLICKSPERSEC,  L"Clicks/sec",  
      L"The number of down clicks per second",  
      PERF_DETAIL_NOVICE, 0, PERF_COUNTER_COUNTER)
PRFDATA_MAP_END("HWInputMon")


///////////////////////////////// End Of File /////////////////////////////////
