cmake_minimum_required(VERSION 2.8)

PROJECT(BaseballServer) 
include_directories (${BaseballServer_SOURCE_DIR}/../../MOB_lib/common)
include_directories (${BaseballServer_SOURCE_DIR}/../../MOB_lib)
include_directories (${BaseballServer_SOURCE_DIR}/protobuf)
include_directories (./)
include_directories (./excel)

link_directories (${BaseballServer_SOURCE_DIR}/../../MOB_lib)



ADD_DEFINITIONS(
	#  -Wall
	-g
	#  -Wno-deprecated
	-DDEF_LINUX
	
	# excel code support
	-DjNOT_USE_nStream_net_string_SQ
	-DjNOT_USE_SQ_BIND_CODE
	-DjEXCEL_SERVER_SIDE_CODE
	-DjEXCEL_LIB_API

)


add_executable (BaseballServer.x 
	main.cpp 
	MOB_template_code.cpp 
	recv_GLReqGameProtocol.cpp 

	BB_Plugin_Connection.cpp 
	BB_Plugin_NetIOModel.cpp 
	BB_Room.cpp 

	./excel/excel_custom_code.cpp
	./excel/excel_all.cpp
	
	./excel/code/excel_enum.cpp
	./excel/code/excel_test.cpp
	./excel/code/excel_test2.cpp
	./excel/code/excel_baseball_table.cpp
	./excel/code/excel_baseball_table_db.cpp
	./excel/code/excel_baseball_table_item.cpp
	./excel/code/excel_baseball_table_etc.cpp
	./excel/code/excel_baseball_string_table.cpp

	./protobuf/game.pb.cc 
	./protobuf/gameLogic.pb.cc 
	./protobuf/ug.pb.cc 
	./protobuf/db.pb.cc
)
target_link_libraries (BaseballServer.x 
	MOB_lib
	boost_thread
	boost_system
	boost_program_options
	boost_filesystem
	boost_unit_test_framework
	protobuf
)
