
#ifndef LoginServer___L2X_CHANNEL_SELECT_RESULT__ 
#define LoginServer___L2X_CHANNEL_SELECT_RESULT__

#ifndef LoginServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_LoginServer(LoginServer);
jxDECL_LoginServer(L2X_CHANNEL_SELECT_RESULT);
#endif //LoginServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nLoginServer
{
	const int pk_L2X_CHANNEL_SELECT_RESULT = /*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+15;
	/* jError e;*/
	/* aname32_t ip;*/
	/* uint16 port;*/
	/* player_id_t pid;*/
	
	struct S_L2X_CHANNEL_SELECT_RESULT;
	bool READ_L2X_CHANNEL_SELECT_RESULT(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_L2X_CHANNEL_SELECT_RESULT &param);
	struct S_L2X_CHANNEL_SELECT_RESULT
	{
		jError e;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_LoginServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_LoginServer

		aname32_t ip;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_LoginServer
					void set_ip(tcstr sz){ja_strncpy(ip,nUNI::scb1024_t(sz).getA(), 32);	ip[32-1]=0;}
					tcstr get_ip(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(ip).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_LoginServer

		uint16 port;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_LoginServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_LoginServer

		player_id_t pid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_LoginServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_LoginServer


		#ifndef jNOT_USE_DebugPrint_LoginServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< L2X_CHANNEL_SELECT_RESULT > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("e"),e);
			jDebugPrint(_T("ip"),ip);
			jDebugPrint(_T("port"),port);
			jDebugPrint(_T("pid"),pid);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_L2X_CHANNEL_SELECT_RESULT(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_LoginServer
	
	inline bool READ_L2X_CHANNEL_SELECT_RESULT(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_L2X_CHANNEL_SELECT_RESULT &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.e);
		nStream::Read(st,param.ip, 32);
		nStream::Read(st,param.port);
		nStream::Read(st,param.pid);
		
		#ifndef jNOT_USE_DebugPrint_LoginServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("L2X_CHANNEL_SELECT_RESULT : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_LoginServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_LoginServer
	inline jPacket_Base WRITE_L2X_CHANNEL_SELECT_RESULT(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_L2X_CHANNEL_SELECT_RESULT &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.e);
			nStream::Write(st,param.ip);
			nStream::Write(st,param.port);
			nStream::Write(st,param.pid);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_L2X_CHANNEL_SELECT_RESULT;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" L2X_CHANNEL_SELECT_RESULT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" L2X_CHANNEL_SELECT_RESULT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_L2X_CHANNEL_SELECT_RESULT(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const jError &_e,  acstr _ip, const uint16 &_port, const player_id_t &_pid)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_e);
			nStream::Write(st,_ip);
			nStream::Write(st,_port);
			nStream::Write(st,_pid);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_L2X_CHANNEL_SELECT_RESULT;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" L2X_CHANNEL_SELECT_RESULT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" L2X_CHANNEL_SELECT_RESULT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_LoginServer

}/*nLoginServer */ }/* nNET*/ } //nMech
#endif //LoginServer___L2X_CHANNEL_SELECT_RESULT__