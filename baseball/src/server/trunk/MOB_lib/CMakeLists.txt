PROJECT(MOB_lib) 
include_directories (./)
include_directories (./common)
include_directories (./excel)

include_directories (${MOB_lib_SOURCE_DIR}/common)
ADD_DEFINITIONS(
	-DDEF_LINUX

	# excel code support
	-DjNOT_USE_nStream_net_string_SQ
	-DjNOT_USE_SQ_BIND_CODE
	-DjEXCEL_SERVER_SIDE_CODE

)
add_library (MOB_lib 
	stdafx.cpp
	nMOB.cpp
	nBASE_BALL.cpp
	
	./common/jBase_Log.cpp	
	./common/linux/linux_filesystem.cpp
	./common/linux/nOS_filesystem.cpp
	./common/jxVar.cpp
	
	./excel/excel_custom_code.cpp
	./excel/excel_all.cpp
	./excel/code/excel_enum.cpp
	./excel/code/excel_baseball_table.cpp
	./excel/code/excel_baseball_table_game.cpp
	./excel/code/excel_baseball_table_db.cpp
	./excel/code/excel_baseball_table_item.cpp
	./excel/code/excel_baseball_table_shop.cpp
	./excel/code/excel_baseball_table_etc.cpp
	./excel/code/excel_baseball_string_table.cpp
	
	./tinyxml/ticpp.cpp
	./tinyxml/tinyxml.cpp
	./tinyxml/tinystr.cpp
	./tinyxml/tinyxmlerror.cpp
	./tinyxml/tinyxmlparser.cpp
	
	
)
#add_library (MOB_lib test.cpp)
