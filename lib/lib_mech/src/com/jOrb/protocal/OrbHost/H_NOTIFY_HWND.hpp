
#ifndef OrbHost___H_NOTIFY_HWND__ 
#define OrbHost___H_NOTIFY_HWND__

#ifndef OrbHost_jNOTUSE_PACKET_JXDEFINE
jxDECL_OrbHost(OrbHost);
jxDECL_OrbHost(H_NOTIFY_HWND);
#endif //OrbHost_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nOrbHost
{
	const int pk_H_NOTIFY_HWND = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+9;
	/* uint32 hWnd;*/
	
	struct S_H_NOTIFY_HWND;
	bool READ_H_NOTIFY_HWND(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_H_NOTIFY_HWND &param);
	struct S_H_NOTIFY_HWND
	{
		uint32 hWnd;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_OrbHost
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_OrbHost


		#ifndef jNOT_USE_DebugPrint_OrbHost
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< H_NOTIFY_HWND > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("hWnd"),hWnd);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_H_NOTIFY_HWND(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_OrbHost
	
	inline bool READ_H_NOTIFY_HWND(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_H_NOTIFY_HWND &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.hWnd);
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("H_NOTIFY_HWND : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_OrbHost

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_OrbHost
	inline jPacket_Base WRITE_H_NOTIFY_HWND(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_H_NOTIFY_HWND &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.hWnd);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_H_NOTIFY_HWND;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" H_NOTIFY_HWND :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" H_NOTIFY_HWND :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_H_NOTIFY_HWND(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const uint32 &_hWnd)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_hWnd);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_H_NOTIFY_HWND;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" H_NOTIFY_HWND :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" H_NOTIFY_HWND :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_OrbHost

}/*nOrbHost */ }/* nNET*/ } //nMech
#endif //OrbHost___H_NOTIFY_HWND__