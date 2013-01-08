rem del .\code\*.txt /f
rem del .\code\*.xml /f

copy code\sql\Create_Tbl_*.sql Baseball_Table.sql
rem notepad Baseball_Table.sql

set DEST_DIR=..\..\..\..\common\Server\GameServer\BaseballServer\BaseballServer\excel\code
copy /y .\code\*.h %DEST_DIR%
copy /y .\code\*.cpp %DEST_DIR%

set DEST_DIR=..\..\..\..\common\Server\GameServer\BaseballServer\BaseballTestClient\excel\code\
copy /y .\code\*.h %DEST_DIR%
copy /y .\code\*.cpp %DEST_DIR%


set DEST_DIR=..\..\..\..\baseball\src\tool\BaseballClient_CSV\
copy /y .\code\*.csv.cs %DEST_DIR%
copy /y .\code\table_const_*.cs %DEST_DIR%


set DEST_DIR=..\..\..\..\baseball\src\tool\BaseballClient_proto\
copy /y .\code\*.proto_contract.cs %DEST_DIR%


copy /y .\code\*.proto.excel.help.cs ..\..\..\..\baseball\src\tool\BaseballClient_net_common\


set DEST_DIR=T:\svn\baseball\MOB_lib\excel\code
copy /y .\code\*.h %DEST_DIR%
copy /y .\code\*.cpp %DEST_DIR%


set DEST_DIR=T:\svn\baseball\game
copy /y .\code\*.proto %DEST_DIR%


set DEST_DIR=..\..\..\..\Common\Server\Tool\DummyClient_unity3d\lib_mech\Assets\DummyClient_baseball\proto
copy /y .\code\excel_baseball_table_db.proto %DEST_DIR%


set DEST_DIR=..\..\..\..\Common\Server\Tool\DummyClient_unity3d\lib_mech\Assets\DummyClient_baseball\excel
copy /y .\code\excel_baseball_string_table.csv.cs %DEST_DIR%
copy /y .\code\excel_enum.csv.cs %DEST_DIR%
copy /y .\code\table_const_excel_enum.cs %DEST_DIR%


rem set DEST_DIR=T:\svn\baseball\etc\sqlite_db
rem copy /y .\code\sql\Create_*.sql %DEST_DIR%


pause
