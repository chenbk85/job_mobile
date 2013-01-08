
#ifndef CentralServer___C2SS_ONLINE_OK__ 
#define CentralServer___C2SS_ONLINE_OK__

#ifndef CentralServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_CentralServer(CentralServer);
jxDECL_CentralServer(C2SS_ONLINE_OK);
#endif //CentralServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nCentralServer
{
	/*[[ 새로운 sid를 발급하고&#x0A;Central에 접속하고 있는 다른서버들정보를 보낸다. ]]*/
	const int pk_C2SS_ONLINE_OK = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+4;
	/* jServerInfo you;*/
	/*[[ 새로세팅된정보를다시보냄 ]]*/
	/* jServerInfo s[-1];*/
	
	struct S_C2SS_ONLINE_OK;
	bool READ_C2SS_ONLINE_OK(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_C2SS_ONLINE_OK &param);
	struct S_C2SS_ONLINE_OK
	{
		/*[[ 새로세팅된정보를다시보냄 ]]*/
		jServerInfo you;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_CentralServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_CentralServer

		std::vector<jServerInfo> s;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_CentralServer
		jServerInfo* get_s(int i){ return &s[i];}
		void 	set_s(int i, jServerInfo* v){ s[i] = *v;}
		void insert_s(jServerInfo* v){ s.push_back(*v);}
		void clear_s(){ s.clear();}
		size_t size_s(){ return s.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_CentralServer


		#ifndef jNOT_USE_DebugPrint_CentralServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< C2SS_ONLINE_OK > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("you"),you);
			jDebugPrint(_T("s"),s);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_C2SS_ONLINE_OK(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_CentralServer
	
	inline bool READ_C2SS_ONLINE_OK(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_C2SS_ONLINE_OK &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.you);
		/*	[[ 새로세팅된정보를다시보냄 ]]*/
		nMech::uint16 tempSizes;
		nStream::Read(st,tempSizes);
		param.s.resize(tempSizes);
		for(nMech::uint16 iTemps=0;iTemps<tempSizes; ++iTemps){
		nStream::Read(st,param.s[iTemps]);
		}
		
		#ifndef jNOT_USE_DebugPrint_CentralServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("C2SS_ONLINE_OK : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_CentralServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_CentralServer
	inline jPacket_Base WRITE_C2SS_ONLINE_OK(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_C2SS_ONLINE_OK &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.you);
			/*[[ 새로세팅된정보를다시보냄 ]]*/
			nMech::uint16 tempSizes= (nMech::uint16)param.s.size();
			nStream::Write(st,tempSizes);
			for(nMech::uint16 iTemps=0;iTemps<tempSizes; ++iTemps){
			nStream::Write(st,param.s[iTemps]);
			}
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_C2SS_ONLINE_OK;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" C2SS_ONLINE_OK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" C2SS_ONLINE_OK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_C2SS_ONLINE_OK(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const jServerInfo &_you, const std::vector<jServerInfo> &_s)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_you);
			/*[[ 새로세팅된정보를다시보냄 ]]*/
			nMech::uint16 tempSizes = (nMech::uint16)_s.size();
			nStream::Write(st,tempSizes);
			for(nMech::uint16 iTemps=0;iTemps<tempSizes; ++iTemps){
			nStream::Write(st,_s[iTemps]);
			}
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_C2SS_ONLINE_OK;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" C2SS_ONLINE_OK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" C2SS_ONLINE_OK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_CentralServer

}/*nCentralServer */ }/* nNET*/ } //nMech
#endif //CentralServer___C2SS_ONLINE_OK__