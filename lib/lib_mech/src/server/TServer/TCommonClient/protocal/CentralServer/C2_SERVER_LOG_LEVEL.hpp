
#ifndef CentralServer___C2_SERVER_LOG_LEVEL__ 
#define CentralServer___C2_SERVER_LOG_LEVEL__

#ifndef CentralServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_CentralServer(CentralServer);
jxDECL_CentralServer(C2_SERVER_LOG_LEVEL);
#endif //CentralServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nCentralServer
{
	const int pk_C2_SERVER_LOG_LEVEL = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+15;
	/* tname32_t type;*/
	/* bool enable;*/
	
	struct S_C2_SERVER_LOG_LEVEL;
	bool READ_C2_SERVER_LOG_LEVEL(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_C2_SERVER_LOG_LEVEL &param);
	struct S_C2_SERVER_LOG_LEVEL
	{
		tname32_t type;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_CentralServer
					void set_type(tcstr sz){jt_strncpy(type,nUNI::scb1024_t(sz).getT(), 32);	type[32-1]=0;}
					tcstr get_type(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(type).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_CentralServer

		bool enable;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_CentralServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_CentralServer


		#ifndef jNOT_USE_DebugPrint_CentralServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< C2_SERVER_LOG_LEVEL > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("type"),type);
			jDebugPrint(_T("enable"),enable);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_C2_SERVER_LOG_LEVEL(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_CentralServer
	
	inline bool READ_C2_SERVER_LOG_LEVEL(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_C2_SERVER_LOG_LEVEL &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.type, 32);
		nStream::Read(st,param.enable);
		
		#ifndef jNOT_USE_DebugPrint_CentralServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("C2_SERVER_LOG_LEVEL : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_CentralServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_CentralServer
	inline jPacket_Base WRITE_C2_SERVER_LOG_LEVEL(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_C2_SERVER_LOG_LEVEL &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.type);
			nStream::Write(st,param.enable);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_C2_SERVER_LOG_LEVEL;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" C2_SERVER_LOG_LEVEL :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" C2_SERVER_LOG_LEVEL :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_C2_SERVER_LOG_LEVEL(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  tcstr _type, const bool &_enable)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_type);
			nStream::Write(st,_enable);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_C2_SERVER_LOG_LEVEL;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" C2_SERVER_LOG_LEVEL :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" C2_SERVER_LOG_LEVEL :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_CentralServer

}/*nCentralServer */ }/* nNET*/ } //nMech
#endif //CentralServer___C2_SERVER_LOG_LEVEL__