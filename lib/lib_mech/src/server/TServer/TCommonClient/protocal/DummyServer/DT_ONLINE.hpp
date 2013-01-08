
#ifndef DummyServer___DT_ONLINE__ 
#define DummyServer___DT_ONLINE__

#ifndef DummyServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DummyServer(DummyServer);
jxDECL_DummyServer(DT_ONLINE);
#endif //DummyServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nDummyServer
{
	const int pk_DT_ONLINE = /*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+5;
	/* tname32_t test_id;*/
	/*[[ 테스트용 계정 접두어&#x0A; ]]*/
	/* int TEST_ID_START_NUM;*/
	/* uint16 iDummyCount;*/
	/*[[ 테스트클라이언트당 더미갯수 ]]*/
	/* tname32_t szLoginIP;*/
	/* uint16 iLoginPort;*/
	
	struct S_DT_ONLINE;
	bool READ_DT_ONLINE(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DT_ONLINE &param);
	struct S_DT_ONLINE
	{
		/*[[ 테스트용 계정 접두어&#x0A; ]]*/
		tname32_t test_id;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DummyServer
					void set_test_id(tcstr sz){jt_strncpy(test_id,nUNI::scb1024_t(sz).getT(), 32);	test_id[32-1]=0;}
					tcstr get_test_id(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(test_id).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DummyServer

		int TEST_ID_START_NUM;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DummyServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DummyServer

		/*[[ 테스트클라이언트당 더미갯수 ]]*/
		uint16 iDummyCount;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DummyServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DummyServer

		tname32_t szLoginIP;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DummyServer
					void set_szLoginIP(tcstr sz){jt_strncpy(szLoginIP,nUNI::scb1024_t(sz).getT(), 32);	szLoginIP[32-1]=0;}
					tcstr get_szLoginIP(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(szLoginIP).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DummyServer

		uint16 iLoginPort;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DummyServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DummyServer


		#ifndef jNOT_USE_DebugPrint_DummyServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DT_ONLINE > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("test_id"),test_id);
			jDebugPrint(_T("TEST_ID_START_NUM"),TEST_ID_START_NUM);
			jDebugPrint(_T("iDummyCount"),iDummyCount);
			jDebugPrint(_T("szLoginIP"),szLoginIP);
			jDebugPrint(_T("iLoginPort"),iLoginPort);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DT_ONLINE(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_DummyServer
	
	inline bool READ_DT_ONLINE(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DT_ONLINE &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.test_id, 32);
		/*	[[ 테스트용 계정 접두어&#x0A; ]]*/
		nStream::Read(st,param.TEST_ID_START_NUM);
		nStream::Read(st,param.iDummyCount);
		/*	[[ 테스트클라이언트당 더미갯수 ]]*/
		nStream::Read(st,param.szLoginIP, 32);
		nStream::Read(st,param.iLoginPort);
		
		#ifndef jNOT_USE_DebugPrint_DummyServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DT_ONLINE : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_DummyServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_DummyServer
	inline jPacket_Base WRITE_DT_ONLINE(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DT_ONLINE &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.test_id);
			/*[[ 테스트용 계정 접두어&#x0A; ]]*/
			nStream::Write(st,param.TEST_ID_START_NUM);
			nStream::Write(st,param.iDummyCount);
			/*[[ 테스트클라이언트당 더미갯수 ]]*/
			nStream::Write(st,param.szLoginIP);
			nStream::Write(st,param.iLoginPort);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DT_ONLINE;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DT_ONLINE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DT_ONLINE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DT_ONLINE(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  tcstr _test_id, const int &_TEST_ID_START_NUM, const uint16 &_iDummyCount,  tcstr _szLoginIP, const uint16 &_iLoginPort)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_test_id);
			/*[[ 테스트용 계정 접두어&#x0A; ]]*/
			nStream::Write(st,_TEST_ID_START_NUM);
			nStream::Write(st,_iDummyCount);
			/*[[ 테스트클라이언트당 더미갯수 ]]*/
			nStream::Write(st,_szLoginIP);
			nStream::Write(st,_iLoginPort);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DT_ONLINE;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DT_ONLINE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DT_ONLINE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_DummyServer

}/*nDummyServer */ }/* nNET*/ } //nMech
#endif //DummyServer___DT_ONLINE__