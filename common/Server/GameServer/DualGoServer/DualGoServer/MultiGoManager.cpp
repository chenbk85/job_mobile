//
//  MultiGoManager.cpp
//  DualGoServer
//
//  Created by jin young park on 11. 11. 23..
//  Copyright (c) 2011년 집. All rights reserved.
//

#include "DualGoInclude.h"



CMultiGoManager::CMultiGoManager(boost::asio::io_service& io_service, short port) : io_service_(io_service), acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
{
    start_accept();
}

CMultiGoManager::~CMultiGoManager()
{
    
}

void CMultiGoManager::start_accept()
{
    user_ptr new_user(new CMultiUser(io_service_, this));
    acceptor_.async_accept(new_user->socket(),
                           boost::bind(&CMultiGoManager::handle_accept, this, new_user,
                                       boost::asio::placeholders::error));
#ifdef LOGSET
    std::cerr << "Client Connect Wait............\n";
#endif

}

void CMultiGoManager::handle_accept(user_ptr user, const boost::system::error_code& error)
{
    if (!error)
    {
        //유저가 이미 리스트에 있는지 체크 하고 적절한 조치가 필요하다. 룸을 생성할 수 있어야 한다.
        //여기서 구현해야 한다.
        
        //그리고 스타트 시킨다.
        user->read_socket();
        
        //유저를 리스트에 넣는다
        gameUserList.push_back(user);
        
#ifdef LOGSET
        std::cerr << "User Add count = " << gameUserList.size() << "\n";
#endif
        
    }
    
    //클라이언트를 기다린다.
    start_accept();
}

void CMultiGoManager::setMatchRoom(int gameID, int roomID) //방을 매치한다.
{
#ifdef LOGSET
    std::cerr << "gameid = " << gameID << "  roomid = " << roomID << "\n";
#endif
    
    int nResult = ERROR_VALUE;
    
    bool bMatching = false;
    
    user_ptr pInfo = getUser(gameID);
    
    //리스트를 돌면서 WAIT 상태의 유저를 찾는다.
    std::list<user_ptr>::iterator iter;
    
    for(iter = gameUserList.begin(); iter != gameUserList.end(); iter++)
    {
        user_ptr pUser = (user_ptr) *iter;
        
        if(pUser->getRoomID() == roomID && pInfo->getGameID() != pUser->getGameID())
        {
            if(pInfo != NULL)
            {
                pUser->setUserState(USER_ROOM_RUN);
                pInfo->setUserState(USER_ROOM_RUN);
                
                pUser->setMatchUser(pInfo->JoinInfo);
                pInfo->setMatchUser(pUser->JoinInfo);
                
                //방생성
                CLogicMultiCommand* pLogic = new CLogicMultiCommand(this);               
                
                //인덱스 셋팅
                pUser->setUserIndex(0);
                pInfo->setUserIndex(1);
                
                pUser->setLogicCommand(pLogic);
                pInfo->setLogicCommand(pLogic);
                
                GameUserInfo* pJoin = pUser->JoinInfo.mutable_gameuserinfo();
                GameInfo* pDetGame = pJoin->mutable_gameinfo();
                
                long long llMoney = atoll(pDetGame->money().c_str());
                
                pLogic->setUserMoney(0, (unsigned long long) llMoney);
                
                pJoin = pInfo->JoinInfo.mutable_gameuserinfo();
                pDetGame = pJoin->mutable_gameinfo();
                
                llMoney = atoll(pDetGame->money().c_str());
                
                pLogic->setUserMoney(1, (unsigned long long) llMoney);
                
                bMatching = true;
                
                pUser->setRoomState(ROOM_RUN);
                pInfo->setRoomState(ROOM_RUN);
            }
            
            break;
        }
    }
    
    //매칭이 되지 않았으면...
    if(!bMatching)
    {
        //방을 생성하고 인덱스를 준다.
        pInfo->setUserState(USER_ROOM_WAIT);
        
        pInfo->setUserIndex(0);
        
        pInfo->YouJoinInfo.Clear();
    }
}

int CMultiGoManager::getUserIndex(int gameID)
{
    int nResult = ERROR_VALUE;
    
    user_ptr pUser = (user_ptr)getUser(gameID);
    
    if(pUser != NULL)
    {
        GameUserInfo* pGame = pUser->JoinInfo.mutable_gameuserinfo();
        
        GameInfo* pInfo = pGame->mutable_gameinfo();
        
        nResult = pInfo->gameindex();
    }
    
    return nResult;
}

void CMultiGoManager::setUserIndex(user_ptr user)
{
    
}

//게임 usn으로 유저 포인터를 얻어온다.
user_ptr CMultiGoManager::getUser(int gameID) 
{
    user_ptr pUser;
    
    std::list<user_ptr>::iterator iter;
    
    for(iter = gameUserList.begin(); iter != gameUserList.end(); iter++)
    {
        pUser = (user_ptr) *iter;

        if(pUser->getGameID() == gameID)
        {
            return pUser;
        }
    }
    
    user_ptr pNull;
    
    return pNull;
}

bool CMultiGoManager::checkUser(int gameID)
{
    bool bResult = false;
    
    user_ptr pUser;
    
    std::list<user_ptr>::iterator iter;
    
    for(iter = gameUserList.begin(); iter != gameUserList.end(); iter++)
    {
        pUser = (user_ptr) *iter;
        
        if(pUser->getGameID() == gameID)
        {
            bResult = true;
            break;
        }
    }
    
    return bResult;
}

void CMultiGoManager::sendAllMessage(GLAnsGameProtocol_Type nType)
{
    
}

void CMultiGoManager::sendMessage(GLAnsGameProtocol_Type nType, int nGameID)//메시를 하나만 보낸다.
{
    
}

void CMultiGoManager::leave(int nGameID) //리스트에서 떠나 보낸다.
{
    //연결되어 있던 유저가 있다면 상태를 바꾼다.
    
    user_ptr pUser;
    
    std::list<user_ptr>::iterator iter;
        
    for(iter = gameUserList.begin(); iter != gameUserList.end(); iter++)
    {
        pUser = (user_ptr) *iter;
        
        if(pUser->getGameID() == nGameID)
        {
            gameUserList.erase(iter);
            break;
        }
    }
    
//    //매치 되었던 상대는 다시 기다릴 수 있게 한다.
//    for (iter = gameUserList.begin(); iter != gameUserList.end(); iter++) 
//    {
//        pUser = (user_ptr) *iter;
//        
//        if(pUser->getMatchUserGameID() == nGameID)
//        {
//            pUser->setUserIndex(0);
//            pUser->setUserState(USER_ROOM_WAIT);
//            pUser->YouJoinInfo.Clear();
//            
//            break;
//        }
//    }
}
