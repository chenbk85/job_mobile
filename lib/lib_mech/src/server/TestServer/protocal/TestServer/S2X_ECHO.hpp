
#ifndef TestServer___S2X_ECHO__ 
#define TestServer___S2X_ECHO__

#ifndef TestServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_TestServer(TestServer);
jxDECL_TestServer(S2X_ECHO);
#endif //TestServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nTestServer
{
	const int pk_S2X_ECHO = /*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+5;
	/* uint8 type;*/
	/* wstring msg;*/
	
	struct S_S2X_ECHO;
	bool READ_S2X_ECHO(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_S2X_ECHO &param);
	struct S_S2X_ECHO
	{
		uint8 type;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_TestServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_TestServer

		wstring msg;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_TestServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_TestServer


		#ifndef jNOT_USE_DebugPrint_TestServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< S2X_ECHO > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("type"),type);
			jDebugPrint(_T("msg"),msg);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_S2X_ECHO(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_TestServer
	
	inline bool READ_S2X_ECHO(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_S2X_ECHO &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.type);
		nStream::Read(st,param.msg);
		
		#ifndef jNOT_USE_DebugPrint_TestServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("S2X_ECHO : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_TestServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_TestServer
	inline jPacket_Base WRITE_S2X_ECHO(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_S2X_ECHO &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.type);
			nStream::Write(st,param.msg);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_S2X_ECHO;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" S2X_ECHO :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" S2X_ECHO :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_S2X_ECHO(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const uint8 &_type, const wstring &_msg)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_type);
			nStream::Write(st,_msg);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_S2X_ECHO;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" S2X_ECHO :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" S2X_ECHO :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_TestServer

}/*nTestServer */ }/* nNET*/ } //nMech
#endif //TestServer___S2X_ECHO__