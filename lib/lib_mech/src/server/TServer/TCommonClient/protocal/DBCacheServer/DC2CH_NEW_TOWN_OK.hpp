
#ifndef DBCacheServer___DC2CH_NEW_TOWN_OK__ 
#define DBCacheServer___DC2CH_NEW_TOWN_OK__

#ifndef DBCacheServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DBCacheServer(DBCacheServer);
jxDECL_DBCacheServer(DC2CH_NEW_TOWN_OK);
#endif //DBCacheServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nDBCacheServer
{
	const int pk_DC2CH_NEW_TOWN_OK = /*nMech::nNET::EProtocal_jINet_OGS_END+*/6000+1;
	/* player_id_t pid;*/
	/* channelid_t index;*/
	/* Use_Town town;*/
	/* bool isCapital;*/
	
	struct S_DC2CH_NEW_TOWN_OK;
	bool READ_DC2CH_NEW_TOWN_OK(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DC2CH_NEW_TOWN_OK &param);
	struct S_DC2CH_NEW_TOWN_OK
	{
		player_id_t pid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer

		channelid_t index;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer

		Use_Town town;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer

		bool isCapital;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer


		#ifndef jNOT_USE_DebugPrint_DBCacheServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DC2CH_NEW_TOWN_OK > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("pid"),pid);
			jDebugPrint(_T("index"),index);
			jDebugPrint(_T("town"),town);
			jDebugPrint(_T("isCapital"),isCapital);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DC2CH_NEW_TOWN_OK(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_DBCacheServer
	
	inline bool READ_DC2CH_NEW_TOWN_OK(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DC2CH_NEW_TOWN_OK &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.pid);
		nStream::Read(st,param.index);
		nStream::Read(st,param.town);
		nStream::Read(st,param.isCapital);
		
		#ifndef jNOT_USE_DebugPrint_DBCacheServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DC2CH_NEW_TOWN_OK : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_DBCacheServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_DBCacheServer
	inline jPacket_Base WRITE_DC2CH_NEW_TOWN_OK(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DC2CH_NEW_TOWN_OK &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.pid);
			nStream::Write(st,param.index);
			nStream::Write(st,param.town);
			nStream::Write(st,param.isCapital);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DC2CH_NEW_TOWN_OK;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC2CH_NEW_TOWN_OK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC2CH_NEW_TOWN_OK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DC2CH_NEW_TOWN_OK(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const player_id_t &_pid, const channelid_t &_index, const Use_Town &_town, const bool &_isCapital)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_pid);
			nStream::Write(st,_index);
			nStream::Write(st,_town);
			nStream::Write(st,_isCapital);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DC2CH_NEW_TOWN_OK;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC2CH_NEW_TOWN_OK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC2CH_NEW_TOWN_OK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_DBCacheServer

}/*nDBCacheServer */ }/* nNET*/ } //nMech
#endif //DBCacheServer___DC2CH_NEW_TOWN_OK__