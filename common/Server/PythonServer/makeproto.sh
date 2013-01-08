#!/bin/bash

cp ../../protobuf/*.proto .

cp ./gameGostop.proto ./gameLogic.proto

protoc --python_out=. db.proto
protoc --python_out=. gameLogic.proto
protoc --python_out=. game.proto
protoc --python_out=. ug.proto
protoc --python_out=. presence.proto
