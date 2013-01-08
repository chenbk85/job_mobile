#!/bin/bash

#export MONO_PREFIX=/Applications/Unity/Unity.app/Contents/Frameworks/Mono
#export MONO_CFG_DIR=$MONO_PREFIX/etc
#export MONO_PATH=$MONO_PREFIX/lib/mono/2.0
#/Applications/Unityy/Unity.app/Contents/Frameworks/Mono/bin/mono protogen.exe -i:rps_game.proto -o:rps_game.cs -ns:MSG -p:lightFramework
# mono protogen.exe -i:rps_game.proto -o:rps_game.cs -ns:MSG -p:lightFramework

#rm *.temp #임시파일 지우기.

# 1단계 : 기존에 출력된 c#파일지우기.
rm *.cs 
# 2단계 : 먼저 protoc를 이용해 임시 매타파일 생성.
protoc --descriptor_set_out=rps_game.proto.temp --proto_path=. --error_format=gcc rps_game.proto
# 3단계 : 임시 매타파일을 이용해 c#코드 생성.
mono protogen.exe -i:rps_game.proto -o:rps_game.cs -ns:MSG -p:lightFramework
