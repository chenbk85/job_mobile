
#ifndef CentralServer___SS2C_SERVERINFO_ACK__ 
#define CentralServer___SS2C_SERVERINFO_ACK__

#ifndef CentralServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_CentralServer(CentralServer);
jxDECL_CentralServer(SS2C_SERVERINFO_ACK);
#endif //CentralServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nCentralServer
{
	const int pk_SS2C_SERVERINFO_ACK = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+6;
	/* jServerInfo si;*/
	
	struct S_SS2C_SERVERINFO_ACK;
	bool READ_SS2C_SERVERINFO_ACK(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_SS2C_SERVERINFO_ACK &param);
	struct S_SS2C_SERVERINFO_ACK
	{
		jServerInfo si;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_CentralServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_CentralServer


		#ifndef jNOT_USE_DebugPrint_CentralServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< SS2C_SERVERINFO_ACK > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("si"),si);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_SS2C_SERVERINFO_ACK(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_CentralServer
	
	inline bool READ_SS2C_SERVERINFO_ACK(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_SS2C_SERVERINFO_ACK &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.si);
		
		#ifndef jNOT_USE_DebugPrint_CentralServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("SS2C_SERVERINFO_ACK : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_CentralServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_CentralServer
	inline jPacket_Base WRITE_SS2C_SERVERINFO_ACK(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_SS2C_SERVERINFO_ACK &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.si);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_SS2C_SERVERINFO_ACK;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" SS2C_SERVERINFO_ACK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" SS2C_SERVERINFO_ACK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_SS2C_SERVERINFO_ACK(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const jServerInfo &_si)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_si);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_SS2C_SERVERINFO_ACK;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" SS2C_SERVERINFO_ACK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" SS2C_SERVERINFO_ACK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_CentralServer

}/*nCentralServer */ }/* nNET*/ } //nMech
#endif //CentralServer___SS2C_SERVERINFO_ACK__