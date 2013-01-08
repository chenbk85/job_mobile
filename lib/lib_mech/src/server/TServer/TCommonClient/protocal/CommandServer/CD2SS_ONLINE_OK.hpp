
#ifndef CommandServer___CD2SS_ONLINE_OK__ 
#define CommandServer___CD2SS_ONLINE_OK__

#ifndef CommandServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_CommandServer(CommandServer);
jxDECL_CommandServer(CD2SS_ONLINE_OK);
#endif //CommandServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nCommandServer
{
	/*[[ Central서버가 죽었을때만 대신 해서 보냄.	
Command에 접속하고 있는 다른서버들정보를 보낸다. ]]*/
	const int pk_CD2SS_ONLINE_OK = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1500+3;
	/* jServerInfo you;*/
	/* jServerInfo s[-1];*/
	
	struct S_CD2SS_ONLINE_OK;
	bool READ_CD2SS_ONLINE_OK(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_CD2SS_ONLINE_OK &param);
	struct S_CD2SS_ONLINE_OK
	{
		jServerInfo you;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_CommandServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_CommandServer

		std::vector<jServerInfo> s;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_CommandServer
		jServerInfo* get_s(int i){ return &s[i];}
		void 	set_s(int i, jServerInfo* v){ s[i] = *v;}
		void insert_s(jServerInfo* v){ s.push_back(*v);}
		void clear_s(){ s.clear();}
		size_t size_s(){ return s.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_CommandServer


		#ifndef jNOT_USE_DebugPrint_CommandServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< CD2SS_ONLINE_OK > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("you"),you);
			jDebugPrint(_T("s"),s);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_CD2SS_ONLINE_OK(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_CommandServer
	
	inline bool READ_CD2SS_ONLINE_OK(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_CD2SS_ONLINE_OK &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.you);
		nMech::uint16 tempSizes;
		nStream::Read(st,tempSizes);
		param.s.resize(tempSizes);
		for(nMech::uint16 iTemps=0;iTemps<tempSizes; ++iTemps){
		nStream::Read(st,param.s[iTemps]);
		}
		
		#ifndef jNOT_USE_DebugPrint_CommandServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("CD2SS_ONLINE_OK : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_CommandServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_CommandServer
	inline jPacket_Base WRITE_CD2SS_ONLINE_OK(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_CD2SS_ONLINE_OK &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.you);
			nMech::uint16 tempSizes= (nMech::uint16)param.s.size();
			nStream::Write(st,tempSizes);
			for(nMech::uint16 iTemps=0;iTemps<tempSizes; ++iTemps){
			nStream::Write(st,param.s[iTemps]);
			}
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_CD2SS_ONLINE_OK;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" CD2SS_ONLINE_OK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" CD2SS_ONLINE_OK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_CD2SS_ONLINE_OK(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const jServerInfo &_you, const std::vector<jServerInfo> &_s)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_you);
			nMech::uint16 tempSizes = (nMech::uint16)_s.size();
			nStream::Write(st,tempSizes);
			for(nMech::uint16 iTemps=0;iTemps<tempSizes; ++iTemps){
			nStream::Write(st,_s[iTemps]);
			}
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_CD2SS_ONLINE_OK;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" CD2SS_ONLINE_OK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" CD2SS_ONLINE_OK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_CommandServer

}/*nCommandServer */ }/* nNET*/ } //nMech
#endif //CommandServer___CD2SS_ONLINE_OK__