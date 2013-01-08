
#ifndef LoginServer___L2X_NOTICE__ 
#define LoginServer___L2X_NOTICE__

#ifndef LoginServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_LoginServer(LoginServer);
jxDECL_LoginServer(L2X_NOTICE);
#endif //LoginServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nLoginServer
{
	const int pk_L2X_NOTICE = /*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+4;
	/* jNoticeInfo info;*/
	/* wname1024_t msg;*/
	/* aname32_t date;*/
	
	struct S_L2X_NOTICE;
	bool READ_L2X_NOTICE(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_L2X_NOTICE &param);
	struct S_L2X_NOTICE
	{
		jNoticeInfo info;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_LoginServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_LoginServer

		wname1024_t msg;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_LoginServer
					void set_msg(tcstr sz){jw_strncpy(msg,nUNI::scb1024_t(sz).getW(), 1024);	msg[1024-1]=0;}
					tcstr get_msg(fname_t _buf){jt_strncpy(_buf, nUNI::scb1024_t(msg).getT() , 1024);_buf[1024-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_LoginServer

		aname32_t date;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_LoginServer
					void set_date(tcstr sz){ja_strncpy(date,nUNI::scb1024_t(sz).getA(), 32);	date[32-1]=0;}
					tcstr get_date(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(date).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_LoginServer


		#ifndef jNOT_USE_DebugPrint_LoginServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< L2X_NOTICE > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("info"),info);
			jDebugPrint(_T("msg"),msg);
			jDebugPrint(_T("date"),date);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_L2X_NOTICE(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_LoginServer
	
	inline bool READ_L2X_NOTICE(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_L2X_NOTICE &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.info);
		nStream::Read(st,param.msg, 1024);
		nStream::Read(st,param.date, 32);
		
		#ifndef jNOT_USE_DebugPrint_LoginServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("L2X_NOTICE : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_LoginServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_LoginServer
	inline jPacket_Base WRITE_L2X_NOTICE(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_L2X_NOTICE &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.info);
			nStream::Write(st,param.msg);
			nStream::Write(st,param.date);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_L2X_NOTICE;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" L2X_NOTICE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" L2X_NOTICE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_L2X_NOTICE(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const jNoticeInfo &_info,  wcstr _msg,  acstr _date)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_info);
			nStream::Write(st,_msg);
			nStream::Write(st,_date);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_L2X_NOTICE;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" L2X_NOTICE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" L2X_NOTICE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_LoginServer

}/*nLoginServer */ }/* nNET*/ } //nMech
#endif //LoginServer___L2X_NOTICE__