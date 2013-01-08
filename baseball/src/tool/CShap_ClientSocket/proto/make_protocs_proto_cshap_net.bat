SET CPP_OUT_DIR=..\..\..\..\..\common\Server\GameServer\BaseballServer\BaseballTestClient\proto
SET PROTOC_EXE=..\..\..\..\..\lib\lib_protobuf\vsprojects\bin\Release\protoc.exe
SET PROTOC_GEN_DIR=..\..\..\..\..\lib\lib_protobuf_csharp\bin\Release\v2.0
SET PROTO_BIN=..\..\..\..\..\lib\lib_protobuf\vsprojects\bin\Release
SET PROTO_FILE_LIST=PT_BaseballServer.proto PT_UserGateServer.proto gameLogic.proto  excel_baseball_table_db.proto ug.proto db.proto
set CSHAP_OUT_DIR=%cd%
set LINUX_SVN_ROOT=t:\svn



DEL /Y PT_BaseballServer.proto
del /f /q PT_UserGateServer.proto
del /f /q PT_BaseballServer.proto
del /f /q gameLogic.proto 
del /f /q excel_baseball_table.proto
del /f /q ug.proto 
del /f /q db.proto

pushd %LINUX_SVN_ROOT%


copy /y baseball\game\*.proto %CSHAP_OUT_DIR%
copy /y MSG\src\protocol\* %CSHAP_OUT_DIR%
copy /y baseball\game\*.proto %CSHAP_OUT_DIR%

popd



copy /y %LINUX_SVN_ROOT%\baseball\game\*.proto.h %CPP_OUT_DIR%
%PROTOC_GEN_DIR%\protogen.exe %PROTO_FILE_LIST% --protoc_dir=%PROTO_BIN% -output_directory=%CSHAP_OUT_DIR%

%PROTOC_EXE% --cpp_out=%CPP_OUT_DIR% %PROTO_FILE_LIST%


pause