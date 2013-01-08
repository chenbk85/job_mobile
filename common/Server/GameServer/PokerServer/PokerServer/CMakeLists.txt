cmake_minimum_required(VERSION 2.8)

PROJECT(PokerServer) 
include_directories (${PokerServer_SOURCE_DIR}/../../../common)
include_directories (${PokerServer_SOURCE_DIR}/../../MOB_lib)
include_directories (${PokerServer_SOURCE_DIR}/protobuf)
include_directories (./)

link_directories (${PokerServer_SOURCE_DIR}/../../MOB_lib)



ADD_DEFINITIONS(
#  -Wall
	-g
#  -Wno-deprecated
  -DDEF_LINUX
)


add_executable ( PokerServer.x 

	./protobuf/game.pb.cc 
	./protobuf/gameLogic.pb.cc 
	./protobuf/ug.pb.cc 
	./protobuf/db.pb.cc
		
	./stdafx.cpp
	./main.cpp
	./MOB_template_code.cpp
	./recv_GLReqGameProtocol.cpp
	
	./PK_Plugin_Connection.cpp
	./PK_Plugin_NetIOModel.cpp
	./PK_Room.cpp
	
	./PB_Server/Data/GameData.cpp
	./PB_Server/Data/GameInfo.cpp
	
	./PB_Server/Manager/GameMgr_Poker.cpp
	./PB_Server/Manager/GameMgr_Poker_Card.cpp
	./PB_Server/Manager/GameMgr_Poker_Game.cpp
	./PB_Server/Manager/GameMgr_Poker_Promotion.cpp
	./PB_Server/Manager/GameMgr_Poker_Query.cpp
	./PB_Server/Manager/GameMgr_Poker_Recv.cpp
	./PB_Server/Manager/GameMgr_Poker_Rule.cpp
	./PB_Server/Manager/GameMgr_Poker_Send.cpp
	./PB_Server/Manager/GameRule_Poker.cpp
	./PB_Server/Manager/iRoomContext.cpp
	./PB_Server/Manager/Object.cpp
	./PB_Server/Manager/ObjectData.cpp
	./PB_Server/Manager/ObjectMgr.cpp
	./PB_Server/Manager/ObjectMgr_Recv.cpp
	./PB_Server/Manager/ObjectMgr_Send.cpp
	./PB_Server/Manager/Standard/ObjectItem.cpp
	./PB_Server/Manager/Standard/ObjectRefill.cpp
	./PB_Server/Manager/Standard/ObjectWaiting.cpp
	
	./PB_Server/Library/NeoRand.cpp
	./PB_Server/util/FileDebug.cpp
	./PB_Server/util/FileLog.cpp
	./PB_Server/util/GRCUtil.cpp
	./PB_Server/util/Log.cpp
	./PB_Server/util/PublicFunc.cpp
	./PB_Server/util/StaticFunc.cpp
	./PB_Server/util/util.cpp

	
)
target_link_libraries (PokerServer.x 
	MOB_lib
	boost_thread
	boost_system
	boost_program_options
	protobuf
)
