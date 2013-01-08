
#ifndef LoginServer___L2X_CHANNEL_LIST__ 
#define LoginServer___L2X_CHANNEL_LIST__

#ifndef LoginServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_LoginServer(LoginServer);
jxDECL_LoginServer(L2X_CHANNEL_LIST);
#endif //LoginServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nLoginServer
{
	/*[[ 각 인터넷업체별(또한 성별) 개설된 월드리스트받기&#x0A;	
world이름은 xml로 존재한다. data/xml/world_servers.xml	
해당 월드서버리스트를 보냄( 클라이언트에서는 캐슁하세요)&#x0A;약 5분이 경과했을때 다시 요청하는게 좋음. ]]*/
	const int pk_L2X_CHANNEL_LIST = /*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+8;
	/* serverid_t channel[-1];*/
	/* astring channel_name[-1];*/
	/* uint8 buzy_level[-1];*/
	
	struct S_L2X_CHANNEL_LIST;
	bool READ_L2X_CHANNEL_LIST(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_L2X_CHANNEL_LIST &param);
	struct S_L2X_CHANNEL_LIST
	{
		std::vector<serverid_t> channel;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_LoginServer
		serverid_t* get_channel(int i){ return &channel[i];}
		void 	set_channel(int i, serverid_t* v){ channel[i] = *v;}
		void insert_channel(serverid_t* v){ channel.push_back(*v);}
		void clear_channel(){ channel.clear();}
		size_t size_channel(){ return channel.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_LoginServer

		std::vector<astring> channel_name;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_LoginServer
		astring* get_channel_name(int i){ return &channel_name[i];}
		void 	set_channel_name(int i, astring* v){ channel_name[i] = *v;}
		void insert_channel_name(astring* v){ channel_name.push_back(*v);}
		void clear_channel_name(){ channel_name.clear();}
		size_t size_channel_name(){ return channel_name.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_LoginServer

		std::vector<uint8> buzy_level;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_LoginServer
		uint8* get_buzy_level(int i){ return &buzy_level[i];}
		void 	set_buzy_level(int i, uint8* v){ buzy_level[i] = *v;}
		void insert_buzy_level(uint8* v){ buzy_level.push_back(*v);}
		void clear_buzy_level(){ buzy_level.clear();}
		size_t size_buzy_level(){ return buzy_level.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_LoginServer


		#ifndef jNOT_USE_DebugPrint_LoginServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< L2X_CHANNEL_LIST > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("channel"),channel);
			jDebugPrint(_T("channel_name"),channel_name);
			jDebugPrint(_T("buzy_level"),buzy_level);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_L2X_CHANNEL_LIST(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_LoginServer
	
	inline bool READ_L2X_CHANNEL_LIST(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_L2X_CHANNEL_LIST &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nMech::uint16 tempSizechannel;
		nStream::Read(st,tempSizechannel);
		param.channel.resize(tempSizechannel);
		for(nMech::uint16 iTempchannel=0;iTempchannel<tempSizechannel; ++iTempchannel){
		nStream::Read(st,param.channel[iTempchannel]);
		}
		nMech::uint16 tempSizechannel_name;
		nStream::Read(st,tempSizechannel_name);
		param.channel_name.resize(tempSizechannel_name);
		for(nMech::uint16 iTempchannel_name=0;iTempchannel_name<tempSizechannel_name; ++iTempchannel_name){
		nStream::Read(st,param.channel_name[iTempchannel_name]);
		}
		nMech::uint16 tempSizebuzy_level;
		nStream::Read(st,tempSizebuzy_level);
		param.buzy_level.resize(tempSizebuzy_level);
		for(nMech::uint16 iTempbuzy_level=0;iTempbuzy_level<tempSizebuzy_level; ++iTempbuzy_level){
		nStream::Read(st,param.buzy_level[iTempbuzy_level]);
		}
		
		#ifndef jNOT_USE_DebugPrint_LoginServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("L2X_CHANNEL_LIST : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_LoginServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_LoginServer
	inline jPacket_Base WRITE_L2X_CHANNEL_LIST(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_L2X_CHANNEL_LIST &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizechannel= (nMech::uint16)param.channel.size();
			nStream::Write(st,tempSizechannel);
			for(nMech::uint16 iTempchannel=0;iTempchannel<tempSizechannel; ++iTempchannel){
			nStream::Write(st,param.channel[iTempchannel]);
			}
			nMech::uint16 tempSizechannel_name= (nMech::uint16)param.channel_name.size();
			nStream::Write(st,tempSizechannel_name);
			for(nMech::uint16 iTempchannel_name=0;iTempchannel_name<tempSizechannel_name; ++iTempchannel_name){
			nStream::Write(st,param.channel_name[iTempchannel_name]);
			}
			nMech::uint16 tempSizebuzy_level= (nMech::uint16)param.buzy_level.size();
			nStream::Write(st,tempSizebuzy_level);
			for(nMech::uint16 iTempbuzy_level=0;iTempbuzy_level<tempSizebuzy_level; ++iTempbuzy_level){
			nStream::Write(st,param.buzy_level[iTempbuzy_level]);
			}
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_L2X_CHANNEL_LIST;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" L2X_CHANNEL_LIST :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" L2X_CHANNEL_LIST :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_L2X_CHANNEL_LIST(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const std::vector<serverid_t> &_channel, const std::vector<astring> &_channel_name, const std::vector<uint8> &_buzy_level)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizechannel = (nMech::uint16)_channel.size();
			nStream::Write(st,tempSizechannel);
			for(nMech::uint16 iTempchannel=0;iTempchannel<tempSizechannel; ++iTempchannel){
			nStream::Write(st,_channel[iTempchannel]);
			}
			nMech::uint16 tempSizechannel_name = (nMech::uint16)_channel_name.size();
			nStream::Write(st,tempSizechannel_name);
			for(nMech::uint16 iTempchannel_name=0;iTempchannel_name<tempSizechannel_name; ++iTempchannel_name){
			nStream::Write(st,_channel_name[iTempchannel_name]);
			}
			nMech::uint16 tempSizebuzy_level = (nMech::uint16)_buzy_level.size();
			nStream::Write(st,tempSizebuzy_level);
			for(nMech::uint16 iTempbuzy_level=0;iTempbuzy_level<tempSizebuzy_level; ++iTempbuzy_level){
			nStream::Write(st,_buzy_level[iTempbuzy_level]);
			}
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_L2X_CHANNEL_LIST;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" L2X_CHANNEL_LIST :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" L2X_CHANNEL_LIST :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_LoginServer

}/*nLoginServer */ }/* nNET*/ } //nMech
#endif //LoginServer___L2X_CHANNEL_LIST__