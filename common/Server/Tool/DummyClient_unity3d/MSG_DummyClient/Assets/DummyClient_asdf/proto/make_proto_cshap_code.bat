@rem http://nwmsvn.nwinet.co.kr/index.php/Unity3d/Protobuf

set PROTOGEN=..\..\..\..\MSG_NetworkLib\ProtoGen.Win


pushd Assets\DummyClient_asdf\proto

%PROTOGEN%\protogen.exe -i:gameLogic.proto -o:asdf_gameLogic.cs -t:csharp.xslt -ns:nProtoGLasdf -p:lightFramework
%PROTOGEN%\protogen.exe -i:PT_UserGateServer.proto -o:asdf_UserGateServer.cs -t:csharp.xslt -ns:nProtoUGasdf -p:lightFramework -p:import=nProtoGLasdf
%PROTOGEN%\protogen.exe -i:PT_GameServer.proto -o:asdf_GameServer.cs -t:csharp.xslt -ns:nProtoGSasdf -p:lightFramework -p:import=nProtoGLasdf

popd

pause