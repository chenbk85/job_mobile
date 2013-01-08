; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CNotepadreView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "notepadre.h"
LastPage=0

ClassCount=9
Class1=CNotepadreApp
Class2=CNotepadreDoc
Class3=CNotepadreView
Class4=CMainFrame

ResourceCount=13
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_GOTO
Resource4=IDD_ENCODING_FILE_DLG (English (U.K.))
Class6=CGotoDlg
Resource5=IDD_ABOUTBOX (English (U.S.))
Resource6=IDD_PAGE_SETUP (English (U.S.))
Resource7=IDD_REGEX_SYNTAX
Class7=CFindReplaceDlg
Class8=CEncodingFileDlg
Resource8=IDR_MAINFRAME (English (U.S.))
Resource9=IDD_ENCODING_FILE_DLG
Resource10=IDD_FIND (English (U.S.))
Resource11=IDD_FIND_REPLACE (English (U.S.))
Class9=CRegexSyntaxDlg
Resource12=IDD_GOTO (German (Switzerland))
Resource13=IDD_REGEX_SYNTAX (English (U.K.))

[CLS:CNotepadreApp]
Type=0
HeaderFile=notepadre.h
ImplementationFile=notepadre.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CNotepadreApp

[CLS:CNotepadreDoc]
Type=0
HeaderFile=notepadreDoc.h
ImplementationFile=notepadreDoc.cpp
Filter=N
LastObject=CNotepadreDoc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CNotepadreView]
Type=0
HeaderFile=notepadreView.h
ImplementationFile=notepadreView.cpp
Filter=C
BaseClass=CEditView
VirtualFilter=VWC
LastObject=ID_OPTION_READ_ONLY


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_EDIT_REPLACE




[CLS:CAboutDlg]
Type=0
HeaderFile=notepadre.cpp
ImplementationFile=notepadre.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
CommandCount=17
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command16=ID_HELP_FINDER
Command17=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=16
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_CONTEXT_HELP
Command16=ID_HELP


