        //
//  MultiUser.cpp
//  DualGoServer
//
//  Created by jin young park on 11. 11. 23..
//  Copyright (c) 2011년 집. All rights reserved.
//

#include "DualGoInclude.h"
//#define DEF_USE_WRITE_QUEUE

#define DEF_USE_WRITE_QUEUE


CMultiUser::CMultiUser(boost::asio::io_service& io_service, CMultiGoManager* manager) :socket_(io_service)
{
    mulManager = manager;
    offset = INDEX_ZERO;
    setUserState(USER_STATE_ZERO);
    JoinInfo.set_roomid(ERROR_VALUE);
    m_iReadSize=0;
    m_iReadedSize=0;
#ifndef DEF_USE_ASIO_ASYNC_READ
	m_iReadedSize=0;
#endif
    
    kickType = GAnsGameLeave_KICK_TYPE_KICK_ZERO;
}

CMultiUser::~CMultiUser()
{
	if(getRoomState() == ROOM_RUN)
    {
        destoryRoom();
    }
}

void CMultiUser::destoryRoom()
{
    setRoomState(ROOM_DIE);
    
    if(mulManager != NULL)
    {
        //상대의 룸상태를 바꾼다
        user_ptr pUser = mulManager->getUser(getMatchUserGameID());
        
        if(pUser != NULL)
        {
            pUser->setRoomState(ROOM_DIE);
        }
    }
    
    pjyDELETE(logicCommand);
}

tcp::socket& CMultiUser::socket()
{
    return socket_;
}

