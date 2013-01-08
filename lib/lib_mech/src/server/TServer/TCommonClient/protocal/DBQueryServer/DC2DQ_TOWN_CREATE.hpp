
#ifndef DBQueryServer___DC2DQ_TOWN_CREATE__ 
#define DBQueryServer___DC2DQ_TOWN_CREATE__

#ifndef DBQueryServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DBQueryServer(DBQueryServer);
jxDECL_DBQueryServer(DC2DQ_TOWN_CREATE);
#endif //DBQueryServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nDBQueryServer
{
	const int pk_DC2DQ_TOWN_CREATE = /*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+4;
	/* player_id_t pid;*/
	/* Sys_Castle_id_t csid;*/
	/* Sys_TownPos_id_t tpsid;*/
	/* wname32_t name;*/
	
	struct S_DC2DQ_TOWN_CREATE;
	bool READ_DC2DQ_TOWN_CREATE(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DC2DQ_TOWN_CREATE &param);
	struct S_DC2DQ_TOWN_CREATE
	{
		player_id_t pid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer

		Sys_Castle_id_t csid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer

		Sys_TownPos_id_t tpsid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer

		wname32_t name;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer
					void set_name(tcstr sz){jw_strncpy(name,nUNI::scb1024_t(sz).getW(), 32);	name[32-1]=0;}
					tcstr get_name(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(name).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer


		#ifndef jNOT_USE_DebugPrint_DBQueryServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DC2DQ_TOWN_CREATE > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("pid"),pid);
			jDebugPrint(_T("csid"),csid);
			jDebugPrint(_T("tpsid"),tpsid);
			jDebugPrint(_T("name"),name);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DC2DQ_TOWN_CREATE(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_DBQueryServer
	
	inline bool READ_DC2DQ_TOWN_CREATE(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DC2DQ_TOWN_CREATE &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.pid);
		nStream::Read(st,param.csid);
		nStream::Read(st,param.tpsid);
		nStream::Read(st,param.name, 32);
		
		#ifndef jNOT_USE_DebugPrint_DBQueryServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DC2DQ_TOWN_CREATE : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_DBQueryServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_DBQueryServer
	inline jPacket_Base WRITE_DC2DQ_TOWN_CREATE(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DC2DQ_TOWN_CREATE &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.pid);
			nStream::Write(st,param.csid);
			nStream::Write(st,param.tpsid);
			nStream::Write(st,param.name);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DC2DQ_TOWN_CREATE;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC2DQ_TOWN_CREATE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC2DQ_TOWN_CREATE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DC2DQ_TOWN_CREATE(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const player_id_t &_pid, const Sys_Castle_id_t &_csid, const Sys_TownPos_id_t &_tpsid,  wcstr _name)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_pid);
			nStream::Write(st,_csid);
			nStream::Write(st,_tpsid);
			nStream::Write(st,_name);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DC2DQ_TOWN_CREATE;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC2DQ_TOWN_CREATE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC2DQ_TOWN_CREATE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_DBQueryServer

}/*nDBQueryServer */ }/* nNET*/ } //nMech
#endif //DBQueryServer___DC2DQ_TOWN_CREATE__