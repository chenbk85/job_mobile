set CLIENT_DIR=..\..\..\..\..\baseball\src\tool\CShap_ClientSocket\proto

mkdir code
..\..\bin\URelease\PacketGenerator.exe usd "%cd%\code" "%cd%"

copy /y .\code\*.proto t:\svn\baseball\game\
copy /y .\code\*.proto.h t:\svn\baseball\game\

copy /y .\code\*.proto.help.cs ..\..\..\..\..\baseball\src\tool\BaseballClient_net_common\UML
copy /y .\code\*.proto_contract.cs ..\..\..\..\..\baseball\src\tool\BaseballClient_proto\UML


set UNITY3D_DUMMY_DIR=..\..\..\..\..\common\Server\Tool\DummyClient_unity3d\lib_mech\Assets\DummyClient_baseball\proto
copy /y t:\svn\MSG\src\protocol\db.proto  %UNITY3D_DUMMY_DIR%
copy /y t:\svn\MSG\src\protocol\ug.proto  %UNITY3D_DUMMY_DIR%
copy /y t:\svn\baseball\game\gameLogic.proto  %UNITY3D_DUMMY_DIR%
copy /y .\code\PT_*.proto  %UNITY3D_DUMMY_DIR%


pushd %UNITY3D_DUMMY_DIR%
make_proto_cshap_code.bat
popd

pushd %CLIENT_DIR%
make_protocs.bat
popd

pause