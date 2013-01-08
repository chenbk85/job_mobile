
#ifndef OrbHost___H_GET_XML__ 
#define OrbHost___H_GET_XML__

#ifndef OrbHost_jNOTUSE_PACKET_JXDEFINE
jxDECL_OrbHost(OrbHost);
jxDECL_OrbHost(H_GET_XML);
#endif //OrbHost_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nOrbHost
{
	/*[[ 해당 XML을 요청하는 메세지 ]]*/
	const int pk_H_GET_XML = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+14;
	/* tname256_t szXml;*/
	
	struct S_H_GET_XML;
	bool READ_H_GET_XML(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_H_GET_XML &param);
	struct S_H_GET_XML
	{
		tname256_t szXml;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_OrbHost
					void set_szXml(tcstr sz){jt_strncpy(szXml,nUNI::scb1024_t(sz).getT(), 256);	szXml[256-1]=0;}
					tcstr get_szXml(fname_t _buf){jt_strncpy(_buf, nUNI::scb256_t(szXml).getT() , 256);_buf[256-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_OrbHost


		#ifndef jNOT_USE_DebugPrint_OrbHost
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< H_GET_XML > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("szXml"),szXml);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_H_GET_XML(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_OrbHost
	
	inline bool READ_H_GET_XML(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_H_GET_XML &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.szXml, 256);
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("H_GET_XML : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_OrbHost

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_OrbHost
	inline jPacket_Base WRITE_H_GET_XML(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_H_GET_XML &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.szXml);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_H_GET_XML;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" H_GET_XML :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" H_GET_XML :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_H_GET_XML(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  tcstr _szXml)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_szXml);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_H_GET_XML;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" H_GET_XML :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" H_GET_XML :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_OrbHost

}/*nOrbHost */ }/* nNET*/ } //nMech
#endif //OrbHost___H_GET_XML__