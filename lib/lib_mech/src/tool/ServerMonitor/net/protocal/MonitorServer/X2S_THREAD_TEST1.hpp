
#ifndef MonitorServer___X2S_THREAD_TEST1__ 
#define MonitorServer___X2S_THREAD_TEST1__

#ifndef MonitorServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_MonitorServer(MonitorServer);
jxDECL_MonitorServer(X2S_THREAD_TEST1);
#endif //MonitorServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nMonitorServer
{
	const int pk_X2S_THREAD_TEST1 = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+6;
	/* uint8 type;*/
	/* wstring msg;*/
	
	struct S_X2S_THREAD_TEST1;
	bool READ_X2S_THREAD_TEST1(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_X2S_THREAD_TEST1 &param);
	struct S_X2S_THREAD_TEST1
	{
		uint8 type;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer

		wstring msg;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer


		#ifndef jNOT_USE_DebugPrint_MonitorServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< X2S_THREAD_TEST1 > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("type"),type);
			jDebugPrint(_T("msg"),msg);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_X2S_THREAD_TEST1(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_MonitorServer
	
	inline bool READ_X2S_THREAD_TEST1(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_X2S_THREAD_TEST1 &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.type);
		nStream::Read(st,param.msg);
		
		#ifndef jNOT_USE_DebugPrint_MonitorServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("X2S_THREAD_TEST1 : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_MonitorServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_MonitorServer
	inline jPacket_Base WRITE_X2S_THREAD_TEST1(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_X2S_THREAD_TEST1 &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.type);
			nStream::Write(st,param.msg);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_X2S_THREAD_TEST1;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2S_THREAD_TEST1 :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2S_THREAD_TEST1 :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_X2S_THREAD_TEST1(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const uint8 &_type, const wstring &_msg)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_type);
			nStream::Write(st,_msg);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_X2S_THREAD_TEST1;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2S_THREAD_TEST1 :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2S_THREAD_TEST1 :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_MonitorServer

}/*nMonitorServer */ }/* nNET*/ } //nMech
#endif //MonitorServer___X2S_THREAD_TEST1__