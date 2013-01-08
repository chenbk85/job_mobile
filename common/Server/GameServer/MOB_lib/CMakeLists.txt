PROJECT(MOB_lib) 
include_directories (./)
include_directories (./common)

include_directories (${MOB_lib_SOURCE_DIR}/common)
ADD_DEFINITIONS(
	-DDEF_LINUX

	# excel code support
	-DjNOT_USE_nStream_net_string_SQ
	-DjNOT_USE_SQ_BIND_CODE
	-DjEXCEL_SERVER_SIDE_CODE
	-DjEXCEL_LIB_API

)
add_library (MOB_lib 
	MOB_Connection.cpp 
	MOB_net.cpp 
	MOB_NetIOModel.cpp 
	stdafx.cpp
	./common/jBase_Log.cpp	
	./common/linux/linux_filesystem.cpp
	./common/linux/nOS_filesystem.cpp
	

)
#add_library (MOB_lib test.cpp)
