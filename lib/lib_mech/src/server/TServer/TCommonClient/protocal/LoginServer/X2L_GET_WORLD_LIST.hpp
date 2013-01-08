
#ifndef LoginServer___X2L_GET_WORLD_LIST__ 
#define LoginServer___X2L_GET_WORLD_LIST__

#ifndef LoginServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_LoginServer(LoginServer);
jxDECL_LoginServer(X2L_GET_WORLD_LIST);
#endif //LoginServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nLoginServer
{
	const int pk_X2L_GET_WORLD_LIST = /*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+9;
	
	struct S_X2L_GET_WORLD_LIST;
	bool READ_X2L_GET_WORLD_LIST(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_X2L_GET_WORLD_LIST &param);
	struct S_X2L_GET_WORLD_LIST
	{

		#ifndef jNOT_USE_DebugPrint_LoginServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< X2L_GET_WORLD_LIST > ="));
			if(!isPrintAll)return;
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_X2L_GET_WORLD_LIST(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_LoginServer
	
	inline bool READ_X2L_GET_WORLD_LIST(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_X2L_GET_WORLD_LIST &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		
		#ifndef jNOT_USE_DebugPrint_LoginServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("X2L_GET_WORLD_LIST : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_LoginServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_LoginServer
	inline jPacket_Base WRITE_X2L_GET_WORLD_LIST(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_X2L_GET_WORLD_LIST &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_X2L_GET_WORLD_LIST;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2L_GET_WORLD_LIST :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2L_GET_WORLD_LIST :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_X2L_GET_WORLD_LIST(nNET::nStream::_jNetStreamWriteBufferBase &buffer )
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_X2L_GET_WORLD_LIST;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2L_GET_WORLD_LIST :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2L_GET_WORLD_LIST :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_LoginServer

}/*nLoginServer */ }/* nNET*/ } //nMech
#endif //LoginServer___X2L_GET_WORLD_LIST__