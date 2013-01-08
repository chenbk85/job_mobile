rem copy ..\..\..\bin\DEV\TEST\Client\Data\csv\*.* ..\..\..\bin\DEV\TEST\Server\Data\csv\*.*  /y
rem copy /y .\csv\*.csv ..\..\..\..\common\Server\Tool\bin\MDebug\csv

copy /y .\csv\*.csv ..\..\..\..\common\Server\Tool\bin\MDebug\csv

set DEST_DIR=..\..\..\..\baseball\src\tool\CShap_ClientSocket\bin\Debug
copy /y .\csv\*.csv %DEST_DIR%


set DEST_DIR=t:\svn\baseball\etc\csv
copy /y .\csv\*.csv %DEST_DIR%

call excel_csv_kijun.bat


set DEST_DIR=..\..\..\..\Common\Server\Tool\DummyClient_unity3d\lib_mech\Assets\DummyClient_baseball\excel\file
copy /y .\csv\file_Sys_Error.csv %DEST_DIR%\file_Sys_Error.csv.txt



pushd ..\..\..\src\tool\CShap_ClientSocket\bin\debug\
ClientSocket.exe
popd

pause