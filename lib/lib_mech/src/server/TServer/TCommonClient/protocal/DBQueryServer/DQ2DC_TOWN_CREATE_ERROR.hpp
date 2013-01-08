
#ifndef DBQueryServer___DQ2DC_TOWN_CREATE_ERROR__ 
#define DBQueryServer___DQ2DC_TOWN_CREATE_ERROR__

#ifndef DBQueryServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DBQueryServer(DBQueryServer);
jxDECL_DBQueryServer(DQ2DC_TOWN_CREATE_ERROR);
#endif //DBQueryServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nDBQueryServer
{
	const int pk_DQ2DC_TOWN_CREATE_ERROR = /*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+9;
	/* player_id_t pid;*/
	/* jError e;*/
	
	struct S_DQ2DC_TOWN_CREATE_ERROR;
	bool READ_DQ2DC_TOWN_CREATE_ERROR(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DQ2DC_TOWN_CREATE_ERROR &param);
	struct S_DQ2DC_TOWN_CREATE_ERROR
	{
		player_id_t pid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer

		jError e;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer


		#ifndef jNOT_USE_DebugPrint_DBQueryServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DQ2DC_TOWN_CREATE_ERROR > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("pid"),pid);
			jDebugPrint(_T("e"),e);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DQ2DC_TOWN_CREATE_ERROR(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_DBQueryServer
	
	inline bool READ_DQ2DC_TOWN_CREATE_ERROR(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DQ2DC_TOWN_CREATE_ERROR &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.pid);
		nStream::Read(st,param.e);
		
		#ifndef jNOT_USE_DebugPrint_DBQueryServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DQ2DC_TOWN_CREATE_ERROR : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_DBQueryServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_DBQueryServer
	inline jPacket_Base WRITE_DQ2DC_TOWN_CREATE_ERROR(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DQ2DC_TOWN_CREATE_ERROR &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.pid);
			nStream::Write(st,param.e);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DQ2DC_TOWN_CREATE_ERROR;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DQ2DC_TOWN_CREATE_ERROR :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DQ2DC_TOWN_CREATE_ERROR :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DQ2DC_TOWN_CREATE_ERROR(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const player_id_t &_pid, const jError &_e)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_pid);
			nStream::Write(st,_e);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DQ2DC_TOWN_CREATE_ERROR;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DQ2DC_TOWN_CREATE_ERROR :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DQ2DC_TOWN_CREATE_ERROR :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_DBQueryServer

}/*nDBQueryServer */ }/* nNET*/ } //nMech
#endif //DBQueryServer___DQ2DC_TOWN_CREATE_ERROR__