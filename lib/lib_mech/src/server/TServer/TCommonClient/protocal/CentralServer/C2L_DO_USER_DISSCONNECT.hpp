
#ifndef CentralServer___C2L_DO_USER_DISSCONNECT__ 
#define CentralServer___C2L_DO_USER_DISSCONNECT__

#ifndef CentralServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_CentralServer(CentralServer);
jxDECL_CentralServer(C2L_DO_USER_DISSCONNECT);
#endif //CentralServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nCentralServer
{
	const int pk_C2L_DO_USER_DISSCONNECT = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+16;
	/* player_id_t pid[-1];*/
	
	struct S_C2L_DO_USER_DISSCONNECT;
	bool READ_C2L_DO_USER_DISSCONNECT(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_C2L_DO_USER_DISSCONNECT &param);
	struct S_C2L_DO_USER_DISSCONNECT
	{
		std::vector<player_id_t> pid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_CentralServer
		player_id_t* get_pid(int i){ return &pid[i];}
		void 	set_pid(int i, player_id_t* v){ pid[i] = *v;}
		void insert_pid(player_id_t* v){ pid.push_back(*v);}
		void clear_pid(){ pid.clear();}
		size_t size_pid(){ return pid.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_CentralServer


		#ifndef jNOT_USE_DebugPrint_CentralServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< C2L_DO_USER_DISSCONNECT > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("pid"),pid);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_C2L_DO_USER_DISSCONNECT(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_CentralServer
	
	inline bool READ_C2L_DO_USER_DISSCONNECT(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_C2L_DO_USER_DISSCONNECT &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nMech::uint16 tempSizepid;
		nStream::Read(st,tempSizepid);
		param.pid.resize(tempSizepid);
		for(nMech::uint16 iTemppid=0;iTemppid<tempSizepid; ++iTemppid){
		nStream::Read(st,param.pid[iTemppid]);
		}
		
		#ifndef jNOT_USE_DebugPrint_CentralServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("C2L_DO_USER_DISSCONNECT : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_CentralServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_CentralServer
	inline jPacket_Base WRITE_C2L_DO_USER_DISSCONNECT(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_C2L_DO_USER_DISSCONNECT &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizepid= (nMech::uint16)param.pid.size();
			nStream::Write(st,tempSizepid);
			for(nMech::uint16 iTemppid=0;iTemppid<tempSizepid; ++iTemppid){
			nStream::Write(st,param.pid[iTemppid]);
			}
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_C2L_DO_USER_DISSCONNECT;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" C2L_DO_USER_DISSCONNECT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" C2L_DO_USER_DISSCONNECT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_C2L_DO_USER_DISSCONNECT(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const std::vector<player_id_t> &_pid)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizepid = (nMech::uint16)_pid.size();
			nStream::Write(st,tempSizepid);
			for(nMech::uint16 iTemppid=0;iTemppid<tempSizepid; ++iTemppid){
			nStream::Write(st,_pid[iTemppid]);
			}
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_C2L_DO_USER_DISSCONNECT;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" C2L_DO_USER_DISSCONNECT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" C2L_DO_USER_DISSCONNECT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_CentralServer

}/*nCentralServer */ }/* nNET*/ } //nMech
#endif //CentralServer___C2L_DO_USER_DISSCONNECT__