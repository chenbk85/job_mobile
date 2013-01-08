
#ifndef UserServer___U2W_USER_LOGIN_DUPLICATE__ 
#define UserServer___U2W_USER_LOGIN_DUPLICATE__

#ifndef UserServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_UserServer(UserServer);
jxDECL_UserServer(U2W_USER_LOGIN_DUPLICATE);
#endif //UserServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nUserServer
{
	const int pk_U2W_USER_LOGIN_DUPLICATE = /*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+15;
	/* wname64_t id;*/
	/* player_id_t pid;*/
	
	struct S_U2W_USER_LOGIN_DUPLICATE;
	bool READ_U2W_USER_LOGIN_DUPLICATE(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_U2W_USER_LOGIN_DUPLICATE &param);
	struct S_U2W_USER_LOGIN_DUPLICATE
	{
		wname64_t id;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_UserServer
					void set_id(tcstr sz){jw_strncpy(id,nUNI::scb1024_t(sz).getW(), 64);	id[64-1]=0;}
					tcstr get_id(fname_t _buf){jt_strncpy(_buf, nUNI::scb64_t(id).getT() , 64);_buf[64-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_UserServer

		player_id_t pid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_UserServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_UserServer


		#ifndef jNOT_USE_DebugPrint_UserServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< U2W_USER_LOGIN_DUPLICATE > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("id"),id);
			jDebugPrint(_T("pid"),pid);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_U2W_USER_LOGIN_DUPLICATE(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_UserServer
	
	inline bool READ_U2W_USER_LOGIN_DUPLICATE(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_U2W_USER_LOGIN_DUPLICATE &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.id, 64);
		nStream::Read(st,param.pid);
		
		#ifndef jNOT_USE_DebugPrint_UserServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("U2W_USER_LOGIN_DUPLICATE : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_UserServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_UserServer
	inline jPacket_Base WRITE_U2W_USER_LOGIN_DUPLICATE(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_U2W_USER_LOGIN_DUPLICATE &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.id);
			nStream::Write(st,param.pid);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_U2W_USER_LOGIN_DUPLICATE;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" U2W_USER_LOGIN_DUPLICATE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" U2W_USER_LOGIN_DUPLICATE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_U2W_USER_LOGIN_DUPLICATE(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  wcstr _id, const player_id_t &_pid)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_id);
			nStream::Write(st,_pid);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_U2W_USER_LOGIN_DUPLICATE;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" U2W_USER_LOGIN_DUPLICATE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" U2W_USER_LOGIN_DUPLICATE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_UserServer

}/*nUserServer */ }/* nNET*/ } //nMech
#endif //UserServer___U2W_USER_LOGIN_DUPLICATE__