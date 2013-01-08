/******************************************************************************
Module name: HWInputPrfDataMap.h
Notices: Written 1998 by Jeffrey Richter
Description: Definition of performance objects and counters
******************************************************************************/


#include "PrfData.h"


///////////////////////////////////////////////////////////////////////////////


PRFDATA_DEFINE_OBJECT(PRFOBJ_HWINPUT,            100);
PRFDATA_DEFINE_COUNTER(HWINPUT_KEYS,             101);
PRFDATA_DEFINE_COUNTER(HWINPUT_KEYSPERSEC,       102);
PRFDATA_DEFINE_COUNTER(HWINPUT_MOUSEMOVES,       103);
PRFDATA_DEFINE_COUNTER(HWINPUT_MOUSEMOVESPERSEC, 104);

PRFDATA_DEFINE_OBJECT(PRFOBJ_MOUSECLCKS,         200);
PRFDATA_DEFINE_COUNTER(MOUSECLCKS_CLICKS,        201);
PRFDATA_DEFINE_COUNTER(MOUSECLCKS_CLICKSPERSEC,  202);


///////////////////////////////// End Of File /////////////////////////////////
