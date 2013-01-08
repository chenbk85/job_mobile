
#ifndef MsgServer___MG_ECHO__ 
#define MsgServer___MG_ECHO__

#ifndef MsgServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_MsgServer(MsgServer);
jxDECL_MsgServer(MG_ECHO);
#endif //MsgServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nMsgServer
{
	const int pk_MG_ECHO = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1900+3;
	/* tname256_t msg;*/
	/* int8 type;*/
	
	struct S_MG_ECHO;
	bool READ_MG_ECHO(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_MG_ECHO &param);
	struct S_MG_ECHO
	{
		tname256_t msg;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_MsgServer
					void set_msg(tcstr sz){jt_strncpy(msg,nUNI::scb1024_t(sz).getT(), 256);	msg[256-1]=0;}
					tcstr get_msg(fname_t _buf){jt_strncpy(_buf, nUNI::scb256_t(msg).getT() , 256);_buf[256-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_MsgServer

		int8 type;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_MsgServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_MsgServer


		#ifndef jNOT_USE_DebugPrint_MsgServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< MG_ECHO > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("msg"),msg);
			jDebugPrint(_T("type"),type);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_MG_ECHO(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_MsgServer
	
	inline bool READ_MG_ECHO(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_MG_ECHO &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.msg, 256);
		nStream::Read(st,param.type);
		
		#ifndef jNOT_USE_DebugPrint_MsgServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("MG_ECHO : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_MsgServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_MsgServer
	inline jPacket_Base WRITE_MG_ECHO(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_MG_ECHO &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.msg);
			nStream::Write(st,param.type);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_MG_ECHO;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" MG_ECHO :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" MG_ECHO :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_MG_ECHO(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  tcstr _msg, const int8 &_type)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_msg);
			nStream::Write(st,_type);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_MG_ECHO;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" MG_ECHO :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" MG_ECHO :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_MsgServer

}/*nMsgServer */ }/* nNET*/ } //nMech
#endif //MsgServer___MG_ECHO__