
#ifndef WorldServer___DC2W_USER_LOGIN_DUPLICATE_OK__ 
#define WorldServer___DC2W_USER_LOGIN_DUPLICATE_OK__

#ifndef WorldServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_WorldServer(WorldServer);
jxDECL_WorldServer(DC2W_USER_LOGIN_DUPLICATE_OK);
#endif //WorldServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nWorldServer
{
	const int pk_DC2W_USER_LOGIN_DUPLICATE_OK = /*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+18;
	/* wname64_t id;*/
	
	struct S_DC2W_USER_LOGIN_DUPLICATE_OK;
	bool READ_DC2W_USER_LOGIN_DUPLICATE_OK(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DC2W_USER_LOGIN_DUPLICATE_OK &param);
	struct S_DC2W_USER_LOGIN_DUPLICATE_OK
	{
		wname64_t id;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_WorldServer
					void set_id(tcstr sz){jw_strncpy(id,nUNI::scb1024_t(sz).getW(), 64);	id[64-1]=0;}
					tcstr get_id(fname_t _buf){jt_strncpy(_buf, nUNI::scb64_t(id).getT() , 64);_buf[64-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_WorldServer


		#ifndef jNOT_USE_DebugPrint_WorldServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DC2W_USER_LOGIN_DUPLICATE_OK > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("id"),id);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DC2W_USER_LOGIN_DUPLICATE_OK(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_WorldServer
	
	inline bool READ_DC2W_USER_LOGIN_DUPLICATE_OK(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DC2W_USER_LOGIN_DUPLICATE_OK &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.id, 64);
		
		#ifndef jNOT_USE_DebugPrint_WorldServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DC2W_USER_LOGIN_DUPLICATE_OK : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_WorldServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_WorldServer
	inline jPacket_Base WRITE_DC2W_USER_LOGIN_DUPLICATE_OK(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DC2W_USER_LOGIN_DUPLICATE_OK &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.id);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DC2W_USER_LOGIN_DUPLICATE_OK;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC2W_USER_LOGIN_DUPLICATE_OK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC2W_USER_LOGIN_DUPLICATE_OK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DC2W_USER_LOGIN_DUPLICATE_OK(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  wcstr _id)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_id);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DC2W_USER_LOGIN_DUPLICATE_OK;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC2W_USER_LOGIN_DUPLICATE_OK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC2W_USER_LOGIN_DUPLICATE_OK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_WorldServer

}/*nWorldServer */ }/* nNET*/ } //nMech
#endif //WorldServer___DC2W_USER_LOGIN_DUPLICATE_OK__