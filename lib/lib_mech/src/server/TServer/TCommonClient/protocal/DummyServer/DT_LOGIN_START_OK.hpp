
#ifndef DummyServer___DT_LOGIN_START_OK__ 
#define DummyServer___DT_LOGIN_START_OK__

#ifndef DummyServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DummyServer(DummyServer);
jxDECL_DummyServer(DT_LOGIN_START_OK);
#endif //DummyServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nDummyServer
{
	const int pk_DT_LOGIN_START_OK = /*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+8;
	/* uint32 process_msec;*/
	/* aname32_t user_id;*/
	/* CHAR lobby_ip[32];*/
	
	struct S_DT_LOGIN_START_OK;
	bool READ_DT_LOGIN_START_OK(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DT_LOGIN_START_OK &param);
	struct S_DT_LOGIN_START_OK
	{
		uint32 process_msec;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DummyServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DummyServer

		aname32_t user_id;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DummyServer
					void set_user_id(tcstr sz){ja_strncpy(user_id,nUNI::scb1024_t(sz).getA(), 32);	user_id[32-1]=0;}
					tcstr get_user_id(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(user_id).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DummyServer

		CHAR lobby_ip[32];
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DummyServer
		tcstr 	get_lobby_ip(){ static TCHAR buf[32];jt_strcpy(buf,nUNI::scb1024_t(lobby_ip).getT()); return buf;}
		void 	set_lobby_ip(tcstr sz){ ja_strcpy(lobby_ip,nUNI::scb1024_t(sz).getA());}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DummyServer


		#ifndef jNOT_USE_DebugPrint_DummyServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DT_LOGIN_START_OK > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("process_msec"),process_msec);
			jDebugPrint(_T("user_id"),user_id);
			jDebugPrint(_T("lobby_ip"),lobby_ip);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DT_LOGIN_START_OK(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_DummyServer
	
	inline bool READ_DT_LOGIN_START_OK(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DT_LOGIN_START_OK &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.process_msec);
		nStream::Read(st,param.user_id, 32);
		nStream::Read(st,param.lobby_ip, 32);
		
		#ifndef jNOT_USE_DebugPrint_DummyServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DT_LOGIN_START_OK : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_DummyServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_DummyServer
	inline jPacket_Base WRITE_DT_LOGIN_START_OK(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DT_LOGIN_START_OK &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.process_msec);
			nStream::Write(st,param.user_id);
			nStream::Write(st,param.lobby_ip);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DT_LOGIN_START_OK;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DT_LOGIN_START_OK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DT_LOGIN_START_OK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DT_LOGIN_START_OK(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const uint32 &_process_msec,  acstr _user_id, const CHAR *_lobby_ip)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_process_msec);
			nStream::Write(st,_user_id);
			nStream::Write(st,_lobby_ip);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DT_LOGIN_START_OK;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DT_LOGIN_START_OK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DT_LOGIN_START_OK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_DummyServer

}/*nDummyServer */ }/* nNET*/ } //nMech
#endif //DummyServer___DT_LOGIN_START_OK__