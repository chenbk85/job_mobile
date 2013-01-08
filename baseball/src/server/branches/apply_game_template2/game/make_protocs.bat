set OUT_DIR=D:\svn\baseball\src\tool\CShap_ClientSocket\proto
SET PROTO_BIN=D:\svn\lib\lib_protobuf\vsprojects\bin\Release

protogen.exe PT_BaseballServer.proto  gameLogic.proto  excel_baseball_table.proto --protoc_dir=%PROTO_BIN% -output_directory=%OUT_DIR%
