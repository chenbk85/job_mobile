
#ifndef DBQueryServer___DC2DQ_USER_DISCONNECT__ 
#define DBQueryServer___DC2DQ_USER_DISCONNECT__

#ifndef DBQueryServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DBQueryServer(DBQueryServer);
jxDECL_DBQueryServer(DC2DQ_USER_DISCONNECT);
#endif //DBQueryServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nDBQueryServer
{
	const int pk_DC2DQ_USER_DISCONNECT = /*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+1;
	/* player_id_t pid[-1];*/
	
	struct S_DC2DQ_USER_DISCONNECT;
	bool READ_DC2DQ_USER_DISCONNECT(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DC2DQ_USER_DISCONNECT &param);
	struct S_DC2DQ_USER_DISCONNECT
	{
		std::vector<player_id_t> pid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer
		player_id_t* get_pid(int i){ return &pid[i];}
		void 	set_pid(int i, player_id_t* v){ pid[i] = *v;}
		void insert_pid(player_id_t* v){ pid.push_back(*v);}
		void clear_pid(){ pid.clear();}
		size_t size_pid(){ return pid.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBQueryServer


		#ifndef jNOT_USE_DebugPrint_DBQueryServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DC2DQ_USER_DISCONNECT > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("pid"),pid);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DC2DQ_USER_DISCONNECT(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_DBQueryServer
	
	inline bool READ_DC2DQ_USER_DISCONNECT(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DC2DQ_USER_DISCONNECT &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nMech::uint16 tempSizepid;
		nStream::Read(st,tempSizepid);
		param.pid.resize(tempSizepid);
		for(nMech::uint16 iTemppid=0;iTemppid<tempSizepid; ++iTemppid){
		nStream::Read(st,param.pid[iTemppid]);
		}
		
		#ifndef jNOT_USE_DebugPrint_DBQueryServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DC2DQ_USER_DISCONNECT : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_DBQueryServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_DBQueryServer
	inline jPacket_Base WRITE_DC2DQ_USER_DISCONNECT(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DC2DQ_USER_DISCONNECT &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizepid= (nMech::uint16)param.pid.size();
			nStream::Write(st,tempSizepid);
			for(nMech::uint16 iTemppid=0;iTemppid<tempSizepid; ++iTemppid){
			nStream::Write(st,param.pid[iTemppid]);
			}
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DC2DQ_USER_DISCONNECT;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC2DQ_USER_DISCONNECT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC2DQ_USER_DISCONNECT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DC2DQ_USER_DISCONNECT(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const std::vector<player_id_t> &_pid)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizepid = (nMech::uint16)_pid.size();
			nStream::Write(st,tempSizepid);
			for(nMech::uint16 iTemppid=0;iTemppid<tempSizepid; ++iTemppid){
			nStream::Write(st,_pid[iTemppid]);
			}
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DC2DQ_USER_DISCONNECT;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC2DQ_USER_DISCONNECT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC2DQ_USER_DISCONNECT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_DBQueryServer

}/*nDBQueryServer */ }/* nNET*/ } //nMech
#endif //DBQueryServer___DC2DQ_USER_DISCONNECT__