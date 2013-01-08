
#ifndef CommandServer___CD_SERVER_OFFLINE__ 
#define CommandServer___CD_SERVER_OFFLINE__

#ifndef CommandServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_CommandServer(CommandServer);
jxDECL_CommandServer(CD_SERVER_OFFLINE);
#endif //CommandServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nCommandServer
{
	const int pk_CD_SERVER_OFFLINE = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1500+6;
	/* serverid_t sid;*/
	
	struct S_CD_SERVER_OFFLINE;
	bool READ_CD_SERVER_OFFLINE(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_CD_SERVER_OFFLINE &param);
	struct S_CD_SERVER_OFFLINE
	{
		serverid_t sid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_CommandServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_CommandServer


		#ifndef jNOT_USE_DebugPrint_CommandServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< CD_SERVER_OFFLINE > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("sid"),sid);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_CD_SERVER_OFFLINE(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_CommandServer
	
	inline bool READ_CD_SERVER_OFFLINE(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_CD_SERVER_OFFLINE &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.sid);
		
		#ifndef jNOT_USE_DebugPrint_CommandServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("CD_SERVER_OFFLINE : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_CommandServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_CommandServer
	inline jPacket_Base WRITE_CD_SERVER_OFFLINE(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_CD_SERVER_OFFLINE &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.sid);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_CD_SERVER_OFFLINE;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" CD_SERVER_OFFLINE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" CD_SERVER_OFFLINE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_CD_SERVER_OFFLINE(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const serverid_t &_sid)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_sid);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_CD_SERVER_OFFLINE;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" CD_SERVER_OFFLINE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" CD_SERVER_OFFLINE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_CommandServer

}/*nCommandServer */ }/* nNET*/ } //nMech
#endif //CommandServer___CD_SERVER_OFFLINE__