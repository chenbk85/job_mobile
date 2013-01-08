
#ifndef DummyServer___DT2_UPDATE_XPATH_VALUE__ 
#define DummyServer___DT2_UPDATE_XPATH_VALUE__

#ifndef DummyServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DummyServer(DummyServer);
jxDECL_DummyServer(DT2_UPDATE_XPATH_VALUE);
#endif //DummyServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nDummyServer
{
	const int pk_DT2_UPDATE_XPATH_VALUE = /*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+9;
	
	struct S_DT2_UPDATE_XPATH_VALUE;
	bool READ_DT2_UPDATE_XPATH_VALUE(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DT2_UPDATE_XPATH_VALUE &param);
	struct S_DT2_UPDATE_XPATH_VALUE
	{

		#ifndef jNOT_USE_DebugPrint_DummyServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DT2_UPDATE_XPATH_VALUE > ="));
			if(!isPrintAll)return;
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DT2_UPDATE_XPATH_VALUE(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_DummyServer
	
	inline bool READ_DT2_UPDATE_XPATH_VALUE(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DT2_UPDATE_XPATH_VALUE &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		
		#ifndef jNOT_USE_DebugPrint_DummyServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DT2_UPDATE_XPATH_VALUE : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_DummyServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_DummyServer
	inline jPacket_Base WRITE_DT2_UPDATE_XPATH_VALUE(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DT2_UPDATE_XPATH_VALUE &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DT2_UPDATE_XPATH_VALUE;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DT2_UPDATE_XPATH_VALUE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DT2_UPDATE_XPATH_VALUE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DT2_UPDATE_XPATH_VALUE(nNET::nStream::_jNetStreamWriteBufferBase &buffer )
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DT2_UPDATE_XPATH_VALUE;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DT2_UPDATE_XPATH_VALUE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DT2_UPDATE_XPATH_VALUE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_DummyServer

}/*nDummyServer */ }/* nNET*/ } //nMech
#endif //DummyServer___DT2_UPDATE_XPATH_VALUE__