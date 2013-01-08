
#ifndef GameServer___D_ECHO__ 
#define GameServer___D_ECHO__

#ifndef GameServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_GameServer(GameServer);
jxDECL_GameServer(D_ECHO);
#endif //GameServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nGameServer
{
	const int pk_D_ECHO = /*nMech::nNET::EProtocal_jINet_OGS_END+*/3000+6;
	
	struct S_D_ECHO;
	bool READ_D_ECHO(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_D_ECHO &param);
	struct S_D_ECHO
	{

		#ifndef jNOT_USE_DebugPrint_GameServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< D_ECHO > ="));
			if(!isPrintAll)return;
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_D_ECHO(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_GameServer
	
	inline bool READ_D_ECHO(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_D_ECHO &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		
		#ifndef jNOT_USE_DebugPrint_GameServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("D_ECHO : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_GameServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_GameServer
	inline jPacket_Base WRITE_D_ECHO(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_D_ECHO &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_D_ECHO;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" D_ECHO :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" D_ECHO :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_D_ECHO(nNET::nStream::_jNetStreamWriteBufferBase &buffer )
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_D_ECHO;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" D_ECHO :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" D_ECHO :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_GameServer

}/*nGameServer */ }/* nNET*/ } //nMech
#endif //GameServer___D_ECHO__