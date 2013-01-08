
#ifndef DBCacheServer___CH2DC_TOWN_DELETE__ 
#define DBCacheServer___CH2DC_TOWN_DELETE__

#ifndef DBCacheServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DBCacheServer(DBCacheServer);
jxDECL_DBCacheServer(CH2DC_TOWN_DELETE);
#endif //DBCacheServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nDBCacheServer
{
	const int pk_CH2DC_TOWN_DELETE = /*nMech::nNET::EProtocal_jINet_OGS_END+*/6000+2;
	/* player_id_t pid;*/
	/* channelid_t index;*/
	
	struct S_CH2DC_TOWN_DELETE;
	bool READ_CH2DC_TOWN_DELETE(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_CH2DC_TOWN_DELETE &param);
	struct S_CH2DC_TOWN_DELETE
	{
		player_id_t pid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer

		channelid_t index;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer


		#ifndef jNOT_USE_DebugPrint_DBCacheServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< CH2DC_TOWN_DELETE > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("pid"),pid);
			jDebugPrint(_T("index"),index);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_CH2DC_TOWN_DELETE(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_DBCacheServer
	
	inline bool READ_CH2DC_TOWN_DELETE(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_CH2DC_TOWN_DELETE &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.pid);
		nStream::Read(st,param.index);
		
		#ifndef jNOT_USE_DebugPrint_DBCacheServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("CH2DC_TOWN_DELETE : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_DBCacheServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_DBCacheServer
	inline jPacket_Base WRITE_CH2DC_TOWN_DELETE(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_CH2DC_TOWN_DELETE &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.pid);
			nStream::Write(st,param.index);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_CH2DC_TOWN_DELETE;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" CH2DC_TOWN_DELETE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" CH2DC_TOWN_DELETE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_CH2DC_TOWN_DELETE(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const player_id_t &_pid, const channelid_t &_index)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_pid);
			nStream::Write(st,_index);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_CH2DC_TOWN_DELETE;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" CH2DC_TOWN_DELETE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" CH2DC_TOWN_DELETE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_DBCacheServer

}/*nDBCacheServer */ }/* nNET*/ } //nMech
#endif //DBCacheServer___CH2DC_TOWN_DELETE__