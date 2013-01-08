cmake_minimum_required(VERSION 2.8)

PROJECT(SampleServer) 
include_directories (${SampleServer_SOURCE_DIR}/../../../common)
include_directories (${SampleServer_SOURCE_DIR}/../../MOB_lib)
include_directories (${SampleServer_SOURCE_DIR}/protobuf)
include_directories (./)

link_directories (${SampleServer_SOURCE_DIR}/../../MOB_lib)



ADD_DEFINITIONS(
#  -Wall
	-g
#  -Wno-deprecated
  -DDEF_LINUX
)


add_executable (SampleServer.x 
	main.cpp 
	MOB_template_code.cpp 
	recv_GLReqGameProtocol.cpp 

	SAMPLE_Plugin_Connection.cpp 
	SAMPLE_Plugin_NetIOModel.cpp 
	SAMPLE_Room.cpp 

	./protobuf/game.pb.cc 
	./protobuf/gameLogic.pb.cc 
	./protobuf/ug.pb.cc 
	./protobuf/db.pb.cc
)
target_link_libraries (SampleServer.x 
	MOB_lib
	boost_thread
	boost_system
	boost_program_options
	protobuf
)
