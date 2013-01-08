
#ifndef TestServer___S2X_LOGIN_OK__ 
#define TestServer___S2X_LOGIN_OK__

#ifndef TestServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_TestServer(TestServer);
jxDECL_TestServer(S2X_LOGIN_OK);
#endif //TestServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nTestServer
{
	const int pk_S2X_LOGIN_OK = /*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+3;
	/* wname32_t server_name;*/
	
	struct S_S2X_LOGIN_OK;
	bool READ_S2X_LOGIN_OK(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_S2X_LOGIN_OK &param);
	struct S_S2X_LOGIN_OK
	{
		wname32_t server_name;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_TestServer
					void set_server_name(tcstr sz){jw_strncpy(server_name,nUNI::scb1024_t(sz).getW(), 32);	server_name[32-1]=0;}
					tcstr get_server_name(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(server_name).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_TestServer


		#ifndef jNOT_USE_DebugPrint_TestServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< S2X_LOGIN_OK > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("server_name"),server_name);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_S2X_LOGIN_OK(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_TestServer
	
	inline bool READ_S2X_LOGIN_OK(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_S2X_LOGIN_OK &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.server_name, 32);
		
		#ifndef jNOT_USE_DebugPrint_TestServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("S2X_LOGIN_OK : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_TestServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_TestServer
	inline jPacket_Base WRITE_S2X_LOGIN_OK(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_S2X_LOGIN_OK &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.server_name);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_S2X_LOGIN_OK;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" S2X_LOGIN_OK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" S2X_LOGIN_OK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_S2X_LOGIN_OK(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  wcstr _server_name)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_server_name);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_S2X_LOGIN_OK;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" S2X_LOGIN_OK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" S2X_LOGIN_OK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_TestServer

}/*nTestServer */ }/* nNET*/ } //nMech
#endif //TestServer___S2X_LOGIN_OK__