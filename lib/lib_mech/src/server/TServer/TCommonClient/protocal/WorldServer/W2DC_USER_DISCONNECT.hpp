
#ifndef WorldServer___W2DC_USER_DISCONNECT__ 
#define WorldServer___W2DC_USER_DISCONNECT__

#ifndef WorldServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_WorldServer(WorldServer);
jxDECL_WorldServer(W2DC_USER_DISCONNECT);
#endif //WorldServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nWorldServer
{
	const int pk_W2DC_USER_DISCONNECT = /*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+7;
	/* player_id_t pid[-1];*/
	
	struct S_W2DC_USER_DISCONNECT;
	bool READ_W2DC_USER_DISCONNECT(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_W2DC_USER_DISCONNECT &param);
	struct S_W2DC_USER_DISCONNECT
	{
		std::vector<player_id_t> pid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_WorldServer
		player_id_t* get_pid(int i){ return &pid[i];}
		void 	set_pid(int i, player_id_t* v){ pid[i] = *v;}
		void insert_pid(player_id_t* v){ pid.push_back(*v);}
		void clear_pid(){ pid.clear();}
		size_t size_pid(){ return pid.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_WorldServer


		#ifndef jNOT_USE_DebugPrint_WorldServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< W2DC_USER_DISCONNECT > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("pid"),pid);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_W2DC_USER_DISCONNECT(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_WorldServer
	
	inline bool READ_W2DC_USER_DISCONNECT(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_W2DC_USER_DISCONNECT &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nMech::uint16 tempSizepid;
		nStream::Read(st,tempSizepid);
		param.pid.resize(tempSizepid);
		for(nMech::uint16 iTemppid=0;iTemppid<tempSizepid; ++iTemppid){
		nStream::Read(st,param.pid[iTemppid]);
		}
		
		#ifndef jNOT_USE_DebugPrint_WorldServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("W2DC_USER_DISCONNECT : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_WorldServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_WorldServer
	inline jPacket_Base WRITE_W2DC_USER_DISCONNECT(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_W2DC_USER_DISCONNECT &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizepid= (nMech::uint16)param.pid.size();
			nStream::Write(st,tempSizepid);
			for(nMech::uint16 iTemppid=0;iTemppid<tempSizepid; ++iTemppid){
			nStream::Write(st,param.pid[iTemppid]);
			}
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_W2DC_USER_DISCONNECT;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" W2DC_USER_DISCONNECT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" W2DC_USER_DISCONNECT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_W2DC_USER_DISCONNECT(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const std::vector<player_id_t> &_pid)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizepid = (nMech::uint16)_pid.size();
			nStream::Write(st,tempSizepid);
			for(nMech::uint16 iTemppid=0;iTemppid<tempSizepid; ++iTemppid){
			nStream::Write(st,_pid[iTemppid]);
			}
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_W2DC_USER_DISCONNECT;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" W2DC_USER_DISCONNECT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" W2DC_USER_DISCONNECT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_WorldServer

}/*nWorldServer */ }/* nNET*/ } //nMech
#endif //WorldServer___W2DC_USER_DISCONNECT__