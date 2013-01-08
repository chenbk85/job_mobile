
#ifndef ChannelServer___X2CH_CHAT__ 
#define ChannelServer___X2CH_CHAT__

#ifndef ChannelServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_ChannelServer(ChannelServer);
jxDECL_ChannelServer(X2CH_CHAT);
#endif //ChannelServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nChannelServer
{
	const int pk_X2CH_CHAT = /*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+2;
	/* wname128_t msg;*/
	/* uint8 type;*/
	/* wstring id[-1];*/
	/* player_id_t pid[-1];*/
	
	struct S_X2CH_CHAT;
	bool READ_X2CH_CHAT(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_X2CH_CHAT &param);
	struct S_X2CH_CHAT
	{
		wname128_t msg;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer
					void set_msg(tcstr sz){jw_strncpy(msg,nUNI::scb1024_t(sz).getW(), 128);	msg[128-1]=0;}
					tcstr get_msg(fname_t _buf){jt_strncpy(_buf, nUNI::scb128_t(msg).getT() , 128);_buf[128-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer

		uint8 type;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer

		std::vector<wstring> id;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer
		wstring* get_id(int i){ return &id[i];}
		void 	set_id(int i, wstring* v){ id[i] = *v;}
		void insert_id(wstring* v){ id.push_back(*v);}
		void clear_id(){ id.clear();}
		size_t size_id(){ return id.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer

		std::vector<player_id_t> pid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer
		player_id_t* get_pid(int i){ return &pid[i];}
		void 	set_pid(int i, player_id_t* v){ pid[i] = *v;}
		void insert_pid(player_id_t* v){ pid.push_back(*v);}
		void clear_pid(){ pid.clear();}
		size_t size_pid(){ return pid.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer


		#ifndef jNOT_USE_DebugPrint_ChannelServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< X2CH_CHAT > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("msg"),msg);
			jDebugPrint(_T("type"),type);
			jDebugPrint(_T("id"),id);
			jDebugPrint(_T("pid"),pid);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_X2CH_CHAT(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_ChannelServer
	
	inline bool READ_X2CH_CHAT(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_X2CH_CHAT &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.msg, 128);
		nStream::Read(st,param.type);
		nMech::uint16 tempSizeid;
		nStream::Read(st,tempSizeid);
		param.id.resize(tempSizeid);
		for(nMech::uint16 iTempid=0;iTempid<tempSizeid; ++iTempid){
		nStream::Read(st,param.id[iTempid]);
		}
		nMech::uint16 tempSizepid;
		nStream::Read(st,tempSizepid);
		param.pid.resize(tempSizepid);
		for(nMech::uint16 iTemppid=0;iTemppid<tempSizepid; ++iTemppid){
		nStream::Read(st,param.pid[iTemppid]);
		}
		
		#ifndef jNOT_USE_DebugPrint_ChannelServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("X2CH_CHAT : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_ChannelServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_ChannelServer
	inline jPacket_Base WRITE_X2CH_CHAT(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_X2CH_CHAT &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.msg);
			nStream::Write(st,param.type);
			nMech::uint16 tempSizeid= (nMech::uint16)param.id.size();
			nStream::Write(st,tempSizeid);
			for(nMech::uint16 iTempid=0;iTempid<tempSizeid; ++iTempid){
			nStream::Write(st,param.id[iTempid]);
			}
			nMech::uint16 tempSizepid= (nMech::uint16)param.pid.size();
			nStream::Write(st,tempSizepid);
			for(nMech::uint16 iTemppid=0;iTemppid<tempSizepid; ++iTemppid){
			nStream::Write(st,param.pid[iTemppid]);
			}
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_X2CH_CHAT;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2CH_CHAT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2CH_CHAT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_X2CH_CHAT(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  wcstr _msg, const uint8 &_type, const std::vector<wstring> &_id, const std::vector<player_id_t> &_pid)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_msg);
			nStream::Write(st,_type);
			nMech::uint16 tempSizeid = (nMech::uint16)_id.size();
			nStream::Write(st,tempSizeid);
			for(nMech::uint16 iTempid=0;iTempid<tempSizeid; ++iTempid){
			nStream::Write(st,_id[iTempid]);
			}
			nMech::uint16 tempSizepid = (nMech::uint16)_pid.size();
			nStream::Write(st,tempSizepid);
			for(nMech::uint16 iTemppid=0;iTemppid<tempSizepid; ++iTemppid){
			nStream::Write(st,_pid[iTemppid]);
			}
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_X2CH_CHAT;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2CH_CHAT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2CH_CHAT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_ChannelServer

}/*nChannelServer */ }/* nNET*/ } //nMech
#endif //ChannelServer___X2CH_CHAT__