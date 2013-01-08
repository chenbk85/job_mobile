
#ifndef MonitorServer___X2S_LOGIN__ 
#define MonitorServer___X2S_LOGIN__

#ifndef MonitorServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_MonitorServer(MonitorServer);
jxDECL_MonitorServer(X2S_LOGIN);
#endif //MonitorServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nMonitorServer
{
	/*[[ 콤마로 구분된 스트링 : eLOGIN콤마EXE_NAME ]]*/
	const int pk_X2S_LOGIN = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+3;
	/* wname32_t name;*/
	/* aname32_t ip;*/
	/* astring servers[-1];*/
	/* tstring states[-1];*/
	
	struct S_X2S_LOGIN;
	bool READ_X2S_LOGIN(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_X2S_LOGIN &param);
	struct S_X2S_LOGIN
	{
		wname32_t name;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer
					void set_name(tcstr sz){jw_strncpy(name,nUNI::scb1024_t(sz).getW(), 32);	name[32-1]=0;}
					tcstr get_name(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(name).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer

		aname32_t ip;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer
					void set_ip(tcstr sz){ja_strncpy(ip,nUNI::scb1024_t(sz).getA(), 32);	ip[32-1]=0;}
					tcstr get_ip(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(ip).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer

		std::vector<astring> servers;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer
		astring* get_servers(int i){ return &servers[i];}
		void 	set_servers(int i, astring* v){ servers[i] = *v;}
		void insert_servers(astring* v){ servers.push_back(*v);}
		void clear_servers(){ servers.clear();}
		size_t size_servers(){ return servers.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer

		std::vector<tstring> states;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer
		tcstr get_states(int i){ return states[i].c_str();}
		void 	set_states(int i, tcstr v){ states[i] = v;}
		void insert_states(tcstr v){ states.push_back(v);}
		void clear_states(){ states.clear();}
		size_t size_states(){ return states.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_MonitorServer


		#ifndef jNOT_USE_DebugPrint_MonitorServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< X2S_LOGIN > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("name"),name);
			jDebugPrint(_T("ip"),ip);
			jDebugPrint(_T("servers"),servers);
			jDebugPrint(_T("states"),states);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_X2S_LOGIN(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_MonitorServer
	
	inline bool READ_X2S_LOGIN(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_X2S_LOGIN &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.name, 32);
		nStream::Read(st,param.ip, 32);
		nMech::uint16 tempSizeservers;
		nStream::Read(st,tempSizeservers);
		param.servers.resize(tempSizeservers);
		for(nMech::uint16 iTempservers=0;iTempservers<tempSizeservers; ++iTempservers){
		nStream::Read(st,param.servers[iTempservers]);
		}
		nMech::uint16 tempSizestates;
		nStream::Read(st,tempSizestates);
		param.states.resize(tempSizestates);
		for(nMech::uint16 iTempstates=0;iTempstates<tempSizestates; ++iTempstates){
		nStream::Read(st,param.states[iTempstates]);
		}
		
		#ifndef jNOT_USE_DebugPrint_MonitorServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("X2S_LOGIN : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_MonitorServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_MonitorServer
	inline jPacket_Base WRITE_X2S_LOGIN(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_X2S_LOGIN &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.name);
			nStream::Write(st,param.ip);
			nMech::uint16 tempSizeservers= (nMech::uint16)param.servers.size();
			nStream::Write(st,tempSizeservers);
			for(nMech::uint16 iTempservers=0;iTempservers<tempSizeservers; ++iTempservers){
			nStream::Write(st,param.servers[iTempservers]);
			}
			nMech::uint16 tempSizestates= (nMech::uint16)param.states.size();
			nStream::Write(st,tempSizestates);
			for(nMech::uint16 iTempstates=0;iTempstates<tempSizestates; ++iTempstates){
			nStream::Write(st,param.states[iTempstates]);
			}
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_X2S_LOGIN;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2S_LOGIN :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2S_LOGIN :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_X2S_LOGIN(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  wcstr _name,  acstr _ip, const std::vector<astring> &_servers, const std::vector<tstring> &_states)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_name);
			nStream::Write(st,_ip);
			nMech::uint16 tempSizeservers = (nMech::uint16)_servers.size();
			nStream::Write(st,tempSizeservers);
			for(nMech::uint16 iTempservers=0;iTempservers<tempSizeservers; ++iTempservers){
			nStream::Write(st,_servers[iTempservers]);
			}
			nMech::uint16 tempSizestates = (nMech::uint16)_states.size();
			nStream::Write(st,tempSizestates);
			for(nMech::uint16 iTempstates=0;iTempstates<tempSizestates; ++iTempstates){
			nStream::Write(st,_states[iTempstates]);
			}
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_X2S_LOGIN;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2S_LOGIN :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2S_LOGIN :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_MonitorServer

}/*nMonitorServer */ }/* nNET*/ } //nMech
#endif //MonitorServer___X2S_LOGIN__