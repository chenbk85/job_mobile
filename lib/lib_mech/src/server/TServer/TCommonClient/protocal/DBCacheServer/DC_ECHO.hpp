
#ifndef DBCacheServer___DC_ECHO__ 
#define DBCacheServer___DC_ECHO__

#ifndef DBCacheServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DBCacheServer(DBCacheServer);
jxDECL_DBCacheServer(DC_ECHO);
#endif //DBCacheServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nDBCacheServer
{
	const int pk_DC_ECHO = /*nMech::nNET::EProtocal_jINet_OGS_END+*/6000+8;
	/* tname256_t msg;*/
	/* int8 type;*/
	
	struct S_DC_ECHO;
	bool READ_DC_ECHO(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DC_ECHO &param);
	struct S_DC_ECHO
	{
		tname256_t msg;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer
					void set_msg(tcstr sz){jt_strncpy(msg,nUNI::scb1024_t(sz).getT(), 256);	msg[256-1]=0;}
					tcstr get_msg(fname_t _buf){jt_strncpy(_buf, nUNI::scb256_t(msg).getT() , 256);_buf[256-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer

		int8 type;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer


		#ifndef jNOT_USE_DebugPrint_DBCacheServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DC_ECHO > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("msg"),msg);
			jDebugPrint(_T("type"),type);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DC_ECHO(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_DBCacheServer
	
	inline bool READ_DC_ECHO(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DC_ECHO &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.msg, 256);
		nStream::Read(st,param.type);
		
		#ifndef jNOT_USE_DebugPrint_DBCacheServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DC_ECHO : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_DBCacheServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_DBCacheServer
	inline jPacket_Base WRITE_DC_ECHO(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DC_ECHO &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.msg);
			nStream::Write(st,param.type);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DC_ECHO;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC_ECHO :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC_ECHO :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DC_ECHO(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  tcstr _msg, const int8 &_type)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_msg);
			nStream::Write(st,_type);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DC_ECHO;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC_ECHO :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC_ECHO :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_DBCacheServer

}/*nDBCacheServer */ }/* nNET*/ } //nMech
#endif //DBCacheServer___DC_ECHO__