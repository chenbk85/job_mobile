
#ifndef WorldServer___DC2W_USER_LOGIN_CHANNEL_FAIL__ 
#define WorldServer___DC2W_USER_LOGIN_CHANNEL_FAIL__

#ifndef WorldServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_WorldServer(WorldServer);
jxDECL_WorldServer(DC2W_USER_LOGIN_CHANNEL_FAIL);
#endif //WorldServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nWorldServer
{
	const int pk_DC2W_USER_LOGIN_CHANNEL_FAIL = /*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+17;
	/* player_id_t pid;*/
	/* jError e;*/
	
	struct S_DC2W_USER_LOGIN_CHANNEL_FAIL;
	bool READ_DC2W_USER_LOGIN_CHANNEL_FAIL(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DC2W_USER_LOGIN_CHANNEL_FAIL &param);
	struct S_DC2W_USER_LOGIN_CHANNEL_FAIL
	{
		player_id_t pid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_WorldServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_WorldServer

		jError e;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_WorldServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_WorldServer


		#ifndef jNOT_USE_DebugPrint_WorldServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DC2W_USER_LOGIN_CHANNEL_FAIL > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("pid"),pid);
			jDebugPrint(_T("e"),e);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DC2W_USER_LOGIN_CHANNEL_FAIL(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_WorldServer
	
	inline bool READ_DC2W_USER_LOGIN_CHANNEL_FAIL(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DC2W_USER_LOGIN_CHANNEL_FAIL &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.pid);
		nStream::Read(st,param.e);
		
		#ifndef jNOT_USE_DebugPrint_WorldServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DC2W_USER_LOGIN_CHANNEL_FAIL : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_WorldServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_WorldServer
	inline jPacket_Base WRITE_DC2W_USER_LOGIN_CHANNEL_FAIL(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DC2W_USER_LOGIN_CHANNEL_FAIL &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.pid);
			nStream::Write(st,param.e);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DC2W_USER_LOGIN_CHANNEL_FAIL;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC2W_USER_LOGIN_CHANNEL_FAIL :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC2W_USER_LOGIN_CHANNEL_FAIL :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DC2W_USER_LOGIN_CHANNEL_FAIL(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const player_id_t &_pid, const jError &_e)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_pid);
			nStream::Write(st,_e);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DC2W_USER_LOGIN_CHANNEL_FAIL;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC2W_USER_LOGIN_CHANNEL_FAIL :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC2W_USER_LOGIN_CHANNEL_FAIL :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_WorldServer

}/*nWorldServer */ }/* nNET*/ } //nMech
#endif //WorldServer___DC2W_USER_LOGIN_CHANNEL_FAIL__