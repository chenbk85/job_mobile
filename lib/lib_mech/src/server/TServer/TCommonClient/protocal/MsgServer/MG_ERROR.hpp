
#ifndef MsgServer___MG_ERROR__ 
#define MsgServer___MG_ERROR__

#ifndef MsgServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_MsgServer(MsgServer);
jxDECL_MsgServer(MG_ERROR);
#endif //MsgServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nMsgServer
{
	const int pk_MG_ERROR = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1900+6;
	/* jErrorInfo ei;*/
	
	struct S_MG_ERROR;
	bool READ_MG_ERROR(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_MG_ERROR &param);
	struct S_MG_ERROR
	{
		jErrorInfo ei;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_MsgServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_MsgServer


		#ifndef jNOT_USE_DebugPrint_MsgServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< MG_ERROR > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("ei"),ei);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_MG_ERROR(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_MsgServer
	
	inline bool READ_MG_ERROR(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_MG_ERROR &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.ei);
		
		#ifndef jNOT_USE_DebugPrint_MsgServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("MG_ERROR : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_MsgServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_MsgServer
	inline jPacket_Base WRITE_MG_ERROR(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_MG_ERROR &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.ei);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_MG_ERROR;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" MG_ERROR :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" MG_ERROR :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_MG_ERROR(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const jErrorInfo &_ei)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_ei);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_MG_ERROR;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" MG_ERROR :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" MG_ERROR :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_MsgServer

}/*nMsgServer */ }/* nNET*/ } //nMech
#endif //MsgServer___MG_ERROR__