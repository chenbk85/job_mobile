
#ifndef WorldServer___DC2W_TOWN_DELETE_OK__ 
#define WorldServer___DC2W_TOWN_DELETE_OK__

#ifndef WorldServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_WorldServer(WorldServer);
jxDECL_WorldServer(DC2W_TOWN_DELETE_OK);
#endif //WorldServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nWorldServer
{
	const int pk_DC2W_TOWN_DELETE_OK = /*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+5;
	/* wname64_t user;*/
	/* Sys_Castle_id_t csid;*/
	/* Sys_TownPos_id_t tp;*/
	
	struct S_DC2W_TOWN_DELETE_OK;
	bool READ_DC2W_TOWN_DELETE_OK(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DC2W_TOWN_DELETE_OK &param);
	struct S_DC2W_TOWN_DELETE_OK
	{
		wname64_t user;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_WorldServer
					void set_user(tcstr sz){jw_strncpy(user,nUNI::scb1024_t(sz).getW(), 64);	user[64-1]=0;}
					tcstr get_user(fname_t _buf){jt_strncpy(_buf, nUNI::scb64_t(user).getT() , 64);_buf[64-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_WorldServer

		Sys_Castle_id_t csid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_WorldServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_WorldServer

		Sys_TownPos_id_t tp;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_WorldServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_WorldServer


		#ifndef jNOT_USE_DebugPrint_WorldServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DC2W_TOWN_DELETE_OK > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("user"),user);
			jDebugPrint(_T("csid"),csid);
			jDebugPrint(_T("tp"),tp);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DC2W_TOWN_DELETE_OK(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_WorldServer
	
	inline bool READ_DC2W_TOWN_DELETE_OK(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DC2W_TOWN_DELETE_OK &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.user, 64);
		nStream::Read(st,param.csid);
		nStream::Read(st,param.tp);
		
		#ifndef jNOT_USE_DebugPrint_WorldServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DC2W_TOWN_DELETE_OK : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_WorldServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_WorldServer
	inline jPacket_Base WRITE_DC2W_TOWN_DELETE_OK(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DC2W_TOWN_DELETE_OK &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.user);
			nStream::Write(st,param.csid);
			nStream::Write(st,param.tp);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DC2W_TOWN_DELETE_OK;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC2W_TOWN_DELETE_OK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC2W_TOWN_DELETE_OK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DC2W_TOWN_DELETE_OK(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  wcstr _user, const Sys_Castle_id_t &_csid, const Sys_TownPos_id_t &_tp)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_user);
			nStream::Write(st,_csid);
			nStream::Write(st,_tp);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DC2W_TOWN_DELETE_OK;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC2W_TOWN_DELETE_OK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC2W_TOWN_DELETE_OK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_WorldServer

}/*nWorldServer */ }/* nNET*/ } //nMech
#endif //WorldServer___DC2W_TOWN_DELETE_OK__