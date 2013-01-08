
#ifndef UserServer___L2U_USER_LOGIN__ 
#define UserServer___L2U_USER_LOGIN__

#ifndef UserServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_UserServer(UserServer);
jxDECL_UserServer(L2U_USER_LOGIN);
#endif //UserServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nUserServer
{
	const int pk_L2U_USER_LOGIN = /*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+11;
	/* serverid_t world;*/
	/* wname64_t id;*/
	
	struct S_L2U_USER_LOGIN;
	bool READ_L2U_USER_LOGIN(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_L2U_USER_LOGIN &param);
	struct S_L2U_USER_LOGIN
	{
		serverid_t world;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_UserServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_UserServer

		wname64_t id;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_UserServer
					void set_id(tcstr sz){jw_strncpy(id,nUNI::scb1024_t(sz).getW(), 64);	id[64-1]=0;}
					tcstr get_id(fname_t _buf){jt_strncpy(_buf, nUNI::scb64_t(id).getT() , 64);_buf[64-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_UserServer


		#ifndef jNOT_USE_DebugPrint_UserServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< L2U_USER_LOGIN > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("world"),world);
			jDebugPrint(_T("id"),id);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_L2U_USER_LOGIN(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_UserServer
	
	inline bool READ_L2U_USER_LOGIN(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_L2U_USER_LOGIN &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.world);
		nStream::Read(st,param.id, 64);
		
		#ifndef jNOT_USE_DebugPrint_UserServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("L2U_USER_LOGIN : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_UserServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_UserServer
	inline jPacket_Base WRITE_L2U_USER_LOGIN(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_L2U_USER_LOGIN &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.world);
			nStream::Write(st,param.id);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_L2U_USER_LOGIN;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" L2U_USER_LOGIN :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" L2U_USER_LOGIN :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_L2U_USER_LOGIN(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const serverid_t &_world,  wcstr _id)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_world);
			nStream::Write(st,_id);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_L2U_USER_LOGIN;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" L2U_USER_LOGIN :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" L2U_USER_LOGIN :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_UserServer

}/*nUserServer */ }/* nNET*/ } //nMech
#endif //UserServer___L2U_USER_LOGIN__