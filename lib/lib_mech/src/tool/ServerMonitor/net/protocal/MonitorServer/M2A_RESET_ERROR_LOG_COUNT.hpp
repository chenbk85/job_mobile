
#ifndef MonitorServer___M2A_RESET_ERROR_LOG_COUNT__ 
#define MonitorServer___M2A_RESET_ERROR_LOG_COUNT__

#ifndef MonitorServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_MonitorServer(MonitorServer);
jxDECL_MonitorServer(M2A_RESET_ERROR_LOG_COUNT);
#endif //MonitorServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nMonitorServer
{
	const int pk_M2A_RESET_ERROR_LOG_COUNT = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+18;
	
	struct S_M2A_RESET_ERROR_LOG_COUNT;
	bool READ_M2A_RESET_ERROR_LOG_COUNT(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_M2A_RESET_ERROR_LOG_COUNT &param);
	struct S_M2A_RESET_ERROR_LOG_COUNT
	{

		#ifndef jNOT_USE_DebugPrint_MonitorServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< M2A_RESET_ERROR_LOG_COUNT > ="));
			if(!isPrintAll)return;
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_M2A_RESET_ERROR_LOG_COUNT(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_MonitorServer
	
	inline bool READ_M2A_RESET_ERROR_LOG_COUNT(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_M2A_RESET_ERROR_LOG_COUNT &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		
		#ifndef jNOT_USE_DebugPrint_MonitorServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("M2A_RESET_ERROR_LOG_COUNT : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_MonitorServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_MonitorServer
	inline jPacket_Base WRITE_M2A_RESET_ERROR_LOG_COUNT(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_M2A_RESET_ERROR_LOG_COUNT &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_M2A_RESET_ERROR_LOG_COUNT;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" M2A_RESET_ERROR_LOG_COUNT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" M2A_RESET_ERROR_LOG_COUNT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_M2A_RESET_ERROR_LOG_COUNT(nNET::nStream::_jNetStreamWriteBufferBase &buffer )
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_M2A_RESET_ERROR_LOG_COUNT;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" M2A_RESET_ERROR_LOG_COUNT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" M2A_RESET_ERROR_LOG_COUNT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_MonitorServer

}/*nMonitorServer */ }/* nNET*/ } //nMech
#endif //MonitorServer___M2A_RESET_ERROR_LOG_COUNT__