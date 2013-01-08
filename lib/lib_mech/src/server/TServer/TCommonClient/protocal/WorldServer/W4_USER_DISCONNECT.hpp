
#ifndef WorldServer___W4_USER_DISCONNECT__ 
#define WorldServer___W4_USER_DISCONNECT__

#ifndef WorldServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_WorldServer(WorldServer);
jxDECL_WorldServer(W4_USER_DISCONNECT);
#endif //WorldServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nWorldServer
{
	/*[[ 모든접속이 끊겼을때 약 6초간격으로&#x0A;모아서 보낸다.	
Town서버와 Dungeon서버의 유저 disconnection은	
월드와 유저에 따로 보낸다.	
월드에서는 DC로 다시 보낸다. ]]*/
	const int pk_W4_USER_DISCONNECT = /*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+6;
	/* wstring id[-1];*/
	
	struct S_W4_USER_DISCONNECT;
	bool READ_W4_USER_DISCONNECT(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_W4_USER_DISCONNECT &param);
	struct S_W4_USER_DISCONNECT
	{
		std::vector<wstring> id;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_WorldServer
		wstring* get_id(int i){ return &id[i];}
		void 	set_id(int i, wstring* v){ id[i] = *v;}
		void insert_id(wstring* v){ id.push_back(*v);}
		void clear_id(){ id.clear();}
		size_t size_id(){ return id.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_WorldServer


		#ifndef jNOT_USE_DebugPrint_WorldServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< W4_USER_DISCONNECT > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("id"),id);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_W4_USER_DISCONNECT(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_WorldServer
	
	inline bool READ_W4_USER_DISCONNECT(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_W4_USER_DISCONNECT &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nMech::uint16 tempSizeid;
		nStream::Read(st,tempSizeid);
		param.id.resize(tempSizeid);
		for(nMech::uint16 iTempid=0;iTempid<tempSizeid; ++iTempid){
		nStream::Read(st,param.id[iTempid]);
		}
		
		#ifndef jNOT_USE_DebugPrint_WorldServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("W4_USER_DISCONNECT : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_WorldServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_WorldServer
	inline jPacket_Base WRITE_W4_USER_DISCONNECT(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_W4_USER_DISCONNECT &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizeid= (nMech::uint16)param.id.size();
			nStream::Write(st,tempSizeid);
			for(nMech::uint16 iTempid=0;iTempid<tempSizeid; ++iTempid){
			nStream::Write(st,param.id[iTempid]);
			}
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_W4_USER_DISCONNECT;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" W4_USER_DISCONNECT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" W4_USER_DISCONNECT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_W4_USER_DISCONNECT(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const std::vector<wstring> &_id)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizeid = (nMech::uint16)_id.size();
			nStream::Write(st,tempSizeid);
			for(nMech::uint16 iTempid=0;iTempid<tempSizeid; ++iTempid){
			nStream::Write(st,_id[iTempid]);
			}
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_W4_USER_DISCONNECT;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" W4_USER_DISCONNECT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" W4_USER_DISCONNECT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_WorldServer

}/*nWorldServer */ }/* nNET*/ } //nMech
#endif //WorldServer___W4_USER_DISCONNECT__