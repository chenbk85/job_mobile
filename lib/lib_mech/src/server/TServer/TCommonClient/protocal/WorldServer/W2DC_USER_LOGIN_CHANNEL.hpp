
#ifndef WorldServer___W2DC_USER_LOGIN_CHANNEL__ 
#define WorldServer___W2DC_USER_LOGIN_CHANNEL__

#ifndef WorldServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_WorldServer(WorldServer);
jxDECL_WorldServer(W2DC_USER_LOGIN_CHANNEL);
#endif //WorldServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nWorldServer
{
	const int pk_W2DC_USER_LOGIN_CHANNEL = /*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+16;
	/* player_id_t pid;*/
	/* wname64_t id;*/
	/* serverid_t town;*/
	
	struct S_W2DC_USER_LOGIN_CHANNEL;
	bool READ_W2DC_USER_LOGIN_CHANNEL(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_W2DC_USER_LOGIN_CHANNEL &param);
	struct S_W2DC_USER_LOGIN_CHANNEL
	{
		player_id_t pid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_WorldServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_WorldServer

		wname64_t id;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_WorldServer
					void set_id(tcstr sz){jw_strncpy(id,nUNI::scb1024_t(sz).getW(), 64);	id[64-1]=0;}
					tcstr get_id(fname_t _buf){jt_strncpy(_buf, nUNI::scb64_t(id).getT() , 64);_buf[64-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_WorldServer

		serverid_t town;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_WorldServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_WorldServer


		#ifndef jNOT_USE_DebugPrint_WorldServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< W2DC_USER_LOGIN_CHANNEL > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("pid"),pid);
			jDebugPrint(_T("id"),id);
			jDebugPrint(_T("town"),town);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_W2DC_USER_LOGIN_CHANNEL(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_WorldServer
	
	inline bool READ_W2DC_USER_LOGIN_CHANNEL(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_W2DC_USER_LOGIN_CHANNEL &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.pid);
		nStream::Read(st,param.id, 64);
		nStream::Read(st,param.town);
		
		#ifndef jNOT_USE_DebugPrint_WorldServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("W2DC_USER_LOGIN_CHANNEL : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_WorldServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_WorldServer
	inline jPacket_Base WRITE_W2DC_USER_LOGIN_CHANNEL(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_W2DC_USER_LOGIN_CHANNEL &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.pid);
			nStream::Write(st,param.id);
			nStream::Write(st,param.town);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_W2DC_USER_LOGIN_CHANNEL;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" W2DC_USER_LOGIN_CHANNEL :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" W2DC_USER_LOGIN_CHANNEL :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_W2DC_USER_LOGIN_CHANNEL(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const player_id_t &_pid,  wcstr _id, const serverid_t &_town)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_pid);
			nStream::Write(st,_id);
			nStream::Write(st,_town);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_W2DC_USER_LOGIN_CHANNEL;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" W2DC_USER_LOGIN_CHANNEL :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" W2DC_USER_LOGIN_CHANNEL :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_WorldServer

}/*nWorldServer */ }/* nNET*/ } //nMech
#endif //WorldServer___W2DC_USER_LOGIN_CHANNEL__