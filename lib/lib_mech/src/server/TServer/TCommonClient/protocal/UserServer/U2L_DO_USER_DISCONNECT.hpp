
#ifndef UserServer___U2L_DO_USER_DISCONNECT__ 
#define UserServer___U2L_DO_USER_DISCONNECT__

#ifndef UserServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_UserServer(UserServer);
jxDECL_UserServer(U2L_DO_USER_DISCONNECT);
#endif //UserServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nUserServer
{
	const int pk_U2L_DO_USER_DISCONNECT = /*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+18;
	/* player_id_t uids[-1];*/
	
	struct S_U2L_DO_USER_DISCONNECT;
	bool READ_U2L_DO_USER_DISCONNECT(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_U2L_DO_USER_DISCONNECT &param);
	struct S_U2L_DO_USER_DISCONNECT
	{
		std::vector<player_id_t> uids;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_UserServer
		player_id_t* get_uids(int i){ return &uids[i];}
		void 	set_uids(int i, player_id_t* v){ uids[i] = *v;}
		void insert_uids(player_id_t* v){ uids.push_back(*v);}
		void clear_uids(){ uids.clear();}
		size_t size_uids(){ return uids.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_UserServer


		#ifndef jNOT_USE_DebugPrint_UserServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< U2L_DO_USER_DISCONNECT > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("uids"),uids);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_U2L_DO_USER_DISCONNECT(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_UserServer
	
	inline bool READ_U2L_DO_USER_DISCONNECT(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_U2L_DO_USER_DISCONNECT &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nMech::uint16 tempSizeuids;
		nStream::Read(st,tempSizeuids);
		param.uids.resize(tempSizeuids);
		for(nMech::uint16 iTempuids=0;iTempuids<tempSizeuids; ++iTempuids){
		nStream::Read(st,param.uids[iTempuids]);
		}
		
		#ifndef jNOT_USE_DebugPrint_UserServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("U2L_DO_USER_DISCONNECT : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_UserServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_UserServer
	inline jPacket_Base WRITE_U2L_DO_USER_DISCONNECT(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_U2L_DO_USER_DISCONNECT &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizeuids= (nMech::uint16)param.uids.size();
			nStream::Write(st,tempSizeuids);
			for(nMech::uint16 iTempuids=0;iTempuids<tempSizeuids; ++iTempuids){
			nStream::Write(st,param.uids[iTempuids]);
			}
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_U2L_DO_USER_DISCONNECT;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" U2L_DO_USER_DISCONNECT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" U2L_DO_USER_DISCONNECT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_U2L_DO_USER_DISCONNECT(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const std::vector<player_id_t> &_uids)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizeuids = (nMech::uint16)_uids.size();
			nStream::Write(st,tempSizeuids);
			for(nMech::uint16 iTempuids=0;iTempuids<tempSizeuids; ++iTempuids){
			nStream::Write(st,_uids[iTempuids]);
			}
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_U2L_DO_USER_DISCONNECT;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" U2L_DO_USER_DISCONNECT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" U2L_DO_USER_DISCONNECT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_UserServer

}/*nUserServer */ }/* nNET*/ } //nMech
#endif //UserServer___U2L_DO_USER_DISCONNECT__