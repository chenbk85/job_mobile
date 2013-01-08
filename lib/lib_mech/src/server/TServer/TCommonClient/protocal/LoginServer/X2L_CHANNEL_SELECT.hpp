
#ifndef LoginServer___X2L_CHANNEL_SELECT__ 
#define LoginServer___X2L_CHANNEL_SELECT__

#ifndef LoginServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_LoginServer(LoginServer);
jxDECL_LoginServer(X2L_CHANNEL_SELECT);
#endif //LoginServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nLoginServer
{
	const int pk_X2L_CHANNEL_SELECT = /*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+14;
	/* serverid_t sid;*/
	
	struct S_X2L_CHANNEL_SELECT;
	bool READ_X2L_CHANNEL_SELECT(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_X2L_CHANNEL_SELECT &param);
	struct S_X2L_CHANNEL_SELECT
	{
		serverid_t sid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_LoginServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_LoginServer


		#ifndef jNOT_USE_DebugPrint_LoginServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< X2L_CHANNEL_SELECT > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("sid"),sid);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_X2L_CHANNEL_SELECT(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_LoginServer
	
	inline bool READ_X2L_CHANNEL_SELECT(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_X2L_CHANNEL_SELECT &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.sid);
		
		#ifndef jNOT_USE_DebugPrint_LoginServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("X2L_CHANNEL_SELECT : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_LoginServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_LoginServer
	inline jPacket_Base WRITE_X2L_CHANNEL_SELECT(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_X2L_CHANNEL_SELECT &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.sid);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_X2L_CHANNEL_SELECT;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2L_CHANNEL_SELECT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2L_CHANNEL_SELECT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_X2L_CHANNEL_SELECT(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const serverid_t &_sid)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_sid);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_X2L_CHANNEL_SELECT;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2L_CHANNEL_SELECT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2L_CHANNEL_SELECT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_LoginServer

}/*nLoginServer */ }/* nNET*/ } //nMech
#endif //LoginServer___X2L_CHANNEL_SELECT__