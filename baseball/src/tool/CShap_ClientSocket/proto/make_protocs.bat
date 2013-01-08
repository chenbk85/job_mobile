SET PROTO_FILE_LIST=PT_BaseballServer.proto PT_UserGateServer.proto gameLogic.proto  excel_baseball_table_db.proto ug.proto db.proto
SET CPP_OUT_DIR=..\..\..\..\..\common\Server\GameServer\BaseballServer\BaseballTestClient\proto
SET PROTOC_EXE=..\..\..\..\..\lib\lib_protobuf\vsprojects\bin\Release\protoc.exe

SET PROTOC_GEN_DIR=..\..\..\..\..\lib\lib-protobuf_net\protobuf-net_r282\NET20
set CSHAP_OUT_DIR=%cd%
set LINUX_SVN_ROOT=t:\svn

pushd %LINUX_SVN_ROOT%

copy /y baseball\game\*.proto %CSHAP_OUT_DIR%
copy /y MSG\src\protocol\* %CSHAP_OUT_DIR%


popd

@rem %PROTOC_GEN_DIR%\protogen.exe -i:excel_baseball_table_db.proto -o:proto.excel_baseball_table_db.cs
@rem %PROTOC_GEN_DIR%\protogen.exe -i:db.proto -o:proto.db.cs
@rem %PROTOC_GEN_DIR%\protogen.exe -i:ug.proto -o:proto.ug.cs -p:import=db
@rem %PROTOC_GEN_DIR%\protogen.exe -i:gameLogic.proto -o:proto.gameLogic.cs -p:import=db;ug;excel_baseball_table_db
@rem %PROTOC_GEN_DIR%\protogen.exe -i:PT_BaseballServer.proto -o:proto.PT_BaseballServer.cs -p:import=db;ug;gameLogic;excel_baseball_table_db
@rem %PROTOC_GEN_DIR%\protogen.exe -i:PT_UserGateServer.proto -o:proto.PT_UserGateServer.cs -p:import=db;ug;gameLogic;excel_baseball_table_db

copy /y %LINUX_SVN_ROOT%\baseball\game\*.proto.h %CPP_OUT_DIR%
%PROTOC_EXE% --cpp_out=%CPP_OUT_DIR% %PROTO_FILE_LIST%

pause