[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PAGE_SETUP
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_CLEAR
Command15=ID_EDIT_FIND
Command16=ID_EDIT_REPEAT
Command17=ID_EDIT_REPLACE
Command18=ID_EDIT_GOTO
Command19=ID_EDIT_SELECT_ALL
Command20=ID_EDIT_TIMEDATE
Command21=ID_FORMAT_WORD_WRAP
Command22=ID_FORMAT_READ_ONLY
Command23=ID_FORMAT_FONT
Command24=ID_OPTIONS_REGEX_SYNTAX
Command25=ID_OPTIONS_SCROLL_TO_END
Command26=ID_OPTIONS_DROP_FILES
Command27=ID_OPTIONS_FILE_CHANGE_NOTIFY
Command28=ID_OPTIONS_AUTO_RELOAD
Command29=ID_VIEW_TOOLBAR
Command30=ID_VIEW_STATUS_BAR
Command31=ID_HELP_FINDER
Command32=ID_HELP_REGEX
Command33=ID_APP_ABOUT
CommandCount=33

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_HELP_FINDER
CommandCount=9

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_SELECT_ALL
Command2=ID_EDIT_FIND
Command3=ID_EDIT_GOTO
Command4=ID_EDIT_REPLACE
Command5=ID_FILE_NEW
Command6=ID_FILE_OPEN
Command7=ID_FILE_PRINT
Command8=ID_FILE_SAVE
Command9=ID_EDIT_UNDO
Command10=ID_HELP_FINDER
Command11=ID_CONTEXT_HELP
Command12=ID_EDIT_REPEAT
Command13=ID_EDIT_TIMEDATE
Command14=ID_NEXT_PANE
Command15=ID_PREV_PANE
CommandCount=15

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_BUTTON_URL,button,1342242816

[DLG:IDD_GOTO]
Type=1
Class=CGotoDlg
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_LINE,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_COLUMN,edit,1350631552
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816

[CLS:CGotoDlg]
Type=0
HeaderFile=GotoDlg.h
ImplementationFile=GotoDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CGotoDlg
VirtualFilter=dWC

[DLG:IDD_GOTO (German (Switzerland))]
Type=1
Class=CGotoDlg
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_LINE,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_COLUMN,edit,1350631552
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816

[DLG:IDD_FIND (English (U.S.))]
Type=1
Class=CFindReplaceDlg
ControlCount=12
Control1=65535,static,1342308352
Control2=IDC_EDIT_FIND,edit,1350762624
Control3=IDC_CHECK_WHOLE_WORD,button,1342373891
Control4=IDC_CHECK_MATCH_CASE,button,1342242819
Control5=IDC_CHECK_REGEX,button,1342242819
Control6=1072,button,1342308359
Control7=IDC_RADIO_UP,button,1342308361
Control8=IDC_RADIO_DOWN,button,1342177289
Control9=IDC_CHECK_CLOSE_ON_MATCH,button,1342242819
Control10=IDOK,button,1342373889
Control11=IDCANCEL,button,1342242816
Control12=IDC_BUTTON_HELP,button,1342242816

[DLG:IDD_FIND_REPLACE (English (U.S.))]
Type=1
Class=CFindReplaceDlg
ControlCount=13
Control1=65535,static,1342308352
Control2=IDC_EDIT_FIND,edit,1350762624
Control3=65535,static,1342308352
Control4=IDC_EDIT_REPLACE,edit,1350762624
Control5=IDC_CHECK_WHOLE_WORD,button,1342373891
Control6=IDC_CHECK_MATCH_CASE,button,1342242819
Control7=IDC_CHECK_REGEX,button,1342242819
Control8=IDC_CHECK_LIKE_NOTEPAD,button,1342242819
Control9=IDOK,button,1342373889
Control10=IDC_BUTTON_REPLACE,button,1342242816
Control11=IDC_BUTTON_REPLACE_ALL,button,1342242816
Control12=IDCANCEL,button,1342242816
Control13=IDC_BUTTON_HELP,button,1342242816

[CLS:CFindReplaceDlg]
Type=0
HeaderFile=FindReplaceDlg.h
ImplementationFile=FindReplaceDlg.cpp
BaseClass=CDialogBar
Filter=D
LastObject=65535
VirtualFilter=dWC

[CLS:CEncodingFileDlg]
Type=0
HeaderFile=EncodingFileDlg.h
ImplementationFile=EncodingFileDlg.cpp
BaseClass=CFileDialog
Filter=D
LastObject=CEncodingFileDlg
VirtualFilter=dWC

[DLG:IDD_ENCODING_FILE_DLG]
Type=1
Class=CEncodingFileDlg
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_COMBO_ENCODING,combobox,1344340227
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO_FORMAT,combobox,1344339971

[DLG:IDD_PAGE_SETUP (English (U.S.))]
Type=1
Class=?
ControlCount=28
Control1=1073,button,1342308359
Control2=1089,static,1342308352
Control3=1137,combobox,1344471299
Control4=1090,static,1342308352
Control5=1138,combobox,1344471299
Control6=1072,button,1342308359
Control7=1056,button,1342373897
Control8=1057,button,1342177289
Control9=1075,button,1342308359
Control10=1102,static,1342308352
Control11=1155,edit,1350762496
Control12=1103,static,1342308352
Control13=1157,edit,1350762496
Control14=1104,static,1342308352
Control15=1156,edit,1350762496
Control16=1105,static,1342308352
Control17=1158,edit,1350762496
Control18=32,static,1342308352
Control19=IDC_EDIT_HEADER,edit,1350631552
Control20=33,static,1342308352
Control21=IDC_EDIT_FOOTER,edit,1350631552
Control22=1,button,1342373889
Control23=2,button,1342242816
Control24=1026,button,1342242816
Control25=65535,button,1342177287
Control26=1080,static,1342177286
Control27=1081,static,1342177285
Control28=1082,static,1342177285

[DLG:IDD_ENCODING_FILE_DLG (English (U.K.))]
Type=1
Class=CEncodingFileDlg
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_COMBO_ENCODING,combobox,1344340227
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO_FORMAT,combobox,1344339971

[CLS:CRegexSyntaxDlg]
Type=0
HeaderFile=RegexSyntaxDlg.h
ImplementationFile=RegexSyntaxDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CRegexSyntaxDlg
VirtualFilter=dWC

[DLG:IDD_REGEX_SYNTAX]
Type=1
Class=CRegexSyntaxDlg
ControlCount=39
Control1=IDC_STATIC,button,1342177287
Control2=IDC_RADIO_NONE,button,1342308361
Control3=IDC_RADIO_BASIC_POSIX,button,1342177289
Control4=IDC_RADIO_EXTENDED_POSIX,button,1342177289
Control5=IDC_RADIO_PERL_SUBSET,button,1342177289
Control6=IDC_RADIO_EMACS,button,1342177289
Control7=IDC_RADIO_AWK,button,1342177289
Control8=IDC_RADIO_GREP,button,1342177289
Control9=IDC_RADIO_EGREP,button,1342177289
Control10=IDC_STATIC,button,1342308359
Control11=IDC_CHECK_ESCAPE_IN_LISTS,button,1342242819
Control12=IDC_CHECK_CHAR_CLASSES,button,1342242819
Control13=IDC_CHECK_INTERVALS,button,1342242819
Control14=IDC_CHECK_LIMITED_OPS,button,1342242819
Control15=IDC_CHECK_NEWLINE_ALT,button,1342242819
Control16=IDC_CHECK_BK_PLUS_QM,button,1342242819
Control17=IDC_CHECK_BK_BRACES,button,1342242819
Control18=IDC_CHECK_BK_PARENS,button,1342242819
Control19=IDC_CHECK_BK_REFS,button,1342242819
Control20=IDC_CHECK_BK_VBAR,button,1342242819
Control21=IDC_CHECK_LITERAL,button,1342242819
Control22=IDC_CHECK_COLLATE,button,1342242819
Control23=IDC_CHECK_PERLEX,button,1342242819
Control24=IDC_CHECK_NOSUBS,button,1342242819
Control25=IDC_STATIC,button,1342177287
Control26=IDC_CHECK_NOT_DOT_NEWLINE,button,1342242819
Control27=IDC_CHECK_NOT_DOT_NULL,button,1342242819
Control28=IDC_CHECK_ANY,button,1342242819
Control29=IDC_CHECK_NOT_NULL,button,1342242819
Control30=IDC_CHECK_CONTINUOUS,button,1342242819
Control31=IDC_CHECK_EXTRA,button,1342242819
Control32=IDC_CHECK_SINGLE_LINE,button,1342242819
Control33=IDC_STATIC,button,1342177287
Control34=IDC_CHECK_PERL,button,1342242819
Control35=IDC_CHECK_SED,button,1342242819
Control36=IDC_CHECK_ALL,button,1342242819
Control37=IDC_CHECK_FIRST_ONLY,button,1342242819
Control38=IDOK,button,1342242817
Control39=IDCANCEL,button,1342242816

[DLG:IDD_REGEX_SYNTAX (English (U.K.))]
Type=1
Class=?
ControlCount=39
Control1=IDC_STATIC,button,1342177287
Control2=IDC_RADIO_NONE,button,1342308361
Control3=IDC_RADIO_BASIC_POSIX,button,1342177289
Control4=IDC_RADIO_EXTENDED_POSIX,button,1342177289
Control5=IDC_RADIO_PERL_SUBSET,button,1342177289
Control6=IDC_RADIO_EMACS,button,1342177289
Control7=IDC_RADIO_AWK,button,1342177289
Control8=IDC_RADIO_GREP,button,1342177289
Control9=IDC_RADIO_EGREP,button,1342177289
Control10=IDC_STATIC,button,1342308359
Control11=IDC_CHECK_ESCAPE_IN_LISTS,button,1342242819
Control12=IDC_CHECK_CHAR_CLASSES,button,1342242819
Control13=IDC_CHECK_INTERVALS,button,1342242819
Control14=IDC_CHECK_LIMITED_OPS,button,1342242819
Control15=IDC_CHECK_NEWLINE_ALT,button,1342242819
Control16=IDC_CHECK_BK_PLUS_QM,button,1342242819
Control17=IDC_CHECK_BK_BRACES,button,1342242819
Control18=IDC_CHECK_BK_PARENS,button,1342242819
Control19=IDC_CHECK_BK_REFS,button,1342242819
Control20=IDC_CHECK_BK_VBAR,button,1342242819
Control21=IDC_CHECK_LITERAL,button,1342242819
Control22=IDC_CHECK_COLLATE,button,1342242819
Control23=IDC_CHECK_PERLEX,button,1342242819
Control24=IDC_CHECK_NOSUBS,button,1342242819
Control25=IDC_STATIC,button,1342177287
Control26=IDC_CHECK_NOT_DOT_NEWLINE,button,1342242819
Control27=IDC_CHECK_NOT_DOT_NULL,button,1342242819
Control28=IDC_CHECK_ANY,button,1342242819
Control29=IDC_CHECK_NOT_NULL,button,1342242819
Control30=IDC_CHECK_CONTINUOUS,button,1342242819
Control31=IDC_CHECK_EXTRA,button,1342242819
Control32=IDC_CHECK_SINGLE_LINE,button,1342242819
Control33=IDC_STATIC,button,1342177287
Control34=IDC_CHECK_PERL,button,1342242819
Control35=IDC_CHECK_SED,button,1342242819
Control36=IDC_CHECK_ALL,button,1342242819
Control37=IDC_CHECK_FIRST_ONLY,button,1342242819
Control38=IDOK,button,1342242817
Control39=IDCANCEL,button,1342242816

