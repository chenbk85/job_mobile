
#ifndef DummyServer___DT2X_SET_TEST_ENV__ 
#define DummyServer___DT2X_SET_TEST_ENV__

#ifndef DummyServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DummyServer(DummyServer);
jxDECL_DummyServer(DT2X_SET_TEST_ENV);
#endif //DummyServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nDummyServer
{
	const int pk_DT2X_SET_TEST_ENV = /*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+12;
	
	struct S_DT2X_SET_TEST_ENV;
	bool READ_DT2X_SET_TEST_ENV(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DT2X_SET_TEST_ENV &param);
	struct S_DT2X_SET_TEST_ENV
	{

		#ifndef jNOT_USE_DebugPrint_DummyServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DT2X_SET_TEST_ENV > ="));
			if(!isPrintAll)return;
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DT2X_SET_TEST_ENV(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_DummyServer
	
	inline bool READ_DT2X_SET_TEST_ENV(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DT2X_SET_TEST_ENV &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		
		#ifndef jNOT_USE_DebugPrint_DummyServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DT2X_SET_TEST_ENV : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_DummyServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_DummyServer
	inline jPacket_Base WRITE_DT2X_SET_TEST_ENV(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DT2X_SET_TEST_ENV &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DT2X_SET_TEST_ENV;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DT2X_SET_TEST_ENV :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DT2X_SET_TEST_ENV :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DT2X_SET_TEST_ENV(nNET::nStream::_jNetStreamWriteBufferBase &buffer )
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DT2X_SET_TEST_ENV;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DT2X_SET_TEST_ENV :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DT2X_SET_TEST_ENV :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_DummyServer

}/*nDummyServer */ }/* nNET*/ } //nMech
#endif //DummyServer___DT2X_SET_TEST_ENV__