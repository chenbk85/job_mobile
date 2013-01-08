
#ifndef MonitorServer___A2M_SEND_ERROR_LOG__ 
#define MonitorServer___A2M_SEND_ERROR_LOG__

#ifndef MonitorServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_MonitorServer(MonitorServer);
jxDECL_MonitorServer(A2M_SEND_ERROR_LOG);
#endif //MonitorServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nMonitorServer
{
	const int pk_A2M_SEND_ERROR_LOG = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+17;
	/* aname32_t eServerType;*/
	/* wstring log;*/
	
	struct S_A2M_SEND_ERROR_LOG;
	bool READ_A2M_SEND_ERROR_LOG(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_A2M_SEND_ERROR_LOG &param);
	struct S_A2M_SEND_ERROR_LOG
	{
		aname32_t eServerType;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer
					void set_eServerType(tcstr sz){ja_strncpy(eServerType,nUNI::scb1024_t(sz).getA(), 32);	eServerType[32-1]=0;}
					tcstr get_eServerType(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(eServerType).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer

		wstring log;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer


		#ifndef jNOT_USE_DebugPrint_MonitorServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< A2M_SEND_ERROR_LOG > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("eServerType"),eServerType);
			jDebugPrint(_T("log"),log);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_A2M_SEND_ERROR_LOG(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_MonitorServer
	
	inline bool READ_A2M_SEND_ERROR_LOG(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_A2M_SEND_ERROR_LOG &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.eServerType, 32);
		nStream::Read(st,param.log);
		
		#ifndef jNOT_USE_DebugPrint_MonitorServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("A2M_SEND_ERROR_LOG : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_MonitorServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_MonitorServer
	inline jPacket_Base WRITE_A2M_SEND_ERROR_LOG(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_A2M_SEND_ERROR_LOG &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.eServerType);
			nStream::Write(st,param.log);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_A2M_SEND_ERROR_LOG;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" A2M_SEND_ERROR_LOG :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" A2M_SEND_ERROR_LOG :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_A2M_SEND_ERROR_LOG(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  acstr _eServerType, const wstring &_log)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_eServerType);
			nStream::Write(st,_log);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_A2M_SEND_ERROR_LOG;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" A2M_SEND_ERROR_LOG :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" A2M_SEND_ERROR_LOG :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_MonitorServer

}/*nMonitorServer */ }/* nNET*/ } //nMech
#endif //MonitorServer___A2M_SEND_ERROR_LOG__