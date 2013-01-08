
#ifndef GameServer___G_ECHO__ 
#define GameServer___G_ECHO__

#ifndef GameServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_GameServer(GameServer);
jxDECL_GameServer(G_ECHO);
#endif //GameServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nGameServer
{
	const int pk_G_ECHO = /*nMech::nNET::EProtocal_jINet_OGS_END+*/3000+1;
	/* tname256_t msg;*/
	/* uint8 type;*/
	
	struct S_G_ECHO;
	bool READ_G_ECHO(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_G_ECHO &param);
	struct S_G_ECHO
	{
		tname256_t msg;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_GameServer
					void set_msg(tcstr sz){jt_strncpy(msg,nUNI::scb1024_t(sz).getT(), 256);	msg[256-1]=0;}
					tcstr get_msg(fname_t _buf){jt_strncpy(_buf, nUNI::scb256_t(msg).getT() , 256);_buf[256-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_GameServer

		uint8 type;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_GameServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_GameServer


		#ifndef jNOT_USE_DebugPrint_GameServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< G_ECHO > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("msg"),msg);
			jDebugPrint(_T("type"),type);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_G_ECHO(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_GameServer
	
	inline bool READ_G_ECHO(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_G_ECHO &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.msg, 256);
		nStream::Read(st,param.type);
		
		#ifndef jNOT_USE_DebugPrint_GameServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("G_ECHO : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_GameServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_GameServer
	inline jPacket_Base WRITE_G_ECHO(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_G_ECHO &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.msg);
			nStream::Write(st,param.type);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_G_ECHO;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" G_ECHO :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" G_ECHO :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_G_ECHO(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  tcstr _msg, const uint8 &_type)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_msg);
			nStream::Write(st,_type);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_G_ECHO;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" G_ECHO :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" G_ECHO :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_GameServer

}/*nGameServer */ }/* nNET*/ } //nMech
#endif //GameServer___G_ECHO__