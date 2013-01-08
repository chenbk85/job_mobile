//
//  MultiGoManager.h
//  DualGoServer
//
//  Created by jin young park on 11. 11. 23..
//  Copyright (c) 2011년 집. All rights reserved.
//

#ifndef DualGoServer_MultiGoManager_h
#define DualGoServer_MultiGoManager_h

#include "DualGoInclude.h"

#include "game.pb.h"
#include "ug.pb.h"
#include "gameLogic.pb.h"


typedef boost::shared_ptr<CMultiUser> user_ptr;
typedef std::list<user_ptr> user_list;
//typedef boost::shared_ptr<CLogicMultiCommand> logicCommand_ptr;
//typedef std::list<logicCommand_ptr> logic_list;

using boost::asio::ip::tcp;

class CMultiGoManager
{
public:
    CMultiGoManager(boost::asio::io_service& io_service, short port);
    ~CMultiGoManager();
        
public:
    void start_accept();
    void handle_accept(user_ptr user, const boost::system::error_code& error);

public:
    void setMatchRoom(int gameID, int roomID); //방을 매치하고 방에 필요한거 매칭한다.
    int getUserIndex(int gameID);
    user_ptr getUser(int gameID);   //게임 usn으로 유저 포인터를 얻어온다.
    bool checkUser(int gameID);
    
    void sendAllMessage(GLAnsGameProtocol_Type nType);             //메시지를 모두 보낸다.
    void sendMessage(GLAnsGameProtocol_Type nType, int nGameID);   //메시를 하나만 보낸다.
    
    void leave(int nGameID); //리스트에서 떠나 보낸다.
    
    boost::asio::io_service& io_service_;

private:
    tcp::acceptor acceptor_;
    
    user_list gameUserList;
//    logic_list roomList;
    
private:
    void setUserIndex(user_ptr user);       //인덱스를 가져온다.
};

#endif
