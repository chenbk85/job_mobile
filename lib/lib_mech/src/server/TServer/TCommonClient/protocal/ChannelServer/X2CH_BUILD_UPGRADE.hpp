
#ifndef ChannelServer___X2CH_BUILD_UPGRADE__ 
#define ChannelServer___X2CH_BUILD_UPGRADE__

#ifndef ChannelServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_ChannelServer(ChannelServer);
jxDECL_ChannelServer(X2CH_BUILD_UPGRADE);
#endif //ChannelServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nChannelServer
{
	const int pk_X2CH_BUILD_UPGRADE = /*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+24;
	/* tname32_t build_slot;*/
	/* uint8 hero_id;*/
	
	struct S_X2CH_BUILD_UPGRADE;
	bool READ_X2CH_BUILD_UPGRADE(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_X2CH_BUILD_UPGRADE &param);
	struct S_X2CH_BUILD_UPGRADE
	{
		tname32_t build_slot;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer
					void set_build_slot(tcstr sz){jt_strncpy(build_slot,nUNI::scb1024_t(sz).getT(), 32);	build_slot[32-1]=0;}
					tcstr get_build_slot(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(build_slot).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer

		uint8 hero_id;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer


		#ifndef jNOT_USE_DebugPrint_ChannelServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< X2CH_BUILD_UPGRADE > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("build_slot"),build_slot);
			jDebugPrint(_T("hero_id"),hero_id);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_X2CH_BUILD_UPGRADE(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_ChannelServer
	
	inline bool READ_X2CH_BUILD_UPGRADE(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_X2CH_BUILD_UPGRADE &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.build_slot, 32);
		nStream::Read(st,param.hero_id);
		
		#ifndef jNOT_USE_DebugPrint_ChannelServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("X2CH_BUILD_UPGRADE : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_ChannelServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_ChannelServer
	inline jPacket_Base WRITE_X2CH_BUILD_UPGRADE(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_X2CH_BUILD_UPGRADE &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.build_slot);
			nStream::Write(st,param.hero_id);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_X2CH_BUILD_UPGRADE;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2CH_BUILD_UPGRADE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2CH_BUILD_UPGRADE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_X2CH_BUILD_UPGRADE(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  tcstr _build_slot, const uint8 &_hero_id)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_build_slot);
			nStream::Write(st,_hero_id);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_X2CH_BUILD_UPGRADE;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2CH_BUILD_UPGRADE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2CH_BUILD_UPGRADE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_ChannelServer

}/*nChannelServer */ }/* nNET*/ } //nMech
#endif //ChannelServer___X2CH_BUILD_UPGRADE__