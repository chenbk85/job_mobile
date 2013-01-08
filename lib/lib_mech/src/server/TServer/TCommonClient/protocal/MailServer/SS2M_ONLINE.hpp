
#ifndef MailServer___SS2M_ONLINE__ 
#define MailServer___SS2M_ONLINE__

#ifndef MailServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_MailServer(MailServer);
jxDECL_MailServer(SS2M_ONLINE);
#endif //MailServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nMailServer
{
	/*[[ M_HELLO에 대한 응답. ]]*/
	const int pk_SS2M_ONLINE = /*nMech::nNET::EProtocal_jINet_OGS_END+*/7000+2;
	/* serverid_t your_sid;*/
	/*[[ 확인용패킷 ]]*/
	/* jServerInfo my;*/
	
	struct S_SS2M_ONLINE;
	bool READ_SS2M_ONLINE(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_SS2M_ONLINE &param);
	struct S_SS2M_ONLINE
	{
		/*[[ 확인용패킷 ]]*/
		serverid_t your_sid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_MailServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_MailServer

		jServerInfo my;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_MailServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_MailServer


		#ifndef jNOT_USE_DebugPrint_MailServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< SS2M_ONLINE > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("your_sid"),your_sid);
			jDebugPrint(_T("my"),my);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_SS2M_ONLINE(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_MailServer
	
	inline bool READ_SS2M_ONLINE(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_SS2M_ONLINE &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.your_sid);
		/*	[[ 확인용패킷 ]]*/
		nStream::Read(st,param.my);
		
		#ifndef jNOT_USE_DebugPrint_MailServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("SS2M_ONLINE : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_MailServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_MailServer
	inline jPacket_Base WRITE_SS2M_ONLINE(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_SS2M_ONLINE &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.your_sid);
			/*[[ 확인용패킷 ]]*/
			nStream::Write(st,param.my);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_SS2M_ONLINE;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" SS2M_ONLINE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" SS2M_ONLINE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_SS2M_ONLINE(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const serverid_t &_your_sid, const jServerInfo &_my)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_your_sid);
			/*[[ 확인용패킷 ]]*/
			nStream::Write(st,_my);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_SS2M_ONLINE;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" SS2M_ONLINE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" SS2M_ONLINE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_MailServer

}/*nMailServer */ }/* nNET*/ } //nMech
#endif //MailServer___SS2M_ONLINE__