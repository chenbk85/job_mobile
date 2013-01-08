
#ifndef MailServer___SS2M_SERVERINFO_ACK__ 
#define MailServer___SS2M_SERVERINFO_ACK__

#ifndef MailServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_MailServer(MailServer);
jxDECL_MailServer(SS2M_SERVERINFO_ACK);
#endif //MailServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nMailServer
{
	const int pk_SS2M_SERVERINFO_ACK = /*nMech::nNET::EProtocal_jINet_OGS_END+*/7000+4;
	/* jServerInfo si;*/
	
	struct S_SS2M_SERVERINFO_ACK;
	bool READ_SS2M_SERVERINFO_ACK(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_SS2M_SERVERINFO_ACK &param);
	struct S_SS2M_SERVERINFO_ACK
	{
		jServerInfo si;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_MailServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_MailServer


		#ifndef jNOT_USE_DebugPrint_MailServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< SS2M_SERVERINFO_ACK > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("si"),si);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_SS2M_SERVERINFO_ACK(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_MailServer
	
	inline bool READ_SS2M_SERVERINFO_ACK(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_SS2M_SERVERINFO_ACK &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.si);
		
		#ifndef jNOT_USE_DebugPrint_MailServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("SS2M_SERVERINFO_ACK : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_MailServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_MailServer
	inline jPacket_Base WRITE_SS2M_SERVERINFO_ACK(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_SS2M_SERVERINFO_ACK &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.si);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_SS2M_SERVERINFO_ACK;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" SS2M_SERVERINFO_ACK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" SS2M_SERVERINFO_ACK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_SS2M_SERVERINFO_ACK(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const jServerInfo &_si)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_si);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_SS2M_SERVERINFO_ACK;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" SS2M_SERVERINFO_ACK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" SS2M_SERVERINFO_ACK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_MailServer

}/*nMailServer */ }/* nNET*/ } //nMech
#endif //MailServer___SS2M_SERVERINFO_ACK__