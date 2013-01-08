
#ifndef UserServer___U_HELLO__ 
#define UserServer___U_HELLO__

#ifndef UserServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_UserServer(UserServer);
jxDECL_UserServer(U_HELLO);
#endif //UserServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nUserServer
{
	const int pk_U_HELLO = /*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+2;
	/* jServerInfo si;*/
	
	struct S_U_HELLO;
	bool READ_U_HELLO(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_U_HELLO &param);
	struct S_U_HELLO
	{
		jServerInfo si;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_UserServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_UserServer


		#ifndef jNOT_USE_DebugPrint_UserServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< U_HELLO > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("si"),si);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_U_HELLO(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_UserServer
	
	inline bool READ_U_HELLO(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_U_HELLO &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.si);
		
		#ifndef jNOT_USE_DebugPrint_UserServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("U_HELLO : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_UserServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_UserServer
	inline jPacket_Base WRITE_U_HELLO(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_U_HELLO &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.si);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_U_HELLO;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" U_HELLO :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" U_HELLO :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_U_HELLO(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const jServerInfo &_si)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_si);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_U_HELLO;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" U_HELLO :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" U_HELLO :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_UserServer

}/*nUserServer */ }/* nNET*/ } //nMech
#endif //UserServer___U_HELLO__