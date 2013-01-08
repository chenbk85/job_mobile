
#ifndef MonitorServer___M2A_PROCESS_INFO_UPDATE__ 
#define MonitorServer___M2A_PROCESS_INFO_UPDATE__

#ifndef MonitorServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_MonitorServer(MonitorServer);
jxDECL_MonitorServer(M2A_PROCESS_INFO_UPDATE);
#endif //MonitorServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nMonitorServer
{
	const int pk_M2A_PROCESS_INFO_UPDATE = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+16;
	/* tstring eServerType;*/
	/* wstring name;*/
	/* wstring value;*/
	
	struct S_M2A_PROCESS_INFO_UPDATE;
	bool READ_M2A_PROCESS_INFO_UPDATE(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_M2A_PROCESS_INFO_UPDATE &param);
	struct S_M2A_PROCESS_INFO_UPDATE
	{
		tstring eServerType;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer

		wstring name;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer

		wstring value;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer


		#ifndef jNOT_USE_DebugPrint_MonitorServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< M2A_PROCESS_INFO_UPDATE > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("eServerType"),eServerType);
			jDebugPrint(_T("name"),name);
			jDebugPrint(_T("value"),value);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_M2A_PROCESS_INFO_UPDATE(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_MonitorServer
	
	inline bool READ_M2A_PROCESS_INFO_UPDATE(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_M2A_PROCESS_INFO_UPDATE &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.eServerType);
		nStream::Read(st,param.name);
		nStream::Read(st,param.value);
		
		#ifndef jNOT_USE_DebugPrint_MonitorServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("M2A_PROCESS_INFO_UPDATE : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_MonitorServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_MonitorServer
	inline jPacket_Base WRITE_M2A_PROCESS_INFO_UPDATE(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_M2A_PROCESS_INFO_UPDATE &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.eServerType);
			nStream::Write(st,param.name);
			nStream::Write(st,param.value);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_M2A_PROCESS_INFO_UPDATE;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" M2A_PROCESS_INFO_UPDATE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" M2A_PROCESS_INFO_UPDATE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_M2A_PROCESS_INFO_UPDATE(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const tstring &_eServerType, const wstring &_name, const wstring &_value)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_eServerType);
			nStream::Write(st,_name);
			nStream::Write(st,_value);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_M2A_PROCESS_INFO_UPDATE;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" M2A_PROCESS_INFO_UPDATE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" M2A_PROCESS_INFO_UPDATE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_MonitorServer

}/*nMonitorServer */ }/* nNET*/ } //nMech
#endif //MonitorServer___M2A_PROCESS_INFO_UPDATE__