cmake_minimum_required(VERSION 2.8)

FIND_LIBRARY(SQLRELAY_CLIENT NAMES sqlrclient PATHS /usr/local/firstworks/lib)

unset(PROTO_SRC)
unset(PROTO_GEN)
unset(PROTO_GEN_DIR)
#set(PROTO_SRC ../../game/excel_baseball_table_db.proto )
set(PROTO_SRC ../../game/gameLogic.proto ../../game/PT_UserGateServer.proto ../../game/PT_BaseballServer.proto ../../game/excel_baseball_table_db.proto )

FIND_PROGRAM(PROTOC protoc)
SET(PROTOC_C_OUT_FLAG --cpp_out)

#protobuf output
SET(PROTO_GEN_DIR ${CMAKE_CURRENT_BINARY_DIR})
FOREACH(PROTO_FILE ${PROTO_SRC})
  #get the name of the file without extension
  GET_FILENAME_COMPONENT(PROTO_NAME ${PROTO_FILE} NAME_WE)
  #add the generated files
  SET(PROTO_GEN ${PROTO_GEN}
    ${PROTO_GEN_DIR}/${PROTO_NAME}.pb.h
    ${PROTO_GEN_DIR}/${PROTO_NAME}.pb.cc)

  SET(PROTO_HDR ${PROTO_HDR}
    ${PROTO_GEN_DIR}/${PROTO_NAME}.pb.h)

ENDFOREACH(PROTO_FILE ${PROTO_SRC})

ADD_CUSTOM_COMMAND(
  OUTPUT ${PROTO_GEN}
  COMMAND ${PROTOC} ${PROTO_SRC} --proto_path=../../game ${PROTOC_C_OUT_FLAG}
  ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS ${PROTOC} ${PROTO_SRC}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

INCLUDE_DIRECTORIES(
  ./
  ../../../include
  ../../MOB_lib/
  ../../MOB_lib/common
  /usr/include
  /usr/local/include
  /usr/local/firstworks/include
)


ADD_DEFINITIONS(
  -Wall
  -g
  -DBOOST_ASIO_DISABLE_EPOLL
  -DBOOST_ASIO_DISABLE_KQUEUE
  -DBOOST_ASIO_DISABLE_IOCP
)



#ADD_LIBRARY(test_client
#  socket.cpp
#  client.cpp
#  server.cpp
#  presence.cpp
#  game.cpp
#)
#
#
#ADD_DEPENDENCIES(test_client
#  basekit
#  protocol
#  baseball_game
#)


FIND_LIBRARY(MSG_BASEKIT_LIB NAMES basekit PATHS ../../../lib)
FIND_LIBRARY(MSG_PROTOCOL_LIB NAMES protocol PATHS ../../../lib)


#ADD_EXECUTABLE(tc1
#  tc1.cpp
#)
#
#ADD_DEPENDENCIES(tc1
#  poker_gateway
#  test_client
#)
#
#TARGET_LINK_LIBRARIES(tc1
# test_client
# ${MSG_PROTOCOL_LIB}
# ${MSG_BASEKIT_LIB}
# 
# protobuf
# boost_system
# boost_thread
#)
#
#
#ADD_EXECUTABLE(tc2
#  tc2.cpp
#  ../../game/dump.cpp
#)
#
#ADD_DEPENDENCIES(tc2
#  poker_gateway
#  test_client
#)
#
#TARGET_LINK_LIBRARIES(tc2
# test_client
# ${MSG_PROTOCOL_LIB}
# ${MSG_BASEKIT_LIB}
#
# protobuf
# boost_system
# boost_thread
#)
#
#ADD_EXECUTABLE(tc5
#  tc5.cpp
#  ../../game/dump.cpp
#)
#
#ADD_DEPENDENCIES(tc5
#  poker_gateway
#  test_client
#)
#
#TARGET_LINK_LIBRARIES(tc5
# test_client
# ${MSG_PROTOCOL_LIB}
# ${MSG_BASEKIT_LIB}
#
# protobuf
# boost_system
# boost_thread
#)
#
#
#
#ADD_EXECUTABLE(tc3
#  tc3.cpp
#  ../../game/dump.cpp
#)
#
#ADD_DEPENDENCIES(tc3
#  poker_gateway
#  test_client
#)
#
#TARGET_LINK_LIBRARIES(tc3
# test_client
# ${MSG_PROTOCOL_LIB}
# ${MSG_BASEKIT_LIB}
#
# protobuf
# boost_system
# boost_thread
# boost_test_exec_monitor
#)
#
#ADD_EXECUTABLE(tc
#  tc.cpp
#  ../../game/dump.cpp
#)
#
#ADD_DEPENDENCIES(tc
#  poker_gateway
#  test_client
#)
#
#TARGET_LINK_LIBRARIES(tc
# test_client
# ${MSG_PROTOCOL_LIB}
# ${MSG_BASEKIT_LIB}
#
# protobuf
# boost_system
# boost_thread
# boost_test_exec_monitor
#)


ADD_EXECUTABLE(db_module_test
	db_module_test.cpp
	db_module_crud_test.cpp
	db_module_shop_test.cpp
	../baseball_db.cpp
	../baseball_db_sqlite.cpp
	../baseball_db_sqlite_crud_impl.cpp
	../baseball_db_sqlite_query_impl.cpp
	../baseball_db_sqlite_shop_impl.cpp
	${PROTO_GEN}
	#../../game/excel_baseball_table_db.pb.cc
)


TARGET_LINK_LIBRARIES(db_module_test
	MOB_lib
	protobuf
	sqlite3
 	boost_system
 	boost_date_time
 	boost_filesystem
	boost_unit_test_framework
	#	${SQLRELAY_CLIENT}
)



