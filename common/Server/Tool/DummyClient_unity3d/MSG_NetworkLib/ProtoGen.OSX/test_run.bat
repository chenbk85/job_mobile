
protoc --descriptor_set_out=rps_game.proto.temp --proto_path=. --error_format=gcc rps_game.proto
protogen.exe -i:rps_game.proto -o:rps_game.cs -ns:MSG -p:lightFramework 
