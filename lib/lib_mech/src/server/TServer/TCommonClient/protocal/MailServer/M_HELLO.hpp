
#ifndef MailServer___M_HELLO__ 
#define MailServer___M_HELLO__

#ifndef MailServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_MailServer(MailServer);
jxDECL_MailServer(M_HELLO);
#endif //MailServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nMailServer
{
	const int pk_M_HELLO = /*nMech::nNET::EProtocal_jINet_OGS_END+*/7000+1;
	/* jServerInfo si;*/
	
	struct S_M_HELLO;
	bool READ_M_HELLO(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_M_HELLO &param);
	struct S_M_HELLO
	{
		jServerInfo si;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_MailServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_MailServer


		#ifndef jNOT_USE_DebugPrint_MailServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< M_HELLO > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("si"),si);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_M_HELLO(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_MailServer
	
	inline bool READ_M_HELLO(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_M_HELLO &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.si);
		
		#ifndef jNOT_USE_DebugPrint_MailServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("M_HELLO : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_MailServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_MailServer
	inline jPacket_Base WRITE_M_HELLO(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_M_HELLO &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.si);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_M_HELLO;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" M_HELLO :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" M_HELLO :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_M_HELLO(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const jServerInfo &_si)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_si);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_M_HELLO;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" M_HELLO :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" M_HELLO :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_MailServer

}/*nMailServer */ }/* nNET*/ } //nMech
#endif //MailServer___M_HELLO__