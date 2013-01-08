
#ifndef MsgServer___MG_SERVERINFO_ACK__ 
#define MsgServer___MG_SERVERINFO_ACK__

#ifndef MsgServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_MsgServer(MsgServer);
jxDECL_MsgServer(MG_SERVERINFO_ACK);
#endif //MsgServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nMsgServer
{
	/*[[ SS2MG_ONLINE을 받았을때 보낸쪽의 sid=0일때	
다시 요청하여 받음.	
왜냐면 sid=0이라는예기는 아직 central이나 command로&#x0A;부터 sid를 발급받는중이기때문이다. ]]*/
	const int pk_MG_SERVERINFO_ACK = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1900+4;
	/* jServerInfo si;*/
	
	struct S_MG_SERVERINFO_ACK;
	bool READ_MG_SERVERINFO_ACK(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_MG_SERVERINFO_ACK &param);
	struct S_MG_SERVERINFO_ACK
	{
		jServerInfo si;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_MsgServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_MsgServer


		#ifndef jNOT_USE_DebugPrint_MsgServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< MG_SERVERINFO_ACK > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("si"),si);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_MG_SERVERINFO_ACK(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_MsgServer
	
	inline bool READ_MG_SERVERINFO_ACK(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_MG_SERVERINFO_ACK &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.si);
		
		#ifndef jNOT_USE_DebugPrint_MsgServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("MG_SERVERINFO_ACK : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_MsgServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_MsgServer
	inline jPacket_Base WRITE_MG_SERVERINFO_ACK(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_MG_SERVERINFO_ACK &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.si);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_MG_SERVERINFO_ACK;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" MG_SERVERINFO_ACK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" MG_SERVERINFO_ACK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_MG_SERVERINFO_ACK(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const jServerInfo &_si)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_si);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_MG_SERVERINFO_ACK;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" MG_SERVERINFO_ACK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" MG_SERVERINFO_ACK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_MsgServer

}/*nMsgServer */ }/* nNET*/ } //nMech
#endif //MsgServer___MG_SERVERINFO_ACK__