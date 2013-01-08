#!/bin/bash

#export MONO_PREFIX=/Applications/Unity/Unity.app/Contents/Frameworks/Mono
#export MONO_CFG_DIR=$MONO_PREFIX/etc
#export MONO_PATH=$MONO_PREFIX/lib/mono/2.0
#/Applications/Unityy/Unity.app/Contents/Frameworks/Mono/bin/mono protogen.exe -i:rps_game.proto -o:rps_game.cs -ns:MSG -p:lightFramework
# mono protogen.exe -i:rps_game.proto -o:rps_game.cs -ns:MSG -p:lightFramework

#rm *.temp #�ӽ����� �����.

# 1�ܰ� : ������ ��µ� c#���������.
rm *.cs 
# 2�ܰ� : ���� protoc�� �̿��� �ӽ� ��Ÿ���� ����.
protoc --descriptor_set_out=rps_game.proto.temp --proto_path=. --error_format=gcc rps_game.proto
# 3�ܰ� : �ӽ� ��Ÿ������ �̿��� c#�ڵ� ����.
mono protogen.exe -i:rps_game.proto -o:rps_game.cs -ns:MSG -p:lightFramework
