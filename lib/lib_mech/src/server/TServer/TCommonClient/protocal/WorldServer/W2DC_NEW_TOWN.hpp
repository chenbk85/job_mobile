
#ifndef WorldServer___W2DC_NEW_TOWN__ 
#define WorldServer___W2DC_NEW_TOWN__

#ifndef WorldServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_WorldServer(WorldServer);
jxDECL_WorldServer(W2DC_NEW_TOWN);
#endif //WorldServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nWorldServer
{
	/*[[ 선택된성에서 랜덤하게 마을선택	
사용하지 않는 Sys_TownPos_id_t를 결정 ]]*/
	const int pk_W2DC_NEW_TOWN = /*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+3;
	/* player_id_t pid;*/
	/* Sys_Castle_id_t csid;*/
	/* Sys_TownPos_id_t tpsid;*/
	/* wname32_t name;*/
	
	struct S_W2DC_NEW_TOWN;
	bool READ_W2DC_NEW_TOWN(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_W2DC_NEW_TOWN &param);
	struct S_W2DC_NEW_TOWN
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

		wname32_t name;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_WorldServer
					void set_name(tcstr sz){jw_strncpy(name,nUNI::scb1024_t(sz).getW(), 32);	name[32-1]=0;}
					tcstr get_name(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(name).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_WorldServer


		#ifndef jNOT_USE_DebugPrint_WorldServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< W2DC_NEW_TOWN > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("pid"),pid);
			jDebugPrint(_T("csid"),csid);
			jDebugPrint(_T("tpsid"),tpsid);
			jDebugPrint(_T("name"),name);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_W2DC_NEW_TOWN(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_WorldServer
	
	inline bool READ_W2DC_NEW_TOWN(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_W2DC_NEW_TOWN &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.pid);
		nStream::Read(st,param.csid);
		nStream::Read(st,param.tpsid);
		nStream::Read(st,param.name, 32);
		
		#ifndef jNOT_USE_DebugPrint_WorldServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("W2DC_NEW_TOWN : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_WorldServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_WorldServer
	inline jPacket_Base WRITE_W2DC_NEW_TOWN(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_W2DC_NEW_TOWN &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.pid);
			nStream::Write(st,param.csid);
			nStream::Write(st,param.tpsid);
			nStream::Write(st,param.name);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_W2DC_NEW_TOWN;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" W2DC_NEW_TOWN :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" W2DC_NEW_TOWN :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_W2DC_NEW_TOWN(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const player_id_t &_pid, const Sys_Castle_id_t &_csid, const Sys_TownPos_id_t &_tpsid,  wcstr _name)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_pid);
			nStream::Write(st,_csid);
			nStream::Write(st,_tpsid);
			nStream::Write(st,_name);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_W2DC_NEW_TOWN;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" W2DC_NEW_TOWN :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" W2DC_NEW_TOWN :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_WorldServer

}/*nWorldServer */ }/* nNET*/ } //nMech
#endif //WorldServer___W2DC_NEW_TOWN__