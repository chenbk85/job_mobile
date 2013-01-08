
#ifndef DummyServer___DT_TEST_LOGIN_START__ 
#define DummyServer___DT_TEST_LOGIN_START__

#ifndef DummyServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DummyServer(DummyServer);
jxDECL_DummyServer(DT_TEST_LOGIN_START);
#endif //DummyServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nDummyServer
{
	const int pk_DT_TEST_LOGIN_START = /*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+6;
	/* int16 per_user;*/
	/* uint32 delay;*/
	/* tname32_t testClientName;*/
	
	struct S_DT_TEST_LOGIN_START;
	bool READ_DT_TEST_LOGIN_START(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DT_TEST_LOGIN_START &param);
	struct S_DT_TEST_LOGIN_START
	{
		int16 per_user;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DummyServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DummyServer

		uint32 delay;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DummyServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DummyServer

		tname32_t testClientName;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DummyServer
					void set_testClientName(tcstr sz){jt_strncpy(testClientName,nUNI::scb1024_t(sz).getT(), 32);	testClientName[32-1]=0;}
					tcstr get_testClientName(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(testClientName).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DummyServer


		#ifndef jNOT_USE_DebugPrint_DummyServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DT_TEST_LOGIN_START > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("per_user"),per_user);
			jDebugPrint(_T("delay"),delay);
			jDebugPrint(_T("testClientName"),testClientName);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DT_TEST_LOGIN_START(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_DummyServer
	
	inline bool READ_DT_TEST_LOGIN_START(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DT_TEST_LOGIN_START &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.per_user);
		nStream::Read(st,param.delay);
		nStream::Read(st,param.testClientName, 32);
		
		#ifndef jNOT_USE_DebugPrint_DummyServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DT_TEST_LOGIN_START : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_DummyServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_DummyServer
	inline jPacket_Base WRITE_DT_TEST_LOGIN_START(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DT_TEST_LOGIN_START &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.per_user);
			nStream::Write(st,param.delay);
			nStream::Write(st,param.testClientName);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DT_TEST_LOGIN_START;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DT_TEST_LOGIN_START :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DT_TEST_LOGIN_START :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DT_TEST_LOGIN_START(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const int16 &_per_user, const uint32 &_delay,  tcstr _testClientName)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_per_user);
			nStream::Write(st,_delay);
			nStream::Write(st,_testClientName);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DT_TEST_LOGIN_START;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DT_TEST_LOGIN_START :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DT_TEST_LOGIN_START :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_DummyServer

}/*nDummyServer */ }/* nNET*/ } //nMech
#endif //DummyServer___DT_TEST_LOGIN_START__