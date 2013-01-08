
#ifndef DBQueryServer___DC2DQ_USER_LOGIN__ 
#define DBQueryServer___DC2DQ_USER_LOGIN__

#ifndef DBQueryServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DBQueryServer(DBQueryServer);
jxDECL_DBQueryServer(DC2DQ_USER_LOGIN);
#endif //DBQueryServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nDBQueryServer
{
	const int pk_DC2DQ_USER_LOGIN = /*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+14;
	/* player_id_t pid;*/
	
	struct S_DC2DQ_USER_LOGIN;
	bool READ_DC2DQ_USER_LOGIN(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DC2DQ_USER_LOGIN &param);
	struct S_DC2DQ_USER_LOGIN
	{
		player_id_t pid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer


		#ifndef jNOT_USE_DebugPrint_DBQueryServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DC2DQ_USER_LOGIN > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("pid"),pid);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DC2DQ_USER_LOGIN(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_DBQueryServer
	
	inline bool READ_DC2DQ_USER_LOGIN(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DC2DQ_USER_LOGIN &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.pid);
		
		#ifndef jNOT_USE_DebugPrint_DBQueryServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DC2DQ_USER_LOGIN : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_DBQueryServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_DBQueryServer
	inline jPacket_Base WRITE_DC2DQ_USER_LOGIN(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DC2DQ_USER_LOGIN &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.pid);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DC2DQ_USER_LOGIN;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC2DQ_USER_LOGIN :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC2DQ_USER_LOGIN :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DC2DQ_USER_LOGIN(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const player_id_t &_pid)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_pid);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DC2DQ_USER_LOGIN;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC2DQ_USER_LOGIN :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC2DQ_USER_LOGIN :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_DBQueryServer

}/*nDBQueryServer */ }/* nNET*/ } //nMech
#endif //DBQueryServer___DC2DQ_USER_LOGIN__