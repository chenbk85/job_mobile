
#ifndef UserServer___U4_USER_CONNECTION_NOTIFY__ 
#define UserServer___U4_USER_CONNECTION_NOTIFY__

#ifndef UserServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_UserServer(UserServer);
jxDECL_UserServer(U4_USER_CONNECTION_NOTIFY);
#endif //UserServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nUserServer
{
	/*[[ 약3초정도의 딜레이후 보낸다. ]]*/
	const int pk_U4_USER_CONNECTION_NOTIFY = /*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+1;
	/* wstring id_connect[-1];*/
	/* wstring id_disconnect[-1];*/
	
	struct S_U4_USER_CONNECTION_NOTIFY;
	bool READ_U4_USER_CONNECTION_NOTIFY(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_U4_USER_CONNECTION_NOTIFY &param);
	struct S_U4_USER_CONNECTION_NOTIFY
	{
		std::vector<wstring> id_connect;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_UserServer
		wstring* get_id_connect(int i){ return &id_connect[i];}
		void 	set_id_connect(int i, wstring* v){ id_connect[i] = *v;}
		void insert_id_connect(wstring* v){ id_connect.push_back(*v);}
		void clear_id_connect(){ id_connect.clear();}
		size_t size_id_connect(){ return id_connect.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_UserServer

		std::vector<wstring> id_disconnect;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_UserServer
		wstring* get_id_disconnect(int i){ return &id_disconnect[i];}
		void 	set_id_disconnect(int i, wstring* v){ id_disconnect[i] = *v;}
		void insert_id_disconnect(wstring* v){ id_disconnect.push_back(*v);}
		void clear_id_disconnect(){ id_disconnect.clear();}
		size_t size_id_disconnect(){ return id_disconnect.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_UserServer


		#ifndef jNOT_USE_DebugPrint_UserServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< U4_USER_CONNECTION_NOTIFY > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("id_connect"),id_connect);
			jDebugPrint(_T("id_disconnect"),id_disconnect);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_U4_USER_CONNECTION_NOTIFY(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_UserServer
	
	inline bool READ_U4_USER_CONNECTION_NOTIFY(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_U4_USER_CONNECTION_NOTIFY &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nMech::uint16 tempSizeid_connect;
		nStream::Read(st,tempSizeid_connect);
		param.id_connect.resize(tempSizeid_connect);
		for(nMech::uint16 iTempid_connect=0;iTempid_connect<tempSizeid_connect; ++iTempid_connect){
		nStream::Read(st,param.id_connect[iTempid_connect]);
		}
		nMech::uint16 tempSizeid_disconnect;
		nStream::Read(st,tempSizeid_disconnect);
		param.id_disconnect.resize(tempSizeid_disconnect);
		for(nMech::uint16 iTempid_disconnect=0;iTempid_disconnect<tempSizeid_disconnect; ++iTempid_disconnect){
		nStream::Read(st,param.id_disconnect[iTempid_disconnect]);
		}
		
		#ifndef jNOT_USE_DebugPrint_UserServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("U4_USER_CONNECTION_NOTIFY : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_UserServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_UserServer
	inline jPacket_Base WRITE_U4_USER_CONNECTION_NOTIFY(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_U4_USER_CONNECTION_NOTIFY &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizeid_connect= (nMech::uint16)param.id_connect.size();
			nStream::Write(st,tempSizeid_connect);
			for(nMech::uint16 iTempid_connect=0;iTempid_connect<tempSizeid_connect; ++iTempid_connect){
			nStream::Write(st,param.id_connect[iTempid_connect]);
			}
			nMech::uint16 tempSizeid_disconnect= (nMech::uint16)param.id_disconnect.size();
			nStream::Write(st,tempSizeid_disconnect);
			for(nMech::uint16 iTempid_disconnect=0;iTempid_disconnect<tempSizeid_disconnect; ++iTempid_disconnect){
			nStream::Write(st,param.id_disconnect[iTempid_disconnect]);
			}
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_U4_USER_CONNECTION_NOTIFY;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" U4_USER_CONNECTION_NOTIFY :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" U4_USER_CONNECTION_NOTIFY :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_U4_USER_CONNECTION_NOTIFY(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const std::vector<wstring> &_id_connect, const std::vector<wstring> &_id_disconnect)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nMech::uint16 tempSizeid_connect = (nMech::uint16)_id_connect.size();
			nStream::Write(st,tempSizeid_connect);
			for(nMech::uint16 iTempid_connect=0;iTempid_connect<tempSizeid_connect; ++iTempid_connect){
			nStream::Write(st,_id_connect[iTempid_connect]);
			}
			nMech::uint16 tempSizeid_disconnect = (nMech::uint16)_id_disconnect.size();
			nStream::Write(st,tempSizeid_disconnect);
			for(nMech::uint16 iTempid_disconnect=0;iTempid_disconnect<tempSizeid_disconnect; ++iTempid_disconnect){
			nStream::Write(st,_id_disconnect[iTempid_disconnect]);
			}
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_U4_USER_CONNECTION_NOTIFY;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" U4_USER_CONNECTION_NOTIFY :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" U4_USER_CONNECTION_NOTIFY :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_UserServer

}/*nUserServer */ }/* nNET*/ } //nMech
#endif //UserServer___U4_USER_CONNECTION_NOTIFY__