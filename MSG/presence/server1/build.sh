#!/bin/bash -v

pushd ./yaml-cpp > /dev/null
./build.sh
popd > /dev/null

#Now building presence server

g++ -g3 -O0 -o presence -D_GLIBCXX_DEBUG -I/home/sk68/local/include -L/home/sk68/local/lib -I./yaml-cpp/include -L./yaml-cpp -I/home/sk68/boost_1_51_0 -L/home/sk68/boost_1_51_0/stage/lib -lyaml-cpp -lboost_chrono -lboost_filesystem -lboost_system -lboost_thread -lboost_program_options -lprotobuf -lncurses -Wl,-rpath=/home/sk68/local/lib -Wl,-rpath=/home/sk68/boost_1_51_0/stage/lib -Wl,-rpath=./yaml-cpp presence.pb.cc config.cpp game_service.cpp connection_manager.cpp ug_request_handler.cpp server.cpp connection.cpp backend_handler.cpp backend_room.cpp log.cpp main.cpp

#backend_sqlite.cpp

#Now building dummy client

g++ -g -o dummy_client -I/home/sk68/local/include -L/home/sk68/local/lib -I./yaml-cpp/include -L./yaml-cpp -I/home/sk68/boost_1_51_0 -L/home/sk68/boost_1_51_0/stage/lib -lyaml-cpp -lboost_chrono -lboost_filesystem -lboost_system -lboost_thread -lboost_program_options -lprotobuf -Wl,-rpath=/home/sk68/local/lib -Wl,-rpath=/home/sk68/boost_1_51_0/stage/lib -Wl,-rpath=./yaml-cpp presence.pb.cc test_client.cpp

#Now building test client

g++ -g -o test_client -I/home/sk68/local/include -L/home/sk68/local/lib -I./yaml-cpp/include -L./yaml-cpp -I/home/sk68/boost_1_51_0 -L/home/sk68/boost_1_51_0/stage/lib -lyaml-cpp -lboost_chrono -lboost_filesystem -lboost_system -lboost_thread -lboost_program_options -lprotobuf -lncurses -Wl,-rpath=/home/sk68/local/lib -Wl,-rpath=/home/sk68/boost_1_51_0/stage/lib -Wl,-rpath=./yaml-cpp presence.pb.cc config.cpp game_service.cpp connection_manager.cpp ug_request_handler.cpp server.cpp connection.cpp backend_handler.cpp backend_room.cpp log.cpp test_backend_room.cpp
