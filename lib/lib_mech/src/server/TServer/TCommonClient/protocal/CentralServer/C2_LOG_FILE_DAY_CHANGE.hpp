
#ifndef CentralServer___C2_LOG_FILE_DAY_CHANGE__ 
#define CentralServer___C2_LOG_FILE_DAY_CHANGE__

#ifndef CentralServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_CentralServer(CentralServer);
jxDECL_CentralServer(C2_LOG_FILE_DAY_CHANGE);
#endif //CentralServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nCentralServer
{
	const int pk_C2_LOG_FILE_DAY_CHANGE = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+9;
	
	struct S_C2_LOG_FILE_DAY_CHANGE;
	bool READ_C2_LOG_FILE_DAY_CHANGE(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_C2_LOG_FILE_DAY_CHANGE &param);
	struct S_C2_LOG_FILE_DAY_CHANGE
	{

		#ifndef jNOT_USE_DebugPrint_CentralServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< C2_LOG_FILE_DAY_CHANGE > ="));
			if(!isPrintAll)return;
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_C2_LOG_FILE_DAY_CHANGE(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_CentralServer
	
	inline bool READ_C2_LOG_FILE_DAY_CHANGE(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_C2_LOG_FILE_DAY_CHANGE &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		
		#ifndef jNOT_USE_DebugPrint_CentralServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("C2_LOG_FILE_DAY_CHANGE : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_CentralServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_CentralServer
	inline jPacket_Base WRITE_C2_LOG_FILE_DAY_CHANGE(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_C2_LOG_FILE_DAY_CHANGE &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_C2_LOG_FILE_DAY_CHANGE;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" C2_LOG_FILE_DAY_CHANGE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" C2_LOG_FILE_DAY_CHANGE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_C2_LOG_FILE_DAY_CHANGE(nNET::nStream::_jNetStreamWriteBufferBase &buffer )
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_C2_LOG_FILE_DAY_CHANGE;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" C2_LOG_FILE_DAY_CHANGE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" C2_LOG_FILE_DAY_CHANGE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_CentralServer

}/*nCentralServer */ }/* nNET*/ } //nMech
#endif //CentralServer___C2_LOG_FILE_DAY_CHANGE__