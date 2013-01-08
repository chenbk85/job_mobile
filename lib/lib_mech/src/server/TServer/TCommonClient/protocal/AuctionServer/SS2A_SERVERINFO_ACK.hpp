
#ifndef AuctionServer___SS2A_SERVERINFO_ACK__ 
#define AuctionServer___SS2A_SERVERINFO_ACK__

#ifndef AuctionServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_AuctionServer(AuctionServer);
jxDECL_AuctionServer(SS2A_SERVERINFO_ACK);
#endif //AuctionServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nAuctionServer
{
	const int pk_SS2A_SERVERINFO_ACK = /*nMech::nNET::EProtocal_jINet_OGS_END+*/7300+4;
	/* jServerInfo si;*/
	
	struct S_SS2A_SERVERINFO_ACK;
	bool READ_SS2A_SERVERINFO_ACK(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_SS2A_SERVERINFO_ACK &param);
	struct S_SS2A_SERVERINFO_ACK
	{
		jServerInfo si;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_AuctionServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_AuctionServer


		#ifndef jNOT_USE_DebugPrint_AuctionServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< SS2A_SERVERINFO_ACK > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("si"),si);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_SS2A_SERVERINFO_ACK(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_AuctionServer
	
	inline bool READ_SS2A_SERVERINFO_ACK(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_SS2A_SERVERINFO_ACK &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.si);
		
		#ifndef jNOT_USE_DebugPrint_AuctionServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("SS2A_SERVERINFO_ACK : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_AuctionServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_AuctionServer
	inline jPacket_Base WRITE_SS2A_SERVERINFO_ACK(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_SS2A_SERVERINFO_ACK &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.si);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_SS2A_SERVERINFO_ACK;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" SS2A_SERVERINFO_ACK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" SS2A_SERVERINFO_ACK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_SS2A_SERVERINFO_ACK(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const jServerInfo &_si)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_si);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_SS2A_SERVERINFO_ACK;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" SS2A_SERVERINFO_ACK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" SS2A_SERVERINFO_ACK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_AuctionServer

}/*nAuctionServer */ }/* nNET*/ } //nMech
#endif //AuctionServer___SS2A_SERVERINFO_ACK__