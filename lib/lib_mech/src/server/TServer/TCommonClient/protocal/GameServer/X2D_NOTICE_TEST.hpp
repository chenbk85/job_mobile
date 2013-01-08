
#ifndef GameServer___X2D_NOTICE_TEST__ 
#define GameServer___X2D_NOTICE_TEST__

#ifndef GameServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_GameServer(GameServer);
jxDECL_GameServer(X2D_NOTICE_TEST);
#endif //GameServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nGameServer
{
	const int pk_X2D_NOTICE_TEST = /*nMech::nNET::EProtocal_jINet_OGS_END+*/3000+5;
	/* jNoticeInfo info;*/
	/* wname1024_t msg;*/
	/* aname32_t date;*/
	
	struct S_X2D_NOTICE_TEST;
	bool READ_X2D_NOTICE_TEST(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_X2D_NOTICE_TEST &param);
	struct S_X2D_NOTICE_TEST
	{
		jNoticeInfo info;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_GameServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_GameServer

		wname1024_t msg;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_GameServer
					void set_msg(tcstr sz){jw_strncpy(msg,nUNI::scb1024_t(sz).getW(), 1024);	msg[1024-1]=0;}
					tcstr get_msg(fname_t _buf){jt_strncpy(_buf, nUNI::scb1024_t(msg).getT() , 1024);_buf[1024-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_GameServer

		aname32_t date;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_GameServer
					void set_date(tcstr sz){ja_strncpy(date,nUNI::scb1024_t(sz).getA(), 32);	date[32-1]=0;}
					tcstr get_date(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(date).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_GameServer


		#ifndef jNOT_USE_DebugPrint_GameServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< X2D_NOTICE_TEST > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("info"),info);
			jDebugPrint(_T("msg"),msg);
			jDebugPrint(_T("date"),date);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_X2D_NOTICE_TEST(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_GameServer
	
	inline bool READ_X2D_NOTICE_TEST(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_X2D_NOTICE_TEST &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.info);
		nStream::Read(st,param.msg, 1024);
		nStream::Read(st,param.date, 32);
		
		#ifndef jNOT_USE_DebugPrint_GameServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("X2D_NOTICE_TEST : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_GameServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_GameServer
	inline jPacket_Base WRITE_X2D_NOTICE_TEST(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_X2D_NOTICE_TEST &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.info);
			nStream::Write(st,param.msg);
			nStream::Write(st,param.date);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_X2D_NOTICE_TEST;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2D_NOTICE_TEST :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2D_NOTICE_TEST :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_X2D_NOTICE_TEST(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const jNoticeInfo &_info,  wcstr _msg,  acstr _date)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_info);
			nStream::Write(st,_msg);
			nStream::Write(st,_date);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_X2D_NOTICE_TEST;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2D_NOTICE_TEST :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2D_NOTICE_TEST :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_GameServer

}/*nGameServer */ }/* nNET*/ } //nMech
#endif //GameServer___X2D_NOTICE_TEST__