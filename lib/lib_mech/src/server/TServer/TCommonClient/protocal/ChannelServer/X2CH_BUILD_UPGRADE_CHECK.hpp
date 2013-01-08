
#ifndef ChannelServer___X2CH_BUILD_UPGRADE_CHECK__ 
#define ChannelServer___X2CH_BUILD_UPGRADE_CHECK__

#ifndef ChannelServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_ChannelServer(ChannelServer);
jxDECL_ChannelServer(X2CH_BUILD_UPGRADE_CHECK);
#endif //ChannelServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nChannelServer
{
	/*[[ 업글 서버종료시간을 클라가 알기때문에	
업글 종료시간에 맞추어 이패킷을 보내자.	
	
이패킷을 불법적으로 보내면 클라 종료시키자. ]]*/
	const int pk_X2CH_BUILD_UPGRADE_CHECK = /*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+28;
	/* tname32_t build_slot;*/
	
	struct S_X2CH_BUILD_UPGRADE_CHECK;
	bool READ_X2CH_BUILD_UPGRADE_CHECK(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_X2CH_BUILD_UPGRADE_CHECK &param);
	struct S_X2CH_BUILD_UPGRADE_CHECK
	{
		tname32_t build_slot;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer
					void set_build_slot(tcstr sz){jt_strncpy(build_slot,nUNI::scb1024_t(sz).getT(), 32);	build_slot[32-1]=0;}
					tcstr get_build_slot(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(build_slot).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer


		#ifndef jNOT_USE_DebugPrint_ChannelServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< X2CH_BUILD_UPGRADE_CHECK > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("build_slot"),build_slot);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_X2CH_BUILD_UPGRADE_CHECK(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_ChannelServer
	
	inline bool READ_X2CH_BUILD_UPGRADE_CHECK(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_X2CH_BUILD_UPGRADE_CHECK &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.build_slot, 32);
		
		#ifndef jNOT_USE_DebugPrint_ChannelServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("X2CH_BUILD_UPGRADE_CHECK : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_ChannelServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_ChannelServer
	inline jPacket_Base WRITE_X2CH_BUILD_UPGRADE_CHECK(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_X2CH_BUILD_UPGRADE_CHECK &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.build_slot);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_X2CH_BUILD_UPGRADE_CHECK;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2CH_BUILD_UPGRADE_CHECK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2CH_BUILD_UPGRADE_CHECK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_X2CH_BUILD_UPGRADE_CHECK(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  tcstr _build_slot)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_build_slot);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_X2CH_BUILD_UPGRADE_CHECK;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2CH_BUILD_UPGRADE_CHECK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2CH_BUILD_UPGRADE_CHECK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_ChannelServer

}/*nChannelServer */ }/* nNET*/ } //nMech
#endif //ChannelServer___X2CH_BUILD_UPGRADE_CHECK__