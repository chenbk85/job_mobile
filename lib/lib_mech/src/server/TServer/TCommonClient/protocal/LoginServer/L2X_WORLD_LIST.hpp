
#ifndef LoginServer___L2X_WORLD_LIST__ 
#define LoginServer___L2X_WORLD_LIST__

#ifndef LoginServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_LoginServer(LoginServer);
jxDECL_LoginServer(L2X_WORLD_LIST);
#endif //LoginServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nLoginServer
{
	const int pk_L2X_WORLD_LIST = /*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+10;
	/* jWorldServerInfo worlds[-1];*/
	
	struct S_L2X_WORLD_LIST;
	bool READ_L2X_WORLD_LIST(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_L2X_WORLD_LIST &param);
	struct S_L2X_WORLD_LIST
	{
		std::vector<jWorldServerInfo> worlds;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_LoginServer
		jWorldServerInfo* get_worlds(int i){ return &worlds[i];}
		void 	set_worlds(int i, jWorldServerInfo* v){ worlds[i] = *v;}
		void insert_worlds(jWorldServerInfo* v){ worlds.push_back(*v);}
		void clear_worlds(){ worlds.clear();}
		size_t size_worlds(){ return worlds.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_LoginServer


		#ifndef jNOT_USE_DebugPrint_LoginServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< L2X_WORLD_LIST > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("worlds"),worlds);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_L2X_WORLD_LIST(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_LoginServer
	
	inline bool READ_L2X_WORLD_LIST(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_L2X_WORLD_LIST &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nMech::uint16 tempSizeworlds;
		nStream::Read(st,tempSizeworlds);
		param.worlds.resize(tempSizeworlds);
		for(nMech::uint16 iTempworlds=0;iTempworlds<tempSizeworlds; ++iTempworlds){
		nStream::Read(st,param.worlds[iTempworlds]);
		}
		
		#ifndef jNOT_USE_DebugPrint_LoginServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("L2X_WORLD_LIST : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_LoginServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_LoginServer
	inline jPacket_Base WRITE_L2X_WORLD_LIST(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_L2X_WORLD_LIST &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizeworlds= (nMech::uint16)param.worlds.size();
			nStream::Write(st,tempSizeworlds);
			for(nMech::uint16 iTempworlds=0;iTempworlds<tempSizeworlds; ++iTempworlds){
			nStream::Write(st,param.worlds[iTempworlds]);
			}
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_L2X_WORLD_LIST;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" L2X_WORLD_LIST :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" L2X_WORLD_LIST :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_L2X_WORLD_LIST(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const std::vector<jWorldServerInfo> &_worlds)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizeworlds = (nMech::uint16)_worlds.size();
			nStream::Write(st,tempSizeworlds);
			for(nMech::uint16 iTempworlds=0;iTempworlds<tempSizeworlds; ++iTempworlds){
			nStream::Write(st,_worlds[iTempworlds]);
			}
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_L2X_WORLD_LIST;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" L2X_WORLD_LIST :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" L2X_WORLD_LIST :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_LoginServer

}/*nLoginServer */ }/* nNET*/ } //nMech
#endif //LoginServer___L2X_WORLD_LIST__