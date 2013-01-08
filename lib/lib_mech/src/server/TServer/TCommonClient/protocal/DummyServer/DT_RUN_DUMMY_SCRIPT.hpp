
#ifndef DummyServer___DT_RUN_DUMMY_SCRIPT__ 
#define DummyServer___DT_RUN_DUMMY_SCRIPT__

#ifndef DummyServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DummyServer(DummyServer);
jxDECL_DummyServer(DT_RUN_DUMMY_SCRIPT);
#endif //DummyServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nDummyServer
{
	const int pk_DT_RUN_DUMMY_SCRIPT = /*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+13;
	/* TCHAR code[4096];*/
	
	struct S_DT_RUN_DUMMY_SCRIPT;
	bool READ_DT_RUN_DUMMY_SCRIPT(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DT_RUN_DUMMY_SCRIPT &param);
	struct S_DT_RUN_DUMMY_SCRIPT
	{
		TCHAR code[4096];
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DummyServer
		tcstr 	get_code(){ return code;}
		void 	set_code(tcstr sz){ jt_strncpy(code, sz,4096-1); code[4096-1]=0; }
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DummyServer


		#ifndef jNOT_USE_DebugPrint_DummyServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DT_RUN_DUMMY_SCRIPT > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("code"),code);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DT_RUN_DUMMY_SCRIPT(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_DummyServer
	
	inline bool READ_DT_RUN_DUMMY_SCRIPT(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DT_RUN_DUMMY_SCRIPT &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.code, 4096);
		
		#ifndef jNOT_USE_DebugPrint_DummyServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DT_RUN_DUMMY_SCRIPT : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_DummyServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_DummyServer
	inline jPacket_Base WRITE_DT_RUN_DUMMY_SCRIPT(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DT_RUN_DUMMY_SCRIPT &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.code);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DT_RUN_DUMMY_SCRIPT;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DT_RUN_DUMMY_SCRIPT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DT_RUN_DUMMY_SCRIPT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DT_RUN_DUMMY_SCRIPT(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const TCHAR *_code)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_code);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DT_RUN_DUMMY_SCRIPT;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DT_RUN_DUMMY_SCRIPT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DT_RUN_DUMMY_SCRIPT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_DummyServer

}/*nDummyServer */ }/* nNET*/ } //nMech
#endif //DummyServer___DT_RUN_DUMMY_SCRIPT__