 // ***** sample.mc *****
 // This is the header. mc -U jLog.mc => jLog.h , jLog.rc
 // ***** sample.mc *****
 // This is the header.
 // The following are message definitions.
//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define FACILITY_SYSTEM                  0x0
#define FACILITY_STUBS                   0x3
#define FACILITY_RUNTIME                 0x2
#define FACILITY_IO_ERROR_CODE           0x4


//
// Define the severity codes
//
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#define STATUS_SEVERITY_ERROR            0x3


//
// MessageId: EVT_NORMAL
//
// MessageText:
//
// jLog : %1
//
#define EVT_NORMAL                       ((DWORD)0xC0020001L)

//
// MessageId: CATEGORY_TWO
//
// MessageText:
//
// Second category event
//
#define CATEGORY_TWO                     ((DWORD)0x00020002L)

////////////////////////////////////////
// Events
//
//
// MessageId: EVENT_STARTED_BY
//
// MessageText:
//
// The app %1 has been started successfully by user %2
//
#define EVENT_STARTED_BY                 ((DWORD)0x00020003L)

//
// MessageId: EVENT_BACKUP
//
// MessageText:
//
// You should backup your data regulary!
//
#define EVENT_BACKUP                     ((DWORD)0x00020004L)

////////////////////////////////////////
// Additional messages
//
//
// MessageId: IDS_HELLO
//
// MessageText:
//
// Hello World!
//
#define IDS_HELLO                        ((DWORD)0x000203E8L)

//
// MessageId: IDS_GREETING
//
// MessageText:
//
// Hello %1. How do you do?
//
#define IDS_GREETING                     ((DWORD)0x000203E9L)

