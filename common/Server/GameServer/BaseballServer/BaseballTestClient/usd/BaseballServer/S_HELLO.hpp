
#ifndef BaseballServer___S_HELLO__ 
#define BaseballServer___S_HELLO__

#ifndef BaseballServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_BaseballServer(BaseballServer);
jxDECL_BaseballServer(S_HELLO);
#endif //BaseballServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nBaseballServer
{
	const int pk_S_HELLO = /*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+1;
	/* int type;*/
	/* astring msg;*/
	
	struct S_S_HELLO;
	bool READ_S_HELLO(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_S_HELLO &param);
	struct S_S_HELLO
	{
		int type;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_BaseballServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_BaseballServer

		astring msg;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_BaseballServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_BaseballServer


		#ifndef jNOT_USE_DebugPrint_BaseballServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< S_HELLO > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("type"),type);
			jDebugPrint(_T("msg"),msg);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_S_HELLO(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_BaseballServer
	
	inline bool READ_S_HELLO(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_S_HELLO &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.type);
		nStream::Read(st,param.msg);
		
		#ifndef jNOT_USE_DebugPrint_BaseballServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("S_HELLO : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_BaseballServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_BaseballServer
	inline jPacket_Base WRITE_S_HELLO(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_S_HELLO &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.type);
			nStream::Write(st,param.msg);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_S_HELLO;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" S_HELLO :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" S_HELLO :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_S_HELLO(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const int &_type, const astring &_msg)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_type);
			nStream::Write(st,_msg);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_S_HELLO;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" S_HELLO :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" S_HELLO :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_BaseballServer

}/*nBaseballServer */ }/* nNET*/ } //nMech
#endif //BaseballServer___S_HELLO__