mkdir GameServer_cpp
thrift-0.9.0.exe -r -out GameServer_cpp --gen cpp BingoGameServer.thrift
mkdir GameServer_csharp
thrift-0.9.0.exe -r -out GameServer_csharp --gen csharp BingoGameServer.thrift

pause
