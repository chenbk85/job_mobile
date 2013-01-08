; // ***** sample.mc *****


; // This is the header. mc -U jLog.mc => jLog.h , jLog.rc

; // ***** sample.mc *****

; // This is the header.

MessageIdTypedef=DWORD

SeverityNames=(Success=0x0:STATUS_SEVERITY_SUCCESS
    Informational=0x1:STATUS_SEVERITY_INFORMATIONAL
    Warning=0x2:STATUS_SEVERITY_WARNING
    Error=0x3:STATUS_SEVERITY_ERROR
    )


FacilityNames=(System=0x0:FACILITY_SYSTEM
    Runtime=0x2:FACILITY_RUNTIME
    Stubs=0x3:FACILITY_STUBS
    Io=0x4:FACILITY_IO_ERROR_CODE
)

LanguageNames=(English=0x409:MSG00409)

; // The following are message definitions.

MessageId=0x1
Severity=Error
Facility=Runtime
SymbolicName=EVT_NORMAL
Language=English
jLog : %1
.



MessageId       = +1
SymbolicName    = CATEGORY_TWO
Severity        = Success
Language        = English
Second category event
.

;////////////////////////////////////////
;// Events
;//

MessageId       = +1
SymbolicName    = EVENT_STARTED_BY
Language        = English
The app %1 has been started successfully by user %2
.

MessageId       = +1
SymbolicName    = EVENT_BACKUP
Language        = English
You should backup your data regulary!
.

;////////////////////////////////////////
;// Additional messages
;//

MessageId       = 1000
SymbolicName    = IDS_HELLO
Language        = English
Hello World!
.

MessageId       = +1
SymbolicName    = IDS_GREETING
Language        = English
Hello %1. How do you do?
.
