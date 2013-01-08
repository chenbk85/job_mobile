
#ifndef TestServer___X2S_TEST_PACKET__ 
#define TestServer___X2S_TEST_PACKET__

#ifndef TestServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_TestServer(TestServer);
jxDECL_TestServer(X2S_TEST_PACKET);
#endif //TestServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nTestServer
{
	const int pk_X2S_TEST_PACKET = /*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+8;
	/* int32 val;*/
	/* string msg;*/
	
	struct S_X2S_TEST_PACKET;
	bool READ_X2S_TEST_PACKET(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_X2S_TEST_PACKET &param);
	struct S_X2S_TEST_PACKET
	{
		int32 val;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_TestServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_TestServer

		string msg;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_TestServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_TestServer


		#ifndef jNOT_USE_DebugPrint_TestServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< X2S_TEST_PACKET > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("val"),val);
			jDebugPrint(_T("msg"),msg);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_X2S_TEST_PACKET(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_TestServer
	
	inline bool READ_X2S_TEST_PACKET(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_X2S_TEST_PACKET &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.val);
		nStream::Read(st,param.msg);
		
		#ifndef jNOT_USE_DebugPrint_TestServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("X2S_TEST_PACKET : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_TestServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_TestServer
	inline jPacket_Base WRITE_X2S_TEST_PACKET(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_X2S_TEST_PACKET &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.val);
			nStream::Write(st,param.msg);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_X2S_TEST_PACKET;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2S_TEST_PACKET :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2S_TEST_PACKET :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_X2S_TEST_PACKET(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const int32 &_val, const string &_msg)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_val);
			nStream::Write(st,_msg);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_X2S_TEST_PACKET;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2S_TEST_PACKET :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2S_TEST_PACKET :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_TestServer

}/*nTestServer */ }/* nNET*/ } //nMech
#endif //TestServer___X2S_TEST_PACKET__