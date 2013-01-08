
#ifndef TestServer___S_HELLO__ 
#define TestServer___S_HELLO__

#ifndef TestServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_TestServer(TestServer);
jxDECL_TestServer(S_HELLO);
#endif //TestServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nTestServer
{
	const int pk_S_HELLO = /*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+1;
	
	struct S_S_HELLO;
	bool READ_S_HELLO(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_S_HELLO &param);
	struct S_S_HELLO
	{

		#ifndef jNOT_USE_DebugPrint_TestServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< S_HELLO > ="));
			if(!isPrintAll)return;
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_S_HELLO(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_TestServer
	
	inline bool READ_S_HELLO(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_S_HELLO &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		
		#ifndef jNOT_USE_DebugPrint_TestServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("S_HELLO : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_TestServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_TestServer
	inline jPacket_Base WRITE_S_HELLO(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_S_HELLO &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_S_HELLO;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" S_HELLO :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" S_HELLO :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_S_HELLO(nNET::nStream::_jNetStreamWriteBufferBase &buffer )
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_S_HELLO;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" S_HELLO :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" S_HELLO :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_TestServer

}/*nTestServer */ }/* nNET*/ } //nMech
#endif //TestServer___S_HELLO__