
#ifndef CentralServer___C4_USER_CONNECTION_NOTIFY__ 
#define CentralServer___C4_USER_CONNECTION_NOTIFY__

#ifndef CentralServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_CentralServer(CentralServer);
jxDECL_CentralServer(C4_USER_CONNECTION_NOTIFY);
#endif //CentralServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nCentralServer
{
	/*[[ 6초정도의 딜레이후 보낸다. ]]*/
	const int pk_C4_USER_CONNECTION_NOTIFY = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+12;
	/* uint16 userCnt;*/
	
	struct S_C4_USER_CONNECTION_NOTIFY;
	bool READ_C4_USER_CONNECTION_NOTIFY(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_C4_USER_CONNECTION_NOTIFY &param);
	struct S_C4_USER_CONNECTION_NOTIFY
	{
		uint16 userCnt;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_CentralServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_CentralServer


		#ifndef jNOT_USE_DebugPrint_CentralServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< C4_USER_CONNECTION_NOTIFY > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("userCnt"),userCnt);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_C4_USER_CONNECTION_NOTIFY(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_CentralServer
	
	inline bool READ_C4_USER_CONNECTION_NOTIFY(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_C4_USER_CONNECTION_NOTIFY &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.userCnt);
		
		#ifndef jNOT_USE_DebugPrint_CentralServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("C4_USER_CONNECTION_NOTIFY : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_CentralServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_CentralServer
	inline jPacket_Base WRITE_C4_USER_CONNECTION_NOTIFY(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_C4_USER_CONNECTION_NOTIFY &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.userCnt);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_C4_USER_CONNECTION_NOTIFY;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" C4_USER_CONNECTION_NOTIFY :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" C4_USER_CONNECTION_NOTIFY :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_C4_USER_CONNECTION_NOTIFY(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const uint16 &_userCnt)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_userCnt);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_C4_USER_CONNECTION_NOTIFY;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" C4_USER_CONNECTION_NOTIFY :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" C4_USER_CONNECTION_NOTIFY :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_CentralServer

}/*nCentralServer */ }/* nNET*/ } //nMech
#endif //CentralServer___C4_USER_CONNECTION_NOTIFY__