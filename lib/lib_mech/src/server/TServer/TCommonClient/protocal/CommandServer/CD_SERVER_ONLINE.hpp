
#ifndef CommandServer___CD_SERVER_ONLINE__ 
#define CommandServer___CD_SERVER_ONLINE__

#ifndef CommandServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_CommandServer(CommandServer);
jxDECL_CommandServer(CD_SERVER_ONLINE);
#endif //CommandServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nCommandServer
{
	const int pk_CD_SERVER_ONLINE = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1500+5;
	/* jServerInfo s;*/
	
	struct S_CD_SERVER_ONLINE;
	bool READ_CD_SERVER_ONLINE(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_CD_SERVER_ONLINE &param);
	struct S_CD_SERVER_ONLINE
	{
		jServerInfo s;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_CommandServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_CommandServer


		#ifndef jNOT_USE_DebugPrint_CommandServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< CD_SERVER_ONLINE > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("s"),s);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_CD_SERVER_ONLINE(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_CommandServer
	
	inline bool READ_CD_SERVER_ONLINE(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_CD_SERVER_ONLINE &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.s);
		
		#ifndef jNOT_USE_DebugPrint_CommandServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("CD_SERVER_ONLINE : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_CommandServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_CommandServer
	inline jPacket_Base WRITE_CD_SERVER_ONLINE(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_CD_SERVER_ONLINE &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.s);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_CD_SERVER_ONLINE;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" CD_SERVER_ONLINE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" CD_SERVER_ONLINE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_CD_SERVER_ONLINE(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const jServerInfo &_s)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_s);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_CD_SERVER_ONLINE;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" CD_SERVER_ONLINE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" CD_SERVER_ONLINE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_CommandServer

}/*nCommandServer */ }/* nNET*/ } //nMech
#endif //CommandServer___CD_SERVER_ONLINE__