@rem http://nwmsvn.nwinet.co.kr/index.php/Unity3d/Protobuf

set PROTOGEN=..\..\..\..\MSG_NetworkLib\ProtoGen.Win


pushd Assets\DummyClient_baseball\proto

%PROTOGEN%\protogen.exe -i:excel_baseball_table_db.proto -o:excel_baseball_table_db.cs -t:csharp.xslt -ns:nProtoExcel -p:lightFramework
%PROTOGEN%\protogen.exe -i:gameLogic.proto -o:gameLogic.cs -t:csharp.xslt -ns:nProtoGL -p:lightFramework -p:import=nProtoExcel
%PROTOGEN%\protogen.exe -i:PT_UserGateServer.proto -o:PT_UserGateServer.cs -t:csharp.xslt -ns:nProtoUG -p:lightFramework -p:import=nProtoExcel;nProtoGL
%PROTOGEN%\protogen.exe -i:PT_BaseballServer.proto -o:PT_BaseballServer.cs -t:csharp.xslt -ns:nProtoBS -p:lightFramework -p:import=nProtoExcel;nProtoGL

popd

pause