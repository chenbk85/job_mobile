
#ifndef CentralServer___C2_NOTICE__ 
#define CentralServer___C2_NOTICE__

#ifndef CentralServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_CentralServer(CentralServer);
jxDECL_CentralServer(C2_NOTICE);
#endif //CentralServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nCentralServer
{
	const int pk_C2_NOTICE = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+14;
	/* jNoticeInfo info;*/
	/* wname1024_t msg;*/
	/* aname32_t date;*/
	
	struct S_C2_NOTICE;
	bool READ_C2_NOTICE(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_C2_NOTICE &param);
	struct S_C2_NOTICE
	{
		jNoticeInfo info;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_CentralServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_CentralServer

		wname1024_t msg;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_CentralServer
					void set_msg(tcstr sz){jw_strncpy(msg,nUNI::scb1024_t(sz).getW(), 1024);	msg[1024-1]=0;}
					tcstr get_msg(fname_t _buf){jt_strncpy(_buf, nUNI::scb1024_t(msg).getT() , 1024);_buf[1024-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_CentralServer

		aname32_t date;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_CentralServer
					void set_date(tcstr sz){ja_strncpy(date,nUNI::scb1024_t(sz).getA(), 32);	date[32-1]=0;}
					tcstr get_date(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(date).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_CentralServer


		#ifndef jNOT_USE_DebugPrint_CentralServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< C2_NOTICE > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("info"),info);
			jDebugPrint(_T("msg"),msg);
			jDebugPrint(_T("date"),date);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_C2_NOTICE(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_CentralServer
	
	inline bool READ_C2_NOTICE(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_C2_NOTICE &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.info);
		nStream::Read(st,param.msg, 1024);
		nStream::Read(st,param.date, 32);
		
		#ifndef jNOT_USE_DebugPrint_CentralServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("C2_NOTICE : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_CentralServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_CentralServer
	inline jPacket_Base WRITE_C2_NOTICE(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_C2_NOTICE &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.info);
			nStream::Write(st,param.msg);
			nStream::Write(st,param.date);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_C2_NOTICE;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" C2_NOTICE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" C2_NOTICE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_C2_NOTICE(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const jNoticeInfo &_info,  wcstr _msg,  acstr _date)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_info);
			nStream::Write(st,_msg);
			nStream::Write(st,_date);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_C2_NOTICE;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" C2_NOTICE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" C2_NOTICE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_CentralServer

}/*nCentralServer */ }/* nNET*/ } //nMech
#endif //CentralServer___C2_NOTICE__