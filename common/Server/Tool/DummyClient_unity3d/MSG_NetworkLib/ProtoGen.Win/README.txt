File description:

protogen.exe -- compiles .proto files into c# script.  (uses csharp.xslt as template)
	Example usage: protogen -i:RPCMessage.proto -o:RPCMessage.cs -t:csharp.xslt -ns:ProtoBufRemote -p:lightFramework

Source\ProtoBufRemote -- main library for rpc functionality using protobuf generated message (supports both TCP and UDP).
	RPCMessage (message format) is defined in RPCMessage.proto.
	RPCMetaMessage is not implemented yet.
	assembly dependency --> protobuf-net.dll

Source\ProtoBufRemoteClient -- client side helper library
	assembly dependency --> ProtoBufRemote

Source\ProtoBufRemoteServer -- server side helper library
	assembly dependency --> ProtoBufRemote

NOTE: Both ProtoBufRemoteClient and ProtoBufRemoteServer library will be merged in the future.

Source\TestClient -- sample test client using ProtoBufRemoteClient
	assembly dependency --> ProtoBufRemoteClient

Source\TestServer -- sample test client using ProtoBufRemoteServer
	assembly dependency --> ProtoBufRemoteServer

--------------------

Currently set to .NET 2.0 compatibility.
