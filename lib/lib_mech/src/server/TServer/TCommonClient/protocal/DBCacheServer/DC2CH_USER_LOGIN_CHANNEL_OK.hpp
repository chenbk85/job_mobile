
#ifndef DBCacheServer___DC2CH_USER_LOGIN_CHANNEL_OK__ 
#define DBCacheServer___DC2CH_USER_LOGIN_CHANNEL_OK__

#ifndef DBCacheServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DBCacheServer(DBCacheServer);
jxDECL_DBCacheServer(DC2CH_USER_LOGIN_CHANNEL_OK);
#endif //DBCacheServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nDBCacheServer
{
	/*[[ iMAX_USER_TOWN	= 20 ]]*/
	const int pk_DC2CH_USER_LOGIN_CHANNEL_OK = /*nMech::nNET::EProtocal_jINet_OGS_END+*/6000+10;
	/* player_id_t pid;*/
	/* nAQ::Use_User user;*/
	/* nAQ::Use_Town town[-1];*/
	
	struct S_DC2CH_USER_LOGIN_CHANNEL_OK;
	bool READ_DC2CH_USER_LOGIN_CHANNEL_OK(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DC2CH_USER_LOGIN_CHANNEL_OK &param);
	struct S_DC2CH_USER_LOGIN_CHANNEL_OK
	{
		player_id_t pid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer

		nAQ::Use_User user;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer

		std::vector<nAQ::Use_Town> town;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer
		nAQ::Use_Town* get_town(int i){ return &town[i];}
		void 	set_town(int i, nAQ::Use_Town* v){ town[i] = *v;}
		void insert_town(nAQ::Use_Town* v){ town.push_back(*v);}
		void clear_town(){ town.clear();}
		size_t size_town(){ return town.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer


		#ifndef jNOT_USE_DebugPrint_DBCacheServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DC2CH_USER_LOGIN_CHANNEL_OK > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("pid"),pid);
			jDebugPrint(_T("user"),user);
			jDebugPrint(_T("town"),town);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DC2CH_USER_LOGIN_CHANNEL_OK(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_DBCacheServer
	
	inline bool READ_DC2CH_USER_LOGIN_CHANNEL_OK(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DC2CH_USER_LOGIN_CHANNEL_OK &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.pid);
		nStream::Read(st,param.user);
		nMech::uint16 tempSizetown;
		nStream::Read(st,tempSizetown);
		param.town.resize(tempSizetown);
		for(nMech::uint16 iTemptown=0;iTemptown<tempSizetown; ++iTemptown){
		nStream::Read(st,param.town[iTemptown]);
		}
		
		#ifndef jNOT_USE_DebugPrint_DBCacheServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DC2CH_USER_LOGIN_CHANNEL_OK : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_DBCacheServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_DBCacheServer
	inline jPacket_Base WRITE_DC2CH_USER_LOGIN_CHANNEL_OK(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DC2CH_USER_LOGIN_CHANNEL_OK &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.pid);
			nStream::Write(st,param.user);
			nMech::uint16 tempSizetown= (nMech::uint16)param.town.size();
			nStream::Write(st,tempSizetown);
			for(nMech::uint16 iTemptown=0;iTemptown<tempSizetown; ++iTemptown){
			nStream::Write(st,param.town[iTemptown]);
			}
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DC2CH_USER_LOGIN_CHANNEL_OK;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC2CH_USER_LOGIN_CHANNEL_OK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC2CH_USER_LOGIN_CHANNEL_OK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DC2CH_USER_LOGIN_CHANNEL_OK(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const player_id_t &_pid, const nAQ::Use_User &_user, const std::vector<nAQ::Use_Town> &_town)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_pid);
			nStream::Write(st,_user);
			nMech::uint16 tempSizetown = (nMech::uint16)_town.size();
			nStream::Write(st,tempSizetown);
			for(nMech::uint16 iTemptown=0;iTemptown<tempSizetown; ++iTemptown){
			nStream::Write(st,_town[iTemptown]);
			}
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DC2CH_USER_LOGIN_CHANNEL_OK;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC2CH_USER_LOGIN_CHANNEL_OK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC2CH_USER_LOGIN_CHANNEL_OK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_DBCacheServer

}/*nDBCacheServer */ }/* nNET*/ } //nMech
#endif //DBCacheServer___DC2CH_USER_LOGIN_CHANNEL_OK__