#ifndef DEF_USE_ASIO_ASYNC_READ
void CMultiUser::_async_read_some()
{
	socket_.async_read_some(boost::asio::buffer(m_pDataBuff_Read, BUFFER_SIZE),
		boost::bind(&CMultiUser::handle_read, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}
#endif

void CMultiUser::_async_read()
{
	boost::asio::async_read(socket_,boost::asio::buffer(&m_PPacketHeader_Read
		, sizeof(m_PPacketHeader_Read))
		, boost::bind(&CMultiUser::handle_read_header, shared_from_this()
		, boost::asio::placeholders::error) );
}

void CMultiUser::read_socket()
{
#ifdef DEF_USE_ASIO_ASYNC_READ
	_async_read();
#else
	_async_read_some();
#endif
}



#ifndef DEF_USE_ASIO_ASYNC_READ
void CMultiUser::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
{
	const int iSIZE_m_pDataBuff_Readed = nGS::BUFFER_SIZE*8;

	const int iHEADER_SIZE= sizeof(int);
	if (error)
	{
		jWARN("소켓 아웃 error");
        GameUserInfo* pInfo = JoinInfo.mutable_gameuserinfo();
        
        GameInfo* pGame = pInfo->mutable_gameinfo();

		mulManager->leave(pGame->gameid());
		return;
	}
	if((bytes_transferred + m_iReadedSize) >= iSIZE_m_pDataBuff_Readed )
	{
		jWARN("소켓 아웃 if((bytes_transferred+ m_iReadedSize)>= iSIZE_m_pDataBuff_Readed)");
        GameUserInfo* pInfo = JoinInfo.mutable_gameuserinfo();
        
        GameInfo* pGame = pInfo->mutable_gameinfo();

		mulManager->leave(pGame->gameid());

		return;
	}

	memcpy(m_pDataBuff_Readed+m_iReadedSize,m_pDataBuff_Read,bytes_transferred);
	m_iReadedSize+=bytes_transferred;

	if(m_iReadedSize<= iHEADER_SIZE)
	{
		_async_read_some();
		return;
	}

	char* pBody = m_pDataBuff_Readed;
	int iLengthBody=0;
	memcpy(&iLengthBody , pBody, iHEADER_SIZE);
	pBody+=iHEADER_SIZE;

	if(iLengthBody<=0 || (iLengthBody>=(BUFFER_SIZE-iHEADER_SIZE) ) )
	{
		jWARN("소켓 아웃 error if(iLengthBody<=0 || (iLengthBody>=(BUFFER_SIZE-iHEADER_SIZE) ) )");
        GameUserInfo* pInfo = JoinInfo.mutable_gameuserinfo();
        
        GameInfo* pGame = pInfo->mutable_gameinfo();
		mulManager->leave(pGame->gameid());

		return;
	}

	if(iLengthBody > (m_iReadedSize-iHEADER_SIZE) )
	{
		// 바디가 iLengthBody만큼 못읽었으모.
		_async_read_some();
		return;
	}

	size_t iStayReadedSize = m_iReadedSize;
	try
	{
		for(;;)
		{
			google::protobuf::io::ArrayInputStream is(pBody, iLengthBody);
			GReqProtocol matgo;
			matgo.ParseFromZeroCopyStream(&is);
			switch(matgo.type())
			{
			case GReqProtocol_Type_GLREQGAMEPROTOCOL:
				{
					GLReqGameProtocol* packet = matgo.mutable_reqgameprotocol();
					jBREAK(packet);
					packetParse(packet);
					break;
				}
            case GReqProtocol_Type_GREQGAMEENTER:
                {
                    GReqGameEnter* enter = matgo.mutable_reqgameenter();
                    jBREAK(enter);
                    
                    GameUserInfo* gameUserInfo = enter->mutable_gameuserinfo();
                    GameInfo* pSocGame = gameUserInfo->mutable_gameinfo();

                    
                    if(mulManager->checkUser(pSocGame->gameid()))
                    {
                        mulManager->leave(pSocGame->gameid());
                        
#ifdef LOGSET
                        std::cerr << "User duplicate = " << pSocGame->gameid() << "\n";
#endif
                    }
                    else
                    {
                        parseEnterGame(enter);
                        
                        GAnsProtocol ansPro;
                        
                        makeEnter(ansPro);
                        
                        sendAllPacket(ansPro);
                    }
                    break;
                }
            case GReqProtocol_Type_GREQGAMELEAVE:
                {
                    GReqGameLeave* leave = matgo.mutable_reqgameleave();
                    jBREAK(leave);
                    parseLeave(leave);
                    break;
                }
            case GReqProtocol_Type_GREQPLUG:
            {
                GReqPlug* plug = matgo.mutable_reqplug();
                jBREAK(plug);
                parsePlug(plug);
                break;
            }
            case GReqProtocol_Type_GREQDETACH:
            {
                GReqDetach* detach = matgo.mutable_reqdetach();
                jBREAK(detach);
                parseDetach(detach);
                break;
            }
            case GReqProtocol_Type_GDBANS:
            {
                AnsDB* db = matgo.mutable_ansdb();
                jBREAK(db);
                parseDB(db);
                break;
            }
//			case FlowMatGo_Type_PING:
//				{
//					FlowMatGo req;
//					req.set_type(FlowMatGo_Type_PONG);
//					sendPacket(req);
//					jLOG("Send Pong");
//					break;
//				}
			default:
				{
					jWARN("matgo.type() : invalied packet");
                    GameUserInfo* pInfo = JoinInfo.mutable_gameuserinfo();
                    
                    GameInfo* pGame = pInfo->mutable_gameinfo();
                    mulManager->leave(pGame->gameid());
					return;
				}
			}//switch(matgo.type())

			iStayReadedSize -= (iLengthBody+iHEADER_SIZE);
			if(iStayReadedSize<=0)
			{
				m_iReadedSize=0;
				break;
			}

			jWARN("data뭉쳐서왔다.");
			if(iStayReadedSize<= iHEADER_SIZE)
			{
				memmove(m_pDataBuff_Readed, pBody, iStayReadedSize);
				m_iReadedSize=iStayReadedSize;
				break;
			}
			//파싱할 패킷이 남았다.
			pBody = pBody+iLengthBody;
			memcpy(&iLengthBody,pBody,iHEADER_SIZE);
			if(iLengthBody > (iStayReadedSize-iHEADER_SIZE ) ) //아직 바디 데이타가 완성안되었으모.
			{
				memmove(m_pDataBuff_Readed, pBody, iLengthBody);
				m_iReadedSize=iLengthBody;
				break;
			}
			pBody+=iHEADER_SIZE;

		}//for(;;)
		_async_read_some();

	}
	catch (...) 
	{
		jWARN("try");
        
        GameUserInfo* pInfo = JoinInfo.mutable_gameuserinfo();
        
        GameInfo* pGame = pInfo->mutable_gameinfo();
		mulManager->leave(pGame->gameid());
	}
}
#endif

void CMultiUser::handle_read_header(const boost::system::error_code& error)
{
	if(error)
	{
		jERROR("소켓 아웃");
        GameUserInfo* pInfo = JoinInfo.mutable_gameuserinfo();
        
        GameInfo* pGame = pInfo->mutable_gameinfo();

		mulManager->leave(pGame->gameid());

		return;
	}
	if (m_PPacketHeader_Read.data_length < 0 && m_PPacketHeader_Read.data_length >= nGS::BUFFER_SIZE)
	{
		return;
	}
	boost::asio::async_read(socket_,
		boost::asio::buffer(m_pDataBuff_Read, m_PPacketHeader_Read.data_length ),
		boost::bind(&CMultiUser::handle_read_body, shared_from_this(),
		boost::asio::placeholders::error));
}

void CMultiUser::handle_read_body(const boost::system::error_code& error)
{
    if (error)
	{
		jERROR("소켓 아웃 여기서 에러처리한다.")
        GameUserInfo* pInfo = JoinInfo.mutable_gameuserinfo();
        
        GameInfo* pGame = pInfo->mutable_gameinfo();
		mulManager->leave(pGame->gameid());

		return;
	}

	google::protobuf::io::ArrayInputStream is(m_pDataBuff_Read, m_PPacketHeader_Read.data_length);

	try
	{
		GReqProtocol matgo;
		matgo.ParseFromZeroCopyStream(&is);
		jONCE
		{
			if (matgo.type() == GReqProtocol_Type_GLREQGAMEPROTOCOL)
			{
				GLReqGameProtocol* packet = matgo.mutable_reqgameprotocol();
				jBREAK(packet);
				packetParse(packet);
			}
//			else if (matgo.type() == FlowMatGo_Type_PING)
//			{
//				FlowMatGo req;
//				req.set_type(FlowMatGo_Type_PONG);
//				sendPacket(req);
//				jLOG(_T("Send Pong"));
//			}
		}
	}
	catch (...)
	{
		jERROR(" matgo.ParseFromZeroCopyStream");
	}

	this->read_socket();
}


void CMultiUser::sendPacket(GAnsProtocol& matgo)              
{
	int nSize = matgo.ByteSize();
	m_writeBuff.header.data_length = matgo.ByteSize()+sizeof(int);
	jRETURN(m_writeBuff.header.data_length<nGS::BUFFER_SIZE);
	memcpy(m_writeBuff.pBody, &nSize, sizeof(int));
	assert(sizeof(m_writeBuff.header)==4);

	google::protobuf::io::ArrayOutputStream os(m_writeBuff.pBody+sizeof(int), matgo.ByteSize());
	matgo.SerializeToZeroCopyStream(&os);
#ifdef DEF_USE_WRITE_QUEUE
//패킷을 보낸다.
	bool write_msgs_empty = m_write_msgs.empty();
	m_write_msgs.push_back(m_writeBuff);	
	if (write_msgs_empty)
#endif
	{
		this->_send();
	}
    
#ifdef LOGSET    
    std::cerr << "send packet uid = " << getGameID() << "\n";
#endif


}

void CMultiUser::_send()
{
#ifdef DEF_USE_WRITE_QUEUE
	boost::asio::async_write(socket_,
		boost::asio::buffer(m_write_msgs.front().pBody,m_write_msgs.front().header.data_length),
		boost::bind(&CMultiUser::handle_write, shared_from_this(),
		boost::asio::placeholders::error));

#else
	boost::asio::async_write(socket_,
		boost::asio::buffer(m_writeBuff.pBody,m_writeBuff.header.data_length),
		boost::bind(&CMultiUser::handle_write, shared_from_this(),
		boost::asio::placeholders::error));
#endif
}


//패킷을 다른 사람에게 보낸다.
void CMultiUser::sendYouPacket(GAnsProtocol& matgo, int GameID)
{
    //상대방 포인터를 찾는다.
    user_ptr pUser = mulManager->getUser(GameID);
    
    if(pUser != NULL)
    {
        pUser->sendPacket(matgo);
    }
    else
    {

    }   
}

void CMultiUser::sendYouPacket(GAnsProtocol& matgo)
{
    GameUserInfo* pYouInfo = YouJoinInfo.mutable_gameuserinfo();
    GameUserInfo* pInfo = JoinInfo.mutable_gameuserinfo();
    
    GameInfo* pGame = pInfo->mutable_gameinfo();
    
    GameInfo* pYouGame = pYouInfo->mutable_gameinfo();
    
#ifdef LOGSET
    std::cerr << "send you id = " << pYouGame->gameid() << "\n";
#endif
    
    if((pGame->gameid() != pYouGame->gameid()) && pYouGame->gameid() > 0)
    {
#ifdef LOGSET
        
        std::cerr << "send you packet\n";
#endif
        sendYouPacket(matgo, pYouGame->gameid());
    }
    
}

//패킷을 모두 보낸다.
void CMultiUser::sendAllPacket(GAnsProtocol& matgo)
{
    sendPacket(matgo);

    GameUserInfo* pYouInfo = YouJoinInfo.mutable_gameuserinfo();
    GameUserInfo* pInfo = JoinInfo.mutable_gameuserinfo();
    
    GameInfo* pGame = pInfo->mutable_gameinfo();
    GameInfo* pYouGame = pYouInfo->mutable_gameinfo();
    
#ifdef LOGSET
    std::cerr << "send id = " << getGameID() << "\n";
    std::cerr << "send you id = " << pYouGame->gameid() << "\n";
#endif
    
    if((pGame->gameid() != pYouGame->gameid()) && pYouGame->gameid() > 0)
    {
#ifdef LOGSET
        
        std::cerr << "send you packet\n";
#endif
        sendYouPacket(matgo, pYouGame->gameid());
    }
}


//패킷 보낸후 콜백
void CMultiUser::handle_write(const boost::system::error_code& error)
{
	if (error)
	{
		// 		m_write_error_count++;
		// 		if(m_write_error_count>50)
		// 		{
					jWARN(_T("handle_write..."));
        GameUserInfo* pInfo = JoinInfo.mutable_gameuserinfo();
        
        GameInfo* pGame = pInfo->mutable_gameinfo();

       mulManager->leave(pGame->gameid());

		// 			...
		// 		}
		return;
	}
#ifdef DEF_USE_WRITE_QUEUE
	m_write_msgs.pop_front();
	if(!m_write_msgs.empty())
		this->_send();
#endif
}

//게임 패킷을 만든다.
void CMultiUser::makePacket(GAnsProtocol_Type nType, GAnsProtocol& matgo)
{    
    switch (nType) {
        case GReqProtocol_Type_GREQGAMEENTER:
            //makeReqGameJoinRoom(matgo);
            break;
        case GReqProtocol_Type_GREQGAMELEAVE:
            break;
        case GReqProtocol_Type_GREQDETACH:
            break;
        case GReqProtocol_Type_GREQPLUG:
            break;
//        case GAnsProtocol_Type_GANSGAMEENTER:
///            makeEnter(matgo);
            break;

        default:
            break;
    }
                                                  
//  makeGameStartReady(matgo);
//  
//  setTimer(TIMER_START);
//
//       
//       GLAnsGameProtocol_Type
}

//게임 패킷을 만든다.
void CMultiUser::makeGamePacket(GLAnsGameProtocol_Type nType, GAnsProtocol& matgo)
{    
    switch (nType) {
            
        case GLAnsGameProtocol_Type_GAME_STARTREADY:
            makeGameStartReady(matgo);
            
            setTimer(TIMER_START);
            break;
            
        default:
            break;
    }
}

void CMultiUser::makeEnter(GAnsProtocol& matgo)
{
    matgo.set_type(::GAnsProtocol_Type_GANSGAMEENTER);
    
    GAnsGameEnter* packet = matgo.mutable_ansgameenter();
    
    GameRoomInfo* pRoom = packet->mutable_gameroominfo();
    
    pRoom->set_roomid(getRoomID());
    pRoom->set_pointmoney((int)getPointMoney(JoinInfo.categoryid()));
    
    GameUserInfo* gameUserInfo = JoinInfo.mutable_gameuserinfo();
    GameUserInfo* pJoin = pRoom->add_gameuserinfo();
    
    GameInfo* pDetGame = pJoin->mutable_gameinfo();
    GameInfo* pSocGame = gameUserInfo->mutable_gameinfo();
        
    pDetGame->CopyFrom(*pSocGame);
    
    MemberInfo* pDetMember = pJoin->mutable_memberinfo();
    MemberInfo* pSocMember = gameUserInfo->mutable_memberinfo();
    
    pDetMember->CopyFrom(*pSocMember);
        
    pRoom = packet->mutable_gameroominfo();
    
    pRoom->set_roomid(getRoomID());
    pRoom->set_pointmoney((int)getPointMoney(JoinInfo.categoryid()));
    
    gameUserInfo = YouJoinInfo.mutable_gameuserinfo();
    
    pSocGame = gameUserInfo->mutable_gameinfo();
    
    if(pSocGame->gameid() > 0)
    {  
        pJoin = pRoom->add_gameuserinfo();
        
        pDetGame = pJoin->mutable_gameinfo();
        pSocGame = gameUserInfo->mutable_gameinfo();
        
        pDetGame->CopyFrom(*pSocGame);
            
        pDetMember = pJoin->mutable_memberinfo();
        pSocMember = gameUserInfo->mutable_memberinfo();
        
        pDetMember->CopyFrom(*pSocMember);
    }
}

void CMultiUser::makeLeave(GAnsProtocol& matgo, int gameID, GAnsGameLeave_KICK_TYPE nType)
{
    matgo.set_type(::GAnsProtocol_Type_GANSGAMELEAVE);
    
    GAnsGameLeave* packet = matgo.mutable_ansgameleave();
    
    packet->set_gameid(gameID);
    packet->set_ntype(nType);
    
}

void CMultiUser::makePlug(GAnsProtocol& matgo, int gameID)
{
    matgo.set_type(::GAnsProtocol_Type_GANSPLUG);
    
    GAnsPlug* packet = matgo.mutable_ansplug();
    
    packet->set_gameid(gameID);
}

void CMultiUser::makePlugErr(GAnsProtocol& matgo, std::string str)
{
    matgo.set_type(::GAnsProtocol_Type_GERRPLUG);
    
    GErrPlug* packet = matgo.mutable_anserr();
    
    GError* err = packet->mutable_error();
    
    err->set_errorcode(1);
    err->set_errorinfo(str);
}

void CMultiUser::makeExitReservation(GAnsProtocol& matgo, int gameIndex, bool bExit)
{
    matgo.set_type(::GAnsProtocol_Type_GLANSGAMEPROTOCOL);
    
    GLAnsGameProtocol* packet = matgo.mutable_ansgameprotocol();
    
    packet->set_type(::GLAnsGameProtocol_Type_GAME_EXITRESERVATION);
    
    GLAnsExitReservation* exit = packet->mutable_ansexitreservation();
    
    exit->set_gameindex(gameIndex);
    exit->set_bexit(bExit);
}

//패킷 파서
void CMultiUser::packetParse(GLReqGameProtocol* packet)           
{
#ifdef LOGSET
    std::cerr << "rec packet\n";
#endif
    switch (packet->type()) 
    {              
        case GLReqGameProtocol_Type_REQ_GAME_READY:
            parseGameReady(packet->mutable_reqgameready());
            break;            
        case GLReqGameProtocol_Type_REQ_GAME_INITGAME:
            parseGameReqInitGame(packet->mutable_reqinitgame());
            break;
        case GLReqGameProtocol_Type_REQ_GAME_SELECTSUNCARD:
            parseGameReqSelectSunCard(packet->mutable_reqselectsuncard());
            break;
        case GLReqGameProtocol_Type_REQ_GAME_START:
            parseGameReqGameStart(packet->mutable_reqstart());
            break;
        case GLReqGameProtocol_Type_REQ_GAME_SELECTCARD:
            parseGameSelectCard(packet->mutable_reqselectcard());
            break;
        case GLReqGameProtocol_Type_REQ_GAME_ASKSHAKEANS:
            parseGameAskShakeAns(packet->mutable_reqaskshakeans());
            break;
        case GLReqGameProtocol_Type_REQ_GAME_CHOICECARDANS:
            parseGameChoiceCard(packet->mutable_reqchoicecardans());
            break;
        case GLReqGameProtocol_Type_REQ_GAME_RESET:
            parseGameReset(packet->mutable_reqreset());
            break;
        case GLReqGameProtocol_Type_REQ_GAME_RESULTOK:
            parseGameResultOk(packet->mutable_reqresultok());
            break;
        case GLReqGameProtocol_Type_REQ_GAME_ASKGOSTOPANS:
            parseGameAskGostopAns(packet->mutable_reqaskgostopans());
            break;
        case GLReqGameProtocol_Type_REQ_GAME_MOVETEN:
            parseGameMoveTen(packet->mutable_reqmoveten());
            break;
        case GLReqGameProtocol_Type_REQ_GAME_CHONGTONG:
            parseGameChongtong(packet->mutable_reqchongtong());
            break;
        case GLReqGameProtocol_Type_REQ_GAME_AUTOPLAY:
            parseGameAutoPlay(packet->mutable_reqgameautoplay());
            break;
        case GLReqGameProtocol_Type_REQ_GAME_EXITRESERVATION:
            parseExitReservation(packet->mutable_reqexitreservation());
            break;
        case GLReqGameProtocol_Type_REQ_GAME_RELAYINFO:
            parseGameRelayInfo(packet->mutable_reqrelayinfo());
            break;
        case GLReqGameProtocol_Type_REQ_GAME_EMOTI:
            parseGameEmoti(packet->mutable_reqgameemoti());
        case GLReqGameProtocol_Type_REQ_GAME_END:
            
            break;
            
        case GLReqGameProtocol_Type_REQ_GAME_INITGAMETAN:
            parseGameInitTan(packet->mutable_reqtaninit());
            break;
        default:
            break;
    }
}

void CMultiUser::parseLeave(GReqGameLeave* packet)
{
    if(packet != NULL)
    { 
        if(logicCommand != NULL && getRoomState() == ROOM_RUN)
        {
            if(packet->gameid() == getGameID())
            {
                logicCommand->requestGameLeave(getGameID(), EXIT_RESERVATION);
            }
        }
        else
        {
            GAnsProtocol matgo;
            makeLeave(matgo, packet->gameid(), GAnsGameLeave_KICK_TYPE_EXIT_RESERVATION);
            
            sendPacket(matgo);
        }
        
#ifdef LOGSET
        std::cerr << "i = " << getGameID() << "you = " << packet->gameid() << "\n";
#endif
    }
}

//게임을 떠날때 정리한다.
void CMultiUser::leaveSet(int nGameID)
{
    //떠나는 사람이 내가 아니면
    if(getGameID() != nGameID)
    {
        YouJoinInfo.Clear();
        
        //게임을 리셋한다.
        logicCommand->resetInit();
        
        setUserIndex(0);
        
//        setLogicCommand(logicCommand);
        
        setRoomState(ROOM_DIE);
    }
    else
    {
        //게임을 리셋한다.
        logicCommand->resetInit();
        
        user_ptr pUser = mulManager->getUser(getMatchUserGameID());
        
        if(pUser != NULL)
        {
            pUser->setUserIndex(0);
        }
        
//        setLogicUser();
        
        pUser->setRoomState(ROOM_DIE);
    }
}

void CMultiUser::parseEnterGame(GReqGameEnter* packet)
{
    if(packet != NULL)
    {
        GameUserInfo* gameUserInfo = packet->mutable_gameuserinfo();
        GameUserInfo* pJoin = JoinInfo.mutable_gameuserinfo();
        
        GameInfo* pDetGame = pJoin->mutable_gameinfo();
        GameInfo* pSocGame = gameUserInfo->mutable_gameinfo();
        
        JoinInfo.set_categoryid(packet->categoryid());
        JoinInfo.set_channelid(packet->channelid());
        JoinInfo.set_roomid(packet->roomid());
        
        pDetGame->CopyFrom(*pSocGame);
        
        MemberInfo* pDetMember = pJoin->mutable_memberinfo();
        MemberInfo* pSocMember = gameUserInfo->mutable_memberinfo();
        
        pDetMember->CopyFrom(*pSocMember);
        
        mulManager->setMatchRoom(pSocGame->gameid(), packet->roomid());
    }
}

void CMultiUser::parsePlug(GReqPlug* packet)
{
    if(packet != NULL)
    {
        GAnsProtocol matgo;
        int gameID = packet->gameid();
        
        if(mulManager->getUserIndex(gameID) == ERROR_VALUE)
        {
            makePlugErr(matgo, "plug Error");
            
            sendPacket(matgo);
            //sendAllPacket(matgo);
        }
        else
        {
            makePlug(matgo, gameID);
            
            sendPacket(matgo);
            
            //sendAllPacket(matgo);
        }
    }
}

void CMultiUser::parseDetach(GReqDetach* detach)
{
    int uID = detach->gameid();
    
    user_ptr pUser = mulManager->getUser(uID);
    
    if(pUser != NULL)
    {
        GAnsProtocol ans;
        
        GAnsGameLeave_KICK_TYPE nType = GAnsGameLeave_KICK_TYPE_EXIT_RESERVATION;
        
        if(pUser->getUserState() == USER_ROOM_WAIT)
        {
            makeLeave(ans, uID, nType);
            
            sendAllPacket(ans);
            
            mulManager->leave(uID);
        }
    }
}

void CMultiUser::parseDB(AnsDB* db)
{
    if(db->retcode() == 1)
    {
        if(db->seq() == (int)GAME_RESULT)
        {
            GameUserInfo* pUserGame = JoinInfo.mutable_gameuserinfo();
            GameInfo* pGameInfo = pUserGame->mutable_gameinfo();
            
            GameUserInfo* pYouGame = YouJoinInfo.mutable_gameuserinfo();
            GameInfo* pYou = pYouGame->mutable_gameinfo();
            
            user_ptr pMatchUser = mulManager->getUser(getMatchUserGameID());
            
            GameUserInfo* pMatchUserGame;
            GameInfo* pMatchGameInfo;            
            GameUserInfo* pMatchYouGame;
            GameInfo* pMatchYou;
            
            if(pMatchUser != NULL)
            {
                pMatchUserGame = pMatchUser->JoinInfo.mutable_gameuserinfo();
                pMatchGameInfo = pMatchUserGame->mutable_gameinfo();
                
                pMatchYouGame = pMatchUser->YouJoinInfo.mutable_gameuserinfo();
                pMatchYou = pMatchYouGame->mutable_gameinfo();
            }

            GameUpdateInfo upInfo;
            
            upInfo.ParseFromString(*db->mutable_result());
    
            MoneyInfo pInfo;
            
            pInfo.set_money("0");
                        
            int level = -1;
                        
            for(int i=0; i< upInfo.gameinfo_size(); i++)
            {
                GameInfo pGame = upInfo.gameinfo(i);
            
                if(pGame.gameid() == pGameInfo->gameid())
                {
                    pGameInfo->CopyFrom(pGame);
                    
                    if(pMatchYou != NULL)
                    {
                        pMatchYou->CopyFrom(pGame);
                    }
                }
                else if(pGame.gameid() == pYou->gameid())
                {
                    pYou->CopyFrom(pGame);
                    
                    if(pMatchGameInfo != NULL)
                    {
                        pMatchGameInfo->CopyFrom(pGame);
                    }
                }
                
                if(upInfo.moneyinfo_size() > 0)
                {
                    pInfo = upInfo.moneyinfo(0);
                    
                    if(pGame.gameid() == pInfo.gameid())
                    {
                        level = pGame.level();
                    }
                }
            }

            logicCommand->sendDbUpdate(pInfo.gameid(), level, atoll(pInfo.money().c_str()));
        }
        else
        {
#ifdef LOGSET
            std::cerr << "Mission DB Recv";
#endif 
            GameUpdateInfo upInfo;
            
            upInfo.ParseFromString(*db->mutable_result());
            
            MoneyInfo pInfo;
            
            for(int i=0; i<upInfo.moneyinfo_size(); i++)
            {
                pInfo = upInfo.moneyinfo(i);
            }
        }
    }
    else
    {
        //DB 에러 처리
        GAnsProtocol matgo;
        makeLeave(matgo, getGameID(), GAnsGameLeave_KICK_TYPE_SYSTEM_ERROR);
        
        sendAllPacket(matgo);
    }
}
                                
unsigned long long CMultiUser::getPointMoney(int cateID)
{
    unsigned long long llPoint = 1000;
    
    switch(cateID)
    {
        case 0:
            llPoint = 1000;
            break;
        case 1:
            llPoint = 3000;
            break;
        case 2:
            llPoint = 5000;
            break;
        case 3:
            llPoint = 10000;
            break;
        case 4:
            llPoint = 30000;
            break;
        case 5:
            llPoint = 50000;
            break;

        default:
            llPoint = 1000;
            break;
    }
    
    return llPoint;
}


//유저 응답 응답을 보낸다.
//void CMultiUser::makeUserConnectAns(FlowMatGo& matgo)
//{
//    matgo.set_type(::FlowMatGo_Type_MATGOPACKET);
//    
//    GamePacket* packet = matgo.mutable_gamepacket();
//    
//    packet->set_type(::GamePacket_Type_UG_USERCONNECT_ANS);
//    
//    GameUserConnectAns* ans = packet->mutable_gameuserconnectans();
//    
//    ans->set_gameindex(mulManager->getUserIndex(JoinInfo.gameid()));
//}
//
//GameJoinRoom 패킷을 만든다.
void CMultiUser::makeGameJoinRoom(GAnsProtocol& matgo)
{
//    matgo.set_type(::FlowMatGo_Type_MATGOPACKET);
//    
//    GamePacket* packet = matgo.mutable_gamepacket();
//    
//    packet->set_type(::GamePacket_Type_GAME_JOINROOM);
//    
//    GameJoinRoom* pJoinRoom = packet->mutable_gamejoin();
//    
//    pJoinRoom->set_gameid(JoinInfo.gameid());   
//    pJoinRoom->set_gameindex(JoinInfo.gameindex());
//    
//    pJoinRoom->set_avatarurl(JoinInfo.avatarurl());
//    pJoinRoom->set_nickname(JoinInfo.nickname());
//    pJoinRoom->set_level(JoinInfo.level());
//    pJoinRoom->set_money(JoinInfo.money());
//    pJoinRoom->set_wincnt(JoinInfo.wincnt());
//    pJoinRoom->set_losecnt(JoinInfo.losecnt());
//    pJoinRoom->set_allincnt(JoinInfo.allincnt());
//    
//    pJoinRoom->set_pointmoney(JoinInfo.pointmoney());
    
//#ifdef LOGSET
//    std::cerr << "gameID = " << pJoinRoom->gameid() << "\n";
//    std::cerr << "avataUrl = " << pJoinRoom->avatarurl() << "\n";
//    std::cerr << "nickname = " << pJoinRoom->nickname() << "\n";
//    std::cerr << "level = " << pJoinRoom->level() << "\n";
//    std::cerr << "winCnt = " << pJoinRoom->wincnt() << "\n";
//    std::cerr << "losecnt = " << pJoinRoom->losecnt() << "\n";
//    std::cerr << "allincnt = " << pJoinRoom->allincnt() << "\n";
//    std::cerr << "point money = " << pJoinRoom->pointmoney() << "\n";    
//#endif

}

void CMultiUser::makeReqGameJoinRoom(GAnsProtocol& matgo)
{
//    matgo.set_type(::FlowMatGo_Type_MATGOPACKET);
//    
//    GamePacket* packet = matgo.mutable_gamepacket();
//    
//    packet->set_type(::GamePacket_Type_REQ_GAME_JOINROOM);
    
}

//게임 스타트 버튼을 준비 시킨다.
void CMultiUser::makeGameStartReady(GAnsProtocol& matgo)
{
#ifdef LOGSET
    std::cerr << "make packet start ready!!\n";
#endif
    matgo.set_type(::GAnsProtocol_Type_GLANSGAMEPROTOCOL);
    
    GLAnsGameProtocol* packet = matgo.mutable_ansgameprotocol();
    
    packet->set_type(::GLAnsGameProtocol_Type_GAME_STARTREADY);
    
    GLAnsGameStartReady* ready = packet->mutable_gamestartready();
    
    GameUserInfo* pGame = JoinInfo.mutable_gameuserinfo();
    
    GameInfo* pInfo = pGame->mutable_gameinfo();
    
    ready->set_gameid(pInfo->gameid());
    ready->set_gameindex(pInfo->gameindex());
}

//게임룸에 입장할때
void CMultiUser::parseJoinRoom(GReqGameEnter* joinRoom)
{
    //여기서 게임 룸을 조인한 정보를 가지고 있는다.
//    if(joinRoom->gameid() == JoinInfo.gameid())
//    {
//        JoinInfo.set_gameindex(joinRoom->gameindex());
//        JoinInfo.set_avatarurl(joinRoom->avatarurl());
//        JoinInfo.set_nickname(joinRoom->nickname());
//        JoinInfo.set_level(joinRoom->level());
//        JoinInfo.set_money(joinRoom->money());
//        JoinInfo.set_wincnt(joinRoom->wincnt());
//        JoinInfo.set_losecnt(joinRoom->losecnt());
//        JoinInfo.set_allincnt(joinRoom->allincnt());
//        JoinInfo.set_pointmoney(joinRoom->pointmoney());
//    }
//    else
//    {
//        YouJoinInfo.set_gameid(joinRoom->gameid());
//        YouJoinInfo.set_gameindex(joinRoom->gameindex());
//        YouJoinInfo.set_avatarurl(joinRoom->avatarurl());
//        YouJoinInfo.set_nickname(joinRoom->nickname());
//        YouJoinInfo.set_level(joinRoom->level());
//        YouJoinInfo.set_money(joinRoom->money());
//        YouJoinInfo.set_wincnt(joinRoom->wincnt());
//        YouJoinInfo.set_losecnt(joinRoom->losecnt());
//        YouJoinInfo.set_allincnt(joinRoom->allincnt());
//        YouJoinInfo.set_pointmoney(joinRoom->pointmoney());
//    }
}

//게임 준비가 되었다.
void CMultiUser::parseGameReady(GLReqGameReady* gameReady)
{
    //래디 상태로 바꾼다.
    setUserState(USER_GAME_READY);
    
    //게임이 전부 래디 상태인지 확인한다.
    user_ptr pUSer = mulManager->getUser(getMatchUserGameID());
    
    if(pUSer != NULL)
    {
        if(pUSer->getUserState() == USER_GAME_READY)
        {
            GAnsProtocol matgo;
            
            GameUserInfo* pGame = JoinInfo.mutable_gameuserinfo();
            GameUserInfo* pYouGame = YouJoinInfo.mutable_gameuserinfo();
        
            GameInfo* pInfo = pGame->mutable_gameinfo();
            GameInfo* pYouInfo = pYouGame->mutable_gameinfo();

            if(pInfo->gameindex() == 0)
            {
                makeGamePacket(::GLAnsGameProtocol_Type_GAME_STARTREADY, matgo);
                
                sendPacket(matgo);
                
    #ifdef LOGSET
                std::cerr << "gameID = " << pInfo->gameid() << " start ready send\n";
    #endif
            }
            else if(pYouInfo->gameindex() == 0)
            {
                pUSer->makeGamePacket(::GLAnsGameProtocol_Type_GAME_STARTREADY, matgo);
                
                pUSer->sendPacket(matgo);
    #ifdef LOGSET
                std::cerr << "gameID = " << pYouInfo->gameid() << " start ready send\n";
    #endif

            }
        }
    }
}

//처음 접속할때
//void CMultiUser::parseConnectUserReq(GameUserConnectReq* userConnectReq)
//{
//    JoinInfo.set_gameid(userConnectReq->gameid());
//    
//    JoinInfo.set_avatarurl(userConnectReq->avataurl());
//    JoinInfo.set_nickname(userConnectReq->nickname());
//    JoinInfo.set_level(userConnectReq->level());
//    JoinInfo.set_money(userConnectReq->money());
//    JoinInfo.set_wincnt(userConnectReq->wincnt());
//    JoinInfo.set_losecnt(userConnectReq->losecnt());
//    JoinInfo.set_allincnt(userConnectReq->allincnt());
//    JoinInfo.set_pointmoney(userConnectReq->pointmoney());
//    
//#ifdef LOGSET
//    std::cerr << "gameID = " << JoinInfo.gameid() << "\n";
//    std::cerr << "avataUrl = " << JoinInfo.avatarurl() << "\n";
//    std::cerr << "nickname = " << JoinInfo.nickname() << "\n";
//    std::cerr << "level = " << JoinInfo.level() << "\n";
//    std::cerr << "winCnt = " << JoinInfo.wincnt() << "\n";
//    std::cerr << "losecnt = " << JoinInfo.losecnt() << "\n";
//    std::cerr << "allincnt = " << JoinInfo.allincnt() << "\n";
//    std::cerr << "point money = " << JoinInfo.pointmoney() << "\n";    
//#endif
//}

//최초 게임을 시작한다.
void CMultiUser::parseGameReqInitGame(GLReqGameInitGame* gameInit)
{  
    //포인트 머니 어디서 받을것인가?
//    GameUserInfo* pInfo = JoinInfo.mutable_gameuserinfo();
//    
//    GameInfo* pGame = pInfo->mutable_gameinfo();
    
    if(logicCommand != NULL && getRoomState() != ROOM_DIE)
    {
        logicCommand->initGame();
    }
}

void CMultiUser::parseGameInitTan(GLReqGameInitGameTan* tan)
{
    if(tan != NULL && logicCommand != NULL)
    {
        logicCommand->setRoomPointMoney();
        
        logicCommand->requestInitGame((TAN_TYPE)tan->tantype(), (MISSION_TYPE)tan->missiontype(), tan->missionmul());
    }
}


//선을 선택한 인덱스
void CMultiUser::parseGameReqSelectSunCard(GLReqGameSelectSunCard* sunCard)
{
    if(sunCard != NULL)
    {
        logicCommand->requestSelectSunCard(sunCard->gameindex(), sunCard->ncard());
    }
}

//게임을 시작한다.
void CMultiUser::parseGameReqGameStart(GLReqGameStart* start)
{
    if(start != NULL)
    {
        logicCommand->requestGameStart(MULTI_GAME, MISSION_ZERO, INDEX_ZERO, TAN_ZERO);
    }
}

void CMultiUser::parseGameReset(GLReqGameReset* reset)
{
    if(reset != NULL)
    {
        logicCommand->resetGame();
    }
}

void CMultiUser::parseGameResultOk(GLReqResultOk* resultOk)
{
    if(resultOk != NULL)
    {
        if(logicCommand != NULL && getRoomState() == ROOM_RUN)
        {
            logicCommand->requestResultOk(resultOk->gameindex());
        }
    }
}

void CMultiUser::parseGameSelectCard(GLReqGameSelectCard* slect)
{
    if(getRoomState() == ROOM_RUN)
    {
        if(select != NULL)
        {
            logicCommand->requestSelectCard(slect->gameindex(), slect->ncard());
        }
    }
}

void CMultiUser::parseGameAskGostopAns(GLReqGameAskGoStopAns* ans)
{
    if(ans != NULL)
    {
        logicCommand->requestAskGoStopAns(ans->gameindex(), ans->bgo());
    }
}

void CMultiUser::parseGameAskShakeAns(GLReqGameAskShakeAns* ans)
{
    if(ans != NULL)
    {
        logicCommand->requestAskShakeAns(ans->gameindex(), ans->bshake());
    }
}

void CMultiUser::parseGameChoiceCard(GLReqGameChoiceCardAns* card)
{
    if(card != NULL)
    {
        GAME_STATE nType = GAME_ZERO;
        
        switch (card->ntype()) 
        {
            case GLReqGameChoiceCardAns_Type_SELECT:
                nType = GAME_SELECTCARD;
                break;
            case GLReqGameChoiceCardAns_Type_UPSET:
                nType = GAME_UPSET;
                break;
                
            default:
                break;
        }
        
        logicCommand->requestChoiceHTAns(card->gameindex(), card->ncard(), nType);
    }
}

void CMultiUser::parseGameMoveTen(GLReqGameMoveTen* move)
{
    if(move != NULL)
    {
        logicCommand->requestMoveTenAns(move->gameindex(), move->bmove());
    }
}

void CMultiUser::parseGameChongtong(GLReqGameChongTong* chong)
{
    if(chong != NULL)
    {
        logicCommand->request4HTAns(chong->gameindex(), chong->byes());
    }
}

void CMultiUser::parseGameAutoPlay(GLReqGameAutoPlay* play)
{
    if(play != NULL)
    {
        logicCommand->requestGameAutoPlay(play->gameindex(), play->bauto());
    }
}
void CMultiUser::parse_REQ_GAME_TEST_PACKET(G_REQ_GAME_TEST_PACKET* p)
{
	if(p!= NULL)
	{
		logicCommand->request_REQ_GAME_TEST_PACKET(p->test_string(),p->test_int());
	}
}

void CMultiUser::parseExitReservation(GLReqExitReservation* exit)
{
    if(getRoomState() == ROOM_RUN)
    {
        if(exit != NULL)
        {
            logicCommand->reqExitReservation(exit->gameindex(), exit->bexit());
        }
        
        //바로 보내기
        GAnsProtocol matgo;
        
        matgo.set_type(::GAnsProtocol_Type_GLANSGAMEPROTOCOL);
        
        GLAnsGameProtocol* packet = matgo.mutable_ansgameprotocol();
        
        packet->set_type(::GLAnsGameProtocol_Type_GAME_EXITRESERVATION);
        
        GLAnsExitReservation* pExit = packet->mutable_ansexitreservation();
        
        pExit->set_gameindex(exit->gameindex());
        pExit->set_bexit(exit->bexit());
        
        sendAllPacket(matgo);
    }
}

void CMultiUser::parseGameRelayInfo(GLReqRelayInfo* relay)
{
#ifdef LOGSET
    std::cerr << "RelayInfo : ROOM STATE = " << getRoomState() << "\n";
#endif
    if(relay != NULL)
    {
        if(getRoomState() == ROOM_RUN && logicCommand != NULL)
        {
            logicCommand->reqRelayInfo(relay->gameid());
        }
        else
        {
            GAnsProtocol ans;

            makeLeave(ans, getGameID(), GAnsGameLeave_KICK_TYPE_SYSTEM_ERROR);
            
            sendPacket(ans);
        }
    }
}

void CMultiUser::parseGameEmoti(GLReqGameEmoti* emoti)
{
    if(emoti != NULL)
    {
        //바로 보내기
        GAnsProtocol matgo;
        
        matgo.set_type(::GAnsProtocol_Type_GLANSGAMEPROTOCOL);
        
        GLAnsGameProtocol* packet = matgo.mutable_ansgameprotocol();
        
        packet->set_type(::GLAnsGameProtocol_Type_GAME_EMOTI);
        
        GLAnsGameEmoti* pEmoti = packet->mutable_ansgameemoti();
        
        pEmoti->set_gameindex(emoti->gameindex());
        pEmoti->set_ntype(emoti->ntype());
        
        sendYouPacket(matgo);
    }
}

//유저의 상태값을 가져온다.
USER_STATE CMultiUser::getUserState()
{
    return userState;
}

ROOM_STATE CMultiUser::getRoomState()
{
    return roomState;
}

//현재 유저의 룸의 아이디를 가져온다
int CMultiUser::getRoomID()
{
    return JoinInfo.roomid();
}

//유저의 usn을 가져온다.
int CMultiUser::getGameID()
{
    int nResult = ERROR_VALUE;
    
    GameUserInfo* pGame = JoinInfo.mutable_gameuserinfo();
    
    GameInfo* pInfo = pGame->mutable_gameinfo();
    
    nResult = pInfo->gameid();
    
    return nResult;
}

//true 자기 , false 남
void CMultiUser::getGameUserInfo(GameUserInfo& info, bool bMe)
{
    GameUserInfo* pInfo;
    
    if(bMe)
    {
        pInfo = JoinInfo.mutable_gameuserinfo();
    }
    else
    {
       pInfo = YouJoinInfo.mutable_gameuserinfo();
    }
    
    info.CopyFrom(*pInfo);
}
//로직 커맨드 포인터를 가져옴
CLogicMultiCommand* CMultiUser::getLogicCommand()
{
    return logicCommand;
}

//매칭된 유저의 게임 아이디
int CMultiUser::getMatchUserGameID()
{
    GameUserInfo* pGame = YouJoinInfo.mutable_gameuserinfo();

    GameInfo* pInfo = pGame->mutable_gameinfo();

    return pInfo->gameid();
}

//유저의 상태값을 가져온다.
void CMultiUser::setUserState(USER_STATE nState)
{
    userState = nState;
}

void CMultiUser::setRoomState(ROOM_STATE nState)
{
    roomState = nState;
}

//유저 인덱스 셋팅
void CMultiUser::setUserIndex(int ui)
{
    GameUserInfo* pGame = JoinInfo.mutable_gameuserinfo();
    
    GameInfo* pInfo = pGame->mutable_gameinfo();
    
    pInfo->set_gameindex(ui);
}

//유저의 게임 인덱스를 가져온다.

int CMultiUser::getGameIndex()
{
    GameUserInfo* pGame = JoinInfo.mutable_gameuserinfo();
    
    GameInfo* pInfo = pGame->mutable_gameinfo();
    
    return pInfo->gameindex();
}

void CMultiUser::setGameIndex(int iUI)
{
    GameUserInfo* pGame = JoinInfo.mutable_gameuserinfo();
    
    GameInfo* pInfo = pGame->mutable_gameinfo();
    
    pInfo->set_gameindex(iUI);
}

//로직 커맨드를 셋팅한다.
void CMultiUser::setLogicCommand(CLogicMultiCommand* pLogicCommand)
{
    logicCommand = pLogicCommand;
    
    if(logicCommand != NULL)
    {
        GameUserInfo* pGame = JoinInfo.mutable_gameuserinfo();

        GameInfo* pInfo = pGame->mutable_gameinfo();
        
        logicCommand->SetGameType(MULTI_GAME);
        logicCommand->setUserAdd(getGameID(), pInfo->gameindex());
        logicCommand->setRoomID(JoinInfo.roomid());
        logicCommand->setPointMoney(getPointMoney(JoinInfo.categoryid()));
        logicCommand->setCategoryID(JoinInfo.categoryid());
    }
}

//로직 커맨드중 상대방을 셋팅한다.
void CMultiUser::setLogicUser()
{
    if(logicCommand != NULL)
    {
        GameUserInfo* pGame = YouJoinInfo.mutable_gameuserinfo();
        
        GameInfo* pInfo = pGame->mutable_gameinfo();
        
        pInfo->set_gameindex(0);
        
        logicCommand->SetGameType(MULTI_GAME);
        logicCommand->setUserAdd(pInfo->gameid(), pInfo->gameindex());
        logicCommand->setRoomID(YouJoinInfo.roomid());
        logicCommand->setPointMoney(getPointMoney(YouJoinInfo.categoryid()));
        logicCommand->setCategoryID(YouJoinInfo.categoryid());
    }
}
//상대방의 게임 usn을 셋팅한다.
void CMultiUser::setMatchUserGameId(int gameId)
{
    GameUserInfo* pGame = YouJoinInfo.mutable_gameuserinfo();
    GameInfo* pInfo = pGame->mutable_gameinfo();
    pInfo->set_gameid(gameId);
}

void CMultiUser::setMatchUser(GReqGameEnter& matchUser)     //매치 유저
{
    
    YouJoinInfo.CopyFrom(matchUser);

}

//조인룸을 보낸다.
void CMultiUser::sendJoinRoom(GAnsProtocol& matgo)
{
    //조인 메시지를 만든다.
    makeGameJoinRoom(matgo);

    //패캣을 만든다.
    makePacket(::GAnsProtocol_Type_GANSGAMEENTER, matgo);
    
    //모둥게 보낸다.
    
    
//    user_ptr pUser = mulManager->getUser(getMatchUserGameID());
//    
//    pUser->sendPacket(matgo);

    //패킷을 상대에게 보낸다.
//    sendYouPacket(matgo, YouJoinInfo.gameid());
}

//타이머 셋팅
void CMultiUser::setTimer(TIMER_TYPE nType)
{
    if(logicCommand != NULL)
    {
        logicCommand->setTimer(nType);
    }
}

//인덱스를 변경한다.
void CMultiUser::changeIndex(int index)
{
    logicCommand->changeIndex(index);
}


void CMultiUser::setKickType(GAnsGameLeave_KICK_TYPE nType)
{
    kickType = nType;
}

GAnsGameLeave_KICK_TYPE CMultiUser::getKickType()
{
    return kickType;
}



