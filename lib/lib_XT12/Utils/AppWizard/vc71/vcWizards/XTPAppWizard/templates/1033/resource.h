//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by [!output PROJECT_NAME].rc
//
[!if APP_TYPE_MDI]
[!if MINI_SERVER || FULL_SERVER || CONTAINER_SERVER]
#define IDR_[!output SAFE_DOC_TYPE_NAME]TYPE_SRVR_IP        4
#define IDR_[!output SAFE_DOC_TYPE_NAME]TYPE_SRVR_EMB       5
[!endif]
[!if CONTAINER || CONTAINER_SERVER]
#define IDR_[!output SAFE_DOC_TYPE_NAME]TYPE_CNTR_IP        6
[!endif]
[!else]
[!if MINI_SERVER || FULL_SERVER || CONTAINER_SERVER]
#define IDR_SRVR_INPLACE            4
#define IDR_SRVR_EMBEDDED           5
[!endif]
[!if CONTAINER || CONTAINER_SERVER]
#define IDR_CNTR_INPLACE            6
[!endif]
[!endif]
#define IDD_ABOUTBOX                100
[!if FORM_VIEW || OLEDB_RECORD_VIEW || ODBC_RECORD_VIEW]
#define IDD_[!output UPPER_CASE_SAFE_PROJECT_NAME]_FORM         101
[!endif]
[!if CONTAINER || CONTAINER_SERVER || MINI_SERVER || FULL_SERVER || AUTOMATION || ACTIVEX_CONTROLS || OLEDB || ACCESSIBILITY]
#define IDP_OLE_INIT_FAILED         100
[!if MINI_SERVER]
#define IDP_USE_INSERT_OBJECT       101
[!endif]
[!if CONTAINER || CONTAINER_SERVER]
#define IDP_FAILED_TO_CREATE        102
#define ID_CANCEL_EDIT_CNTR         32768
[!endif]
[!if MINI_SERVER || FULL_SERVER || CONTAINER_SERVER]
#define ID_CANCEL_EDIT_SRVR         32769
[!endif]
[!endif]
[!if OLEDB_RECORD_VIEW || ODBC_RECORD_VIEW]
#define IDP_FAILED_OPEN_DATABASE    103
[!endif]
[!if SOCKETS]
#define IDP_SOCKETS_INIT_FAILED     104
[!endif]
[!if PROJECT_STYLE_EXPLORER]
[!if LIST_VIEW]
#define ID_VIEW_ARRANGE             127
[!endif]
[!endif]
#define IDR_MAINFRAME               128
#define IDR_[!output SAFE_DOC_TYPE_NAME]TYPE                129
#define IDR_MANIFEST                CREATEPROCESS_MANIFEST_RESOURCE_ID
[!if DOCK_PANE]
#define IDB_BITMAP_ICONS            130
#define IDR_PANE_OPTIONS            4000
#define IDR_PANE_PROPERTIES         4001
[!endif]


// Next default values for new objects
//
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE    130
#define _APS_NEXT_CONTROL_VALUE     1000
#define _APS_NEXT_SYMED_VALUE       101
#define _APS_NEXT_COMMAND_VALUE     32771
#endif
#endif
