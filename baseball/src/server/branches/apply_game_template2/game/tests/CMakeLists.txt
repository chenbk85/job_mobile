cmake_minimum_required(VERSION 2.8)

SET(MSG_ROOT ../../../MSG)


INCLUDE_DIRECTORIES(
  ./
  ../
  ${MSG_ROOT}/include
)

ADD_DEFINITIONS(
  -Wall
  -g
)


ADD_EXECUTABLE(test
  test.cpp
  gateway.cpp
  socket.cpp
  
  play1.cpp
  play2.cpp
  play3.cpp
  play4.cpp
)


LINK_DIRECTORIES(
  /usr/lib 
  /usr/local/lib
) 

FIND_LIBRARY(MSG_BASEKIT_LIB NAMES basekit PATHS ${MSG_ROOT}/lib)
FIND_LIBRARY(MSG_PROTOCOL_LIB NAMES protocol PATHS ${MSG_ROOT}/lib)

TARGET_LINK_LIBRARIES(test
    ${MSG_PROTOCOL_LIB}
    ${MSG_BASEKIT_LIB}

    protobuf
    boost_system
    boost_test_exec_monitor
)


ADD_DEPENDENCIES(test
    baseball_game
)
