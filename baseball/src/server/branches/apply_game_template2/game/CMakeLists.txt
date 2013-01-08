cmake_minimum_required(VERSION 2.8)

project(baseball_game)

SET(MSG_ROOT ../../MSG)
set(PROTO_SRC gameLogic.proto PT_UserGateServer.proto PT_BaseballServer.proto excel_baseball_table_db.proto )

find_program(PROTOC protoc)
set(PROTOC_C_OUT_FLAG --cpp_out)

#protobuf output
set(PROTO_GEN_DIR ${CMAKE_CURRENT_BINARY_DIR})
foreach(PROTO_FILE ${PROTO_SRC})
  #get the name of the file without extension
  get_filename_component(PROTO_NAME ${PROTO_FILE} NAME_WE)
  #add the generated files
  set(PROTO_GEN ${PROTO_GEN}
    ${PROTO_GEN_DIR}/${PROTO_NAME}.pb.h
    ${PROTO_GEN_DIR}/${PROTO_NAME}.pb.cc)

  set(PROTO_HDR ${PROTO_HDR}
    ${PROTO_GEN_DIR}/${PROTO_NAME}.pb.h)

endforeach(PROTO_FILE ${PROTO_SRC})

add_custom_command(
  OUTPUT ${PROTO_GEN}
  COMMAND ${PROTOC} ${PROTO_SRC} 
            ${PROTOC_C_OUT_FLAG} ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS ${PROTOC} ${PROTO_SRC}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

INCLUDE_DIRECTORIES(
  ./
  ${CMAKE_CURRENT_SOURCE_DIR}/../MOB_lib
  ${CMAKE_CURRENT_SOURCE_DIR}/../MOB_lib/common
  ${MSG_ROOT}/include
)

link_directories (${CMAKE_CURRENT_SOURCE_DIR}/../MOB_lib)


ADD_DEFINITIONS(
  -Wall
  -g
	-DDEF_LINUX

	# excel code support
	-DjNOT_USE_nStream_net_string_SQ
	-DjNOT_USE_SQ_BIND_CODE
	-DjEXCEL_SERVER_SIDE_CODE
	-DnExcelUtil=nMech

)


SET(LOGIC ./logic)


ADD_EXECUTABLE(baseball_game
  main.cpp
  #user.h
  #user.cpp
  #room.h
  #room.cpp
  baseball_room.cpp
  baseball_user.cpp
  version.cpp
  recv_Client_BaseballServer.cpp
  recv_UserGateServer_BaseballServer.cpp
	

  ${PROTO_GEN}
)


FIND_LIBRARY(MSG_BASEKIT_LIB NAMES basekit PATHS ${MSG_ROOT}/lib)
FIND_LIBRARY(MSG_GAME_LIB NAMES game PATHS ${MSG_ROOT}/lib)
FIND_LIBRARY(MSG_GAME2_LIB NAMES game2 PATHS ${MSG_ROOT}/lib)
FIND_LIBRARY(MSG_PROTOCOL_LIB NAMES protocol PATHS ${MSG_ROOT}/lib)


LINK_DIRECTORIES(
  /usr/lib 
  /usr/local/lib
) 


TARGET_LINK_LIBRARIES(baseball_game
	#${MSG_GAME_LIB}
	${MSG_GAME2_LIB}
	${MSG_PROTOCOL_LIB}
	${MSG_BASEKIT_LIB} 
	MOB_lib
	protobuf
	boost_system
	boost_program_options
	boost_date_time
	boost_thread
	boost_filesystem
	boost_unit_test_framework
	boost_test_exec_monitor
	yaml-cpp
)


INSTALL(TARGETS baseball_game DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../bin)

#ADD_SUBDIRECTORY(unittest)
#ADD_SUBDIRECTORY(tests)
