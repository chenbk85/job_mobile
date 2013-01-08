
#ifndef OrbHost___ORB_IS_ALIVE__ 
#define OrbHost___ORB_IS_ALIVE__

#ifndef OrbHost_jNOTUSE_PACKET_JXDEFINE
jxDECL_OrbHost(OrbHost);
jxDECL_OrbHost(ORB_IS_ALIVE);
#endif //OrbHost_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nOrbHost
{
	const int pk_ORB_IS_ALIVE = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+6;
	
	struct S_ORB_IS_ALIVE;
	bool READ_ORB_IS_ALIVE(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_ORB_IS_ALIVE &param);
	struct S_ORB_IS_ALIVE
	{

		#ifndef jNOT_USE_DebugPrint_OrbHost
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< ORB_IS_ALIVE > ="));
			if(!isPrintAll)return;
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_ORB_IS_ALIVE(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_OrbHost
	
	inline bool READ_ORB_IS_ALIVE(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_ORB_IS_ALIVE &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("ORB_IS_ALIVE : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_OrbHost

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_OrbHost
	inline jPacket_Base WRITE_ORB_IS_ALIVE(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_ORB_IS_ALIVE &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_ORB_IS_ALIVE;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" ORB_IS_ALIVE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" ORB_IS_ALIVE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_ORB_IS_ALIVE(nNET::nStream::_jNetStreamWriteBufferBase &buffer )
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_ORB_IS_ALIVE;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" ORB_IS_ALIVE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" ORB_IS_ALIVE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_OrbHost

}/*nOrbHost */ }/* nNET*/ } //nMech
#endif //OrbHost___ORB_IS_ALIVE__