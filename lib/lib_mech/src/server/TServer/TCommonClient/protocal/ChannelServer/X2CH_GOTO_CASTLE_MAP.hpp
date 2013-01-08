
#ifndef ChannelServer___X2CH_GOTO_CASTLE_MAP__ 
#define ChannelServer___X2CH_GOTO_CASTLE_MAP__

#ifndef ChannelServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_ChannelServer(ChannelServer);
jxDECL_ChannelServer(X2CH_GOTO_CASTLE_MAP);
#endif //ChannelServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nChannelServer
{
	const int pk_X2CH_GOTO_CASTLE_MAP = /*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+15;
	/* uint8 channelNo;*/
	
	struct S_X2CH_GOTO_CASTLE_MAP;
	bool READ_X2CH_GOTO_CASTLE_MAP(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_X2CH_GOTO_CASTLE_MAP &param);
	struct S_X2CH_GOTO_CASTLE_MAP
	{
		uint8 channelNo;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer


		#ifndef jNOT_USE_DebugPrint_ChannelServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< X2CH_GOTO_CASTLE_MAP > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("channelNo"),channelNo);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_X2CH_GOTO_CASTLE_MAP(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_ChannelServer
	
	inline bool READ_X2CH_GOTO_CASTLE_MAP(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_X2CH_GOTO_CASTLE_MAP &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.channelNo);
		
		#ifndef jNOT_USE_DebugPrint_ChannelServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("X2CH_GOTO_CASTLE_MAP : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_ChannelServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_ChannelServer
	inline jPacket_Base WRITE_X2CH_GOTO_CASTLE_MAP(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_X2CH_GOTO_CASTLE_MAP &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.channelNo);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_X2CH_GOTO_CASTLE_MAP;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2CH_GOTO_CASTLE_MAP :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2CH_GOTO_CASTLE_MAP :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_X2CH_GOTO_CASTLE_MAP(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const uint8 &_channelNo)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_channelNo);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_X2CH_GOTO_CASTLE_MAP;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2CH_GOTO_CASTLE_MAP :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2CH_GOTO_CASTLE_MAP :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_ChannelServer

}/*nChannelServer */ }/* nNET*/ } //nMech
#endif //ChannelServer___X2CH_GOTO_CASTLE_MAP__