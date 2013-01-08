
#ifndef UserServer___W2U_ONLINE_USERS__ 
#define UserServer___W2U_ONLINE_USERS__

#ifndef UserServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_UserServer(UserServer);
jxDECL_UserServer(W2U_ONLINE_USERS);
#endif //UserServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nUserServer
{
	/*[[ UserServer�� ���������������� ���� ]]*/
	const int pk_W2U_ONLINE_USERS = /*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+4;
	/* player_id_t pid[-1];*/
	/* wstring id[-1];*/
	/* serverid_t town[-1];*/
	/*[[ ������ Ÿ��� ]]*/
	
	struct S_W2U_ONLINE_USERS;
	bool READ_W2U_ONLINE_USERS(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_W2U_ONLINE_USERS &param);
	struct S_W2U_ONLINE_USERS
	{
		std::vector<player_id_t> pid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_UserServer
		player_id_t* get_pid(int i){ return &pid[i];}
		void 	set_pid(int i, player_id_t* v){ pid[i] = *v;}
		void insert_pid(player_id_t* v){ pid.push_back(*v);}
		void clear_pid(){ pid.clear();}
		size_t size_pid(){ return pid.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_UserServer

		std::vector<wstring> id;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_UserServer
		wstring* get_id(int i){ return &id[i];}
		void 	set_id(int i, wstring* v){ id[i] = *v;}
		void insert_id(wstring* v){ id.push_back(*v);}
		void clear_id(){ id.clear();}
		size_t size_id(){ return id.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_UserServer

		/*[[ ������ Ÿ��� ]]*/
		std::vector<serverid_t> town;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_UserServer
		serverid_t* get_town(int i){ return &town[i];}
		void 	set_town(int i, serverid_t* v){ town[i] = *v;}
		void insert_town(serverid_t* v){ town.push_back(*v);}
		void clear_town(){ town.clear();}
		size_t size_town(){ return town.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_UserServer


		#ifndef jNOT_USE_DebugPrint_UserServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< W2U_ONLINE_USERS > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("pid"),pid);
			jDebugPrint(_T("id"),id);
			jDebugPrint(_T("town"),town);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_W2U_ONLINE_USERS(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_UserServer
	
	inline bool READ_W2U_ONLINE_USERS(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_W2U_ONLINE_USERS &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nMech::uint16 tempSizepid;
		nStream::Read(st,tempSizepid);
		param.pid.resize(tempSizepid);
		for(nMech::uint16 iTemppid=0;iTemppid<tempSizepid; ++iTemppid){
		nStream::Read(st,param.pid[iTemppid]);
		}
		nMech::uint16 tempSizeid;
		nStream::Read(st,tempSizeid);
		param.id.resize(tempSizeid);
		for(nMech::uint16 iTempid=0;iTempid<tempSizeid; ++iTempid){
		nStream::Read(st,param.id[iTempid]);
		}
		nMech::uint16 tempSizetown;
		nStream::Read(st,tempSizetown);
		param.town.resize(tempSizetown);
		for(nMech::uint16 iTemptown=0;iTemptown<tempSizetown; ++iTemptown){
		nStream::Read(st,param.town[iTemptown]);
		}
		/*	[[ ������ Ÿ��� ]]*/
		
		#ifndef jNOT_USE_DebugPrint_UserServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("W2U_ONLINE_USERS : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_UserServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_UserServer
	inline jPacket_Base WRITE_W2U_ONLINE_USERS(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_W2U_ONLINE_USERS &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizepid= (nMech::uint16)param.pid.size();
			nStream::Write(st,tempSizepid);
			for(nMech::uint16 iTemppid=0;iTemppid<tempSizepid; ++iTemppid){
			nStream::Write(st,param.pid[iTemppid]);
			}
			nMech::uint16 tempSizeid= (nMech::uint16)param.id.size();
			nStream::Write(st,tempSizeid);
			for(nMech::uint16 iTempid=0;iTempid<tempSizeid; ++iTempid){
			nStream::Write(st,param.id[iTempid]);
			}
			nMech::uint16 tempSizetown= (nMech::uint16)param.town.size();
			nStream::Write(st,tempSizetown);
			for(nMech::uint16 iTemptown=0;iTemptown<tempSizetown; ++iTemptown){
			nStream::Write(st,param.town[iTemptown]);
			}
			/*[[ ������ Ÿ��� ]]*/
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_W2U_ONLINE_USERS;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" W2U_ONLINE_USERS :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" W2U_ONLINE_USERS :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_W2U_ONLINE_USERS(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const std::vector<player_id_t> &_pid, const std::vector<wstring> &_id, const std::vector<serverid_t> &_town)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizepid = (nMech::uint16)_pid.size();
			nStream::Write(st,tempSizepid);
			for(nMech::uint16 iTemppid=0;iTemppid<tempSizepid; ++iTemppid){
			nStream::Write(st,_pid[iTemppid]);
			}
			nMech::uint16 tempSizeid = (nMech::uint16)_id.size();
			nStream::Write(st,tempSizeid);
			for(nMech::uint16 iTempid=0;iTempid<tempSizeid; ++iTempid){
			nStream::Write(st,_id[iTempid]);
			}
			nMech::uint16 tempSizetown = (nMech::uint16)_town.size();
			nStream::Write(st,tempSizetown);
			for(nMech::uint16 iTemptown=0;iTemptown<tempSizetown; ++iTemptown){
			nStream::Write(st,_town[iTemptown]);
			}
			/*[[ ������ Ÿ��� ]]*/
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_W2U_ONLINE_USERS;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" W2U_ONLINE_USERS :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" W2U_ONLINE_USERS :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_UserServer

}/*nUserServer */ }/* nNET*/ } //nMech
#endif //UserServer___W2U_ONLINE_USERS__