PROJECT(PB_Server_lib) 
include_directories (${PB_Server_lib_SOURCE_DIR}/../../../../common)
include_directories (${PB_Server_lib_SOURCE_DIR}/../../../MOB_lib)
include_directories (./)
ADD_DEFINITIONS(-DDEF_LINUX)

add_library (PB_Server_lib 
	./Library/NeoRand.cpp
	
	./util/FileDebug.cpp
	./util/FileLog.cpp
	./util/GRCUtil.cpp
	./util/Log.cpp
	./util/PublicFunc.cpp
	./util/StaticFunc.cpp
	./util/util.cpp
	
)

