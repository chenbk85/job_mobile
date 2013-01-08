//
//  MultiUser.h
//  DualGoServer
//
//  Created by jin young park on 11. 11. 23..
//  Copyright (c) 2011년 집. All rights reserved.
//

#ifndef DualGoServer_MultiUser_h
#define DualGoServer_MultiUser_h

#include "MultiGoDefine.h"
#include "ug.pb.h"
#include "game.pb.h"
#include "gameLogic.pb.h"
#include "boost/asio.hpp"

//#define DEF_USE_ASIO_ASYNC_READ


class CMultiGoManager;
class CLogicMultiCommand;

//typedef boost::shared_ptr<CLogicMultiCommand> logicCommand_ptr;

using boost::asio::ip::tcp;

struct jGameServerMsg
{
	PPacketHeader header;
	char pBody[nGS::BUFFER_SIZE];
};
typedef std::deque<jGameServerMsg> jGameServerMsg_queue;

class CMultiUser
	: public boost::enable_shared_from_this<CMultiUser>
	,private boost::noncopyable
{
public:
    CMultiUser(boost::asio::io_service& io_service, CMultiGoManager* manager);
	~CMultiUser();
    
public:
    tcp::socket& socket();
    
    void read_socket();
    
private:
    CMultiGoManager* mulManager;
    tcp::socket socket_;
	PPacketHeader m_PPacketHeader_Read;
    char m_pDataBuff_Read[nGS::BUFFER_SIZE];
	int m_iReadSize;

#ifndef DEF_USE_ASIO_ASYNC_READ
	// async_read_some용. DEF_USE_ASIO_ASYNC_READ가 define안되었을때만 필요.
	char m_pDataBuff_Readed[nGS::BUFFER_SIZE*8];
	int m_iReadedSize;
	void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
	void _async_read_some();
#endif

	jGameServerMsg m_writeBuff;
	jGameServerMsg_queue m_write_msgs;
    
    int offset;
        
    //유저의 상태
    USER_STATE userState;
    //룸의 상태
    ROOM_STATE roomState;

    CLogicMultiCommand* logicCommand;
    
    GAnsGameLeave_KICK_TYPE kickType;
public:
    GReqGameEnter JoinInfo;          //나의 게임 정보이다.
    GReqGameEnter YouJoinInfo;       //상대방의 게임 정보이다.
    
public:
    USER_STATE getUserState();  //유저의 상태값을 가져온다.
    ROOM_STATE getRoomState();  //룸의 상태값을 가져온다.
    int getRoomID();            //현재 유저의 룸의 아이디를 가져온다
    int getGameID();            //유저의 usn을 가져온다.
    int getGameIndex();         //유저의 게임 인덱스를 가져온다.
    
    CLogicMultiCommand* getLogicCommand();             //로직 커맨드 포인터를 가져옴
    
    int getMatchUserGameID();            //매칭된 유저의 게임 아이디
    
    void setUserState(USER_STATE nState);           //유저의 상태값을 가져온다.
    void setRoomState(ROOM_STATE nState);           //룸의 상태값을 가져온다.
    void setUserIndex(int ui);                      //유저 인덱스 셋팅
    void setMatchUser(GReqGameEnter& matchUser);     //매치 유저
    void setMatchUserGameId(int gameId);            //상대방의 게임 usn을 셋팅한다.
    void setLogicCommand(CLogicMultiCommand* pLogicCommand);   //로직 커맨드를 셋팅한다.
    void setLogicUser(); 
    
    
    //게임을 떠날때 정리한다.
    void leaveSet(int nGameID);
    //게임방을 파괴한다.
    void destoryRoom();

    //로직 커맨드중 상대방을 셋팅한다.
        
    void changeIndex(int index);                                  //인덱스를 변경한다.
    void setGameIndex(int iUI);             //인덱스 설정한다.
    
    void sendPacket(GAnsProtocol& matgo);              //패킷을 보낸다.
    void sendAllPacket(GAnsProtocol& matgo);           //패킷을 모두 보낸다.
    void makeLeave(GAnsProtocol& matgo, int gameID, GAnsGameLeave_KICK_TYPE nType);
    
    void getGameUserInfo(GameUserInfo& info, bool bMe); //true 자기 , false 남
    void setKickType(GAnsGameLeave_KICK_TYPE nType);
    GAnsGameLeave_KICK_TYPE getKickType();

private:

	void handle_read_header(const boost::system::error_code& error);
    void handle_read_body(const boost::system::error_code& error);     //패킷을 받는다.
    void handle_write(const boost::system::error_code& error);                              //패킷을 보내고 난 다음에 불리는 콜백.
	void _send();
	void _async_read();
    
    void sendYouPacket(GAnsProtocol& matgo);                //패킷을 다른 사람에게 보낸다.
    void sendYouPacket(GAnsProtocol& matgo, int GameID);   //패킷을 다른 사람에게 보낸다.
    
    void sendJoinRoom(GAnsProtocol& matgo);            //조인룸을 보낸다.
    
    void makePacket(GAnsProtocol_Type nType, GAnsProtocol& matgo);     //게임 패킷을 만든다.
    void makeGamePacket(GLAnsGameProtocol_Type nType, GAnsProtocol& matgo);

    void makeGameJoinRoom(GAnsProtocol& matgo);    //GameJoinRoom 패킷을 만든다.
    void makeReqGameJoinRoom(GAnsProtocol& matgo); //게임 조인을 보내라고 요구한다.
    void makeGameStartReady(GAnsProtocol& matgo);  //게임 스타트 버튼을 준비 시킨다.
    void makeEnter(GAnsProtocol& matgo);
    void makeExitReservation(GAnsProtocol& matgo, int gameIndex, bool bExit);
    
    void makePlug(GAnsProtocol& matgo, int gameID);
    void makePlugErr(GAnsProtocol& matgo, std::string str);

    
    void parseEnterGame(GReqGameEnter* packet);
    void parseLeave(GReqGameLeave* packet);
    void parsePlug(GReqPlug* packet);
    void parseDetach(GReqDetach* packet);
    void parseDB(AnsDB* db);
    
    void packetParse(GLReqGameProtocol* packet);           //패킷 파서
    void parseJoinRoom(GReqGameEnter* joinRoom);     //게임룸에 입장할때
    void parseGameReady(GLReqGameReady* gameReady);      //게임 준비가 되었다.
    void parseGameReqInitGame(GLReqGameInitGame* gameInit);    //최초 게임을 시작한다.
    void parseGameReqSelectSunCard(GLReqGameSelectSunCard* sunCard);  //선을 선택한 인덱스
    void parseGameReqGameStart(GLReqGameStart* start);            //게임을 시작한다.
    void parseGameReset(GLReqGameReset* reset);
    void parseGameResultOk(GLReqResultOk* resultOk);
    void parseGameSelectCard(GLReqGameSelectCard* slect);
    void parseGameAskGostopAns(GLReqGameAskGoStopAns* ans);
    void parseGameAskShakeAns(GLReqGameAskShakeAns* ans);
    void parseGameChoiceCard(GLReqGameChoiceCardAns* card);
    void parseGameMoveTen(GLReqGameMoveTen* move);
    void parseGameChongtong(GLReqGameChongTong* chong);
	void parseGameAutoPlay(GLReqGameAutoPlay* play);	
    void parseExitReservation(GLReqExitReservation* exit);
    void parseGameRelayInfo(GLReqRelayInfo* relay);
    void parseGameEmoti(GLReqGameEmoti* emoti);
    void parseGameInitTan(GLReqGameInitGameTan* tan);
	void parse_REQ_GAME_TEST_PACKET(G_REQ_GAME_TEST_PACKET* p);    
    
    void setTimer(TIMER_TYPE nType);        //타이머 셋팅
    
    unsigned long long getPointMoney(int cateID);
};


#endif
