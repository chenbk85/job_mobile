

void MOB_CONN_CLASS::send_me(GAnsProtocol& msg)
{
	MOB_NetPacketBuffer & wBuf = m_pMOB_IConnection->m_writeBuff;
	int32 nSize = msg.ByteSize();
	wBuf.header.data_length = msg.ByteSize()+sizeof(int);
	jRETURN(wBuf.header.data_length<nMOB::BUFFER_SIZE);
	memcpy(wBuf.pBody, &nSize, sizeof(int32));
	assert(sizeof(wBuf.header)==sizeof(int32));
	google::protobuf::io::ArrayOutputStream os(wBuf.pBody+sizeof(int), msg.ByteSize());
	msg.SerializeToZeroCopyStream(&os);
	m_pMOB_IConnection->WritePacket(&wBuf);
}
void MOB_CONN_CLASS::send_to(GAnsProtocol& msg, int gameID)
{
	MOB_CONN_CLASS* pCon = GetParent()->Connection_Find(gameID);
	jRETURN(pCon);
	pCon->send_me(msg);
}
#define jLAMDA_send_to_all_(X,Z)  X(ESendAllType ,eSkipMe) X(GAnsProtocol&, msg) Z(pp_game_id_t,skip_gid)
jLAMDA_for_each(send_to_all_,MOB_IConnection*)
{
	MOB_CONN_CLASS*pCon=(MOB_CONN_CLASS*)it->m_pPlugin;
	if(eSkipMe == nMOB::eSAT_SkipMe)
		if( it->m_pPlugin->m_gid == skip_gid ) 
			return;
	pCon->send_me(msg);
}
jLAMDA_end();

void MOB_CONN_CLASS::send_to_all(GAnsProtocol& msg,ESendAllType eSkipMe)
{

	boost::function<void (MOB_IConnection*)> func = send_to_all_(eSkipMe,msg,m_gid);
	GetParent()->m_pMOB_INetIOModel->for_each(func);
}
#define jLAMDA_send_room_user_all(X,Z)  X(ESendAllType ,eSkipMe) X(pp_game_id_t,skip_gid) Z(GAnsProtocol& , msg)
jLAMDA_for_each(send_room_user_all,MOB_CONN_CLASS*)
{
	if(eSkipMe == nMOB::eSAT_SkipMe)
		if( it->m_gid == skip_gid) 
			return;
	it->send_me(msg);
}
jLAMDA_end();


void MOB_CONN_CLASS::send_to_room_user(GAnsProtocol& msg,ESendAllType eSkipMe)
{
	boost::function<void(MOB_CONN_CLASS*)> func = send_room_user_all(eSkipMe,m_gid, msg);
	MOB_ROOM(this,MOB_ROOM_CLASS,pRoom);
	pRoom->for_each(func);
}
bool MOB_CONN_CLASS::MOB_OnReadPacket( char* pBody, int iLengthBody )
{
	google::protobuf::io::ArrayInputStream is(pBody, iLengthBody);
	GReqProtocol recvMsg;
	recvMsg.ParseFromZeroCopyStream(&is);
	switch(recvMsg.type())
	{
	case GReqProtocol_Type_GLREQGAMEPROTOCOL:
		{
			GLReqGameProtocol recv;
			recv.ParseFromString(recvMsg.reqgameprotocol());
			OnReadPacket_GLReqGameProtocol(&recv);
			break;
		}
	case GReqProtocol_Type_GREQGAMEENTER:
		{
			GReqGameEnter* p= recvMsg.mutable_reqgameenter();
			jBREAK(p);
			OnReadPacket_GReqGameEnter(p);
			break;
		}
	case GReqProtocol_Type_GREQGAMELEAVE:
		{
			GReqGameLeave* p = recvMsg.mutable_reqgameleave();
			jBREAK(p);
			OnReadPacket_GReqGameLeave(p);
			break;
		}
	default:
		{
			OnReadPacket_Unkown(&recvMsg);
			jWARN(_T("recvMsg.type() : invalied packet"));
			return false;/* return false이면 MOB_ OnDisconnect()가 호출되고 접속해제됨.*/
		}
	}
	return true;
}

#define __call_GLReqGameProtocol_Type(PACKET_NAME,HELP) \
case GLReqGameProtocol_Type_##PACKET_NAME:\
	void On_##PACKET_NAME(MOB_CONN_CLASS* pCon,s_##PACKET_NAME* p);\
	On_##PACKET_NAME(this,p->mutable_m_##PACKET_NAME());break;\


void MOB_CONN_CLASS::OnReadPacket_GLReqGameProtocol( GLReqGameProtocol* p )
{
	jRETURN(p);
	switch (p->type()) 
	{
		MOB_MESSAGE_LIST(__call_GLReqGameProtocol_Type);
	}
}





static MOB_ROOM_CLASS s_MOB_ROOM_CLASS[MOB_MAX_ROOM_COUNT];
jONCE_RUN(MOB_ROOM_CLASS) {for( int i=0; i< MOB_MAX_ROOM_COUNT; ++i)s_MOB_ROOM_CLASS[i].m_isUse=false;}

MOB_ROOM_CLASS* MOB_IOMODEL_CLASS::Room_Create(ug_room_id_t rid)
{
	jRETURN_ret(0,rid >=0);
	jRETURN_ret(0,rid <MOB_MAX_ROOM_COUNT);
	MOB_ROOM_CLASS* pRoom = s_MOB_ROOM_CLASS + rid;
	jRETURN_ret(0, !pRoom->m_isUse);
	pRoom->m_isUse=true;
	pRoom->m_UserList.clear();
	pRoom->MOB_OnCreate();
	return pRoom;
}

void MOB_IOMODEL_CLASS::Room_Delete(MOB_ROOM_CLASS* pRoom)
{
	jRETURN(pRoom);
	pRoom->MOB_OnDelete();
	pRoom->m_isUse=false;
	pRoom->m_UserList.clear();
}
 
MOB_ROOM_CLASS*  MOB_IOMODEL_CLASS::Room_Find(ug_room_id_t rid)
{
	jRETURN_ret(0,rid >= 0);
	jRETURN_ret(0,rid <MOB_MAX_ROOM_COUNT);
	MOB_ROOM_CLASS* pRoom = s_MOB_ROOM_CLASS + rid;
	if(pRoom->m_isUse) return pRoom;
	return 0;
}

void				MOB_ROOM_CLASS::for_each(boost::function<void(MOB_ROOM_CLASS::RoomUser_t*)>& func)
{
	jFOR_EACH(m_UserList,func);
}

MOB_ROOM_CLASS::RoomUser_t*	MOB_ROOM_CLASS::find_if(boost::function<bool(MOB_ROOM_CLASS::RoomUser_t*)>& func)
{
	m_UserList_it it = jFIND_IF(m_UserList,func);
	if(it == m_UserList.end()) return 0;
	return (*it);
}

void MOB_ROOM_CLASS::send_to(GAnsProtocol& msg,nMOB::pp_game_id_t gid)
{
	for( size_t i = 0; i< m_UserList.size(); ++i)
	{
		MOB_CONN_CLASS* pCon = m_UserList[i];
		if(!pCon) continue;
		if(pCon->m_gid != gid) continue;
		pCon->send_me(msg);
	}
}


void MOB_ROOM_CLASS::send_to_all(GAnsProtocol& msg,ESendAllType eSkipMe,nMOB::pp_game_id_t gid)
{
	boost::function<void(MOB_CONN_CLASS*)> func = send_room_user_all(eSkipMe,gid, msg);
	this->for_each(func);
}
