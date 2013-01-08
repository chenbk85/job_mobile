cmake_minimum_required(VERSION 2.8)

PROJECT(baseball_gateway)


set(PROTO_SRC ../game/gameLogic.proto ../game/PT_UserGateServer.proto ../game/PT_BaseballServer.proto ../game/excel_baseball_table_db.proto )

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
  COMMAND ${PROTOC} ${PROTO_SRC} --proto_path=../game ${PROTOC_C_OUT_FLAG}
  ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS ${PROTOC} ${PROTO_SRC}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)


FIND_LIBRARY(EVENT NAMES event PATHS /usr/local/lib)
FIND_LIBRARY(EVENT NAMES event PATHS /opt/local/lib)
FIND_LIBRARY(SQLRELAY_CLIENT NAMES sqlrclient PATHS /usr/local/firstworks/lib /neowiz/cpool3/lib)
FIND_LIBRARY(SQLITE NAMES sqlite3 PATHS /usr/local/lib)


SET(MSG_ROOT ../../MSG)


INCLUDE_DIRECTORIES(
  ${MSG_ROOT}/include
  /neowiz/cpool3/include
  /usr/include
  /usr/local/include
  /usr/local/firstworks/include
  
  ${CMAKE_CURRENT_SOURCE_DIR}/../MOB_lib
  ${CMAKE_CURRENT_SOURCE_DIR}/../MOB_lib/common
  
)


ADD_DEFINITIONS(
  -Wall
  -g
  -DBOOST_ASIO_DISABLE_EPOLL
  -DBOOST_ASIO_DISABLE_KQUEUE
  -DBOOST_ASIO_DISABLE_IOCP
  -Wno-deprecated
)


ADD_EXECUTABLE(baseball_gateway
  main.cpp
  database.cpp
  database_oracle.cpp  
  version.cpp
  jUser.cpp
  ../game/dump.cpp
  recv_Client_UserGateServer.cpp
  recv_BaseballServer_UserGateServer.cpp
  nDB.cpp
  nREDIS.cpp
  baseball_db.cpp
  baseball_db_sqlite.cpp
  baseball_db_sqlite_crud_impl.cpp
  baseball_db_sqlite_query_impl.cpp
  baseball_db_sqlite_shop_impl.cpp
  logdef.cpp
  ${PROTO_GEN}
)


ADD_DEPENDENCIES(baseball_gateway
  baseball_game
)



FIND_LIBRARY(MSG_BASEKIT_LIB NAMES basekit PATHS ${MSG_ROOT}/lib)
FIND_LIBRARY(MSG_GATEWAY_LIB NAMES gateway PATHS ${MSG_ROOT}/lib)
FIND_LIBRARY(MSG_PROTOCOL_LIB NAMES protocol PATHS ${MSG_ROOT}/lib)
FIND_LIBRARY(MOB_LIB NAMES MOB_lib PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../MOB_lib)


TARGET_LINK_LIBRARIES(baseball_gateway
	${MSG_GATEWAY_LIB}
	${MSG_PROTOCOL_LIB}
	${MSG_BASEKIT_LIB}
	MOB_lib
	protobuf
	boost_system
	boost_date_time
	boost_program_options
	boost_thread
	boost_filesystem
	boost_unit_test_framework
	yaml-cpp
	${SQLRELAY_CLIENT}
	${SQLITE}
    ${EVENT}
)

INSTALL(TARGETS baseball_gateway 
  DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../bin)


ADD_SUBDIRECTORY(tests)
