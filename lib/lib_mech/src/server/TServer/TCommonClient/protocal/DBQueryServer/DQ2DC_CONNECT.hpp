
#ifndef DBQueryServer___DQ2DC_CONNECT__ 
#define DBQueryServer___DQ2DC_CONNECT__

#ifndef DBQueryServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DBQueryServer(DBQueryServer);
jxDECL_DBQueryServer(DQ2DC_CONNECT);
#endif //DBQueryServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nDBQueryServer
{
	const int pk_DQ2DC_CONNECT = /*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+11;
	/* tname32_t WORLD_NAME;*/
	/* tname32_t SM_QUERY2CACHE_NAME;*/
	/* tname32_t SM_CACHE2QUERY_NAME;*/
	/* tname32_t SM_USER_INFO_NAME;*/
	/* tname32_t GAMEDB_NAME;*/
	/* uint32 processid;*/
	
	struct S_DQ2DC_CONNECT;
	bool READ_DQ2DC_CONNECT(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DQ2DC_CONNECT &param);
	struct S_DQ2DC_CONNECT
	{
		tname32_t WORLD_NAME;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer
					void set_WORLD_NAME(tcstr sz){jt_strncpy(WORLD_NAME,nUNI::scb1024_t(sz).getT(), 32);	WORLD_NAME[32-1]=0;}
					tcstr get_WORLD_NAME(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(WORLD_NAME).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer

		tname32_t SM_QUERY2CACHE_NAME;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer
					void set_SM_QUERY2CACHE_NAME(tcstr sz){jt_strncpy(SM_QUERY2CACHE_NAME,nUNI::scb1024_t(sz).getT(), 32);	SM_QUERY2CACHE_NAME[32-1]=0;}
					tcstr get_SM_QUERY2CACHE_NAME(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(SM_QUERY2CACHE_NAME).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer

		tname32_t SM_CACHE2QUERY_NAME;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer
					void set_SM_CACHE2QUERY_NAME(tcstr sz){jt_strncpy(SM_CACHE2QUERY_NAME,nUNI::scb1024_t(sz).getT(), 32);	SM_CACHE2QUERY_NAME[32-1]=0;}
					tcstr get_SM_CACHE2QUERY_NAME(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(SM_CACHE2QUERY_NAME).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer

		tname32_t SM_USER_INFO_NAME;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer
					void set_SM_USER_INFO_NAME(tcstr sz){jt_strncpy(SM_USER_INFO_NAME,nUNI::scb1024_t(sz).getT(), 32);	SM_USER_INFO_NAME[32-1]=0;}
					tcstr get_SM_USER_INFO_NAME(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(SM_USER_INFO_NAME).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer

		tname32_t GAMEDB_NAME;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer
					void set_GAMEDB_NAME(tcstr sz){jt_strncpy(GAMEDB_NAME,nUNI::scb1024_t(sz).getT(), 32);	GAMEDB_NAME[32-1]=0;}
					tcstr get_GAMEDB_NAME(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(GAMEDB_NAME).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer

		uint32 processid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer


		#ifndef jNOT_USE_DebugPrint_DBQueryServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DQ2DC_CONNECT > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("WORLD_NAME"),WORLD_NAME);
			jDebugPrint(_T("SM_QUERY2CACHE_NAME"),SM_QUERY2CACHE_NAME);
			jDebugPrint(_T("SM_CACHE2QUERY_NAME"),SM_CACHE2QUERY_NAME);
			jDebugPrint(_T("SM_USER_INFO_NAME"),SM_USER_INFO_NAME);
			jDebugPrint(_T("GAMEDB_NAME"),GAMEDB_NAME);
			jDebugPrint(_T("processid"),processid);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DQ2DC_CONNECT(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_DBQueryServer
	
	inline bool READ_DQ2DC_CONNECT(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DQ2DC_CONNECT &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.WORLD_NAME, 32);
		nStream::Read(st,param.SM_QUERY2CACHE_NAME, 32);
		nStream::Read(st,param.SM_CACHE2QUERY_NAME, 32);
		nStream::Read(st,param.SM_USER_INFO_NAME, 32);
		nStream::Read(st,param.GAMEDB_NAME, 32);
		nStream::Read(st,param.processid);
		
		#ifndef jNOT_USE_DebugPrint_DBQueryServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DQ2DC_CONNECT : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_DBQueryServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_DBQueryServer
	inline jPacket_Base WRITE_DQ2DC_CONNECT(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DQ2DC_CONNECT &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.WORLD_NAME);
			nStream::Write(st,param.SM_QUERY2CACHE_NAME);
			nStream::Write(st,param.SM_CACHE2QUERY_NAME);
			nStream::Write(st,param.SM_USER_INFO_NAME);
			nStream::Write(st,param.GAMEDB_NAME);
			nStream::Write(st,param.processid);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DQ2DC_CONNECT;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DQ2DC_CONNECT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DQ2DC_CONNECT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DQ2DC_CONNECT(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  tcstr _WORLD_NAME,  tcstr _SM_QUERY2CACHE_NAME,  tcstr _SM_CACHE2QUERY_NAME,  tcstr _SM_USER_INFO_NAME,  tcstr _GAMEDB_NAME, const uint32 &_processid)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_WORLD_NAME);
			nStream::Write(st,_SM_QUERY2CACHE_NAME);
			nStream::Write(st,_SM_CACHE2QUERY_NAME);
			nStream::Write(st,_SM_USER_INFO_NAME);
			nStream::Write(st,_GAMEDB_NAME);
			nStream::Write(st,_processid);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DQ2DC_CONNECT;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DQ2DC_CONNECT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DQ2DC_CONNECT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_DBQueryServer

}/*nDBQueryServer */ }/* nNET*/ } //nMech
#endif //DBQueryServer___DQ2DC_CONNECT__