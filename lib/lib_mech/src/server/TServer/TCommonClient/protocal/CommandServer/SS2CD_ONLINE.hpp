
#ifndef CommandServer___SS2CD_ONLINE__ 
#define CommandServer___SS2CD_ONLINE__

#ifndef CommandServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_CommandServer(CommandServer);
jxDECL_CommandServer(SS2CD_ONLINE);
#endif //CommandServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nCommandServer
{
	/*[[ 어떤 서버가 CommandServer에 접속했다.	
만약 CentralServer가 죽었고 si.m_sid==0이면 &#x0A;Command가 sid를 발급해준다. ]]*/
	const int pk_SS2CD_ONLINE = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1500+2;
	/* serverid_t your_sid;*/
	/* jServerInfo my;*/
	
	struct S_SS2CD_ONLINE;
	bool READ_SS2CD_ONLINE(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_SS2CD_ONLINE &param);
	struct S_SS2CD_ONLINE
	{
		serverid_t your_sid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_CommandServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_CommandServer

		jServerInfo my;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_CommandServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_CommandServer


		#ifndef jNOT_USE_DebugPrint_CommandServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< SS2CD_ONLINE > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("your_sid"),your_sid);
			jDebugPrint(_T("my"),my);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_SS2CD_ONLINE(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_CommandServer
	
	inline bool READ_SS2CD_ONLINE(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_SS2CD_ONLINE &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.your_sid);
		nStream::Read(st,param.my);
		
		#ifndef jNOT_USE_DebugPrint_CommandServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("SS2CD_ONLINE : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_CommandServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_CommandServer
	inline jPacket_Base WRITE_SS2CD_ONLINE(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_SS2CD_ONLINE &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.your_sid);
			nStream::Write(st,param.my);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_SS2CD_ONLINE;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" SS2CD_ONLINE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" SS2CD_ONLINE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_SS2CD_ONLINE(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const serverid_t &_your_sid, const jServerInfo &_my)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_your_sid);
			nStream::Write(st,_my);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_SS2CD_ONLINE;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" SS2CD_ONLINE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" SS2CD_ONLINE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_CommandServer

}/*nCommandServer */ }/* nNET*/ } //nMech
#endif //CommandServer___SS2CD_ONLINE__