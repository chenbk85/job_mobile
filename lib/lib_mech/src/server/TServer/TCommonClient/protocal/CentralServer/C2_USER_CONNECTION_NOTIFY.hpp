
#ifndef CentralServer___C2_USER_CONNECTION_NOTIFY__ 
#define CentralServer___C2_USER_CONNECTION_NOTIFY__

#ifndef CentralServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_CentralServer(CentralServer);
jxDECL_CentralServer(C2_USER_CONNECTION_NOTIFY);
#endif //CentralServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nCentralServer
{
	/*[[ 약 3~6초간 딜레이후 전달&#x0A;던젼서버의 경우 해당 월드의 모든 Town서버에 전달&#x0A;마을서버의 경우 모든 로긴서버에 전달. ]]*/
	const int pk_C2_USER_CONNECTION_NOTIFY = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+13;
	/* serverid_t sid[-1];*/
	/* uint16 userCnt[-1];*/
	
	struct S_C2_USER_CONNECTION_NOTIFY;
	bool READ_C2_USER_CONNECTION_NOTIFY(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_C2_USER_CONNECTION_NOTIFY &param);
	struct S_C2_USER_CONNECTION_NOTIFY
	{
		std::vector<serverid_t> sid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_CentralServer
		serverid_t* get_sid(int i){ return &sid[i];}
		void 	set_sid(int i, serverid_t* v){ sid[i] = *v;}
		void insert_sid(serverid_t* v){ sid.push_back(*v);}
		void clear_sid(){ sid.clear();}
		size_t size_sid(){ return sid.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_CentralServer

		std::vector<uint16> userCnt;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_CentralServer
		uint16* get_userCnt(int i){ return &userCnt[i];}
		void 	set_userCnt(int i, uint16* v){ userCnt[i] = *v;}
		void insert_userCnt(uint16* v){ userCnt.push_back(*v);}
		void clear_userCnt(){ userCnt.clear();}
		size_t size_userCnt(){ return userCnt.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_CentralServer


		#ifndef jNOT_USE_DebugPrint_CentralServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< C2_USER_CONNECTION_NOTIFY > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("sid"),sid);
			jDebugPrint(_T("userCnt"),userCnt);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_C2_USER_CONNECTION_NOTIFY(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_CentralServer
	
	inline bool READ_C2_USER_CONNECTION_NOTIFY(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_C2_USER_CONNECTION_NOTIFY &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nMech::uint16 tempSizesid;
		nStream::Read(st,tempSizesid);
		param.sid.resize(tempSizesid);
		for(nMech::uint16 iTempsid=0;iTempsid<tempSizesid; ++iTempsid){
		nStream::Read(st,param.sid[iTempsid]);
		}
		nMech::uint16 tempSizeuserCnt;
		nStream::Read(st,tempSizeuserCnt);
		param.userCnt.resize(tempSizeuserCnt);
		for(nMech::uint16 iTempuserCnt=0;iTempuserCnt<tempSizeuserCnt; ++iTempuserCnt){
		nStream::Read(st,param.userCnt[iTempuserCnt]);
		}
		
		#ifndef jNOT_USE_DebugPrint_CentralServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("C2_USER_CONNECTION_NOTIFY : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_CentralServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_CentralServer
	inline jPacket_Base WRITE_C2_USER_CONNECTION_NOTIFY(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_C2_USER_CONNECTION_NOTIFY &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizesid= (nMech::uint16)param.sid.size();
			nStream::Write(st,tempSizesid);
			for(nMech::uint16 iTempsid=0;iTempsid<tempSizesid; ++iTempsid){
			nStream::Write(st,param.sid[iTempsid]);
			}
			nMech::uint16 tempSizeuserCnt= (nMech::uint16)param.userCnt.size();
			nStream::Write(st,tempSizeuserCnt);
			for(nMech::uint16 iTempuserCnt=0;iTempuserCnt<tempSizeuserCnt; ++iTempuserCnt){
			nStream::Write(st,param.userCnt[iTempuserCnt]);
			}
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_C2_USER_CONNECTION_NOTIFY;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" C2_USER_CONNECTION_NOTIFY :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" C2_USER_CONNECTION_NOTIFY :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_C2_USER_CONNECTION_NOTIFY(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const std::vector<serverid_t> &_sid, const std::vector<uint16> &_userCnt)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizesid = (nMech::uint16)_sid.size();
			nStream::Write(st,tempSizesid);
			for(nMech::uint16 iTempsid=0;iTempsid<tempSizesid; ++iTempsid){
			nStream::Write(st,_sid[iTempsid]);
			}
			nMech::uint16 tempSizeuserCnt = (nMech::uint16)_userCnt.size();
			nStream::Write(st,tempSizeuserCnt);
			for(nMech::uint16 iTempuserCnt=0;iTempuserCnt<tempSizeuserCnt; ++iTempuserCnt){
			nStream::Write(st,_userCnt[iTempuserCnt]);
			}
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_C2_USER_CONNECTION_NOTIFY;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" C2_USER_CONNECTION_NOTIFY :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" C2_USER_CONNECTION_NOTIFY :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_CentralServer

}/*nCentralServer */ }/* nNET*/ } //nMech
#endif //CentralServer___C2_USER_CONNECTION_NOTIFY__