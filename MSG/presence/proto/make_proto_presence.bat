SET SVN_ROOT=..\..\..

SET PROTO_FILE_LIST=presence.proto
SET CPP_OUT_DIR=%CD%
SET PROTOC_EXE=%SVN_ROOT%\lib\lib_protobuf\vsprojects\bin\Release\protoc.exe

%PROTOC_EXE% --cpp_out=%CPP_OUT_DIR% %PROTO_FILE_LIST%

pause
