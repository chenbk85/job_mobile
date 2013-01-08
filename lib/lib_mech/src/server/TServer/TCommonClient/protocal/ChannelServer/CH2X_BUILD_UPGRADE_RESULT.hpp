
#ifndef ChannelServer___CH2X_BUILD_UPGRADE_RESULT__ 
#define ChannelServer___CH2X_BUILD_UPGRADE_RESULT__

#ifndef ChannelServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_ChannelServer(ChannelServer);
jxDECL_ChannelServer(CH2X_BUILD_UPGRADE_RESULT);
#endif //ChannelServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nChannelServer
{
	const int pk_CH2X_BUILD_UPGRADE_RESULT = /*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+25;
	/* tname32_t build_slot;*/
	/* uint8 _EBuildType;*/
	/* uint8 level;*/
	/* jError e;*/
	/* j_time_t curr_server_time;*/
	/* int32 upgrade_sec;*/
	/* uint8 hero_id;*/
	
	struct S_CH2X_BUILD_UPGRADE_RESULT;
	bool READ_CH2X_BUILD_UPGRADE_RESULT(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_CH2X_BUILD_UPGRADE_RESULT &param);
	struct S_CH2X_BUILD_UPGRADE_RESULT
	{
		tname32_t build_slot;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer
					void set_build_slot(tcstr sz){jt_strncpy(build_slot,nUNI::scb1024_t(sz).getT(), 32);	build_slot[32-1]=0;}
					tcstr get_build_slot(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(build_slot).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer

		uint8 _EBuildType;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer

		uint8 level;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer

		jError e;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer

		j_time_t curr_server_time;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer

		int32 upgrade_sec;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer

		uint8 hero_id;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer


		#ifndef jNOT_USE_DebugPrint_ChannelServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< CH2X_BUILD_UPGRADE_RESULT > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("build_slot"),build_slot);
			jDebugPrint(_T("_EBuildType"),_EBuildType);
			jDebugPrint(_T("level"),level);
			jDebugPrint(_T("e"),e);
			jDebugPrint(_T("curr_server_time"),curr_server_time);
			jDebugPrint(_T("upgrade_sec"),upgrade_sec);
			jDebugPrint(_T("hero_id"),hero_id);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_CH2X_BUILD_UPGRADE_RESULT(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_ChannelServer
	
	inline bool READ_CH2X_BUILD_UPGRADE_RESULT(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_CH2X_BUILD_UPGRADE_RESULT &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.build_slot, 32);
		nStream::Read(st,param._EBuildType);
		nStream::Read(st,param.level);
		nStream::Read(st,param.e);
		nStream::Read(st,param.curr_server_time);
		nStream::Read(st,param.upgrade_sec);
		nStream::Read(st,param.hero_id);
		
		#ifndef jNOT_USE_DebugPrint_ChannelServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("CH2X_BUILD_UPGRADE_RESULT : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_ChannelServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_ChannelServer
	inline jPacket_Base WRITE_CH2X_BUILD_UPGRADE_RESULT(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_CH2X_BUILD_UPGRADE_RESULT &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.build_slot);
			nStream::Write(st,param._EBuildType);
			nStream::Write(st,param.level);
			nStream::Write(st,param.e);
			nStream::Write(st,param.curr_server_time);
			nStream::Write(st,param.upgrade_sec);
			nStream::Write(st,param.hero_id);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_CH2X_BUILD_UPGRADE_RESULT;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" CH2X_BUILD_UPGRADE_RESULT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" CH2X_BUILD_UPGRADE_RESULT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_CH2X_BUILD_UPGRADE_RESULT(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  tcstr _build_slot, const uint8 &__EBuildType, const uint8 &_level, const jError &_e, const j_time_t &_curr_server_time, const int32 &_upgrade_sec, const uint8 &_hero_id)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_build_slot);
			nStream::Write(st,__EBuildType);
			nStream::Write(st,_level);
			nStream::Write(st,_e);
			nStream::Write(st,_curr_server_time);
			nStream::Write(st,_upgrade_sec);
			nStream::Write(st,_hero_id);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_CH2X_BUILD_UPGRADE_RESULT;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" CH2X_BUILD_UPGRADE_RESULT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" CH2X_BUILD_UPGRADE_RESULT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_ChannelServer

}/*nChannelServer */ }/* nNET*/ } //nMech
#endif //ChannelServer___CH2X_BUILD_UPGRADE_RESULT__