# Install script for directory: C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "C:/")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/Debug/libyaml-cppmdd.lib")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/Release/libyaml-cppmd.lib")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/MinSizeRel/libyaml-cppmd.lib")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/RelWithDebInfo/libyaml-cppmd.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/yaml-cpp" TYPE FILE FILES
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/aliasmanager.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/anchor.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/conversion.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/dll.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/emitfromevents.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/emitter.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/emittermanip.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/eventhandler.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/exceptions.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/iterator.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/ltnode.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/mark.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/node.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/nodeimpl.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/nodereadimpl.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/nodeutil.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/noncopyable.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/null.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/ostream.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/parser.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/stlemitter.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/stlnode.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/traits.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/yaml.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/contrib/anchordict.h"
    "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/include/yaml-cpp/contrib/graphbuilder.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/test/cmake_install.cmake")
  INCLUDE("C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/util/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "C:/Mobile/MSG/trunk/thirdparty/package/yaml-cpp-0.2.7.tar/yaml-cpp-0.2.7/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
