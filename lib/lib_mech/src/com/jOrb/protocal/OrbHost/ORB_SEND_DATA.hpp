
#ifndef OrbHost___ORB_SEND_DATA__ 
#define OrbHost___ORB_SEND_DATA__

#ifndef OrbHost_jNOTUSE_PACKET_JXDEFINE
jxDECL_OrbHost(OrbHost);
jxDECL_OrbHost(ORB_SEND_DATA);
#endif //OrbHost_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nOrbHost
{
	const int pk_ORB_SEND_DATA = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+12;
	/* tname32_t name;*/
	/* BYTE data[-1];*/
	
	struct S_ORB_SEND_DATA;
	bool READ_ORB_SEND_DATA(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_ORB_SEND_DATA &param);
	struct S_ORB_SEND_DATA
	{
		tname32_t name;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_OrbHost
					void set_name(tcstr sz){jt_strncpy(name,nUNI::scb1024_t(sz).getT(), 32);	name[32-1]=0;}
					tcstr get_name(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(name).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_OrbHost

		std::vector<BYTE> data;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_OrbHost
		BYTE* get_data(int i){ return &data[i];}
		void 	set_data(int i, BYTE* v){ data[i] = *v;}
		void insert_data(BYTE* v){ data.push_back(*v);}
		void clear_data(){ data.clear();}
		size_t size_data(){ return data.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_OrbHost


		#ifndef jNOT_USE_DebugPrint_OrbHost
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< ORB_SEND_DATA > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("name"),name);
			jDebugPrint(_T("data"),data);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_ORB_SEND_DATA(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_OrbHost
	
	inline bool READ_ORB_SEND_DATA(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_ORB_SEND_DATA &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.name, 32);
		nMech::uint16 tempSizedata;
		nStream::Read(st,tempSizedata);
		param.data.resize(tempSizedata);
		for(nMech::uint16 iTempdata=0;iTempdata<tempSizedata; ++iTempdata){
		nStream::Read(st,param.data[iTempdata]);
		}
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("ORB_SEND_DATA : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_OrbHost

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_OrbHost
	inline jPacket_Base WRITE_ORB_SEND_DATA(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_ORB_SEND_DATA &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.name);
			nMech::uint16 tempSizedata= (nMech::uint16)param.data.size();
			nStream::Write(st,tempSizedata);
			for(nMech::uint16 iTempdata=0;iTempdata<tempSizedata; ++iTempdata){
			nStream::Write(st,param.data[iTempdata]);
			}
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_ORB_SEND_DATA;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" ORB_SEND_DATA :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" ORB_SEND_DATA :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_ORB_SEND_DATA(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  tcstr _name, const std::vector<BYTE> &_data)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_name);
			nMech::uint16 tempSizedata = (nMech::uint16)_data.size();
			nStream::Write(st,tempSizedata);
			for(nMech::uint16 iTempdata=0;iTempdata<tempSizedata; ++iTempdata){
			nStream::Write(st,_data[iTempdata]);
			}
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_ORB_SEND_DATA;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" ORB_SEND_DATA :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" ORB_SEND_DATA :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_OrbHost

}/*nOrbHost */ }/* nNET*/ } //nMech
#endif //OrbHost___ORB_SEND_DATA__