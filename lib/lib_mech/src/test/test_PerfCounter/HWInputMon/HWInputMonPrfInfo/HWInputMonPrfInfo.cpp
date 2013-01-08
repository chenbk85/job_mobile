/********************************************************************
Module name: HWInputMonPrfInfo.cpp
Notices: Written 1998 by Jeffrey Richter
Description: DLL that exposes HWInputMon's Performance Informtion
********************************************************************/


#include "..\CmnHdr.h"
#include <Windows.h>

// NOTE: PRFDATA_COLLECT_SUPPORTED must be defined for this project
#if !defined(PRFDATA_COLLECT_SUPPORTED)
#error PRFDATA_COLLECT_SUPPORTED must be defined for this project
#endif

#include "..\HWInputPrfDataMap.h"


//////////////////////////// End Of File ////////////////////////////
