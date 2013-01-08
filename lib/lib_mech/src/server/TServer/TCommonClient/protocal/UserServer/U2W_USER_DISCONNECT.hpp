
#ifndef UserServer___U2W_USER_DISCONNECT__ 
#define UserServer___U2W_USER_DISCONNECT__

#ifndef UserServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_UserServer(UserServer);
jxDECL_UserServer(U2W_USER_DISCONNECT);
#endif //UserServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nUserServer
{
	/*[[ 모든접속이 끊겼을때 약 1초간격으로&#x0A;모아서 보낸다.	
로긴서버에만 접속된 상태일때 보낸다.	
Town서버와 Dungeon서버에 접속된 상태에서는&#x0A;User에서 World로 보낼 필요가 없다. ]]*/
	const int pk_U2W_USER_DISCONNECT = /*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+17;
	/* wstring id[-1];*/
	
	struct S_U2W_USER_DISCONNECT;
	bool READ_U2W_USER_DISCONNECT(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_U2W_USER_DISCONNECT &param);
	struct S_U2W_USER_DISCONNECT
	{
		std::vector<wstring> id;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_UserServer
		wstring* get_id(int i){ return &id[i];}
		void 	set_id(int i, wstring* v){ id[i] = *v;}
		void insert_id(wstring* v){ id.push_back(*v);}
		void clear_id(){ id.clear();}
		size_t size_id(){ return id.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_UserServer


		#ifndef jNOT_USE_DebugPrint_UserServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< U2W_USER_DISCONNECT > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("id"),id);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_U2W_USER_DISCONNECT(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_UserServer
	
	inline bool READ_U2W_USER_DISCONNECT(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_U2W_USER_DISCONNECT &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nMech::uint16 tempSizeid;
		nStream::Read(st,tempSizeid);
		param.id.resize(tempSizeid);
		for(nMech::uint16 iTempid=0;iTempid<tempSizeid; ++iTempid){
		nStream::Read(st,param.id[iTempid]);
		}
		
		#ifndef jNOT_USE_DebugPrint_UserServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("U2W_USER_DISCONNECT : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_UserServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_UserServer
	inline jPacket_Base WRITE_U2W_USER_DISCONNECT(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_U2W_USER_DISCONNECT &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizeid= (nMech::uint16)param.id.size();
			nStream::Write(st,tempSizeid);
			for(nMech::uint16 iTempid=0;iTempid<tempSizeid; ++iTempid){
			nStream::Write(st,param.id[iTempid]);
			}
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_U2W_USER_DISCONNECT;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" U2W_USER_DISCONNECT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" U2W_USER_DISCONNECT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_U2W_USER_DISCONNECT(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const std::vector<wstring> &_id)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizeid = (nMech::uint16)_id.size();
			nStream::Write(st,tempSizeid);
			for(nMech::uint16 iTempid=0;iTempid<tempSizeid; ++iTempid){
			nStream::Write(st,_id[iTempid]);
			}
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_U2W_USER_DISCONNECT;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" U2W_USER_DISCONNECT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" U2W_USER_DISCONNECT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_UserServer

}/*nUserServer */ }/* nNET*/ } //nMech
#endif //UserServer___U2W_USER_DISCONNECT__