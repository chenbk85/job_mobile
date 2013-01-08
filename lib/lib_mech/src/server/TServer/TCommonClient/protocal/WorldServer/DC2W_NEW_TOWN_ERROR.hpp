
#ifndef WorldServer___DC2W_NEW_TOWN_ERROR__ 
#define WorldServer___DC2W_NEW_TOWN_ERROR__

#ifndef WorldServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_WorldServer(WorldServer);
jxDECL_WorldServer(DC2W_NEW_TOWN_ERROR);
#endif //WorldServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nWorldServer
{
	/*[[ DB타운생성실패&#x0A; ]]*/
	const int pk_DC2W_NEW_TOWN_ERROR = /*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+4;
	/* player_id_t pid;*/
	/* Sys_Castle_id_t csid;*/
	/* Sys_TownPos_id_t tpsid;*/
	/* jError e;*/
	
	struct S_DC2W_NEW_TOWN_ERROR;
	bool READ_DC2W_NEW_TOWN_ERROR(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DC2W_NEW_TOWN_ERROR &param);
	struct S_DC2W_NEW_TOWN_ERROR
	{
		player_id_t pid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_WorldServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_WorldServer

		Sys_Castle_id_t csid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_WorldServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_WorldServer

		Sys_TownPos_id_t tpsid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_WorldServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_WorldServer

		jError e;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_WorldServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_WorldServer


		#ifndef jNOT_USE_DebugPrint_WorldServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DC2W_NEW_TOWN_ERROR > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("pid"),pid);
			jDebugPrint(_T("csid"),csid);
			jDebugPrint(_T("tpsid"),tpsid);
			jDebugPrint(_T("e"),e);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DC2W_NEW_TOWN_ERROR(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_WorldServer
	
	inline bool READ_DC2W_NEW_TOWN_ERROR(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DC2W_NEW_TOWN_ERROR &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.pid);
		nStream::Read(st,param.csid);
		nStream::Read(st,param.tpsid);
		nStream::Read(st,param.e);
		
		#ifndef jNOT_USE_DebugPrint_WorldServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DC2W_NEW_TOWN_ERROR : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_WorldServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_WorldServer
	inline jPacket_Base WRITE_DC2W_NEW_TOWN_ERROR(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DC2W_NEW_TOWN_ERROR &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.pid);
			nStream::Write(st,param.csid);
			nStream::Write(st,param.tpsid);
			nStream::Write(st,param.e);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DC2W_NEW_TOWN_ERROR;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC2W_NEW_TOWN_ERROR :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC2W_NEW_TOWN_ERROR :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DC2W_NEW_TOWN_ERROR(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const player_id_t &_pid, const Sys_Castle_id_t &_csid, const Sys_TownPos_id_t &_tpsid, const jError &_e)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_pid);
			nStream::Write(st,_csid);
			nStream::Write(st,_tpsid);
			nStream::Write(st,_e);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DC2W_NEW_TOWN_ERROR;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC2W_NEW_TOWN_ERROR :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC2W_NEW_TOWN_ERROR :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_WorldServer

}/*nWorldServer */ }/* nNET*/ } //nMech
#endif //WorldServer___DC2W_NEW_TOWN_ERROR__